#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"
#include "RefCountCompare.h"
#include "idMath/dMathHeader.h"
#include "engine_interface.h"
#include "ActorUtil.h"

using namespace std;

/*
测试逻辑：
创建一个人物
按一次->键执行一次随机换装
按一次<-键执行一次随机换挂件
*/
class ActorChangeDressTest:public HippoTestCaseBase
{
public:
	HippoLevelScene* m_pScene;
	H3DI::IActor* m_pActor;
	bool m_bActorSex;

	ActorChangeDressTest(const char* case_name) : HippoTestCaseBase(case_name){}

	//
	virtual bool InitScene()
	{
		m_pScene=Hippo_GetSceneManager()->CreateEmptyLevel();

		//create actor
		Hippo_GetIRender()->OpenActionLib("../resources/art/role/actions/role.xml");
		ActorUtil::InitActorDress("../resources/config/shared/item/dress.xml");
		m_bActorSex=false;
		m_pActor=m_pScene->CreateActor(m_bActorSex);
		//m_pActor->SetAdornment((H3DI::EActorAdornmentPosition)5,"../resources/art/role/link/female/4115/4115012002/4115012002.spe");
		m_pScene->RestructScene();

		m_state=CASE_EXECING;
		Hippo_WriteConsole(CC_RED,"InitScene Done");
		return true;
	}

	//
	virtual bool CleanUpScene()
	{
		Hippo_GetSceneManager()->DelScene(m_pScene);
		m_pScene=0;

		return true;
	}

	virtual bool Render()
	{
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
					m_state=CASE_END_EXECING;
					return 1;
				}
			case VK_LEFT:
				{
					ActorUtil::RandomBodypart(m_pActor,m_bActorSex);
					return 1;
				}
			case VK_RIGHT:
				{
					//m_pActor->SetAdornment((H3DI::EActorAdornmentPosition)5,"../resources/art/role/link/female/4115/4115012002/4115012002.spe");
					ActorUtil::RandomLink(m_pActor,m_bActorSex);
					return 1;
				}
			}
		}
		return 0;
	}

private:
	static HippoTestCaseBase* const testcase_;
};

ADD_TESTCASE("ACTOR_TEST",ActorChangeDressTest)