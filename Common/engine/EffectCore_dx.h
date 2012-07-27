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
///主要函数：setActor(),unSetActor(),update(),render()
class ISpecialEffect : public H3DI::IMoveObject{
public:
	/// 获得当前特效的对应文件名称
	virtual const char*  getName() = 0;
	/**
	*设定特效的发动者。可有多个发动者（联合技）
	*/
	virtual void  setActor(EffectActor eActor[], int actorCount, int type = 0) = 0;

	virtual void  setObject(H3DI::ISkeletonModel* actor) = 0;

	///
	///清除特效的发动者，这样可以将该特效直接用于其他发动者
	virtual void  unsetActor() = 0;

	/// 
	/// 得到特效的状态
	virtual int  getState() = 0;

	/// 
	/// 得到特效的当前时间
	virtual float  getCurrentTime() = 0;

	/// 
	///设置特效的状态
	virtual void  setState(int state) = 0;

	/// 
	/// 设置整个特效的透明度
	virtual void  setTransparence(float trans) = 0;

	///
	/// 设置特效是否投射阴影
	virtual void setCastShadow(bool bCastShadow) = 0;

	///
	///交还该特效给特效管理器
	virtual void  release() = 0;

	///
	///判断特效是否有actor
	virtual bool  hasActor() = 0;

	///
	///得到特效的总长度，返回TIME_MAX表示循环特效
	virtual float  getAnimationLength() = 0;

	///
	///更新特效，默认更新时间为间隔时间
	virtual void  update(float interval, bool isinterval = true) = 0;

	///
	///渲染特效
	virtual void  NewRender(int pipeType) = 0;
	/// 
	/// 重设特效状态
	virtual void  reset() = 0;

	// 初始化当前特效
	virtual bool  Initialize() = 0;

	// 设置3个轴的缩放系数
	virtual void _stdcall setScaleInfo(float x, float y, float z) = 0;



	//////////////////////////////////////////////////////////////////////////
	////////////////   以下接口主要供编辑器使用   ////////////////////////////
	////////////////   运行时请勿调用，否则会出错 ////////////////////////////

	///
	///保存特效到文件(主要供编辑器使用,运行时请勿调用，否则会出错)
	virtual bool  save(const char* filename) = 0;

	///
	///删除特效并释放内存空间(主要供编辑器使用,运行时请勿调用，否则会出错)
	virtual void  destroy() = 0;


	// 彻底删除
	virtual void  clean() = 0;


	///获得本物体使用的显存
	unsigned int GetVideoMemUse()
	{
		return 0;
	}
	///获得性能数据
	void* GetPerfData(H3DI::MODEL_PERFDATA_TYPE t)
	{
		return 0;
	}

	///从内存设置一个材质实例给模型的一个网格，返回1表示成功，0表示找不到该网格
	int SetMeshMaterialTemplateFromMemByName(const char* meshName, void* pXmlDoc)
	{
		return 1;
	}

	/*参数：
	0：等同于ReloadAll
	1：Reload Geometry
	2：Reload 材质（包括贴图）
	3：Reload 贴图

	返回值-1为失败，大于0的数表示reload了几张贴图
	*/
	int ReloadFromDisk(int reloadContent)
	{
		return 0;
	}

	/// 设置此特效为角色相关特效
	virtual void	SetIsActorEffect(bool b) = 0;

	//!预生成fx
	virtual int PreGenFx(H3DI::IFxInfo* p)=0;

	//////////////////////////////////////////////////////////////////////////
	// 设置和获取特效播放时间比率
	// 在特效Update的时候处理将传入的时间t处理为t*ratio
	//! 目前由特效编辑器编辑时根据美术的保存类型设置
	//! 同时在特效编辑器编辑状态下此参数并不起作用，只在客户端状态下才起作用
	virtual void SetSpeLengthRatio(float fRatio) = 0;
	virtual float GetSpeLengthRatio() = 0;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 多线程编辑特效
	//////////////////////////////////////////////////////////////////////////
	virtual int			GetTreeNodeCnt() { return 0; }
	virtual ITreeNode*	FindTreeNode(const char* pTreeNodeName) { return 0; }
	virtual ITreeNode*	GetTreeNode(int idx) { return 0; }
	virtual ITreeNode*	CreateTreeNode(const char* name,int nodeType,IEModel* model = 0) { return 0; }
	virtual void		RemoveTreeNode(const char* name) {}
	//////////////////////////////////////////////////////////////////////////
	// 多线程编辑特效
	//////////////////////////////////////////////////////////////////////////
};


struct Editor_SPEMatInfo
{
	char speFilename[256];
	char matFilename[256];
	char matInsName[256];
};

//////////////////////////////////////////////////////////////////////////
///主要接口:getSpecialEffect()，所有特效都将通过该接口得到
class ISpecialEffectManager{
public:
	//////////////////////////////////////////////////////////////////////////
	//!
	// 通过engine_interface里的CreateSpe和CreateSpeAsyn创建特效
	//! 
	/// 根据名称获得一个特效
	virtual ISpecialEffect*  getSpecialEffect(const char* name, bool binary = false) = 0;
	virtual ISpecialEffect*  getSpecialEffect(H3DI::sCreateOp& op,const char* name, bool binary = false) = 0;

	//////////////////////////////////////////////////////////////////////////
	/// 得到粒子等效果的管理器
	virtual IParticleSystemManager*  getParticleManager() = 0;

	//////////////////////////////////////////////////////////////////////////
	/// 删除所有特效（不常用）
	virtual void  deleteAllSpecialEffects() = 0;

	/// 创建子节点对应的各种资源（编辑器调用）
	virtual IEModel*  createEModel(int type, int createinfo, const char* url, const char* extrainfo = 0) = 0;


	virtual void  beginRenderParticle() = 0;
	virtual void  endRenderParticle() = 0;


	//由于特效没有移植完毕,所以需要兼容老版本的保存和加载
	virtual void  setEditModel(bool b)=0;

	// 供编辑器获取特效使用的材质信息
	// 传入特效文件名和一个指向有count个元素的数组的指针
	// 返回实际的元素个数，从0开始
	// 空间由调用者分配
	virtual int Editor_GetMatFromSPEFile(const char* filename, Editor_SPEMatInfo* matInfo, unsigned int count) = 0;

protected:
	virtual ~ISpecialEffectManager(){}	
};
#endif
