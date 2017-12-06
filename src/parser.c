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

void ParseFatal(ParseState* ps, char* s){
	Fatal(ps->filename, ps->tokenList->tLine, 
		"Parse Except %s got(%d)\n", s, ps->tokenList->tCode);
}

void exceptTokenDealError(ParseState* ps, int tcode, char* s){
	if(exceptToken(ps, tcode)){
		return;
	}
	ParseFatal(ps, s);
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

	if(!exceptToken(&ps, TokenStart)){
		Debug(__FILE__, __LINE__, "Token list not start with TokenStart");
	}

	pkgstmt = ParsePackageStmt(&ps);

	while(ps.tokenList->tCode == TKw_import){
		pushToVector(&imports, ParseImportStmt(&ps));
	}

	while(ps.tokenList->tCode != TokenEnd){
		pushToVector(&symbols, ParseExternalDeclareStmt(&ps));
	}

	if(!exceptToken(&ps, TokenEnd)){
		Debug(__FILE__, __LINE__, "Token list not end with TokenEnd");
	}
}