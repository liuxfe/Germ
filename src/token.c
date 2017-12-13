/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Token* TokenAlloc(int code){
	Token* ret;

	ret = Xmalloc(sizeof(Token), __FILE__, __LINE__);
	ret->tCode = code;
	
	return ret;
}

void TokenFree(Token* token){
	Xfree(token, __FILE__, __LINE__);
}

void TokenDump(Token* token){
	printf("(Line:%d)\t", token->tLine);
	if(token->tCode >= TKw_package && token->tCode <= TKw_const){
		printf("KeyWord:%d\n", token->tCode);
		return;
	}
	if(token->tCode == TokenID){
		printf("Id:%s\n", token->sValue->data);
		return;
	}
	if(token->tCode == TokenChar){
		printf("Char:%d(%c)\n", token->iValue,token->iValue);
		return;
	}
	if(token->tCode == TokenString){
		printf("String:%s\n", token->sValue->data);
		return;
	}
	if(token->tCode == TokenInteger){
		printf("Number:%d\n", token->iValue);
		return;
	}
	printf("TCode:%d\n", token->tCode);
}