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
		if(exceptToken(ps, Token_dot)){
			goto repeat;
		}
		if(exceptToken(ps, Token_as)){
			if(ps->tokenList->tCode == Token_ID){
				alias = ps->tokenList->sValue;
				eatToken(ps);
				if(exceptToken(ps, ';')){
					return ;// ret;
				}
				ParseFatal(ps, ";");
			}
			ParseFatal(ps, "id");
		}
		if(exceptToken(ps, ';')){
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
		if(exceptToken(ps, Token_dot)){
			goto repeat;
		}
		if(exceptToken(ps, Token_semicon)){
			VectorPush(vector, GetModuleName(ps->filename));
			return;
		}
		ParseFatal(ps, ";");
	}
	ParseFatal(ps, "id");
}

/*  <Module>:= <Package> <ExternalDeclare>{0,n}  */
Symbol* ParseModule(char* filename, String* name){
	Symbol* ret = SymbolAlloc(ST_Module);
	ret->sName = name;
	ParseState ps = {};

	ps.filename = filename;
	ps.tokenList = ScanFile(filename);

	ParseMatchToken(&ps, Token_Start);
	parsePackage(&ps, &ret->modPackage);
	//while(ps.tokenList->tCode == Token_import){
	//	pushToVector(&imports, ParseImportStmt(&ps));
	//}
	while(ps.tokenList->tCode != Token_EOF){
		ParseExternalStmt(&ps, ret);
	}
	ParseMatchToken(&ps, Token_EOF);

	return ret;
}