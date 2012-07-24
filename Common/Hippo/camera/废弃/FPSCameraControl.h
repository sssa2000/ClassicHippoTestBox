/********************************************************************
	created:	2011/10/24
	created:	24:10:2011   22:35
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\FPSCameraControl.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork
	file base:	FPSCameraControl
	file ext:	h
	author:		sssa2000
	
	purpose:	fps相机控制器
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
	//!消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
	virtual int HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext );
	//!子类必须实现该方法，该方法中将一帧中的输入拿出来，做响应
	virtual int FrameUpdate(float fElapsedTime,H3DI::IRender* pRender);


protected:
	void RoateWithZAix(float degreeInRad);
	void RoateWithXAix(float degreeInRad);
	void SetPos(const H3DVec3& pos);
	void SetCameraParam(const H3DVec3& pos,const H3DVec3& lookatpos);
	//!设置移动的距离
	void SetPosDelta(const H3DVec3& posdelta);
	void SetPosDelta(float dir);

	//!应用旋转，四元数将相乘
	void ApplyRoation(const H3DQuat& q);
	void ApplyRoation(const H3DMat3& m);

	//!设置旋转
	void SetRoation(const H3DQuat& q);
	H3DQuat GetCameraRoate(){return m_quat;}

private:
	int AnalysisKeyInput(float fElapsedTime);
	int AnalysisMouseInput(float fElapsedTime);

	//!表示相机旋转的四元数
	H3DQuat m_quat;
	H3DVec3 m_Pos;
	H3DVec3 m_ViewAtDir;
	H3DVec3 m_UpDir;
	H3DVec3 m_RightDir;

	//!运动的方向，计算加速度会用到
	H3DVec3 m_vKeyboardDirection;
	H3DVec3 m_vVelocity;
	float m_fDragTimer;
	H3DVec3 m_vVelocityDrag;
};