/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

const int ALLOC_SIZE = 16;

dynstr* newDynstr(){
	dynstr* ret = xmalloc(sizeof(dynstr) + ALLOC_SIZE * sizeof(char));
	ret->nalloc = ALLOC_SIZE;
	ret->nchars = 0;
	return ret;
}

dynstr* growDynstr(dynstr* ds){
	dynstr* ret = xmalloc(sizeof(dynstr) + ALLOC_SIZE * sizeof(char) + ds->nalloc);
	ret->nalloc = ALLOC_SIZE + ds->nalloc;
	ret->nchars = ds->nchars;
	memcpy(ret->data, ds->data, ds->nchars*sizeof(char));
	xfree(ds);
	return ret;
}

dynstr* appendChar(dynstr* ds, char ch){
	if(ds->nchars+1 >= ds->nalloc){
		ds = growDynstr(ds);
	}
	ds->data[ds->nchars++] = ch;
	return ds;
}

dynstr* scanStrLiteral(char** str){
	dynstr* ds = newDynstr();
	char* p = *str;
	
	++p;
	while(*p && (*p !='"')){
		if(*p == '\\'){
			++p;
			ds = appendChar(ds, (char)escapeChar(&p));
		} else{
			ds = appendChar(ds, *p);
			++p;
		}
	}
	ds = appendChar(ds, '\0');

	if( *p =='"'){
		*str = ++p; // skip the close ".
	} else{
		printf("Error: lexical sting not close");
		*str = p; // skip the close ".
	}
	return ds;
}

void deleteDynstr(dynstr* ds){
	xfree(ds);
}

void printDynstr(dynstr* ds){
	printf("----------Debug Dynstr:%x -----------\n", (int)ds);
	printf("nalloc: %d\n", ds->nalloc);
	printf("nchars: %d\n", ds->nchars);
	printf("data:\n%s\n",ds->data);
	printf("----------------------------------------\n");
}