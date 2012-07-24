/********************************************************************
	created:	2011/10/25
	created:	25:10:2011   23:04
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\CameraControlBase.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	CameraControlBase
	file ext:	h
	author:		sssa2000
	
	purpose:	����������Ļ��࣬�ṩһЩ���в��������಻�ܱ�����ʹ��
*********************************************************************/
#pragma once
#include "BaseCamera.h"
#include "CameraControlMap.h"
#include <Windows.h>
namespace H3DI
{
	class IRender;

}

class CameraControlBase
{
public:
	CameraControlBase();
	virtual ~CameraControlBase(){}
	BaseCamera* GetCamera(){return &m_camera;}
	int LookAt(H3DI::IRender* pRender);
	void SetPos(const H3DVec3& pos){m_camera.SetPos(pos);}

	void SetCameraParam(const H3DVec3& pos,const H3DVec3& lookatpos);

	//!��Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
	virtual int HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext );

	//!�������ʵ�ָ÷������÷����н�һ֡�е������ó���������Ӧ
	virtual int FrameUpdate(float fElapsedTime)=0;

protected:

	bool IsKeyDown(int key){return m_KeyInputRecord[key]==1;}
	BaseCamera m_camera;

	//!��¼һ֡�еİ�������,1��ʾ����״̬
	int m_KeyInputRecord[CAM_MAX_KEYS];
	//!��¼�ж��ٸ���λ�ڰ���״̬
	int m_cKeysDown;
	bool m_bMouseLButtonDown;    // True if left button is down 
	bool m_bMouseMButtonDown;    // True if middle button is down 
	bool m_bMouseRButtonDown;    // True if right button is down 

	int m_LastMouseX;
	int m_LastMouseY;
	int m_nMouseWheelDelta;
private:
};