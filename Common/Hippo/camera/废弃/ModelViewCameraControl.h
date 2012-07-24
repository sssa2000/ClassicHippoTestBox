/********************************************************************
	created:	2011/11/08
	created:	8:11:2011   23:23
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\ModelViewCameraControl.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	ModelViewCameraControl
	file ext:	h
	author:		sssa2000
	
	purpose:	用于modelview的相机控制器
*********************************************************************/
#pragma once
#include "CameraControlBase.h"


class ModelViewCameraControl:public CameraControlBase
{
public:

	ModelViewCameraControl();

	int FrameUpdate(float fElapsedTime);
	//!消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
	virtual int HandleMsg(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam, void* pUserContext );

	void SetWindow( int nWidth, int nHeigh);
	void SetModelCenter( H3DVec3& vModelCenter ) { m_RoateCenter = vModelCenter; }

	//!获取当前的旋转
	const H3DQuat& GetRotation(){return m_roation;}
	void OnBeginRotation( int nX, int nY );
	void OnRotation( int nX, int nY );
	void OnEndRotation();

	//!将屏幕点转化到单位球上的点
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

	//!旋转的四元数
	H3DQuat m_roation;
	H3DQuat m_tmp_roation;

	//!旋转的半径
	float m_fRadius;
	//!记录开始旋转的点
	H3DVec3 m_BeginRoatePoint;
	//!是否拖放
	bool m_bIsRoating;

};