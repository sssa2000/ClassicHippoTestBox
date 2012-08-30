#include "HippoScene.h"
#include "HippoFrameWork.h"
#include "camera\CameraBase.h"
#include <algorithm>
#include "engine_interface.h"


HippoSceneManager::HippoSceneManager()
{

}
HippoSceneManager::~HippoSceneManager()
{
	SceneConItr itr=m_scenes.begin();
	SceneConItr itrend=m_scenes.end();
	while (itr!=itrend)
	{
		HippoScene* p=(*itr);
		delete p;
		p=0;
		++itr;
	}
	m_scenes.clear();
}

void HippoSceneManager::PushSceneToRender(float timeMs)
{
	H3DI::IRender* prender=Hippo_GetIRender();
	SceneConItr itr=m_scenes.begin();
	SceneConItr itrend=m_scenes.end();
	while (itr!=itrend)
	{
		H3DI::IScene* p=(*itr)->GetH3DScene();
		prender->PushScene(p);
		++itr;
	}
}
void HippoSceneManager::UpdateScene(float timeMs)
{
	SceneConItr itr=m_scenes.begin();
	SceneConItr itrend=m_scenes.end();
	while (itr!=itrend)
	{
		H3DI::IScene* p=(*itr)->GetH3DScene();
		p->Update(timeMs);
		++itr;
	}
}

HippoLevelScene* HippoSceneManager::LoadSceneFromFile(const char* xmlfile)
{
	return 0;
}

HippoTerrainScene*	HippoSceneManager::CreateEmptyTerrain(unsigned int w,unsigned int h)
{
	HippoTerrainScene* p=new HippoTerrainScene();
	m_scenes.push_back(p);
	return p;
}


HippoTerrainScene*	HippoSceneManager::LoadTerrainFromFile(const char* terrain_dir)
{
	HippoTerrainScene* p=new HippoTerrainScene(terrain_dir);
	m_scenes.push_back(p);
	return p;
}

HippoLevelScene* HippoSceneManager::CreateEmptyLevel()
{
	HippoLevelScene* p=new HippoLevelScene;
	m_scenes.push_back(p);
	return p;
}

bool HippoSceneManager::DelScene(HippoScene* p)
{
	SceneConItr itr=std::find(m_scenes.begin(),m_scenes.end(),p);
	if(itr!=m_scenes.end())
	{
		delete p;
		m_scenes.erase(itr);
		return true;
	}
	return false;
}

void HippoSceneManager::LookAt(CameraBase* pCam)
{

	H3DI::IRender* prender=Hippo_GetIRender();
	SceneConItr itr=m_scenes.begin();
	SceneConItr itrend=m_scenes.end();
	while (itr!=itrend)
	{
		H3DI::IScene* pLevel=(*itr)->GetH3DScene();
		pLevel->LookAt(pCam->GetPos(),pCam->GetPos()+pCam->GetViewAtDir(),pCam->GetUp());
		pLevel->UpdateCamera();
		++itr;
	}

}