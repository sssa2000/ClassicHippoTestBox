/********************************************************************
	created:	2012/07/28
	created:	28:7:2012   9:05
	filename: 	F:\Git\ClassicHippoTestBox\Common\Hippo\RefCountCompare.h
	file path:	F:\Git\ClassicHippoTestBox\Common\Hippo
	file base:	RefCountCompare
	file ext:	h
	author:		sssa2000
	
	purpose:	1����ȡĳһʱ�̵��������Դ���ü�����״̬
				2���Ƚ���������ʱ����Դ���ü���״̬�Ĳ�ͬ
*********************************************************************/
#pragma once
#include <vector>

//��Դ���͵Ķ���
enum HIPPO_RESTYPE
{
	HIPPO_MAT_RES,
	HIPPO_TPL_RES,
	HIPPO_TEX_RES
};

//������Դ״̬
struct _SingleResState
{
	char m_name[256];
	int m_ref;
};


//��ʾĳһʱ�̵�ĳ������������Դ��״̬
struct HippoResStateSnapShot
{
	HippoResStateSnapShot(int count,HIPPO_RESTYPE t);
	void Release();
	HIPPO_RESTYPE m_restype;
	int m_res_count;
	_SingleResState* m_pData;
	
};


class RefCountCompare
{
public:


	//�õ���ǰʱ�������ĳ����Դ������ɼ��ص���Դ����״̬
	static HippoResStateSnapShot* GetResState(HIPPO_RESTYPE t);

	//�Ƚ����������Ƿ����
	static bool SnapShotEqual(HippoResStateSnapShot* l,HippoResStateSnapShot* r);
};