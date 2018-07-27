#pragma once
#include <windows.h>
#include <string.h>
#include <stdio.h>
//#include "stdarg.h"

#define LOG_OUT //透過註解取消LOG
 
#define _STR(s)     #s
#define STR(s)      _STR(s)   

#define SHORT_FILE strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__



#ifdef LOG_OUT
static char _gTimeBuffer[20] = {0};
//static int _WirteLog(const char* format, ...);
//static char* _GetLogTime(); 

static int _WirteLog(const char* format, ...){
	FILE* fp = fopen("Log.log", "a+");
	if(fp == NULL){
		return -1;
	}
	va_list args;
	va_start (args, format);
	vfprintf (fp, format, args);
	va_end (args);

	fclose(fp);
	return 0;
}


static char* _GetLogTime(){
	SYSTEMTIME stLocal;
	GetLocalTime(&stLocal);
	sprintf(_gTimeBuffer,"%04d/%02d/%02d %02d:%02d:%02d", stLocal.wYear, stLocal.wMonth, stLocal.wDay, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
	return _gTimeBuffer;
}

#define LOG(format, ...) do{\
	_WirteLog("[%s][%s@%s(%d)] " format "\n", _GetLogTime(), \
	SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__ );}while(0)  

#else
#define LOG(format, ...)
#endif      
 
