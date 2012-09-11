#include "HippoScene.h"
#include "HippoFrameWork.h"
#include "engine_interface.h"

HippoTerrainScene::HippoTerrainScene()
{
	//create empty terrain
	m_pTerrain=Hippo_GetIRender()->CreateTerrain(true);

	H3DI::tTerrainInfo info;
	info.nWidth=128;
	info.nLength=128;

	info.nPageWidth=64;
	info.nPageLength=64;

	info.nPatchWidth=16;
	info.nPatchLength=16;

	info.nLeafWidth=4;
	info.nLeafLength=4;
	info.fGridUnit=4.0f;
	info.fHeightScale=1000.f;

	info.iDataType=0;
	info.iAlphaPrecision=2;


	m_pTerrain->Load(&info);
}

HippoTerrainScene::HippoTerrainScene(const char* terrain_path)
{
	//load terrain from file
	m_pTerrain=Hippo_GetIRender()->CreateTerrain(false);
	bool b=m_pTerrain->Load(terrain_path,Hippo_GetSpeManager());
}

HippoTerrainScene::~HippoTerrainScene()
{
	m_pTerrain->Release();
}

void HippoTerrainScene::Update(float escape)
{
	HippoScene::Update(escape);
	m_pTerrain->Update(escape);
}

H3DI::IScene* HippoTerrainScene::GetH3DScene()
{
	return (H3DI::IScene*)m_pTerrain;
}
void HippoTerrainScene::RestructScene()
{
	m_pTerrain->RestructScene();
}