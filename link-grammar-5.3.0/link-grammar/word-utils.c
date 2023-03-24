/*************************************************************************/
/* Copyright (c) 2004                                                    */
/* Daniel Sleator, David Temperley, and John Lafferty                    */
/* Copyright (c) 2013 Linas Vepstas                                      */
/* All rights reserved                                                   */
/*                                                                       */
/* Use of the link grammar parsing system is subject to the terms of the */
/* license set forth in the LICENSE file included with this software.    */
/* This license allows free redistribution and use in source and binary  */
/* forms, with or without modification, subject to certain conditions.   */
/*                                                                       */
/*************************************************************************/
/*
 * Miscellaneous utilities for dealing with word types.
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>

#include "count.h"
#include "dict-api.h"
#include "disjunct-utils.h"
#include "word-utils.h"

/* ======================================================== */
/* Exp utilities ... */

void free_E_list(E_list *);
void free_Exp(Exp * e)
{
	if (e->type != CONNECTOR_type) {
		free_E_list(e->u.l);
	}
	xfree((char *)e, sizeof(Exp));
}

void free_E_list(E_list * l)
{
	if (l == NULL) return;
	free_E_list(l->next);
	free_Exp(l->e);
	xfree((char *)l, sizeof(E_list));
}

/* Returns the number of connectors in the expression e */
int size_of_expression(Exp * e)
{
	int size;
	E_list * l;
	if (e->type == CONNECTOR_type) return 1;
	size = 0;
	for (l=e->u.l; l!=NULL; l=l->next) {
		size += size_of_expression(l->e);
	}
	return size;
}

/**
 * Build a copy of the given expression (don't copy strings, of course)
 */
static E_list * copy_E_list(E_list * l);
Exp * copy_Exp(Exp * e)
{
	Exp * n;
	if (e == NULL) return NULL;
	n = (Exp *) xalloc(sizeof(Exp));
	*n = *e;
	if (e->type != CONNECTOR_type) {
		n->u.l = copy_E_list(e->u.l);
	}
	return n;
}

static E_list * copy_E_list(E_list * l)
{
	E_list * nl;
	if (l == NULL) return NULL;
	nl = (E_list *) xalloc(sizeof(E_list));
	nl->next = copy_E_list(l->next);
	nl->e = copy_Exp(l->e);
	return nl;
}

/**
 * Compare two expressions, return 1 for equal, 0 for unequal
 */
static int exp_compare(Exp * e1, Exp * e2)
{
	E_list *el1, *el2;

	if ((e1 == NULL) && (e2 == NULL))
	  return 1; /* they are equal */
	if ((e1 == NULL) || (e2 == NULL))
	  return 0; /* they are not equal */
	if (e1->type != e2->type)
		return 0;
	if (fabs (e1->cost - e2->cost) > 0.001)
		return 0;
	if (e1->type == CONNECTOR_type)
	{
		if (e1->dir != e2->dir)
			return 0;
		/* printf("%s %s\n",e1->u.string,e2->u.string); */
		if (strcmp(e1->u.string,e2->u.string)!=0)
			return 0;
	}
	else
	{
		el1 = e1->u.l;
		el2 = e2->u.l;
		/* while at least 1 is non-null */
		for (;(el1!=NULL)||(el2!=NULL);) {
		  /*fail if 1 is null */
			if ((el1==NULL)||(el2==NULL))
				return 0;
			/* fail if they are not compared */
			if (exp_compare(el1->e, el2->e) == 0)
				return 0;
			if (el1!=NULL)
				el1 = el1->next;
			if (el2!=NULL)
				el2 = el2->next;
		}
	}
	return 1; /* if never returned 0, return 1 */
}

/**
 * Sub-expression matcher -- return 1 if sub is non-NULL and
 * contained in super, 0 otherwise.
 */
static int exp_contains(Exp * super, Exp * sub)
{
	E_list * el;

#if 0 /* DEBUG */
	printf("SUP: ");
	if (super) print_expression(super);
	printf("\n");
#endif

	if (sub==NULL || super==NULL)
		return 0;
	if (exp_compare(sub,super)==1)
		return 1;
	if (super->type==CONNECTOR_type)
	  return 0; /* super is a leaf */

	/* proceed through supers children and return 1 if sub
	   is contained in any of them */
	for(el = super->u.l; el!=NULL; el=el->next) {
		if (exp_contains(el->e, sub)==1)
			return 1;
	}
	return 0;
}

/* ======================================================== */
/* X_node utilities ... */
/**
 * frees the list of X_nodes pointed to by x, and all of the expressions
 */
void free_X_nodes(X_node * x)
{
	X_node * y;
	for (; x!= NULL; x = y) {
		y = x->next;
		free_Exp(x->exp);
		xfree((char *)x, sizeof(X_node));
	}
}

