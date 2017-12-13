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
