/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_STATEMENT_H
#define _ToHack_CL_STATEMENT_H

typedef struct _statement Statement;
struct _statement{
	uint                stmtType;
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
	        Vector      defaultStmt;
	        Vector      switchCondElement;
	    };
	    struct{			// forStmt
	        Expression* forExpr1;
	        Expression* forExpr2;
	        Expression* forExpr3;
	        Vector      forStmt;
	    };
	    struct{			// whileStmt
	        Expression* whileExpr;
	        Vector      whileStmt;
	    };
	};
};

// Child Element of ifStmt and switchStmt.
typedef struct _condElement{
	Expression* expression;
	Vector      statement;
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

Statement* ParsePackageStmt(ParseState*);
Statement* ParseImportStmt(ParseState*);
Statement* ParseExternalDeclareStmt(ParseState*);
Statement* ParseLabelStmt(ParseState*, String*);
Statement* ParseExpressionStmt(ParseState*);

#endif