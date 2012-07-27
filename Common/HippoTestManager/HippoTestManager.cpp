#include "HippoTestManager.h"
#include <iostream>

HippoTestManager::HippoTestManager()
{
	m_pCurrentTestCase=0;
	m_TestCaseIdx=0;
}

HippoTestManager::~HippoTestManager()
{
}

// ����
HippoTestManager* HippoTestManager::GetInstance()
{
	static HippoTestManager instance;
	return &instance;
}

// ע����԰���
HippoTestCaseBase* HippoTestManager::RegisterTestCase(HippoTestCaseBase* pCase)
{
	m_all_testcase.push_back(pCase);
	return pCase;
}

// ִ�е�Ԫ����
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
			m_pCurrentTestCase->InitScene();
		}
		else if (s==CASE_BEFORE_EXECING)
		{
			m_pCurrentTestCase->CleanUpScene();
		}
		else if (s==CASE_EXECING)
		{
			m_pCurrentTestCase->Render();
			break;
		}
		else if (s==CASE_END_EXECING)
		{
			//next
			++m_TestCaseIdx;
		}

	}

	return 1;
}


//!�Զ���ļ�����Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
int HippoTestManager::ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
{
	if(!m_pCurrentTestCase)
		return 0;

	return m_pCurrentTestCase->ProcessInput(nChar,bKeyDown,bAltDown,bCrtlDown,bShiftDown,pUserContext);
}