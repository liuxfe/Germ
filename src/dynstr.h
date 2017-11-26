/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _DYNSTR_H
#define _DYNSTR_H

struct _dynstr {
	uint nalloc;
	uint nchars;
	char data[0];
};
typedef struct _dynstr dynstr;

dynstr* newDynstr();
dynstr* growDynstr(dynstr*);
dynstr* appendChar(dynstr*, char);
dynstr* scanStrLiteral(char**);
void deleteDynstr(dynstr*);
void printDynstr(dynstr*);

#endif