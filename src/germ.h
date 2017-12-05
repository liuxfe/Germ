/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _GERM_H
#define _GERM_H

#include <stdio.h>
#include <stdlib.h>

// some basic types in germ.
typedef   signed char   int8;
typedef unsigned char  uint8;
typedef   signed short  int16;
typedef unsigned short uint16;
typedef   signed int    int32;
typedef unsigned int   uint32;
typedef   signed long   int64;
typedef unsigned long  uint64;
typedef unsigned int   uint;

typedef char bool;

#define true  1
#define false 0

// error.c
extern int NoticeCnt;
extern int WarningCnt;
extern int ErrorCnt;
void Notice(char*, int, char*, ...);
void Warning(char*, int, char*, ...);
void Error(char*, int, char*, ...);
void Debug(char*, int, char*, ...);
void Fatal(char*, int, char*, ...);

// xrourine.c
FILE* xfopen(char*, char*, char*, int);
void  xfclose(FILE*, char*, int);
void* xmalloc(uint, char*, int);
void  xfree(void*, char*, int);
void  xmemcpy(void*, void*, int);
int   xstrlen(char*);
int   xstrcmp(char*, char*);
bool  xstrncmp(char*, char*, int);
void  xstrncpy(char*, char*, int);
int   xhex2num(char);

// vector.c
typedef struct _vector{
	int    solt;
	int    item;
	void** data;
} Vector;

void pushToVector(Vector*, void*);
void* lastItemOfVector(Vector*);
void deleteVector(Vector*);

// string.c
typedef struct _string String;
struct _string{
	String* next;
	uint	hash;
	uint	ref;
	uint	len;
	char	data[0];
};

String* StoreString(char*, int);

// input.c
char* LoadFile(char*);

// scanner.c
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
	TokenID,		// 标识符
	TokenNULL,		// NULL常量
	TokenInteger,		// 整数常量
	TokenChar,		// 字符常量
	TokenBool,		// 布尔常量
	TokenFloat,		// 浮点常量
	TokenString,		// 字符串常量
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
	TOp_star,		// *
	TOp_dot,		// .
	TOp_2dot,		// ..
	TOp_3dot,		// ...
};

Token* ScanFile(char*);

#define MAX_ARRAY_DIM   6	// 最大支持6维数组

typedef struct _dataType DataType;
struct _dataType{
	uint              dtType;
	uint              dtBytes;
	DataType*         dtBtype;
	union{
	    uint          btypeId;	// BasicType
	    struct{			// PointerType/ArrayType/PointerArrayType
	        int       pointLevel;
	        int       arrayDimCnt;
	        int       arrayDimItem[MAX_ARRAY_DIM];
	    };
	    struct{			// FunctionType
	        DataType* funcRetType;
	        int       funcParamCnt;
	        Vector    funcParamType;
	    };
	    Vector        field;	// UserCompoundType
	};
};

/* values of dataTypeType */
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

typedef struct _symbol Symbol;
struct _symbol{
	uint             sType;
	String*          sName;
	Symbol*          sScope;
	union{
	   struct{			// 模块
	       Vector    modSymbol;
	   };
	   struct{
	       DataType* varDataType;
	   };
	};
};

/* values of sType*/
enum {
	ST_Module,
	ST_Variable,
};

Symbol* newSymbol(uint);

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

typedef struct _statement Statement;
struct _statement{
	uint                stmtType;
	Statement*          stmtNext;
	union{
	    Vector          pkgVector;	// PackageStmt
	    struct{			// ImportStmt
	        Vector      impVector;
	        String*     impAlias;
	        Symbol*     impSymbol;
	    };
	    Symbol*         declSymbol;	// DeclStmt
	    String*         labelString;// LabelStmt/GotoStmt
	    Expression*     expression;	// ExprsssionStmt/ReturnStmt/ThrowStmt
	    struct{			// ifStmt
	        Statement*  elseStmt;
	        Vector      ifCondElements;
	    };
	    struct{			// switchStmt
	        Expression* switchExpr;
	        Statement*  defaultStmt;
	        Vector      switchCondElement;
	    };
	    struct{			// forStmt
	        Expression* forExpr1;
	        Expression* forExpr2;
	        Expression* forExpr3;
	        Statement*  forStmt;
	    };
	    struct{			// whileStmt
	        Expression* whileExpr;
	        Statement*  whileStmt;
	    };
	};
};

// Child Element of ifStmt and switchStmt.
typedef struct _condElement{
	Expression* expression;
	Statement*  statement;
} CondElement;

/* values of stmtType */
enum{
	Stmt_package,
	Stmt_import,
	Stmt_declare,
	Stmt_lable,
	Stmt_expression,
	Stmt_if,
	Stmt_switch,
	Stmt_for,
	Stmt_while,
	Stmt_break,
	Stmt_continue,
	Stmt_goto,
	Stmt_return,
	Stmt_throw
};

void ParseFile(char* filename);

extern int wantDumpTokenVector;

#endif