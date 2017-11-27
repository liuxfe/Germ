/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _DECLARE_H
#define _DECLARE_H

struct _basictype{
	int typeId;
	int typeBytes;
};
typedef struct _basictype BasicType;

enum {
	BTypeId_int   =1,
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

extern BasicType IntType;
extern BasicType Int8Type;
extern BasicType Int16Type;
extern BasicType Int32Type;
extern BasicType Int64Type;
extern BasicType UintType;
extern BasicType Uint8Type;
extern BasicType Uint16Type;
extern BasicType Uint32Type;
extern BasicType Uint64Type;
extern BasicType FloatType;
extern BasicType Float32Type;
extern BasicType Float64Type;
extern BasicType BoolType;
extern BasicType CharType;

#endif