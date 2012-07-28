/********************************************************************
	created:	2012/07/22
	created:	22:7:2012   15:13
	filename: 	F:\EngineX52MT\���̲߳�����������\Common\HippoTestManager\HippoTestManager.h
	file path:	F:\EngineX52MT\���̲߳�����������\Common\HippoTestManager
	file base:	HippoTestManager
	file ext:	h
	author:		sssa2000
	
	purpose:	������������������google test�Ĵ���
*********************************************************************/
#pragma once

#include <vector>
#include <string>

enum CASE_STATE
{
	CASE_INIT=0, //��ʼ��
	CASE_BEFORE_EXECING,		//
	CASE_EXECING,
	CASE_END_EXECING,
};
//��������
class HippoTestCaseBase
{
public:
	HippoTestCaseBase(const char* case_name) : testcase_name(case_name)
	{
		m_state=CASE_INIT;
	}

	//
	virtual bool InitScene(){return true;}

	//
	virtual bool CleanUpScene(){return true;}

	// ִ�в��԰����ķ���������true��ʾ�Ѿ����
	virtual bool Render() = 0;


	//!�Զ���ļ�����Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
	virtual int ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
	{
		return 0;
	}
	CASE_STATE GetState(){return m_state;}
	const char* GetTestCaseName(){return testcase_name.c_str();}
protected:
	CASE_STATE m_state;

	std::string testcase_name; // ���԰�������
};


//���Կ��ʵ��
class HippoTestManager
{
public:
	HippoTestManager();
	~HippoTestManager();

	// ����
	static HippoTestManager* GetInstance(); 

	// ע����԰���
	HippoTestCaseBase* RegisterTestCase(HippoTestCaseBase* pCase);

	// ִ�е�Ԫ���ԣ���frame begin��end֮�����
	int RunAllTest();

	//!�Զ���ļ�����Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
	virtual int ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext );
protected:
	unsigned int m_TestCaseIdx;//��ǰ���е��ĸ���������
	HippoTestCaseBase* m_pCurrentTestCase; // ��¼��ǰִ�еĲ��԰���
	std::vector<HippoTestCaseBase*> m_all_testcase;
};


//������
#define TESTCASE_NAME(testcase_type,testcase_name) \
	testcase_name##_TEST

#define HIPPO_TEST_(testcase_type,testcase_name) \
class TESTCASE_NAME(testcase_type,testcase_name) : public HippoTestCaseBase \
{ \
public: \
	TESTCASE_NAME(testcase_type,testcase_name)(const char* case_name) : HippoTestCaseBase(case_name){}; \
	virtual void Run(); \
private: \
	static HippoTestCaseBase* const testcase_; \
}; \
	\
	HippoTestCaseBase* const TESTCASE_NAME(testcase_type,testcase_name) \
	::testcase_ = HippoTestManager::GetInstance()->RegisterTestCase( \
	new TESTCASE_NAME(testcase_type,testcase_name)(#testcase_name)); \
	void TESTCASE_NAME(testcase_type,testcase_name)::Run()


//д����������ʱ��ʹ������꼴��
#define HIPPOTEST(testcase_type,testcase_name) \
	HIPPO_TEST_(testcase_type,testcase_name)



#define ADD_TESTCASE(testcase_name)\
	HippoTestCaseBase* const testcase_name \
	::testcase_ = HippoTestManager::GetInstance()->RegisterTestCase( \
	new testcase_name(#testcase_name));