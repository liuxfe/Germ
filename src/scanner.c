/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Token* _newToken(int tokencode){
	Token* ret = xmalloc(sizeof(Token), __FILE__, __LINE__);
	ret->tCode = tokencode;
	return ret;
}

typedef struct _scanState{
	char* filename;
	char* buf;
	char* cur;
	int   line;
} ScanState;

bool _exceptChar(ScanState* ss, char ch){
	if(*ss->cur == ch ){
		ss->cur++;
		return true;
	}
	return false;
}

uint _escapeChar(ScanState* ss){
	uint tmp;
	switch(*ss->cur){
	    case '0': ss->cur++; return '\0';
	    case 'a': ss->cur++; return '\a';
	    case 'b': ss->cur++; return '\b';
	    case 'e': ss->cur++; return '\e';
	    case 'f': ss->cur++; return '\f';
	    case 'n': ss->cur++; return '\n';
	    case 'r': ss->cur++; return '\r';
	    case 't': ss->cur++; return '\t';
	    case 'v': ss->cur++; return '\v';
	    case '\\':ss->cur++; return '\\';
	    case '\'':ss->cur++; return '\'';
	    case '\"':ss->cur++; return '\"';
	    case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7':
		tmp = *ss->cur - '0';
		ss->cur++;
		if( *ss->cur >='0' && *ss->cur<='7'){
			tmp= tmp * 8 + *ss->cur - '0';
			ss->cur++;
		}
		if( *ss->cur >='0' && *ss->cur<='7'){
			tmp= tmp * 8 + *ss->cur - '0';
			ss->cur++;
		}
		return tmp;
	    case 'x':
		ss->cur++;
		if( xhex2num(*ss->cur) == -1){
			Error(ss->filename,ss->line, "lexical escape char");
			return 0;
		} else{
			tmp = xhex2num(*ss->cur);
			ss->cur++;
		}
		if( xhex2num(*ss->cur) == -1){
			return tmp;
		} else{
			tmp = tmp * 16 + xhex2num(*ss->cur);
			ss->cur++;
			return tmp;
		}
	    default:
		ss->cur++;
		Error(ss->filename,ss->line, "lexical escape char");
		return 0;
	}
}

Token* _scanId(ScanState* ss){
	Token* ret;
	char* start = ss->cur;

	while(*ss->cur =='_' || (*ss->cur >= 'a' && *ss->cur <= 'z')
	                     || (*ss->cur >= 'A' && *ss->cur <= 'Z')
	                     || (*ss->cur >= '0' && *ss->cur <= '9') ){
		ss->cur++;
	}

	switch(ss->cur - start){
	    case 2 :
		if(xstrncmp(start,"if",2)){
			return _newToken(TKw_if);
		}
		if(xstrncmp(start,"as",2)){
			return _newToken(TKw_as);
		}
	    case 3 :
		if(xstrncmp(start,"int",3)){
			return _newToken(TKw_int);
		}
		if(xstrncmp(start,"for",3)){
			return _newToken(TKw_for);
		}
	    case 4 :
		if(xstrncmp(start,"int8",4)){
			return _newToken(TKw_int8);
		}
		if(xstrncmp(start,"uint",4)){
			return _newToken(TKw_uint);
		}
		if(xstrncmp(start,"bool",4)){
			return _newToken(TKw_bool);
		}
		if(xstrncmp(start,"char",4)){
			return _newToken(TKw_char);
		}
		if(xstrncmp(start,"void",4)){
			return _newToken(TKw_void);
		}
		if(xstrncmp(start,"func",4)){
			return _newToken(TKw_func);
		}
		if(xstrncmp(start,"elif",4)){
			return _newToken(TKw_elif);
		}
		if(xstrncmp(start,"else",4)){
			return _newToken(TKw_else);
		}
		if(xstrncmp(start,"case",4)){
			return _newToken(TKw_case);
		}
		if(xstrncmp(start,"goto",4)){
			return _newToken(TKw_goto);
		}
		if(xstrncmp(start,"true",4)){
			ret = _newToken(TokenBool);
			ret->iValue = 1;
			return ret;
		}
		if(xstrncmp(start,"NULL",4)){
			return _newToken(TokenNULL);
		}
	    case 5 :
		if(xstrncmp(start,"int16",5)){
			return _newToken(TKw_int16);
		}
		if(xstrncmp(start,"int32",5)){
			return _newToken(TKw_int32);
		}
		if(xstrncmp(start,"int64",5)){
			return _newToken(TKw_int64);
		}
		if(xstrncmp(start,"uint8",5)){
			return _newToken(TKw_uint8);
		}
		if(xstrncmp(start,"float",5)){
			return _newToken(TKw_float);
		}
		if(xstrncmp(start,"union",5)){
			return _newToken(TKw_union);
		}
		if(xstrncmp(start,"while",5)){
			return _newToken(TKw_while);
		}
		if(xstrncmp(start,"break",5)){
			return _newToken(TKw_break);
		}
		if(xstrncmp(start,"throw",5)){
			return _newToken(TKw_throw);
		}
		if(xstrncmp(start,"const",5)){
			return _newToken(TKw_const);
		}
		if(xstrncmp(start,"false",5)){
			ret = _newToken(TokenBool);
			ret->iValue = 0;
			return ret;
		}
	    case 6 :
		if(xstrncmp(start,"import",6)){
			return _newToken(TKw_import);
		}
		if(xstrncmp(start,"uint16",6)){
			return _newToken(TKw_uint16);
		}
		if(xstrncmp(start,"uint32",6)){
			return _newToken(TKw_uint32);
		}
		if(xstrncmp(start,"uint64",6)){
			return _newToken(TKw_uint64);
		}
		if(xstrncmp(start,"struct",6)){
			return _newToken(TKw_struct);
		}
		if(xstrncmp(start,"switch",6)){
			return _newToken(TKw_switch);
		}
		if(xstrncmp(start,"return",6)){
			return _newToken(TKw_return);
		}
	    case 7 :
		if(xstrncmp(start,"package",7)){
			return _newToken(TKw_package);
		}
		if(xstrncmp(start,"float32",7)){
			return _newToken(TKw_float32);
		}
		if(xstrncmp(start,"float64",7)){
			return _newToken(TKw_float64);
		}
		if(xstrncmp(start,"typedef",7)){
			return _newToken(TKw_typedef);
		}
		if(xstrncmp(start,"default",7)){
			return _newToken(TKw_default);
		}
	    case 8 :
		if(xstrncmp(start,"continue",8)){
			return _newToken(TKw_continue);
		}
	}

	ret = _newToken(TokenID);
	ret->sValue= StoreString(start, ss->cur - start);
	return ret;
}

