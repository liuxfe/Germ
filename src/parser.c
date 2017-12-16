/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

void eatToken(ParseState* ps){
	Token* t = ps->tokenList;
	ps->tokenList = ps->tokenList->tNext;
	if(0){
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

void _parseImport(ParseState* ps){
	Vector  imp;
	String* alias;
	//Symbol* ret = SymbolAlloc(ST_Module);

	exceptToken(ps, TKw_import);
    repeat:
	if(ps->tokenList->tCode == TokenID) {
		VectorPush(&imp, ps->tokenList->sValue);
		eatToken(ps);
		if(exceptToken(ps, TOp_dot)){
			goto repeat;
		}
		if(exceptToken(ps, TKw_as)){
			if(ps->tokenList->tCode == TokenID){
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

void _parsePackage(ParseState* ps, Vector* vector){
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
Symbol* _parseModule(char* filename, String* name){
	int i;
	Symbol* s;
	Symbol* ret = SymbolAlloc(ST_Module);
	ret->sName = name;
	ParseState ps = {};

	ps.filename = filename;
	ps.tokenList = ScanFile(filename);

	exceptToken(&ps, TokenStart);

	_parsePackage(&ps, &ret->modPackage);

	//while(ps.tokenList->tCode == TKw_import){
	//	pushToVector(&imports, ParseImportStmt(&ps));
	//}

	while(ps.tokenList->tCode != TokenEnd){
		ParseExternalDeclare(&ps, &ret->modSymbols);
	}

	exceptToken(&ps, TokenEnd);
	
	for(i=0; i<ret->modSymbols.item; i+=1){
		s = ret->modSymbols.data[i];
		if(s->sType == ST_Function && s->funcTokens){
			ps.tokenList = s->funcTokens;
			ParseInternalStmt(&ps, s);
		}
	}

	if(1){
		SymbolDump(ret, 0);
	}

	return ret;
}

Symbol* ParseFile(char* filename){
	return _parseModule(filename, GetModuleName(filename));
}