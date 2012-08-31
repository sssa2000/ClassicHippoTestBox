#include "HippoScene.h"
#include "engine_interface.h"
#include "idMath/dMathHeader.h"
#include "EffectCore_dx.h"
#include "HippoFrameWork.h"
#include <algorithm>
HippoScene::HippoScene()
{

}

HippoScene::~HippoScene()
{
	CleanScene();
}

void HippoScene::CleanScene()
{
	{
		IActorConItr itr=m_IActorCon.begin();
		while (itr!=m_IActorCon.end())
		{
			(*itr)->Release();
			++itr;
		}
		m_IActorCon.clear();
	}
	{
		IAvatarSkeletonModelConItr itr=m_IAvatarSkeletonModelCon.begin();
		while (itr!=m_IAvatarSkeletonModelCon.end())
		{
			(*itr)->Release();
			++itr;
		}
		m_IAvatarSkeletonModelCon.clear();
	}

	{
		IModelConItr itr=m_IModelCon.begin();
		while (itr!=m_IModelCon.end())
		{
			(*itr)->Release();
			++itr;
		}
		m_IModelCon.clear();
	}
	{
		ISkeletonModelConItr itr=m_ISkeletonModelCon.begin();
		while (itr!=m_ISkeletonModelCon.end())
		{
			(*itr)->Release();
			++itr;
		}
		m_ISkeletonModelCon.clear();
	}

	{
		ISpecialEffectConItr itr=m_ISpecialEffectCon.begin();
		while (itr!=m_ISpecialEffectCon.end())
		{
			(*itr)->Release();
			++itr;
		}
		m_ISpecialEffectCon.clear();
	}
	for(int i=0;i<H3DI::LIGHTAFFECTPARAM_END;++i)
	{
		IPrePassLightConItr itr=m_DirCon[i].begin();
		while (itr!=m_DirCon[i].end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Release();
			++itr;
		}
		m_DirCon[i].clear();
	}
	for(int i=0;i<H3DI::LIGHTAFFECTPARAM_END;++i)
	{
		IPrePassLightConItr itr=m_PointCon[i].begin();
		while (itr!=m_PointCon[i].end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Release();
			++itr;
		}
		m_PointCon[i].clear();
	}
	for(int i=0;i<H3DI::LIGHTAFFECTPARAM_END;++i)
	{
		IPrePassLightConItr itr=m_SpotCon[i].begin();
		while (itr!=m_SpotCon[i].end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Release();
			++itr;
		}
		m_SpotCon[i].clear();
	}

	H3DI::IRender* pRender=Hippo_GetIRender();
	pRender->ClearMaterialLib();
}

H3DI::IModel*				HippoScene::CreateDml(const char* fn)
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	H3DI::sCreateOp op;
	op.mat_lod=0;
	H3DI::IModel* p=pRender->CreateModel(op,fn);
	p->Update(0);
	m_IModelCon.push_back(p);

	GetH3DScene()->AttachModel((H3DI::IMoveObject*)p,H3DI::SL_DetailObj);
	
	return p;
}

ISpecialEffect*		HippoScene::CreateSpe(const char* fn)
{
	ISpecialEffect* p=Hippo_GetSpeManager()->getSpecialEffect(fn);
	p->update(0);

	m_ISpecialEffectCon.push_back(p);
	GetH3DScene()->AttachModel((H3DI::IMoveObject*)p,H3DI::SL_SpecialEffect);
	return p;
}

H3DI::INewShader*			HippoScene::CreateShader(const char* fn,const char* matn)
{
	return 0;
}

H3DI::ISkeletonModel*		HippoScene::CreateChr(const char* fn)
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	H3DI::sCreateOp op;
	op.mat_lod=0;
	H3DI::ISkeletonModel* p=(H3DI::ISkeletonModel*)pRender->CreateModel(op,fn);
	p->Update(0);
	m_ISkeletonModelCon.push_back(p);

	GetH3DScene()->AttachModel((H3DI::IMoveObject*)p,H3DI::SL_DetailObj);

	return p;
}

std::string MakeAutoName(const char* prefix)
{
	static size_t idx=0;
	std::string res=prefix;
	++idx;
	char buff[32];
	_itoa_s(idx,buff,32,10);
	res+=buff;
	return res;
}

H3DI::IAvatarSkeletonModel* HippoScene::CreatePet(bool bmale)
{
	std::string n=MakeAutoName("pet");
	H3DI::IRender* pRender=Hippo_GetIRender();
	H3DI::sCreateOp op;
	op.mat_lod=0;
	H3DI::IAvatarSkeletonModel* p=(H3DI::IAvatarSkeletonModel*)pRender->CreateAvatarSkeletonModel(op,n.c_str(),bmale);
	p->Update(0);
	m_IAvatarSkeletonModelCon.push_back(p);

	GetH3DScene()->AttachModel((H3DI::IMoveObject*)p,H3DI::SL_Actors);

	return p;
}

