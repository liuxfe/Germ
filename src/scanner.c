/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

static Token* newToken(int tokencode){
	Token* ret = xmalloc(sizeof(Token));
	ret->tCode = tokencode;
	ret->tNext = null;
	return ret;
}

static bool isId(char ch){
	return (ch =='_' || (ch >= 'a' && ch <= 'z') 
			 || (ch >= 'A' && ch <= 'Z'));
}

static bool isId2(char ch){
	return (ch =='_' || (ch >= 'a' && ch <= 'z') 
			 || (ch >= 'A' && ch <= 'Z')
			 || (ch >= '0' && ch <= '9'));
}

static bool isNumber(char ch){
	return (ch >='1' && ch <= '9');
}

static bool isNumber2(char ch){
	return (ch >='0' && ch <= '9');
}

Token* lexical(Buffer* buf, char** cur, int* line){
	char* start;
	Token* ret;
	char *p = *cur;

    repeat:
	while( *p == ' ' || *p== '\t' || *p== '\r'){
		p++;
	}
	if( *p == '\n' ){
		p++;
		(*line)++;
		goto repeat;
	}

	if(isId(*p)){
		start = p++ ;
		ret = newToken(TokenID);
		while(isId2(*p)){
			p++;
		}
		ret->tValue.s=storeString(start, p - start);
		*cur = p;
		if( ret->tValue.s->symbol){
			if(ret->tValue.s->symbol->sType == ST_KeyWord){
				ret->tCode = ret->tValue.s->symbol->sValue.i;
			}
		}
		return ret;
	}

	if(isNumber(*p)){
		ret = newToken(TokenInteger);
		ret->tValue.i= *p - '0';
		p++;
		while(isNumber2(*p)){
			ret->tValue.i = ret->tValue.i * 10 + *p - '0';
			p++;
		}
		*cur = p;
		return ret;
	}
	// deal with other chars.
	switch(*p){
	    case '{' : case '}' : case '[' : case ']' :
	    case '(' : case ')' : case ';' : case ':' :
	    case ',' :
		*cur =p +1;
		return newToken(*p);
	    case '.' :
		if( *(p+1) =='.' && *(p+2) == '.'){
			*cur = p+3;
			return newToken(TOp_threeDot);
		}else{
			*cur = p+1;
			return newToken(TOp_dot);
		}
	    case '+' :
		if( *(p+1) == '+'){
			*cur = p+2;
			return newToken(TOp_inc);
		}else if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_addAssign);
		}else{
			*cur = p+1;
			return newToken(TOp_add);
		}
	    case '-' :
		if( *(p+1) == '-'){
			*cur = p+2;
			return newToken(TOp_dec);
		}else if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_subAssign);
		}else if( *(p+1) == '>'){
			*cur = p+2;
			return newToken(TOp_ra);
		}else{
			*cur = p+1;
			return newToken(TOp_sub);
		}
	    case '*' :
		if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_mulAssign);
		}else{
			*cur = p+1;
			return newToken(TOp_star);
		}
	     case '/' :
		if( *(p+1) == '/'){		// skip line comment.
			while(*p != '\n'){
				p++;
			}
			goto repeat;
		} else if(*(p+1) =='*'){	// skip multline comment.
			p++;
			do{
				p++;
				if( *p == '\n'){
					(*line)++;
				}
				if(!*p){
					printf("Error: lexical multline comment not close");
					return newToken(TokenEnd);
				}
			}while(!(*p == '*' && *(p+1) == '/'));
			p++;p++;
			goto repeat;
		} else if( *(p+1) == '='){
			*cur = p+1;
			return newToken(TOp_divAssign);
		} else {
			*cur = p+1;
			return newToken(TOp_div);
		}
	    case '%' :
		if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_remAssign);
		}else{
			*cur = p+1;
			return newToken(TOp_rem);
		}
	    case '!' :
		if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_notEq);
		}else{
			*cur = p+1;
			return newToken(TOp_not);
		}
	    case '&' :
		if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_andAssign);
		}else if ( *(p+1) == '&'){
			*cur = p+2;
			return newToken(TOp_andAnd);
		} else {
			*cur = p+1;
			return newToken(TOp_and);
		}
	    case '=' :
		if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_eq);
		}else{
			*cur = p+1;
			return newToken(TOp_assign);
		}
	    case '|' :
		if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_orAssign);
		}else if ( *(p+1) == '|'){
			*cur = p+2;
			return newToken(TOp_orOr);
		} else {
			*cur = p+1;
			return newToken(TOp_or);
		}
	    case '~' :
		if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_negAssign);
		}else{
			*cur = p+1;
			return newToken(TOp_neg);
		}
	    case '>' :
		if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_gtEq);
		}else if ( *(p+1) == '>'){
			if( *(p+2) == '=' ){
				*cur = p+3;
				return newToken(TOp_shrAssign);
			} else{
				*cur = p+2;
				return newToken(TOp_shr);
			}
		}else{
			*cur = p+1;
			return newToken(TOp_gt);
		}
	    case '<' :
		if( *(p+1) == '='){
			*cur = p+2;
			return newToken(TOp_ltEq);
		}else if ( *(p+1) == '<'){
			if( *(p+2) == '=' ){
				*cur = p+3;
				return newToken(TOp_shlAssign);
			} else{
				*cur = p+2;
				return newToken(TOp_shl);
			}
		}else{
			*cur = p+1;
			return newToken(TOp_lt);
		}
	    case '\'':
		ret =newToken(TokenChar);
		p++;
		if(*p == '\\'){
			p++;
			ret->tValue.i=escapeChar(&p);
		} else if( *p == '\''){
			printf("Error: Not have availbe char");
			ret->tValue.i= 0 ; // 空字符就设置成0.
			*cur = ++p;
			return ret;
		} else{
			ret->tValue.i = *p;
			p++;
		}
		// 处理关闭.
		if(*p == '\''){
			*cur = ++p;
			return ret;
		}else{
			printf("Error: have more chars in char:%c\n", *p);
			// skip the more chars.
			while(*p != '\''){
				p++;
			}
			*cur = ++p;
			return ret;
		}
	    case '"' :
		ret = newToken(TokenString);
		ret->tValue.s=scanStringLiteral(&p);
		*cur = p;
		return ret;
	    case '\0':
		*cur = ++p; 
		return newToken(TokenEnd);
	    default:
		printf("Error: lexical can't recognize char:%d(%c)\n", *p, *p);
		++p;
		goto repeat;
	}
}

