#include "CameraControlBase.h"
#include "engine_interface.h"

CameraControlBase::CameraControlBase():
m_cKeysDown(0)
{
	memset(m_KeyInputRecord,0,CAM_MAX_KEYS*sizeof(int));
	m_bMouseLButtonDown=false;
	m_bMouseMButtonDown=false;
	m_bMouseRButtonDown=false;
	m_LastMouseX=0;
	m_LastMouseY=0;
	m_nMouseWheelDelta=0;
}

void CameraControlBase::SetCameraParam(const H3DVec3& pos,const H3DVec3& lookatpos)
{
	m_camera.SetCameraParam(pos,lookatpos);

}


int CameraControlBase::LookAt(H3DI::IRender* pRender)
{
	const H3DVec3& pos=m_camera.GetPos();
	const H3DVec3& at=m_camera.GetViewAtDir();
	const H3DVec3& up=m_camera.GetUp();


	pRender->LookAt(pos,at,up);
	pRender->UpdateCamera();
	//pRender->SetViewMatrix(m_camera.GetViewMatrix());

	return 1;
}

//!消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
int CameraControlBase::HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext )
{
	switch( uMsg )
	{
	case WM_KEYDOWN:
		{
			Hippo_CameraKeys mappedKey = MapKey( ( UINT )wParam );
			if( mappedKey != CAM_UNKNOWN )
			{
				if( FALSE == IsKeyDown( m_KeyInputRecord[mappedKey] ) )
				{
					m_KeyInputRecord[ mappedKey ] = 1;
					++m_cKeysDown;
				}
			}
			break;
		}
	case WM_KEYUP:
		{
			// Map this key to a D3DUtil_CameraKeys enum and update the
			// state of m_aKeys[] by removing the KEY_IS_DOWN_MASK mask.
			Hippo_CameraKeys mappedKey = MapKey( ( UINT )wParam );
			if( mappedKey != CAM_UNKNOWN && ( DWORD )mappedKey < CAM_MAX_KEYS )
			{
				m_KeyInputRecord[ mappedKey ] =0;
				--m_cKeysDown;
			}
			break;
		}
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_LBUTTONDBLCLK:
		{
			// Compute the drag rectangle in screen coord.
			POINT ptCursor = { ( short )LOWORD( lParam ), ( short )HIWORD( lParam ) };

			// Update member var state
			if(  uMsg == WM_LBUTTONDOWN|| uMsg == WM_LBUTTONDBLCLK)
			{
				m_bMouseLButtonDown = true; 
			}
			if(  uMsg == WM_MBUTTONDOWN|| uMsg == WM_MBUTTONDBLCLK )
			{
				m_bMouseMButtonDown = true;
			}
			if(  uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONDBLCLK )
			{
				m_bMouseRButtonDown = true;
			}

			// Capture the mouse, so if the mouse button is 
			// released outside the window, we'll get the WM_LBUTTONUP message
			SetCapture( hWnd );
			GetCursorPos( &ptCursor );
			m_LastMouseX=ptCursor.x;
			m_LastMouseY=ptCursor.y;
			return TRUE;
		}

	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_LBUTTONUP:
		{
			// Update member var state
			if( uMsg == WM_LBUTTONUP )
			{
				m_bMouseLButtonDown = false; 
			}
			if( uMsg == WM_MBUTTONUP )
			{
				m_bMouseMButtonDown = false; 
			}
			if( uMsg == WM_RBUTTONUP )
			{
				m_bMouseRButtonDown = false; 
			}

			// Release the capture if no mouse buttons down
			if( !m_bMouseLButtonDown &&
				!m_bMouseRButtonDown &&
				!m_bMouseMButtonDown )
			{
				ReleaseCapture();
			}
			break;
		}

	default:
		return 0;
	}
	return 0;
}