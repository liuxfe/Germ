/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Dtype* DtypeAlloc(int type, int bytes){
	Dtype* ret;

	ret = Xmalloc(sizeof(Dtype), __FILE__, __LINE__);
	ret->dtType = type;
	ret->dtBytes = bytes;

	return ret;
}