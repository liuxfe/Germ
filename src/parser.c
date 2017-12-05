/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

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

Symbol* _newSymbol(int type){
	Symbol* ret = xmalloc(sizeof(Symbol), __FILE__, __LINE__);
	ret->sType = type;
	return ret;
}

Statement* _newStatement(int type){
	Statement* ret = xmalloc(sizeof(Statement), __FILE__, __LINE__);
	ret->stmtType = type;
	return ret;
}

typedef struct _parseState{
	char*    filename;
	Token*   tokenList;
} ParseState;

void _eatToken(ParseState* ps){
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

bool _exceptToken(ParseState* ps, int tcode){
	if(ps->tokenList && ps->tokenList->tCode == tcode){
		_eatToken(ps);
		return true;
	}
	return false;
}

Statement* _parsePackageStmt(ParseState* ps){
	Statement* ret = _newStatement(Stmt_package);

	_exceptToken(ps,TKw_package);

	while(true){
		if(ps->tokenList->tCode == TokenID) {
			pushToVector(&(ret->pkgVector),ps->tokenList->sValue);
			_exceptToken(ps,TokenID);
			if(_exceptToken(ps, TOp_dot)){
				continue;
			}
			if(_exceptToken(ps, ';')){
				break;
			}
		}
		Fatal(ps->filename, ps->tokenList->tLine, "except id got(%d)",ps->tokenList->tCode);
	}

	if(1){
		int i;
		String* s;
		printf("ParsePackageStmt:\t");
		for(i=0;i<ret->pkgVector.item;i++){
			s= ret->pkgVector.data[i];
			printf("%s\t", s->data);
		}
		printf("\n");
	}
	return ret;
}

Statement* _parseImportStmt(ParseState* ps){
	Statement* ret = _newStatement(Stmt_import);

	while(true){
		if(ps->tokenList->tCode == TokenID) {
			pushToVector(&(ret->impVector),ps->tokenList->sValue);
			_exceptToken(ps,TokenID);
			if(_exceptToken(ps, TOp_dot)){
				continue;
			}
			if(_exceptToken(ps, ';')){
				ret->impAlias = lastItemOfVector(&(ret->impVector));
				break;
			}
			if(_exceptToken(ps, TKw_as)){
				if(ps->tokenList->tCode == TokenID){
					ret->impAlias = ps->tokenList->sValue;
					_exceptToken(ps, TokenID);
					if(_exceptToken(ps, ';')){
						break;
					}
					Fatal(ps->filename, ps->tokenList->tLine, "except ';' got(%d)",ps->tokenList->tCode);
				}
			}
		}
		Fatal(ps->filename, ps->tokenList->tLine, "except id got(%d)",ps->tokenList->tCode);
	}
	if(1){
		int i;
		String* s;
		printf("ParseImportStmt:\t");
		for(i=0;i<ret->impVector.item;i++){
			s= ret->impVector.data[i];
			printf("%s\t", s->data);
		}
		printf("alias:%s\n", ret->impAlias->data);
	}
	return ret;
}

Statement* _parseTypeDecl(ParseState* ps, Symbol* scope){
	return NULL;
}

Statement* _parseDeclStmt(ParseState* ps, Symbol* scope){
	DataType *dt;
	DataType *bdt;

	if(_exceptToken(ps, TKw_typedef)){
		//return _parseTypeDeclare(ps, scope);
	}

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
		Fatal(ps->filename, ps->tokenList->tLine,"except dataType declear");
	}

	if(_exceptToken(ps, '[')){
		//
	}

	return NULL;
}

/*
 * <ParseModule>:= <pkgstmt> <impStmt>{0,n} <declStmt>{0,n}
 */
void ParseFile(char* filename){
	ParseState ps;
	Statement* pkgstmt;
	Vector impStmts;
	Vector declStmts;

	ps.filename = filename;
	ps.tokenList = ScanFile(filename);

	_exceptToken(&ps, TokenStart);

	pkgstmt = _parsePackageStmt(&ps);

	while(_exceptToken(&ps, TKw_import)){
		pushToVector(&impStmts, _parseImportStmt(&ps));
	}

	while(ps.tokenList){
		pushToVector(&declStmts,_parseDeclStmt(&ps, NULL));
	}
}