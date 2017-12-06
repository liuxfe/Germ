/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_ERROR_H
#define _ToHack_CL_ERROR_H

extern int NoticeCnt;
extern int WarningCnt;
extern int ErrorCnt;

void Notice(char*, int, char*, ...);
void Warning(char*, int, char*, ...);
void Error(char*, int, char*, ...);
void Debug(char*, int, char*, ...);
void Fatal(char*, int, char*, ...);

#endif