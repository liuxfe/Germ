/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Dtype* ParseDtype(ParseState* ps){
	Dtype* bdt;

	switch(ps->tokenList->tCode){
	    case Token_int8 :
		bdt = DtypeAlloc(Dtype_int8, 1);
		break; 
	    case Token_int16 :
		bdt = DtypeAlloc(Dtype_int16, 2);
		break;
	    case Token_int32 :
		bdt = DtypeAlloc(Dtype_int32, 4);
		break;
	    case Token_int64 :
		bdt = DtypeAlloc(Dtype_int64, 8);
		break;
	    case Token_int :
		bdt = DtypeAlloc(Dtype_int, 8);
		break;
	    case Token_uint8 :
		bdt = DtypeAlloc(Dtype_uint8, 1);
		break;
	    case Token_uint16 :
		bdt = DtypeAlloc(Dtype_uint16, 2);
		break;
	    case Token_uint32 :
		bdt = DtypeAlloc(Dtype_uint32, 4);
		break;
	    case Token_uint64 :
		bdt = DtypeAlloc(Dtype_uint64, 8);
		break;
	    case Token_uint :
		bdt = DtypeAlloc(Dtype_uint, 8);
		break;
	    case Token_uptr :
		bdt = DtypeAlloc(Dtype_uptr, 8);
		break;
	    case Token_float32 :
		bdt = DtypeAlloc(Dtype_float32, 4);
		break;
	    case Token_float64 :
		bdt = DtypeAlloc(Dtype_float64, 8);
		break;
	    case Token_float :
		bdt = DtypeAlloc(Dtype_float, 8);
		break;
	    case Token_bool :
		bdt = DtypeAlloc(Dtype_bool, 1);
		break;
	    case Token_char :
		bdt = DtypeAlloc(Dtype_char, 4);
		break;
	    case Token_ID :
	    default:
		return bdt = NULL;
	}
	eatToken(ps);
	return bdt;
}

void parseFunctionParam(ParseState* ps, Symbol* symbol){
	Dtype* dt;
	String* name;

	dt = ParseDtype(ps);
	if(!dt){
		ParseFatal(ps, "param require type");
	}
	name = ParseExceptTokenTD(ps);

	VectorPush(&symbol->funcDtype->dtFuncParam, dt);
	VectorPush(&symbol->funcParam, SymbolAllocVariable(name,dt,ST_ParamVar));
}

Symbol* parseFunctionDeclare(ParseState* ps){
	Dtype* dt;
	String* name;
	Symbol* symbol;

	ParseMatchToken(ps, Token_func);
	name = ParseExceptTokenTD(ps);
	dt =Xmalloc(sizeof(Dtype), __FILE__, __LINE__);
	dt->dtType = Dtype_function;

	symbol = SymbolAllocFunction(name, dt);

	ParseMatchToken(ps, Token_lparen);

	if(ParseExceptToken(ps, Token_rparen)){
		goto after_param;
	}
	if(ParseExceptToken(ps, Token_ra)){
		goto has_ra;
	}
    repeat:
	parseFunctionParam(ps,symbol);
	if(ParseExceptToken(ps, Token_comma)){
		goto repeat;
	}
	if(ParseExceptToken(ps, Token_ra)){
		goto has_ra;
	}
	if(ParseExceptToken(ps, Token_rparen)){
		goto after_param;
	}

    has_ra:
	dt->dtFuncReturn = ParseDtype(ps);
	if(!dt->dtFuncReturn){
		ParseFatal(ps, "require type");
	}
	ParseMatchToken(ps, Token_rparen);

    after_param:
	if(!ParseExceptToken(ps, Token_semicon)){	 // no function body
		ParseMatchToken(ps, Token_lbrace);
		while(!ParseExceptToken(ps, Token_rbrace)){ // not empty function
			ParseInternalStmt(ps, symbol);
		}
	}

	return symbol;
}

Symbol* ParseExternalDeclare(ParseState* ps){
	Dtype* dt;
	String* name;

	if(ps->tokenList->tCode == Token_func){
		return parseFunctionDeclare(ps);
	}

	dt = ParseDtype(ps);
	if(!dt){
		ParseFatal(ps, "type");
	}
	name = ParseExceptTokenTD(ps);
	ParseMatchToken(ps, Token_semicon);

	return SymbolAllocVariable(name, dt, ST_GlobalVar);
}

void ParseInternalDeclare(ParseState* ps, Dtype* dt, Vector* scope){
	String* name;
	Symbol* symbol;

	name = ParseExceptTokenTD(ps);

	ParseMatchToken(ps, Token_semicon);

	symbol = SymbolAllocVariable(name, dt, ST_LocalVar);
	SymbolAppend(ps, scope, symbol);
}