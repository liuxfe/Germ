/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Statement* _newStatement(int type){
	Statement* ret = xmalloc(sizeof(Statement), __FILE__, __LINE__);
	ret->stmtType = type;
	return ret;
}

Statement* ParsePackageStmt(ParseState* ps){
	Statement* ret = _newStatement(Stmt_package);

	exceptToken(ps,TKw_package);
    repeat:
	if(ps->tokenList->tCode == TokenID) {
		pushToVector(&(ret->pkgVector),ps->tokenList->sValue);
		eatToken(ps);
		if(exceptToken(ps, TOp_dot)){
			goto repeat;
		}
		if(exceptToken(ps, ';')){
			return ret;
		}
	}
	Fatal(ps->filename, ps->tokenList->tLine, "except id got(%d)",ps->tokenList->tCode);
}

Statement* ParseImportStmt(ParseState* ps){
	Statement* ret = _newStatement(Stmt_import);
    repeat:
	if(ps->tokenList->tCode == TokenID) {
		pushToVector(&ret->impVector, ps->tokenList->sValue);
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
				Fatal(ps->filename, ps->tokenList->tLine, "except ';' got(%d)",ps->tokenList->tCode);
			}
			Fatal(ps->filename, ps->tokenList->tLine, "except id got(%d)",ps->tokenList->tCode);
		}
		if(exceptToken(ps, ';')){
			ret->impAlias = lastItemOfVector(&ret->impVector);
			return ret;
		}
		Fatal(ps->filename, ps->tokenList->tLine, "except ';' got(%d)",ps->tokenList->tCode);
	}
	Fatal(ps->filename, ps->tokenList->tLine, "except id got(%d)",ps->tokenList->tCode);
}

Statement* ParseExternalDeclareStmt(ParseState* ps){
	Statement* ret = _newStatement(Stmt_declare);

	if(exceptToken(ps, TKw_typedef)){
		ret->declSymbol = ParseExternalTypeDeclare(ps);
		return ret;
	}

	ret->declSymbol = ParseExternalOtherDeclare(ps);
	return ret;
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
	Fatal(ps->filename, ps->tokenList->tLine, "except ';' got(%d)",ps->tokenList->tCode);
}
