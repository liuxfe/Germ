/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

void except(Token** tokenlist, uint tcode){
	Token* t = *tokenlist;
	if(t->tCode == tcode){
		*tokenlist = t->tNext;
		deleteToken(t);
		return;
	}
	printf("except:%d(%c) not match at (%s,%d)", tcode,tcode,t->tPosFile,t->tPosLine);
	exit(-1);
}

PackageStmt* parsePackageStmt(Token** tokenlist){
	Token* t = *tokenlist;
	PackageStmt* ret = xmalloc(sizeof(PackageStmt));

	ret->stmtType = StmtT_package;

	except(&t,TKw_package);

    repeat:
	if(t->tCode == TokenID){
		pushToVector(&(ret->vector),t->tValue.s);
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