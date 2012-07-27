#ifndef __EFFECTCORE_H__
#define __EFFECTCORE_H__
//#include "IPrerequisites.h"

#include "engine_interface.h"

namespace H3DI {
	class ISoundSource;
	class I_CameraManager;
	class iFxInfo;

}
namespace H3D
{
	class MaterialLayer;
}
const float TIME_MAX = 999998.f;

enum EFFECT_STATE{
	EFFECT_NEEDACTOR = (1<<1),
	EFFECT_HASACTOR = (1<<2),
	EFFECT_USEMATRIX = (1<<4),
	EFFECT_EDITING = (1<<5),
	EFFECT_CONCAT_PARENT = (1<<6),
	EFFECT_CONCAT_CHILD = (1<<7),
	EFFECT_ACTIVATED = (1<<8),
	EFFECT_HIDE = (1<<9),
};

enum NODE_STATE{
	NODE_UNACTIVATED = 1,
	NODE_PLAYING,
	NODE_FINISHED,
};

enum ACTOR_TYPE
{
	EFFECT_ACTOR,
	CHAIN_ACTOR,
};

#define NameArrayWidth 1024
#define NameArrayLength 128


class IParticleSystemManager;
class IParticleEffect;
class IEModel;

class ITreeNode;

struct ObjManipulator
{
};

struct EffectActor
{
	H3DI::IModel* actor;
	ObjManipulator* obj;
};

//////////////////////////////////////////////////////////////////////////
///��Ҫ������setActor(),unSetActor(),update(),render()
class ISpecialEffect : public H3DI::IMoveObject{
public:
	/// ��õ�ǰ��Ч�Ķ�Ӧ�ļ�����
	virtual const char*  getName() = 0;
	/**
	*�趨��Ч�ķ����ߡ����ж�������ߣ����ϼ���
	*/
	virtual void  setActor(EffectActor eActor[], int actorCount, int type = 0) = 0;

	virtual void  setObject(H3DI::ISkeletonModel* actor) = 0;

	///
	///�����Ч�ķ����ߣ��������Խ�����Чֱ����������������
	virtual void  unsetActor() = 0;

	/// 
	/// �õ���Ч��״̬
	virtual int  getState() = 0;

	/// 
	/// �õ���Ч�ĵ�ǰʱ��
	virtual float  getCurrentTime() = 0;

	/// 
	///������Ч��״̬
	virtual void  setState(int state) = 0;

	/// 
	/// ����������Ч��͸����
	virtual void  setTransparence(float trans) = 0;

	///
	/// ������Ч�Ƿ�Ͷ����Ӱ
	virtual void setCastShadow(bool bCastShadow) = 0;

	///
	///��������Ч����Ч������
	virtual void  release() = 0;

	///
	///�ж���Ч�Ƿ���actor
	virtual bool  hasActor() = 0;

	///
	///�õ���Ч���ܳ��ȣ�����TIME_MAX��ʾѭ����Ч
	virtual float  getAnimationLength() = 0;

	///
	///������Ч��Ĭ�ϸ���ʱ��Ϊ���ʱ��
	virtual void  update(float interval, bool isinterval = true) = 0;

	///
	///��Ⱦ��Ч
	virtual void  NewRender(int pipeType) = 0;
	/// 
	/// ������Ч״̬
	virtual void  reset() = 0;

	// ��ʼ����ǰ��Ч
	virtual bool  Initialize() = 0;

	// ����3���������ϵ��
	virtual void _stdcall setScaleInfo(float x, float y, float z) = 0;



	//////////////////////////////////////////////////////////////////////////
	////////////////   ���½ӿ���Ҫ���༭��ʹ��   ////////////////////////////
	////////////////   ����ʱ������ã��������� ////////////////////////////

	///
	///������Ч���ļ�(��Ҫ���༭��ʹ��,����ʱ������ã���������)
	virtual bool  save(const char* filename) = 0;

	///
	///ɾ����Ч���ͷ��ڴ�ռ�(��Ҫ���༭��ʹ��,����ʱ������ã���������)
	virtual void  destroy() = 0;


	// ����ɾ��
	virtual void  clean() = 0;


