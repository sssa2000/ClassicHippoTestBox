#include "HippoScene.h"
#include "engine_interface.h"
#include "idMath/dMathHeader.h"

H3DI::IModel*				HippoScene::CreateDml(const char* fn)
{
	return 0;
}
H3DI::ISpecialEffect*		HippoScene::CreateSpe(const char* fn)
{
	return 0;
}
H3DI::INewShader*			HippoScene::CreateShader(const char* fn,const char* matn)
{
	return 0;
}
H3DI::ISkeletonModel*		HippoScene::CreateChr(const char* fn)
{
	return 0;
}
H3DI::IAvatarSkeletonModel* HippoScene::CreatePet()
{
	return 0;
}
H3DI::IPrePassLight*		HippoScene::CreateDirLight()
{
	return 0;
}
H3DI::IPrePassLight*		HippoScene::CreateSpotLight()
{
	return 0;
}
H3DI::IPrePassLight*		HippoScene::CreatePointLight()
{
	return 0;
}

bool HippoScene::DelActor(H3DI::IActor* p)
{
	return true;
}
bool HippoScene::DelDml(H3DI::IModel* p)
{
	return true;
}
bool HippoScene::DelSpe(H3DI::ISpecialEffect* p)
{
	return true;
}
bool HippoScene::DelShader(H3DI::INewShader* p)
{
	return true;
}
bool HippoScene::DelChr(H3DI::ISkeletonModel* p)
{
	return true;
}
bool HippoScene::DelPet(H3DI::IAvatarSkeletonModel* p)
{
	return true;
}
bool HippoScene::DelLight(H3DI::IPrePassLight* p)
{
	return true;
}

void HippoScene::RenderScene()
{
	
}
void HippoScene::UpdateScene(float timeMs)
{
	
}

bool HippoScene::LoadSceneFromFile(const char* xmlfile)
{
	return true;
}