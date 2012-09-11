#include "HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>

//ִֻ��ĳһ�������������������Ҫ�뱣�ָñ���Ϊ��
const char* ONLY_EXEC_A_TEST="ManyActorTest";

//ִֻ��ĳһ�����͵Ĳ����������������Ҫ�뱣�ָñ���Ϊ��
const char* ONLY_EXEC_TYPE="";


//����true��ʾ�������
//����false��ʾ������Ӹ�����
bool _filter(const char* type,HippoTestCaseBase* pCase)
{
	if(ONLY_EXEC_A_TEST && strlen(ONLY_EXEC_A_TEST)>0)
	{
		if(strcmp(ONLY_EXEC_A_TEST,pCase->GetTestCaseName())==0)
			return true;
		return false;
	}

	if(ONLY_EXEC_TYPE && strlen(ONLY_EXEC_TYPE)>0)
	{
		if(strcmp(ONLY_EXEC_TYPE,type)==0)
			return true;
		return false;
	}

	return true;
}


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

// ����
HippoTestManager* HippoTestManager::GetInstance()
{
	static HippoTestManager instance;
	return &instance;
}

// ע����԰���
HippoTestCaseBase* HippoTestManager::RegisterTestCase(const char* type,HippoTestCaseBase* pCase)
{
	//�����������������ɾ��
	if(!_filter(type,pCase))
	{
		delete pCase;
		return 0;
	}

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


//!�Զ���ļ�����Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
int HippoTestManager::ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
{
	if(!m_pCurrentTestCase)
		return 0;

	return m_pCurrentTestCase->ProcessInput(nChar,bKeyDown,bAltDown,bCrtlDown,bShiftDown,pUserContext);
}