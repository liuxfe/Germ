/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"
#include "scanner.h"

void parseImport(ParseState* ps){
	Vector  imp;
	String* alias;
	//Symbol* ret = SymbolAlloc(ST_Module);

	ParseMatchToken(ps, Token_import);
    repeat:
	if(ps->tokenList->tCode == Token_ID) {
		VectorPush(&imp, ps->tokenList->sValue);
		eatToken(ps);
		if(ParseExceptToken(ps, Token_dot)){
			goto repeat;
		}
		if(ParseExceptToken(ps, Token_as)){
			if(ps->tokenList->tCode == Token_ID){
				alias = ps->tokenList->sValue;
				eatToken(ps);
				if(ParseExceptToken(ps, ';')){
					return ;// ret;
				}
				ParseFatal(ps, ";");
			}
			ParseFatal(ps, "id");
		}
		if(ParseExceptToken(ps, ';')){
			alias = VectorLastItem(&imp);
			return ;//ret;
		}
		ParseFatal(ps, ";");
	}
	ParseFatal(ps, "id");
	return ; //NULL; //[-Wreturn-type]
}

void parsePackage(ParseState* ps, Vector* vector){
	ParseMatchToken(ps, Token_package);
    repeat:
	if(ps->tokenList->tCode == Token_ID) {
		VectorPush(vector, ps->tokenList->sValue);
		eatToken(ps);
		if(ParseExceptToken(ps, Token_dot)){
			goto repeat;
		}
		if(ParseExceptToken(ps, Token_semicon)){
			VectorPush(vector, GetModuleName(ps->filename));
			return;
		}
		ParseFatal(ps, ";");
	}
	ParseFatal(ps, "id");
}

/*  <Module>:= <Package> <ExternalDeclare>{0,n}  */
Symbol* ParseModule(char* filename, String* name){
	ParseState ps = {};
	ps.filename = filename;
	ps.tokenList = ScanFile(filename);

	Symbol* ret = SymbolAlloc(ST_Module, name);

	parsePackage(&ps, &ret->modPackage);

	//while(ps.tokenList->tCode == Token_import){
	//	pushToVector(&imports, ParseImportStmt(&ps));
	//}

	while(!ParseExceptToken(&ps, Token_EOF)){
		ParseExternalStmt(&ps, ret);
	}

	return ret;
}