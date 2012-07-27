/********************************************************************
	created:	2012/07/22
	created:	22:7:2012   23:27
	filename: 	F:\EngineX52MT\多线程测试用例代码\Common\Hippo\HippoScene.h
	file path:	F:\EngineX52MT\多线程测试用例代码\Common\Hippo
	file base:	HippoScene
	file ext:	h
	author:		sssa2000
	
	purpose:	场景数据保存类
*********************************************************************/
#pragma once
#include <vector>
#include <string>
#include <map>

namespace H3DI
{
	class IActor;
	class IModel;
	class INewShader;
	class ISkeletonModel;
	class IAvatarSkeletonModel;
	class ISkeletonModel;
	class IPrePassLight;
	class ILevel;
}
class ISpecialEffect;

typedef std::vector<H3DI::IActor*> IActorCon;
typedef IActorCon::iterator IActorConItr;

typedef std::vector<H3DI::IModel*> IModelCon;
typedef IModelCon::iterator IModelConItr;

typedef std::vector<ISpecialEffect*> ISpecialEffectCon;
typedef ISpecialEffectCon::iterator ISpecialEffectConItr;

typedef std::vector<H3DI::INewShader*> INewShaderCon;
typedef INewShaderCon::iterator INewShaderConItr;

typedef std::vector<H3DI::ISkeletonModel*> ISkeletonModelCon;
typedef ISkeletonModelCon::iterator ISkeletonModelConItr;

typedef std::vector<H3DI::IAvatarSkeletonModel*> IAvatarSkeletonModelCon;
typedef IAvatarSkeletonModelCon::iterator IAvatarSkeletonModelConItr;

typedef std::vector<H3DI::IPrePassLight*> IPrePassLightCon;
typedef IPrePassLightCon::iterator IPrePassLightConItr;


class HippoScene
{
public:
	HippoScene();
	~HippoScene();

	H3DI::IActor*				CreateActor(bool bmale);
	H3DI::IModel*				CreateDml(const char* fn);
	ISpecialEffect*		CreateSpe(const char* fn);
	H3DI::INewShader*			CreateShader(const char* fn,const char* matn);
	H3DI::ISkeletonModel*		CreateChr(const char* fn);
	H3DI::IAvatarSkeletonModel* CreatePet(bool bmale);
	H3DI::IPrePassLight*		CreateDirLight();
	H3DI::IPrePassLight*		CreateSpotLight();
	H3DI::IPrePassLight*		CreatePointLight();

	bool DelActor(H3DI::IActor* p);
	bool DelDml(H3DI::IModel* p);
	bool DelSpe(ISpecialEffect* p);
	bool DelShader(H3DI::INewShader* p);
	bool DelChr(H3DI::ISkeletonModel* p);
	bool DelPet(H3DI::IAvatarSkeletonModel* p);
	bool DelLight(H3DI::IPrePassLight* p);

	void PushSceneToRender(float timeMs);
	void UpdateScene(float timeMs);

	bool LoadSceneFromFile(const char* xmlfile);

	H3DI::ILevel* GetLevel(){return m_pLevel;}
protected:
	
	//各类容器
	IActorCon m_IActorCon;
	IModelCon m_IModelCon;
	INewShaderCon m_INewShaderCon;
	IPrePassLightCon m_IPrePassLightCon;
	ISpecialEffectCon m_ISpecialEffectCon;
	ISkeletonModelCon m_ISkeletonModelCon;
	IAvatarSkeletonModelCon m_IAvatarSkeletonModelCon;

	H3DI::ILevel* m_pLevel;
private:
};