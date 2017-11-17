/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _SCANNER_H
#define _SCANNER_H

struct _tokenStr{
	char* start;
	int   len;
};
typedef struct _tokenStr tokenStr;

union _tokenValue{
	int      i;
	uint     u;
	float    f;
	double   d;
	tokenStr s;
};
typedef union _tokenValue tokenValue;

struct _token{
	struct _token* tNext;
	int            tCode;
	tokenValue     tValue;
	int            tPosLine;
	int            tPosColumn;
};
typedef struct _token token;

/*
 * const values of token code.
 * TKw_ for KeyWord.
 * TOp_ for Operate.
 */
enum {
	TKw_package = 257,
	TKw_import,
	TKw_as,
	TKw_bool,
	TKw_int,
	TKw_uint,
	TKw_int8,
	TKw_uint8,
	TKw_int16,
	TKw_uint16,
	TKw_int32,
	TKw_uint32,
	TKw_int64,
	TKw_uint64,
	TKw_float,
	TKw_float32,
	TKw_float64,
	TKw_double,
	TKw_char,
	TKw_void,
	TKw_func,
	TKw_typedef,
	TKw_struct,
	TKw_union,
	Tkw_true,
	TKw_false,
	TKw_null,
	TKw_if,
	IKw_else,
	TKw_switch,
	TKw_case,
	TKw_default,
	TKw_for,
	TKw_while,
	TKw_do,
	TKw_continue,
	TKw_break,
	TKw_throw,
	TKw_return,
	TKw_goto,
	TOp_add,
	TOp_sub,
	TOp_mul,
	TOp_div,
	TOp_assign,
	TOp_addAssign,
	TOp_sub,
	TokenId,
	TokenNumber,
	TokenInteger,
	TokenStart,
	TokenEnd
};

token* doScan(Buffer*);
void printTokenList(token*);

#endif