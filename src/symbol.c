/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Symbol* _newSymbol(int type){
	Symbol* ret = xmalloc(sizeof(Symbol), __FILE__, __LINE__);
	ret->sType = type;
	return ret;
}