/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _GERM_H
#define _GERM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// some basic types in germ.
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

#define true  1;
#define false 0;
#define null  NULL;

#include "routine.h"
#include "symbol.h"
#include "xstring.h"
#include "buffer.h"
#include "scanner.h"
#include "declare.h"

#endif