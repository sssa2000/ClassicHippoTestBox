/********************************************************************
	created:	2011/10/25
	created:	25:10:2011   23:04
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\CameraControlBase.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	CameraControlBase
	file ext:	h
	author:		sssa2000
	
	purpose:	相机控制器的基类，提供一些公有操作，该类不能被单独使用
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

	//!消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
	virtual int HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext );

	//!子类必须实现该方法，该方法中将一帧中的输入拿出来，做响应
	virtual int FrameUpdate(float fElapsedTime)=0;

protected:

	bool IsKeyDown(int key){return m_KeyInputRecord[key]==1;}
	BaseCamera m_camera;

	//!记录一帧中的按键输入,1表示按下状态
	int m_KeyInputRecord[CAM_MAX_KEYS];
	//!记录有多少个键位于按下状态
	int m_cKeysDown;
	bool m_bMouseLButtonDown;    // True if left button is down 
	bool m_bMouseMButtonDown;    // True if middle button is down 
	bool m_bMouseRButtonDown;    // True if right button is down 

	int m_LastMouseX;
	int m_LastMouseY;
	int m_nMouseWheelDelta;
private:
};