/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Statement* _newStatement(int type){
	Statement* ret = Xmalloc(sizeof(Statement), __FILE__, __LINE__);
	ret->stmtType = type;
	return ret;
}

Statement* ParseImportStmt(ParseState* ps){
	Statement* ret = _newStatement(Stmt_import);

	exceptToken(ps, TKw_import);
    repeat:
	if(ps->tokenList->tCode == TokenID) {
		VectorPush(&ret->impVector, ps->tokenList->sValue);
		eatToken(ps);
		if(exceptToken(ps, TOp_dot)){
			goto repeat;
		}
		if(exceptToken(ps, TKw_as)){
			if(ps->tokenList->tCode == TokenID){
				ret->impAlias = ps->tokenList->sValue;
				eatToken(ps);
				if(exceptToken(ps, ';')){
					return ret;
				}
				ParseFatal(ps, ";");
			}
			ParseFatal(ps, "id");
		}
		if(exceptToken(ps, ';')){
			ret->impAlias = VectorLastItem(&ret->impVector);
			return ret;
		}
		ParseFatal(ps, ";");
	}
	ParseFatal(ps, "id");
}

// 所以的检查都由调用函数处理。
Statement* ParseLabelStmt(ParseState* ps, String* label){
	Statement* ret = _newStatement(Stmt_declare);
	ret->labelString = label;
	eatToken(ps);
	return ret;
}

Statement* ParseExpressionStmt(ParseState* ps){
	Statement* ret = _newStatement(Stmt_expression);
	ret->expression = ParseExpression(ps);
	if(exceptToken(ps, ';')){
		return ret;
	}
	ParseFatal(ps, ";");
}

Statement* ParseInternalStmt(ParseState* ps){
	return NULL;
}

Statement* ParseIfStmt(ParseState* ps){
	CondElement* ce;
	Statement* ret = _newStatement(Stmt_if);

	if(!exceptToken(ps, TKw_if)){
		Debug(__FILE__, __LINE__, "not have if");
		exit(-1);
	}

    repeat:
	ce = Xmalloc(sizeof(CondElement), __FILE__, __LINE__);
	exceptTokenDealError(ps, '(', "(");
	ce->expression = ParseExpression(ps);
	exceptTokenDealError(ps, ')', ")");
	exceptTokenDealError(ps, '{', "{");
	while(!exceptToken(ps,'}')){
		VectorPush(&ce->statement, ParseInternalStmt(ps));
	}
	VectorPush(&ret->ifCondElements, ce);

	if(exceptToken(ps, TKw_elif)){
		goto repeat;
	}

	if(!exceptToken(ps, TKw_else)){
		return ret;
	}
	exceptTokenDealError(ps, '{', "{");
	while(!exceptToken(ps, '}')){
		VectorPush(&ret->elseStmt, ParseInternalStmt(ps));
	}
	return ret;
}

// 未完全实现
Statement* ParseSwitchStmt(ParseState* ps){
	CondElement* ce;
	Statement* ret = _newStatement(Stmt_switch);

	if(!exceptToken(ps, TKw_if)){
		Debug(__FILE__, __LINE__, "not have if");
		exit(-1);
	}

	exceptTokenDealError(ps, '(', "(");
	ret->switchExpr = ParseExpression(ps);
	exceptTokenDealError(ps, ')', ")");
	exceptTokenDealError(ps, '{', "{");
	while(!exceptToken(ps,'}')){
		ce = Xmalloc(sizeof(CondElement), __FILE__, __LINE__);
		exceptTokenDealError(ps, TKw_case, "case");
		ce->expression = ParseExpression(ps);
		exceptTokenDealError(ps, ':', ":");
	}
}

Statement* ParseForStmt(ParseState* ps){
	Statement* ret = _newStatement(Stmt_for);

	if(!exceptToken(ps, TKw_if)){
		Debug(__FILE__, __LINE__, "not have if");
		exit(-1);
	}
	exceptTokenDealError(ps, '(', "(");
	if(!exceptToken(ps, ';')){
		ret->forExpr1 = ParseExpression(ps);
		exceptTokenDealError(ps, ';', ";");
	}
	if(!exceptToken(ps, ';')){
		ret->forExpr2 = ParseExpression(ps);
		exceptTokenDealError(ps, ';', ";");
	}
	if(!exceptToken(ps, ';')){
		ret->forExpr3 = ParseExpression(ps);
		exceptTokenDealError(ps, ';', ";");
	}
	exceptTokenDealError(ps, ')', ")");
	exceptTokenDealError(ps, '{', "{");
	while(!exceptToken(ps, '}')){
		VectorPush(&ret->forStmt, ParseInternalStmt(ps));
	}
	return ret;
}