#include "Hippo_InputManager.h"
#include "../Camera/CameraBase.h"
#include "../HippoContexInfoDefine.h"
#include "../HippoFrameWork.h"



Hippo_InputManager::Hippo_InputManager()
{
	
}

Hippo_InputManager::~Hippo_InputManager()
{

}

void Hippo_InputManager::Init()
{
	memset(m_Keys,0,256*sizeof(bool));
	memset(m_MouseButtons,0,5*sizeof(bool));
	m_cKeysDown=0;
	m_bMouseLButtonDown=false;
	m_bMouseMButtonDown=false;
	m_bMouseRButtonDown=false;
	m_LastLDrag_ScreenPosX=-1;
	m_LastLDrag_ScreenPosY=-1;
	m_LastRDrag_ScreenPosX=-1;
	m_LastRDrag_ScreenPosY=-1;
	m_MouseLeftDragDeltaX=-1;
	m_MouseLeftDragDeltaY=-1;
	m_MouseRightDragDeltaX=-1;
	m_MouseRightDragDeltaY=-1;
	m_nMouseWheelDelta=0;
	m_bLeftDraging=false;
	m_bRightDraging=false;
	m_LDragBeginPointX_Wnd=0;
	m_LDragBeginPointY_Wnd=0;
	m_LDragBeginPointX_Screen=0;
	m_LDragBeginPointY_Screen=0;

}

//!有的数据需要每帧都重置
void Hippo_InputManager::ResetPerFrame()
{
	m_nMouseWheelDelta=0;
	m_MouseLeftDragDeltaX=0;
	m_MouseLeftDragDeltaY=0;
	m_MouseRightDragDeltaX=0;
	m_MouseRightDragDeltaY=0;

}



//!消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
int Hippo_InputManager::HandleMsg(HippoContexInfo* pState,HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam )
{


	//处理自定义键盘消息
	int r1=ProcessKeyBoardMsg(pState,hWnd,uMsg,wParam,lParam);
	if (r1==1) //已处理不再希望进行默认的消息处理
	{
		return 1;
	}

	//处理自定义鼠标消息
	int r2=ProcessMouseMsg(pState,hWnd,uMsg,wParam,lParam);
	if (r2==1) //已处理不再希望进行默认的消息处理
	{
		return 1;
	}

	//处理自定义消息处理函数
	CALLBACK_MSGPROC pCallbackMsg=pState->GetMsgProcFunc();
	if (pCallbackMsg)
	{
		LRESULT r3=pCallbackMsg(hWnd,uMsg,wParam,lParam,pState->GetMsgProcUserContex());
		if (r3==1)
		{
			return 1;
		}
	}

	return 0;
}


//!处理键盘的消息。返回0表示没有处理希望用默认消息处理函数处理；返回1表示已经处理，不希望再经过默认的处理
int Hippo_InputManager::ProcessKeyBoardMsg(HippoContexInfo* pState,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{

	//无论有没有用户自定义的键盘回调，都记录键盘的情况
	CALLBACK_KEYBOARD pCallbackKeyboard = pState->GetKeyboardFunc();
	if( uMsg == WM_KEYDOWN ||
		uMsg == WM_SYSKEYDOWN ||
		uMsg == WM_KEYUP ||
		uMsg == WM_SYSKEYUP )
	{
		bool bKeyDown = ( uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN );
		bool bShiftDown=GetKeyState(VK_SHIFT)<0;
		bool bCtrlDown=GetKeyState(VK_CONTROL)<0;
		bool bAltDown=GetKeyState(VK_MENU)<0;

		//DWORD dwMask = ( 1 << 29 );
		//bool bAltDown = ( ( lParam & dwMask ) != 0 );

		m_Keys[ ( BYTE )( wParam & 0xFF ) ] = bKeyDown;

		if(pCallbackKeyboard)
			return pCallbackKeyboard( ( UINT )wParam, bKeyDown, bAltDown, bCtrlDown,bShiftDown,pState->GetKeyBoardUserContex() );
	}
	//如果运行到这里证明没有用户自定义的回调函数，应该返回0
	return 0;
}

//!处理鼠标的消息。返回0表示没有处理希望用默认消息处理函数处理；返回1表示已经处理，不希望再经过默认的处理
int Hippo_InputManager::ProcessMouseMsg(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	int res=0;
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		res=OnMouseLeftKeyDown(pStage,hWnd,uMsg,wParam,lParam);
		break;
	case WM_LBUTTONUP:
		res=OnMouseLeftKeyUp(pStage,hWnd,uMsg,wParam,lParam);
		break;
	case WM_MBUTTONDOWN:
		res=OnMouseMiddleKeyDown(pStage,hWnd,uMsg,wParam,lParam);
		break;
	case WM_MBUTTONUP:
		res=OnMouseMiddleKeyUp(pStage,hWnd,uMsg,wParam,lParam);
		break;
	case WM_RBUTTONDOWN:
		res=OnMouseRightKeyDown(pStage,hWnd,uMsg,wParam,lParam);
		break;
	case WM_RBUTTONUP:
		res=OnMouseRightKeyUp(pStage,hWnd,uMsg,wParam,lParam);
		break;
	case WM_MOUSEWHEEL:
		res=OnMouseWheel(pStage,hWnd,uMsg,wParam,lParam);
		break;
	case WM_MOUSEMOVE:
		res=OnMouseMove(pStage,hWnd,uMsg,wParam,lParam);
		break;
	default:
		res=0;
	}
	//如果有自定义鼠标消息处理，把消息转发给它
	CALLBACK_MOUSE pCallbackMouse = pStage->GetMouseFunc();
	if(pCallbackMouse)
		return pCallbackMouse(m_bMouseLButtonDown,m_bMouseRButtonDown,m_bMouseMButtonDown,
								m_nMouseWheelDelta,false,false,m_MousePosX_Wnd,m_MousePosY_Wnd,pStage->GetMouseUserContex());
	//如果运行到这里证明没有用户自定义的回调函数，应该返回0
	return 0;


}


