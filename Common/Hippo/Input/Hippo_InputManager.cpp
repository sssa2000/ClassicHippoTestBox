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

//!�е�������Ҫÿ֡������
void Hippo_InputManager::ResetPerFrame()
{
	m_nMouseWheelDelta=0;
	m_MouseLeftDragDeltaX=0;
	m_MouseLeftDragDeltaY=0;
	m_MouseRightDragDeltaX=0;
	m_MouseRightDragDeltaY=0;

}



//!��Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
int Hippo_InputManager::HandleMsg(HippoContexInfo* pState,HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam )
{


	//�����Զ��������Ϣ
	int r1=ProcessKeyBoardMsg(pState,hWnd,uMsg,wParam,lParam);
	if (r1==1) //�Ѵ�����ϣ������Ĭ�ϵ���Ϣ����
	{
		return 1;
	}

	//�����Զ��������Ϣ
	int r2=ProcessMouseMsg(pState,hWnd,uMsg,wParam,lParam);
	if (r2==1) //�Ѵ�����ϣ������Ĭ�ϵ���Ϣ����
	{
		return 1;
	}

	//�����Զ�����Ϣ������
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


//!������̵���Ϣ������0��ʾû�д���ϣ����Ĭ����Ϣ��������������1��ʾ�Ѿ�������ϣ���پ���Ĭ�ϵĴ���
int Hippo_InputManager::ProcessKeyBoardMsg(HippoContexInfo* pState,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{

	//������û���û��Զ���ļ��̻ص�������¼���̵����
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
	//������е�����֤��û���û��Զ���Ļص�������Ӧ�÷���0
	return 0;
}

//!����������Ϣ������0��ʾû�д���ϣ����Ĭ����Ϣ��������������1��ʾ�Ѿ�������ϣ���پ���Ĭ�ϵĴ���
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
	//������Զ��������Ϣ��������Ϣת������
	CALLBACK_MOUSE pCallbackMouse = pStage->GetMouseFunc();
	if(pCallbackMouse)
		return pCallbackMouse(m_bMouseLButtonDown,m_bMouseRButtonDown,m_bMouseMButtonDown,
								m_nMouseWheelDelta,false,false,m_MousePosX_Wnd,m_MousePosY_Wnd,pStage->GetMouseUserContex());
	//������е�����֤��û���û��Զ���Ļص�������Ӧ�÷���0
	return 0;


}


//!�Ƿ�����ĳ������
bool Hippo_InputManager::IsKeyDown(int key)
{
	return m_Keys[key];
}

//!��ȡ����������ʱ���������µ�λ��
void Hippo_InputManager::GetMouseLKeyDownPos_Wnd(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MousePosX_LeftKeyDown_Wnd;
	*outDeltaY=m_MousePosY_LeftKeyDown_Wnd;
}

//!��ȡ����������ʱ��Ļ�����µ�λ��
void Hippo_InputManager::GetMouseLKeyDownPos_Screen(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MousePosX_LeftKeyDown_Screen;
	*outDeltaY=m_MousePosY_LeftKeyDown_Screen;

}

//!��ȡ��ǰ����λ�ã���������ϵ��
void Hippo_InputManager::GetCurrentMousePos_Wnd(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MousePosX_Wnd;
	*outDeltaY=m_MousePosY_Wnd;

}
//!��ȡ�����ֹ����ľ���
int Hippo_InputManager::GetWheelDelta()
{
	int res=m_nMouseWheelDelta;
	//m_nMouseWheelDelta=0;
	return res;
}

//!�õ��Ƿ����������ק
bool Hippo_InputManager::IsLeftKeyDraging()
{
	return m_bLeftDraging;
}

//!�õ��Ƿ������Ҽ���ק
bool Hippo_InputManager::IsRightKeyDraging()
{
	return m_bRightDraging;
}

int Hippo_InputManager::OnMouseLeftKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	m_bMouseLButtonDown=true;

	//��¼���������µ�λ�ã���������ϵ�£�
	m_MousePosX_LeftKeyDown_Wnd=( int )LOWORD( lParam );
	m_MousePosY_LeftKeyDown_Wnd=( int )HIWORD( lParam );

	m_MousePosX_Wnd=m_MousePosX_LeftKeyDown_Wnd;
	m_MousePosY_Wnd=m_MousePosY_LeftKeyDown_Wnd;
	
	//��¼���������µ�λ�ã���Ļ����ϵ�£�
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
	//��¼��ק
	m_bLeftDraging=m_bMouseLButtonDown;
	m_bRightDraging=m_bMouseRButtonDown;

	m_MousePosX_Wnd=( int )LOWORD( lParam );
	m_MousePosY_Wnd=( int )HIWORD( lParam );


	//���������ק���Ҽ���ק
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

//!�õ���֡��������ק�ƶ��ľ���(��Ļ�ռ�)
int Hippo_InputManager::GetMouseLDragDelta(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MouseLeftDragDeltaX;
	*outDeltaY=m_MouseLeftDragDeltaY;
	return 1;
}
//!�õ���֡����Ҽ���ק�ƶ��ľ���(��Ļ�ռ�)
int Hippo_InputManager::GetMouseRDragDelta(int* outDeltaX,int* outDeltaY)
{
	*outDeltaX=m_MouseRightDragDeltaX;
	*outDeltaY=m_MouseRightDragDeltaY;

	return 1;
}

//!�õ������ק��ʼ�����λ��
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
