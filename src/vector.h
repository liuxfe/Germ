/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _VECTOR_H
#define _VECTOR_H

typedef struct _vector Vector;
struct _vector{
	int    solt;
	int    item;
	void** data;
};

void pushToVector(Vector*, void*);
void deleteVector(Vector*);

#endif