#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"
#include "RefCountCompare.h"
#include "engine_interface.h"

using namespace std;

/*
测试逻辑：
1、加载一个模型，记录引擎当前引用计数
2、查看模型，按回车键删除模型，记录引擎当前引用计数
3、比较两个引用计数是否相等
*/

class DmlTest1:public HippoTestCaseBase
{
public:
	HippoLevelScene* m_pLevelScene;

	HippoResStateSnapShot* m_pMatSnapShot0;
	HippoResStateSnapShot* m_pMatSnapShot1;

	HippoResStateSnapShot* m_pTplSnapShot0;
	HippoResStateSnapShot* m_pTplSnapShot1;

	HippoResStateSnapShot* m_pTexSnapShot0;
	HippoResStateSnapShot* m_pTexSnapShot1;

	DmlTest1(const char* case_name) : HippoTestCaseBase(case_name){}
	//
	virtual bool InitScene()
	{
		m_pMatSnapShot0=RefCountCompare::GetResState(HIPPO_MAT_RES);
		m_pTplSnapShot0=RefCountCompare::GetResState(HIPPO_TPL_RES);
		m_pTexSnapShot0=RefCountCompare::GetResState(HIPPO_TEX_RES);

		const char* path1="../resources/art/stage/actorcreate001/model/actorcreate001_wall002.dml";
		m_pLevelScene=Hippo_GetSceneManager()->CreateEmptyLevel();
		m_pLevelScene->CreateDml(path1);
		m_state=CASE_EXECING;
		return true;
	}

	void CompareRef()
	{
		bool bmat=RefCountCompare::SnapShotEqual(m_pMatSnapShot0,m_pMatSnapShot1);
		bool btpl=RefCountCompare::SnapShotEqual(m_pTplSnapShot0,m_pTplSnapShot1);
		bool btex=RefCountCompare::SnapShotEqual(m_pTexSnapShot0,m_pTexSnapShot1);

		if(bmat)
			Hippo_WriteConsole(CC_GREEN,"Mat引用计数相等，测试通过");
		else
			Hippo_WriteConsole(CC_RED,	"Mat引用计数不等，测试不通过");

		if(btpl)
			Hippo_WriteConsole(CC_GREEN,"Tpl引用计数相等，测试通过");
		else
			Hippo_WriteConsole(CC_RED,	"Tpl引用计数不等，测试不通过");

		if(btex)
			Hippo_WriteConsole(CC_GREEN,"Texture引用计数相等，测试通过");
		else
			Hippo_WriteConsole(CC_RED,	"Texture引用计数不等，测试不通过");
	}
	//
	virtual bool CleanUpScene()
	{
		
		Hippo_GetSceneManager()->DelScene(m_pLevelScene);
		m_pLevelScene=0;

		m_pMatSnapShot1=RefCountCompare::GetResState(HIPPO_MAT_RES);
		m_pTplSnapShot1=RefCountCompare::GetResState(HIPPO_TPL_RES);
		m_pTexSnapShot1=RefCountCompare::GetResState(HIPPO_TEX_RES);

		CompareRef();

		m_pMatSnapShot0->Release();
		m_pMatSnapShot1->Release();
		m_pTplSnapShot0->Release();
		m_pTplSnapShot1->Release();
		m_pTexSnapShot0->Release();
		m_pTexSnapShot1->Release();

		return true;
	}

	virtual bool Render()
	{
		return true;
	}

	//!自定义的键盘消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
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

ADD_TESTCASE("DML_TEST",DmlTest1)