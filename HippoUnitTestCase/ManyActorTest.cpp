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
50个人物（25男25女）
人物服装：素体
人物挂件：无

50个人物（25男25女）
人物服装：随机
人物挂件：无

50个人物（25男25女）
人物服装：随机
人物挂件：随机

50个人物（25男25女）
人物服装：随机
人物挂件：随机
50个宠物（25男25女）
宠物服装：素体
宠物挂件：无

50个人物（25男25女）
人物服装：随机
人物挂件：随机
50个宠物（25男25女）
宠物服装：随机
宠物挂件：无


50个人物（25男25女）
人物服装：随机
人物挂件：随机
50个宠物（25男25女）
宠物服装：随机
宠物挂件：随机


*/

class ManyActorTest:public HippoTestCaseBase
{
public:
	HippoLevelScene* m_pScene;
	typedef std::vector<std::pair<H3DI::IActor*,bool> > tActorCon;
	typedef tActorCon::iterator tActorConItr;

	typedef std::vector<std::pair<H3DI::IAvatarSkeletonModel*,bool> > tPetCon;
	typedef tPetCon::iterator tPetConItr;


	tActorCon m_all_actors;
	tPetCon m_all_pets;


	int m_test_step;
	static const int actor_num=30;	//人物总数
	static const int pet_num=30;	//宠物总数
	static const int num_per_row=10;//一排站10个人
	static const int lod0_num=30;	//lod0数量
	static const int lod1_num=0;	//lod0数量
	static const int lod2_num=0;	//lod0数量
	int* m_actor_matlod;	//每个actor的lod级别的数组
	int* m_pet_matlod;		//每个pet的lod级别的数组

	ManyActorTest(const char* case_name) : HippoTestCaseBase(case_name)
	{



		m_actor_matlod=new int[actor_num];
		memset((void*)(m_actor_matlod+0),0,sizeof(int)* actor_num);
		for (int i=lod0_num;i<lod1_num;++i)
		{
			m_actor_matlod[i]=1;
		}

		for (int i=lod0_num+lod1_num;i<lod2_num;++i)
		{
			m_actor_matlod[i]=2;
		}



		m_pet_matlod=new int[pet_num];
		memset((void*)(m_pet_matlod+0),0,sizeof(int)* lod0_num);
		for (int i=lod0_num;i<lod1_num;++i)
		{
			m_pet_matlod[i]=1;
		}

		for (int i=lod0_num+lod1_num;i<lod2_num;++i)
		{
			m_pet_matlod[i]=2;
		}
	}
	void InitActor()
	{
		Hippo_GetIRender()->OnCommandLine("SetEngineConfig ErrorBoxFlag ture1");
		//male
		bool bmale=true;
		int count=0;
		
		for (int i=0;i<actor_num;++i)
		{
			bmale=(count%2==0);
			int matlod=m_actor_matlod[i];
			H3DI::IActor* pactor=m_pScene->CreateActor(bmale,matlod);
			float x_pos=-num_per_row+2*(i%num_per_row);
			float y_pos=floorf((float)abs(i)/(float)num_per_row);
			pactor->SetPosition(H3DVec3(x_pos,y_pos,0));
			m_all_actors.push_back(std::make_pair(pactor,bmale));
			//
			Hippo_WriteConsole(CC_WHITE,"创建1个人物成功 bmale=%d",bmale);

			++count;
		}

		Hippo_GetIRender()->OnCommandLine("SetEngineConfig ErrorBoxFlag ture");
	}
	
