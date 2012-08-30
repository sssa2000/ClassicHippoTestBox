#include "HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>

HippoTestManager::HippoTestManager()
{
	m_pCurrentTestCase=0;
	m_TestCaseIdx=0;
}

HippoTestManager::~HippoTestManager()
{
	TestCaseConItr itr=m_all_testcase.begin();
	while (itr!=m_all_testcase.end())
	{
		HippoTestCaseBase* p=*itr;
		delete p;
		p=0;
		++itr;
	}
	m_all_testcase.clear();
}

// 单件
HippoTestManager* HippoTestManager::GetInstance()
{
	static HippoTestManager instance;
	return &instance;
}

// 注册测试案例
HippoTestCaseBase* HippoTestManager::RegisterTestCase(HippoTestCaseBase* pCase)
{
	m_all_testcase.push_back(pCase);
	return pCase;
}

// 执行单元测试
int HippoTestManager::RunAllTest()
{
	int nTestResult = 1;
	int nPassed=0;
	int nFailed=0;
	while(m_TestCaseIdx<m_all_testcase.size())
	{
		HippoTestCaseBase* testcase = m_all_testcase.at(m_TestCaseIdx);
		m_pCurrentTestCase = testcase;
		CASE_STATE s=m_pCurrentTestCase->GetState();
		if(s==CASE_INIT)
		{
			Hippo_WriteConsole(CC_BLUE,"*****************Bein A Test:%s*****************",m_pCurrentTestCase->GetTestCaseName());
			m_pCurrentTestCase->InitScene();
		}
		else if (s==CASE_BEFORE_EXECING)
		{
			
		}
		else if (s==CASE_EXECING)
		{
			m_pCurrentTestCase->Render();
			break;
		}
		else if (s==CASE_END_EXECING)
		{
			m_pCurrentTestCase->CleanUpScene();
			Hippo_WriteConsole(CC_BLUE,"*****************End A Test:%s*****************",m_pCurrentTestCase->GetTestCaseName());
			++m_TestCaseIdx;
		}

	}

	return 1;
}


//!自定义的键盘消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
int HippoTestManager::ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
{
	if(!m_pCurrentTestCase)
		return 0;

	return m_pCurrentTestCase->ProcessInput(nChar,bKeyDown,bAltDown,bCrtlDown,bShiftDown,pUserContext);
}