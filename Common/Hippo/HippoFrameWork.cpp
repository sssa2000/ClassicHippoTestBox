#include "HippoFrameWork.h"
#include "resource.h"
#include "ErrReport.h"
#include "EngineBox.h"
#include "HelpeDraw.h"
#include "HippoContexInfoDefine.h"
#include "input/Hippo_InputManager.h"
#include "HippoScene.h"
#include "engine_interface.h"


HippoContexInfo* g_hippo_state=0;
EngineBox* g_engine_box=0;
Hippo_InputManager* gInputManager=0;
HippoSceneManager* gSceneManager=0;
void Hippo_OnSize(int w,int h);

int Hippo_SetMsgProcCallback(CALLBACK_MSGPROC p)
{
	g_hippo_state->m_pMsgProcCallback=p;
	return 1;
}

int Hippo_SetKeyboardCallback(CALLBACK_KEYBOARD p )
{
	g_hippo_state->m_pKeyBoardCallback=p;
	return 1;
}

int Hippo_SetFrameUpdateCallback(CALLBACK_FRAMEUPDATE p )
{
	g_hippo_state->m_pFrameUpdateCallback=p;
	return 1;
}

int Hippo_SetMouseCallback(CALLBACK_MOUSE p)
{
	g_hippo_state->m_pMouseCallback=p;
	return 1;
}

int Hippo_InitFrameWork()
{
	if (!g_hippo_state)
	{
		g_hippo_state=new HippoContexInfo;
	}

	if (!gInputManager)
	{
		gInputManager=new Hippo_InputManager;
		gInputManager->Init();
	}


	::AllocConsole();
	g_hippo_state->m_console_handle=::GetStdHandle(STD_OUTPUT_HANDLE);
	return 1;
}

int Hippo_CreateWindow(const char* wnd_title,HMENU hMenu,HINSTANCE hInstance,int x,int y,int w,int h)
{

	// Register the windows class
	WNDCLASS wndClass;
	wndClass.style = CS_DBLCLKS;
	wndClass.lpfnWndProc = Hippo_StaticWndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon =LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HIPPO_FRAMEWORK));
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
	wndClass.hbrBackground =(HBRUSH)(COLOR_WINDOW+1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName ="HippoWindowClass";

	if( !RegisterClass( &wndClass ) )
	{
		DWORD dwError = GetLastError();
		HippoReportErrWithLastErr(dwError);
		return -1;
	}

	// Create the render window
	int nDefaultWidth = w;
	int nDefaultHeight = h;

	RECT rc;
	SetRect( &rc, 0, 0, nDefaultWidth, nDefaultHeight );
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, ( hMenu != NULL ) ? true : false );



	HWND hWnd = CreateWindow( "HippoWindowClass", wnd_title, WS_OVERLAPPEDWINDOW,
		x, y, ( rc.right - rc.left ), ( rc.bottom - rc.top ), 0,
		hMenu, hInstance, 0 );
	if( hWnd == NULL )
	{
		DWORD dwError = GetLastError();
		HippoReportErrWithLastErr(dwError);
		return -1;
	}
	g_hippo_state->m_hwnd=hWnd;
	g_hippo_state->m_hInstance=hInstance;
	g_hippo_state->m_WndWidth=w;
	g_hippo_state->m_WndHeight=h;
	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);
	return 1;
}

int Hippo_MainLoop()
{
	// Now we're ready to receive and process Windows messages.
	bool bGotMsg;
	MSG msg;
	msg.message = WM_NULL;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

	HACCEL hAccelTable = LoadAccelerators(g_hippo_state->m_hInstance, MAKEINTRESOURCE(IDC_HIPPO_FRAMEWORK));

	while( WM_QUIT != msg.message )
	{
		// Use PeekMessage() so we can use idle time to render the scene. 
		bGotMsg = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 );

		if( bGotMsg )
		{
			// Translate and dispatch the message
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			// Render a frame during idle time (no messages are waiting)
			Hippo_RunFrame();
		}
	}
	return 1;
}


LRESULT CALLBACK Hippo_StaticWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	int r=gInputManager->HandleMsg(g_hippo_state,hWnd,message,wParam,lParam);
	if (r==1)
	{
		return 1;
	}

	//以下是默认的消息处理
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		//lParam高16位是高，低16位是宽
		{
			int w=LOWORD(lParam);
			int h=HIWORD(lParam);
			Hippo_OnSize(w,h);
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int Hippo_RunFrame()
{
	CALLBACK_FRAMEUPDATE pCallbackFrameMove = g_hippo_state->GetFrameUpdateFunc();
	if(!pCallbackFrameMove)
		return -1;

	static DWORD thisframe=0;
	static DWORD lastframe=0;
	lastframe=thisframe;
	thisframe=GetTickCount();
	DWORD t=thisframe-lastframe;
	
	
	pCallbackFrameMove(t,g_hippo_state->GetFrameUpdateUserContex());
	gInputManager->ResetPerFrame();
	return 1;
}


int Hippo_InitIRender()
{
	if(!g_engine_box)
	{
		g_engine_box=new EngineBox;
		g_engine_box->Init(g_hippo_state->m_hwnd,g_hippo_state->m_WndWidth,g_hippo_state->m_WndHeight);
	}

	if(!gSceneManager)
	{
		gSceneManager=new HippoSceneManager;
	}
	return 1;
}


H3DI::IRender* Hippo_GetIRender()
{
	return g_engine_box->m_pRenderer;
}

ISpecialEffectManager* Hippo_GetSpeManager()
{
	return g_engine_box->m_pSpeManager;
}

Hippo_InputManager* GetInputManager()
{
	return gInputManager;
}

HippoSceneManager* Hippo_GetSceneManager()
{
	return gSceneManager;
}

//!绘制地面网格
int Hippo_DrawHelpGrid()
{
	HelpeDraw::DrawHelpGird(g_engine_box->m_pRenderer);
	return 1;
}

void Hippo_OnSize(int w,int h)
{
	if (g_engine_box)
	{
		Hippo_GetIRender()->ResizeWindowForEditor(w,h);
	}
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

void Hippo_WriteConsole(CONSOLE_COLOR color,char *szstr,... )
{
	DWORD numWritten = 0;
	static char szParsedString[1024];

	va_list va;
	va_start( va, szstr );
	vsprintf( szParsedString,szstr, va );
	va_end( va );

	SetConsoleTextAttribute(g_hippo_state->m_console_handle, MakeColor(color));

	WriteConsoleA(g_hippo_state->m_console_handle,szParsedString, (DWORD)strlen(szParsedString),&numWritten,0);
	WriteConsoleA(g_hippo_state->m_console_handle,"\n", 1,&numWritten,0);
}