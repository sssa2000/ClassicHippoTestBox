#include <Windows.h>
#include "HippoFrameWork.h"
#include "engine_interface.h"
#include "idMath/dMathHeader.h"
#include "camera/FPSCamera.h"
#include "camera/ModelViewCamera.h"
#include "HippoTestManager.h"
#include <vector>
#include "HippoScene.h"
#include "HippoTestManager.h"


const int WND_WIDTH=1024;
const int WND_HEIGHT=768;


void InitApp();
LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, void* pUserContext );
int OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext );
int OnFrameUpdate(DWORD fElapsedTimeInMs, void* pUserContext );
int OnMouse( bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, 
	bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext );




FPSCamera* gCameraFps=0;
ModelViewCamera* gCameraModelView=0;
CameraBase* pCam[2];
int cameraIdx=1;

void SetUpCamera(DWORD fElapsedTimeInMs);







//!自定义的键盘消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
int OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
{
	return HippoTestManager::GetInstance()->ProcessInput(nChar,bKeyDown,bAltDown,bCrtlDown,bShiftDown,pUserContext);
}





void InitScene()
{

}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{

	Hippo_InitFrameWork();
	Hippo_CreateWindow("ClassicHippo",0,hInstance,0,0,WND_WIDTH,WND_HEIGHT);

	// Set callbacks
	Hippo_SetMsgProcCallback( MsgProc );
	Hippo_SetKeyboardCallback( OnKeyboard );
	Hippo_SetFrameUpdateCallback( OnFrameUpdate );
	Hippo_SetMouseCallback(OnMouse);

	Hippo_InitIRender();

	InitApp();

	Hippo_MainLoop();

	return 1;
}


void Update(float escape)
{
	Hippo_GetSceneManager()->UpdateScene(escape);

}

int OnFrameUpdate(DWORD fElapsedTimeInMs, void* pUserContext )
{

	HippoTestManager::GetInstance()->RunAllTest();

	H3DI::IRender* pRender=Hippo_GetIRender();
	SetUpCamera(fElapsedTimeInMs);

	Update(fElapsedTimeInMs*0.001f);
	pRender->UpdatePhx(fElapsedTimeInMs);


	pRender->FrameBegin();
	pRender->ClearScreen();

	Hippo_GetSceneManager()->PushSceneToRender(fElapsedTimeInMs*0.001f);


	pRender->Render();

	//Hippo_DrawHelpGrid();
	pRender->FrameEnd();
	pRender->SwapBuffer();

	return 1;
}

void InitApp()
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	pRender->SetFrustum(60,4.f/3.f,0.2f, 5000.f);


	gCameraFps=new FPSCamera;
	gCameraModelView=new ModelViewCamera;

	H3DVec3 eyepos(-1.2857239f,-5.4603639f,13.1436100f);//{x=-1.2857239 y=-5.4603639 z=3.1436100 }
	H3DVec3 lookatpos(0,0,0);//{x=0.16619506 y=0.55046451 z=-0.81814921 }
	//gCamera->SetCameraParam(eyepos,lookatpos);
	gCameraModelView->SetPos(eyepos);
	H3DVec3 tmp=lookatpos-eyepos; //dir是从pos射向目标
	tmp.Normalize();
	gCameraModelView->SetLookAtDir(tmp);
	gCameraModelView->SetWindow(WND_WIDTH,WND_HEIGHT);

	gCameraFps->SetPos(eyepos);
	gCameraFps->SetLookAtDir(tmp);

	pCam[0]=(CameraBase*)gCameraFps;
	pCam[1]=(CameraBase*)gCameraModelView;

	InitScene();
}

void SetUpCamera(DWORD fElapsedTimeInMs)
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	pCam[cameraIdx]->FrameUpdate(fElapsedTimeInMs*0.001f);
	pCam[cameraIdx]->LookAt(pRender);
	Hippo_GetSceneManager()->LookAt(pCam[cameraIdx]);
}

//!自定义的消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, void* pUserContext )
{

	return 0;

}



//!自定义的键盘消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
int OnMouse( bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, 
	bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext )
{

	return 0;

}