	void InitPet()
	{
		Hippo_GetIRender()->OnCommandLine("SetEngineConfig ErrorBoxFlag ture1");

		//male
		bool bmale=true;
		int count=0;
		for (int i=0;i<pet_num;++i)
		{
			bmale=(count%2==0);
			int matlod=m_actor_matlod[i];
			H3DI::IAvatarSkeletonModel* pet=m_pScene->CreatePet(bmale,matlod);

			float x_pos=-num_per_row+2*(i%num_per_row);
			float y_pos=6+floorf((float)abs(i)/(float)num_per_row); //宠物排在人的后面
			pet->SetPosition(H3DVec3(x_pos,y_pos,0));
			m_all_pets.push_back(std::make_pair(pet,bmale));
			Hippo_WriteConsole(CC_WHITE,"创建1个宠物成功 bmale=%d",bmale);

			++count;
		}

		Hippo_GetIRender()->OnCommandLine("SetEngineConfig ErrorBoxFlag ture");
	}

	void RandomActorBodypart()
	{
		tActorConItr itr=m_all_actors.begin();
		tActorConItr itrend=m_all_actors.end();
		while (itr!=itrend)
		{
			H3DI::IActor* p=itr->first;
			ActorUtil::RandomBodypart(p,itr->second);
			Hippo_WriteConsole(CC_WHITE,"Actor RandomBodypart成功 bmale=%d",itr->second);
			++itr;
		}
	}

	void RandomActorLink()
	{
		tActorConItr itr=m_all_actors.begin();
		tActorConItr itrend=m_all_actors.end();
		while (itr!=itrend)
		{
			H3DI::IActor* p=itr->first;
			ActorUtil::RandomLink(p,itr->second);
			Hippo_WriteConsole(CC_WHITE,"Actor RandomLink成功 bmale=%d",itr->second);
			++itr;
		}
	}

	void RandomPetBodypart()
	{
		tPetConItr itr=m_all_pets.begin();
		tPetConItr itrend=m_all_pets.end();
		while (itr!=itrend)
		{
			H3DI::IAvatarSkeletonModel* p=itr->first;
			ActorUtil::RandomBodypart(p,itr->second);
			Hippo_WriteConsole(CC_WHITE,"Pet RandomBodypart成功 bmale=%d",itr->second);
			++itr;
		}
	}

	void RandomPetLink()
	{
		tPetConItr itr=m_all_pets.begin();
		tPetConItr itrend=m_all_pets.end();
		while (itr!=itrend)
		{
			H3DI::IAvatarSkeletonModel* p=itr->first;
			ActorUtil::RandomLink(p,itr->second);
			Hippo_WriteConsole(CC_WHITE,"Pet RandomLink成功 bmale=%d",itr->second);
			++itr;
		}
	}

	void UpdateTestStep()
	{
		switch(m_test_step)
		{
		case 1:
			{
				InitActor();
				break;
			}
		case 2:
			{
				RandomActorBodypart();
				break;
			}
		case 3:
			{
				RandomActorLink();
				break;
			}
		case 4:
			{
				InitPet();
				break;
			}
		case 5:
			{
				RandomPetBodypart();
				break;
			}
		case 6:
			{
				RandomPetLink();
				break;
			}
		default:
			return;
		}
	}
	//
	virtual bool InitScene()
	{
		Hippo_GetIRender()->OnCommandLine("SetEngineConfig OpenPhysX ture1");
		Hippo_GetIRender()->OnCommandLine("SetEngineConfig CastShadow ture1");
		Hippo_GetIRender()->OnCommandLine("SetEngineConfig usePostProcess ture1");

		m_pScene=Hippo_GetSceneManager()->CreateEmptyLevel();
		//create actor
		Hippo_GetIRender()->OpenActionLib("../resources/art/role/actions/role.xml");

		ActorUtil::InitActorDress("../resources/config/shared/item/dress.xml");
		ActorUtil::InitPetDress("../resources/config/shared/item/petdress.xml");

		m_test_step=0;
		m_state=CASE_EXECING;
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
			case VK_RIGHT:
				{
					++m_test_step;
					UpdateTestStep();
					return 1;
				}
			}
		}
		return 0;
	}

private:
	static HippoTestCaseBase* const testcase_;
};

ADD_TESTCASE("ACTOR_TEST",ManyActorTest)