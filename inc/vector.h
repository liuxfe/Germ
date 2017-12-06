/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_VECTOR_H
#define _ToHack_CL_VECTOR_H

typedef struct _vector{
	int    solt;
	int    item;
	void** data;
} Vector;

void pushToVector(Vector*, void*);
void* lastItemOfVector(Vector*);
void deleteVector(Vector*);

#endif