//!是否按下了某个按键
bool Hippo_InputManager::IsKeyDown(int key)
{
	return m_Keys[key];
}

//!获取鼠标左键按下时窗口坐标下的位置
void Hippo_InputManager::GetMouseLKeyDownPos_Wnd(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MousePosX_LeftKeyDown_Wnd;
	*outDeltaY=m_MousePosY_LeftKeyDown_Wnd;
}

//!获取鼠标左键按下时屏幕坐标下的位置
void Hippo_InputManager::GetMouseLKeyDownPos_Screen(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MousePosX_LeftKeyDown_Screen;
	*outDeltaY=m_MousePosY_LeftKeyDown_Screen;

}

//!获取当前鼠标的位置，窗口坐标系下
void Hippo_InputManager::GetCurrentMousePos_Wnd(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MousePosX_Wnd;
	*outDeltaY=m_MousePosY_Wnd;

}
//!获取鼠标滚轮滚动的距离
int Hippo_InputManager::GetWheelDelta()
{
	int res=m_nMouseWheelDelta;
	//m_nMouseWheelDelta=0;
	return res;
}

//!得到是否正在左键拖拽
bool Hippo_InputManager::IsLeftKeyDraging()
{
	return m_bLeftDraging;
}

//!得到是否正在右键拖拽
bool Hippo_InputManager::IsRightKeyDraging()
{
	return m_bRightDraging;
}

