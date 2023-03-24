/*************************************************************************/
/* Copyright (c) 2004                                                    */
/* Daniel Sleator, David Temperley, and John Lafferty                    */
/* All rights reserved                                                   */
/*                                                                       */
/* Use of the link grammar parsing system is subject to the terms of the */
/* license set forth in the LICENSE file included with this softwares.   */ 
/* This license allows free redistribution and use in source and binary  */
/* forms, with or without modification, subject to certain conditions.   */
/*                                                                       */
/*************************************************************************/

#ifndef _LINK_GRAMMAR_DISJUNCT_UTILS_H_
#define _LINK_GRAMMAR_DISJUNCT_UTILS_H_

#include "api-types.h"
#include "structures.h"

/* Disjunct utilities ... */
void free_disjuncts(Disjunct *);
unsigned int count_disjuncts(Disjunct *);
Disjunct * catenate_disjuncts(Disjunct *, Disjunct *);
Disjunct * eliminate_duplicate_disjuncts(Disjunct * );
char * print_one_disjunct(Disjunct *);
void word_record_in_disjunct(const Gword *, Disjunct *);
void disjunct_word_print(Disjunct *);

#endif /* _LINK_GRAMMAR_DISJUNCT_UTILS_H_ */
