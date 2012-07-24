/********************************************************************
	created:	2011/10/24
	created:	24:10:2011   22:35
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\FPSCameraControl.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork
	file base:	FPSCameraControl
	file ext:	h
	author:		sssa2000
	
	purpose:	fps���������
*********************************************************************/
#pragma once
#include "BaseCamera.h"



class FPSCameraControl:public BaseCamera
{
public:

	virtual const H3DVec3& GetPos();
	virtual const H3DVec3& GetViewAtDir();
	virtual const H3DVec3& GetUp();
	virtual void SetPos(const H3DVec3& pos);
	virtual void SetCameraParam(const H3DVec3& pos,const H3DVec3& lookatpos);
	//!��Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
	virtual int HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext );
	//!�������ʵ�ָ÷������÷����н�һ֡�е������ó���������Ӧ
	virtual int FrameUpdate(float fElapsedTime,H3DI::IRender* pRender);


protected:
	void RoateWithZAix(float degreeInRad);
	void RoateWithXAix(float degreeInRad);
	void SetPos(const H3DVec3& pos);
	void SetCameraParam(const H3DVec3& pos,const H3DVec3& lookatpos);
	//!�����ƶ��ľ���
	void SetPosDelta(const H3DVec3& posdelta);
	void SetPosDelta(float dir);

	//!Ӧ����ת����Ԫ�������
	void ApplyRoation(const H3DQuat& q);
	void ApplyRoation(const H3DMat3& m);

	//!������ת
	void SetRoation(const H3DQuat& q);
	H3DQuat GetCameraRoate(){return m_quat;}

private:
	int AnalysisKeyInput(float fElapsedTime);
	int AnalysisMouseInput(float fElapsedTime);

	//!��ʾ�����ת����Ԫ��
	H3DQuat m_quat;
	H3DVec3 m_Pos;
	H3DVec3 m_ViewAtDir;
	H3DVec3 m_UpDir;
	H3DVec3 m_RightDir;

	//!�˶��ķ��򣬼�����ٶȻ��õ�
	H3DVec3 m_vKeyboardDirection;
	H3DVec3 m_vVelocity;
	float m_fDragTimer;
	H3DVec3 m_vVelocityDrag;
};