Token* _scanNumberLiteral(ScanState* ss){
	Token* ret = _newToken(TokenInteger);
	ret->iValue=0;

	while( *ss->cur >='0' && *ss->cur <= '9'){
		ret->iValue= ret->iValue * 10 + *ss->cur - '0';
		ss->cur++;
	}
	return ret;
}

Token* _scanCharLiteral(ScanState* ss){
	Token* ret =_newToken(TokenChar);

	ss->cur++; // skip begin char(')
	if(_exceptChar(ss, '\'')){
		Error(ss->filename, ss->line, "CharLiteral has no char");
		ret->iValue= 0 ; // 空字符就设置成0.
		return ret;
	}
	if(_exceptChar(ss, '\\')){
		ret->iValue = _escapeChar(ss);
	}else{
		ret->iValue = *ss->cur++;
	}

	if(_exceptChar(ss, '\'')){
		return ret;
	}else{
		Error(ss->filename, ss->line, "CharLiteral has too many char");
		while(*ss->cur && (*ss->cur != '\'')){ // skip the more chars.
			ss->cur++;
		}
		if(*ss->cur == '\0'){
			Error(ss->filename, ss->line, "CharLiteral not closed");
			return ret;
		}
		ss->cur++; // skip close char(')
		return ret;
	}
}

Token* _scanStringLiteral(ScanState* ss){
	char* start;
	char* tail;
	Token* ret= _newToken(TokenString);

	ss->cur++; // skip begin char(")
	tail = start = ss->cur;
	while(*ss->cur && (*ss->cur !='"')){
		if(*ss->cur == '\\'){
			ss->cur++;
			*tail = (char)_escapeChar(ss);
			tail++;
		} else{
			*tail++ = *ss->cur++;
		}
	}

	if(!_exceptChar(ss,'"')){
		Error(ss->filename, ss->line,"StringLiteral not close");
	}
	ret->sValue = StoreString(start, tail-start);
	return ret;
}

