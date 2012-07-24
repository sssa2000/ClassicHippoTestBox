#include "ModelViewCameraControl.h"

extern bool autoMoveCamera;

ModelViewCameraControl::ModelViewCameraControl()
{
	m_roation.Identity();
	m_fRadius=1.0f;
	m_BeginRoatePoint.Set(0,0,0);
	m_nWidth=0;
	m_nHeight=0;
	m_bIsRoating=false;
	m_RoateCenter.Set(0,0,0);
	m_r=1.0f;
}

//!消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
int ModelViewCameraControl::HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext )
{
	CameraControlBase::HandleMsg(hWnd,uMsg,wParam,lParam,pUserContext);
	switch( uMsg )
	{
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_LBUTTONDBLCLK:
		{
			int iMouseX = ( short )LOWORD( lParam );
			int iMouseY = ( short )HIWORD( lParam );
			m_bIsRoating=true;
			m_tmp_roation=m_roation;
			m_BeginRoatePoint=ConvertScreenPoint2SpherePoint(iMouseX,iMouseY);

			break;

		}
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_LBUTTONUP:
		{
			m_bIsRoating=false;
			break;
		}
	case WM_MOUSEMOVE:
		{
			int iMouseX = ( short )LOWORD( lParam );
			int iMouseY = ( short )HIWORD( lParam );
			if(!m_bIsRoating)
				return 0;

			//计算当前点的球面坐标
			H3DVec3 sp=ConvertScreenPoint2SpherePoint(iMouseX,iMouseY);

			//计算当前点到上次记录的点的旋转
			H3DQuat this_rot;

			H3DVec3 aix=sp.Cross(m_BeginRoatePoint);
			//H3DVec3 aix=m_BeginRoatePoint.Cross(sp);
			float dot=m_BeginRoatePoint.Dot(sp);
			this_rot.Set(aix.x,aix.y,aix.z,dot);
			this_rot.Normalize();

			//this_rot.GetRotationTo(m_BeginRoatePoint,sp);
			m_roation=m_tmp_roation*this_rot; //实际世界的旋转和单位球的旋转是相反的
			m_roation.Normalize();

			break;
		}
	case WM_MOUSEWHEEL:
		{
			m_nMouseWheelDelta += ( short )HIWORD( wParam );
			break;
		}
	default:
		return 0;
	}
	return 0;
}

int ModelViewCameraControl::AnalysisKeyInput(float fElapsedTime)
{
	return 1;
}


int ModelViewCameraControl::AnalysisMouseInput(float fElapsedTime)
{

    m_r -= m_nMouseWheelDelta * m_r * 0.5f / 120.0f;
	m_nMouseWheelDelta=0;


	return 1;
}

int ModelViewCameraControl::FrameUpdate(float fElapsedTime)
{
	AnalysisKeyInput(fElapsedTime);
	AnalysisMouseInput(fElapsedTime);

	const H3DQuat& q=GetRotation();
	//H3DMat3 m=q.ToMat3();
	//m.InverseSelf();
	//m_camera.SetRoation(q);


	H3DVec3 lookatdir=H3DVec3(0,1,0)* q;
	lookatdir.Normalize();

	H3DVec3 camerapos=m_RoateCenter-lookatdir * m_r;
	m_camera.m_Pos=camerapos;

	m_camera.m_ViewAtDir=lookatdir;
	m_camera.m_ViewAtDir.Normalize();
	//m_camera.m_ViewAtDir=m_RoateCenter;


	m_camera.m_UpDir=H3DVec3(0,0,1)*q;
	m_camera.m_UpDir.Normalize();
	return 1;
}

void ModelViewCameraControl::SetWindow( int nWidth, int nHeigh)
{
	m_nWidth=nWidth;m_nHeight=nHeigh;
}

//!将屏幕点转化到单位球上的点
H3DVec3 ModelViewCameraControl::ConvertScreenPoint2SpherePoint(int fScreenPtX,int fScreenPtY)
{
	H3DVec3 res;
	float x   = (fScreenPtX - m_nWidth/2)  / (m_fRadius*m_nWidth/2);
	float z   = (fScreenPtY - m_nHeight/2) / (m_fRadius*m_nHeight/2);
	float y   = 0.0f;
	float mag = x*x + z*z;
	if (mag > 1.0f)
	{
		float scale = 1.0f/sqrtf(mag);
		x *= scale;
		z *= scale;
	}
	else
		y = sqrtf(1.0f - mag);

	res.Set(-x,y,z);
	return res;

	//H3DVec3 res;
	//float x   = -(fScreenPtX - m_nWidth/2)  / (m_fRadius*m_nWidth/2);
	//float y   = (fScreenPtY - m_nHeight/2) / (m_fRadius*m_nHeight/2);
	//float z   = 0.0f;
	//float mag = x*x + y*y;
	//if (mag > 1.0f)
	//{
	//	float scale = 1.0f/sqrtf(mag);
	//	x *= scale;
	//	y *= scale;
	//}
	//else
	//	z = sqrtf(1.0f - mag);

	//res.Set(x,-z,y);
	//return res;
}
