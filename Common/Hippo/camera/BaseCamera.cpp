#include "BaseCamera.h"


H3DVec3 INIT_VIEWAT(0,1,0);
H3DVec3 INIT_UP(0,0,1);
H3DVec3 INIT_RIGHT(1,0,0);

BaseCamera::BaseCamera()
{
	m_Pos.Set(0,0,0);
	m_UpDir=INIT_UP;
	m_ViewAtDir=INIT_VIEWAT;
	m_RightDir=INIT_RIGHT;
	m_quat.Identity();

}

BaseCamera::~BaseCamera()
{

}



const H3DVec3& BaseCamera::GetPos()
{
	return m_Pos;
}

const H3DVec3& BaseCamera::GetViewAtDir()
{
	return m_ViewAtDir;
}

const H3DVec3& BaseCamera::GetUp()
{
	return m_UpDir;
}

void BaseCamera::SetCameraParam(const H3DVec3& pos,const H3DVec3& lookatpos)
{
	//根据look at dir 计算 旋转
	m_Pos=pos;
	H3DVec3 lookatdir=lookatpos-pos;
	lookatdir.Normalize();
	m_quat.GetRotationTo(m_ViewAtDir,lookatdir);
	UpdateCamera();
}


void BaseCamera::UpdateCamera()
{
	m_RightDir=INIT_RIGHT*m_quat;
	m_RightDir.Normalize();

	m_ViewAtDir=INIT_VIEWAT*m_quat;
	m_ViewAtDir.Normalize();

	//m_UpDir=m_RightDir.Cross(m_ViewAtDir);
	m_UpDir=INIT_UP*m_quat;
	m_UpDir.Normalize();
}


void BaseCamera::RoateWithZAix(float degreeInRad)
{
	//return;
	H3DQuat tquat;
	tquat.FromAngleAxis(degreeInRad,H3DVec3(0,0,1));
	m_quat=tquat*m_quat;
	m_quat.Normalize();
	UpdateCamera();
}

void BaseCamera::RoateWithXAix(float degreeInRad)
{

	H3DQuat tquat;
	tquat.FromAngleAxis(degreeInRad,m_RightDir);
	m_quat=tquat*m_quat;
	m_quat.Normalize();
	UpdateCamera();
}

void BaseCamera::SetPos(const H3DVec3& pos)
{
	m_Pos=pos;
}

//!设置移动的距离
void BaseCamera::SetPosDelta(const H3DVec3& posdelta)
{
	H3DVec3 t=posdelta* m_quat;
	m_Pos+=t;

}

void BaseCamera::SetPosDelta(float len)
{
	SetPosDelta(H3DVec3(len,len,len));
}




void BaseCamera::ApplyRoation(const H3DQuat& q)
{
	m_quat=q*m_quat;
	m_quat.Normalize();
	UpdateCamera();
}

//!设置旋转
void BaseCamera::SetRoation(const H3DQuat& q)
{
	m_quat=q;
	UpdateCamera();

}

void BaseCamera::ApplyRoation(const H3DMat3& m)
{
	m_RightDir=INIT_RIGHT*m;
	m_RightDir.Normalize();

	m_ViewAtDir=INIT_VIEWAT*m;
	m_ViewAtDir.Normalize();

	//m_UpDir=m_RightDir.Cross(m_ViewAtDir);
	m_UpDir=INIT_UP*m;
	m_UpDir.Normalize();
}