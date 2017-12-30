/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

/* ELF_hash */
uint _stringHash(char* start, int len){
	uint h = 0;
	uint x = 0;

	while(len--){
		h = *start + (h << 4);
		if( h & 0xF0000000){
			x = h >> 24;
			h ^= x;
			h &= ~x;
		}
		start++;
	}
	return h;
}

#define HASHITEM  499
String* _StringBucket[HASHITEM];

String* StoreString(char* s, int len){
	uint hash = _stringHash(s, len);

	String* str = _StringBucket[hash % HASHITEM];

	for(;str; str= str->next){
		if(str->hash != hash){
			continue;
		}
		if(str->len != len){
			continue;
		}
		if(Xstrncmp(str->data, s, len)){
			OIncRef(str);
			return str;
		}
	}

	str = Omalloc(sizeof(String) + len + 1, __FILE__, __LINE__);
	Xstrncpy(str->data, s, len);
	str->len = len;
	str->hash= hash;
	str->next= _StringBucket[hash % HASHITEM];
	_StringBucket[hash % HASHITEM] = str;
	return str;
}

String* GetModuleName(char* fullname){
	char* end;
	char* start;
	char* tmp = fullname;

	while(*tmp){
		if(*tmp == '/'){
			start = tmp + 1;
		}
		if(*tmp =='.'){
			end = tmp;
		}
		tmp++;
	}
	if( start >= end){
		Error(__FILE__,__LINE__,"GetModuleName: (%s) cannt get module name", fullname);
	}
	return StoreString(start, end - start);
}