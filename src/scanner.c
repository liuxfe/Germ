/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

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
		if( Xhex2num(*ss->cur) == -1){
			Error(ss->filename,ss->line, "lexical escape char");
			return 0;
		} else{
			tmp = Xhex2num(*ss->cur);
			ss->cur++;
		}
		if( Xhex2num(*ss->cur) == -1){
			return tmp;
		} else{
			tmp = tmp * 16 + Xhex2num(*ss->cur);
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
		if(Xstrncmp(start,"if",2)){
			return TokenAlloc(TKw_if);
		}
		if(Xstrncmp(start,"as",2)){
			return TokenAlloc(TKw_as);
		}
	    case 3 :
		if(Xstrncmp(start,"int",3)){
			return TokenAlloc(TKw_int);
		}
		if(Xstrncmp(start,"for",3)){
			return TokenAlloc(TKw_for);
		}
	    case 4 :
		if(Xstrncmp(start,"int8",4)){
			return TokenAlloc(TKw_int8);
		}
		if(Xstrncmp(start,"uint",4)){
			return TokenAlloc(TKw_uint);
		}
		if(Xstrncmp(start,"bool",4)){
			return TokenAlloc(TKw_bool);
		}
		if(Xstrncmp(start,"char",4)){
			return TokenAlloc(TKw_char);
		}
		if(Xstrncmp(start,"void",4)){
			return TokenAlloc(TKw_void);
		}
		if(Xstrncmp(start,"func",4)){
			return TokenAlloc(TKw_func);
		}
		if(Xstrncmp(start,"elif",4)){
			return TokenAlloc(TKw_elif);
		}
		if(Xstrncmp(start,"else",4)){
			return TokenAlloc(TKw_else);
		}
		if(Xstrncmp(start,"case",4)){
			return TokenAlloc(TKw_case);
		}
		if(Xstrncmp(start,"goto",4)){
			return TokenAlloc(TKw_goto);
		}
		if(Xstrncmp(start,"true",4)){
			ret = TokenAlloc(TokenBool);
			ret->iValue = 1;
			return ret;
		}
		if(Xstrncmp(start,"NULL",4)){
			return TokenAlloc(TokenNULL);
		}
	    case 5 :
		if(Xstrncmp(start,"int16",5)){
			return TokenAlloc(TKw_int16);
		}
		if(Xstrncmp(start,"int32",5)){
			return TokenAlloc(TKw_int32);
		}
		if(Xstrncmp(start,"int64",5)){
			return TokenAlloc(TKw_int64);
		}
		if(Xstrncmp(start,"uint8",5)){
			return TokenAlloc(TKw_uint8);
		}
		if(Xstrncmp(start,"float",5)){
			return TokenAlloc(TKw_float);
		}
		if(Xstrncmp(start,"union",5)){
			return TokenAlloc(TKw_union);
		}
		if(Xstrncmp(start,"while",5)){
			return TokenAlloc(TKw_while);
		}
		if(Xstrncmp(start,"break",5)){
			return TokenAlloc(TKw_break);
		}
		if(Xstrncmp(start,"throw",5)){
			return TokenAlloc(TKw_throw);
		}
		if(Xstrncmp(start,"const",5)){
			return TokenAlloc(TKw_const);
		}
		if(Xstrncmp(start,"false",5)){
			ret = TokenAlloc(TokenBool);
			ret->iValue = 0;
			return ret;
		}
	    case 6 :
		if(Xstrncmp(start,"import",6)){
			return TokenAlloc(TKw_import);
		}
		if(Xstrncmp(start,"uint16",6)){
			return TokenAlloc(TKw_uint16);
		}
		if(Xstrncmp(start,"uint32",6)){
			return TokenAlloc(TKw_uint32);
		}
		if(Xstrncmp(start,"uint64",6)){
			return TokenAlloc(TKw_uint64);
		}
		if(Xstrncmp(start,"struct",6)){
			return TokenAlloc(TKw_struct);
		}
		if(Xstrncmp(start,"switch",6)){
			return TokenAlloc(TKw_switch);
		}
		if(Xstrncmp(start,"return",6)){
			return TokenAlloc(TKw_return);
		}
	    case 7 :
		if(Xstrncmp(start,"package",7)){
			return TokenAlloc(TKw_package);
		}
		if(Xstrncmp(start,"float32",7)){
			return TokenAlloc(TKw_float32);
		}
		if(Xstrncmp(start,"float64",7)){
			return TokenAlloc(TKw_float64);
		}
		if(Xstrncmp(start,"typedef",7)){
			return TokenAlloc(TKw_typedef);
		}
		if(Xstrncmp(start,"default",7)){
			return TokenAlloc(TKw_default);
		}
	    case 8 :
		if(Xstrncmp(start,"continue",8)){
			return TokenAlloc(TKw_continue);
		}
	}

	ret = TokenAlloc(TokenID);
	ret->sValue= StoreString(start, ss->cur - start);
	return ret;
}

