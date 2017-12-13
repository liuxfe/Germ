/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

void VectorPush(Vector* vec, void* item){
	const int V_SIZE = 4;
	void** p;

	if(vec->item +1 >= vec->solt){
		p = Xmalloc((vec->solt + V_SIZE)* sizeof(void**), __FILE__, __LINE__);
		Xmemcpy(p, vec->data, vec->solt * sizeof(void**));
		if(vec->data){
			Xfree(vec->data, __FILE__, __LINE__);
		}
		vec->data = p;
		vec->solt += V_SIZE;
	}

	*(vec->data + vec->item) = item;
	vec->item++;
}

void* VectorLastItem(Vector* vec){
	if(vec->item <=0){
		Debug(__FILE__,__LINE__,"Empty Vector to get last Item");
	}
	return vec->data[vec->item-1];
}

void deleteVector(Vector* vec){
	Xfree(vec->data, __FILE__, __LINE__);
}