#include <Windows.h>
#include "HippoFrameWork.h"
#include "engine_interface.h"
#include "idMath/dMathHeader.h"
#include "camera/FPSCamera.h"
#include "camera/ModelViewCamera.h"
#include "HippoTestManager.h"
#include <vector>

bool useDebug=false;
bool autoMoveCamera=false;
const int WND_WIDTH=1024;
const int WND_HEIGHT=768;


void InitApp();
LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, void* pUserContext );
int OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext );
int OnFrameUpdate(DWORD fElapsedTimeInMs, void* pUserContext );
int OnMouse( bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, 
	bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext );
void ChangeDress1(H3DI::IActor* pActor,H3DI::IRender* pRender);
void ChangeDress2(H3DI::IActor* pActor,H3DI::IRender* pRender);


FPSCamera* gCameraFps=0;
ModelViewCamera* gCameraModelView=0;
CameraBase* pCam[2];
int cameraIdx=1;

void SetUpCamera(DWORD fElapsedTimeInMs);


namespace H3DI
{
	class IActor;
	class IMoveObject;
}

///模型容器
typedef std::vector<H3DI::IModel*> ModelContainer;
typedef ModelContainer::iterator ModelContainerItr;

typedef std::vector<H3DI::IActor*> ActorContainer;
typedef ActorContainer::iterator ActorContainerItr;


ModelContainer models;
ActorContainer actors;


H3DI::IActor* gActor=0;
H3DI::IActor* gActor2=0;
H3DI::IAvatarSkeletonModel* gPet=0;


typedef std::vector<H3DI::IPrePassLight*> LppLightContainer;
typedef LppLightContainer::iterator LppLightContainerItr;
LppLightContainer g_lights;

H3DI::ILevel* gLevel=0;

float trans=1.0f;

//!自定义的键盘消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
int OnKeyboard(UINT nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
{
	return HippoTestManager::GetInstance()->ProcessInput(nChar,bKeyDown,bAltDown,bCrtlDown,bShiftDown,pUserContext);
}

void InitLight(H3DI::IRender* pRender)
{
	H3DI::IPrePassLight* light=pRender->CreatePrePassLight(H3DI::LIGHT_DIR);
	light->SetDirection(H3DVec3(1,1,1));
	float c[4]={1,0,0,1};
	light->SetColor(c);
	light->SetLightAffectParam(H3DI::AFFECT_ACTOR_ONLY);
	light->SetIntensity(11.0f);
	light->SetLightEnable(true);
	g_lights.push_back(light);

	gLevel->AttachModel((H3DI::IMoveObject*)light,H3DI::LL_Light);
}


void LoadDML(H3DI::IRender* pRender)
{
	const char* path1="../resources/art/stage/worldmap/model/gs01.dml";
	const char* path2="../resources/art/stage/epaulet/Model/epaulet_wall002.dml";
	H3DI::IModel* pbox=pRender->CreateModel(path1);
	pbox->Update(0);
	models.push_back((H3DI::IModel*)pbox);
	gLevel->AttachModel((H3DI::IMoveObject*)pbox,H3DI::LL_DetailObj);
}

H3DI::IModel* skls[128];
void ChangeDress1(H3DI::IActor* pActor,H3DI::IRender* pRender)
{
	pActor->SetBodyPart("../resources/art/role/bodypart/male/trousers/106031002/106031002.BPT");
	pActor->SetBodyPart("../resources/art/role/bodypart/male/socks/107000000/107000000.BPT");
	pActor->SetBodyPart("../resources/art/role/bodypart/male/shoe/108019002/108019002.BPT");
	pActor->GetSkeletonModels((H3DI::IModel**)(&skls),128);
}

void ChangeDress2(H3DI::IActor* pActor,H3DI::IRender* pRender)
{
	pActor->SetBodyPart("../resources/art/role/bodypart/male/trousers/106028001/106028001.BPT");
	pActor->GetSkeletonModels((H3DI::IModel**)(&skls),128);

}


void LoadActor(H3DI::IRender* pRender)
{
	gActor = (H3DI::IActor*)pRender->CreateActor("male_0", true/*bmale*/);
	//bool res=gActor->SetAdornment(H3DI::ACTOR_ADORNMENT_TAIL,"../resources/art/role/link/female/4112/4112001002/4112001002.spe");
	gActor->Update(0);
	actors.push_back(gActor);
	gLevel->AttachModel((H3DI::IMoveObject*)gActor,H3DI::LL_Actor);
}


void InitScene()
{

}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{

	Hippo_InitFrameWork();
	Hippo_CreateWindow("TestApp",0,hInstance,0,0,WND_WIDTH,WND_HEIGHT);

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
	H3DI::IRender* pRender=Hippo_GetIRender();

	//gLevel->Update(escape*1000);
	{
		ActorContainerItr itr=actors.begin();
		while (itr!=actors.end())
		{
			(*itr)->UpdateCpuSkin(escape);
			(*itr)->Update(escape);
			++itr;
		}
	}


	{
		ModelContainerItr itr=models.begin();
		while (itr!=models.end())
		{
			(*itr)->Update(escape);
			++itr;
		}
	}

	{
		//pRender->BeginSetCurrentLight();
		LppLightContainerItr itr=g_lights.begin();
		while (itr!=g_lights.end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Update(escape);
			//pRender->SetCurrentLight(plight);
			++itr;
		}
		//pRender->EndSetCurrentLight();
	}

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

	if(gLevel)
		pRender->PushLevel(gLevel);


	pRender->Render();

	Hippo_DrawHelpGrid();
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
	pCam[cameraIdx]->LookAt(pRender,gLevel);
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
