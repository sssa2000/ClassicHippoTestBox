/********************************************************************
	created:	2011/11/08
	created:	8:11:2011   23:38
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\ArcBall.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	ArcBall
	file ext:	h
	author:		sssa2000
	
	purpose:	将2维的平移转化为球面坐标的旋转
*********************************************************************/
#pragma once

#include "../idMath/dMathHeader.h"
class ArcBall
{
public:
	ArcBall();

	void SetWndWidthHeight(int wnd_w,int wnd_h);
	//!获取当前的旋转
	const H3DQuat& GetRotation();
	void OnBeginRotation( int nX, int nY );
	void OnRotation( int nX, int nY );
	void OnEndRotation();

	//!将屏幕点转化到单位球上的点
	H3DVec3 ConvertScreenPoint2SpherePoint(int x,int y);
	//!旋转的四元数
	H3DQuat m_roation;
	H3DQuat m_tmp_roation;
	//!旋转的半径
	float m_fRadius;
	//windows 长宽
	int m_nWidth;
	//windows 长宽
	int m_nHeight;
	//!记录开始旋转的点
	H3DVec3 m_BeginRoatePoint;

	//!是否拖放
	bool m_bIsRoating;
};