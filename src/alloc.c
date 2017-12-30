/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

void* Xmalloc(int bytes, char* __file, int __line){
	void* ret = malloc(bytes);
	char* p = ret;

	if( !ret ){
		Fatal(__file, __line, "xmalloc: out of memory\n");
	}
	while(bytes--){
		*p++ = 0;
	}
	return ret;
}

void  Xfree(void* p, char* __file, int __line){
	if(!p){
		Debug(__file, __line, "xfree: free NULL pointer\n");
		return;
	}
	free(p);
}
