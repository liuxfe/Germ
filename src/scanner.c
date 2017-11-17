/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

static token* newToken(int tokencode){
	token* ret;

	ret = malloc(sizeof(token));
	if ( !ret ){
		printf("Error: alloc token return null");
		exit(-1);
	}
	ret->tCode = tokencode;
	ret->tNext = null;
	return ret;
}

static bool isId(char ch){
	return (ch =='_' || (ch >= 'a' && ch <= 'z') 
			 || (ch >= 'A' && ch <= 'Z'));
}

static bool isId2(char ch){
	return (ch =='_' || (ch >= 'a' && ch <= 'z') 
			 || (ch >= 'A' && ch <= 'Z')
			 || (ch >= '0' && ch <= '9'));
}

static bool isNumber(char ch){
	return (ch >='1' && ch <= '9');
}

static bool isNumber2(char ch){
	return (ch >='1' && ch <= '9');
}

token* lexical(Buffer* buf, char** cur){
	token* ret;
	char *p = *cur;

    repeat:
	// skip white chars first.
	while( *p == ' ' || *p== '\t' || *p== '\n'){
		p++;
	}

	// deal with id and keywords.
	if(isId(*p)){
		p++;
		ret = newToken(TokenId);
		while(isId2(*p)){
			p++;
		}
		ret->tValue.s.start = *cur;
		ret->tValue.s.len = p - *cur;
		*cur = p;
		printf("TokenId\t");
		return ret;
	}

	// deal with number.
	if(isNumber(*p)){
		ret = newToken(TokenInteger);
		ret->tValue.u= *p - '0';
		p++;
		while(isNumber2(*p)){
			ret->tValue.u = ret->tValue.u * 10 + *p - '0';
			p++;
		}
		*cur = p;
		printf("TokenNumber\t");
		return ret;
	}

	// deal with other chars.
	switch(*p){
	    case '\0':
		*cur = ++p; 
		return newToken(TokenEnd);
	    default:
		printf("Error: lexical can't recognize char '%c'\n", *p);
		++p;
		goto repeat;
	}
}

// scan the buffer, return the token list.
token* doScan(Buffer* buf){
	token* head = newToken(TokenStart);
	token* tail = head;
	char* p = buf->data;

	do{
		tail->tNext = lexical(buf, &p);
		tail = tail->tNext;
	}while(tail->tCode != TokenEnd);

	return head;
}

static void printToken(token* t){
	printf("--debug-- token code:%d\n", t->tCode);
}

void printTokenList(token* t){
	token* tmp=t;
	while(tmp->tCode != TokenEnd){
		printToken(tmp);
		tmp = tmp->tNext;
	}
}