/********************************************************************
	created:	2011/11/08
	created:	8:11:2011   23:38
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\ArcBall.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	ArcBall
	file ext:	h
	author:		sssa2000
	
	purpose:	��2ά��ƽ��ת��Ϊ�����������ת
*********************************************************************/
#pragma once

#include "../idMath/dMathHeader.h"
class ArcBall
{
public:
	ArcBall();

	void SetWndWidthHeight(int wnd_w,int wnd_h);
	//!��ȡ��ǰ����ת
	const H3DQuat& GetRotation();
	void OnBeginRotation( int nX, int nY );
	void OnRotation( int nX, int nY );
	void OnEndRotation();

	//!����Ļ��ת������λ���ϵĵ�
	H3DVec3 ConvertScreenPoint2SpherePoint(int x,int y);
	//!��ת����Ԫ��
	H3DQuat m_roation;
	H3DQuat m_tmp_roation;
	//!��ת�İ뾶
	float m_fRadius;
	//windows ����
	int m_nWidth;
	//windows ����
	int m_nHeight;
	//!��¼��ʼ��ת�ĵ�
	H3DVec3 m_BeginRoatePoint;

	//!�Ƿ��Ϸ�
	bool m_bIsRoating;
};