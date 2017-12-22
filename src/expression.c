/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Expression* ExpressionAlloc(int type){
	Expression* ret;

	ret = Xmalloc(sizeof(Statement), __FILE__, __LINE__);
	ret->exprType = type;

	return ret;
}

Expression* parseExprLeafNode(ParseState* ps){
	Expression* ret = NULL;
	Token* t = ps->tokenList;

	switch(t->tCode){
	    case Token_NULL:
	    	ret = ExpressionAlloc(Expr_Null);
	    	break;
	    case Token_Integer:
	        ret = ExpressionAlloc(Expr_Integer);
	        ret->iValue = t->iValue;
	        break;
	    case Token_Char:
	        ret = ExpressionAlloc(Expr_Char);
	        ret->iValue = t->iValue;
	        break;
	    case Token_Bool:
	        ret = ExpressionAlloc(Expr_Bool);
	        ret->iValue = t->iValue;
	        break;
	    case Token_Float:
	        ret = ExpressionAlloc(Expr_Float);
	        ret->iValue = t->fValue;
	        break;
	    case Token_String:
	        ret = ExpressionAlloc(Expr_String);
	        ret->sValue = t->sValue;
	        break;
	    case Token_ID:
	    	ret = ExpressionAlloc(Expr_String);
	        ret->sValue = t->sValue;
	        break;
	}
	if( ret != NULL ){
		eatToken(ps);
	}
	return ret;
}

Expression* ParseExpression(ParseState* ps){
	return parseExprLeafNode(ps);
}