/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

const int POINTER_SIZE = 8;

DataType IntType     = {DTT_Basic, 8, NULL, BTypeId_int    };
DataType Int8Type    = {DTT_Basic, 1, NULL, BTypeId_int8   };
DataType Int16Type   = {DTT_Basic, 2, NULL, BTypeId_int16  };
DataType Int32Type   = {DTT_Basic, 4, NULL, BTypeId_int32  };
DataType Int64Type   = {DTT_Basic, 8, NULL, BTypeId_int64  };
DataType UintType    = {DTT_Basic, 8, NULL, BTypeId_uint   };
DataType Uint8Type   = {DTT_Basic, 1, NULL, BTypeId_uint8  };
DataType Uint16Type  = {DTT_Basic, 2, NULL, BTypeId_uint16 };
DataType Uint32Type  = {DTT_Basic, 4, NULL, BTypeId_uint32 };
DataType Uint64Type  = {DTT_Basic, 8, NULL, BTypeId_uint64 };
DataType FloatType   = {DTT_Basic, 8, NULL, BTypeId_float  };
DataType Float32Type = {DTT_Basic, 4, NULL, BTypeId_float32};
DataType Float64Type = {DTT_Basic, 4, NULL, BTypeId_float64};
DataType BoolType    = {DTT_Basic, 1, NULL, BTypeId_bool   };
DataType CharType    = {DTT_Basic, 4, NULL, BTypeId_char   };
DataType VoidType    = {DTT_Basic, 0, NULL, BTypeId_void   };

DataType* _newDataType(int type){
	DataType* ret = xmalloc(sizeof(DataType), __FILE__, __LINE__);
	ret->dtType = type;
	return ret;
}

Symbol* _newSymbol(int type){
	Symbol* ret = xmalloc(sizeof(Symbol), __FILE__, __LINE__);
	ret->sType = type;
	return ret;
}

char* type2char(DataType* dt){
	if(dt->dtType == DTT_Basic){
		switch(dt->btypeId){
		    case BTypeId_int: return "int";
		    case BTypeId_uint: return "uint";
		}
	}
}

void dumpSymbol(Symbol* symbol, int indent){
	String* str;
	char tmp[80];
	int i;
	for(i=0; i<indent; i+=1){
		tmp[i]=' ';
	}
	tmp[i]=0;
	switch(symbol->sType){
	    case ST_Module:
		printf("%sModule: %s\n", tmp, symbol->sName->data);
		printf("%s  package: ", tmp);
		for(i=0; i<symbol->modPackage.item; i+=1){
			str=symbol->modPackage.data[i];
			printf("%s.", str->data);
		}
		printf("\b\n");
		for(i=0; i< symbol->modSymbols.item; i+=1){
			dumpSymbol(symbol->modSymbols.data[i], indent+2);
		}
		break ;
	    case ST_Variable:
		printf("%sVariable(%s): %s\n", tmp, type2char(symbol->varDataType), symbol->sName->data);
		break ;
	    case ST_Function:
		printf("%sFunciton(ret:%s): %s\n", tmp, type2char(symbol->funcRetType), symbol->sName->data);
		break;
	}
	return ;
}

DataType* _parseDataType(ParseState* ps){
	DataType* ret;
	DataType* bdt;
	int pointerLevel = 0;
	int arrayDimCnt = 0;
	int arrayDimEnt[MAX_ARRAY_DIM];
	int i;
	int sum;

	switch(ps->tokenList->tCode){
	    case TKw_int :	bdt = &IntType; break;
	    case TKw_int8 : 	bdt =  &Int8Type; break;
	    case TKw_int16 :	bdt =  &Int16Type; break;
	    case TKw_int32 :	bdt =  &Int32Type; break;
	    case TKw_int64 :	bdt =  &Int64Type; break;
	    case TKw_uint :	bdt =  &UintType; break;
	    case TKw_uint16 :	bdt =  &Uint16Type; break;
	    case TKw_uint32 :	bdt =  &Uint32Type; break;
	    case TKw_uint64 :	bdt =  &Uint64Type; break;
	    case TKw_float :	bdt =  &FloatType; break;
	    case TKw_float32 :	bdt =  &Float32Type; break;
	    case TKw_float64 :	bdt =  &Float64Type; break;
	    case TKw_bool :	bdt =  &BoolType; break;
	    case TKw_char :	bdt =  &CharType; break;
	    case TKw_void :	bdt =  &VoidType; break;
	    case TokenID :
	    default:
		return bdt = NULL;
		ParseFatal(ps, "dataType");
	}
	eatToken(ps);
	return bdt;
/*
	while(exceptToken(ps,'*')){
		pointerLevel += 1;
	}
	while(true){
		if(!exceptToken(ps, '[')){
			break;
		}
		if(ps->tokenList->tCode != TokenInteger){
			ParseFatal(ps,"Integer");
		}
		arrayDimEnt[arrayDimCnt] = ps->tokenList->iValue;
		arrayDimCnt += 1;
		eatToken(ps);
		exceptTokenDealError(ps, ']',"]");
	}

	if(pointerLevel && arrayDimCnt){
		ret = _newDataType(DTT_PointerArray);
		ret->pointLevel = pointerLevel;
		ret->arrayDimCnt = arrayDimCnt;
		sum=1;
		for(i = 0; i<arrayDimCnt; i++){
			ret->arrayDimItem[i]=arrayDimEnt[i];
			sum *= arrayDimEnt[i];
		}
		ret->dtBytes = POINTER_SIZE * sum;
		ret->dtBtype = bdt;
		return ret;
	}

	if(arrayDimCnt){
		if( bdt ==&VoidType ){
			Fatal(ps->filename,ps->tokenList->tLine, "cant define array of void");
		}
		ret = _newDataType(DTT_PointerArray);
		ret->arrayDimCnt = arrayDimCnt;
		sum=1;
		for(i = 0; i<arrayDimCnt; i++){
			ret->arrayDimItem[i]=arrayDimEnt[i];
			sum *= arrayDimEnt[i];
		}
		ret->dtBytes = POINTER_SIZE * sum;
		ret->dtBtype = bdt;
		return ret;
	}

	if(pointerLevel){
		ret = _newDataType(DTT_Pointer);
		ret->pointLevel = pointerLevel;
		ret->dtBytes = POINTER_SIZE;
		ret->dtBtype = bdt;
		return ret;
	}
*/
}

