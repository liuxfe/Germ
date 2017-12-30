/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

FILE* Xfopen(char* filename, char* op, char* __file, int __line){
	FILE* ret = fopen(filename, op);
	if( !ret ){
		Fatal(__file, __line, "Cannot open \"%s\"\n", filename);
	}
	return ret;
}

void  Xfclose(FILE* fp, char* __file, int __line){
	if( !fp ){
		Debug(__file, __line, "xfclose: fclose NULL file\n");
		return;
	}
	fclose(fp);
}

void  Xmemcpy(void* s1, void* s2, int len){
	char* p1 = s1;
	char* p2 = s2;
	while(len--){
		*p1++ = *p2++;
	}
}

int   Xstrlen(char* s){
	int i = 0;
	while(*s++){
		i++;
	}
	return i;
}

bool  Xstrncmp(char* s1, char* s2, int len){
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

void  Xstrncpy(char* dst, char* src, int len){
	while(len--){
		*dst++ = *src++;
	}
	*dst='\0';
}

bool  Xishex(char ch){
	if(ch >= '0' && ch <='9'){
		return true;
	}
	if(ch >= 'A' && ch <='F'){
		return true;
	}
	if(ch >= 'a' && ch <='f'){
		return true;
	}
	return false;
}

int   Xhex2num(char ch){
	if(ch >= '0' && ch <='9'){
		return ch - '0';
	}
	if(ch >= 'A' && ch <='F'){
		return ch - 'A' + 10;
	}
	if(ch >= 'a' && ch <='f'){
		return ch - 'a' + 10;
	}
	return 0; // [-Wreturn-type]
}