/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"
#include "input.h"

typedef struct _scanState{
	char* filename;
	char* buf;
	char* cur;
	int   line;
} scanState;

bool _exceptChar(scanState* ss, char ch){
	if(*ss->cur == ch ){
		ss->cur++;
		return true;
	}
	return false;
}

uint _escapeChar(scanState* ss){
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
	    case 'x' :ss->cur++;
		if(!Xishex(*ss->cur)){
			Error(ss->filename,ss->line, "lexical escape char");
			return 0;
		} else {
			tmp = Xhex2num(*ss->cur);
			ss->cur++;
		}
		if(!Xishex(*ss->cur)){
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

Token* _scanId(scanState* ss){
	Token* ret;
	char* start = ss->cur;

	while((*ss->cur >= 'a' && *ss->cur <= 'z') ||
	      (*ss->cur >= 'A' && *ss->cur <= 'Z') ||
	      (*ss->cur >= '0' && *ss->cur <= '9') ||
	       *ss->cur =='_' ){
		ss->cur++;
	}

	switch(ss->cur - start){
	    case 2 :
		if(Xstrncmp(start,"if",2)){
			return TokenAlloc(Token_if);
		}
	    case 3 :
		if(Xstrncmp(start,"int",3)){
			return TokenAlloc(Token_int);
		}
		if(Xstrncmp(start,"for",3)){
			return TokenAlloc(Token_for);
		}
	    case 4 :
		if(Xstrncmp(start,"int8",4)){
			return TokenAlloc(Token_int8);
		}
		if(Xstrncmp(start,"uint",4)){
			return TokenAlloc(Token_uint);
		}
		if(Xstrncmp(start,"bool",4)){
			return TokenAlloc(Token_bool);
		}
		if(Xstrncmp(start,"char",4)){
			return TokenAlloc(Token_char);
		}
		if(Xstrncmp(start,"func",4)){
			return TokenAlloc(Token_func);
		}
		if(Xstrncmp(start,"elif",4)){
			return TokenAlloc(Token_elif);
		}
		if(Xstrncmp(start,"else",4)){
			return TokenAlloc(Token_else);
		}
		if(Xstrncmp(start,"case",4)){
			return TokenAlloc(Token_case);
		}
		if(Xstrncmp(start,"goto",4)){
			return TokenAlloc(Token_goto);
		}
		if(Xstrncmp(start,"true",4)){
			ret = TokenAlloc(Token_Bool);
			ret->iValue = 1;
			return ret;
		}
		if(Xstrncmp(start,"NULL",4)){
			return TokenAlloc(Token_NULL);
		}
	    case 5 :
		if(Xstrncmp(start,"int16",5)){
			return TokenAlloc(Token_int16);
		}
		if(Xstrncmp(start,"int32",5)){
			return TokenAlloc(Token_int32);
		}
		if(Xstrncmp(start,"int64",5)){
			return TokenAlloc(Token_int64);
		}
		if(Xstrncmp(start,"uint8",5)){
			return TokenAlloc(Token_uint8);
		}
		if(Xstrncmp(start,"float",5)){
			return TokenAlloc(Token_float);
		}
		if(Xstrncmp(start,"union",5)){
			return TokenAlloc(Token_union);
		}
		if(Xstrncmp(start,"while",5)){
			return TokenAlloc(Token_while);
		}
		if(Xstrncmp(start,"break",5)){
			return TokenAlloc(Token_break);
		}
		if(Xstrncmp(start,"throw",5)){
			return TokenAlloc(Token_throw);
		}
		if(Xstrncmp(start,"false",5)){
			ret = TokenAlloc(Token_Bool);
			ret->iValue = 0;
			return ret;
		}
	    case 6 :
		if(Xstrncmp(start,"import",6)){
			return TokenAlloc(Token_import);
		}
		if(Xstrncmp(start,"uint16",6)){
			return TokenAlloc(Token_uint16);
		}
		if(Xstrncmp(start,"uint32",6)){
			return TokenAlloc(Token_uint32);
		}
		if(Xstrncmp(start,"uint64",6)){
			return TokenAlloc(Token_uint64);
		}
		if(Xstrncmp(start,"struct",6)){
			return TokenAlloc(Token_struct);
		}
		if(Xstrncmp(start,"switch",6)){
			return TokenAlloc(Token_switch);
		}
		if(Xstrncmp(start,"return",6)){
			return TokenAlloc(Token_return);
		}
	    case 7 :
		if(Xstrncmp(start,"package",7)){
			return TokenAlloc(Token_package);
		}
		if(Xstrncmp(start,"float32",7)){
			return TokenAlloc(Token_float32);
		}
		if(Xstrncmp(start,"float64",7)){
			return TokenAlloc(Token_float64);
		}
		if(Xstrncmp(start,"typedef",7)){
			return TokenAlloc(Token_typedef);
		}
		if(Xstrncmp(start,"default",7)){
			return TokenAlloc(Token_default);
		}
	    case 8 :
		if(Xstrncmp(start,"continue",8)){
			return TokenAlloc(Token_continue);
		}
	}

	ret = TokenAlloc(Token_ID);
	ret->sValue = StoreString(start, ss->cur - start);
	return ret;
}

Token* _scanNumberLiteral(scanState* ss){
	Token* ret = TokenAlloc(Token_Integer);
	ret->iValue = 0;

	while( *ss->cur >='0' && *ss->cur <= '9'){
		ret->iValue= ret->iValue * 10 + *ss->cur - '0';
		ss->cur++;
	}
	return ret;
}

Token* _scanCharLiteral(scanState* ss){
	Token* ret =TokenAlloc(Token_Char);

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

Token* _scanStringLiteral(scanState* ss){
	char* start;
	char* tail;
	Token* ret= TokenAlloc(Token_String);

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

Token* _scanLexical(scanState* ss){
    repeat:
	if( (*ss->cur >= 'a' && *ss->cur <= 'z') ||
	    (*ss->cur >= 'A' && *ss->cur <= 'Z') ||
	     *ss->cur == '_' ){
		return _scanId(ss);
	}

	if(*ss->cur >='0' && *ss->cur <= '9'){
		return _scanNumberLiteral(ss);
	}

	switch(*ss->cur){
	    case '\n':
		ss->line++;
	    case ' ' : case '\t' : case '\r' :
		ss->cur++; goto repeat;
	    case '{' : ss->cur++; return TokenAlloc(Token_lbrace);
	    case '}' : ss->cur++; return TokenAlloc(Token_rbrace);
	    case '[' : ss->cur++; return TokenAlloc(Token_lbracket);
	    case ']' : ss->cur++; return TokenAlloc(Token_rbracket);
	    case '(' : ss->cur++; return TokenAlloc(Token_lparen);
	    case ')' : ss->cur++; return TokenAlloc(Token_rparen);
	    case ';' : ss->cur++; return TokenAlloc(Token_semicon);
	    case ':' : ss->cur++; return TokenAlloc(Token_colon);
	    case ',' : ss->cur++; return TokenAlloc(Token_comma);
	    case '.' :
		ss->cur++;
		if(_exceptChar(ss, '.')){
			if(_exceptChar(ss, '.')){
				return TokenAlloc(Token_3dot);
			}
			Error(ss->filename, ss->line, "illegal character ..");
			return TokenAlloc(Token_dot);
		}
		return TokenAlloc(Token_dot);
	    case '+' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_addAssign);
		}
		return TokenAlloc(Token_add);
	    case '-' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_subAssign);
		}
		if(_exceptChar(ss, '>')){
			return TokenAlloc(Token_ra);
		}
		return TokenAlloc(Token_sub);
	    case '*' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_mulAssign);
		}
		return TokenAlloc(Token_star);
	    case '/' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_divAssign);
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
		return TokenAlloc(Token_div);
	    case '%' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_remAssign);
		}
		return TokenAlloc(Token_rem);
	    case '!' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_notEq);
		}
		return TokenAlloc(Token_not);
	    case '&' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_andAssign);
		}
		if(_exceptChar(ss, '&')){
			return TokenAlloc(Token_andAnd);
		}
		return TokenAlloc(Token_and);
	    case '=' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_eq);
		}
		return TokenAlloc(Token_assign);
	    case '|' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_orAssign);
		}
		if(_exceptChar(ss, '|')){
			return TokenAlloc(Token_orOr);
		}
		return TokenAlloc(Token_or);
	    case '~' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_negAssign);
		}
		return TokenAlloc(Token_neg);
	    case '>' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_ge);
		}
		if(_exceptChar(ss, '>')){
			if(_exceptChar(ss, '=')){
				return TokenAlloc(Token_shrAssign);
			}
			return TokenAlloc(Token_shr);
		}
		return TokenAlloc(Token_gt);
	    case '<' :
		ss->cur++;
		if(_exceptChar(ss, '=')){
			return TokenAlloc(Token_le);
		}
		if(_exceptChar(ss, '<')){
			if(_exceptChar(ss, '=')){
				return TokenAlloc(Token_shlAssign);
			}
			return TokenAlloc(Token_shl);
		}
		return TokenAlloc(Token_lt);
	    case '\'':
		return _scanCharLiteral(ss);
	    case '"' :
		return _scanStringLiteral(ss);
	    case '\0':
		return TokenAlloc(Token_EOF);
	    default:
		Error(ss->filename, ss->line, "illegal character \\%d(%c)",*ss->cur, *ss->cur);
		ss->cur++;
		goto repeat;
	}
}

Token* ScanFile(char* filename){
	scanState ss;
	Token tokenHead;
	Token* tokenTail = &tokenHead;

	ss.filename = filename;
	ss.buf = LoadFile(filename);
	ss.cur = ss.buf;
	ss.line = 1;

	while(true){
		tokenTail->tNext = _scanLexical(&ss);
		tokenTail = tokenTail->tNext;
		tokenTail->tLine = ss.line;
		if(tokenTail->tCode == Token_EOF){
			break;
		}
	}

	if(0){
		printf("\n Token Dump in file: %s\n",filename);
		for(tokenTail=tokenHead.tNext; tokenTail; tokenTail=tokenTail->tNext){
			TokenDump(tokenTail);
		}
	}

	return tokenHead.tNext;
}