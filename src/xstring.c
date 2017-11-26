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

/* ELF_hash */
uint _stringHash(char* start, int len){
	uint h = 0;
	uint x = 0;

	while(len--){
		h = *start + h<< 4;
		if( h & 0xF0000000){
			x = h >> 24;
			h ^= x;
			h &= ~x;
		}
		start++;
	}
	return h;
}

String* _newFixString(char* s, int len){
	String* ret = xmalloc(sizeof(String) + len + 1);
	ret->nalloc = len + 1;
	ret->nchars = len;
	ret->hash   = _stringHash(s, len);
	xstrncpy(ret->data, s, len);
	return ret;
}

void deleteString(String* s){
	xfree(s);
}

#define HASHITEM  53
String* _StringHashTable[HASHITEM];

String* lookUpString(String* s){
	String* find = _StringHashTable[s->hash % HASHITEM];

	for(;find; find= find->next){
		if(find->hash != s->hash){
			continue;
		}
		if(strcmp(find->data, s->data) == 0){
			break;
		}
	}
	return find;
}

String* storeString(char* s, int len){
	int i;
	String* ret = _newFixString(s, len);
	String* find= lookUpString(ret);

	if(find){
		deleteString(ret);
		return find;
	}

	i= ret->hash % HASHITEM;

	ret->next = _StringHashTable[i];
	_StringHashTable[i]= ret;

	return ret;
}

void printHashTable(){
	int i;
	String* s;
	printf("--------------String HashTable -------------------");
	for(i=0; i<HASHITEM;i++){
		printf("\n--------hash:%d--------\n",i);
		s = _StringHashTable[i];
		while(s){
			printf("%s\t", s->data);
			s = s->next;
		}
	}
	printf("--------------------------------------------------\n");
}