void _parsePackage(ParseState* ps, Vector* vector){
	exceptTokenDealError(ps, TKw_package, "package");
    repeat:
	if(ps->tokenList->tCode == TokenID) {
		pushToVector(vector, ps->tokenList->sValue);
		eatToken(ps);
		if(exceptToken(ps, TOp_dot)){
			goto repeat;
		}
		if(exceptToken(ps, ';')){
			pushToVector(vector, GetModuleName(ps->filename));
			return;
		}
		ParseFatal(ps, ";");
	}
	ParseFatal(ps, "id");
}

void _appendSymbol(ParseState* ps, Vector* scope, Symbol* symbol){
	Symbol* s;
	int i;

	for(i=0; i<scope->item; i+=1){
		s = scope->data[i];
		if(s->sName != symbol->sName){
			continue;
		}
		Error(ps->filename, ps->tokenList->tLine, "redefined (%s)", symbol->sName->data);
	}
	pushToVector(scope, symbol);
}

Symbol* _parseFunctionDeclare(ParseState* ps, DataType* dt, String* name){
	Symbol* symbol = _newSymbol(ST_Function);

	symbol->sName = name;
	symbol->funcRetType = dt;
	exceptTokenDealError(ps, ')', ")");
	if(exceptToken(ps, ';')){
		return symbol;
	}
	exceptTokenDealError(ps, '{', "{");
	while(!exceptToken(ps, '}')){
		eatToken(ps);
	}
	return symbol;
}

Symbol* _parseExternalDeclare(ParseState* ps){
	Symbol * symbol;
	DataType* dt;
	String* name;

	dt = _parseDataType(ps);
	if(!dt){
		Fatal(ps->filename, ps->tokenList->tLine, "except type declare");
	}

	if(ps->tokenList->tCode != TokenID){
		ParseFatal(ps, "id");
	}
	name = ps->tokenList->sValue;
	eatToken(ps);
	if(exceptToken(ps,'(')){
		return _parseFunctionDeclare(ps, dt, name);
	}
	exceptTokenDealError(ps, ';', ";");

	symbol = _newSymbol(ST_Variable);
	symbol->varDataType = dt;
	symbol->sName = name;

	return symbol;
}


/*
 * <ParseModule>:= <_parsePackage> <ExternalDeclareStmt>{0,n}
 */
Symbol* ParseModule(char* filename, String* name){
	ParseState ps = {};
	Symbol* ret = _newSymbol(ST_Module);
	ret->sName = name;

	ps.filename = filename;
	ps.tokenList = ScanFile(filename);

	if(!exceptToken(&ps, TokenStart)){
		Debug(__FILE__, __LINE__, "Token list not start with TokenStart");
	}

	_parsePackage(&ps, &ret->modPackage);

	/*
	while(ps.tokenList->tCode == TKw_import){
		pushToVector(&imports, ParseImportStmt(&ps));
	}
	*/

	while(ps.tokenList->tCode != TokenEnd){
		_appendSymbol(&ps, &ret->modSymbols, _parseExternalDeclare(&ps));
	}

	if(!exceptToken(&ps, TokenEnd)){
		Debug(__FILE__, __LINE__, "Token list not end with TokenEnd");
	}
	dumpSymbol(ret, 0);
	return ret;
}