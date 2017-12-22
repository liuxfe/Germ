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
	if(token->tCode >= Token_package && token->tCode <= Token_const){
		printf("KeyWord:%d\n", token->tCode);
		return;
	}
	if(token->tCode == Token_ID){
		printf("Id:%s\n", token->sValue->data);
		return;
	}
	if(token->tCode == Token_Char){
		printf("Char:%d(%c)\n", token->iValue,token->iValue);
		return;
	}
	if(token->tCode == Token_String){
		printf("String:%s\n", token->sValue->data);
		return;
	}
	if(token->tCode == Token_Integer){
		printf("Number:%d\n", token->iValue);
		return;
	}
	printf("TCode:%d\n", token->tCode);
}