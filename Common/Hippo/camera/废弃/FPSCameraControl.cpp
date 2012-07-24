#include "FPSCameraControl.h"
#include "engine_interface.h"
#include "CameraControlMap.h"



const H3DVec3& FPSCameraControl::GetPos()
{
	return m_Pos;
}

const H3DVec3& FPSCameraControl::GetViewAtDir()
{
	return m_ViewAtDir;
}

const H3DVec3& FPSCameraControl::GetUp()
{
	return m_UpDir;
}

//!将一帧中记录的输入转化为相机的运动
int FPSCameraControl::AnalysisKeyInput(float fElapsedTime)
{
	m_vKeyboardDirection.Set(0,0,0);
	// Update acceleration vector based on keyboard state
	if( IsKeyDown(CAM_MOVE_FORWARD) )
		m_vKeyboardDirection.y += 1.0f;
	if( IsKeyDown(CAM_MOVE_BACKWARD) )
		m_vKeyboardDirection.y -= 1.0f;

	if( IsKeyDown(CAM_MOVE_UP) )
		m_vKeyboardDirection.z += 1.0f;
	if( IsKeyDown(CAM_MOVE_DOWN) )
		m_vKeyboardDirection.z -= 1.0f;

	if( IsKeyDown(CAM_STRAFE_RIGHT) )
		m_vKeyboardDirection.x += 1.0f;
	if( IsKeyDown(CAM_STRAFE_LEFT) )
		m_vKeyboardDirection.x -= 1.0f;

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

int FPSCameraControl::AnalysisMouseInput(float fElapsedTime)
{
	if (!m_bMouseRButtonDown)
		return 0;

	POINT ptCurMousePos;

	// Get current position of mouse
	GetCursorPos( &ptCurMousePos );

	// Calc how far it's moved since last frame
	int mouseX_dis = ptCurMousePos.x - m_LastMouseX;
	int mousey_dis = ptCurMousePos.y - m_LastMouseY;

	// Record current position for next time
	m_LastMouseX = ptCurMousePos.x;
	m_LastMouseY = ptCurMousePos.y;

	m_camera.RoateWithZAix(mouseX_dis*0.3f);
	m_camera.RoateWithXAix(mousey_dis*0.3f);

	return 1;
}

int FPSCameraControl::FrameUpdate(float fElapsedTime)
{
	AnalysisKeyInput(fElapsedTime);
	AnalysisMouseInput(fElapsedTime);

	if (m_vVelocity.LengthSqr()==0)
	{
		return 1;
	}
	H3DVec3 pos_delta=m_vVelocity * fElapsedTime;
	m_camera.SetPosDelta(pos_delta);
	//m_camera.UpdateCameraRoate();
	return 1;

}
void FPSCameraControl::SetCameraParam(const H3DVec3& pos,const H3DVec3& lookatpos)
{
	//根据look at dir 计算 旋转
	m_Pos=pos;
	H3DVec3 lookatdir=lookatpos-pos;
	lookatdir.Normalize();
	m_quat.GetRotationTo(m_ViewAtDir,lookatdir);
	UpdateCamera();
}


void FPSCameraControl::UpdateCamera()
{
	m_RightDir=INIT_RIGHT*m_quat;
	m_RightDir.Normalize();

	m_ViewAtDir=INIT_VIEWAT*m_quat;
	m_ViewAtDir.Normalize();

	//m_UpDir=m_RightDir.Cross(m_ViewAtDir);
	m_UpDir=INIT_UP*m_quat;
	m_UpDir.Normalize();
}


void FPSCameraControl::RoateWithZAix(float degreeInRad)
{
	//return;
	H3DQuat tquat;
	tquat.FromAngleAxis(degreeInRad,H3DVec3(0,0,1));
	m_quat=tquat*m_quat;
	m_quat.Normalize();
	UpdateCamera();
}

void FPSCameraControl::RoateWithXAix(float degreeInRad)
{

	H3DQuat tquat;
	tquat.FromAngleAxis(degreeInRad,m_RightDir);
	m_quat=tquat*m_quat;
	m_quat.Normalize();
	UpdateCamera();
}