H3DI::IActor* HippoScene::CreateActor(bool bmale)
{
	std::string n=MakeAutoName("ac");
	H3DI::IRender* pRender=Hippo_GetIRender();
	H3DI::sCreateOp op;
	op.mat_lod=0;
	H3DI::IActor* p=(H3DI::IActor*)pRender->CreateActor(op,n.c_str(),bmale);
	p->Update(0);
	m_IActorCon.push_back(p);

	GetH3DScene()->AttachModel((H3DI::IMoveObject*)p,H3DI::SL_Actors);

	return p;
}
H3DI::IPrePassLight* HippoScene::CreateLight(H3DI::LightAffectParam e,H3DI::LIGHT_TYPE t)
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	H3DI::IPrePassLight* p=pRender->CreatePrePassLight(t);
	p->SetLightAffectParam(e);
	GetLightCon(p)->push_back(p);
	GetH3DScene()->AttachModel((H3DI::IMoveObject*)p,H3DI::SL_Lights);
	return p;
}


bool HippoScene::DelActor(H3DI::IActor* p)
{
	return true;
}
bool HippoScene::DelDml(H3DI::IModel* p)
{
	GetH3DScene()->AttachModel(p,H3DI::SL_DetailObj);
	p->Release();
	m_IModelCon.erase(std::find(m_IModelCon.begin(),m_IModelCon.end(),p));
	return true;
}
bool HippoScene::DelSpe(ISpecialEffect* p)
{
	GetH3DScene()->AttachModel(p,H3DI::SL_SpecialEffect);
	return true;
}
bool HippoScene::DelShader(H3DI::INewShader* p)
{
	return true;
}
bool HippoScene::DelChr(H3DI::ISkeletonModel* p)
{
	GetH3DScene()->AttachModel(p,H3DI::SL_DetailObj);
	return true;
}
bool HippoScene::DelPet(H3DI::IAvatarSkeletonModel* p)
{
	GetH3DScene()->AttachModel(p,H3DI::SL_Actors);
	return true;
}

template<class Container,class Item>
bool DeleteItemFromVector(Container* pCon,Item* p)
{
	Container::iterator itr=std::find(pCon->begin(),pCon->end(),p);
	if(itr!=pCon->end())
	{
		pCon->erase(itr);
		return true;
	}
	return false;
}
IPrePassLightCon* HippoScene::GetLightCon(H3DI::IPrePassLight* p)
{
	H3DI::LightAffectParam e=p->GetLightAffectParam();
	H3DI::LIGHT_TYPE t=p->GetLightType();
	if(t==H3DI::LIGHT_DIR)
		return &m_DirCon[e];
	else if(t==H3DI::LIGHT_POINT)
		return &m_PointCon[e];
	else if(t==H3DI::LIGHT_PROJECT)
		return &m_SpotCon[e];

	return 0;
}




bool HippoScene::DelLight(H3DI::IPrePassLight* p)
{
	GetH3DScene()->DetachModel(p);
	return DeleteItemFromVector(GetLightCon(p),p);
}




void HippoScene::Update(float escape)
{
	H3DI::IRender* pRender=Hippo_GetIRender();

	{
		IActorConItr itr=m_IActorCon.begin();
		while (itr!=m_IActorCon.end())
		{
			(*itr)->UpdateCpuSkin(escape);
			(*itr)->Update(escape);
			++itr;
		}
	}
	{
		IAvatarSkeletonModelConItr itr=m_IAvatarSkeletonModelCon.begin();
		while (itr!=m_IAvatarSkeletonModelCon.end())
		{
			(*itr)->UpdateCpuSkin(escape);
			(*itr)->Update(escape);
			++itr;
		}
	}
	
	{
		IModelConItr itr=m_IModelCon.begin();
		while (itr!=m_IModelCon.end())
		{
			(*itr)->Update(escape);
			++itr;
		}
	}
	{
		ISkeletonModelConItr itr=m_ISkeletonModelCon.begin();
		while (itr!=m_ISkeletonModelCon.end())
		{
			(*itr)->Update(escape);
			++itr;
		}
	}
	
	{
		ISpecialEffectConItr itr=m_ISpecialEffectCon.begin();
		while (itr!=m_ISpecialEffectCon.end())
		{
			(*itr)->update(escape);
			++itr;
		}
	}
	for(int i=0;i<H3DI::LIGHTAFFECTPARAM_END;++i)
	{
		IPrePassLightConItr itr=m_DirCon[i].begin();
		while (itr!=m_DirCon[i].end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Update(escape);
			++itr;
		}
	}

	for(int i=0;i<H3DI::LIGHTAFFECTPARAM_END;++i)
	{
		IPrePassLightConItr itr=m_PointCon[i].begin();
		while (itr!=m_PointCon[i].end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Update(escape);
			++itr;
		}
	}

	for(int i=0;i<H3DI::LIGHTAFFECTPARAM_END;++i)
	{
		IPrePassLightConItr itr=m_SpotCon[i].begin();
		while (itr!=m_SpotCon[i].end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Update(escape);
			++itr;
		}
	}

}
