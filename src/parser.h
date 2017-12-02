/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _PARSER_H
#define _PARSER_H

typedef struct _dataType{
	int       dataTypeType;
	int       typeBytes;    // 数据类型占用的空间
}DataType;

typedef struct _basicType{
	int       dataTypeType;
	int       typeBytes;
	int       typeId;
} BasicType;

typedef struct _arrayType{
	int       dataTypeType;
	int       typeBytes;
	DataType* bType;
	int       dimCnt;      // 维数总数
	int       dimItem[0];  // 维数项
} ArrayType;

typedef struct _pointerType{
	int       dataTypeType;
	int       typeBytes;
	DataType* bType;
	int       level;
} PointerType;

typedef struct _pointerArrayType{
	int       dataTypeType;
	int       typeBytes;
	DataType* bType;
	int       level;
	int       dimCnt;      // 维数总数
	int       dimItem[0];  // 维数项
} PointerArrayType;

typedef struct _functionType{
	int       dataTypeType;
	int       typeBytes;   // 函数类型应该占用多少空间呢？
	DataType* ret;
	int       paramCnt;    // 函数参数个数
	Vector    paramType;   // 参数的数据类型
} FunctionType;

typedef struct _userBasicType{
	int       dataTypeType;
	int       typeBytes;
	DataType* bType;
} UserBasicType;

typedef struct _userCompoundType{
	int       dataTypeType;
	int       typeBytes;
	Vector    field;       // field 的类型是Symbol
} UserCompoundType;

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
	int8              exprType;
	int8              isConst;
	int16             operate;
	union{
	    uint          iValue;    // 整数/字符/布尔常量
	    double        fValue;    // 浮点常量
	    Symbol*       sValue;    // 字符串常量/变量
	    Expression*   operand;   // 一元运算操作数
	    Expression*   binary[2]; // 二元运算操作数 0:left,1:right
	    Vector        params;    // 函数调用参数
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

typedef struct _statement{
	uint        stmtType;
} Statement;

typedef struct _packageStmt{
	uint        stmtType;
	Vector      vector;
} PackageStmt;

typedef struct _importStmt{
	uint        stmtType;
	Vector      vector;
	String*     alias;
	Symbol*     symbol;
} ImportStmt;

typedef struct _declareStmt{
	uint        stmtType;
	String*     name;
	Symbol*     symbol;
} DeclareStmt;

typedef struct _lableStmt{
	uint        stmtType;
	String*     alias;
} LableStmt;

typedef struct _expressionStmt{
	uint        stmtType;
	Expression* expr;
} ExpressionStmt;

// Child Element of ifStmt and switchStmt.
typedef struct _condElement{
	Expression* expr;
	Vector      stmts;
} CondElement;

typedef struct _ifStmt{
	uint        stmtType;
	Vector      elseStmts;
	Vector      ifElements;
} IfStmt;

typedef struct _switchStmt{
	uint        stmtType;
	Expression* expr;
	Vector      defaultStmts;
	Vector      caseElemets;
} SwitchStmt;

typedef struct _forStmt{
	uint        stmtType;
	Expression* expr1;
	Expression* expr2;
	Expression* expr3;
	Vector      stmts;
} ForStmt;

typedef struct _whileStmt{
	uint        stmtType;
	Expression* expr;
	Vector      stmts;
} WhileStmt;

typedef struct _breakStmt{
	uint        stmtType;
} BreakStmt;

typedef struct _continueStmt{
	uint        stmtType;
} BreakStmt;

typedef struct _gotoStmt{
	uint        stmtType;
	String*     lable;
} GotoStmt;

typedef struct _throwStmt{
	uint        stmtType;
	Expression* expr;
} ThrowStmt;

typedef struct _returnStmt{
	uint        stmtType;
	Expression* expr;
} ReturnStmt;

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
	Stmt_throw,
	Stmt_return
};

void except(Token**, uint);
PackageStmt* parsePackageStmt(Token**);
void printPackageStmt(PackageStmt*);

#endif