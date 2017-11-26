/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

BasicType IntType     = {BTypeId_int,    8};
BasicType Int8Type    = {BTypeId_int8,   1};
BasicType Int16Type   = {BTypeId_int16,  2};
BasicType Int32Type   = {BTypeId_int32,  4};
BasicType Int64Type   = {BTypeId_int64,  8};
BasicType UintType    = {BTypeId_uint,   8};
BasicType Uint8Type   = {BTypeId_uint8,  1};
BasicType Uint16Type  = {BTypeId_uint16, 2};
BasicType Uint32Type  = {BTypeId_uint32, 4};
BasicType Uint64Type  = {BTypeId_uint64, 8};
BasicType FloatType   = {BTypeId_float,  8};
BasicType Float32Type = {BTypeId_float32,4};
BasicType Float64Type = {BTypeId_float64,8};
BasicType BoolType    = {BTypeId_bool,   1};
BasicType CharType    = {BTypeId_char,   4};

BasicType* matchType(Token* t){
	switch(t->tCode){
	    case TKw_int :
		return &IntType;
	    case TKw_int8 :
		return &Int8Type;
	    case TKw_int16 :
		return &Int16Type;
	    case TKw_int32 :
		return &Int32Type;
	    case TKw_int64 :
		return &Int64Type;
	    case TKw_uint :
		return &UintType;
	    case TKw_uint16 :
		return &Uint16Type;
	    case TKw_uint32 :
		return &Uint32Type;
	    case TKw_uint64 :
		return &Uint64Type;
	    case TKw_float :
		return &FloatType;
	    case TKw_float32 :
		return &Float32Type;
	    case TKw_float64 :
		return &Float64Type;
	    case TKw_float64 :
		return &Float64Type;
	    case TKw_float64 :
		return &Float64Type;
	    case TKw_bool :
		return &BoolType;
	    case TKw_char :
		return &CharType;
	    default :
		return null;
	}
}