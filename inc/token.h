/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_TOKEN_H
#define _ToHack_CL_TOKEN_H

typedef struct _token{
	struct _token* tNext;
	int            tLine;
	int            tCode;
	union{
	    int        iValue;
	    double     fValue;
	    String*    sValue;
	};
} Token;

/* values of token tCode. */
enum {
	Token_Start,
	Token_EOF,
	Token_Integer,		// 整数常量
	Token_Float,		// 浮点常量
	Token_Bool,		// 布尔常量
	Token_Char,		// 字符常量
	Token_String,		// 字符串常量
	Token_NULL,		// NULL常量
	Token_ID,		// 标识符
	Token_package,
	Token_import,
	Token_as,
	Token_using,
	Token_int8,
	Token_int16,
	Token_int32,
	Token_int64,
	Token_uint8,
	Token_uint16,
	Token_uint32,
	Token_uint64,
	Token_int,
	Token_uint,
	Token_uptr,
	Token_float32,
	Token_float64,
	Token_float,
	Token_bool,
	Token_char,
	Token_void,
	Token_func,
	Token_typedef,
	Token_struct,
	Token_union,
	Token_if,
	Token_elif,
	Token_else,
	Token_switch,
	Token_case,
	Token_default,
	Token_for,
	Token_while,
	Token_continue,
	Token_break,
	Token_throw,
	Token_return,
	Token_goto,
	Token_const,
	Token_true,		// bool常量(true)
	Token_false,		// bool常量(false)
	Token_lbrace,		// {
	Token_rbrace,		// }
	Token_lbracket,		// [
	Token_rbracket,		// ]
	Token_lparen,		// (
	Token_rparen,		// )
	Token_semicon,		// ;
	Token_colon,		// :
	Token_comma,		// ,
	Token_dot,		// .
	Token_star,		// *
	Token_add,		// +
	Token_sub,		// -
	Token_div,		// /
	Token_rem,		// %
	Token_assign,		// =
	Token_addAssign,	// +=
	Token_subAssign,	// -=
	Token_mulAssign,	// *=
	Token_divAssign,	// /=
	Token_remAssign,	// %=
	Token_andAssign,	// &=
	Token_and,		// &
	Token_not,		// !
	Token_notEq,		// !=
	Token_eq,		// ==
	Token_andAnd,		// &&
	Token_or,		// |
	Token_orOr,		// ||
	Token_orAssign,		// |=
	Token_neg,		// ~
	Token_negAssign,	// ~=
	Token_gt,		// >
	Token_ge,		// >=
	Token_shr,		// >>
	Token_shrAssign,	// >>=
	Token_ra,		// ->
	Token_lt,		// <
	Token_le,		// <=
	Token_shl,		// <<
	Token_shlAssign,	// <<=
	Token_3dot,		// ...
};

Token* TokenAlloc(int);
void TokenFree(Token*);
void TokenDump(Token*);
char* TokentoString(int);

#endif