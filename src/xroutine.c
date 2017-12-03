/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

FILE* xfopen(char* filename, char* op, char* __file, int __line){
	FILE* ret = fopen(filename, op);
	if( !ret ){
		Fatal(__file, __line, "Cannot open \"%s\"\n", filename);
	}
	return ret;
}

void  xfclose(FILE* fp, char* __file, int __line){
	if( !fp ){
		Debug(__file, __line, "xfclose: fclose NULL file\n");
		return;
	}
	fclose(fp);
}

void* xmalloc(uint bytes, char* __file, int __line){
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

void  xfree(void* p, char* __file, int __line){
	if(!p){
		Debug(__file, __line, "xfree: free NULL pointer\n");
		return;
	}
	free(p);
}

void  xmemcpy(void* s1, void* s2, int len){
	char* p1 = s1;
	char* p2 = s2;
	while(len--){
		*p1++ = *p2++;
	}
}

int   xstrlen(char* s){
	int i = 0;
	while(*s++){
		i++;
	}
	return i;
}

int   xstrcmp(char* s1, char* s2){
	while(*s1 && *s2 && (*s1 == *s2)){
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

bool  xstrncmp(char* s1, char* s2, int len){
	while(len--){
		if(*s1 && *s2 && *s1==*s2){
			s1++;
			s2++;
			continue;
		}
		return false;
	}
	return true;
}

void  xstrncpy(char* dst, char* src, int len){
	while(len--){
		*dst++ = *src++;
	}
	*dst='\0';
}

int   xhex2num(char ch){
	if(ch >= '0' && ch <='9'){
		return ch - '0';
	}
	if(ch >= 'A' && ch <='F'){
		return ch - 'A' + 10;
	}
	if(ch >= 'a' && ch <='f'){
		return ch - 'a' + 10;
	}
	return -1;
}