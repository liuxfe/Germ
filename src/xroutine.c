/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

FILE* xfopen(char* filename, char* op){
	FILE* ret = fopen(filename, op);
	if( !ret ){
		fprintf(stderr, "Fatal: can't find or open %s\n", filename);
		exit(-1);
	}
	return ret;
}

void  xfclose(FILE* fp){
	if( !fp ){
		fprintf(stderr, "Warn: fclose null file\n");
		return;
	}
	fclose(fp);
}

void* xmalloc(uint bytes){
	void* ret = malloc(bytes);
	char* p = ret;

	if( !ret ){
		fprintf(stderr, "Fatal: out of memory\n");
		exit(-1);
	}
	while(bytes--){
		*p++ = 0;
	}
	return ret;
}

void  xfree(void* p){
	if(!p){
		fprintf(stderr, "Warn: free empty memory\n");
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