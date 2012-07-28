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




//�õ���ǰʱ�������ĳ����Դ������ɼ��ص���Դ����״̬
HippoResStateSnapShot* RefCountCompare::GetResState(HIPPO_RESTYPE t)
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	int mng_type=t;
	void* pRes=pRender->QueryInfo(4,(void*)&mng_type,0,0,0,0); //��ȡ������Դ��ǰʱ�̵���Ŀ
	int count=(int)(*((int*)pRes));
	
	HippoResStateSnapShot* pResInfo=new HippoResStateSnapShot(count,t);		//����ռ�
	pRender->QueryInfo(5,(void*)&mng_type,(void*)(pResInfo->m_pData),0,0,0);//��ȡÿ����Դ����Ϣ

	return pResInfo;
}

//�Ƚ����������Ƿ����
bool RefCountCompare::SnapShotEqual(HippoResStateSnapShot* l,HippoResStateSnapShot* r)
{
	//���ȱȽ�����
	if(l->m_res_count != r->m_res_count)
		return false;

	//������Ӧ���������
	for (int i=0;i<l->m_res_count;++i)
	{
		_SingleResState* left=l->m_pData+i;
		_SingleResState* right=r->m_pData+i;

		int name_r=strcmp(left->m_name,right->m_name);
		bool refc_r=left->m_ref == right->m_ref;

		if(name_r!=0 || !refc_r) //���ֺ�ref ֻҪ��һ������ ����Ϊ��ͬ
			return false;
	}
	return true;
}