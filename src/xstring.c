/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"
#define D_SIZE 8

String* _newDynString(){
	String* ret = xmalloc(sizeof(String) + D_SIZE);
	ret->nalloc = D_SIZE;
	return ret;
}

String* _growDynString(String* str){
	String* ret = xmalloc(sizeof(String) + D_SIZE + str->nalloc);
	ret->nalloc = str->nalloc + D_SIZE;
	ret->nchars = str->nchars;
	memcpy(ret->data, str->data, str->nchars);
	xfree(str);
	return ret;
}

String* _appendCharToDynString(String* str, char ch){
	if( str->nchars + 1  >= str->nalloc ){
		str = _growDynString(str);
	}
	str->data[str->nchars++] = ch;
	return str;
}

String* scanStringLiteral(char** str){
	String* ret = _newDynString();
	char* p = *str;

	++p;
	while(*p && (*p !='"')){
		if(*p == '\\'){
			++p;
			ret = _appendCharToDynString(ret, (char)escapeChar(&p));
		} else{
			ret = _appendCharToDynString(ret, *p);
			++p;
		}
	}
	ret = _appendCharToDynString(ret, '\0');

	if( *p =='"'){
		*str = ++p; // skip the close ".
	} else{
		printf("Error: lexical sting not close");
		*str = p;
	}
	return ret;
}