/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_DECLARE_H
#define _ToHack_CL_DECLARE_H

Symbol* ParseExternalDeclare(ParseState*);
void ParseInternalDeclare(ParseState*, Dtype*, Vector*);

#endif