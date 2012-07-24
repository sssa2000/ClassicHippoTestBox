#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
using namespace std;

class ActorTest1:public HippoTestCaseBase
{
public:
	ActorTest1(const char* case_name) : HippoTestCaseBase(case_name){}
	virtual bool Run()
	{
		Hippo_WriteConsole(CC_GREEN,"ActorTest1 Begin Run");
		m_bHasBegin=true;
		m_bHasFinish=true;
		Hippo_WriteConsole(CC_GREEN,"ActorTest1 End Run");
		return true;
	}


private:
	static HippoTestCaseBase* const testcase_; 
};

ADD_TESTCASE(ActorTest1)