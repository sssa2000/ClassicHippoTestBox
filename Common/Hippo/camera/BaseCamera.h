/********************************************************************
	created:	2011/10/22
	created:	22:10:2011   22:39
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\BaseCamera.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	BaseCamera
	file ext:	h
	author:		sssa2000
	
	purpose:	Base Cameraֻ�ṩ����Ļ����������ƶ�λ�á�����ŷ����
*********************************************************************/
#pragma once
#include "../idMath/dMathHeader.h"
#include <windows.h>
namespace H3DI
{
	class IRender;
}

class BaseCamera
{
public:
	BaseCamera();
	virtual ~BaseCamera();


	virtual const H3DVec3& GetPos()=0;
	virtual const H3DVec3& GetViewAtDir()=0;
	virtual const H3DVec3& GetUp()=0;
	virtual void SetPos(const H3DVec3& pos);
	virtual void SetCameraParam(const H3DVec3& pos,const H3DVec3& lookatpos)=0;

	//!��Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
	virtual int HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext )=0;
	//!�������ʵ�ָ÷������÷����н�һ֡�е������ó���������Ӧ
	virtual int FrameUpdate(float fElapsedTime,H3DI::IRender* pRender)=0;

	void RoateWithZAix(float degreeInRad);
	void RoateWithXAix(float degreeInRad);
	//void SetPos(const H3DVec3& pos);
	//!�����ƶ��ľ���
	void SetPosDelta(const H3DVec3& posdelta);
	void SetPosDelta(float dir);

	//!Ӧ����ת����Ԫ�������
	void ApplyRoation(const H3DQuat& q);
	void ApplyRoation(const H3DMat3& m);

	//!������ת
	void SetRoation(const H3DQuat& q);
	H3DQuat GetCameraRoate(){return m_quat;}

//protected:
	
	void UpdateCamera();

	////!��z����ת��ŷ���ǣ�����
	//float m_yaw_rad;
	////!��x����ת��ŷ���ǣ�����
	//float m_pitch_rad;

	//!��ʾ�����ת����Ԫ��
	H3DQuat m_quat;

	H3DVec3 m_Pos;
	H3DVec3 m_ViewAtDir;
	H3DVec3 m_UpDir;
	H3DVec3 m_RightDir;

	H3DMat4 m_ViewMatrix;
private:
};