#include "CameraControlMap.h"
#include <Windows.h>

Hippo_CameraKeys Camera_ControlMap::GetModelViewCameraMapedKey( unsigned int nKey )
{
	return CAM_UNKNOWN;
}

Hippo_CameraKeys Camera_ControlMap::GetFPSCameraMapedKey( unsigned int nKey )
{
	switch( nKey )
	{
	case 'A':
		return CAM_STRAFE_LEFT;
	case 'D':
		return CAM_STRAFE_RIGHT;
	case 'W':
		return CAM_MOVE_FORWARD;
	case 'S':
		return CAM_MOVE_BACKWARD;
	case 'Q':
		return CAM_MOVE_DOWN;
	case 'E':
		return CAM_MOVE_UP;
	default:
		return CAM_UNKNOWN;
	}

	return CAM_UNKNOWN;
}

int Camera_ControlMap::GetFPSCameraKeyCodeFromLogicKey(Hippo_CameraKeys nKey )
{
	switch( nKey )
	{
	case CAM_STRAFE_LEFT:
		return 'A';
	case CAM_STRAFE_RIGHT:
		return 'D';
	case CAM_MOVE_FORWARD:
		return 'W';
	case CAM_MOVE_BACKWARD:
		return 'S';
	case CAM_MOVE_DOWN:
		return 'Q';
	case CAM_MOVE_UP:
		return 'E';
	case CAM_SHIFTDOWN:
		return VK_SHIFT;
	default:
		return -1;
	}
	return -1;
}

//Hippo_CameraKeys MapKey( unsigned int nKey )
//{
//	// This could be upgraded to a method that's user-definable but for 
//	// simplicity, we'll use a hardcoded mapping.
//	switch( nKey )
//	{
//	case VK_CONTROL:
//		return CAM_CONTROLDOWN;
//	case VK_LEFT:
//		return CAM_STRAFE_LEFT;
//	case VK_RIGHT:
//		return CAM_STRAFE_RIGHT;
//	case VK_UP:
//		return CAM_MOVE_FORWARD;
//	case VK_DOWN:
//		return CAM_MOVE_BACKWARD;
//	case VK_PRIOR:
//		return CAM_MOVE_UP;        // pgup
//	case VK_NEXT:
//		return CAM_MOVE_DOWN;      // pgdn
//
//	case 'A':
//		return CAM_STRAFE_LEFT;
//	case 'D':
//		return CAM_STRAFE_RIGHT;
//	case 'W':
//		return CAM_MOVE_FORWARD;
//	case 'S':
//		return CAM_MOVE_BACKWARD;
//	case 'Q':
//		return CAM_MOVE_DOWN;
//	case 'E':
//		return CAM_MOVE_UP;
//
//	case VK_NUMPAD4:
//		return CAM_STRAFE_LEFT;
//	case VK_NUMPAD6:
//		return CAM_STRAFE_RIGHT;
//	case VK_NUMPAD8:
//		return CAM_MOVE_FORWARD;
//	case VK_NUMPAD2:
//		return CAM_MOVE_BACKWARD;
//	case VK_NUMPAD9:
//		return CAM_MOVE_UP;
//	case VK_NUMPAD3:
//		return CAM_MOVE_DOWN;
//
//	case VK_HOME:
//		return CAM_RESET;
//	}
//
//	return CAM_UNKNOWN;
//}
