#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"
#include "RefCountCompare.h"
#include "idMath/dMathHeader.h"
#include "engine_interface.h"

/*
测试逻辑，主要测试赛马的人物光是否正确
目前规定的是Actor接受3个灯光，但是不固定类型

按1：添加一个方向光
按2：减少一个方向光

按3：添加一个点光源
按4：减少一个点光源

按5：添加一个聚光灯
按6：减少一个聚光灯
*/

class ActorLightProjHTest:public HippoTestCaseBase
{
public:
	H3DI::IActor* m_pActor;
	HippoScene* m_pTerrainScene;
	std::vector<H3DI::IPrePassLight*> m_dir_lights;
	std::vector<H3DI::IPrePassLight*> m_pot_lights;
	std::vector<H3DI::IPrePassLight*> m_spt_lights;

	ActorLightProjHTest(const char* case_name) : HippoTestCaseBase(case_name){}

	virtual bool InitScene()
	{
		//m_pTerrainScene=Hippo_GetSceneManager()->LoadTerrainFromFile("../resources/art/scene/scene/terrain01");

 		m_pTerrainScene=(HippoScene*)Hippo_GetSceneManager()->CreateEmptyLevel();
// 		H3DI::IPrePassLight* plight=m_pTerrainScene->CreateLight(H3DI::AFFECT_SCENE_ONLY,H3DI::LIGHT_DIR);
// 		float c[4]={1,1,1,1};
// 		plight->SetColor(c);
// 		plight->SetDirection(H3DVec3(1,1,1));


		//create actor
		Hippo_GetIRender()->OpenActionLib("../resources/art/role/actions/role.xml");
		m_pActor=m_pTerrainScene->CreateActor(false);

		m_pTerrainScene->RestructScene();
		m_state=CASE_EXECING;
		return true;
	}

	//
	virtual bool CleanUpScene()
	{
		Hippo_GetSceneManager()->DelScene(m_pTerrainScene);
		m_pTerrainScene=0;

		return true;
	}

	//!自定义的键盘消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
	virtual int ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
	{
		if( bKeyDown )
		{
			switch( nChar )
			{
			case VK_RETURN:
				{
					//测试结束
					m_state=CASE_END_EXECING;
					return 1;
				}
			case '1':
				{
					//添加一个方向光
					H3DI::IPrePassLight* pl=m_pTerrainScene->CreateLight(H3DI::AFFECT_ACTOR_ONLY,H3DI::LIGHT_DIR);
					float c[4]={1,0,0,1};
					pl->SetColor(c);
					pl->SetDirection(H3DVec3(1,1,1));
					m_dir_lights.push_back(pl);
					return 1;
				}
			case '2':
				{
					//减少一个方向光
					if(m_dir_lights.empty())
						return 1;

					H3DI::IPrePassLight* p=m_dir_lights.back();
					m_dir_lights.pop_back();
					m_pTerrainScene->DelLight(p);
					return 1;
				}
			case '3':
				{
					//添加一个聚光灯
					H3DI::IPrePassLight* pl=m_pTerrainScene->CreateLight(H3DI::AFFECT_ACTOR_ONLY,H3DI::LIGHT_PROJECT);
					float c[4]={0,1,0,1};
					pl->SetColor(c);
					pl->SetDirection(H3DVec3(0,-1,2));
					pl->SetPosition(H3DVec3(0,-1,2));
					pl->SetRange(5.f,10.f);
					m_spt_lights.push_back(pl);
					return 1;
				}
			case '4':
				{
					//添加一个聚光灯
					if(m_spt_lights.empty())
						return 1;

					H3DI::IPrePassLight* p=m_spt_lights.back();
					m_spt_lights.pop_back();
					m_pTerrainScene->DelLight(p);
					return 1;
				}
			}
		}
		return 0;
	}

	virtual bool Render()
	{
		return true;
	}
private:
	static HippoTestCaseBase* const testcase_;
};

ADD_TESTCASE("LIGHT_TEST",ActorLightProjHTest)