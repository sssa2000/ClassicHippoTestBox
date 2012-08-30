#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"
#include "RefCountCompare.h"
#include "idMath/dMathHeader.h"
#include "engine_interface.h"

using namespace std;

/*
�����߼���
1�����ļ�����һ������
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

	//!�Զ���ļ�����Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
	virtual int ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
	{
		return 0;
	}

private:
	static HippoTestCaseBase* const testcase_;
};

ADD_TESTCASE(LoadTerrainTest)