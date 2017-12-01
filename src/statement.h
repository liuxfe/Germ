/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _STATEMENT_H
#define _STATEMENT_H

typedef struct _statement{
	uint     stmtType;
} Statement;

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

typedef struct _packageStmt{
	uint     stmtType;
	Vector   vector;
} PackageStmt;

typedef struct _importStmt{
	uint     stmtType;
	Vector   vector;
	String*  alias;
	Symbol*  symbol;
} ImportStmt;

typedef struct _declareStmt{
	uint     stmtType;
	String*  name;
	Symbol*  symbol;
} DeclareStmt;

typedef struct _lableStmt{
	uint     stmtType;
	String*  alias;
} LableStmt;

typedef struct _expressionStmt{
	uint     stmtType;
	//Expression* expr;
} ExpressionStmt;

// Child Element of ifStmt and switchStmt.
typedef struct _condElement{
	//Expression* expr;
	Vector   stmts;
} CondElement;

typedef struct _ifStmt{
	uint     stmtType;
	Vector   elseStmts;
	Vector   ifElements;
} IfStmt;

typedef struct _switchStmt{
	uint     stmtType;
	// Expression* expr;
	Vector   defaultStmts;
	Vector   caseElemets;
} SwitchStmt;

typedef struct _forStmt{
	uint     stmtType;
	// Expression* expr1;
	// Expression* expr2;
	// Expression* expr3;
	Vector   stmts;
} ForStmt;

typedef struct _whileStmt{
	uint     stmtType;
	// Expression*
};

void except(Token**, uint);
PackageStmt* parsePackageStmt(Token**);
void printPackageStmt(PackageStmt*);

#endif