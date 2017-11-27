/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

Symbol* newSymbol(uint type){
	Symbol* ret=xmalloc(sizeof(Symbol));
	ret->sType=type;
	return ret;
}