#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"
#include "RefCountCompare.h"
#include "idMath/dMathHeader.h"
#include "engine_interface.h"

/*
�����߼�����Ҫ���������������Ƿ���ȷ
Ŀǰ�涨����Actor����3���ƹ⣬���ǲ��̶�����

��1�����һ�������
��2������һ�������

��3�����һ�����Դ
��4������һ�����Դ

��5�����һ���۹��
��6������һ���۹��
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

	//!�Զ���ļ�����Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
	virtual int ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
	{
		if( bKeyDown )
		{
			switch( nChar )
			{
			case VK_RETURN:
				{
					//���Խ���
					m_state=CASE_END_EXECING;
					return 1;
				}
			case '1':
				{
					//���һ�������
					H3DI::IPrePassLight* pl=m_pTerrainScene->CreateLight(H3DI::AFFECT_ACTOR_ONLY,H3DI::LIGHT_DIR);
					float c[4]={1,0,0,1};
					pl->SetColor(c);
					pl->SetDirection(H3DVec3(1,1,1));
					m_dir_lights.push_back(pl);
					return 1;
				}
			case '2':
				{
					//����һ�������
					if(m_dir_lights.empty())
						return 1;

					H3DI::IPrePassLight* p=m_dir_lights.back();
					m_dir_lights.pop_back();
					m_pTerrainScene->DelLight(p);
					return 1;
				}
			case '3':
				{
					//���һ���۹��
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
					//���һ���۹��
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