// scan the buffer, return the token list.
Token* doScan(Buffer* buf){
	Token* head = newToken(TokenStart);
	Token* tail = head;
	char* p = buf->data;
	int line = 1;

	do{
		tail->tPosFile = buf->filename;
		tail->tPosLine = line;
		tail->tNext = lexical(buf, &p, &line);
		tail = tail->tNext;
	}while(tail->tCode != TokenEnd);

	return head;
}

Token* scanFile(char* filename){
	Buffer* buf;
	Token* tokenlist;

	buf = readFileToBuffer(filename);
	tokenlist = doScan(buf);

	deleteBuffer(buf);

	return tokenlist;
}

static void printToken(Token* t){
	printf("(File: %s Line:%d)\t", t->tPosFile, t->tPosLine);
	if(t->tCode >= TKw_package && t->tCode <= TKw_const){
		printf("KeyWord:%s\n", t->tValue.s->data);
		return;
	}
	if(t->tCode == TokenID){
		printf("Id:%s\n", t->tValue.s->data);
		return;
	}
	if(t->tCode == TokenChar){
		printf("Char:%d(%c)\n", t->tValue.i,t->tValue.i);
		return;
	}
	if(t->tCode == TokenString){
		printf("String:%s\n", t->tValue.s->data);
		return;
	}
	if(t->tCode == TokenInteger){
		printf("Number:%d\n", t->tValue.i);
		return;
	}
	printf("TCode:%d\n", t->tCode);
}

void printTokenList(Token* t){
	Token* tmp=t;
	printf("----------Debug Token-------------\n");
	while(tmp->tCode != TokenEnd){
		printToken(tmp);
		tmp = tmp->tNext;
	}
	printf("----------------------------------\n");
}