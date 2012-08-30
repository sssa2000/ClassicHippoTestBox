#include "ModelViewCamera.h"
#include "CameraControlMap.h"
#include "../Input/Hippo_InputManager.h"
#include "../HippoFrameWork.h"
#include "engine_interface.h"

ModelViewCamera::ModelViewCamera()
{
	m_roation.Identity();
	m_r=1.0f;
	m_nHalafWidth=0;
	m_nHalafHeight=0;
	m_RoateCenter.Set(0,0,0);
	m_BeginRoatePoint.Set(0,0,0);
	m_roation.Identity();
	m_tmp_roation.Identity();
	UpdateCameraCoord();
}

ModelViewCamera::~ModelViewCamera()
{

}

//from base
const H3DVec3& ModelViewCamera::GetPos()
{
	return m_Pos;
}

const H3DVec3& ModelViewCamera::GetViewAtDir()
{
	return m_ViewAtDir;

}

const H3DVec3& ModelViewCamera::GetUp()
{
	return m_UpDir;

}

void ModelViewCamera::SetPos(const H3DVec3& pos)
{
	m_r=(pos-m_RoateCenter).Length();
	UpdateCameraCoord();
}

void ModelViewCamera::SetLookAtDir(const H3DVec3& at)
{
	m_roation.GetRotationTo(m_ViewAtDir,at);
	m_roation.Normalize();
	UpdateCameraCoord();
}

void ModelViewCamera::SetLookAtPos(const H3DVec3& at)
{
	H3DVec3 tmp=at-m_Pos; //dir�Ǵ�pos����Ŀ��
	tmp.Normalize();
	SetLookAtDir(tmp);
}
void ModelViewCamera::UpdateCameraCoord()
{
	const H3DQuat& q=GetRotation();

	m_ViewAtDir=INIT_VIEWAT * q;
	m_ViewAtDir.Normalize();

	m_Pos=m_RoateCenter-m_ViewAtDir * m_r;

	m_UpDir=INIT_UP * q;
	m_UpDir.Normalize();
}


void ModelViewCamera::SetWindow( int nWidth, int nHeigh)
{
	m_nHalafWidth=nWidth*0.5f;
	m_nHalafHeight=nHeigh*0.5f;
}

//!����Ļ��ת������λ���ϵĵ�
H3DVec3 ModelViewCamera::ConvertScreenPoint2SpherePoint(int fScreenPtX,int fScreenPtY)
{
	H3DVec3 res;
	float x   = (float)(fScreenPtX-m_nHalafWidth)/m_nHalafWidth;
	float z   = (float)(fScreenPtY-m_nHalafHeight)/m_nHalafHeight;
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
}

int ModelViewCamera::FrameUpdate(float fElapsedTime)
{
	AnalysisKeyInput(fElapsedTime);
	AnalysisMouseInput(fElapsedTime);

	UpdateCameraCoord();

	m_RoateCenter+=m_vVelocity;
	return 1;
}

//!��һ֡�м�¼������ת��Ϊ������˶�
int ModelViewCamera::AnalysisKeyInput(float fElapsedTime)
{
	Hippo_InputManager* pInput=GetInputManager();
	H3DVec3 tmpV;
	tmpV.Set(0,0,0);
	if( pInput->IsKeyDown(Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(CAM_MOVE_UP) ))
	{
		tmpV.z += 0.02f;
		Hippo_WriteConsole(CC_WHITE,"ModelView Camera Z+1\n");
	}
	if( pInput->IsKeyDown(Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(CAM_MOVE_DOWN) ))
	{
		tmpV.z -= 0.02f;
		Hippo_WriteConsole(CC_WHITE,"ModelView Camera Z-1\n");
	}

	m_vVelocity=tmpV;
	if(m_vVelocity.LengthSqr() > 0 )
	{
		m_fDragTimer = 0.1f;
		m_vVelocityDrag = m_vVelocity/m_fDragTimer;
	}
	else
	{
		// If no key being pressed, then slowly decrease velocity to 0
		if( m_fDragTimer > 0 )
		{
			// Drag until timer is <= 0
			m_vVelocity -= m_vVelocityDrag * fElapsedTime;
			m_fDragTimer -= fElapsedTime;
		}
		else
		{
			// Zero velocity
			m_vVelocity .Set( 0, 0, 0 );
		}
	}


	return 1;
}

int ModelViewCamera::AnalysisMouseInput(float fElapsedTime)
{
	Hippo_InputManager* pInput=GetInputManager();

	if (pInput->IsMouseLButtonDown())
	{
		int iMouseX,iMouseY;
		pInput->GetCurrentMousePos_Wnd(&iMouseX,&iMouseY);

		//��������������ˣ���ô���㵱ǰ���������λ��
		if (!pInput->IsLeftKeyDraging())
		{
			m_tmp_roation=m_roation;
			m_BeginRoatePoint=ConvertScreenPoint2SpherePoint(iMouseX,iMouseY);
		}
		else
		{
			//����û��������ק����ô��������������꣬��mouse downʱ���������һ����ת
			//���㵱ǰ�����������
			H3DVec3 sp=ConvertScreenPoint2SpherePoint(iMouseX,iMouseY);

			//���㵱ǰ�㵽�ϴμ�¼�ĵ����ת
			H3DQuat this_rot;

			H3DVec3 aix=sp.Cross(m_BeginRoatePoint);
			float dot=m_BeginRoatePoint.Dot(sp);
			this_rot.Set(aix.x,aix.y,aix.z,dot);
			this_rot.Normalize();

			m_roation=m_tmp_roation*this_rot; //ʵ���������ת�͵�λ�����ת���෴��
			
			if(m_roation.Length()==0)
			{
				//�����ʼ����ʱ���϶�console���ڣ�Ȼ��������Ⱦ���ڻ�ý��㣬�����m_roation= 0��0��0��0�����
				m_roation.Identity();
			}
			m_roation.Normalize();
		}
	}


	int delta=pInput->GetWheelDelta();
	m_r -= delta * m_r * 0.5f / 120.0f;

	return 1;
}

void ModelViewCamera::LookAt(H3DI::IRender* pRender)
{
	pRender->LookAt(m_Pos,m_Pos+m_ViewAtDir,m_UpDir);
	pRender->UpdateCamera();


}

