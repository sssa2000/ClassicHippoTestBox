/********************************************************************
	created:	2012/07/22
	created:	22:7:2012   15:13
	filename: 	F:\EngineX52MT\多线程测试用例代码\Common\HippoTestManager\HippoTestManager.h
	file path:	F:\EngineX52MT\多线程测试用例代码\Common\HippoTestManager
	file base:	HippoTestManager
	file ext:	h
	author:		sssa2000
	
	purpose:	测试用例管理器，简化google test的代码
*********************************************************************/
#pragma once

#include <vector>
#include <string>

enum CASE_STATE
{
	CASE_INIT=0, //初始化
	CASE_BEFORE_EXECING,		//
	CASE_EXECING,
	CASE_END_EXECING,
};
//用例基类
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

	// 执行测试案例的方法，返回true表示已经完成
	virtual bool Render() = 0;


	//!自定义的键盘消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
	virtual int ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext )
	{
		return 0;
	}
	CASE_STATE GetState(){return m_state;}
	const char* GetTestCaseName(){return testcase_name.c_str();}
protected:
	CASE_STATE m_state;

	std::string testcase_name; // 测试案例名称
};


//测试框架实现
class HippoTestManager
{
public:
	HippoTestManager();
	~HippoTestManager();

	// 单件
	static HippoTestManager* GetInstance(); 

	// 注册测试案例
	HippoTestCaseBase* RegisterTestCase(HippoTestCaseBase* pCase);

	// 执行单元测试，在frame begin和end之间调用
	int RunAllTest();

	//!自定义的键盘消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
	virtual int ProcessInput(unsigned int nChar, bool bKeyDown, bool bAltDown,bool bCrtlDown,bool bShiftDown, void* pUserContext );
protected:
	unsigned int m_TestCaseIdx;//当前运行到哪个测试用例
	HippoTestCaseBase* m_pCurrentTestCase; // 记录当前执行的测试案例
	std::vector<HippoTestCaseBase*> m_all_testcase;
};


//宏声明
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


//写测试用例的时候使用这个宏即可
#define HIPPOTEST(testcase_type,testcase_name) \
	HIPPO_TEST_(testcase_type,testcase_name)



#define ADD_TESTCASE(testcase_name)\
	HippoTestCaseBase* const testcase_name \
	::testcase_ = HippoTestManager::GetInstance()->RegisterTestCase( \
	new testcase_name(#testcase_name));