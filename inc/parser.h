/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_PARSER_H
#define _ToHack_CL_PARSER_H

typedef struct _parseState{
	char*    filename;
	Token*   tokenList;
	String*  continueLabel;
	String*  breakLabel;
} ParseState;

void eatToken(ParseState*);
bool exceptToken(ParseState*, int);
void ParseFatal(ParseState*, char*);
void exceptTokenDealError(ParseState*, int, char*);

#include "declare.h"
#include "symbol.h"
#include "expression.h"
#include "statement.h"

void ParseFile(char* filename);

#endif