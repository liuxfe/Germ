/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

#define HASH_MAX 17
symStr* hashTable[HASH_MAX];

/* ELF_hash */
uint hashValue(char* start, char* end){
	uint h = 0;
	uint x = 0;

	while(start < end){
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

symStr* newSymStr(char* start, char* end, uint hash){
	symStr* ret = malloc(sizeof(symStr) + (int)(end - start + 1));
	char* p = ret->data;
	
	while( start < end ){
		*p++ = *start++;
	}
	*p = '\0';

	ret->hashKey = hash;
	ret->symList = null;

	return ret;
}

symStr* lookUpSymStr(char* start, char* end, uint hash){
	symStr* find;

	for(find = hashTable[hash%HASH_MAX]; find; find = find->hashNext){
		if(find->hashKey != hash){
			continue;
		}
		if(xstrcmp(find->data, start, end)){
			break;
		}
	}
	return find;
}

/* 如果字符串已经在散列表中，则直接返回
   如果不在散列表中，新建一个字符串，插入到符号表中 */
symStr* insertSymStr(char* start, char* end){
	uint hash=hashValue(start, end);
	symStr* ret;

	ret = lookUpSymStr(start, end, hash);
	if( ret ){
		return ret;
	}

	ret = newSymStr(start, end, hash);
	ret->hashNext= hashTable[hash%HASH_MAX];
	hashTable[hash%HASH_MAX] = ret;
	return ret;
}

void printHashTable(){
	int i;
	symStr* tmp;

	printf("--------------Dump String HashTable -------------------\n");
	for(i=0; i<HASH_MAX;i++){
		printf("---hash:%d---\n",i);
		tmp = hashTable[i];
		while(tmp){
			printf("%s\n", tmp->data);
			tmp = tmp->hashNext;
		}
	}
	printf("---------------------------------------------------------\n");
}