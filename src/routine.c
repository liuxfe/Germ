/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

/* --------------- Memory Manage Routines ------------------*/
void* xmalloc(uint bytes){
	void* ret = malloc(bytes);
	if( !ret ){
		fprintf(stderr, "Fatal: out of memory\n");
		exit(-1);
	}
	return ret;
}

void xfree(void* p){
	if(!p){
		fprintf(stderr, "Warn: free empty memory\n");
		return;
	}
	free(p);
}

/* -------------- String Operate Routines ----------------*/
/* 比较字符串，相等返回true，反之返回false
   字符串1是null结尾，字符串2指定起始和结尾地址 */
bool xstrcmp(char* s1, char* start, char* end){
	while( *s1 && start < end){
		if( *s1 != *start){
			return false;
		}
		s1++;
		start++;
	}
	if( (*s1 != 0) || (start!=end) ){
		return false;
	}
	return true;
}

/* ---------------- File IO Routines ---------------------*/
FILE* xfopen(char* filename, char* op){
	FILE* ret = fopen(filename, op);
	if( !ret ){
		fprintf(stderr, "Fatal: can't find or open %s\n", filename);
		exit(-1);
	}
	return ret;
}

void xfclose(FILE* fp){
	if( !fp ){
		fprintf(stderr, "Warn: fclose null file\n");
		return;
	}
	fclose(fp);
}