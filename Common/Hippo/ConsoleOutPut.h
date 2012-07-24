/********************************************************************
	created:	2012/07/22
	created:	22:7:2012   15:49
	filename: 	F:\EngineX52MT\多线程测试用例代码\Common\Hippo\ConsoleOutPut.h
	file path:	F:\EngineX52MT\多线程测试用例代码\Common\Hippo
	file base:	ConsoleOutPut
	file ext:	h
	author:		sssa2000
	
	purpose:	
*********************************************************************/
#pragma once
#include <iostream>
#include <windows.h>

static void* g_console_handle=0;

enum CONSOLE_COLOR
{
	CC_RED,
	CC_GREEN,
	CC_BLUE,
	CC_WHITE
};


inline void HippoInitConsole()
{
	::AllocConsole();
	g_console_handle=::GetStdHandle(STD_OUTPUT_HANDLE);
}

inline void HippoDeleteConsole()
{
	::FreeConsole();
	g_console_handle = 0;
}
inline WORD MakeColor(CONSOLE_COLOR color)
{
	WORD res=0;
	if (color==CC_RED)
	{
		res=FOREGROUND_RED|FOREGROUND_INTENSITY;
	}
	else if (color==CC_GREEN)
	{
		res=FOREGROUND_GREEN|FOREGROUND_INTENSITY;
	}
	else if (color==CC_BLUE)
	{
		res=FOREGROUND_BLUE|FOREGROUND_INTENSITY;
	}
	else if (color==CC_WHITE)
	{
		res=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY;
	}
	return res;
}
inline void HippoWriteToConsole(CONSOLE_COLOR color,const char* str,...)
{
	static char szParsedString[1024];
	va_list va;
	va_start( va, str );
	vsprintf( szParsedString, str, va );
	va_end( va );

	SetConsoleTextAttribute(g_console_handle, MakeColor(color));

	DWORD numWrite;
	::WriteConsoleA(g_console_handle,szParsedString,(DWORD)strlen(szParsedString),&numWrite,0);
}

inline std::ostream& console_blue(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
		|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& console_red(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_RED|FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& console_green(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	return s;
}