/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Dtype* DtypeAlloc(int type, int bytes){
	Dtype* ret;

	ret = Xmalloc(sizeof(Dtype), __FILE__, __LINE__);
	ret->dtType = type;
	ret->dtBytes = bytes;

	return ret;
}

Dtype* ParseDtype(ParseState* ps){
	Dtype* bdt;

	switch(ps->tokenList->tCode){
	    case Token_int8 :
		bdt = DtypeAlloc(Dtype_int8, 1);
		break; 
	    case Token_int16 :
		bdt = DtypeAlloc(Dtype_int16, 2);
		break;
	    case Token_int32 :
		bdt = DtypeAlloc(Dtype_int32, 4);
		break;
	    case Token_int64 :
		bdt = DtypeAlloc(Dtype_int64, 8);
		break;
	    case Token_int :
		bdt = DtypeAlloc(Dtype_int, 8);
		break;
	    case Token_uint8 :
		bdt = DtypeAlloc(Dtype_uint8, 1);
		break;
	    case Token_uint16 :
		bdt = DtypeAlloc(Dtype_uint16, 2);
		break;
	    case Token_uint32 :
		bdt = DtypeAlloc(Dtype_uint32, 4);
		break;
	    case Token_uint64 :
		bdt = DtypeAlloc(Dtype_uint64, 8);
		break;
	    case Token_uint :
		bdt = DtypeAlloc(Dtype_uint, 8);
		break;
	    case Token_uptr :
		bdt = DtypeAlloc(Dtype_uptr, 8);
		break;
	    case Token_float32 :
		bdt = DtypeAlloc(Dtype_float32, 4);
		break;
	    case Token_float64 :
		bdt = DtypeAlloc(Dtype_float64, 8);
		break;
	    case Token_float :
		bdt = DtypeAlloc(Dtype_float, 8);
		break;
	    case Token_bool :
		bdt = DtypeAlloc(Dtype_bool, 1);
		break;
	    case Token_char :
		bdt = DtypeAlloc(Dtype_char, 4);
		break;
	    case Token_ID :
	    default:
		return bdt = NULL;
	}
	eatToken(ps);
	return bdt;
}