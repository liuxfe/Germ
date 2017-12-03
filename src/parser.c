/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

BasicType IntType     = {DTT_Basic, 8, BTypeId_int    };
BasicType Int8Type    = {DTT_Basic, 1, BTypeId_int8   };
BasicType Int16Type   = {DTT_Basic, 2, BTypeId_int16  };
BasicType Int32Type   = {DTT_Basic, 4, BTypeId_int32  };
BasicType Int64Type   = {DTT_Basic, 8, BTypeId_int64  };
BasicType UintType    = {DTT_Basic, 8, BTypeId_uint   };
BasicType Uint8Type   = {DTT_Basic, 1, BTypeId_uint8  };
BasicType Uint16Type  = {DTT_Basic, 2, BTypeId_uint16 };
BasicType Uint32Type  = {DTT_Basic, 4, BTypeId_uint32 };
BasicType Uint64Type  = {DTT_Basic, 8, BTypeId_uint64 };
BasicType FloatType   = {DTT_Basic, 8, BTypeId_float  };
BasicType Float32Type = {DTT_Basic, 4, BTypeId_float32};
BasicType Float64Type = {DTT_Basic, 4, BTypeId_float64};
BasicType BoolType    = {DTT_Basic, 1, BTypeId_bool   };
BasicType CharType    = {DTT_Basic, 4, BTypeId_char   };
BasicType VoidType    = {DTT_Basic, 0, BTypeId_void   };

typedef struct _parserState{
	char*    filename;
	Token**  tokenItem;
	int      tokenCnt;
	int      tokenCur;
} ParserState;

BasicType* matchType(Token* t){
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

void except(Token** tokenlist, uint tcode){
	Token* t = *tokenlist;
	if(t->tCode == tcode){
		
		//deleteToken(t);
		return;
	}
	printf("except:%d(%c) not match at (%s,%d)", tcode,tcode,NULL,t->tLine);
	exit(-1);
}

PackageStmt* parsePackageStmt(Token** tokenlist){
	Token* t = *tokenlist;
	PackageStmt* ret = xmalloc(sizeof(PackageStmt));

	ret->stmtType = Stmt_package;

	except(&t,TKw_package);

    repeat:
	if(t->tCode == TokenID){
		pushToVector(&(ret->vector),t->sValue);
		except(&t,TokenID);
		if(t->tCode == TOp_dot){
			except(&t,TOp_dot);
			goto repeat;
		}
	}
	if(t->tCode == ';'){
		if(ret->vector.item == 0){
			printf("Error: error");
			exit(-1);
		}
		except(&t,';');
		return ret;
	}
	printf("Error: error");
	exit(-1);
}

void printPackageStmt(PackageStmt* stmt){
	int i;
	String* s;

	printf("------------");
	for(i=0;i<stmt->vector.item; i++){
		s=stmt->vector.data[i];
		printf("%s\t",s->data);
	}
	printf("------------");
}

Statement* parserIfstmt(){
	
}