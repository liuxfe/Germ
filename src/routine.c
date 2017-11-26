/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

/* --------------- Memory Manage Routines ------------------*/
void* xmalloc(uint bytes){
	void* ret = malloc(bytes);
	if( !ret ){
		fprintf(stderr, "Fatal: out of memory\n");
		exit(-1);
	}
	memset(ret, 0, bytes);
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