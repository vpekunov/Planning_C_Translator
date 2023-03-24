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

#include <stdarg.h>
#include "print-util.h"
#include "utilities.h"

/* This is a "safe" append function, used here to build up a link diagram
   incrementally.  Because the diagram is built up a few characters at
   a time, we keep around a pointer to the end of string to prevent
   the algorithm from being quadratic. */

struct String_s
{
	size_t allocated;  /* Unsigned so VC++ doesn't complain about comparisons */
	size_t eos; /* offset to end of string */
	char * p;
};

String * string_new(void)
{
#define INITSZ 30
	String * string;
	string = (String *) exalloc(sizeof(String));
	string->allocated = INITSZ;
	string->p = (char *) exalloc(INITSZ*sizeof(char));
	string->p[0] = '\0';
	string->eos = 0;
	return string;
}

void string_delete(String *s)
{
	exfree(s->p, s->allocated*sizeof(char));
	exfree(s, sizeof(String));
}

const char * string_value(String *s)
{
	return s->p;
}

char * string_copy(String *s)
{
	char * p = (char *) exalloc(s->eos + 1);
	strcpy(p, s->p);
	return p;
}

void append_string(String * string, const char *fmt, ...)
{
#define TMPLEN 1024
	char temp_buffer[TMPLEN];
	char * temp_string = temp_buffer;
	size_t templen;
	va_list args;
#ifdef _MSC_VER
	char * tmp = alloca(strlen(fmt)+1);
	char * tok = tmp;

	strcpy(tmp, fmt);
	while ((tok = strstr(tok, "%zu"))) { tok[1] = 'I'; tok++;}
	fmt = tmp;
#endif

	va_start(args, fmt);
	templen = vsnprintf(temp_string, TMPLEN, fmt, args);
	if ((int)templen < 0) goto error;
	if (templen >= TMPLEN)
	{
		/* TMPLEN is too small - use a bigger buffer */
		templen = vsnprintf(NULL, 0, fmt, args);
		if ((int)templen < 0) goto error;

		temp_string = alloca(templen+1);
		templen = vsnprintf(temp_string, templen+1, fmt, args);
		if ((int)templen < 0) goto error;
	}
	va_end(args);

	if (string->allocated <= string->eos + templen)
	{
		string->allocated = 2 * string->allocated + templen + 1;
		string->p = (char *)realloc(string->p, string->allocated);
	}
	strcpy(string->p + string->eos, temp_string);
	string->eos += templen;
	return;

error:
	/* Some error has occurred */
	prt_error("Error: append_string(): "
				 "vsnprintf() returned a negative value");
}

size_t append_utf8_char(String * string, const char * mbs)
{
	/* Copy exactly one multi-byte character to buf */
	char buf[10];
	size_t n = utf8_next(mbs);

	assert(n<10, "Multi-byte character is too long!");
	strncpy(buf, mbs, n);
	buf[n] = 0;
	append_string(string, "%s", buf);
	return n;
}
