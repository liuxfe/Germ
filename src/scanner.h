/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _SCANNER_H
#define _SCANNER_H

typedef union _tokenValue tokenValue;
union _tokenValue{
	uint     i;
	double   f;
	String*  s;
};

typedef struct _token Token;
struct _token{
	Token*         tNext;
	int            tCode;
	tokenValue     tValue;
	char*          tPosFile;
	int            tPosLine;
};

/*
 * const values of token code.
 * TKw_ for KeyWord.
 * TOp_ for Operate.
 */
enum {
	TokenStart =257,
	TKw_package,
	TKw_import,
	TKw_as,
	TKw_int,
	TKw_int8,
	TKw_int16,
	TKw_int32,
	TKw_int64,
	TKw_uint,
	TKw_uint8,
	TKw_uint16,
	TKw_uint32,
	TKw_uint64,
	TKw_float,
	TKw_float32,
	TKw_float64,
	TKw_bool,
	TKw_char,
	TKw_void,
	TKw_func,
	TKw_typedef,
	TKw_struct,
	TKw_union,
	TKw_if,
	TKw_elif,
	TKw_else,
	TKw_switch,
	TKw_case,
	TKw_default,
	TKw_for,
	TKw_while,
	TKw_continue,
	TKw_break,
	TKw_throw,
	TKw_return,
	TKw_goto,
	TKw_const,
	TRw_true,		// bool常量
	TRw_false,		// bool常量
	TRw_NULL,		// NULL常量
	TRw___FILE__,		// __FILE__ 字符串常量
	TRw___LINE__,		// __LINE__ 整数常量
	TRw___DATA__,		// __DATE__ 字符串常量
	TRw___TIME__,		// __TIME__ 整数常量
	TOp_add,		// +
	TOp_sub,		// -
	TOp_div,		// /
	TOp_inc,		// ++
	TOp_dec,		// -
	TOp_rem,		// %
	TOp_assign,		// =
	TOp_addAssign,		// +=
	TOp_subAssign,		// -=
	TOp_mulAssign,		// *=
	TOp_divAssign,		// /=
	TOp_remAssign,		// %=
	TOp_andAssign,		// &=
	TOp_and,		// &
	TOp_not,		// !
	TOp_notEq,		// !=
	TOp_eq,			// ==
	TOp_andAnd,		// &&
	TOp_or,			// |
	TOp_orOr,		// ||
	TOp_orAssign,		// |=
	TOp_neg,		// ~
	TOp_negAssign,		// ~=
	TOp_gt,			// >
	TOp_gtEq,		// >=
	TOp_shr,		// >>
	TOp_shrAssign,		// >>=
	TOp_ra,			// ->
	TOp_lt,			// <
	TOp_ltEq,		// <=
	TOp_shl,		// <<
	TOp_shlAssign,		// <<=
	TOp_threeDot,		// ...
	TOp_star,		// *
	TOp_dot,		// .
	TokenInteger,		// 整数常量
	TokenChar,		// 字符常量
	TokenBool,		// 布尔常量
	TokenFloat,		// 浮点常量
	TokenString,		// 字符串常量
	TokenNULL,		// NULL常量
	TokenID,		// 标识符
	TokenEnd
};

Token* scanFile(char*);
void printTokenList(Token*);

#endif