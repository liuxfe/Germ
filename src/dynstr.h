/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _DYNSTR_H
#define _DYNSTR_H

struct _dynstr {
	uint nalloc;
	uint len;
	uint hkey;
	char data[0];
};
typedef struct _dynstr dynstr;

dynstr* newDynstr();
dynstr* appendChar(dynstr* , char);
dynstr* createDynstr(char* , char *);
void printDynstr(dynstr*);

#endif