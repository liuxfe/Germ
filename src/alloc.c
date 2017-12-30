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

typedef union _OHeader{
	struct{
	    int  objRef;
	};
	double   __align;
} OHeader;

void* Omalloc(int bytes, char* __file, int __line){
	OHeader* ret = Xmalloc(bytes + sizeof(OHeader), __FILE__, __LINE__);
	ret->objRef = 1;
	return ret+1;
}

void  OIncRef(void* p){
	OHeader* o = p;

	o++;
	o->objRef++;
}

void  ODecRef(void* p){
	OHeader* o =p;
	o--;

	o->objRef--;
	if(o->objRef == 0){
		free(o);
	}
}