#include "HippoScene.h"
#include "HippoFrameWork.h"
#include "engine_interface.h"

extern std::string MakeAutoName(const char* prefix);


HippoLevelScene::HippoLevelScene()
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	m_pLevel=pRender->CreateLevel(MakeAutoName("Lv").c_str());
}
HippoLevelScene::~HippoLevelScene()
{
	m_pLevel->Release();
	m_pLevel=0;
}
void HippoLevelScene::Update(float escape)
{
	HippoScene::Update(escape);
	m_pLevel->Update(escape);
}
H3DI::IScene* HippoLevelScene::GetH3DScene()
{
	return (H3DI::IScene*)m_pLevel;
}

void HippoLevelScene::RestructScene()
{
	m_pLevel->RestructScene();
}