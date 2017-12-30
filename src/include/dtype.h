/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_DTYPE_H
#define _ToHack_CL_DTYPE_H

typedef struct _dtype{
	int             dtType;
	int             dtBytes;
	struct _dtype*  dtBase;
	int             dtPointLevel;
	int             dtArrayLen;
	struct _dtype*  dtFuncReturn;
	Vector          dtFuncParam;
	Vector          dtField;
} Dtype;

/* values of dtType */
enum {
	Dtype_int8,
	Dtype_int16,
	Dtype_int32,
	Dtype_int64,
	Dtype_int,
	Dtype_uint8,
	Dtype_uint16,
	Dtype_uint32,
	Dtype_uint64,
	Dtype_uint,
	Dtype_uptr,
	Dtype_float32,
	Dtype_float64,
	Dtype_float,
	Dtype_bool,
	Dtype_char,
	Dtype_function,
	Dtype_pointer,
	Dtype_array,
	Dtype_UserBasicType,
	Dtype_UserCompoundType,
};

Dtype* DtypeAlloc(int, int);
Dtype* ParseDtype(ParseState*);

#endif