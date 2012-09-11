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
#include "engine_interface.h"
class CameraBase;
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
	class ITerrain;
	class IScene;

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
	virtual ~HippoScene();

	virtual H3DI::IActor*				CreateActor(bool bmale,int matlod=0);
	virtual H3DI::IActor*				CreateActor_RandomBodyPart(bool bmale,int matlod=0);
	virtual H3DI::IActor*				CreateActor_RandomAllDress(bool bmale,int matlod=0);

	virtual H3DI::IModel*				CreateDml(const char* fn);
	virtual ISpecialEffect*				CreateSpe(const char* fn);
	virtual H3DI::INewShader*			CreateShader(const char* fn,const char* matn);
	virtual H3DI::ISkeletonModel*		CreateChr(const char* fn);
	virtual H3DI::IAvatarSkeletonModel* CreatePet(bool bmale,int matlod=0);

	virtual H3DI::IPrePassLight*		CreateLight(H3DI::LightAffectParam e,H3DI::LIGHT_TYPE t);
	virtual bool						DelLight(H3DI::IPrePassLight* p);


	void CleanScene();
	bool DelActor(H3DI::IActor* p);
	bool DelDml(H3DI::IModel* p);
	bool DelSpe(ISpecialEffect* p);
	bool DelShader(H3DI::INewShader* p);
	bool DelChr(H3DI::ISkeletonModel* p);
	bool DelPet(H3DI::IAvatarSkeletonModel* p);
	bool DelTerrain(H3DI::ITerrain* p);


	virtual void Update(float escape);
	virtual H3DI::IScene* GetH3DScene()=0;

	virtual void RestructScene()=0;
protected:
	
	//各类容器
	IActorCon m_IActorCon;
	IModelCon m_IModelCon;
	INewShaderCon m_INewShaderCon;
	ISpecialEffectCon m_ISpecialEffectCon;
	ISkeletonModelCon m_ISkeletonModelCon;
	IAvatarSkeletonModelCon m_IAvatarSkeletonModelCon;

	IPrePassLightCon* GetLightCon(H3DI::IPrePassLight* p);
	
	//光容器
	IPrePassLightCon m_DirCon[H3DI::LIGHTAFFECTPARAM_END];
	IPrePassLightCon m_PointCon[H3DI::LIGHTAFFECTPARAM_END];
	IPrePassLightCon m_SpotCon[H3DI::LIGHTAFFECTPARAM_END];

private:
};


class HippoLevelScene:public HippoScene
{
public:
	HippoLevelScene();
	~HippoLevelScene();
	virtual void Update(float escape);
	virtual H3DI::IScene* GetH3DScene();
	virtual void RestructScene();
private:
	H3DI::ILevel* m_pLevel;
};


class HippoTerrainScene:public HippoScene
{
public:
	HippoTerrainScene();
	HippoTerrainScene(const char* terrain_path);
	~HippoTerrainScene();
	virtual void Update(float escape);
	virtual H3DI::IScene* GetH3DScene();
	virtual void RestructScene();
private:
	H3DI::ITerrain* m_pTerrain;
};

class HippoSceneManager
{
public:
	HippoSceneManager();
	~HippoSceneManager();

	void LookAt(CameraBase* pCam);
	void PushSceneToRender(float timeMs);
	void UpdateScene(float timeMs);
	HippoLevelScene*	CreateEmptyLevel();
	HippoLevelScene*	LoadSceneFromFile(const char* xmlfile);
	HippoTerrainScene*	CreateEmptyTerrain(unsigned int w,unsigned int h);
	HippoTerrainScene*	LoadTerrainFromFile(const char* terrain_dir);


	bool DelScene(HippoScene* p);
private:
	typedef std::vector<HippoScene*> SceneCon;
	typedef SceneCon::iterator SceneConItr;

	SceneCon m_scenes;
};