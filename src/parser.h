/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _PARSER_H
#define _PARSER_H

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

/* values of basicType->typeid */
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

#endif