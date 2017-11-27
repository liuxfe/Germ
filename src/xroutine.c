/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

/* --------------- Memory Manage Function ------------------*/

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


/* -------------- String Operate Function ----------------*/

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

void  xmemcpy(void* s1, void* s2, int len){
	char* p1 = s1;
	char* p2 = s2;
	while(len--){
		*p1++ = *p2++;
	}
}

void  xstrncpy(char* dst, char* src, int len){
	while(len--){
		*dst++ = *src++;
	}
	*dst='\0';
}

uint escapeChar(char** str){
	uint tmp;
	char *p =*str;
	switch(*p){
	    case 'a': *str = ++p; return '\a';
	    case 'b': *str = ++p; return '\b';
	    case 'e': *str = ++p; return '\e';
	    case 'f': *str = ++p; return '\f';
	    case 'n': *str = ++p; return '\n';
	    case 'r': *str = ++p; return '\r';
	    case 't': *str = ++p; return '\t';
	    case 'v': *str = p++; return '\v';
	    case '\\':*str = p++; return '\\';
	    case '\'':*str = p++; return '\'';
	    case '"': *str = p++; return '"';
	    case '?': *str = p++; return '\?';
	    case '0':
		if( !(*(p+1)>='1' && *(p+1)<='9') ){
			*str= p;
			return '\0';
		}
	    case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7':
		tmp = *p - '0';
		p++;
		if( *p >='0' && *p<='7'){
			tmp= tmp * 8 + *p - '0';
			p++;
		}
		if( *p >='0' && *p<='7'){
			tmp= tmp * 8 + *p - '0';
			p++;
		}
		*str = p;
		return tmp;
	    case 'x':
		p++;
		// 处理第一个字符.
		if( *p >='0' && *p <='9'){
			tmp = *p - '9';
		} else if( *p >= 'A' && *p <='F'){
			tmp = *p - 'A' +10;
		}else if( *p >= 'a' && *p <='f'){
			tmp = *p - 'a' +10;
		} else {
			*str =p;
			return 'x';
		}
		p++;
		// 处理第二个字符.
		if( *p >='0' && *p <='9'){
			tmp = tmp * 16 + *p - '9';
		} else if( *p >= 'A' && *p <='F'){
			tmp = tmp * 16 + *p - 'A' +10;
		}else if( *p >= 'a' && *p <='f'){
			tmp = tmp * 16 + *p - 'a' +10;
		} else {
			*str =++p;
			return tmp;
		}
		*str = ++p;
		return tmp;
	    default:
		*str = ++p;
		return *(p-1);
	}
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