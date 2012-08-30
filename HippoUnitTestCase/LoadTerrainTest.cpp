#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"
#include "RefCountCompare.h"
#include "idMath/dMathHeader.h"
#include "engine_interface.h"

using namespace std;

/*
测试逻辑：
1、从文件加载一个地形
*/

class LoadTerrainTest:public HippoTestCaseBase
{
public:
	HippoTerrainScene* m_pTerrainScene;
	LoadTerrainTest(const char* case_name) : HippoTestCaseBase(case_name){}
	//
	virtual bool InitScene()
	{
		m_pTerrainScene=Hippo_GetSceneManager()->LoadTerrainFromFile("../resources/art/scene/scene/terrain01");
		H3DI::IPrePassLight* plight=m_pTerrainScene->CreateDirLight();
		float c[4]={1,1,1,1};
		plight->SetColor(c);
		plight->SetDirection(H3DVec3(1,1,1));

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
		return 0;
	}

private:
	static HippoTestCaseBase* const testcase_;
};

ADD_TESTCASE(LoadTerrainTest)