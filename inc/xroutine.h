/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_XROUTINE_H
#define _ToHack_CL_XROUTINE_H

FILE* xfopen(char*, char*, char*, int);
void  xfclose(FILE*, char*, int);
void* xmalloc(uint, char*, int);
void  xfree(void*, char*, int);
void  xmemcpy(void*, void*, int);
int   xstrlen(char*);
int   xstrcmp(char*, char*);
bool  xstrncmp(char*, char*, int);
void  xstrncpy(char*, char*, int);
int   xhex2num(char);

#endif