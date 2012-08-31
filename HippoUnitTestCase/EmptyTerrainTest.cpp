#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"
#include "RefCountCompare.h"
#include "engine_interface.h"

using namespace std;

/*
测试逻辑：
1、加载一个空地形
*/

class EmptyTerrainTest:public HippoTestCaseBase
{
public:
	HippoTerrainScene* m_pTerrainScene;
	EmptyTerrainTest(const char* case_name) : HippoTestCaseBase(case_name){}
	//
	virtual bool InitScene()
	{
		m_pTerrainScene=Hippo_GetSceneManager()->CreateEmptyTerrain(128,128);
		
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
			}
		}
		return 0;
	}

private:
	static HippoTestCaseBase* const testcase_;
};

ADD_TESTCASE("TERRAIN_TEST",EmptyTerrainTest)