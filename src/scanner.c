/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

const int FB_GROWSIZE = 1024;

typedef struct _buffer{
	int     nalloc;
	int     nchars;
	char*   data;
} Buffer;

void _insertCharToBuffer(Buffer* buf, char ch){
	char* tmp;
	if(buf->nchars+1 >= buf->nalloc){
		tmp = xmalloc(buf->nalloc + FB_GROWSIZE);
		if(buf->data){
			xmemcpy(tmp, buf->data, buf->nchars);
			xfree(buf->data);
		}
		buf->nalloc = buf->nalloc + FB_GROWSIZE;
		buf->data = tmp;
	}
	buf->data[buf->nchars++] = ch;
}

char* _loadFile(char* filename){
	int  ch;

	Buffer buf = {0, 0, NULL};
	FILE* file = xfopen(filename, "r");

	for(ch=fgetc(file); ch != EOF; ch=fgetc(file)){
		_insertCharToBuffer(&buf,(char)ch);
	}
	// Append '\n','\0' to the file end, make lexcier easier.
	_insertCharToBuffer(&buf,'\n');
	_insertCharToBuffer(&buf,'\0');

	xfclose(file);

	return buf.data;
}

typedef struct _scanState{
	char* filename;
	char* buf;
	char* cur;
	int   line;
} ScanState;

static Token* _newToken(int tokencode){
	Token* ret = xmalloc(sizeof(Token));
	ret->tCode = tokencode;
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

bool _exceptChar(ScanState* ss, char ch){
	if(*ss->cur == ch ){
		ss->cur++;
		return true;
	}
	return false;
}

Token* lexical(ScanState* ss){
	char* start;
	Token* ret;

    repeat:
	if(isId(*ss->cur)){
		start = ss->cur;
		ret = _newToken(TokenID);
		while(isId2(*ss->cur)){
			ss->cur++;
		}
		ret->tValue.s=storeString(start, ss->cur - start);
		if( ret->tValue.s->symbol){
			if(ret->tValue.s->symbol->sType == ST_KeyWord){
				ret->tCode = ret->tValue.s->symbol->sValue.i;
				return ret;
			}
			if(ret->tValue.s->symbol->sType == ST_ResWord){
				switch(ret->tValue.s->symbol->sValue.i){
				    case TRw_true:
					ret->tCode = TokenBool;
					ret->tValue.i = 1;
					return ret;
				    case TRw_false:
					ret->tCode = TokenBool;
					ret->tValue.i = 0;
					return ret;
				    case TRw_NULL:
					ret->tCode = TokenNULL;
					return ret;
				    //case TRw___FILE__:
					//ret->tCode = TokenString;
					//ret->tValue.s=storeString(buf->filename, xstrlen(buf->filename));
					//return ret;
				    //case TRw___LINE__:
					//ret->tCode = TokenInteger;
					//ret->tValue.i = *line;
					//return ret;
				    case TRw___DATA__:
					ret->tCode = TokenString;
					ret->tValue.s=storeString("2017-11-11",10);
					return ret;
				    case TRw___TIME__:
					ret->tCode = TokenInteger;
					ret->tValue.i=115;
					return ret;
				    default:
					printf("Fatal: ResWord not deal");
				}
			}
		}
		return ret;
	}

	if(isNumber(*ss->cur)){
		ret = _newToken(TokenInteger);
		ret->tValue.i= *ss->cur - '0';
		ss->cur++;
		while(isNumber2(*ss->cur)){
			ret->tValue.i = ret->tValue.i * 10 + *ss->cur - '0';
			ss->cur++;
		}
		return ret;
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
				return _newToken(TOp_3dot);
			}
			return _newToken(TOp_2dot);
		}
		return _newToken(TOp_dot);
	    case '+' :
		ss->cur++;
		if(_exceptChar(ss, '+')){
			return _newToken(TOp_inc);
		}
		if(_exceptChar(ss, '=')){
			return _newToken(TOp_addAssign);
		}
		return _newToken(TOp_add);
	    case '-' :
		ss->cur++;
		if(_exceptChar(ss, '-')){
			return _newToken(TOp_dec);
		}
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
		if(_exceptChar(ss, '/')){		// skip line comment.
			while(*ss->cur != '\n'){
				ss->cur++;
			}
			goto repeat;
		}
		if(_exceptChar(ss, '*')){	// skip multline comment.
			do{
				if(!*ss->cur){
					printf("Error: lexical multline comment not close");
					return NULL;
				}
				if( *ss->cur == '\n'){
					ss->line++;
				}
				ss->cur++;
			}while(!(*ss->cur == '*' && *(ss->cur+1) == '/'));
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
			return _newToken(TOp_gtEq);
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
			return _newToken(TOp_ltEq);
		}
		if(_exceptChar(ss, '<')){
			if(_exceptChar(ss, '=')){
				return _newToken(TOp_shlAssign);
			}
			return _newToken(TOp_shl);
		}
		return _newToken(TOp_lt);
	    case '\'':
		ss->cur++;
		ret =_newToken(TokenChar);
		if(_exceptChar(ss, '\'')){
			printf("Error: Not have availbe char");
			ret->tValue.i= 0 ; // 空字符就设置成0.
			return ret;
		}
		if(_exceptChar(ss, '\\')){
			//ret->tValue.i=escapeChar(&p);
		}else{
			ret->tValue.i = *ss->cur++;
		}

		if(_exceptChar(ss, '\'')){
			return ret;
		}else{
			printf("Error: have more chars in char:%c\n", *ss->cur);
			// skip the more chars.
			while(*ss->cur != '\''){
				ss->cur++;
			}
			ss->cur++;
			return ret;
		}
	    case '"' :
		ret = _newToken(TokenString);
		ret->tValue.s=scanStringLiteral(&ss->cur);
		return ret;
	    case '\0':
		return NULL;
	    default:
		printf("Error: lexical can't recognize char:%d(%c)\n", *ss->cur, *ss->cur);
		ss->cur++;
		goto repeat;
	}
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

void _dumpTokenVector(Vector* tokenVector){
	Token* token;
	int i;
	for(i=0; i<tokenVector->item;i++){
		token = tokenVector->data[i];
		printToken(token);
	}
}

Vector* ScanFile(char* filename){
	ScanState ss;
	Token* token;
	Vector* tokenVector = xmalloc(sizeof(Vector));

	ss.filename = filename;
	ss.buf = _loadFile(filename);
	ss.cur = ss.buf;
	ss.line = 1;

	while(true){
		token = lexical(&ss);
		if( !token){
			break;
		}
		token->tPosFile = filename;
		token->tPosLine = ss.line;
		pushToVector(tokenVector, token);
	}
	_dumpTokenVector(tokenVector);
	return tokenVector;
}