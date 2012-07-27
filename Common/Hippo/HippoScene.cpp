#include "HippoScene.h"
#include "engine_interface.h"
#include "idMath/dMathHeader.h"
#include "EffectCore_dx.h"
#include "HippoFrameWork.h"

HippoScene::HippoScene()
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	m_pLevel=pRender->CreateLevel("HippoLevel");
}

HippoScene::~HippoScene()
{
	{
		IActorConItr itr=m_IActorCon.begin();
		while (itr!=m_IActorCon.end())
		{
			(*itr)->Release();
			++itr;
		}
	}
	{
		IAvatarSkeletonModelConItr itr=m_IAvatarSkeletonModelCon.begin();
		while (itr!=m_IAvatarSkeletonModelCon.end())
		{
			(*itr)->Release();
			++itr;
		}
	}

	{
		IModelConItr itr=m_IModelCon.begin();
		while (itr!=m_IModelCon.end())
		{
			(*itr)->Release();
			++itr;
		}
	}
	{
		ISkeletonModelConItr itr=m_ISkeletonModelCon.begin();
		while (itr!=m_ISkeletonModelCon.end())
		{
			(*itr)->Release();
			++itr;
		}
	}

	{
		ISpecialEffectConItr itr=m_ISpecialEffectCon.begin();
		while (itr!=m_ISpecialEffectCon.end())
		{
			(*itr)->Release();
			++itr;
		}
	}
	{
		IPrePassLightConItr itr=m_IPrePassLightCon.begin();
		while (itr!=m_IPrePassLightCon.end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Release();
			++itr;
		}
	}
}

H3DI::IModel*				HippoScene::CreateDml(const char* fn)
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	H3DI::sCreateOp op;
	op.mat_lod=0;
	H3DI::IModel* p=pRender->CreateModel(op,fn);
	p->Update(0);
	m_IModelCon.push_back(p);

	if(m_pLevel)
		m_pLevel->AttachModel((H3DI::IMoveObject*)p,H3DI::LL_DetailObj);
	
	return p;
}

ISpecialEffect*		HippoScene::CreateSpe(const char* fn)
{
	ISpecialEffect* p=Hippo_GetSpeManager()->getSpecialEffect(fn);
	p->update(0);

	m_ISpecialEffectCon.push_back(p);
	if(m_pLevel)
		m_pLevel->AttachModel((H3DI::IMoveObject*)p,H3DI::LL_SpeEffect);
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

	if(m_pLevel)
		m_pLevel->AttachModel((H3DI::IMoveObject*)p,H3DI::LL_DetailObj);

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

	if(m_pLevel)
		m_pLevel->AttachModel((H3DI::IMoveObject*)p,H3DI::LL_Actor);

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

	if(m_pLevel)
		m_pLevel->AttachModel((H3DI::IMoveObject*)p,H3DI::LL_Actor);

	return p;
}

H3DI::IPrePassLight*		HippoScene::CreateDirLight()
{
	return 0;
}
H3DI::IPrePassLight*		HippoScene::CreateSpotLight()
{
	return 0;
}
H3DI::IPrePassLight*		HippoScene::CreatePointLight()
{
	return 0;
}

bool HippoScene::DelActor(H3DI::IActor* p)
{
	return true;
}
bool HippoScene::DelDml(H3DI::IModel* p)
{
	return true;
}
bool HippoScene::DelSpe(ISpecialEffect* p)
{
	return true;
}
bool HippoScene::DelShader(H3DI::INewShader* p)
{
	return true;
}
bool HippoScene::DelChr(H3DI::ISkeletonModel* p)
{
	return true;
}
bool HippoScene::DelPet(H3DI::IAvatarSkeletonModel* p)
{
	return true;
}
bool HippoScene::DelLight(H3DI::IPrePassLight* p)
{
	return true;
}

void HippoScene::PushSceneToRender(float timeMs)
{
	H3DI::IRender* pRender=Hippo_GetIRender();
	if (m_pLevel)
		pRender->PushLevel(m_pLevel);

}


void HippoScene::UpdateScene(float escape)
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
		IPrePassLightConItr itr=m_IPrePassLightCon.begin();
		while (itr!=m_IPrePassLightCon.end())
		{
			H3DI::IPrePassLight* plight=*itr;
			plight->Update(escape);
			++itr;
		}
	}
}

bool HippoScene::LoadSceneFromFile(const char* xmlfile)
{
	return true;
}