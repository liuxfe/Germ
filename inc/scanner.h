/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_SCANNER_H
#define _ToHack_CL_SCANNER_H

typedef struct _token{
	struct _token* tNext;
	int            tLine;
	int            tCode;
	union{
	    uint       iValue;
	    double     fValue;
	    String*    sValue;
	};
} Token;

/* values of token tCode. */
enum {
	TokenStart = 257,
	TokenEnd,
	TokenID,		// 标识符
	TokenNULL,		// NULL常量
	TokenInteger,		// 整数常量
	TokenChar,		// 字符常量
	TokenBool,		// 布尔常量
	TokenFloat,		// 浮点常量
	TokenString,		// 字符串常量
	Token3dot,		// ...
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
	//TRw___FILE__,		// __FILE__ 字符串常量
	//TRw___LINE__,		// __LINE__ 整数常量
	//TRw___DATA__,		// __DATE__ 字符串常量
	//TRw___TIME__,		// __TIME__ 整数常量
	TOp_add,		// +
	TOp_sub,		// -
	TOp_div,		// /
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
	TOp_ge,			// >=
	TOp_shr,		// >>
	TOp_shrAssign,		// >>=
	TOp_ra,			// ->
	TOp_lt,			// <
	TOp_le,			// <=
	TOp_shl,		// <<
	TOp_shlAssign,		// <<=
	TOp_star,		// *
	TOp_dot,		// .
};

Token* ScanFile(char*);

#endif