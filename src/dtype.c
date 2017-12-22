/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

const int POINTER_SIZE = 8;

Dtype Int8Type    = {DTT_Basic, 1, NULL, {BTypeId_int8   }};
Dtype Int16Type   = {DTT_Basic, 2, NULL, {BTypeId_int16  }};
Dtype Int32Type   = {DTT_Basic, 4, NULL, {BTypeId_int32  }};
Dtype Int64Type   = {DTT_Basic, 8, NULL, {BTypeId_int64  }};
Dtype IntType     = {DTT_Basic, 8, NULL, {BTypeId_int    }};
Dtype Uint8Type   = {DTT_Basic, 1, NULL, {BTypeId_uint8  }};
Dtype Uint16Type  = {DTT_Basic, 2, NULL, {BTypeId_uint16 }};
Dtype Uint32Type  = {DTT_Basic, 4, NULL, {BTypeId_uint32 }};
Dtype Uint64Type  = {DTT_Basic, 8, NULL, {BTypeId_uint64 }};
Dtype UintType    = {DTT_Basic, 8, NULL, {BTypeId_uint   }};
Dtype UptrType    = {DTT_Basic, 8, NULL, {BTypeId_uptr   }};
Dtype Float32Type = {DTT_Basic, 4, NULL, {BTypeId_float32}};
Dtype Float64Type = {DTT_Basic, 8, NULL, {BTypeId_float64}};
Dtype FloatType   = {DTT_Basic, 8, NULL, {BTypeId_float  }};
Dtype BoolType    = {DTT_Basic, 1, NULL, {BTypeId_bool   }};
Dtype CharType    = {DTT_Basic, 4, NULL, {BTypeId_char   }};

Dtype* ParseDtype(ParseState* ps){
//	Dtype* ret;
	Dtype* bdt;
/*
	int pointerLevel = 0;
	int arrayDimCnt = 0;
	int arrayDimEnt[MAX_ARRAY_DIM];
	int i;
	int sum;
*/
	switch(ps->tokenList->tCode){
	    case TKw_int :	bdt = &IntType; break;
	    case TKw_int8 : 	bdt = &Int8Type; break;
	    case TKw_int16 :	bdt = &Int16Type; break;
	    case TKw_int32 :	bdt = &Int32Type; break;
	    case TKw_int64 :	bdt = &Int64Type; break;
	    case TKw_uint :	bdt = &UintType; break;
	    case TKw_uint16 :	bdt = &Uint16Type; break;
	    case TKw_uint32 :	bdt = &Uint32Type; break;
	    case TKw_uint64 :	bdt = &Uint64Type; break;
	    case TKw_float :	bdt = &FloatType; break;
	    case TKw_float32 :	bdt = &Float32Type; break;
	    case TKw_float64 :	bdt = &Float64Type; break;
	    case TKw_bool :	bdt = &BoolType; break;
	    case TKw_char :	bdt = &CharType; break;
	    case TokenID :
	    default:
		return bdt = NULL;
	}
	eatToken(ps);
	return bdt;
/*
	while(exceptToken(ps,'*')){
		pointerLevel += 1;
	}
	while(true){
		if(!exceptToken(ps, '[')){
			break;
		}
		if(ps->tokenList->tCode != TokenInteger){
			ParseFatal(ps,"Integer");
		}
		arrayDimEnt[arrayDimCnt] = ps->tokenList->iValue;
		arrayDimCnt += 1;
		eatToken(ps);
		exceptTokenDealError(ps, ']',"]");
	}

	if(pointerLevel && arrayDimCnt){
		ret = _newDtype(DTT_PointerArray);
		ret->pointLevel = pointerLevel;
		ret->arrayDimCnt = arrayDimCnt;
		sum=1;
		for(i = 0; i<arrayDimCnt; i++){
			ret->arrayDimItem[i]=arrayDimEnt[i];
			sum *= arrayDimEnt[i];
		}
		ret->dtBytes = POINTER_SIZE * sum;
		ret->dtBtype = bdt;
		return ret;
	}

	if(arrayDimCnt){
		if( bdt ==&VoidType ){
			Fatal(ps->filename,ps->tokenList->tLine, "cant define array of void");
		}
		ret = _newDtype(DTT_PointerArray);
		ret->arrayDimCnt = arrayDimCnt;
		sum=1;
		for(i = 0; i<arrayDimCnt; i++){
			ret->arrayDimItem[i]=arrayDimEnt[i];
			sum *= arrayDimEnt[i];
		}
		ret->dtBytes = POINTER_SIZE * sum;
		ret->dtBtype = bdt;
		return ret;
	}

	if(pointerLevel){
		ret = _newDtype(DTT_Pointer);
		ret->pointLevel = pointerLevel;
		ret->dtBytes = POINTER_SIZE;
		ret->dtBtype = bdt;
		return ret;
	}
*/
}