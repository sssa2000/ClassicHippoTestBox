#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"
#include "RefCountCompare.h"
#include "engine_interface.h"

using namespace std;

/*
�����߼���
1������һ���յ���
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

	//!�Զ���ļ�����Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
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