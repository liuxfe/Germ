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

DataType* matchType(Token* t){
	switch(t->tCode){
	    case TKw_int :	return &IntType;
	    case TKw_int8 : 	return &Int8Type;
	    case TKw_int16 :	return &Int16Type;
	    case TKw_int32 :	return &Int32Type;
	    case TKw_int64 :	return &Int64Type;
	    case TKw_uint :	return &UintType;
	    case TKw_uint16 :	return &Uint16Type;
	    case TKw_uint32 :	return &Uint32Type;
	    case TKw_uint64 :	return &Uint64Type;
	    case TKw_float :	return &FloatType;
	    case TKw_float32 :	return &Float32Type;
	    case TKw_float64 :	return &Float64Type;
	    case TKw_bool :	return &BoolType;
	    case TKw_char :	return &CharType;
	    case TKw_void :	return &VoidType;
	    default :		return NULL;
	}
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

Statement* _parseDeclStmt(ParseState* ps, Symbol* scope){
	if(_exceptToken(ps, TKw_typedef)){
		//return _parseTypeDeclStmt(ps, scope);
	}

	//if(_exceptToken(ps, TKw_int)){}
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