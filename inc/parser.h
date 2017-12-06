/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_PARSER_H
#define _ToHack_CL_PARSER_H

typedef struct _parseState{
	char*    filename;
	Token*   tokenList;
} ParseState;

void eatToken(ParseState*);
bool exceptToken(ParseState*, int);

#include "declare.h"
#include "symbol.h"
#include "expression.h"
#include "statement.h"

void ParseFile(char* filename);

#endif