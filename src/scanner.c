/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

static token* newToken(int tokencode){
	token* ret;

	ret = malloc(sizeof(token));
	if ( !ret ){
		printf("Error: alloc token return null");
		exit(-1);
	}
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
	return (ch >='1' && ch <= '9');
}

static uint char_escape(char **str){
	uint tmp;
	char *p =*str;
	switch(*p){
	    case 'a':
		*str = ++p;
		return '\a';
	    case 'b':
		*str = ++p;
		return '\b';
	    case 'f':
		*str = ++p;
		return '\f';
	    case 'n':
		*str = ++p;
		return '\n';
	    case 'r':
		*str = ++p;
		return '\r';
	    case 't':
		*str = ++p;
		return '\t';
	    case 'v':
		*str = p++;
		return '\v';
	    case '\\':
		*str = p++;
		return '\\';
	    case '\'':
		*str = p++;
		return '\'';
	    case '"':
		*str = p++;
		return '"';
	    case '?':
		*str = p++;
		return '\?';
	    case '0':
		if( !(*(p+1)>='1' && *(p+1)<='9') ){
			*str= p;
			return '\0';
		}
	    case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7':
		tmp = *p - '0';
		p++;
		if( *p >='0' && *p<='7'){
			tmp= tmp * 8 + *p - '0';
			p++;
		}
		if( *p >='0' && *p<='7'){
			tmp= tmp * 8 + *p - '0';
			p++;
		}
		*str = p;
		return tmp;
	    case 'x':
		p++;
		// 处理第一个字符.
		if( *p >='0' && *p <='9'){
			tmp = *p - '9';
		} else if( *p >= 'A' && *p <='F'){
			tmp = *p - 'A' +10;
		}else if( *p >= 'a' && *p <='f'){
			tmp = *p - 'a' +10;
		} else {
			*str =p;
			return 'x';
		}
		p++;
		// 处理第二个字符.
		if( *p >='0' && *p <='9'){
			tmp = tmp * 16 + *p - '9';
		} else if( *p >= 'A' && *p <='F'){
			tmp = tmp * 16 + *p - 'A' +10;
		}else if( *p >= 'a' && *p <='f'){
			tmp = tmp * 16 + *p - 'a' +10;
		} else {
			*str =++p;
			return tmp;
		}
		*str = ++p;
		return tmp;
	    default:
		*str = ++p;
		return *(p-1);
	}
}

token* lexical(Buffer* buf, char** cur){
	dynstr *ds;
	token* ret;
	char *p = *cur;

    repeat:
	// skip white chars first.
	while( *p == ' ' || *p== '\t' || *p== '\n'){
		p++;
	}
	// deal with id and keywords.
	if(isId(*p)){
		p++;
		ret = newToken(TokenId);
		while(isId2(*p)){
			p++;
		}
		ret->tValue.s.start = *cur;
		ret->tValue.s.len = p - *cur;
		*cur = p;
		//printf("TokenId\t");
		return ret;
	}
	// deal with number.
	if(isNumber(*p)){
		ret = newToken(TokenInteger);
		ret->tValue.i= *p - '0';
		p++;
		while(isNumber2(*p)){
			ret->tValue.i = ret->tValue.i * 10 + *p - '0';
			p++;
		}
		*cur = p;
		//printf("TokenNumber\t");
		return ret;
	}
	// deal with other chars.
	switch(*p){
	    case '{':
	    case '}' :
	    case '[' :
	    case ']' :
	    case '(' :
	    case ')' :
	    case ';' :
	    case ':' :
	    case ',' :
		*cur =p +1;
		return newToken(*p);
	    case '.' :
		if( *(p+1) =='.' && *(p+2) == '.'){
			*cur = p+3;
			return newToken(TokenThreeDot);
		}else{
			*cur = p+1;
			return newToken(TokenDot);
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
			return newToken(TokenStar);
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
			ret->tValue.i=char_escape(&p);
		} else if( *p == '\''){
			printf("Error: Not have availbe char");
			ret->tValue.i= 0 ; // 空字符就设置成0.
			*cur = ++p;
			return ret;
		} else{
			ret->tValue.i=*p;
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
		ds  = newDynstr();
		++p;
		while(*p && (*p !='"')){
			if(*p == '\\'){
				++p;
				ds = appendChar(ds, (char)char_escape(&p));
			} else{
				ds = appendChar(ds, *p);
				++p;
			}
		}
		ds = appendChar(ds, '\0');
		ret->tValue.ds = ds;
		
		if( *p =='"'){
			*cur = ++p; // skip the close ".
			return ret;
		}
		printf("Error: lexical sting not close");
		*cur = p; // skip the close ".
		return ret;
	    case '\0':
		*cur = ++p; 
		return newToken(TokenEnd);
	    default:
		printf("Error: lexical can't recognize char '%c'\n", *p);
		++p;
		goto repeat;
	}
}

// scan the buffer, return the token list.
token* doScan(Buffer* buf){
	token* head = newToken(TokenStart);
	token* tail = head;
	char* p = buf->data;

	do{
		tail->tNext = lexical(buf, &p);
		tail = tail->tNext;
	}while(tail->tCode != TokenEnd);

	return head;
}

static void printToken(token* t){
	if(t->tCode == TokenChar){
		printf("Char token value:%d(%c)\n", t->tValue.i,t->tValue.i);
		return;
	}
	if(t->tCode == TokenString){
		printf("String token value:%s\n", t->tValue.ds->data);
		return;
	}
	printf("token code:%d\n", t->tCode);
}

void printTokenList(token* t){
	token* tmp=t;
	printf("----------Debug Token-------------\n");
	while(tmp->tCode != TokenEnd){
		printToken(tmp);
		tmp = tmp->tNext;
	}
	printf("----------------------------------\n");
}