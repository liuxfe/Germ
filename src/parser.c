/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

void eatToken(ParseState* ps){
	Token* t = ps->tokenList;
	ps->tokenList = ps->tokenList->tNext;
	if(1){
		if(t->tCode == TokenID){
			printf("eat:%s\n",t->sValue->data);
		}else{
			printf("eat:%d\n",t->tCode);
		}
	}
	xfree(t, __FILE__, __LINE__);
}

bool exceptToken(ParseState* ps, int tcode){
	if(ps->tokenList && ps->tokenList->tCode == tcode){
		eatToken(ps);
		return true;
	}
	return false;
}

/*
 * <ParseModule>:= <PackageStmt> <ImportStmt>{0,n} <ExternalDeclareStmt>{0,n}
 */
void ParseFile(char* filename){
	ParseState ps;
	Statement* pkgstmt;
	Vector imports;
	Vector symbols;

	ps.filename = filename;
	ps.tokenList = ScanFile(filename);

	exceptToken(&ps, TokenStart);

	pkgstmt = ParsePackageStmt(&ps);

	while(exceptToken(&ps, TKw_import)){
		pushToVector(&imports, ParseImportStmt(&ps));
	}

	while(ps.tokenList){
		pushToVector(&symbols, ParseExternalDeclareStmt(&ps));
	}
}