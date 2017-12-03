/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include <stdarg.h>
#include "germ.h"

static
void _error(char* label, char* file, int line, char* fmt, va_list ap){
	fprintf(stderr, "[%s:%s:%d] ",label, file, line);
	vfprintf(stderr, fmt, ap);
}

int NoticeCnt;
int WarningCnt;
int ErrorCnt;

void Notice(char* file, int line, char* fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	_error("Notice", file, line, fmt, ap);
	NoticeCnt++;
}

void Warning(char* file, int line, char* fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	_error("Warning", file, line, fmt, ap);
	WarningCnt++;
}

void Error(char* file, int line, char* fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	_error("Error", file, line, fmt, ap);
	ErrorCnt++;
}

void Debug(char* file, int line, char* fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	_error("Debug", file, line, fmt, ap);
}

void Fatal(char* file, int line, char* fmt, ...){
	va_list ap;

	va_start(ap,fmt);
	_error("Fatal", file, line, fmt, ap);
	exit(-1);
}