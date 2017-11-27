/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _STATEMENT_H
#define _STATEMENT_H

typedef struct _statement Statement;
struct _statement{
	uint     stmtType;
};

typedef struct _packageStmt PackageStmt;
struct _packageStmt{
	uint     stmtType;
	Vector   vector;
};

/* values of stmtType */
enum{
	StmtT_package = 100,
	StmtT_import,
	StmtT_declare,
	StmtT_expression,
	StmtT_if,
	StmtT_switch,
	StmtT_for,
	StmtT_while,
	StmtT_break,
	StmtT_continue,
	StmtT_goto,
	StmtT_throw,
	StmtT_return,
	StmtT_lable,
};

void except(Token**, uint);
PackageStmt* parsePackageStmt(Token**);
void printPackageStmt(PackageStmt*);

#endif