	///��ñ�����ʹ�õ��Դ�
	unsigned int GetVideoMemUse()
	{
		return 0;
	}
	///�����������
	void* GetPerfData(H3DI::MODEL_PERFDATA_TYPE t)
	{
		return 0;
	}

	///���ڴ�����һ������ʵ����ģ�͵�һ�����񣬷���1��ʾ�ɹ���0��ʾ�Ҳ���������
	int SetMeshMaterialTemplateFromMemByName(const char* meshName, void* pXmlDoc)
	{
		return 1;
	}

	/*������
	0����ͬ��ReloadAll
	1��Reload Geometry
	2��Reload ���ʣ�������ͼ��
	3��Reload ��ͼ

	����ֵ-1Ϊʧ�ܣ�����0������ʾreload�˼�����ͼ
	*/
	int ReloadFromDisk(int reloadContent)
	{
		return 0;
	}

	/// ���ô���ЧΪ��ɫ�����Ч
	virtual void	SetIsActorEffect(bool b) = 0;

	//!Ԥ����fx
	virtual int PreGenFx(H3DI::IFxInfo* p)=0;

	//////////////////////////////////////////////////////////////////////////
	// ���úͻ�ȡ��Ч����ʱ�����
	// ����ЧUpdate��ʱ���������ʱ��t����Ϊt*ratio
	//! Ŀǰ����Ч�༭���༭ʱ���������ı�����������
	//! ͬʱ����Ч�༭���༭״̬�´˲������������ã�ֻ�ڿͻ���״̬�²�������
	virtual void SetSpeLengthRatio(float fRatio) = 0;
	virtual float GetSpeLengthRatio() = 0;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// ���̱߳༭��Ч
	//////////////////////////////////////////////////////////////////////////
	virtual int			GetTreeNodeCnt() { return 0; }
	virtual ITreeNode*	FindTreeNode(const char* pTreeNodeName) { return 0; }
	virtual ITreeNode*	GetTreeNode(int idx) { return 0; }
	virtual ITreeNode*	CreateTreeNode(const char* name,int nodeType,IEModel* model = 0) { return 0; }
	virtual void		RemoveTreeNode(const char* name) {}
	//////////////////////////////////////////////////////////////////////////
	// ���̱߳༭��Ч
	//////////////////////////////////////////////////////////////////////////
};


struct Editor_SPEMatInfo
{
	char speFilename[256];
	char matFilename[256];
	char matInsName[256];
};

//////////////////////////////////////////////////////////////////////////
///��Ҫ�ӿ�:getSpecialEffect()��������Ч����ͨ���ýӿڵõ�
class ISpecialEffectManager{
public:
	//////////////////////////////////////////////////////////////////////////
	//!
	// ͨ��engine_interface���CreateSpe��CreateSpeAsyn������Ч
	//! 
	/// �������ƻ��һ����Ч
	virtual ISpecialEffect*  getSpecialEffect(const char* name, bool binary = false) = 0;
	virtual ISpecialEffect*  getSpecialEffect(H3DI::sCreateOp& op,const char* name, bool binary = false) = 0;

	//////////////////////////////////////////////////////////////////////////
	/// �õ����ӵ�Ч���Ĺ�����
	virtual IParticleSystemManager*  getParticleManager() = 0;

	//////////////////////////////////////////////////////////////////////////
	/// ɾ��������Ч�������ã�
	virtual void  deleteAllSpecialEffects() = 0;

	/// �����ӽڵ��Ӧ�ĸ�����Դ���༭�����ã�
	virtual IEModel*  createEModel(int type, int createinfo, const char* url, const char* extrainfo = 0) = 0;


	virtual void  beginRenderParticle() = 0;
	virtual void  endRenderParticle() = 0;


	//������Чû����ֲ���,������Ҫ�����ϰ汾�ı���ͼ���
	virtual void  setEditModel(bool b)=0;

	// ���༭����ȡ��Чʹ�õĲ�����Ϣ
	// ������Ч�ļ�����һ��ָ����count��Ԫ�ص������ָ��
	// ����ʵ�ʵ�Ԫ�ظ�������0��ʼ
	// �ռ��ɵ����߷���
	virtual int Editor_GetMatFromSPEFile(const char* filename, Editor_SPEMatInfo* matInfo, unsigned int count) = 0;

protected:
	virtual ~ISpecialEffectManager(){}	
};
#endif
