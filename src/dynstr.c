/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

const int ALLOC_SIZE = 16;

dynstr* newDynstr(){
	dynstr* ret;

	ret = malloc(sizeof(dynstr) + ALLOC_SIZE * sizeof(char));
	if(!ret){
		printf("Error: alloc dynstr return null");
		exit(-1);
	}
	ret->nalloc=ALLOC_SIZE;
	ret->len=0;
	return ret;
}

dynstr* growDynstr(dynstr* ds){
	dynstr* ret;

	ret = malloc(sizeof(dynstr) + ALLOC_SIZE * sizeof(char) + ds->nalloc);
	if(!ret){
		printf("Error: grow dynstr return null");
		exit(-1);
	}
	ret->nalloc = ALLOC_SIZE + ds->nalloc;
	ret->len    = ds->len;
	memcpy(ret->data, ds->data, ds->len*sizeof(char));
	free(ds);
	return ret;
}

dynstr* appendChar(dynstr* ds, char ch){
	if(ds->len+1 >= ds->nalloc){
		ds = growDynstr(ds);
	}
	ds->data[ds->len++] = ch;
	return ds;
}

// Note: *end 指向的字符不包含在字符串中.
dynstr* createDynstr(char* start, char *end){
	dynstr* ret = newDynstr();

	while( start < end ){
		ret = appendChar(ret, *start);
		start++;
	}
	ret = appendChar(ret, '\0');
	return ret;
}

void printDynstr(dynstr* ds){
	printf("----------Debug Dynstr:%x -----------\n", (int)ds);
	printf("nalloc: %d\n", ds->nalloc);
	printf("len: %d\n", ds->len);
	printf("hkey: %x\n", ds->hkey);
	printf("data:\n%s\n",ds->data);
	printf("----------------------------------------\n");
}