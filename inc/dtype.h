/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_DTYPE_H
#define _ToHack_CL_DTYPE_H

#define MAX_ARRAY_DIM   6	// 最大支持6维数组

typedef struct _dtype Dtype;
struct _dtype{
	int             dtType;
	int             dtBytes;
	Dtype*           dtBtype;
	union{
	    int         btypeId;	// BasicType
	    struct{			// PointerType/ArrayType/PointerArrayType
	        int      pointLevel;
	        int      arrayDimCnt;
	        int      arrayDimItem[MAX_ARRAY_DIM];
	    };
	    struct{			// FunctionType
	        Dtype*   funcReturn;
	        Vector   funcParam;
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
	BTypeId_int8,
	BTypeId_int16,
	BTypeId_int32,
	BTypeId_int64,
	BTypeId_int,
	BTypeId_uint8,
	BTypeId_uint16,
	BTypeId_uint32,
	BTypeId_uint64,
	BTypeId_uint,
	BTypeId_uptr,
	BTypeId_float32,
	BTypeId_float64,
	BTypeId_float,
	BTypeId_bool,
	BTypeId_char,
};

Dtype* ParseDtype(ParseState*);

#endif