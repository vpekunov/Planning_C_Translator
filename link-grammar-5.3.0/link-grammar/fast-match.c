/**************************************************************************/
/* Copyright (c) 2004                                                     */
/* Daniel Sleator, David Temperley, and John Lafferty                     */
/* Copyright (c) 2014 Linas Vepstas                                       */
/* All rights reserved                                                    */
/*                                                                        */
/* Use of the link grammar parsing system is subject to the terms of the  */
/* license set forth in the LICENSE file included with this software.     */
/* This license allows free redistribution and use in source and binary   */
/* forms, with or without modification, subject to certain conditions.    */
/*                                                                        */
/**************************************************************************/

#include "api-structures.h"
#include "externs.h"
#include "fast-match.h"
#include "word-utils.h"

/**
 * The entire goal of this file is provide a fast lookup of all of the
 * disjuncts on a given word that might be able to connect to a given
 * connector on the left or the right. The main entry point is
 * form_match_list(), which performs this lookup.
 *
 * The lookup is fast, because it uses a precomputed lookup table to
 * find the match candidates.  The lookup table is stocked by looking
 * at all disjuncts on all words, and sorting them into bins organized
 * by connectors they could potentially connect to.  The lookup table
 * is created by calling the alloc_fast_matcher() function.
 *
 * free_fast_matcher() is used to free the matcher.
 * put_match_list() releases the memory that form_match_list returned.
 */

/**
 * returns the number of disjuncts in the list that have non-null
 * left connector lists.
 */
static int left_disjunct_list_length(const Disjunct * d)
{
	int i;
	for (i=0; d!=NULL; d=d->next) {
		if (d->left != NULL) i++;
	}
	return i;
}

static int right_disjunct_list_length(const Disjunct * d)
{
	int i;
	for (i=0; d!=NULL; d=d->next) {
		if (d->right != NULL) i++;
	}
	return i;
}

struct fast_matcher_s
{
	size_t size;
	unsigned int *l_table_size;  /* the sizes of the hash tables */
	unsigned int *r_table_size;

	/* the beginnings of the hash tables */
	Match_node *** l_table;
	Match_node *** r_table;

	/* I'll pedantically maintain my own list of these cells */
	Match_node * mn_free_list;
};


/**
 * Return a match node to be used by the caller
 */
static Match_node * get_match_node(fast_matcher_t *ctxt)
{
	Match_node * m;
	if (ctxt->mn_free_list != NULL)
	{
		m = ctxt->mn_free_list;
		ctxt->mn_free_list = m->next;
	}
	else
	{
		m = (Match_node *) xalloc(sizeof(Match_node));
	}
	return m;
}

/**
 * Put these nodes back onto my free list
 */
void put_match_list(fast_matcher_t *ctxt, Match_node *m)
{
	Match_node * xm;

	for (; m != NULL; m = xm)
	{
		xm = m->next;
		m->next = ctxt->mn_free_list;
		ctxt->mn_free_list = m;
	}
}

static void free_match_list(Match_node * t)
{
	Match_node *xt;
	for (; t!=NULL; t=xt) {
		xt = t->next;
		xfree((char *)t, sizeof(Match_node));
	}
}

/**
 * Free all of the hash tables and Match_nodes
 */
void free_fast_matcher(fast_matcher_t *mchxt)
{
	size_t w;
	unsigned int i;

	for (w = 0; w < mchxt->size; w++)
	{
		for (i = 0; i < mchxt->l_table_size[w]; i++)
		{
			free_match_list(mchxt->l_table[w][i]);
		}
		xfree((char *)mchxt->l_table[w], mchxt->l_table_size[w] * sizeof (Match_node *));
		for (i = 0; i < mchxt->r_table_size[w]; i++)
		{
			free_match_list(mchxt->r_table[w][i]);
		}
		xfree((char *)mchxt->r_table[w], mchxt->r_table_size[w] * sizeof (Match_node *));
	}
	free_match_list(mchxt->mn_free_list);
	mchxt->mn_free_list = NULL;

	xfree(mchxt->l_table_size, mchxt->size * sizeof(unsigned int));
	xfree(mchxt->l_table, mchxt->size * sizeof(Match_node **));
	xfree(mchxt, sizeof(fast_matcher_t));
}

/**
 * Adds the match node m to the sorted list of match nodes l.
 * The parameter dir determines the order of the sorting to be used.
 * Makes the list sorted from smallest to largest.
 */
static Match_node * add_to_right_table_list(Match_node * m, Match_node * l)
{
	Match_node *p, *prev;

	if (l == NULL) return m;

	/* Insert m at head of list */
	if ((m->d->right->word) <= (l->d->right->word)) {
		m->next = l;
		return m;
	}

	/* Walk list to insertion point */
	prev = l;
	p = prev->next;
	while (p != NULL && ((m->d->right->word) > (p->d->right->word))) {
		prev = p;
		p = p->next;
	}

	m->next = p;
	prev->next = m;

	return l;  /* return pointer to original head */
}

