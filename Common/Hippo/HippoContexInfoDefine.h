/********************************************************************
	created:	2011/12/23
	created:	23:12:2011   0:16
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\HippoContexInfoDefine.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork
	file base:	HippoContexInfoDefine
	file ext:	h
	author:		sssa2000
	
	purpose:	定义保存运行contex信息的数据
*********************************************************************/
#pragma once

typedef int    (*CALLBACK_FRAMEUPDATE)(DWORD fElapsedTimeInMs, void* pUserContext );
typedef LRESULT (*CALLBACK_MSGPROC)( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, void* pUserContext );
typedef int    (*CALLBACK_KEYBOARD)( UINT nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext );
typedef int    (*CALLBACK_MOUSE)( bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down,
								 int nMouseWheelDelta, int xPos, int yPos, void* pUserContext );
typedef int	(*CALLBACK_ONSIZE)(int w,int h);

class HippoContexInfo
{
public:
	HippoContexInfo()
	{
		m_pMsgProcCallback=0;
		m_pKeyBoardCallback=0;
		m_pMouseCallback=0;
		m_pFrameUpdateCallback=0;
		m_WndWidth=800;
		m_WndHeight=600;
	}

	CALLBACK_MSGPROC m_pMsgProcCallback;
	CALLBACK_KEYBOARD m_pKeyBoardCallback;
	CALLBACK_MOUSE m_pMouseCallback;
	CALLBACK_FRAMEUPDATE m_pFrameUpdateCallback;
	HWND m_hwnd;
	HINSTANCE m_hInstance;
	//console窗口
	HANDLE m_console_handle;
	//bool    m_Keys[256];                                // array of key state
	//bool    m_LastKeys[256];                            // array of last key state
	//bool    m_MouseButtons[5];                          // array of mouse states
	void* m_FrameUpdateUserContext;                // user context for frame move callback
	void* m_KeyboardUserContext;                 // user context for keyboard callback
	void* m_MouseUserContext;                    // user context for mouse callback
	void* m_MsgProcUserContext;                // user context for window messages callback
	int m_WndWidth;
	int m_WndHeight;
	CALLBACK_MSGPROC GetMsgProcFunc(){return m_pMsgProcCallback;}
	CALLBACK_KEYBOARD GetKeyboardFunc(){return m_pKeyBoardCallback;}
	CALLBACK_MOUSE GetMouseFunc(){return m_pMouseCallback;}
	CALLBACK_FRAMEUPDATE GetFrameUpdateFunc(){return m_pFrameUpdateCallback;}

	void* GetFrameUpdateUserContex(){return m_FrameUpdateUserContext;}
	void* GetKeyBoardUserContex(){return m_KeyboardUserContext;}
	void* GetMouseUserContex(){return m_MouseUserContext;}
	void* GetMsgProcUserContex(){return m_MsgProcUserContext;}

	//bool* GetKeys(){return m_Keys;}
};
