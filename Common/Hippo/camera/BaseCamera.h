/********************************************************************
	created:	2011/10/22
	created:	22:10:2011   22:39
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\BaseCamera.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	BaseCamera
	file ext:	h
	author:		sssa2000
	
	purpose:	Base Camera只提供相机的基本操作：移动位置、设置欧拉角
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

	//!消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
	virtual int HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext )=0;
	//!子类必须实现该方法，该方法中将一帧中的输入拿出来，做响应
	virtual int FrameUpdate(float fElapsedTime,H3DI::IRender* pRender)=0;

	void RoateWithZAix(float degreeInRad);
	void RoateWithXAix(float degreeInRad);
	//void SetPos(const H3DVec3& pos);
	//!设置移动的距离
	void SetPosDelta(const H3DVec3& posdelta);
	void SetPosDelta(float dir);

	//!应用旋转，四元数将相乘
	void ApplyRoation(const H3DQuat& q);
	void ApplyRoation(const H3DMat3& m);

	//!设置旋转
	void SetRoation(const H3DQuat& q);
	H3DQuat GetCameraRoate(){return m_quat;}

//protected:
	
	void UpdateCamera();

	////!绕z轴旋转的欧拉角，弧度
	//float m_yaw_rad;
	////!绕x轴旋转的欧拉角，弧度
	//float m_pitch_rad;

	//!表示相机旋转的四元数
	H3DQuat m_quat;

	H3DVec3 m_Pos;
	H3DVec3 m_ViewAtDir;
	H3DVec3 m_UpDir;
	H3DVec3 m_RightDir;

	H3DMat4 m_ViewMatrix;
private:
};