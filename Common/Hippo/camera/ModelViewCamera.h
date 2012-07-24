/********************************************************************
	created:	2011/12/23
	created:	23:12:2011   23:59
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\ModelViewCamera.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	ModelViewCamera
	file ext:	h
	author:		sssa2000
	
	purpose:	modelview�����������������˶��ģ����������λ����m_r��������λ��m_roation����
*********************************************************************/
#pragma once
#include "CameraBase.h"

class ModelViewCamera:public CameraBase
{
public:
	ModelViewCamera();
	~ModelViewCamera();

	//from base
	const H3DVec3& GetPos();
	const H3DVec3& GetViewAtDir();
	const H3DVec3& GetUp();
	void SetPos(const H3DVec3& pos);
	void SetLookAtDir(const H3DVec3& at);
	void SetLookAtPos(const H3DVec3& at);

	int FrameUpdate(float fElapsedTime);
	void LookAt(H3DI::IRender* pRender,H3DI::ILevel* pLevel);

	void SetWindow( int nWidth, int nHeigh);
	void SetModelCenter( H3DVec3& vModelCenter ) { m_RoateCenter = vModelCenter; }
	//!��ȡ��ǰ����ת
	const H3DQuat& GetRotation(){return m_roation;}

protected:
private:

	//!�������������ϵ��up��right��lookat
	void UpdateCameraCoord();
	int AnalysisKeyInput(float fElapsedTime);
	int AnalysisMouseInput(float fElapsedTime);

	//!����Ļ��ת������λ���ϵĵ�
	H3DVec3 ConvertScreenPoint2SpherePoint(int x,int y);

	//!����w
	int m_nHalafWidth;
	//!����h
	int m_nHalafHeight;
	//!��������ĵ�
	H3DVec3 m_RoateCenter;
	//!���������İ뾶��������յ�λ���ɸı�������
	float m_r;

	//!��ת����Ԫ��
	H3DQuat m_roation;
	H3DQuat m_tmp_roation;

	//!��¼��ʼ��ת�ĵ�
	H3DVec3 m_BeginRoatePoint;

	H3DVec3 m_Pos;
	H3DVec3 m_ViewAtDir;
	H3DVec3 m_UpDir;

	float m_fDragTimer;
	H3DVec3 m_vVelocityDrag;
	H3DVec3 m_vVelocity;
};