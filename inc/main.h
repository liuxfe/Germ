/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_MAIN_H
#define _ToHack_CL_MAIN_H

#include <stdio.h>
#include <stdlib.h>

typedef   signed char   int8;
typedef unsigned char  uint8;
typedef   signed short  int16;
typedef unsigned short uint16;
typedef   signed int    int32;
typedef unsigned int   uint32;
typedef   signed long   int64;
typedef unsigned long  uint64;
typedef unsigned int   uint;

typedef char bool;

#define true  1
#define false 0

#include "error.h"
#include "xroutine.h"
#include "vector.h"
#include "string.h"

#include "input.h"
#include "scanner.h"
#include "parser.h"

extern int wantDumpTokenVector;

#endif