/**
 * Adds the match node m to the sorted list of match nodes l.
 * The parameter dir determines the order of the sorting to be used.
 * Makes the list sorted from largest to smallest
 */
static Match_node * add_to_left_table_list(Match_node * m, Match_node * l)
{
	Match_node *p, *prev;

	if (l == NULL) return m;

	/* Insert m at head of list */
	if ((m->d->left->word) >= (l->d->left->word)) {
		m->next = l;
		return m;
	}

	/* Walk list to insertion point */
	prev = l;
	p = prev->next;
	while (p != NULL && ((m->d->left->word) < (p->d->left->word))) {
		prev = p;
		p = p->next;
	}

	m->next = p;
	prev->next = m;

	return l;  /* return pointer to original head */
}

/**
 * The disjunct d (whose left or right pointer points to c) is put
 * into the appropriate hash table
 * dir =  1, we're putting this into a right table.
 * dir = -1, we're putting this into a left table.
 */
static void put_into_match_table(unsigned int size, Match_node ** t,
								 Disjunct * d, Connector * c, int dir )
{
	unsigned int h;
	Match_node * m;
	h = connector_hash(c) & (size-1);
	m = (Match_node *) xalloc (sizeof(Match_node));
	m->next = NULL;
	m->d = d;
	if (dir == 1) {
		t[h] = add_to_right_table_list(m, t[h]);
	} else {
		t[h] = add_to_left_table_list(m, t[h]);
	}
}

fast_matcher_t* alloc_fast_matcher(const Sentence sent)
{
	unsigned int size;
	size_t w;
	int len;
	Match_node ** t;
	Disjunct * d;
	fast_matcher_t *ctxt;

	ctxt = (fast_matcher_t *) xalloc(sizeof(fast_matcher_t));
	ctxt->size = sent->length;
	ctxt->l_table_size = xalloc(2 * sent->length * sizeof(unsigned int));
	ctxt->r_table_size = ctxt->l_table_size + sent->length;
	ctxt->l_table = xalloc(2 * sent->length * sizeof(Match_node **));
	ctxt->r_table = ctxt->l_table + sent->length;
	memset(ctxt->l_table, 0, 2 * sent->length * sizeof(Match_node **));
	ctxt->mn_free_list = NULL;

	for (w=0; w<sent->length; w++)
	{
		len = left_disjunct_list_length(sent->word[w].d);
		size = next_power_of_two_up(len);
		ctxt->l_table_size[w] = size;
		t = ctxt->l_table[w] = (Match_node **) xalloc(size * sizeof(Match_node *));
		memset(t, 0, size * sizeof(Match_node *));

		for (d = sent->word[w].d; d != NULL; d = d->next)
		{
			if (d->left != NULL)
			{
				put_into_match_table(size, t, d, d->left, -1);
			}
		}

		len = right_disjunct_list_length(sent->word[w].d);
		size = next_power_of_two_up(len);
		ctxt->r_table_size[w] = size;
		t = ctxt->r_table[w] = (Match_node **) xalloc(size * sizeof(Match_node *));
		memset(t, 0, size * sizeof(Match_node *));

		for (d = sent->word[w].d; d != NULL; d = d->next)
		{
			if (d->right != NULL)
			{
				put_into_match_table(size, t, d, d->right, 1);
			}
		}
	}

	return ctxt;
}

/**
 * Forms and returns a list of disjuncts coming from word w, that might
 * match lc or rc or both. The lw and rw are the words from which lc
 * and rc came respectively.
 *
 * The list is returned in a linked list of Match_nodes.
 * The list contains no duplicates.
 */
Match_node *
form_match_list(fast_matcher_t *ctxt, int w,
                Connector *lc, int lw,
                Connector *rc, int rw)
{
	Match_node *ml, *mr, *mx, *my, *mr_end, *front;

	if (lc != NULL) {
		ml = ctxt->l_table[w][connector_hash(lc) & (ctxt->l_table_size[w]-1)];
	} else {
		ml = NULL;
	}
	if (rc != NULL) {
		mr = ctxt->r_table[w][connector_hash(rc) & (ctxt->r_table_size[w]-1)];
	} else {
		mr = NULL;
	}

	/* In order to eliminate duplicates from the lists, we mark the disjuncts. */
	for (mx = mr; mx != NULL; mx = mx->next)
	{
		if (mx->d->right->word > rw) break;
		mx->d->marked = true;
	}
	mr_end = mx;

	front = NULL;
	/* Construct the list of things that could match the left. */
	for (mx = ml; mx != NULL; mx = mx->next)
	{
		if (mx->d->left->word < lw) break;
		mx->d->marked = false;
		my = get_match_node(ctxt);
		my->d = mx->d;
		my->next = front;
		front = my;
	}

	/* Append the list of things that could match the right. */
	for (mx = mr; mx != mr_end; mx = mx->next)
	{
		if (mx->d->marked)
		{
			/* mx is not in the l list. */
			my = get_match_node(ctxt);
			my->d = mx->d;
			my->next = front;
			front = my;
		}
	}

	return front;
}
