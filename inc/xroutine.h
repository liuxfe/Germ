/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_XROUTINE_H
#define _ToHack_CL_XROUTINE_H

FILE* Xfopen(char*, char*, char*, int);
void  Xfclose(FILE*, char*, int);
void* Xmalloc(uint, char*, int);
void  Xfree(void*, char*, int);
void  Xmemcpy(void*, void*, int);
int   Xstrlen(char*);
bool  Xstrncmp(char*, char*, int);
void  Xstrncpy(char*, char*, int);
bool  Xishex(char);
int   Xhex2num(char);

#endif