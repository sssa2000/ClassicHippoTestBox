#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"

using namespace std;

class ActorTest1:public HippoTestCaseBase
{
public:
	ActorTest1(const char* case_name) : HippoTestCaseBase(case_name){}
	//
	virtual bool InitScene()
	{
		const char* path1="../resources/art/stage/actorcreate001/model/actorcreate001_wall002.dml";
		HippoScene* pScene=Hippo_GetScene();
		pScene->CreateDml(path1);
		m_state=CASE_EXECING;
		return true;
	}

	//
	virtual bool CleanUpScene()
	{
		return true;
	}

	virtual bool Render()
	{
		Hippo_WriteConsole(CC_GREEN,"ActorTest1 Begin Run");
		//m_state=CASE_END_EXECING;
		Hippo_WriteConsole(CC_GREEN,"ActorTest1 End Run");
		return true;
	}


private:
	static HippoTestCaseBase* const testcase_; 
};

ADD_TESTCASE(ActorTest1)