/**
 * Destructively catenates the two disjunct lists d1 followed by d2.
 * Doesn't change the contents of the disjuncts.
 * Traverses the first list, but not the second.
 */
X_node * catenate_X_nodes(X_node *d1, X_node *d2)
{
	X_node * dis = d1;

	if (d1 == NULL) return d2;
	if (d2 == NULL) return d1;
	while (dis->next != NULL) dis = dis->next;
	dis->next = d2;
	return d1;
}

/* ======================================================== */
/* Connector utilities ... */

/**
 * free_connectors() -- free the list of connectors pointed to by e
 * (does not free any strings)
 */
void free_connectors(Connector *e)
{
	Connector * n;
	for (; e != NULL; e = n)
	{
		n = e->next;
		xfree((char *)e, sizeof(Connector));
	}
}

Connector * connector_new(void)
{
	Connector *c = (Connector *) xalloc(sizeof(Connector));
	init_connector(c);
	c->string = "";
	c->multi = false;
	c->next = NULL;
	c->tableNext = NULL;
	return c;
}

/* ======================================================== */
/* Connector-set utilities ... */
/**
 * This hash function only looks at the leading upper case letters of
 * the string, and the direction, '+' or '-'.
 */
static unsigned int connector_set_hash(Connector_set *conset, const char * s, int d)
{
	unsigned int i;
	if (islower((int)*s)) s++; /* skip head-dependent indicator */

	/* djb2 hash */
	i = 5381;
	i = ((i << 5) + i) + d;
	while (isupper((int) *s)) /* connector tables cannot contain UTF8, yet */
	{
		i = ((i << 5) + i) + *s;
		s++;
	}
	return (i & (conset->table_size-1));
}

static void build_connector_set_from_expression(Connector_set * conset, Exp * e)
{
	E_list * l;
	Connector * c;
	unsigned int h;
	if (e->type == CONNECTOR_type)
	{
		c = connector_new();
		c->string = e->u.string;
		c->word = e->dir;       /* just use the word field to give the dir */
		h = connector_set_hash(conset, c->string, c->word);
		c->next = conset->hash_table[h];
		conset->hash_table[h] = c;
	} else {
		for (l=e->u.l; l!=NULL; l=l->next) {
			build_connector_set_from_expression(conset, l->e);
		}
	}
}

Connector_set * connector_set_create(Exp *e)
{
	unsigned int i;
	Connector_set *conset;

	conset = (Connector_set *) xalloc(sizeof(Connector_set));
	conset->table_size = next_power_of_two_up(size_of_expression(e));
	conset->hash_table =
	  (Connector **) xalloc(conset->table_size * sizeof(Connector *));
	for (i=0; i<conset->table_size; i++) conset->hash_table[i] = NULL;
	build_connector_set_from_expression(conset, e);
	return conset;
}

void connector_set_delete(Connector_set * conset)
{
	unsigned int i;
	if (conset == NULL) return;
	for (i=0; i<conset->table_size; i++) free_connectors(conset->hash_table[i]);
	xfree(conset->hash_table, conset->table_size * sizeof(Connector *));
	xfree(conset, sizeof(Connector_set));
}

/**
 * Returns TRUE the given connector is in this conset.  FALSE otherwise.
 * d='+' means this connector is on the right side of the disjunct.
 * d='-' means this connector is on the left side of the disjunct.
 */

bool match_in_connector_set(Connector_set *conset, Connector * c)
{
	unsigned int h;
	Connector * c1;
	if (conset == NULL) return false;
	h = connector_set_hash(conset, c->string, '+');
	for (c1 = conset->hash_table[h]; c1 != NULL; c1 = c1->next)
	{
		if (easy_match(c1->string, c->string)) return true;
	}
	return false;
}

/* ======================================================== */
/* More connector utilities ... */

/**
 * word_has_connector() -- return TRUE if dictionary expression has connector
 * This function takes a dict_node (corresponding to an entry in a
 * given dictionary), a string (representing a connector), and a
 * direction (+ = right-pointing, '-' = left-pointing); it returns true
 * if the dictionary expression for the word includes the connector,
 * false otherwise.  This can be used to see if a word is in a certain
 * category (checking for a category connector in a table), or to see
 * if a word has a connector in a normal dictionary. The connector
 * check uses a "smart-match", the same kind used by the parser.
 */
