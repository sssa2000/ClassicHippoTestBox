#include "HippoTestManager/HippoTestManager.h"
#include "HippoFrameWork.h"
#include <iostream>
#include "HippoScene.h"
#include "RefCountCompare.h"
#include "engine_interface.h"

using namespace std;

/*
�����߼���
1������һ��ģ�ͣ���¼���浱ǰ���ü���
2���鿴ģ�ͣ����س���ɾ��ģ�ͣ���¼���浱ǰ���ü���
3���Ƚ��������ü����Ƿ����
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
			Hippo_WriteConsole(CC_GREEN,"Mat���ü�����ȣ�����ͨ��");
		else
			Hippo_WriteConsole(CC_RED,	"Mat���ü������ȣ����Բ�ͨ��");

		if(btpl)
			Hippo_WriteConsole(CC_GREEN,"Tpl���ü�����ȣ�����ͨ��");
		else
			Hippo_WriteConsole(CC_RED,	"Tpl���ü������ȣ����Բ�ͨ��");

		if(btex)
			Hippo_WriteConsole(CC_GREEN,"Texture���ü�����ȣ�����ͨ��");
		else
			Hippo_WriteConsole(CC_RED,	"Texture���ü������ȣ����Բ�ͨ��");
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

	//!�Զ���ļ�����Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
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