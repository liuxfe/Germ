/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_MAIN_H
#define _ToHack_CL_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

typedef   signed char   int8;
typedef   signed short  int16;
typedef   signed int    int32;
typedef   signed long   int64;
typedef   signed long   INT;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned long  uint64;
typedef unsigned long  UINT;
typedef void*          uptr;
typedef float          float32;
typedef double         float64;
typedef double         FLOAT;
typedef char           bool;
typedef   signed int   CHAR;

#define true  1
#define false 0

#include "error.h"
#include "xroutine.h"
#include "vector.h"
#include "string.h"

#include "input.h"
#include "token.h"
#include "scanner.h"
#include "parser.h"

#endif