#if CRAZY_OBESE_CHECKING_AGLO
bool word_has_connector(Dict_node * dn, const char * cs, char direction)
{
	Connector * c2 = NULL;
	Disjunct *d, *d0;
	if (dn == NULL) return false;
	d0 = d = build_disjuncts_for_dict_node(dn);
	if (d == NULL) return false;
	for (; d != NULL; d = d->next) {
		if (direction == '+') c2 = d->right;
		if (direction == '-') c2 = d->left;
		for (; c2 != NULL; c2 = c2->next) {
			if (easy_match(c2->string, cs)) {
				free_disjuncts(d0);
				return true;
			}
		}
	}
	free_disjuncts(d0);
	return false;
}
#else /* CRAZY_OBESE_CHECKING_AGLO */

static bool exp_has_connector(Exp * e, const char * cs, char direction)
{
	E_list * el;
	if (e->type == CONNECTOR_type)
	{
		if (direction == e->dir)
			return easy_match(e->u.string, cs);
		return false;
	}
	for (el = e->u.l; el != NULL; el = el->next)
	{
		if (exp_has_connector(el->e, cs, direction)) return false;
	}
	return false;
}

bool word_has_connector(Dict_node * dn, const char * cs, char direction)
{
	return exp_has_connector(dn->exp, cs, direction);
}
#endif /* CRAZY_OBESE_CHECKING_AGLO */

/**
 * If word has a connector, return it.
 * If word has more than one connector, return NULL.
 */
const char * word_only_connector(Dict_node * dn)
{
	Exp * e = dn->exp;
	if (CONNECTOR_type == e->type)
		return e->u.string;
	return NULL;
}

/* ======================================================== */
/* Dictionary utilities ... */

static bool dn_word_contains(Dictionary dict,
                             Dict_node * w_dn, const char * macro)
{
	Exp * m_exp;
	Dict_node *m_dn;

	if (w_dn == NULL) return false;

	m_dn = dictionary_lookup_list(dict, macro);
	if (m_dn == NULL) return false;

	m_exp = m_dn->exp;

#if 0 /* DEBUG */
	printf("\nWORD: ");
	print_expression(w_dn->exp);
	printf("\nMACR: ");
	print_expression(m_exp);
	printf("\n");
#endif

	for (;w_dn != NULL; w_dn = w_dn->right)
	{
		if (1 == exp_contains(w_dn->exp, m_exp))
		{
			free_lookup_list(dict, m_dn);
			return true;
		}
	}
	free_lookup_list(dict, m_dn);
	return false;
}

/**
 * word_contains: return true if the word may involve application of
 * a rule.
 *
 * @return: true if word's expression contains macro's expression,
 * false otherwise.
 */
bool word_contains(Dictionary dict, const char * word, const char * macro)
{
	Dict_node *w_dn = abridged_lookup_list(dict, word);
	bool ret = dn_word_contains(dict, w_dn, macro);
	free_lookup_list(dict, w_dn);
	return ret;
}

/**
 * This hash function only looks at the leading upper case letters of
 * the connector string, and the label fields.  This ensures that if two
 * strings match (formally), then they must hash to the same place.
 */
int calculate_connector_hash(Connector * c)
{
	const char *s;
	unsigned int i;

	/* For most situations, all three hashes are very nearly equal;
	 * as to which is faster depends on the parsed text.
	 * For both English and Russian, there are about 100 pre-defined
	 * connectors, and another 2K-4K autogen'ed ones (the IDxxx idiom
	 * connectors, and the LLxxx suffix connectors for Russian).
	 * Turns out the cost of setting up the hash table dominates the
	 * cost of collisions. */
#ifdef USE_DJB2
	/* djb2 hash */
	i = 5381;
	s = c->string;
	if (islower((int) *s)) s++; /* ignore head-dependent indicator */
	while (isupper((int) *s)) /* connector tables cannot contain UTF8, yet */
	{
		i = ((i << 5) + i) + *s;
		s++;
	}
	i += i>>14;
#endif /* USE_DJB2 */

#define USE_JENKINS
#ifdef USE_JENKINS
	/* Jenkins one-at-a-time hash */
	i = 0;
	s = c->string;
	if (islower((int) *s)) s++; /* ignore head-dependent indicator */
	while (isupper((int) *s)) /* connector tables cannot contain UTF8, yet */
	{
		i += *s;
		i += (i<<10);
		i ^= (i>>6);
		s++;
	}
	i += (i << 3);
	i ^= (i >> 11);
	i += (i << 15);
#endif /* USE_JENKINS */

#ifdef USE_SDBM
	/* sdbm hash */
	i = 0;
	s = c->string;
	if (islower((int) *s)) s++; /* ignore head-dependent indicator */
	while (isupper((int) *s))
	{
		i = *s + (i << 6) + (i << 16) - i;
		s++;
	}
#endif /* USE_SDBM */

	c->hash = i;
	return i;
}

/* ========================= END OF FILE ============================== */
