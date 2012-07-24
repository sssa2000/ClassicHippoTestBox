#include "ArcBall.h"
#include <Windows.h>

extern bool useDebug;

ArcBall::ArcBall()
{
	m_roation.Identity();
	m_fRadius=0.5f;
	m_BeginRoatePoint.Set(0,0,0);
	m_nWidth=0;
	m_nHeight=0;
	m_bIsRoating=false;
}

void ArcBall::SetWndWidthHeight(int wnd_w,int wnd_h)
{
	m_nWidth=wnd_w;
	m_nHeight=wnd_h;
}

const H3DQuat& ArcBall::GetRotation()
{
	return m_roation;
}

void ArcBall::OnBeginRotation( int nX, int nY )
{
	m_bIsRoating=true;
	m_tmp_roation=m_roation;
	m_BeginRoatePoint=ConvertScreenPoint2SpherePoint(nX,nY);

	//char buff[256];
	//sprintf_s(buff,256,"OnBeginRotation:%f,%f,%f\n",m_BeginRoatePoint.x,m_BeginRoatePoint.y,m_BeginRoatePoint.z);
	//OutputDebugStringA(buff);

}

void ArcBall::OnRotation( int nX, int nY )
{
	if(!m_bIsRoating)
		return;

	//计算当前点的球面坐标
	H3DVec3 sp=ConvertScreenPoint2SpherePoint(nX,nY);


	//计算当前点到上次记录的点的旋转
	H3DQuat this_rot;

	H3DVec3 aix=sp.Cross(m_BeginRoatePoint);
	float dot=m_BeginRoatePoint.Dot(sp);
	this_rot.Set(aix.x,aix.y,aix.z,dot);
	this_rot.Normalize();
	
	//this_rot.GetRotationTo(m_BeginRoatePoint,sp);
	m_roation=m_tmp_roation*this_rot;
	m_roation.Normalize();
}

void ArcBall::OnEndRotation()
{
	m_bIsRoating=false;
}

//!将屏幕点转化到单位球上的点
H3DVec3 ArcBall::ConvertScreenPoint2SpherePoint(int fScreenPtX,int fScreenPtY)
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
