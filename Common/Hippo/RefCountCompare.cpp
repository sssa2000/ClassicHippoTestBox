#include "RefCountCompare.h"
#include "engine_interface.h"
#include "HippoFrameWork.h"

HippoResStateSnapShot::HippoResStateSnapShot(int count,HIPPO_RESTYPE t)
{
	m_pData=new _SingleResState[count];
	m_res_count=count;
	m_restype=t;
}

void HippoResStateSnapShot::Release()
{
	delete[] m_pData;
	delete this;
}




//得到当前时刻引擎的某种资源（已完成加载的资源）的状态
HippoResStateSnapShot* RefCountCompare::GetResState(HIPPO_RESTYPE t)
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	int mng_type=t;
	void* pRes=pRender->QueryInfo(4,(void*)&mng_type,0,0,0,0); //获取该类资源当前时刻的数目
	int count=(int)(*((int*)pRes));
	
	HippoResStateSnapShot* pResInfo=new HippoResStateSnapShot(count,t);		//分配空间
	pRender->QueryInfo(5,(void*)&mng_type,(void*)(pResInfo->m_pData),0,0,0);//获取每个资源的信息

	return pResInfo;
}

//比较两个快照是否相等
bool RefCountCompare::SnapShotEqual(HippoResStateSnapShot* l,HippoResStateSnapShot* r)
{
	//首先比较数量
	if(l->m_res_count != r->m_res_count)
		return false;

	//容器内应该是有序的
	for (int i=0;i<l->m_res_count;++i)
	{
		_SingleResState* left=l->m_pData+i;
		_SingleResState* right=r->m_pData+i;

		int name_r=strcmp(left->m_name,right->m_name);
		bool refc_r=left->m_ref == right->m_ref;

		if(name_r!=0 || !refc_r) //名字和ref 只要有一个不等 就认为不同
			return false;
	}
	return true;
}