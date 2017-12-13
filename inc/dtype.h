/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_DTYPE_H
#define _ToHack_CL_DTYPE_H

#define MAX_ARRAY_DIM   6	// 最大支持6维数组

typedef struct _dtype Dtype;
struct _dtype{
	uint             dtType;
	uint             dtBytes;
	Dtype*           dtBtype;
	union{
	    uint         btypeId;	// BasicType
	    struct{			// PointerType/ArrayType/PointerArrayType
	        int      pointLevel;
	        int      arrayDimCnt;
	        int      arrayDimItem[MAX_ARRAY_DIM];
	    };
	    struct{			// FunctionType
	        Dtype*   funcRetType;
	        int      funcParamCnt;
	        Vector   funcParamType;
	    };
	    Vector       field;		// UserCompoundType
	};
};

/* values of dtType */
enum {
	DTT_Basic,
	DTT_Array,
	DTT_Pointer,
	DTT_PointerArray,
	DTT_Function,
	DTT_UserBasicType,
	DTT_UserCompoundType,
};

/* values of btypeId */
enum {
	BTypeId_int,
	BTypeId_int8,
	BTypeId_int16,
	BTypeId_int32,
	BTypeId_int64,
	BTypeId_uint,
	BTypeId_uint8,
	BTypeId_uint16,
	BTypeId_uint32,
	BTypeId_uint64,
	BTypeId_float,
	BTypeId_float32,
	BTypeId_float64,
	BTypeId_bool,
	BTypeId_char,
	BTypeId_void,
};

Dtype* ParseDtype(ParseState*);

#endif