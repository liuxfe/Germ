/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ROUTINE_H
#define _ROUTINE_H

void* xmalloc(uint);
void  xfree(void*);
void  xstrncpy(char*, char*, int);
uint escapeChar(char**);
FILE* xfopen(char*, char*);
void  xfclose(FILE*);

#endif