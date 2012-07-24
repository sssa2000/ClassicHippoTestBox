#include "FPSCamera.h"
#include "CameraControlMap.h"
#include "../Input/Hippo_InputManager.h"
#include "../HippoFrameWork.h"
#include "engine_interface.h"



FPSCamera::FPSCamera()
{
	m_quat.Identity();
	m_Pos.Set(0,0,0);
	UpdateCameraCoord();
}
FPSCamera::~FPSCamera()
{

}

//from base
const H3DVec3& FPSCamera::GetPos()
{
	return m_Pos;
}

const H3DVec3& FPSCamera::GetViewAtDir()
{
	return m_ViewAtDir;
}

const H3DVec3& FPSCamera::GetUp()
{
	return m_UpDir;
}

void FPSCamera::SetPos(const H3DVec3& pos)
{
	m_Pos=pos;
}

void FPSCamera::SetLookAtDir(const H3DVec3& at)
{
	m_quat.GetRotationTo(m_ViewAtDir,at);
	UpdateCameraCoord();
}

void FPSCamera::SetLookAtPos(const H3DVec3& at)
{
	H3DVec3 tmp=at-m_Pos; //dir是从pos射向目标
	tmp.Normalize();
	SetLookAtDir(tmp);
}

const H3DQuat& FPSCamera::GetRotation()
{
	return m_quat;
}

int FPSCamera::FrameUpdate(float fElapsedTime)
{
	AnalysisKeyInput(fElapsedTime);
	AnalysisMouseInput(fElapsedTime);

	if (m_vVelocity.LengthSqr()==0)
	{
		return 1;
	}
	H3DVec3 pos_delta=m_vVelocity * fElapsedTime;
	SetPosDelta(pos_delta);
	return 1;
}

void FPSCamera::LookAt(H3DI::IRender* pRender,H3DI::ILevel* pLevel)
{
	pRender->LookAt(m_Pos,m_Pos+m_ViewAtDir,m_UpDir);
	pRender->UpdateCamera();

	pLevel->LookAt(m_Pos,m_Pos+m_ViewAtDir,m_UpDir);
	pLevel->UpdateCamera();
}

//!将一帧中记录的输入转化为相机的运动
int FPSCamera::AnalysisKeyInput(float fElapsedTime)
{
	Hippo_InputManager* pInput=GetInputManager();
	m_vKeyboardDirection.Set(0,0,0);
	// Update acceleration vector based on keyboard state
	if( pInput->IsKeyDown(Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(CAM_MOVE_FORWARD) ))
		m_vKeyboardDirection.y += 1.0f;
	if( pInput->IsKeyDown(Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(CAM_MOVE_BACKWARD) ))
		m_vKeyboardDirection.y -= 1.0f;

	if( pInput->IsKeyDown(Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(CAM_MOVE_UP) ))
		m_vKeyboardDirection.z += 1.0f;
	if( pInput->IsKeyDown(Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(CAM_MOVE_DOWN) ))
		m_vKeyboardDirection.z -= 1.0f;

	if( pInput->IsKeyDown(Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(CAM_STRAFE_RIGHT) ))
		m_vKeyboardDirection.x += 1.0f;
	if( pInput->IsKeyDown(Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(CAM_STRAFE_LEFT) ))
		m_vKeyboardDirection.x -= 1.0f;
	//按下shift 速度加倍
	if( pInput->IsKeyDown(Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(CAM_SHIFTDOWN) ))
		m_vKeyboardDirection *= 2.0f;

	H3DVec3 vAccel=m_vKeyboardDirection;
	if(vAccel.LengthSqr() > 0 )
	{
		// If so, then this means the user has pressed a movement key\
		// so change the velocity immediately to acceleration 
		// upon keyboard input.  This isn't normal physics
		// but it will give a quick response to keyboard input
		m_vVelocity = vAccel;
		m_fDragTimer = 0.25f;
		m_vVelocityDrag = vAccel / m_fDragTimer;
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

int FPSCamera::AnalysisMouseInput(float fElapsedTime)
{
	Hippo_InputManager* pInput=GetInputManager();

	if (!pInput->IsLeftKeyDraging())
		return 0;

	int mouseX_dis = 0;
	int mousey_dis = 0;

	pInput->GetMouseLDragDelta(&mouseX_dis,&mousey_dis);

	RoateWithZAix(mouseX_dis*0.3f);
	RoateWithXAix(-mousey_dis*0.3f);

	return 1;
}

void FPSCamera::UpdateCameraCoord()
{
	m_RightDir=INIT_RIGHT*m_quat;
	m_RightDir.Normalize();

	m_ViewAtDir=INIT_VIEWAT*m_quat;
	m_ViewAtDir.Normalize();

	//m_UpDir=m_RightDir.Cross(m_ViewAtDir);
	m_UpDir=INIT_UP*m_quat;
	m_UpDir.Normalize();
}


void FPSCamera::RoateWithZAix(float degreeInRad)
{
	//return;
	H3DQuat tquat;
	tquat.FromAngleAxis(-degreeInRad,H3DVec3(0,0,1));
	m_quat=tquat*m_quat;
	m_quat.Normalize();
	UpdateCameraCoord();
}

void FPSCamera::RoateWithXAix(float degreeInRad)
{

	H3DQuat tquat;
	tquat.FromAngleAxis(degreeInRad,m_RightDir);
	m_quat=tquat*m_quat;
	m_quat.Normalize();
	UpdateCameraCoord();
}


//!设置移动的距离
void FPSCamera::SetPosDelta(const H3DVec3& posdelta)
{
	H3DVec3 t=posdelta* m_quat;
	m_Pos+=t;

}

void FPSCamera::SetPosDelta(float len)
{
	SetPosDelta(H3DVec3(len,len,len));
}
