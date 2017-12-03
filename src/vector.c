/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

const int V_SIZE = 4;

void _expandVector(Vector* vec){
	void** p = xmalloc((vec->solt + V_SIZE)* sizeof(void**), __FILE__, __LINE__);
	xmemcpy(p, vec->data, vec->solt * sizeof(void**));
	if(vec->data){
		xfree(vec->data, __FILE__, __LINE__);
	}
	vec->data = p;
	vec->solt += V_SIZE;
}

void pushToVector(Vector* vec, void* item){
	if(vec->item + 1 >= vec->solt){
		_expandVector(vec);
	}
	*(vec->data + vec->item) = item;
	vec->item++;
}

void deleteVector(Vector* vec){
	xfree(vec->data, __FILE__, __LINE__);
}