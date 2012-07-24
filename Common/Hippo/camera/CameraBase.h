/********************************************************************
	created:	2011/12/23
	created:	23:12:2011   23:56
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\CameraBase.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	CameraBase
	file ext:	h
	author:		sssa2000
	
	purpose:	base class of camera
*********************************************************************/
#pragma once
#include "../idMath/dMathHeader.h"

namespace H3DI
{
	class IRender;
	class ILevel;
}


#define INIT_UP H3DVec3(0,0,1)
#define INIT_RIGHT H3DVec3(1,0,0)
#define INIT_VIEWAT H3DVec3(0,1,0)

class CameraBase
{
public:
	virtual ~CameraBase(){}
	virtual const H3DVec3& GetPos()=0;
	virtual const H3DVec3& GetViewAtDir()=0;
	virtual const H3DVec3& GetUp()=0;
	virtual const H3DQuat& GetRotation()=0;
	virtual void SetPos(const H3DVec3& pos)=0;
	virtual void SetLookAtDir(const H3DVec3& at)=0;
	virtual void SetLookAtPos(const H3DVec3& at)=0;

	//!子类必须实现该方法，该方法中将一帧中的输入拿出来，做响应
	virtual int FrameUpdate(float fElapsedTime)=0;
	virtual void LookAt(H3DI::IRender* pRender,H3DI::ILevel* pLevel)=0;
protected:
private:
};