Token* _lexical(ScanState* ss){
    repeat:
	if( *ss->cur =='_' || (*ss->cur >= 'a' && *ss->cur <= 'z')
	                   || (*ss->cur >= 'A' && *ss->cur <= 'Z') ){
		return _scanId(ss);
	}

	if(*ss->cur >='0' && *ss->cur <= '9'){
		return _scanNumberLiteral(ss);
	}

	switch(*ss->cur){
	    case '\n':
		ss->line++;
	    case ' ' : case '\t' : case '\r' :
		ss->cur++;
		goto repeat;
	    case '{' : case '}' : case '[' : case ']' : case '(' : case ')' :
	    case ';' : case ':' : case ',' :
		return _newToken(*ss->cur++);
	    case '.' :
		ss->cur++;
		if(_exceptChar(ss, '.')){
			if(_exceptChar(ss, '.')){
				return _newToken(Token3dot);
			}
			Error(ss->filename, ss->line, "illegal character ..");
			return _newToken(TOp_dot);
		}
		return _newToken(TOp_dot);
	    case '+' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_addAssign);
		}
		return _newToken(TOp_add);
	    case '-' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_subAssign);
		}
		if(_exceptChar(ss, '>')){
			return _newToken(TOp_ra);
		}
		return _newToken(TOp_sub);
	    case '*' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_mulAssign);
		}
		return _newToken(TOp_star);
	    case '/' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_divAssign);
		}
		if(_exceptChar(ss, '/')){  // skip line comment.
			while(*ss->cur != '\n'){
				ss->cur++;
			}
			goto repeat;
		}
		if(_exceptChar(ss, '*')){  // skip multline comment.
			while(!(*ss->cur == '*' && *(ss->cur+1) == '/')){
				ss->cur++;
				if( *ss->cur == '\n'){
					ss->line++;
				}
				if( *ss->cur == '\0'){
					Error(ss->filename, ss->line, "Error: lexical multline comment not close");
					return NULL;
				}
			}
			ss->cur += 2;
			goto repeat;
		}
		return _newToken(TOp_div);
	    case '%' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_remAssign);
		}
		return _newToken(TOp_rem);
	    case '!' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_notEq);
		}
		return _newToken(TOp_not);
	    case '&' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_andAssign);
		}
		if(_exceptChar(ss, '&')){
			return _newToken(TOp_andAnd);
		}
		return _newToken(TOp_and);
	    case '=' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_eq);
		}
		return _newToken(TOp_assign);
	    case '|' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_orAssign);
		}
		if(_exceptChar(ss, '|')){
			return _newToken(TOp_orOr);
		}
		return _newToken(TOp_or);
	    case '~' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_negAssign);
		}
		return _newToken(TOp_neg);
	    case '>' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_ge);
		}
		if(_exceptChar(ss, '>')){
			if(_exceptChar(ss, '=')){
				return _newToken(TOp_shrAssign);
			}
			return _newToken(TOp_shr);
		}
		return _newToken(TOp_gt);
	    case '<' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_le);
		}
		if(_exceptChar(ss, '<')){
			if(_exceptChar(ss, '=')){
				return _newToken(TOp_shlAssign);
			}
			return _newToken(TOp_shl);
		}
		return _newToken(TOp_lt);
	    case '\'':
		return _scanCharLiteral(ss);
	    case '"' :
		return _scanStringLiteral(ss);
	    case '\0':
		return NULL;
	    default:
		Error(ss->filename, ss->line, "illegal character \\%d(%c)",*ss->cur, *ss->cur);
		ss->cur++;
		goto repeat;
	}
}

void _dumpTokenList(Token* tokenlist){
	Token* t = tokenlist;
	for(t=tokenlist; t; t=t->tNext){
		printf("(Line:%d)\t", t->tLine);
		if(t->tCode >= TKw_package && t->tCode <= TKw_const){
			printf("KeyWord:%d\n", t->tCode);
			continue;
		}
		if(t->tCode == TokenID){
			printf("Id:%s\n", t->sValue->data);
			continue;
		}
		if(t->tCode == TokenChar){
			printf("Char:%d(%c)\n", t->iValue,t->iValue);
			continue;
		}
		if(t->tCode == TokenString){
			printf("String:%s\n", t->sValue->data);
			continue;
		}
		if(t->tCode == TokenInteger){
			printf("Number:%d\n", t->iValue);
			continue;
		}
		printf("TCode:%d\n", t->tCode);
	}
}

Token* ScanFile(char* filename){
	ScanState ss;
	Token* tokenHead = _newToken(TokenStart);
	Token* tokenTail = tokenHead;

	ss.filename = filename;
	ss.buf = LoadFile(filename);
	ss.cur = ss.buf;
	ss.line = 1;

	do{
		tokenTail->tLine = ss.line;
		tokenTail->tNext = _lexical(&ss);
		tokenTail = tokenTail->tNext;
	}while(tokenTail);

	if(wantDumpTokenVector){
		printf("\nDump Token in file: %s\n",filename);
		_dumpTokenList(tokenHead);
	}
	return tokenHead;
}