int Hippo_InputManager::OnMouseLeftKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_bMouseLButtonDown=true;

	//记录鼠标左键按下的位置（窗口坐标系下）
	m_MousePosX_LeftKeyDown_Wnd=( int )LOWORD( lParam );
	m_MousePosY_LeftKeyDown_Wnd=( int )HIWORD( lParam );

	m_MousePosX_Wnd=m_MousePosX_LeftKeyDown_Wnd;
	m_MousePosY_Wnd=m_MousePosY_LeftKeyDown_Wnd;
	
	//记录鼠标左键按下的位置（屏幕坐标系下）
	SetCapture( hWnd );
	POINT ptCurMousePos;
	GetCursorPos( &ptCurMousePos );
	m_MousePosX_LeftKeyDown_Screen=ptCurMousePos.x;
	m_MousePosY_LeftKeyDown_Screen=ptCurMousePos.y;

	m_LastLDrag_ScreenPosX=ptCurMousePos.x;
	m_LastLDrag_ScreenPosY=ptCurMousePos.y;

	m_LDragBeginPointX_Wnd=m_MousePosX_Wnd;
	m_LDragBeginPointY_Wnd=m_MousePosY_Wnd;
	m_LDragBeginPointX_Screen=ptCurMousePos.x;
	m_LDragBeginPointY_Screen=ptCurMousePos.y;
	return 1;
}
int Hippo_InputManager::OnMouseLeftKeyUp(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_bMouseLButtonDown=false;
	m_bLeftDraging=false;

	m_MousePosX_Wnd=( int )LOWORD( lParam );
	m_MousePosY_Wnd=( int )HIWORD( lParam );
	m_LDragBeginPointX_Wnd=0;
	m_LDragBeginPointY_Wnd=0;
	m_LDragBeginPointX_Screen=0;
	m_LDragBeginPointY_Screen=0;

	ReleaseCapture();
	return 1;
}
int Hippo_InputManager::OnMouseRightKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_bMouseRButtonDown=true;
	m_MousePosX_Wnd=( int )LOWORD( lParam );
	m_MousePosY_Wnd=( int )HIWORD( lParam );

	return 1;
}
int Hippo_InputManager::OnMouseRightKeyUp(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_bMouseRButtonDown=false;
	m_MousePosX_Wnd=( int )LOWORD( lParam );
	m_MousePosY_Wnd=( int )HIWORD( lParam );

	return 1;
}
int Hippo_InputManager::OnMouseMiddleKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_bMouseMButtonDown=true;
	m_MousePosX_Wnd=( int )LOWORD( lParam );
	m_MousePosY_Wnd=( int )HIWORD( lParam );

	return 1;
}
int Hippo_InputManager::OnMouseMiddleKeyUp(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_bMouseMButtonDown=false;
	m_MousePosX_Wnd=( int )LOWORD( lParam );
	m_MousePosY_Wnd=( int )HIWORD( lParam );

	return 1;
}
int Hippo_InputManager::OnMouseWheel(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_nMouseWheelDelta = 0;
	if( uMsg == WM_MOUSEWHEEL )
	{
		m_nMouseWheelDelta = ( short )HIWORD( wParam );

		// WM_MOUSEWHEEL passes screen mouse coords
		// so convert them to client coords

		//POINT pt;
		//pt.x = xPos; pt.y = yPos;
		//ScreenToClient( hWnd, &pt );
		//xPos = pt.x; yPos = pt.y;
	}
	return 1;
}

int Hippo_InputManager::OnMouseMove(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//记录拖拽
	m_bLeftDraging=m_bMouseLButtonDown;
	m_bRightDraging=m_bMouseRButtonDown;

	m_MousePosX_Wnd=( int )LOWORD( lParam );
	m_MousePosY_Wnd=( int )HIWORD( lParam );


	//处理左键拖拽和右键拖拽
	if (m_bLeftDraging)
	{
		SetCapture( hWnd );
		POINT ptCurMousePos;
		GetCursorPos( &ptCurMousePos );
		m_MouseLeftDragDeltaX=ptCurMousePos.x-m_LastLDrag_ScreenPosX;
		m_MouseLeftDragDeltaY=ptCurMousePos.y-m_LastLDrag_ScreenPosY;
		m_LastLDrag_ScreenPosX=ptCurMousePos.x;
		m_LastLDrag_ScreenPosY=ptCurMousePos.y;
		Hippo_WriteConsole(CC_GREEN,"m_MouseLeftDragDeltaX=%d,m_MouseLeftDragDeltaY=%d",m_MouseLeftDragDeltaX,m_MouseLeftDragDeltaY);

	}
	else if (m_bRightDraging)
	{
		SetCapture( hWnd );
		POINT ptCurMousePos;
		GetCursorPos( &ptCurMousePos );
		m_MouseRightDragDeltaX=ptCurMousePos.x-m_LastRDrag_ScreenPosX;
		m_MouseRightDragDeltaY=ptCurMousePos.y-m_LastRDrag_ScreenPosY;
		m_LastRDrag_ScreenPosX=ptCurMousePos.x;
		m_LastRDrag_ScreenPosY=ptCurMousePos.y;
	}
	return 1;
}

//!得到本帧鼠标左键拖拽移动的距离(屏幕空间)
int Hippo_InputManager::GetMouseLDragDelta(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MouseLeftDragDeltaX;
	*outDeltaY=m_MouseLeftDragDeltaY;
	return 1;
}
//!得到本帧鼠标右键拖拽移动的距离(屏幕空间)
int Hippo_InputManager::GetMouseRDragDelta(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MouseRightDragDeltaX;
	*outDeltaY=m_MouseRightDragDeltaY;

	return 1;
}

//!得到左键拖拽开始的鼠标位置
int Hippo_InputManager::GetLeftKeyDragingBeginPoint_Wnd(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_LDragBeginPointX_Wnd;
	*outDeltaY=m_LDragBeginPointY_Wnd;
	return 1;
}
int Hippo_InputManager::GetLeftKeyDragingBeginPoint_Screen(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_LDragBeginPointX_Screen;
	*outDeltaY=m_LDragBeginPointY_Screen;
	return 1;
}
