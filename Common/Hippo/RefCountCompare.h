/********************************************************************
	created:	2012/07/28
	created:	28:7:2012   9:05
	filename: 	F:\Git\ClassicHippoTestBox\Common\Hippo\RefCountCompare.h
	file path:	F:\Git\ClassicHippoTestBox\Common\Hippo
	file base:	RefCountCompare
	file ext:	h
	author:		sssa2000
	
	purpose:	1、获取某一时刻的引擎的资源引用计数的状态
				2、比较任意两个时刻资源引用计数状态的不同
*********************************************************************/
#pragma once
#include <vector>

//资源类型的定义
enum HIPPO_RESTYPE
{
	HIPPO_MAT_RES,
	HIPPO_TPL_RES,
	HIPPO_TEX_RES
};

//单个资源状态
struct _SingleResState
{
	char m_name[256];
	int m_ref;
};


//表示某一时刻的某种类型所有资源的状态
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


	//得到当前时刻引擎的某种资源（已完成加载的资源）的状态
	static HippoResStateSnapShot* GetResState(HIPPO_RESTYPE t);

	//比较两个快照是否相等
	static bool SnapShotEqual(HippoResStateSnapShot* l,HippoResStateSnapShot* r);
};