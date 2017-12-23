/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

void eatToken(ParseState* ps){
	Token* t = ps->tokenList;
	ps->tokenList = ps->tokenList->tNext;
	if(0){
		if(t->tCode == Token_ID){
			printf("eat:%s\n",t->sValue->data);
		}else{
			printf("eat:%d\n",t->tCode);
		}
	}
	TokenFree(t);
}

void ParseMatchToken(ParseState* ps, int tcode){
	if(ps->tokenList && ps->tokenList->tCode == tcode){
		eatToken(ps);
		return ;
	}
	Fatal(ps->filename, ps->tokenList->tLine, 
		"ParseMatch Except %s got(%s)\n", 
		TokentoString(tcode), 
		TokentoString(ps->tokenList->tCode));
}

String* ParseExceptTokenTD(ParseState* ps){
	String* ret;

	if(ps->tokenList && ps->tokenList->tCode != Token_ID){
		Fatal(ps->filename, ps->tokenList->tLine, 
			"Parse Except TokenID\n");
	}
	ret = ps->tokenList->sValue;
	eatToken(ps);
	return ret;
}

bool exceptToken(ParseState* ps, int tcode){
	if(ps->tokenList && ps->tokenList->tCode == tcode){
		eatToken(ps);
		return true;
	}
	return false;
}

void ParseFatal(ParseState* ps, char* s){
	Fatal(ps->filename, ps->tokenList->tLine, 
		"Parse Except %s got(%d)\n", s, ps->tokenList->tCode);
}