Token* _scanNumberLiteral(ScanState* ss){
	Token* ret = TokenAlloc(TokenInteger);
	ret->iValue=0;

	while( *ss->cur >='0' && *ss->cur <= '9'){
		ret->iValue= ret->iValue * 10 + *ss->cur - '0';
		ss->cur++;
	}
	return ret;
}

Token* _scanCharLiteral(ScanState* ss){
	Token* ret =TokenAlloc(TokenChar);

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
	Token* ret= TokenAlloc(TokenString);

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
		return TokenAlloc(*ss->cur++);
	    case '.' :
		ss->cur++;
		if(_exceptChar(ss, '.')){
			if(_exceptChar(ss, '.')){
				return TokenAlloc(Token3dot);
			}
			Error(ss->filename, ss->line, "illegal character ..");
			return TokenAlloc(TOp_dot);
		}
		return TokenAlloc(TOp_dot);
	    case '+' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_addAssign);
		}
		return TokenAlloc(TOp_add);
	    case '-' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_subAssign);
		}
		if(_exceptChar(ss, '>')){
			return TokenAlloc(TOp_ra);
		}
		return TokenAlloc(TOp_sub);
	    case '*' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_mulAssign);
		}
		return TokenAlloc(TOp_star);
	    case '/' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_divAssign);
		}
		if(_exceptChar(ss, '/')){  // skip line comment.
			while(*ss->cur && *ss->cur != '\n'){
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
					goto repeat;
				}
			}
			ss->cur += 2;
			goto repeat;
		}
		return TokenAlloc(TOp_div);
	    case '%' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_remAssign);
		}
		return TokenAlloc(TOp_rem);
	    case '!' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_notEq);
		}
		return TokenAlloc(TOp_not);
	    case '&' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_andAssign);
		}
		if(_exceptChar(ss, '&')){
			return TokenAlloc(TOp_andAnd);
		}
		return TokenAlloc(TOp_and);
	    case '=' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_eq);
		}
		return TokenAlloc(TOp_assign);
	    case '|' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_orAssign);
		}
		if(_exceptChar(ss, '|')){
			return TokenAlloc(TOp_orOr);
		}
		return TokenAlloc(TOp_or);
	    case '~' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_negAssign);
		}
		return TokenAlloc(TOp_neg);
	    case '>' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_ge);
		}
		if(_exceptChar(ss, '>')){
			if(_exceptChar(ss, '=')){
				return TokenAlloc(TOp_shrAssign);
			}
			return TokenAlloc(TOp_shr);
		}
		return TokenAlloc(TOp_gt);
	    case '<' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(TOp_le);
		}
		if(_exceptChar(ss, '<')){
			if(_exceptChar(ss, '=')){
				return TokenAlloc(TOp_shlAssign);
			}
			return TokenAlloc(TOp_shl);
		}
		return TokenAlloc(TOp_lt);
	    case '\'':
		return _scanCharLiteral(ss);
	    case '"' :
		return _scanStringLiteral(ss);
	    case '\0':
		return TokenAlloc(TokenEnd);
	    default:
		Error(ss->filename, ss->line, "illegal character \\%d(%c)",*ss->cur, *ss->cur);
		ss->cur++;
		goto repeat;
	}
}

Token* ScanFile(char* filename){
	ScanState ss;
	Token* tokenHead = TokenAlloc(TokenStart);
	Token* tokenTail = tokenHead;

	ss.filename = filename;
	ss.buf = LoadFile(filename);
	ss.cur = ss.buf;
	ss.line = 1;

	while(tokenTail->tCode != TokenEnd){
		tokenTail->tNext = _lexical(&ss);
		tokenTail = tokenTail->tNext;
		tokenTail->tLine = ss.line;
	}

	if(1){
		printf("\n Token Dump in file: %s\n",filename);
		for(tokenTail=tokenHead; tokenTail; tokenTail=tokenTail->tNext){
			TokenDump(tokenTail);
		}
	}

	return tokenHead;
}