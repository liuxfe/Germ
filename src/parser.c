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
	TokenFree(t);
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

void parsePackage(ParseState* ps, Vector* vector){
	exceptTokenDealError(ps, TKw_package, "package");
    repeat:
	if(ps->tokenList->tCode == TokenID) {
		VectorPush(vector, ps->tokenList->sValue);
		eatToken(ps);
		if(exceptToken(ps, TOp_dot)){
			goto repeat;
		}
		if(exceptToken(ps, ';')){
			VectorPush(vector, GetModuleName(ps->filename));
			return;
		}
		ParseFatal(ps, ";");
	}
	ParseFatal(ps, "id");
}

/*  <Module>:= <Package> <ExternalDeclare>{0,n}  */
Symbol* parseModule(char* filename, String* name){
	ParseState ps = {};
	Symbol* ret = SymbolAlloc(ST_Module);
	ret->sName = name;

	ps.filename = filename;
	ps.tokenList = ScanFile(filename);

	if(!exceptToken(&ps, TokenStart)){
		Debug(__FILE__, __LINE__, "Token list not start with TokenStart");
	}

	parsePackage(&ps, &ret->modPackage);

	//while(ps.tokenList->tCode == TKw_import){
	//	pushToVector(&imports, ParseImportStmt(&ps));
	//}

	while(ps.tokenList->tCode != TokenEnd){
		ParseExternalDeclare(&ps, &ret->modSymbols);
	}

	if(!exceptToken(&ps, TokenEnd)){
		Debug(__FILE__, __LINE__, "Token list not end with TokenEnd");
	}
	
	if(1){
		SymbolDump(ret, 0);
	}
	
	return ret;
}

Symbol* ParseFile(char* filename){
	return parseModule(filename, GetModuleName(filename));
}