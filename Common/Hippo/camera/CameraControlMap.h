/********************************************************************
	created:	2011/12/24
	created:	24:12:2011   0:44
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera\CameraControlMap.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\camera
	file base:	ModelViewCamera_ControlMap
	file ext:	h
	author:		sssa2000
	
	purpose:	保存model view相机的按键设定
*********************************************************************/
#pragma once


enum Hippo_CameraKeys
{
	CAM_STRAFE_LEFT = 0,
	CAM_STRAFE_RIGHT,
	CAM_MOVE_FORWARD,
	CAM_MOVE_BACKWARD,
	CAM_MOVE_UP,
	CAM_MOVE_DOWN,
	CAM_RESET,
	CAM_CONTROLDOWN,
	CAM_SHIFTDOWN,
	CAM_ALTDOWN,

	CAM_MAX_KEYS,
	CAM_UNKNOWN     = 0xFF
};

#define KEY_WAS_DOWN_MASK 0x80
#define KEY_IS_DOWN_MASK  0x01

#define MOUSE_LEFT_BUTTON   0x01
#define MOUSE_MIDDLE_BUTTON 0x02
#define MOUSE_RIGHT_BUTTON  0x04
#define MOUSE_WHEEL         0x08



class Camera_ControlMap
{
public:
	//!从一个键盘码获取相机逻辑按键
	static Hippo_CameraKeys GetModelViewCameraMapedKey( unsigned int nKey );
	static Hippo_CameraKeys GetFPSCameraMapedKey( unsigned int nKey );
	static int GetFPSCameraKeyCodeFromLogicKey(Hippo_CameraKeys nKey );

};