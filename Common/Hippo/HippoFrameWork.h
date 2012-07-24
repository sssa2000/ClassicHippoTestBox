/********************************************************************
	created:	2011/10/19
	created:	19:10:2011   0:45
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\HippoFrameWork.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork
	file base:	HippoFrameWork
	file ext:	h
	author:		sssa2000
	
	purpose:	
*********************************************************************/
#pragma once
#include <Windows.h>


enum CONSOLE_COLOR
{
	CC_RED,
	CC_GREEN,
	CC_BLUE,
	CC_WHITE
};

namespace H3DI
{
	class IRender;
}
class Hippo_InputManager;

typedef int    (*CALLBACK_FRAMEUPDATE)(DWORD fElapsedTimeInMs, void* pUserContext );
typedef LRESULT (*CALLBACK_MSGPROC)( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, void* pUserContext );
typedef int    (*CALLBACK_KEYBOARD)( UINT nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext );
typedef int    (*CALLBACK_MOUSE)( bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down,
 int nMouseWheelDelta, int xPos, int yPos, void* pUserContext );
typedef int	(*CALLBACK_ONSIZE)(int w,int h);


int Hippo_SetMsgProcCallback(CALLBACK_MSGPROC p);
int Hippo_SetKeyboardCallback(CALLBACK_KEYBOARD p );
int Hippo_SetFrameUpdateCallback(CALLBACK_FRAMEUPDATE p );
int Hippo_SetMouseCallback(CALLBACK_MOUSE p);
int Hippo_InitFrameWork();
int Hippo_CreateWindow(const char* wnd_title,HMENU hMenu,HINSTANCE hInstance,int x,int y,int w,int h);
int Hippo_MainLoop(); 
int Hippo_RunFrame();
void Hippo_WriteConsole(CONSOLE_COLOR color,char *szstr,... );
int Hippo_InitIRender();

LRESULT CALLBACK Hippo_StaticWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

//!绘制地面网格
int Hippo_DrawHelpGrid();

//!some get fun
H3DI::IRender* Hippo_GetIRender();
Hippo_InputManager* GetInputManager();