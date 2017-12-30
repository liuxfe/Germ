/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_ALLOC_H
#define _ToHack_CL_ALLOC_H

void* Xmalloc(int, char*, int);
void  Xfree(void*, char*, int);
void* Omalloc(int);
void  OIncRef(void*);
void  ODecRef(void*);

#endif