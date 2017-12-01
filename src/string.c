/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

const int DYS_GROWSIZE = 8;

String* CreateDynString(){
	String* ret = xmalloc(sizeof(String) + DYS_GROWSIZE);
	ret->nalloc = DYS_GROWSIZE;
	return ret;
}

String* AppendCharToDynString(String* str, char ch){
	String* ret = str;
	if( ret->nchars + 1 >= ret->nalloc ){
		ret = xmalloc(sizeof(String) + DYS_GROWSIZE + str->nalloc);
		ret->nalloc = str->nalloc + DYS_GROWSIZE;
		ret->nchars = str->nchars;
		xmemcpy(ret->data, str->data, str->nchars);
		xfree(str);
	}
	ret->data[ret->nchars++] = ch;
	return ret;
}

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
		if(xstrcmp(find->data, s->data) == 0){
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