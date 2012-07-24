/********************************************************************
	created:	2011/12/23
	created:	23:12:2011   23:59
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\ModelViewCamera.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	ModelViewCamera
	file ext:	h
	author:		sssa2000
	
	purpose:	modelview相机，相机是在球面运动的，相机的最终位置由m_r决定，方位由m_roation决定
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
	//!获取当前的旋转
	const H3DQuat& GetRotation(){return m_roation;}

protected:
private:

	//!更新相机的坐标系即up、right、lookat
	void UpdateCameraCoord();
	int AnalysisKeyInput(float fElapsedTime);
	int AnalysisMouseInput(float fElapsedTime);

	//!将屏幕点转化到单位球上的点
	H3DVec3 ConvertScreenPoint2SpherePoint(int x,int y);

	//!窗口w
	int m_nHalafWidth;
	//!窗口h
	int m_nHalafHeight;
	//!相机的中心点
	H3DVec3 m_RoateCenter;
	//!相机所在球的半径，相机最终的位置由改变量决定
	float m_r;

	//!旋转的四元数
	H3DQuat m_roation;
	H3DQuat m_tmp_roation;

	//!记录开始旋转的点
	H3DVec3 m_BeginRoatePoint;

	H3DVec3 m_Pos;
	H3DVec3 m_ViewAtDir;
	H3DVec3 m_UpDir;

	float m_fDragTimer;
	H3DVec3 m_vVelocityDrag;
	H3DVec3 m_vVelocity;
};