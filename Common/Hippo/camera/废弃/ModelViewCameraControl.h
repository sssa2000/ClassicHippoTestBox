/********************************************************************
	created:	2011/11/08
	created:	8:11:2011   23:23
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\ModelViewCameraControl.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	ModelViewCameraControl
	file ext:	h
	author:		sssa2000
	
	purpose:	����modelview�����������
*********************************************************************/
#pragma once
#include "CameraControlBase.h"


class ModelViewCameraControl:public CameraControlBase
{
public:

	ModelViewCameraControl();

	int FrameUpdate(float fElapsedTime);
	//!��Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
	virtual int HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext );

	void SetWindow( int nWidth, int nHeigh);
	void SetModelCenter( H3DVec3& vModelCenter ) { m_RoateCenter = vModelCenter; }

	//!��ȡ��ǰ����ת
	const H3DQuat& GetRotation(){return m_roation;}
	void OnBeginRotation( int nX, int nY );
	void OnRotation( int nX, int nY );
	void OnEndRotation();

	//!����Ļ��ת������λ���ϵĵ�
	H3DVec3 ConvertScreenPoint2SpherePoint(int x,int y);

protected:
	void MoveFowardBack();
	void MoveLeftRight();
	void Pitch();
	void Yaw();

private:
	int AnalysisKeyInput(float fElapsedTime);
	int AnalysisMouseInput(float fElapsedTime);

	int m_nWidth;
	int m_nHeight;
	H3DVec3 m_RoateCenter;
	float m_r;

	//!��ת����Ԫ��
	H3DQuat m_roation;
	H3DQuat m_tmp_roation;

	//!��ת�İ뾶
	float m_fRadius;
	//!��¼��ʼ��ת�ĵ�
	H3DVec3 m_BeginRoatePoint;
	//!�Ƿ��Ϸ�
	bool m_bIsRoating;

};