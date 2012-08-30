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
	{
		IPrePassLightConItr itr=m_DirCon.begin();
		while (itr!=m_DirCon.end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Release();
			++itr;
		}
		m_DirCon.clear();
	}
	{
		IPrePassLightConItr itr=m_PointCon.begin();
		while (itr!=m_PointCon.end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Release();
			++itr;
		}
		m_PointCon.clear();
	}
	{
		IPrePassLightConItr itr=m_SpotCon.begin();
		while (itr!=m_SpotCon.end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Release();
			++itr;
		}
		m_SpotCon.clear();
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

H3DI::IPrePassLight*		HippoScene::CreateDirLight()
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	H3DI::IPrePassLight* p=pRender->CreatePrePassLight(H3DI::LIGHT_DIR);
	m_DirCon.push_back(p);
	GetH3DScene()->AttachModel((H3DI::IMoveObject*)p,H3DI::SL_Lights);
	
	return p;
}
H3DI::IPrePassLight*		HippoScene::CreateSpotLight()
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	H3DI::IPrePassLight* p=pRender->CreatePrePassLight(H3DI::LIGHT_POINT);
	m_PointCon.push_back(p);
	GetH3DScene()->AttachModel((H3DI::IMoveObject*)p,H3DI::SL_Lights);
	
	return p;
}
H3DI::IPrePassLight*		HippoScene::CreatePointLight()
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	H3DI::IPrePassLight* p=pRender->CreatePrePassLight(H3DI::LIGHT_PROJECT);
	m_SpotCon.push_back(p);
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
void DeleteItemFromVector(Container* pCon,Item* p)
{
	Container::iterator itr=std::find(pCon->begin(),pCon->end(),p);
	if(itr!=pCon->end())
	{
		pCon->erase(itr);
	}
}
bool HippoScene::DelDirLight(H3DI::IPrePassLight* p)
{
	GetH3DScene()->AttachModel(p,H3DI::SL_Lights);
	DeleteItemFromVector(&m_DirCon,p);
	return true;
}
bool HippoScene::DelPointLight(H3DI::IPrePassLight* p)
{
	GetH3DScene()->AttachModel(p,H3DI::SL_Lights);
	DeleteItemFromVector(&m_PointCon,p);
	return true;
}
bool HippoScene::DelSpotLight(H3DI::IPrePassLight* p)
{
	GetH3DScene()->AttachModel(p,H3DI::SL_Lights);
	DeleteItemFromVector(&m_SpotCon,p);
	return true;
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
	{
		IPrePassLightConItr itr=m_DirCon.begin();
		while (itr!=m_DirCon.end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Update(escape);
			++itr;
		}
	}
	{
		IPrePassLightConItr itr=m_PointCon.begin();
		while (itr!=m_PointCon.end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Update(escape);
			++itr;
		}
	}
	{
		IPrePassLightConItr itr=m_SpotCon.begin();
		while (itr!=m_SpotCon.end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Update(escape);
			++itr;
		}
	}

}
