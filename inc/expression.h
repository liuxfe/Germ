/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_EXPRESSION_H
#define _ToHack_CL_EXPRESSION_H

typedef struct _expression Expression;
struct _expression{
	int8                exprType;
	int8                isConst;
	int16               operate;
	union{
	    uint            iValue;	// 整数/字符/布尔常量
	    double          fValue;	// 浮点常量
	    Symbol*         sValue;	// 字符串常量/变量
	    Expression*     operand;	// 一元运算操作数
	    struct{			// 二元运算操作数
	        Expression* left;
	        Expression* right;
	    };
	    Vector          params;	// 函数调用参数
	};
};

/* values of exprType */
enum {
	Expr_Integer,
	Expr_Char,
	Expr_Bool,
	Expr_Float,
	Expr_String,
	Expr_ID,
	Expr_Uarry,
	Expr_Binary,
	Expr_FunCall,
};

Expression* ParseExpression(ParseState*);

#endif