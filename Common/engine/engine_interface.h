#ifndef __render__model__
#define __render__model__

#pragma warning(disable : 4819)

#include <windows.h>


class H3DMat4;
class H3DVec3;
class H3DVec4;
class H3DQuat;
class ISpecialEffectManager;
class ISpecialEffect;

namespace H3DI
{
	class IFxInfo;

	struct sCreateOp
	{
		int geo_lod; //几何lod级别
		int mat_lod; //材质lod级别
	};

	enum OBJ_TYPE
	{
		IOBJ = 0,
		IMODEL ,
		ISKLMODEL ,
		ILIGHT,
	};
	enum GLOBAL_PERFDATA_TYPE
	{
		//fps (unsigned int)
		FPS=0,
		//本帧绘制的所有三角形数量 (unsigned int)
		TOTAL_TRIANGLE_NUM,
		//本帧执行的所有dip (unsigned int)
		TOTAL_DIP_NUM,
		//本帧参与绘制的光源数量 (unsigned int)
		TOTAL_LIGHT_NUM,
		///引擎使用的Texture数量 (unsigned int)
		TOTAL_TEXTURE_NUM,
		//引擎使用的rt数量 (unsigned int)
		TOTAL_RT_NUM,
		//场景中模型数量(unsigned int)
		TOTAL_MODEL_NUM,
		//场景中所有Fx切换次数(unsigned int)
		TOTAL_FX_CHANGES,
		//场景中所有BeginPass调用次数(unsigned int)
		TOTAL_BEGINPASS_NUM,
		//场景中所有ShaderConst提交次数：(unsigned int)
		TOTAL_SC_NUM,
		//场景中私有ShaderConst提交次数：(unsigned int)
		TOTAL_PRIVATE_SC_NUM,
		//场景中所有透明物体的个数(unsigned int)
		TOTAL_TRANSPARENT_NUM,
		//场景中所有透明物体的m_DIP(unsigned int)
		TOTAL_TRANSPARENT_DIP,

		//引擎使用的内存总数 (unsigned int 字节)
		TOTAL_MEMORY_USEAGE,
		//引擎使用的显存总数 (unsigned int 字节)
		TOTAL_VIDEO_MEMORY_USAGE,
		//当前场景的填充率 (float)
		FILLRATE_PERCENT,
		//当前的顶点cache命中百分比 (float)
		VERTEX_CACHE_PERCENT,
		//当前的纹理cache命中百分比 (float)
		TEX_CACHE_PERCENT,
		//GPU 空闲的时间百分比 (float)
		GPU_IDLE_PERCENT,
		//渲染状态切换次数(unsigned int)
		TOTAL_RS_CHANGENUM,
		//Batches：(unsigned int)
		TOTAL_BATCHES,
		//Number of objects in video memory(unsigned int)
		TOTAL_WORKINGSET,
		//Number of objects in video memory (unsigned int字节)
		TOTAL_WORKINGSET_BYTES,
		//Total number of managed objects.(unsigned int)
		TOTAL_MANAGED,
		//Total number of bytes of managed objects.(unsigned int字节)
		TOTAL_MANAGED_BYTES,

		GLOBAL_PERFDATA_TYPE_END
	};

	enum MODEL_PERFDATA_TYPE
	{
		//该模型的三角形数量 (unsigned int)
		TRIANGLE_NUM=0,
		//该模型的dip数量 (unsigned int)
		DIP_NUM,
		//该模型的的vertex shader指令数 (unsigned int)
		VS_INS_NUM,
		//该模型的geometry shader指令数 (unsigned int)
		GS_INS_NUM,
		//该模型的pixel shader指令数 (unsigned int)
		PS_INS_NUM,
		//该模型收到的灯光数量 (unsigned int)
		LIGHT_NUM,
		//该模型使用的贴图数(unsigned int )
		TEXTURE_NUM,
		//该模型绘制用了多少个fx
		FX_NUM,
		//该模型绘制用了多少个shaderconst
		SC_NUM,
		//该模型占用的内存数(unsigned int 字节)
		MEMORY_USAGE,
		//该模型占用的显存数(unsigned int 字节)
		VIDEOMEM_USAGE,

		MODEL_PERFDATA_TYPE_END
	};

	enum EFILLMODE
	{
		FILL_NORMAL = 0,			//普通模式
		FILL_WIREFRAME,				//线框模式
		FILL_NORMAL_WIREFRAME,		//普通+线框模式
		FILL_LIGHTMAP,				//当有LIGHTMAP时，只看LightMap的效果
		FILL_REALTIME_LIGHTING,				//只看光照效果
	};

	class IObject
	{
	public:
		virtual void					Release()=0;
		virtual bool					IsValid()const=0;

		virtual void                    SetUserPtr(void*)=0;
		virtual void*                  GetUserPtr(void)const = 0;

		//	virtual OBJ_TYPE				GetType()=0;
	};



	class IAnimation : public IObject
	{
	public:
		virtual	void					clear()= 0;


		virtual const H3DVec3&	get_pos(void)const = 0;
		virtual const H3DQuat&	get_rot(void)const = 0 ;

		virtual void					update(float interval)=0;
		virtual void					set_passtime(float *time_passed)=0;
		virtual int						getrotnum()const=0;
		virtual int						getposnum()const=0;


		virtual void					getposkey(int i, H3DVec3& pos)=0;
		virtual void					getrotkey(int i, H3DQuat& rot)=0 ;

		virtual float					get_animtime()const=0;
		virtual float					get_curtime()const=0;
		virtual int						get_curposfrm()const=0;
		virtual int						get_currotfrm()const=0;
		virtual void					reset()=0;
		virtual void					setloop(int lp)=0;
	};



	class IAction : public IObject
	{
	public:
		virtual							~IAction()=0{};
		virtual const char*				GetName()=0;
		virtual IAnimation*				GetAnimation(unsigned int nBone)=0;
		virtual float					GetAnimationTime()=0;
		virtual void					SetAnimationRunningTime(float fAnimTime)=0;
	};

	/**
	材质类型
	*/
	enum MATERIAL_TYPE
	{
		MATERIAL_SHADER,//SHADER
		MATERIAL_NEW_SHADER,//new SHADER
		MATERIAL_PASS,//PASS
		MATERIAL_STAGE,//STAGE
		MATERIAL_TEXTURE//TEXTURE
	};

	enum PRIMITIVE_TYPE
	{
		POINT_LIST = 0,
		LINE_LIST,
		LINE_STRIP,
		TRIANGLE_LIST,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		QUAD_LIST
	};


	/**
	IMaterial为所有材质的统一接口，负责材质树的管理。所以其他材质都从此接口派生
	*/
	class IMaterial: public IObject
	{
	public:
		virtual ~IMaterial()=0{};
		virtual const char*				GetName()=0;
		virtual MATERIAL_TYPE			GetType()=0;
	};

	///振荡器参数枚举
	enum WaveFormParam
	{
		WFP_FREQ=0,
		WFP_RANGE,
		WFP_OFFSET,
		WFP_RANGEOFFSET
	};


	struct MaterialInfo
	{
		int		IsTransparent;

		int		UseAlphaTest;

		int		AlphaTestValue;

		int		UseNormalMap;

		int		CastShadow;

		int		ReceiveLight;

		int		UseVertexColor;

		int		TwoSides;

		const char*		MaterialName;
		const char*		DiffuseTextureName;
	};

	class ITexture;
	class INewShader:public IMaterial
	{
	public:

		///得到pass数量
		virtual unsigned int GetPassNumber()=0;

		///得到某个变量的值,浮点数类型，返回值为1表示成功 0表示失败
		virtual int GetNodeVarValue_Float(const char* varName,float& res)=0;
		virtual int GetNodeVarValue_Int(const char* varName,int& res)=0;
		virtual int GetNodeVarValue_Float4(const char* varName,float& f1,float& f2,float& f3,float& f4)=0;
		virtual int GetNodeVarValue_Str(const char* varName,const char*& res)=0; //res为外部传入的一个指针，引擎内部会修改这个指针的值
		virtual int GetNodeVarValue_Matrix44(const char* varName,float* mat)=0; //mat为至少16个元素的数组,mat的空间由使用者分配

		virtual int SetNodeVarValue_Float(const char* varName,float res)=0;
		virtual int SetNodeVarValue_Int(const char* varName,int res)=0;
		virtual int SetNodeVarValue_Float4(const char* varName,float f1,float f2,float f3,float f4)=0;
		virtual int SetNodeVarValue_Str(const char* varName,const char* res)=0;
		virtual int SetNodeVarValue_Matrix44(const char* varName,float* mat)=0; //mat为至少16个元素的数组,mat的空间由使用者分配

		virtual void GetMaterialInfo(MaterialInfo* mtlInfo) = 0;

		///设置贴图给Shader,返回1表示成功，0表示失败
		virtual int SetTexture(const char* varName,H3DI::ITexture* pTex)=0;

		/// 得到此材质使用的ITexture，0表示没有
		virtual H3DI::ITexture* GetTexture(const char* varName) = 0;

		///放弃一个变量所有的修改，恢复初始值
		virtual int ResetVar(const char* varName)=0;
		///得到一个shader所有的变量数量
		virtual int GetAllNodeVarNumber()=0;
		///得到一个变量名字的类型字符串
		virtual const char* GetNodeVarType(const char* varName)=0;
		///得到材质名称
		virtual const char* GetMaterialName()=0;


		///设置振荡器参数。该接口对该材质的所有的，在编辑器中指定了 “接受程序控制的振荡器”的 振荡器
		///对没有设置了该标志的振荡器无效，对没有振荡器的材质设置无效

		///varName:振荡器的参数枚举
		///f0，f1: 振荡器该变量的值将= 振荡器改变量当前值×f0+f1
		///返回值：有多少个振荡器受到影响
		virtual int SetWaveformVar(WaveFormParam varName,float f0,float f1)=0; //最终参数的值=f0*v+f1

		///varName:振荡器的参数枚举
		///v: 振荡器该变量的值将= v
		///返回值：有多少个振荡器受到影响
		virtual int SetWaveformVar(WaveFormParam varName,float v)=0;//最终参数的值=v
		
		virtual void AddRef()=0;
		virtual void DelRef()=0;
		virtual unsigned int GetRef()=0;

		//自动lod1的 亮度、对比度、高光范围、高光强度
		virtual float GetBrightness_AutoLod1()=0;
		virtual float GetContrast_AutoLod1()=0;
		virtual float GetSpecluarRange_AutoLod1()=0;
		virtual float GetSpecluarIntensity_AutoLod1()=0;

		virtual void SetBrightness_AutoLod1(float v)=0;
		virtual void SetContrast_AutoLod1(float v)=0;
		virtual void SetSpecluarRange_AutoLod1(float v)=0;
		virtual void SetSpecluarIntensity_AutoLod1(float v)=0;

		///后门
		virtual int Exec(int a,int b,void* c)=0;
	};
	/**
	IShader为引擎渲染用的SHADER。可从文件*.shd中读取。读取由RENDERCORE负责。此接口可得到SHADER以及SHADER树内其他节点信息
	*/
	class ITexture;
	class IShader : public IMaterial
	{

	public:
		virtual bool					IsPolygonOffset()=0;
		virtual int						GetCulling()=0;
		virtual float					GetOffsetUnit1()=0;
		virtual float					GetOffsetUnit2()=0;
		virtual unsigned int			GetNumPass()=0;
		virtual unsigned int			GetNumStage(unsigned int nPass)=0;
		virtual unsigned int			GetNumTexture(unsigned int nPass,unsigned int nStage)=0;
		virtual ITexture*				GetTexture(unsigned int nPass,unsigned int nStage)=0;
		virtual void					SetAnimTextureFrame(unsigned int nPass,unsigned int nStage,unsigned int nFrame)=0;
		virtual unsigned int			GetAnimTextureHandle(unsigned int nPass,unsigned int nStage,unsigned int nFrame)=0;
		virtual unsigned int			GetAnimTextureNum(unsigned int nPass,unsigned int nStage)=0;
		virtual unsigned int			GetTextureHandle(unsigned int nPass,unsigned int nStage)=0;
		virtual float					GetAnimTextureFPS(unsigned int nPass,unsigned int nStage)=0;//frames per second
		virtual float					GetAnimTextureSPF(unsigned int nPass,unsigned int nStage)=0;//second per frame
		virtual float					GetAnimTime(unsigned int nPass,unsigned int nStage)=0;

		virtual unsigned int			GetWidth()=0;
		virtual unsigned int			GetHeight()=0;
		virtual const char*				GetName()=0;
		virtual float					GetTransparence()const=0;
		virtual void					SetTransparence(float trans)=0;
		virtual bool					IsTrans()=0;
		virtual bool					Reload()=0;
		virtual void					AddRef()=0;
		virtual void					DelRef()=0;
		virtual const unsigned int		GetRef()const=0;
		virtual void                    SetTexture(unsigned int nPass, unsigned int nStage, ITexture* pTex) = 0;
	};


	enum TEX_TYPE
	{
		TEXTURE_1D,//一维贴图
		TEXTURE_2D,//二维贴图
		TEXTURE_3D,//三维贴图
		TEXTURE_CUBEMAP,//立方体贴图
		TEXTURE_RECT,//长方形二维贴图
		TEXTURE_OFFSET,//环境凹凸偏移贴图
		TEXTURE_FLOAT,//浮点贴图
		TEXTURE_RENDER//渲染目标贴图
	};
	/**
	ITexture接口可以得到关于SHADER树中贴图的信息。GetHandle()得到的是OPENGL 贴图句柄。可以由glBindTexture()直接设置。
	*/
	class ITexture : public IMaterial
	{
	public:
		virtual unsigned int			GetSize()=0;
		virtual unsigned int			GetWidth()=0;
		virtual unsigned int			GetHeight()=0;
		virtual TEX_TYPE			GetTexType()=0;
		virtual unsigned int			GetHandle()=0;
		virtual unsigned int			GetBit()=0;

		//!lock贴图,用于用户自己填充内容
		virtual void*                  Lock(unsigned int level, unsigned int& pitch) = 0;
		virtual void                    Unlock(void) = 0;
		virtual void					AddRef()=0;
		virtual void					DelRef()=0;
		//!将贴图保存成文件,PNG格式
		virtual void                    SaveToFile(const char* )const = 0;
		//!return HDC ,2008-3-24
		virtual void*					GetDC()=0;
		virtual void					ReleaseDC(void* hDC)=0;	

	};


	class IRenderTarget : public ITexture
	{
	public:
		virtual void Activate(unsigned int channel) = 0;
		virtual void Deactivate(void) = 0;
	};



	/**
	IBone，骨骼系统中的骨头。其中包围球或包围盒信息尚未放入。在后续版本中加入
	*/
	class IBone: public IObject
	{
	public:
		virtual const char*				GetName()=0;
		virtual	int						GetID()const=0;
		virtual IBone*					GetParent()=0;
		virtual unsigned int			GetNumChildren()=0;
		virtual IBone*					GetChild(unsigned int n)=0;
	};

	/**
	骨骼系统不参与实时渲染时的计算，只作为存储骨骼初始状态的容器
	*/
	class ISkeleton: public IObject
	{
	public:
		virtual IBone*					GetRootBone()=0;
		virtual unsigned int			GetNumBone()=0;
		virtual IBone*					GetBone(unsigned int n)=0;
		virtual IBone*					GetBone(const char* sBoneName)=0;
	};



	enum EVertexBufferFMT
	{
		VB_POS = 1<<0,
		VB_COLOR = 1<<1,
		VB_UV = 1<<2
	};

	/*
	现在index buffer格式是short, 因为有的显卡不支持32bit index
	*/
	class IVB: public IObject
	{
	public:
		virtual ~IVB()=0{};
		virtual char*					GetVertexBuffer()=0;
		virtual char*					GetIndexBuffer()=0;
		virtual void					UnLock(unsigned int nType)=0;

		virtual char*					Lock(unsigned int nType, unsigned int fmt, unsigned int stride)=0;
		virtual bool					CreateBuffer(unsigned int nVBufSize, unsigned int indexCount,
			unsigned int nUsage, unsigned int nElemUsage, char* pVBuf, char* pEBuf)=0;

		virtual unsigned int			GetMaxSize()=0;
	};


	struct MeshData
	{
		int			NumVertices;
		int			NumFaces;
		float		LocalAABB[6];

		int			NumIndices;
		int			NumFloatsPerTangent;

		const unsigned int*	Index;	 
		const float*	Position;		// float3
		const float*	Normal;			// float3
		const float*	Tangent;
		const float*	Binormal;		// float3
		const float*	Texcoord0;		// float2
		const float*	Texcoord1;		// float2
		const float*	VertexColor;	// float4
	};

	class IMesh: public IObject
	{
	public:
		virtual ~IMesh()=0{};
		virtual IVB*					GetVB()=0;
		virtual bool					GetMeshData(H3DI::MeshData* meshData)=0;
		virtual unsigned int			GetDefaultLightmapSize() const = 0;
	};

	class IModel;

	enum//IMoveObject s' flags
	{
		ENTITY_UPDATE_CHILDREN,
		ENTITY_ANIMTRACK_RUNNING,
		ENTITY_NEED_SORT,
	};

	/**
	物体实例的类型
	*/
	enum MODEL_TYPE
	{
		MODEL_STATIC,
		MODEL_SKELETON,
		MODEL_DEFORMED,
		MODEL_LIGHTMAP,	
		MODEL_ACTOR,
		MODEL_REFLECTION,
		OBJECT_BILLBOARD,
		OBJECT_LIGHT,
		OBJECT_LIGHTEFFECT,
		OBJECT_SOUND,
		OBJECT_INDOOR,
		OBJECT_SPECIALEFFECT,
	};


	/**
	物体运行时状态
	*/
	enum MODEL_STATE
	{
		MODEL_CUSTOM_SHADER = 1<<0,
		MODEL_TRANSPARENT = 1<<1,
		SKLMODEL_ANIM_RUNNING = 1<<2,
		SKLMODEL_SWITCHING_ACTION = 1<<3,	
		//		MODEL_ANIMTRACK_RUNNING = 1<<4,
		SKLMODEL_ANIM_END = 1<<5,
		DFM_MODEL_ANIM_RUNNING = 1<<6,
		MODEL_UPDATE_TIME =1 <<7,
		MODEL_UPDATE_DATA = 1<<8,
		MODEL_NEED_UPDATE = 1<<9,
		MODEL_CUSTOM_TRANS_GLASS = 1<<10,
		MODEL_CUSTOM_TRANS_ADD = 1<<11,
		MODEL_GEOM_ANIMTRACK_RUNNING = 1<<12,
		MODEL_NONE_UPATE = 1<<13,//Nothing need update,used in grass, rock,tec...
		MODEL_SUBMODEL_TREE = 1<<14,//it's a submodel tree model, need update submodel's local matrix
		//		MODEL_UPDATE_CHILDREN = 1<<15,//if it has a model tree, it should update the model children locate matrix
		MODEL_LIGHTED = 1<<15,//shined by point light
		MODEL_SHADOWED = 1<<16,//can be a shadow receiver
		MODEL_OCCLUDER = 1<<17,//can be a occluder to generate shadow
		MODEL_USING_EFFECT_SHADER = 1<<18,
		MODEL_REFLECT = 1<<19,
		MODEL_REFRACT =1<<20,
		MODEL_REFLECT_REFRACT = 1<<21,
		SKLMODEL_ANIM_TRANSITION = 1<<22,
		MODEL_NO_RENDER = 1<<23,
		MODEL_USE_COLOR=1<<24,
		MODEL_USE_NECK_IK=1<<31,
		MODEL_USE_WAIST_IK=1<<30,
		MODEL_UNLOAD=1<<29,
		MODEL_USE_CONSTCOLOR_BLEND=1<<28,
	};

	enum EEntityFlag
	{
		I_ENTITY_USE_NECK_IK = 1<<0,
		I_ENTITY_USE_WAIST_IK = 1<<1,
		I_SKLMODEL_ANIM_TRANSITION = 1<<2,
		I_SKLMODEL_ANIM_RUNNING = 1<<3,
		I_SKLMODEL_ANIM_END = 1<<4,
		I_DFM_MODEL_ANIM_RUNNING = 1<<5,
		I_ENTITY_NO_RENDER = 1<<6,
		//说明entity正在副线程中进行数据的更新，有些操作必须阻塞等待更新完毕
		//比如Actor::~Actor, Actor::PostProcessing, etc...
		I_ENTITY_THREAD_PROCESSING=1<<7,
		I_ENTITY_CAST_SHADOW = 1 << 8,
		I_ENTITY_PLANT = 1 << 9,
		I_ENTITY_RENDERIN_REFLECTION = 1 << 10, //该模型在反射中渲染
		I_ENTITY_NOT_WRITE_COLOR = 1 << 11, //渲染时不写颜色。目前仅在引擎内部使用
		I_ENTITY_RALATIVETOACTOR = 1 << 12, //该模型绘制使用角色灯光(环境光)，与角色绘制一致 
		I_ENTITY_RECEIVE_FAKELIGHTSPOT = 1<<13,
		I_ENTITY_HIGHTLIGHT = 1 << 14, //
		I_ENTITY_HIDE = 1 << 15, //
	};
	class IGeometry;


	class IMoveObject : public IObject//IUserObject
	{
	public:
		virtual MODEL_TYPE				Type()=0;
		virtual unsigned int			GetID()=0;
		virtual unsigned int			PrepareDraw()=0;
		virtual unsigned int			Draw()=0;//排序之后，透明OBJECT必须绘制自己！
		virtual void*					GetAllInside(int n)=0;
		//运动控制
		virtual IAnimation*				GetAnimTrack()=0;
		virtual void					SetAnimTrack(IAnimation* pAnim)=0;
		virtual float					GetCurAnimTime()=0;
		virtual void					RunAnimation(bool bRun,float fStartTime)=0;
		virtual bool					IsAnimationRun()=0;

		virtual void					Update()=0;
		virtual void					Update(float fIntervalTime)=0;

		virtual void                    GetAABB(float*)=0;
		virtual void					SetAABB(const float* boxWorld)=0;
		virtual float					Picking(const float* Dir,const float* Point,float* vecIntPoint=0)=0;

		virtual void                    GetLocalAABB(float*)=0;
		virtual const H3DMat4& GetLocationMatrix()const=0;
		virtual const H3DMat4& GetOrgMatrix()const=0;
		virtual void					SetLocationMatrix(const H3DMat4& mat)=0;//设置物体状态矩阵后，Z轴方向旋转角度自动清0
		virtual void					SetOrgMatrix(const H3DMat4& mat)=0;//设置物体原始状态矩阵后
		virtual void					SetPosition(const H3DVec3&)=0;
		virtual void		            GetPosition(H3DVec3&)const=0;

		virtual void					SetZRotation(float degree)=0;
		virtual float					GetZRotation()const =0;
		virtual void					SetScale(const H3DVec3& scale)=0;
		virtual void	                GetScale(H3DVec3&)const=0;
		virtual void					SetDirection(const H3DVec3& dir)=0;
		virtual void                    GetDirection(H3DVec3&)const=0;

		virtual void					SetColor(const float* col, bool bUseColor)=0;
		virtual const float*			GetColor()const=0;

		//层次关系控制，上升到IMoveObject
		virtual unsigned int			GetNumChild()const=0;
		virtual IMoveObject*			GetChild(unsigned int n)=0;
		virtual void					AddChild(IMoveObject* pMoveObj)=0;
		virtual IMoveObject*			GetParent()=0;
		virtual void					SetParent(IMoveObject* pMoveObj)=0;

		virtual void					EnableSort()=0;
		virtual void					DisableSort()=0;
		virtual bool					IsSortEnabled()=0;
		virtual void					SetLOD(size_t nLOD)=0;
		virtual size_t					GetLOD()const=0;
		virtual size_t					GetLODNum()=0;
		virtual float					GetLodDist(size_t nLod)const=0;

		virtual void					EnableChildrenUpdate(bool bEnable)=0;

		virtual IShader*				GetShader()=0;
		virtual void					SetShader(IShader* pIShader)=0;
		virtual void					SetEffectShader(IShader* pShader)=0;
		///重新载入所有,返回1表示成功，0表示失败。
		virtual int						ReloadAll()	= 0;

		/*参数：
		0：等同于ReloadAll
		1：Reload Geometry
		2：Reload 材质（包括贴图）
		3：Reload 贴图

		返回值-1为失败，大于0的数表示reload了几张贴图
		*/
		virtual int						ReloadFromDisk(int reloadContent)=0;
		///获得本物体使用的显存
		virtual unsigned int GetVideoMemUse()=0;

		///获得性能数据
		virtual void* GetPerfData(MODEL_PERFDATA_TYPE t)=0;

		///从内存设置一个材质实例给模型的一个网格，返回1表示成功，0表示找不到该网格
		virtual int SetMeshMaterialTemplateFromMemByName(const char* meshName,void* pXmlDoc)=0;

		//用AABB测试是否和某个射线相交。point和dir都是x、y、z三个分量
		//返回值为1表示相交
		virtual int RayHitTestWithAABB(const H3DVec3& point,const H3DVec3& dir)=0;

		//设置颜色系数
		//f是颜色系数的数组，arraysize是颜色系数数组长度
		//返回值=1表示成功，返回值小于0表示不成功，不成功的原因是材质中没有定义颜色系数
		virtual int SetMaterialColorFactor(float* f,int arraysize)=0;

		/// 设置固有色颜色系数,要求传入两个float[4]，影响方法： (Mat_d*C0.rgb)+C1.rgb，fC0的Alpha用于饱和度计算，fC1的Alpha用于亮度计算
		/// meshPart表示模型接受变色的网格的ID（对于一般模型可以是MeshID），
		///     如果是角色，表示服装的BodypartID或挂件ID(BODYPART_NUM+挂件ID)，当值为-1时，将变色此模型所有的部分。
		/// bUpdateChildren为true时，将变色此模型的子节点（例如挂件上的特效）
		virtual int SetDiffuseColorFactor(float* fC0,int arraysizeC0, float* fC1, int arraysizeC1, int meshPart=-1, bool bUpdateChildren=true)=0;

		//为模型设置渲染参数。参数是EEntityFlag的按位运算的结果
		virtual unsigned int			GetFlags()=0;
		virtual void					SetFlags(unsigned int nFlags)=0;

		///设置材质lod,nLod=0即为最高细节，nLod=2为最简单细节
		virtual void SetMaterialLod(int nLod)=0;
		virtual int GetMaterialLod()=0;

		virtual unsigned int ApplyMaterialLodAndFinishTask(unsigned int taskid)= 0;

		// 异步材质lod的同步设置接口
		//virtual void SetMaterialLodAndFinishTask(unsigned int taskId) = 0;
	};


	struct tClothInfo
	{
		tClothInfo()
		{
			fileName = 0;
			dim[0] = dim[1] = dim[2] = 1;
			pose[0] = pose[5] = pose[10] = pose[15] = 1;
			pose[1] = pose[2] = pose[3] = pose[4] = 0;
			pose[6] = pose[7] = pose[8] = pose[9] = 0;
			pose[11] = pose[12] = pose[13] = pose[14] = 0;
		}
		float dim[3];
		float pose[16];
		const char* fileName;
	};

	class ICloth
	{
	public:
		virtual void AttachVertexToGlobalPosition(unsigned int vertexId, const float* pos) = 0;
		virtual unsigned int GetNumRow(void)const = 0;
		virtual unsigned int GetNumColumn(void)const = 0;
		virtual unsigned int GetNumFaces(void)const = 0;
		virtual unsigned int getNumVertices(void)const = 0;
		virtual void SetThickness(float) = 0;
		virtual float GetThickness(void)const = 0;
		virtual void SetDensity(float) = 0;
		virtual float GetDensity(void)const = 0;
		virtual void SetBending(float) = 0;
		virtual float GetBending(void)const = 0;
		virtual void SetStretch(float) = 0;
		virtual float GetStretch(void)const = 0;
		virtual void SetDamping(float) = 0;
		virtual float GetDamping(void)const = 0;
		virtual void SetFriction(float) = 0;
		virtual float GetFriction(void)const = 0;
		virtual void SetGravity(const float*) = 0;
		virtual const float* GetGravity(void)const = 0;
		virtual void SetStableForce(float t) = 0;
		virtual float GetStableForce(void)const = 0;
	protected:
		virtual ~ICloth(){}
	};
	struct ModelBoundingVolumeTestInfo
	{
		//碰撞的包围盒的ID
		int id;
		//碰撞点的世界坐标
		float x ,y ,z;
		//碰撞点的参数坐标
		float fScale;
	};

	struct  IBoneWeight 
	{
		int m_nBones[4];
		float m_fWeights[4];
	
		IBoneWeight()
		{
			Reset();
		}
		void Reset()
		{
			memset(m_nBones,0,sizeof(int)*4);
			memset(m_fWeights,0,sizeof(int)*4);
		}
	};
	//和挂饰相关的数据集合
	struct IAttachModelInfo
	{
		float m_rayOrg[3];
		float m_rayDir[3];
		float m_attachPos[3];
		float m_attachNormal[3];

		//如果挂接的BPT没有动作,和上面的一致
		float m_attachPosLocal[3];
		float m_attachNormalLocal[3];

		//如果是背面的射线,需要设置标志位
		//-1:翻转射线,0默认,1不翻转射线
		int m_bInverseRay;

		//玩家操作的挂饰数据
		//缩放
		float m_scaleX,m_scaleY,m_scaleZ;
		//绕挂接点法线的旋转
		float m_rotateAngle;
		//到挂接点的偏移
		float m_offX,m_offY,m_offZ;
		
		//挂接点属性
		IBoneWeight m_boneWeights[3];
		int m_vertIndex[3];
		int m_phyVertIndex[3];
		//重心权重
		float m_vertWeight[3];

		//挂接点处的朝向
		float m_attachMat[16];

		//挂饰挂接的网格名称
		char m_meshName[256];
		//挂接的BodyPart部位
		int m_bodyPart;

		//被挂接的挂饰
		IModel* m_attachModel;

		//最短距离
		float m_minDist;

		IAttachModelInfo()
		{
			Reset();
		}
		void Reset()
		{
			memset(m_rayOrg,0,sizeof(float)*3);
			memset(m_rayDir,0,sizeof(float)*3);
			memset(m_attachPos,0,sizeof(float)*3);
			memset(m_attachPosLocal,0,sizeof(float)*3);
			memset(m_attachMat,0,sizeof(float)*16);

			memset(m_meshName,0,sizeof(char)*256);

			memset(m_vertIndex,0,sizeof(int)*3);
			memset(m_phyVertIndex,-1,sizeof(int)*3);

			m_attachModel = 0;
			
			m_bodyPart = -1;

			m_attachNormal[0] = m_attachNormal[1] = 0.0f;
			m_attachNormal[2] = 1.0f;

			m_attachNormalLocal[0] = m_attachNormalLocal[1] = 0.0f;
			m_attachNormalLocal[2] = 1.0f;

			m_scaleX = m_scaleY = m_scaleZ = 1.0f;
			m_rotateAngle = 0.0f;
			m_offX = m_offY = m_offZ = 0.0f;

			m_boneWeights[0].Reset();
			m_boneWeights[1].Reset();
			m_boneWeights[2].Reset();

			m_minDist = 1e30f;

			m_bInverseRay = 0;
		}
	};

	/// 模型相关的LightMap属性
	struct ILightMapInfo
	{
		H3DI::ITexture* m_pTex;	/// LIGHTMAP贴图指针

		float m_CoordBias[2]; /// UV偏移信息
		float m_CoordScale[2];/// UV缩放信息

		float m_clrScale[3]; /// 颜色增强系数
	};

	class IModel: public IMoveObject
	{ 
	public:

		virtual ~IModel()=0{};
		virtual unsigned int			GetFlags()=0;
		virtual void					SetFlags(unsigned int nFlags)=0;

		virtual unsigned int			GetNumSubModel()const=0;
		virtual void					SetTransparence(float trans)=0;
		virtual float					GetTransparence()const=0;

		//运行控制

		virtual void					SetGeometry(IGeometry* pGeom)=0;
		virtual IGeometry*				GetGeometry()=0;
		virtual void					RunGeomAnimation(bool bRun,float fStartTime)=0;//启动物体本身的几何动画

		//CLONE
		virtual IModel*					Clone()=0;

		//LOD
		virtual void					EnableRender()=0;
		virtual void					DisableRender()=0;
		virtual bool					IsNeedRender()=0;
		virtual void					SetLoop(bool bLoop)=0;
		virtual bool					GetLoop()const=0;

		virtual void                    SetFakeShadowSize(float) = 0;
		virtual float                    GetFakeShadowSize(void)const = 0;

		//by sssa2000 090210
		virtual bool					IsCullByOctree()=0;
		virtual bool					IsCullByOccluder()=0;


		//可视范围
		virtual	float GetVisibleDist() = 0;
		virtual	void SetVisibleDist(float dist) = 0;

		//获得一个模型号的顶点和索引数据，
		//pVertBuf，pIndexBuff，顶点和索引的指针，用于传出数值
		//pVertNum,pIndexNum顶点和索引的个数，当前pVertBuf，pIndexBuff都传入空指针是，返回顶点和索引的个数。一般情况下传入顶点和索引的个数。
		//返回值：当传入的顶点和索引的数量大于等于实际的模型所需的数量时返回真,否则返回假
		virtual bool GetVertexAndIndex( float *pVertBuf,unsigned int *pIndexBuff,int *pVertNum,int *pIndexNum ) = 0;

		///重新载入这个模型的材质,返回1表示成功，0表示失败。
		virtual int ReloadMaterialInstance()=0;
		///重新载入fx
		virtual int ReloadFx()=0;

		///设置模型的模糊因子。0.0-1.0的浮点数。为0时表示模型完全清晰，为1是表示完全参与运动模糊。0-1之间的数表示参与运动模糊的程度。
		virtual void SetMotionBlurFactor(float fFactor) = 0;
		///设置遮挡查询的状态
		virtual void	SetUseOcclusionQuery(bool bVal) = 0;
		///获取是否使用遮挡查询的状态
		virtual bool	UseOcclusionQuery() const = 0;
		///获得查询结果，0表示被完全遮挡了
		virtual unsigned int GetOcclusionQueryResult() = 0;


		//////////////////////////////////////////////////////////////////////////
		//材质相关

		//高亮参数是2个颜色c0,c1，最终的颜色是c0*物体颜色+c1
		//返回值1表示成功，0表示失败。失败的原因是物体的材质不支持该操作
		virtual int HightLight(float r0,float b0,float c0,float r1,float b1,float c1)=0;

		///得到新材质，参数是网格的id，从0开始
		virtual H3DI::INewShader* GetNewShaderByIndex(unsigned int i)=0;

		///得到新材质，参数是网格的名字
		virtual H3DI::INewShader* GetNewShaderByName(const char* name)=0;

		///设置新材质 将影响到整个模型的所有mesh
		virtual int SetNewShader(H3DI::INewShader* p)=0;

		///通过一个材质实例的文件名和材质实例的名字 将一个材质设置给整个模型，将影响到整个模型的所有mesh
		///返回值是从文件中得到的INewShader,0表示失败
		virtual H3DI::INewShader* SetNewShader(const char* filename,const char* matballName)=0;


		///设置新材质 将一个材质设置给某个mesh，返回0表示失败，可能是没有该mesh
		virtual int SetMeshNewShaderByName(const char* meshName,H3DI::INewShader* p)=0;

		///通过一个材质实例的文件名和材质实例的名字 将一个材质设置给某个mesh
		///返回值是从文件中得到的INewShader,0表示失败
		virtual H3DI::INewShader* SetMeshNewShaderByName(const char* meshName,const char* filename,const char* matballName)=0;

		///设置新材质 将一个材质设置给某个mesh，返回0表示失败，可能是没有该mesh
		virtual int SetMeshNewShaderByIndex(int meshIdx,H3DI::INewShader* p)=0;

		///通过一个材质实例的文件名和材质实例的名字 将一个材质设置给某个mesh
		///返回值是从文件中得到的INewShader,0表示失败
		virtual H3DI::INewShader* SetMeshNewShaderByIndex(int meshIdx,const char* filename,const char* matballName)=0;

		///从内存设置一个材质模板给模型，模型的所有网格都受到影响。返回1表示成功
		virtual int SetMaterialTemplateFromMem(void* pXmlDoc)=0;

		///从内存设置一个材质模板给模型的一个网格，返回1表示成功，0表示找不到改名字的网格
		virtual int SetMeshMaterialTemplateFromMemByName(const char* meshName,void* pXmlDoc)=0;

		///从内存设置一个材质模板给模型的一个网格，返回1表示成功，0表示找不到该网格
		virtual int SetMeshMaterialTemplateFromMemByIndex(int meshIdx,void* pXmlDoc)=0;

		///从内存设置一个材质实例给模型的一个网格，返回1表示成功，0表示找不到该网格
		virtual int SetMeshMaterialInstanceFromMemByName(int meshIdx,void* pXmlDoc)=0;	

		///从内存设置一个材质实例给模型的一个网格，返回1表示成功，0表示找不到该网格
		virtual int SetMeshMaterialInstanceFromMemByName(const char* meshName,void* pXmlDoc)=0;
		//////////////////////////////////////////////////////////////////////////
		//以下接口不要使用

		///设置物体是否具有反射效果
		///参数b:是否开启反射
		///参数plane：是一个4个元素的数组，保存的是平面的方程
		virtual void SetIsReflectionObj(bool b,float* plane)=0;

		///获取物体是否具有反射效果
		///返回:是否开启反射
		///参数plane：是一个4个元素的数组，保存的是平面的方程
		virtual bool GetIsReflectionObj(float* plane)=0;

		///设置物体是否参与反射渲染
		virtual void SetCanBeReflection(bool b)=0;

		///获取物体是否参与反射渲染
		virtual bool GetCanBeReflection()=0;

		///设置反射远平面
		///参数：远平面距离
		virtual void SetReflectionFarClipPlane(float dis)=0;

		///设置物体是否是折射物体
		virtual void SetIsRefracionObj(bool b)=0;
		virtual bool GetIsRefracionObj()=0;

		///设置折射率
		virtual void SetRefracionIndex(float f)=0;
		virtual float GetRefracionIndex()=0;

		//编辑器生成光芒时调用的接口
		virtual void  Editor_GenerateMetalStar() = 0;
		//////////////////////////////////////////////////////////////////////////
		//获取光芒文件数据
		//	返回：光芒数据值针
		//	参数：psize，输出型参数，返回光芒数据大小。
		virtual void * Editor_GetMetalStarData (unsigned int* psize) = 0;//

		//功能：计算一条射线与模型上的包围盒相碰撞的信息
		//参数
		//rayOrigin：传入三个浮点数组成的数组，表示一条射线的起始点
		//rayDir：传入三个浮点数组成的数组，表示一条射线的方向
		//ModelBVTestInfo ：一个数组首地址，用于结果的返回。所有碰撞到的包围盒按先后顺序将ID和碰撞点坐标返回给客户端。数组的大小不能小于一个模型的包围盒个数，包围盒个数由引擎再提供一个接中得到
		//nResultBufferCount：数组的元素个数，防止引擎填充数据越界
		//返回值：返回的结果的个数,如果为，说明没有碰撞
		virtual int  RayTestWithBoundingVolumes(const float* rayOrigin, const float * rayDir, ModelBoundingVolumeTestInfo *pOut, int nResultBufferCount) const = 0;
		//获取包围体的个数
		virtual int	 GetBoundingVolumesCount() = 0;

		//功能：射线求交
		//	//参数
		//	RayOrg：传入的射线起点
		//	RayDir：传入射线方向
		//	fOutDistance：引擎返回的结果，这个数值是碰撞点到射线起点的距离。
		//返回值：射线与模型是否碰撞
		virtual bool  RayTestWithTriangles(const H3DVec3 & RayOrg, const H3DVec3 & RayDir,float & fOutDistance) = 0;

		//!挂饰相关接口
		//根据射线得到挂接数据集
		//第二个参数表示是否需要转换射线空间
		virtual int	  QueryAttachPoint(IAttachModelInfo& rayResInfo,bool bTransToLocal=true) = 0;
		
		//!挂接挂饰.
		virtual int	  AttachModel(const IAttachModelInfo& rayInfo) = 0;

		//!取消挂接
		virtual int	  DetachModel(const IAttachModelInfo& rayInfo) = 0;

		//!预生成fx
		virtual int PreGenFx(H3DI::IFxInfo* p)=0;

		///!设置LightMap贴图文件名及Info等,MeshID为此模型的网格索引
		virtual int SetLightMapInfo(unsigned int MeshID, const ILightMapInfo& info) = 0;

		/**
			lightmapSizeBuffer: mesh对应的lightmap size，与geometry中mesh的数量一致
			uvTexturePathName: 用于预览uv拆分的结果，如传入"d:\\lightmapUVTest%d.bmp",则
								保存出d:\\lightmapUVTest0.bmp, d:\\lightmapUVTest1.bmp等文件。
								不用时传NULL
			bReadOnlyModified: 用于返回是否修改了lmm文件的只读属性，可以为NULL
			返回值：成功返回true，失败返回false。如果失败，或者用更大的lightmapsize，或者让美术手动展uv
		*/
		virtual bool GenerateLightmapUV(const int* lightmapSizeBuffer, const char* uvTexturePathName, int* bReadOnlyModified) = 0;

		///后门函数
		virtual void HelpFunction(int i,void* param0,void* param1=0,void* param2=0,void* param3=0,void* param4=0)=0;


	};

	class IReflectModel: public IModel
	{
	public:
		virtual void							SetPlane(const float* vec4PlaneEq)=0;
		virtual void                            GetPlane(float* vec4PlaneEq)=0;
	};
	/**
	动作过渡模式
	*/
	enum EActionTransitionMode
	{
		/**
		0结束过渡到A1开始期间，是否更新A1，如不更新A1，A0,A1之间会凭空多出一段过渡时间.
		如果更新A1，过渡时间会算作A1的动作时间内，动作序列总长度不会变化
		*/
		TRANSITION_NEXT_UPDATE = 1<<0,
		/**
		A0结束前0.3秒开始过渡到A1的第一桢，这段时间内是否更新A0，如不更新，相当于两个静桢插值
		*/
		TRANSITION_CURRENT_UPDATE	= 1<<1,//具体方式由EActionTransitionMethod指定
		/**
		A0结束，A1开始，是否认为A1是局部动作。
		如A1是局部动作，A1开始时根骨骼的位置等于A0最后一桢根骨骼位置＋A1第一桢的根骨骼位置。
		如A1是全局动作，A1开始时根骨骼位置等于A1第一桢的根骨骼位置
		*/
		TRANSITION_LOCALLY	= 1<<2,
		/**
		A0结束前0.3秒到A1第一桢过渡期间，脚的位置不变
		*/
		TRANSITION_FIXED_FOOT = 1<<3           
	};
	//动作过渡时的插值方式
	enum EActionTransitionMethod
	{
		//从当前帧过渡到一个静态帧,从A0到A1的0.3秒
		TRANSITION_TO_STATIC = 0,
		//从当前帧过渡到一个动态帧,从A0到A1的当前时间
		TRANSITION_TO_DYNAMIC = 1,
	};
	/**
	一轨独立骨骼动画
	多轨动画可以混合起来影响一个角色的姿态
	*/
	class IAnimationChannel : public IObject
	{
	public:
		/************************************************************************/
		/* 0 : succeed
		1 : action is not in actionlib
		2 : action is in actionlib, but can't load ase file
		3 : Invalid Params
		*/
		/************************************************************************/
		/**
		设置单一静态帧
		*/
		virtual int SetStaticFrame(const char* name) = 0;
		/**
		设置静态帧
		*/
		virtual int SetStaticFrame(unsigned int id, const char* name, float weight) = 0;
		/**
		设置静态帧序列
		*/
		virtual void SetStaticSeq(const char** names, const float* intervals, unsigned int count, bool loop) = 0;
		/**
		设置动画帧序列
		*/
		virtual void SetActionSeq(const char** names, unsigned int count, bool loop) = 0;
		/**
		设置单一动画帧
		*/
		virtual int SetAction(const char* names, bool loop) = 0;
		virtual int SetNextAction(const char* names, bool loop) = 0;
		// 同步设置一个异步加载的action
		virtual unsigned int SetActionAndFinishTask(unsigned int taskId, bool loop)=0;
		virtual unsigned int SetNextActionAndFinishTask(unsigned int taskId, bool loop)=0;
		
		/**
		得到当前动作
		*/
		virtual IAction* GetCurrAction(void) = 0;
		/**
		Clear all stuff
		*/
		virtual void Clear() = 0;
		/**
		设置这个通道的权重, 所有激活通道的权重会被规一化
		*/
		virtual void SetWeight(float) = 0;
		/**
		得到权重
		*/
		virtual float GetWeight(void)const = 0;
		/**
		设置动作过渡时间
		*/
		virtual void SetTransitionTimeFromCurrent(float) = 0;

		virtual void SetTransitionTimeToNext(float) = 0;
		/**
		得到动作过渡时间
		*/
		virtual float GetTransitionTimeFromCurrent(void)const = 0;

		virtual float GetTransitionTimeToNext(void)const = 0;
		/**
		设置当前动作时间,只在静帧序列,单一动画帧,动画帧序列模式下起作用
		*/
		virtual void SetCurrActionTime(float) = 0;
		/**
		得到当前动作时间
		*/
		virtual float GetCurrActionTime(void)const = 0;
		/**
		得到当前动作长度
		*/
		virtual float GetCurrActionLength(void)const = 0;
		/**
		只否正在过渡动作
		*/
		virtual bool IsTransitingToNext(void)const = 0;

		virtual bool IsTransitingFromCurrent(void)const = 0;
		/**
		是否循环
		*/
		virtual bool IsLoop(void)const = 0;
		/**
		是否独占
		*/
		virtual bool IsDominating(void)const = 0;
		/**
		得到channel ID
		*/
		virtual unsigned int GetChannelID(void)const = 0;
		/**
		设置动作过渡模式, 默认为TRANSITION_SYNC
		*/
		virtual void SetTransitionMode(int mode) = 0;
		/**
		得到动作过渡模式
		*/
		virtual int GetTransitionMode(void)const = 0;

		virtual void Draw(void)const =0;

		//得到当前动作的名字，返回值：0表示没有当前动作，1：表示成功，-1表示传入的buffer长度太小
		virtual int GetCurrentActionName(char* buffer,unsigned int bufferlen)=0;

		//得到下一个动作的名字，返回值：0表示没有next动作，1：表示成功，-1表示传入的buffer长度太小
		virtual int GetNextActionName(char* buffer,unsigned int bufferlen)=0;

		//得到下一个动作是否循环，返回-1表示没有下一个动作 返回0表示不循环 返回1表示循环
		virtual int GetIsNextActionLoop()=0;
		//在当前动作播放设置循环参数
		virtual	void SetActionLoop(bool) = 0;
		//在当前下一个播放设置循环参数
		virtual void SetNextActionLoop(bool)=0;
		//动作过渡时的插值方式
		virtual void SetTrainsitionMethod(EActionTransitionMethod) = 0;
		//设置当前动作累积位移
		virtual void SetRootPos(const H3DVec3& pos) = 0;
		//获取当前动作累积位移
		virtual const H3DVec3& GetRootPos()const = 0;
		//设置当前动作是否不被融合
		virtual void SetSkipBlend(bool) = 0;

	protected:
		virtual ~IAnimationChannel(){}
	};

	/**
	骨骼物体。ISkeletonModel可以控制骨骼物体当前的动作动画。得到物体每根骨头的当前位置/旋转状态
	和相对以及世界绝对矩阵。同时可以得到每根骨头当前的动画IAnimation。
	*/


	/**
	channel mode:
	0 : 单一静帧
	1 : 两个静帧
	2 : 静帧序列
	3 : 动画帧序列
	4 : 单一动画帧
	5 : 停止
	*/
	class AnimationChannelState
	{
	public:
		unsigned int m_nChannelCount;
		float* m_vChannelWeights;
		float* m_vChannelTransitionWeights;
		unsigned int* m_vChannelMode;
	};

	class IAnimationChannelModifier
	{
	public:
		virtual bool UpdateState(AnimationChannelState& state)=0;
	};

	/*
	*	给编辑器添加的接口数据结构,用于编辑器编辑布料属性数据
	*/

	enum EPHXDATATYPE
	{
		//保存刚体数据模板
		PHXDATATYPE_BOUND,
		//保存布料数据模板
		PHXDATATYPE_CLOTH,
		//保存关节数据,保存关节数据等于保存所有刚体链数据模板
		PHXDATATYPE_JOINT,
		//布料网格
		PHXDATATYPE_CLOTHMESH,
		//
		PHXDATATYPE_COUNT
	};
	//标志位,其值对应于NxFlag
	enum ECLOTHPHXFLAG
	{
		CLOTH_PHXFLAG_PRESSURE = 1<<0,
		CLOTH_PHXFLAG_STATIC	  = 1<<1,
		CLOTH_PHXFLAG_DISABLE_COLLISION = 1<<2,
		CLOTH_PHXFLAG_SELFCOLLISION = 1<<3,
		CLOTH_PHXFLAG_VISUALIZATION = 1<<4,
		CLOTH_PHXFLAG_GRAVITY = 1<<5,
		CLOTH_PHXFLAG_BENDING = 1<<6,
		CLOTH_PHXFLAG_BENDING_ORTHO = 1<<7,
		CLOTH_PHXFLAG_DAMPING = 1<<8,
		CLOTH_PHXFLAG_COLLISION_TWOWAY = 1<<9,
		CLOTH_PHXFLAG_HARDWARE = 1<<13,
		CLOTH_PHXFLAG_COMDAMPING = 1<<14,
		CLOTH_PHXFLAG_DISABLE_DYNAMIC_CCD = 1<<17,
		CLOTH_PHXFLAG_HARD_STRETCH_LIMITATION = 1<<20
	};
	//标志位,和物理标志无关
	enum ECLOTHFLAG
	{
		CLOTH_FLAG_ATTACH_TO_COLLISIONSHAPE = 1<<0,
		CLOTH_FLAG_USE_CONSTRAIN = 1<<1
	};
	//刚体类型
	enum EBOUNDTYPE
	{
		//!球形
		BOUND_SPHERE = 0,
		//!胶囊
		BOUND_CAPSULE,
		//!未知
		BOUND_UNKNOWN
	};
	//刚体标志位
	enum EBOUNDFLAG
	{
		BOUND_FLAG_KINEMATIC = 1<<0,
		BOUND_FLAG_BE_ATTACHED = 1<<1
	};
	//关节类型
	enum EJOINTTYPE
	{
		JOINT_SPHERICAL = 0,
		JOINT_DISTANCE
	};
	struct H3DClothMesh
	{
		//网格
		const float* m_meshData;
		//顶点个数
		int m_vertCount;
		//三角形个数
		int m_triCount;
		//顶点索引.大小是triCount*3
		const unsigned int* m_indexBuffer;

		H3DClothMesh()
		{
			m_meshData = 0;
			m_vertCount = 0;
			m_triCount = 0;
			m_indexBuffer = 0;
		}
	};
	struct H3DClothPara
	{
		//参数名称
		char m_paraName[256];
		//布料标志位
		int m_clothFlag;
		//布料物理标志位
		unsigned int m_clothPhxFlag;
		//弯曲系数
		float m_bendingStiffness;
		//拉伸系数
		float m_stretchStiffness;
		//厚度
		float m_thickness;
		//衰减系数
		float m_damping;
		//迭代次数
		int m_iterations;
		//摩擦系数
		float m_friction;
		//布料密度
		float m_clothDesity;
		//挂接响应系数
		float m_attachResponse;
		//碰撞响应系数
		float m_collResponse;
		//模拟层次
		int m_hierarchLevel;
		//气压
		float m_pressure;

		H3DClothPara()
		{
			m_clothFlag = 0;
			m_clothPhxFlag |= CLOTH_PHXFLAG_BENDING;
			m_clothPhxFlag |= CLOTH_PHXFLAG_DAMPING;
			m_clothPhxFlag |= CLOTH_PHXFLAG_GRAVITY;
			m_bendingStiffness = 1.0f;
			m_stretchStiffness = 1.0f;
			m_thickness = 0.15f;
			m_damping = 0.3f;
			m_iterations = 5;
			m_friction = 0.01f;
			m_clothDesity = 10.0f;
			m_attachResponse = 0.2f;
			m_collResponse = 0.2f;
			strcpy(m_paraName,"default");
			m_hierarchLevel = 0;
			m_pressure = 0.0f;
		}
	};
	struct H3DBoundPara
	{
		//name
		char m_boundName[256];
		//尺寸
		float m_dim[3];
		//包围体绑定的骨骼.目前最大只支持2个
		char m_parBoneName[4][256];
		//对应的权重
		float m_parBoneWeight[4];
		//碰撞体类型
		int m_boundType;
		//标志位
		int m_boundFlag;
		//姿态
		float m_pos[3];
		float m_quat[4];
		//物理属性
		int m_simCount;
		float m_skinWidth;
		float m_mass;
		float m_density;
		float m_linearDamping;
		float m_angluarDamping;
		float m_restriction;
		float m_staticFriction;
		float m_dynamicFirction;

		H3DBoundPara()
		{
			memset(m_dim,1,sizeof(m_dim));
			
			strcpy(m_boundName,"DefaultBound");
			strcpy(m_parBoneName[0],"Bip01");
			strcpy(m_parBoneName[1],"Bip01");
			strcpy(m_parBoneName[2],"Bip01");
			strcpy(m_parBoneName[3],"Bip01");

			m_parBoneWeight[0] = 1.0f;
			m_parBoneWeight[1] = 0.0f;
			m_parBoneWeight[2] = 0.0f;
			m_parBoneWeight[3] = 0.0f;

			m_boundType = BOUND_UNKNOWN;
			m_pos[0] = m_pos[1] = m_pos[2] = 0.0f;
			m_quat[0] = m_quat[1] =m_quat[2] = 0.0f;
			m_quat[3] = 1.0f;

			m_boundFlag = 0;
			m_simCount = 5;
			m_skinWidth = 0.1f;
			m_mass = 0.0f;
			m_density = 10.0f;
			m_linearDamping = 0.0f;
			m_angluarDamping = 0.0f;
			m_restriction = 0.01f;
			m_staticFriction = 0.05f;
			m_dynamicFirction = 0.05f;
		}
	};
	struct H3DJointPara
	{
		char m_srcBound[256];
		char m_dstBound[256];
		int m_jointType;
		int m_jointFlag;
		float m_swingLimit;
		float m_swingSpring;
		float m_swingDamper;

		H3DJointPara()
		{
			m_jointFlag = 0;
			m_jointType = 0;
			m_swingLimit = 15.0f/180.0f;
			m_swingSpring = 1.0f;
			m_swingDamper = 0.5f;
		}
	};
	struct ScaleSkeletonInfo
	{
		float zValue;
		float xValue;
		float yValue;
		const char* boneName;

		ScaleSkeletonInfo()
		{
			zValue = xValue = yValue = 1.0f;
			boneName = 0;
		}
	};
	class ISkeletonModel : public IModel
	{
	public:

		virtual const H3DMat4&	 GetCurMatrix(unsigned int nBone)const=0;
		//骨骼渲染矩阵。和逻辑矩阵可能有所不同
		virtual const H3DMat4&	 GetRendingMatrix(unsigned int nBone)const=0;
		virtual const H3DMat4&	 GetCurRalativeMatrix(unsigned int nBone)const=0;
		virtual const H3DVec3&  GetCurPos(unsigned int nBone)const=0;
		virtual const H3DQuat&	 GetCurRot(unsigned int nBone)const=0;

		virtual int					SetAction(const char* sName)=0;
		virtual int					SetMixAction(const char* sName, float fWeight, int nIdx, int nParam)=0;
		virtual void				GetMixAction(int nIdx, float& fWeight, int& nActionIdx)=0;
		virtual IAction*			GetCurAction()=0;
		virtual IAnimation*			GetCurBoneAnimation(unsigned int nBone)=0;
		virtual float				GetCurActionTime()=0;
		virtual void				SetCurActionTime(float fActionTime)=0;
		virtual void				SetActionTransitionTime(float fTime)=0;
		virtual float				GetActionTransitionTime()const=0;

		virtual void				SetHeadDir(const H3DVec3& dir)=0;
		virtual void				SetWaistDir(const H3DVec3& dir)=0;
		virtual const H3DVec3& GetHeadDir()const=0;
		virtual const H3DVec3& GetWaistDir()const=0;


		//================Used in action lib model====================
		virtual ISkeleton*				GetSkeleton()=0;
		virtual const char*				GetActionName(unsigned int n)=0;
		virtual IAction*				GetAction(unsigned int n)=0;
		virtual IAction*				GetAction(const char* sActionName)=0;
		virtual unsigned int			GetNumAction()const=0;
		virtual int						SetStaticMixAction(unsigned int id/*0, 1*/, const char* actName) = 0;
		virtual void					SetStaticActionMixWeight(float weight /*0-1*/) = 0;/*weight x action0+(1-weight) x action1*/
		/*
		actNames = const char*[count]; interval = float[count-1]
		*/
		virtual void SetStaticActionSequence(const char** actNames, float* intervals, unsigned int count, bool loop) = 0;
		/*
		得到某一个通道的动画, id合法值为[0,3]
		*/
		virtual IAnimationChannel* GetAnmChannel(unsigned int id) = 0;
		/*
		清除所有通道的数据
		*/
		virtual void          ClearAllAnmChannels(void) = 0;
		//by zhengchengjun 2011-11-25
		/*
		设置哪些动作通道为独占通道, buff=NULL会把所有通道设为非独占通道
		*/
		virtual void   SetDominatingChannel(int* buff, unsigned int buffLen) = 0;

		virtual unsigned int   GetDominatingChannel(int* buff, unsigned int buffLen)const = 0;

		virtual void  SetChannelModifier(IAnimationChannelModifier* p) = 0;

		virtual IAnimationChannelModifier*  GetChannelModifier(void)const = 0;

		virtual void ClearChannelModifier(void) = 0;

		virtual void LoadBodyBounds(const char* fileName) = 0;


		virtual unsigned int GetActionNames(const char** buff, unsigned int buffLen) = 0;
		virtual unsigned int GetActionNamesCopy(char* buff, unsigned int buffLen, unsigned int nameLen) = 0;

		//by sssa2000 090203 为编辑器添加接口
		//绘制骨骼
		virtual void DrawSkeleton()=0;
		virtual void CopyTo(ISkeletonModel *pModel)const = 0;
		//关联两个物体的动作，使当前物体的动作根骨骼基于骑乘物体某个骨骼,iBoneId是绑定的骨骼ID
		virtual bool	RelationAnimation(ISkeletonModel *pHorseModel,const char *animNameSelf,const char *animHorse,int iBoneId = 0) = 0;

		//在更新骨骼模型的时候,是否对各个骨头进行计算, 默认值为true
		//如果该选项为false, 在ISkeletonModel的copy函数内也不需要拷贝骨头数据.
		virtual void	SetUpdateBones(bool bUpdateBones) = 0;

		//设置坐骑矩阵,太特殊了,用于修正马对布料更新的影响
		virtual void	SetMountMatrix(const H3DMat4& mountMatrix)=0;

		//获得人物物理成员的名字,传入指定的物理实体类型
		virtual int		GetPhxEntityNames(const char** pNames,int num,int phxType)=0;
		//设置物理实体的属性,当是布料参数时,传入的是布料网格名
		virtual void   SetPhxEntityPara(const char* pName,void* phxPara,int phxType) = 0;
		//获取物理实体的属性,当是布料参数时,传入的是布料网格名
		virtual void	GetPhxEntityPara(const char* pName,void* phxPara,int phxType) = 0;
		//获取物理参数,传入物理参数名,目前只支持布料
		virtual void   GetPhxParaByName(const char* paraName,void* phxPara,int phxType) = 0;
		//!从参数库中删除掉一个参数,目前只支持布料
		virtual void   DelPhxParaByName(const char* paraName,int phxType) = 0;
		//新建一个物理实体
		virtual void   CreatePhxEntity(const char* pName,void* phxPara,int phxType) = 0;
		//删除一个物理实体
		virtual void   DelPhxEntity(const char* pName) = 0;
		//保存物理数据模板,类型由EPhxDataType指定
		virtual void   SavePhxDataTemplate(const char* pName,int phxDataType) = 0;
		//保存物理数据到bp3中,当前无用
		virtual void   SavePhxDataToBp3(const char* pFileName) = 0;
		//加载.传入clearCur表明是否需要清楚掉当前已经读取的参数
		virtual void   LoadPhxDataTemplate(const char* pName,int phxDataType,bool clearCur) = 0;
		//获取当前所有布料参数组
		virtual int   GetAllPhxDataParas(const char** pNames,int bufferLen,int phxDataType) = 0;
		//融合物理结果
		virtual void   BlendPhxResult() = 0;
		//绘制物理
		virtual void   RenderPhxInfo() = 0;

		//填加一个附加在骨骼上的四元数，在动作计算之后，将旋转附加到骨骼上
		virtual void	AddQuatToBone(int index,const H3DQuat& quat) = 0;
		//清空所有的四元数
		virtual void	ClearAdditionalQuat() = 0;
		//获取布料光芒文件数据
		//返回：光芒数据值针
		//参数：psize，输出型参数，返回光芒数据大小。
		virtual void *  Editor_GetClothMetalStarData (unsigned int* psize) = 0;
		//缩放骨骼,by lzp 2011-4-14
		virtual void    SetScaleInfo(const ScaleSkeletonInfo& sInfo)=0;
		virtual void	 ClearScaleInfo() = 0;

		//sssa2000 08.03.24:
		//动态设置该人物的物理
		virtual void                SetThisActorPhy(bool b)=0;
		//获得该人物的物理状态，注意，在人物一创建 就需要显示的设置一次SetThisActorPhy，这样每次的GetThisActorPhy才能生效
		virtual bool				GetThisActorPhy()=0;

		// 给某个mesh设置排序补偿值
		virtual void SetSortingOffset(const char* meshName, float offset) = 0;

		// 使某个mesh高亮显示
		// bHightLight true : 设置高光效果，false : 恢复
		virtual void HightLightSubEntity(const char* subEntityName, bool bHightLight) = 0;

		//
		virtual void	UpdateCpuSkin(float t) = 0;

		//更新蒙皮到预定义姿态
		virtual void  UpdateSkinPose(int bpID,bool bUpdate) = 0;
	};
	enum 
	{
		BODY_FACE =0,
		BODY_HAIR,
		BODY_UP,
		BODY_LEGS,
		BODY_RARM,
		BODY_LARM,
	};
	enum IKUpdateState
	{
		//使马腿竖直
		IKUS_PLUMB = 1<<1,
		//使马腿在地面上
		IKUS_ONTERRAIN = 1<<2,
		//动作检查状态
		IKUS_CHECKE = 1<<3,
	};

	enum EIKDebugState
	{
		//从马的脚底向上画线，
		IK_DEBUG_LINE_FOOT_UP = 1<<1,
		//从马的脚底的地面向上画线，
		IK_DEBUG_LINE_GROUND_UP = 1<<2,
	};
	class IIKSkeletonModel: public ISkeletonModel
	{
	public:
		//得到IK链的初始端点
		virtual void	GetIKLine( int index,H3DVec3 &pPosBegine,H3DVec3 &pPosEnd ) = 0;
		//得到IK链被调节之后，原端点所在的位置
		virtual void	GetIKPos(int index ,H3DVec3 &begin,H3DVec3 &end ) = 0;

		//通过给定的的矩阵判断马是否着地
		//phySceneId物理世界ID
		//phyObjId物理物体ID
		virtual bool			IsOnTerrain(const H3DVec3 &vPos,const H3DQuat &vQuat,float fEpsilon,bool bforceComputNormal,float &fFrontHeight,float &fBackHeight,H3DVec3& vFrontNormal,H3DVec3& vBackNormal,unsigned int phySceneId,unsigned int phyObjId) = 0;

		//virtual void			GetFeetNormal(const H3DMat4 &transform,H3DVec3 *pNormals) = 0;

		//得到当前马在地面上的姿态
		//vPos.x,vpos.y设置成马当前的坐标，高度返回在vPos.z中
		//qRetRot运算返回的旋转四元数
		//phySceneId物理世界ID
		//phyObjId物理物体ID
		virtual void			GetTransformByTerrain(H3DVec3 &vPos,H3DQuat &qRetRot,unsigned int phySceneId,unsigned int phyObjId) = 0;


		//设置IK更新时的标志，IKUpdateState
		virtual void	SetIKUpdateState(unsigned int nState) = 0;


		//设置调试标志 取值是EIKDebugState的按位或
		virtual void	SetDebugState(unsigned int nState) = 0;



	};

	// actor类型
	enum EActorType
	{
		ACTOR_HUMAN = 0,	// 人
		ACTOR_PET,			// 宠
		ACTOR_TYPE_NUM,
	};

	/// 角色Bodypart位置
	enum EBodypartType
	{
		BODYPART_SKIN = 0,	// 0 皮肤
		BODYPART_EYE,		// 1 眼睛
		BODYPART_FACE,		// 2 脸
		BODYPART_HAIR,		// 3 头发
		BODYPART_UPPER,		// 4 上衣
		BODYPART_HAND,		// 5 手套
		BODYPART_PANTS,		// 6 裤子
		BODYPART_STOCKING,	// 7 袜子
		BODYPART_SHOES,		// 8 鞋
		BODYPART_SUIT,		// 9 套装
		BODYPART_ARM,		// a 胳膊
		BODYPART_NUM,
	};

	/// 宠物Bodypart位置
	enum EPetBodypartType
	{
		PET_BODYPART_FACE = 0,	// 0 头
		PET_BODYPART_BODY,		// 1 
		PET_BODYPART_NUM,
	};

	//! 人物挂件位置
	enum EActorAdornmentPosition
	{
		ACTOR_ADORNMENT_LEFTWRIST = 0,		// 0 左手腕
		ACTOR_ADORNMENT_RIGHTWRIST,			// 1 右手腕
		ACTOR_ADORNMENT_TAIL,				// 2 尾巴
		ACTOR_ADORNMENT_LEFTHAND,			// 3 左手持
		ACTOR_ADORNMENT_RIGHTHAND,			// 4 右手持
		ACTOR_ADORNMENT_BACK,				// 5 背部
		ACTOR_ADORNMENT_HEADGEAR,			// 6 头饰
		ACTOR_ADORNMENT_FACEGEAR,			// 7 面部
		ACTOR_ADORNMENT_EARRING,			// 8 耳环
		ACTOR_ADORNMENT_NECKLACE,			// 9 项链
		ACTOR_ADORNMENT_BRACELET,			// 10 手链
		ACTOR_ADORNMENT_ANKLETS,			// 11 脚链
		ACTOR_ADORNMENT_CHESTBADGER,		// 12 胸章

		ACTOR_ADORNMENT_NUM,
	};
	//! 宠物挂件位置
	enum EPetAdornmentPosition
	{
		PET_ADORNMENT_BACK = 0,		// 0 背部
		PET_ADOENMENT_ANKLETS,		// 1 脚链

		PET_ADORNMENT_NUM,
	};


	//!可换装的骨骼模型，例如人形宠物
	class IAvatarSkeletonModel:public ISkeletonModel
	{
	public:
		//!设置bodypart，参数是bpt文件的路径
		virtual bool SetBodyPart(const char* bpt_path)=0;

		virtual unsigned int SetBodyPartAndFinishTask(unsigned int taskId)=0;

		//!设置挂件，参数0是位置的索引，参数1是spe文件的路径
		virtual bool SetAdornment(EPetAdornmentPosition adornmentposition, const char* adornmentname)=0;

		virtual unsigned int SetAdornmentAndFinishTask(EPetAdornmentPosition adornmentposition, unsigned int taskId) = 0;

		//! 设置挂件的可见性
		//! 为保证向前兼容，挂件默认是可见的
		virtual void			SetAdornmentVisibility(EPetAdornmentPosition adornmentposition, bool inVisibility) = 0;

		virtual int GetSkeletonModels(IModel** pSkeletonModelVector,int vectorSize) = 0;

		virtual int GetAdornmentSkeletonModels(H3DI::IModel** pSkeletonModelVector, int vectorSize) = 0;

		//设置人物是否使用包围体. 返回值1表示成功，小于0不成功
		virtual int SetUseCustomBoundBox (bool b)=0;

		//调试函数
		virtual void	DebugFunction(int i)=0;
	};

	class IActor : public ISkeletonModel
	{
	public:
		virtual bool			SetBodyPart(const char* sBodyName)=0;

		virtual unsigned int	SetBodyPartAndFinishTask(unsigned int taskId)=0;

		virtual void			SetSkinColor(const float* color)=0;

		virtual unsigned int    GetCloth(ICloth** buff, unsigned int buffCount) = 0;
		//add by 2007-12
		//设置ACTOR位置，但是Z永远被设置为0
		virtual void			SetActorLocationMatrix(const H3DMat4& mat)=0;
		//当BODYPART都调入后，拼接BODYPART之间的顶点和法线
		virtual void			PostProcessCreating()=0;

		//动态设置透明排序
		virtual	void			SetThisActorClothSort(bool b)=0;

		virtual bool			GetThisActorClothSort()=0;	

		///by sssa2000 2008.04.25
		// 如果头发穿帮了，那么调用该函数即可
		virtual void			ResetActorHair()=0;

		//调试函数
		virtual void			DebugFunction(int i)=0;

		virtual int GetSkeletonModels(IModel** pSkeletonModelVector,int vectorSize) = 0;

		virtual int GetAdornmentSkeletonModels(H3DI::IModel** pSkeletonModelVector, int vectorSize) = 0;

		//设置人物是否使用包围体. 返回值1表示成功，小于0不成功
		virtual int SetUseCustomBoundBox (bool b)=0;

		//通过bodpyart的名字获取该bodypart 当前在引擎中所有renderable的所有材质。将材质填充到pResArray
		//如果引擎要返回的材质数量大于调用者分配的数组的长度，返回值为-1
		//返回值：返回实际填充的材质个数
		//参数bpName：bodypart的名字，例如104001003，如果是挂件 也类似
		//参数pResArray:由调用者分配的INewShader的数组，
		//参数len:数组的长度
		virtual int GetAllShaderByBodyPartName(const char* bpName,INewShader** pResArray,int arraylen)=0;

		//根据bodypart名字获取INewShader
		// 设置挂件
		virtual bool			SetAdornment(EActorAdornmentPosition adornmentposition, const char* adornmentname) = 0;

		virtual unsigned int	SetAdornmentAndFinishTask(EActorAdornmentPosition adornmentposition, unsigned int taskId) = 0;

		//! 设置挂件的可见性
		//! 为保证向前兼容，挂件默认是可见的
		virtual void			SetAdornmentVisibility(EActorAdornmentPosition adornmentposition, bool inVisibility) = 0;
	};

	/**
	数据模板。由RenderCore由磁盘文件调入。被多个IModel共享。数据资源和共享由引擎管理。用户只需要由
	IGeometry得到IMesh。IMesh也可以由ISubModel得到。
	*/
	class IGeometry: public IObject
	{
	public:
		virtual unsigned int		GetNumMesh()=0;
		virtual IMesh*				GetMesh(unsigned int n)=0;
		virtual const char*			GetFileName()=0;

		virtual const H3DMat4&		GetObjectSlot(int n)const=0;
		virtual void				SetObjectSlot(int n, const H3DMat4& mat)=0;

		virtual int					GetNumObjectSlot()const=0;
	};

	/**
	用来得到骨骼物体的ISkeleton数据。ISkeleton只代表骨骼系统的初始状态。不参与实际运算。
	通过ISkeleton可以得到根骨骼序号以及访问IBone中的信息。
	*/
	class IGeometrySkin : public IGeometry
	{
	public:
		virtual ISkeleton*				GetSkeleton()=0;
		virtual const char*				GetActionName(unsigned int n)=0;
		virtual IAction*				GetAction(unsigned int n)=0;
		virtual IAction*				GetAction(const char* sActionName)=0;
		virtual unsigned int			GetNumAction()const=0;
	};

	class IGeometryActor: public IGeometry
	{
	public:
		virtual unsigned int				GetBodyPartNumber()=0;
		virtual const char*					GetBodyPartName(unsigned int index,unsigned int& nPart)=0;

		/**
		获取当前actor正在使用的mesh
		pBuffer : 用于存放IMesh指针的buffer，可以为NULL，这是仅返回mesh的数量
		bufferSize : buffer的大小，如果buffer不够大，函数返回0
		返回值:mesh的数量
		**/
		virtual unsigned int		GetBodypartUsingMeshes(IMesh** pBuffer, int bufferSize) = 0;
	};

	//lighting system
	enum LIGHT_TYPE
	{
		LIGHT_DIR,
		LIGHT_POINT,
		LIGHT_PROJECT,//can be a spot light
	};

	class ILight : public IMoveObject
	{
	public:
		virtual LIGHT_TYPE		GetLightType()const=0;

		virtual void					GetDiffuseColor(float* vec4)const=0;
		virtual void                    GetSpecularColor(float* vec4)const=0;
		virtual void                    GetAmbientColor(float* vec4)const=0;

		virtual void					SetAmbientColor(const float* col)=0;
		virtual void					SetDiffuseColor(const float* col)=0;
		virtual void					SetSpecularColor(const float* col)=0;
		virtual void					SetRadius(float radius)=0;
		virtual float					GetRadius(void)const =0;
		virtual void					SetIntensity(float intensity)=0;
		virtual float					GetIntensity(void)const=0;
	};
	//光柱类型
	enum EH3DBEAMTYPE
	{
		//带体积感的光柱
		E_H3D_BEAM_VOL,
		//面片光柱
		E_H3D_BEAM_BOARD,
		//后处理光柱
		E_H3D_BEAM_POST,
		//UE光柱
		E_H3D_BEAM_UE
	};
	//光斑参数结构
	struct tGlareProperty
	{
		//尺寸
		float m_width;
		float m_height;
		//颜色
		float m_color[4];
		//贴图
		const char* m_pTextureName;
		//材质lib
		const char* m_pShaderLib;
		//材质实例名
		const char* m_pShaderInstanceName;
		//到光源的距离
		float m_disToLight;
		//旋转速度
		float m_glareRotVel;
		//是否可见
		bool m_bVisable;
		//是否跟随摄像机旋转
		bool m_bRotateWithCamera;
		//是否面向摄像机
		bool m_bViewCamera;

		tGlareProperty()
		{
			m_width = m_height = 1.0f;
			m_color[0] = m_color[1] = m_color[2] = m_color[3] = 1.0f;
			m_pTextureName = 0;
			m_pShaderLib = 0;
			m_pShaderInstanceName = 0;
			m_disToLight = 0.0f;
			m_glareRotVel = 5.0f;
			m_bVisable = true;
			m_bRotateWithCamera = true;
			m_bViewCamera = true;
		}
	};

	enum LightAffectParam
	{
		AFFECT_ALL=0,
		AFFECT_SCENE_ONLY,
		AFFECT_ACTOR_ONLY,

		LIGHTAFFECTPARAM_END
	};
	class IPrePassLight : public IMoveObject
	{
	public:

		virtual void SetLightAffectParam(LightAffectParam t)=0;
		virtual LightAffectParam GetLightAffectParam()=0;

		virtual LIGHT_TYPE				GetLightType()const=0;

		virtual void                    GetColor(float* vec4) const = 0;
		virtual void					SetColor(const float* col) = 0;

		//	光强,方向光光强分为两个，分别影响固有色和高光，其他类型光、延迟渲染只使用第一个光强。
		//	获取光强index=1时取高光光强SpecIntensity,index=0时去原始光强intensity
		virtual void					SetIntensity(float intensity, float SpecIntensity=-1.0f) = 0;
		virtual float					GetIntensity(int index=0) const = 0;


		// 聚光灯的内外角度，光强从内角开始衰减，到外角无光照。单位为角度
		virtual void					GetAngle(float* inner, float* outter) const = 0;
		virtual void					SetAngle(float inner, float outter) = 0;

		// 设置这个灯是否产生阴影以及阴影的颜色
		virtual bool					GetShadowEnable() const = 0;
		virtual void					SetShadowEnable(bool bEnable) = 0;

		virtual void					GetShadowColor(float* vec4) const = 0;
		virtual void					SetShadowColor(const float* col) = 0;

		// 衰减范围，从near开始衰减，到far结束
		virtual void					GetRange(float* nearRange, float* farRange) const = 0;
		virtual void					SetRange(float nearRange, float farRange) = 0;

		// 优先级
		virtual int						GetPriority() const = 0;
		virtual void					SetPriority(int nPriority) = 0;

		// 是否使用投影贴图
		virtual bool					GetProjTextureEnable() const = 0;
		virtual void					SetProjTextureEnable(bool bEnable) = 0;
		// 投影贴图的文件名
		virtual void					SetProjTextureName(const char* strFileName) = 0;

		// 是否使用光斑贴图
		virtual bool					GetFakeLightSpot() const = 0;
		virtual void					EnableFakeLightSpot(bool bEnable) = 0;
		// 光斑贴图的文件名
		virtual void					SetFakeLightSpotTexture(const char* strFileName) = 0;

		//创建一个光柱
		virtual void CreateLightBeam(EH3DBEAMTYPE beamType = E_H3D_BEAM_VOL) = 0;
		//设置光柱类型
		virtual void SetLightBeamType(EH3DBEAMTYPE beamType) = 0;
		//释放光柱.会释放掉当前已经创建的所有光柱类型
		virtual void ReleaseLightBeam() = 0;
		//创建一个光斑.由于一个灯光会有多个光斑,所以这里返回光斑的索引
		virtual int CreateGlare(const tGlareProperty& gPro) = 0;
		//释放光斑
		virtual void ReleaseGlare(int glareIndex) = 0;
		//设置光柱本地矩阵
		virtual void SetBeamLocalMat(const H3DMat4& mat) = 0;
		//设置光斑的属性
		virtual void SetGlareProperty(int glareIndex,const tGlareProperty& gPro) = 0;
		//获取光斑的属性
		virtual void GetGlareProperty(int glareIndex,tGlareProperty& gPro) = 0;
		//设置光柱的可见性
		virtual void SetBeamVisable(bool b) = 0;
		//启用/停用光源
		virtual void SetLightEnable(bool b) = 0;
		//
		virtual bool GetLightEnable() = 0;
		//设置光柱的明暗
		virtual void SetBeamBrightness(float t) = 0;
		//设置光柱的内径（0.1~1）
		virtual void SetBeamInnerRadius(float t) = 0;
		//设置后处理光柱的模糊度(0~1)
		virtual void SetBeamBlurCoeff(float f) = 0;

		// 光柱衰减范围，从near开始衰减，到far结束
		virtual void GetBeamRange(float* nearRange, float* farRange) const = 0;
		virtual void SetBeamRange(float nearRange, float farRange) = 0;
		// 光柱内外角度，单位为角度
		virtual void GetBeamAngle(float* inner, float* outter) const = 0;
		virtual void SetBeamAngle(float inner, float outter) = 0;
		//===============================LightShaft===================================
		//add by liren 2010-11-2 
		//!开启或关闭体积光
		virtual void SetLightShaftEnable(bool bEnable) = 0;
		//!设置体积光颜色
		virtual void SetLightShaftColor(const float *pcolor) = 0;
		//!设置体积光的深度 
		virtual void SetLightShaftDepth(float fDepth) = 0;
		//!体积光是否开启
		virtual bool GetLightShaftEnable() const = 0;
		//!获取体积光颜色
		virtual void GetLightShaftColor(float *pColor) const = 0;
		//!获取体积光的深度 
		virtual float GetLightShaftDepth() const = 0;

		//!设置体积光阈值
		virtual void SetLightShaftThreshold(float fThreshold) = 0;
		//!设置体积光阈值
		virtual float GetLightShaftThreshold()const = 0;
		//!设置体积光强度
		virtual float GetLightShaftIntensity() const = 0;
		//!获取体积光颜色
		virtual void SetLightShaftIntensity(float fIntensity) = 0;
		//===============================!LightShaft===================================

		//!设置灯光的GUID
		virtual void SetGUID(const char* szGUID) = 0;
	};
	///描述一个世外场景的环境信息
	struct OutDoorEnvInfo
	{
		//Light 
		float m_LightDirX;
		float m_LightDirY;
		float m_LightDirZ;

		float m_LightDiffuseR;
		float m_LightDiffuseG;
		float m_LightDiffuseB;

		float m_LightAmibentR;
		float m_LightAmibentG;
		float m_LightAmibentB;

		float m_LightSpecluarR;
		float m_LightSpecluarG;
		float m_LightSpecluarB;

		//以下几个是单独给人物材质专用的
		//////////////////////////////////////////////////////////////////////////
		float m_EnvAmibentR;		//整体环境光
		float m_EnvAmibentG;		//整体环境光
		float m_EnvAmibentB;		//整体环境光

		float m_HemiLightRangeX;	//光照范围
		float m_HemiLightRangeY;	//光照范围
		float m_HemiLightRangeZ;	//光照范围

		/// 标志位，是否使用四盏灯
		bool bUse1stLight;
		bool bUse2ndLight;
		bool bUse3rdLight;
		bool bUse4thLight;

/////   现在一盏灯就一个方向和一个颜色（不再区分为灯光固有色颜色，灯光高光颜色，灯光环境光颜色了）
		float m_1stLightDirX;
		float m_1stLightDirY;
		float m_1stLightDirZ;

		float m_1stLightDiffuseR;
		float m_1stLightDiffuseG;
		float m_1stLightDiffuseB;


		float m_2ndLightDirX;		//人物的第二盏灯
		float m_2ndLightDirY;		//人物的第二盏灯
		float m_2ndLightDirZ;		//人物的第二盏灯

		float m_2ndLightColorR;
		float m_2ndLightColorG;
		float m_2ndLightColorB;

		float m_3rdLightDirX;		//人物的第3盏灯
		float m_3rdLightDirY;		//人物的第3盏灯
		float m_3rdLightDirZ;		//人物的第3盏灯

		float m_3rdLightColorR;
		float m_3rdLightColorG;
		float m_3rdLightColorB;

		float m_4thLightDirX;		//人物的第4盏灯
		float m_4thLightDirY;		//人物的第4盏灯
		float m_4thLightDirZ;		//人物的第4盏灯

		float m_4thLightColorR;
		float m_4thLightColorG;
		float m_4thLightColorB;

		/*
		float m_1stLightDiffuseR;
		float m_1stLightDiffuseG;
		float m_1stLightDiffuseB;

		float m_1stLightAmibentR;
		float m_1stLightAmibentG;
		float m_1stLightAmibentB;

		float m_1stLightSpecluarR;
		float m_1stLightSpecluarG;
		float m_1stLightSpecluarB;

		float m_2ndLightDirX;		//人物的第二盏灯
		float m_2ndLightDirY;		//人物的第二盏灯
		float m_2ndLightDirZ;		//人物的第二盏灯

		float m_2ndLightDiffuseR;	//人物的第二盏灯
		float m_2ndLightDiffuseG;	//人物的第二盏灯
		float m_2ndLightDiffuseB;	//人物的第二盏灯

		float m_2ndLightAmibentR;	//人物的第二盏灯
		float m_2ndLightAmibentG;	//人物的第二盏灯
		float m_2ndLightAmibentB;	//人物的第二盏灯
		*/
		//////////////////////////////////////////////////////////////////////////

		//世界的范围
		float m_WorldMinX;
		float m_WorldMinY;
		float m_WorldMinZ;

		float m_WorldSizeX;
		float m_WorldSizeY;
		float m_WorldSizeZ;

		//天空的颜色
		float m_SkyColorR;
		float m_SkyColorG;
		float m_SkyColorB;

		//地表颜色
		float m_GroundColorR;
		float m_GroundColorG;
		float m_GroundColorB;

		//全局阴影图路径
		const char* m_ShmPath;
		//是否需要强制重新载入阴影图
		bool m_bForceLoadShm;

		//Terrain Light 0 
		float m_TerrainLightDir0X;
		float m_TerrainLightDir0Y;
		float m_TerrainLightDir0Z;

		//Terrain Light 1 
		float m_TerrainLightDir1X;
		float m_TerrainLightDir1Y;
		float m_TerrainLightDir1Z;
	};

	//运行时信息
	struct IRuntimeInfo
	{
		unsigned int AllTriangles;						//场景中所有的三角形数量
		unsigned int ThisFrameTriangles;				//本帧中的三角形数目
		unsigned int AllModelNumber;					//场景中所有的模型数量（包括在透明模型）
		unsigned int AllTransparentModelNumber;			//场景中所有的透明的模型数量
		unsigned int ThisFrameModelNumber;				//本帧中的模型数目（包括透明）
		unsigned int ThisFrameTransparentModelNumber;	//本帧中的透明模型的数量
		unsigned int AllH3DShaderNumber;				//所有的h3dshader对象的数量
		unsigned int ThisFrameH3DShaderNumber;			//本帧中使用的h3dshader数量
		unsigned int ThisFrameShaderChangedNumber;		//本帧中shader切换的次数
		unsigned int AllTextureNumber;					//场景中所有的纹理的数量
		unsigned int RenderStateChangedNumber;			//本帧中渲染状态的改变
		float AllTextureMemory;							//场景中所有纹理占用的内存（kb，下同）
		float ThisFrameTextureMemory;					//本帧中所有纹理占用的内存
		float AllVertexBufferMemory;					//场景中所有的vb占用的内存
		float ThisFrameVertexBufferMemory;				//本帧中使用的vb占用的内存
		float AllIndexBufferMemory;						//场景中所有的ib占用的内存
		float ThisFrameIndexBufferMemory;				//本帧中使用的ib占用的内存
		float fps;										//fps

	};
	enum BILLBOARD_PROPERTY
	{
		SIMPLE_QUAD = 0,//简单四边形，顶点由用户指定
		COMMON = 1<<0,//简单billboard，永远指向镜头
		ROTATE=1<<1,//随镜头旋转而垂直EYE DIR旋转，光晕旋转效果
		ZOCCLUDE=1<<2,//只受中心Z遮挡（没实现）
		HALO=1<<3,//光晕，大小在SCENE SPACE不变（没实现）
		LENFLEAR=1<<4,//镜头光（没实现）
		OPACITY = 1<<5,//（没实现）
		CORRECT_ROT = 1<<6,//与EYE POS到VECPOS的连线垂直, 而不是简单与EYE DIR垂直
		AXIS_ROT = 1<<7,//（不用）饶着Z轴尽量与EYE垂直，Z轴为 mat[2] ,mat[6] , mat[10],矩形的长沿Z轴。需要在编辑器里建立一个RECT
		RADIUS_ROT = 1<<8,//给定一个半径，BILLBOARD以一个球为中心旋转
		DIR_AXIS = 1<<9,//只向一头延伸的billboard_axis或者billboard_ray
	};

	enum BILLBOARD_TYPE
	{
		BILLBOARD_SINGLE,//单个billboard
		BILLBOARD_FLARE,//（没实现）
		BILLBOARD_RAY,//模仿光柱，射线，贴图必须符合光柱贴图要求
		BILLBOARD_AXIS,//长方形billboard。
		BILLBOARD_HALO,//（没实现）
	};
	/**
	billboard即可以代表BILLBOARD，也可以代表一个 四边形面片
	*/
	class IBillboard : public IMoveObject
	{
	public:
		virtual BILLBOARD_TYPE			GetBillboardType()const=0;
		virtual float					GetBillboardRotate()const=0;
		//billboard的旋转是为了给光晕使用。光晕会随着镜头角度转动而转动
		virtual void					SetBillboardRotate(float fRotate)=0;
		//靠COLOR的32-24位控制透明度,ABGR
		virtual void					SetBillBoardColor(unsigned int col)=0;
		virtual unsigned int			GetBillBoardColor()const=0;

		virtual void					SetSize(float fWidth,float fHeight)=0;
		virtual void					GetSize(float &fWidth,float &fHeight)=0;
		//靠属性控制BILLBOARD种类
		virtual void					SetProperty(BILLBOARD_PROPERTY prop)=0;
		virtual BILLBOARD_PROPERTY		GetProperty()=0;
		virtual void					SetRadius(float fRadius)=0;
		virtual float					GetRadius()const=0;
	};


#define MAX_TERRAIN_OBJ_LAYER  16
	enum
	{
		TOBJ_GEOM_LAYER = 0,
		TOBJ_LIGHT_LAYER = MAX_TERRAIN_OBJ_LAYER-1,
	};

	enum
	{
		TERRAIN_MINLOD=1<<0,
		TERRAIN_MINTEX=1<<1,//only use global texture
		TERRAIN_USE_INDOOR_CULLING=1<<2,
		TERRAIN_USE_CONTINUED_WORLD=1<<3,
	};
	// Scene Graph System
	struct tTerrainInfo
	{	
		//各种层次地形节点的长宽
		unsigned int nWidth,nLength,nPageWidth,nPageLength,nPatchWidth,nPatchLength,nLeafWidth,nLeafLength;
		//外部不用填充以下变量，由地形初始化时计算而得。表示各地形节点在四叉树中的层次数
		unsigned int nNumLevel,nPageLevel,nPatchLevel,nLeafLevel;
		//地形每个格子的单位
		float fGridUnit;
		//高度图中高度与实际地形中高度的缩放比例。
		float fHeightScale;
		//外部不管这个参数，置0即可
		int	  iDataType;
		//Alpha贴图的精度
		int	  iAlphaPrecision;
	};

	//得到在场景中搜索的结果，这个结果必须由CLIENT调用RELEASE及时释放
	class ISceneSearch
	{
	public:
		//!!!!!! ISceneSearch must be Released by CLIENT !!!!!!
		virtual void					Release()=0;

		virtual int						GetNumObject(int nIndex)=0;
		virtual IMoveObject*			GetObject(int nIndex,int n)=0;
	};
	//	Terrain System
	class IRender;


	class IScene : public IMoveObject
	{
	public:
		//把一个物体加入场景中
		virtual void					AttachModel(IMoveObject* pObj,int nLayer)=0;

		//把一个物体从场景删除
		virtual void					DetachModel(IMoveObject* pObj)=0;

		//当物体移动时，必须使物体在场景中移动！ 只有CLIENT知道MODEL是否移动了
		//当物体没有移动时，不要调用此函数。
		virtual void					MoveModel(IMoveObject* pObj)=0;	

		//!!!!!! ISceneSearch must be Released by CLIENT !!!!!!
		//use aabb to search
		//使用AABB搜索
		virtual ISceneSearch*			FindObjects(const float* pAABB,const int* pLayers,int numLayer)=0;
		//使用AABB在X，Y平面上搜索，不考虑Z范围
		virtual ISceneSearch*			FindObjects2D(const float* pAABB,const int* pLayers,int numLayer)=0;
		//use IRender's camera to search
		virtual ISceneSearch*			FindObjects(IRender* pRenderer,const int* pLayers,int numLayer)=0;
		//以锥体来搜索，在各种RENDER TO IMAGE的特效中，和SPOT LIGHTING中需要
		//virtual ISceneSearch			FindObjects(tClipPlanes[5],const int* pLayers,int numLayer)=0


		//根据MATRIX得到CAMERA信息（未实现03-12-3)
		virtual void					SetCurrentCamera(const float* pViewMatrix,const float* pProjectMatrix)=0;
		//根据位置和角度得到CAMERA信息（未实现03-12-3)
		virtual void					SetCurrentCamera(const float* vecEyePos,float fov,float ratio,float near, float far)=0;
		//根据IRENDER中当前的CAMERA来设置场景CULLING CAMERA，推荐使用
		virtual void					SetCurrentCamera(IRender* pRenderer)=0;
	};
	//地形细节物体的类型
	enum ETerrainObjectLayer
	{

		ETOL_SmallPatch = 0,
		//草
		ETOL_Grass,
		//细节物体
		ETOL_Tree,
		//动态添加的其它物体
		ETOL_Others,
		//光
		ETOL_Lights,
		//细节物体
		ETOL_DetailObj,
		//特效
		ETOL_SpecialEffect,
		//层数量
		ETOL_LayerCount,
	};


	class ITerrain : public IScene
	{
	public :

		//用户填充一个信息，根信息创建一个地形，高度都为0
		virtual bool					Load(tTerrainInfo *pInfo)=0;	
		virtual bool					Load(const char* sTerrainFileName, ISpecialEffectManager *m_pSpeManager)=0;
		virtual bool					Save(const char* sTerrainFileName)=0;
		//得到地形长宽等数据
		virtual const tTerrainInfo&		GetTerrainInfo()const=0;

		//得到远山
		virtual	IModel*					GetMountainModel() = 0;

		//设置某层可见
		virtual void							SetLayerVisable(ETerrainObjectLayer type,bool bVisable) = 0;

		//设置远截面
		virtual void							SetLayerDist(ETerrainObjectLayer type,float farDist,float nearDist) = 0;

		virtual bool					TurnOff()=0;//*
		//计算LOD

		virtual void					SetFlags(unsigned int nFlags)=0;//*
		virtual unsigned int			GetFlags()const=0;//*
		//绘制
		virtual unsigned int			Render()=0;//*
		virtual unsigned int			RenderMinLOD()=0;//*
		virtual unsigned int			RenderPatchs(const float* boxAABB,float s0,float t0,float s1,float t1,IShader* pIShader,float fRotation)=0;//*
		virtual int 					RenderRect(const float* pAABB,float s0,float t0,float s1,float t1,IShader* pShader,const float* vec4Color,float fRotation)=0;//*


		//得到地形中所有特效数量
		virtual int						GetSpecialEffectNum() = 0;
		//得到当前视锥中的特效
		virtual  void					GetVisableSpecialEffect(ISpecialEffect **pBuffer,int &num) = 0;
		//地形不改变一般不用调用
		virtual void					ReCaculateAABB()=0;//*
		//打开和关闭LOD
		virtual void					EnableLOD(bool bLod)=0;
		virtual void					SetErrorPixel(int nErrPixel)=0;
		virtual int						GetErrPixel()const=0;
		//
		virtual bool					IsLODEnabled()=0;
		//设置整个地形地图在世界坐标的位置。一般，当地形调入时自动设置为地形的中点为（0，0，），但是
		//当CAMERA跨越两个地形时，必须把所有场景中的数据（地形，MODEL）都转换为另一个TERRAIN的坐标
		virtual void					SetCenter(float x,float y,float z)=0;

		virtual void					GetCenter(float& x,float& y,float& z)=0;

		//一般缺省一米为16 。不推荐改变
		virtual void					SetUnit(float unit)=0;
		virtual float					GetUnit()=0;

		//设置地形上的阳光(未实现 RENDERCORE接口03-12-3)
		virtual void					SetGlobalLight(ILight* pLight)=0;
		virtual ILight*					GetGlobalLight()=0;



		virtual float					GetHeight(float x, float y)=0;

		//（UN FINISHED 03-12-3）
		virtual float					GetHeight(const float* pAABB)=0;
		virtual int						GetTriangles(const float* pAABB,float* pVertexBuffer,int nMaxTriangle )=0;
		virtual int						GetTriangles(const float* pAABB,float* pVertexBuffer,unsigned int* pIndexBuffer,int& nNumVert,int& nNumElem,int nMaxVert ,int nMaxIndex)=0;
		virtual int						GetTriangles(float x,float y,float* pVertexBuffer)=0;
		virtual int						GetTriangles(float DirX,float DirY,float DirZ,float* pVertexBuffer)=0;
		virtual int						GetTriangles(float radius,const float* pPos,float* pVertexBuffer)=0;
		virtual bool					GetTriangles(const float* pDir,const float* pPos,float* vecIntersectPoint,float* pVertexBuffer)=0;

		virtual void					SetLODErrPixels(float nNumPixels)=0;
		virtual float					GetLODErrPixels()=0;
		virtual void					SetBaseTileParam(int nLayer, float fXTile,float fYTile)=0;
		virtual void					SetAlphaTileParam(int nLayer, float fXTile,float fYTile)=0;
		virtual void					SetLightmapTileParam(int nLayer, float fXTile,float fYTile)=0;
		virtual int						GetTerrainTriangleNumber()=0;
		// 
		// 		参数：
		// 			pPoints：三角形条带在水平方向上的坐标。数据以条带转折处的两个对应点为一组，连续存储。
		// 			num：条带转折点的组数。
		// 			pVertexBuf：返回值，生成的顶点数据存储在指针所指向的空间中
		// 			ivbSize： 传入pVertexBuf所指空间的大小，以字节单位。传出实际填充的字节数.
		//			pIndexBuf: 返回值，生成的顶点索引数据存储在指针所指向的空间中
		// 			iIbSize： pIndexBuf所指空间的大小，以字节单位。传出实际填充的字节数.
		virtual void					GenerateTriangels( const float* pPoints, int num, void *pVertexBuf, int &vbSize, void *pIndexBuf, int &iIbSize ,float fUVScale) = 0;

		//激活一个地形，一个地形激活的时候，其它地形变为非激活状态
		virtual void					Active() = 0;
		//判断一个地形是否被激活
		virtual bool					IsActive() = 0;
		//编辑器接口，只在编辑器模式下可以调用

		//高度图的size是(length+1)*(width+1)
		virtual float*					GetHeightMap() = 0;

		//用户如果获得高度图指针，并直接修改内存数值，则要添加一个修改区域，以便引擎可以查找相应的地形Patch来更新高度。
		//这个接口传的四个参数是一个矩形的X方向的最小值，X方向的最大值，Y方向的最小值，Y方向的最大值，是以网格数为单位.不是以实际地形的大小为单位
		virtual	void					AddHeightMapDirtyRect(int left,int right,int top,int bottom) = 0;

		virtual	void					SetHeight(int x,int y,float fHeight) = 0;

		virtual	void					ShowWireFrame(bool b) = 0;

		virtual	void					SetLightMap(ITexture *pTexture) = 0;

		virtual bool					GetTriangleInfo(const float* pDir,const float* pPos,float* pVertexBuffer,int &row,int &col,int &ind1,int &ind2,int &ind3)=0;
		//设置某个PATCH的某层贴图id
		virtual bool					SetPatchTexture(int iPatchIndex,int iTextureLayer,unsigned int nID) = 0;
		//得到某个PATCH的某层贴图id
		virtual unsigned int 			GetPatchTexture(int iPatchIndex,int iTextureLayer) = 0;
		//向地形内部贴图列表中添加一个贴图
		virtual bool					AddTextureToList(unsigned int nId,ITexture *pTex,float fUVTilingX,float fUVTilingY,float offsetX,float offsetY) = 0;

		virtual	bool					DeleteTextureFromList(unsigned int nId) = 0;

		virtual bool					UpdateTextureInList(unsigned int nId,ITexture *pTex,float fUVTilingX,float fUVTilingY,float offsetX,float offsetY) = 0;

		//得到地形内部贴图列表中添加一个贴图信息
		virtual ITexture				*GetTextureInfo(unsigned int nId,float& UVTilingXRet, float& pUVTilingYRet,float& pOffsetXRet, float& pOffsetYRet) = 0;
		//计算AlphaMap中和通道的差，可以确定空的通道
		virtual void					GetAlphaLayerDifferen(int iPatchIndex,int &iTextureLayer0,int &iTextureLayer1,int &iTextureLayer2,int &iTextureLayer3,int &iTextureLayer4) = 0;

		virtual int						GetPatchTexNum(int iPatchIndex) = 0;

		//设置一个Patch的贴图层数
		virtual void					SetPatchTexNum(int iPatchIndex,int iTextureLayernum) = 0;
		//AlphaMap的接口
		virtual unsigned int			*GetAlphaMap() = 0;

		virtual	void					AddAlphaMapDirtyRect(int left,int right,int top,int bottom) = 0;

		//一个格占多少个AlphaMapP像素
		virtual	void					SetAlphaMapPrecision(int precision) = 0;

		virtual	int						GetAlphaMapPrecision() = 0;

		virtual void					UpdateNormal() = 0;	


		//设置某个PATCH的AlphaMap
		virtual void					SetPatchAlphaMapPrecision(int iPatchIndex,int intprecision) = 0;
		virtual int						GetPatchAlphaMapPrecision(int iPatchInde) = 0;

		virtual unsigned int*			GetGlobalMap(int iPatchIndex,int intprecision) = 0;
		virtual	void					AddGlobalMapDirtyRect(int left,int right,int top,int bottom) = 0;


		//得到草地分部数据的内存指针
		virtual unsigned short*			GetGrassMap() = 0;
		//修改后设定修改范围
		virtual	void					AddGrassMapDirtyRect(int left,int right,int top,int bottom) = 0;

		//草从的渐隐信息
		virtual void	SetGrassFadeOut(float fFadeOutStart,float fFadeOutEnd) = 0;
		//获得草从的渐隐信息
		virtual void	GetGrassFadeOut(float& fFadeOutStart,float& fFadeOutEnd) = 0;

		//获得当前帧的草从渲染信息,绘制的次数和草的总数
		virtual void	GetGrassRenderInfo(int &nDrawTimes, int &numGrass) = 0;

		virtual void					SetOutDoorEnvInfo(const H3DI::OutDoorEnvInfo& info) = 0;
		virtual void					GetOutDoorEnvInfo(H3DI::OutDoorEnvInfo* info) = 0;

	};

	class IInDoor:public IMoveObject
	{
	public:
		//调入地形文件
		virtual bool					Load(const char* sTerrainFileName)=0;
		virtual bool					TurnOff()=0;
		//Culling
		virtual void					Update()=0;
		//绘制
		virtual unsigned int			Render()=0;
		virtual int 					RenderRect(const float* pAABB,float s0,float t0,float s1,float t1,IShader* pShader,const float* vec4Color,float fRotation)=0;
		//根据MATRIX得到CAMERA信息（未实现03-12-3)
		virtual void					SetCurrentCamera(const float* pViewMatrix,const float* pProjectMatrix)=0;
		//根据位置和角度得到CAMERA信息（未实现03-12-3)
		virtual void					SetCurrentCamera(const float* vecEyePos,float fov,float ratio,float near, float far)=0;
		//根据IRENDER中当前的CAMERA来设置场景CULLING CAMERA，推荐使用
		virtual void					SetCurrentCamera(IRender* pRenderer)=0;
		//地形不改变一般不用调用
		virtual void					ReCaculateAABB()=0;
		//!!!!!! ISceneSearch must be Released by CLIENT !!!!!!
		//use aabb to search
		//使用AABB搜索
		virtual void					ReCaculateBuffer()=0;
		virtual ISceneSearch*			FindObjects(const float* pAABB,const int* pLayers,int numLayer)=0;
		//使用AABB在X，Y平面上搜索，不考虑Z范围
		virtual ISceneSearch*			FindObjects2D(const float* pAABB,const int* pLayers,int numLayer)=0;
		//use IRender's camera to search
		virtual ISceneSearch*			FindObjects(IRender* pRenderer,const int* pLayers,int numLayer)=0;
		//以锥体来搜索，在各种RENDER TO IMAGE的特效中，和SPOT LIGHTING中需要
		//virtual ISceneSearch			FindObjects(tClipPlanes[5],const int* pLayers,int numLayer)=0


		virtual float					GetHeight(float x, float y)=0;
		//（UN FINISHED 03-12-3）
		virtual float					GetHeight(const float* pAABB)=0;
		virtual int						GetTriangles(const float* pAABB,float* pVertexBuffer,int nMaxTriangle )=0;
		virtual int						GetTriangles(const float* pAABB,float* pVertexBuffer,unsigned int* pIndexBuffer,int& nNumVert,int& nNumElem,int nMaxVert ,int nMaxIndex)=0;
		virtual int						GetTriangles(float x,float y,float* pVertexBuffer)=0;
		virtual int						GetTriangles(float DirX,float DirY,float DirZ,float* pVertexBuffer)=0;
		virtual int						GetTriangles(float radius,const float* pPos,float* pVertexBuffer)=0;
		virtual bool					GetTriangles(const float* pDir,const float* pPos,float* vecIntersectPoint,float* pVertexBuffer)=0;

	};

	enum FOG_TYPE
	{
		FOG_LINEAR,
		FOG_EXP,
		FOG_EXP2,
		FOG_VERTEX,
	};


	/**
	显示模式设置
	*/
	enum
	{
		DEVMODE_DYNAMIC  ,//非全屏
		DEVMODE_TEST ,
		DEVMODE_FULLSCREEN ,//全屏
		DEVMODE_RESET ,
		DEVMODE_NORESET,
	};

	enum EAAMode
	{
		AA_Disable = 1<<0,
		AA_2 = 1<<1,
		AA_4 = 1<<2,
		AA_6 = 1<<3,
		AA_8 = 1<<4,
		AA_10 = 1<<5
	};

	enum EAFMode
	{
		AF_Disable = 1<<0,
		AF_2 = 1<<1,
		AF_4 = 1<<2,
		AF_8 = 1<<3,
		AF_16 = 1<<4
	};


	struct tWindowCreateInfoImp
	{
		tWindowCreateInfoImp()
		{
			instance = 0;
			hWnd = 0;
			nLeft = nTop = 0;
			nWidth = 640;
			nHeight = 480;
			uColorbit = 32;
			uDepthbit = 24;
			uStencilbit = 8;
			uTexturebit = 32;
			uFreq = 60;
			uDevMode = DEVMODE_DYNAMIC;//DEVMODE_DYNAMIC
			uAlphabit  = 8;
			uWinWidth = 640;
			uWinHeight = 480;
			uWinTop = 0;
			uWinLeft = 0;
			vSync = false;
			aaMode = AA_Disable;
		};
		HINSTANCE instance;
		HWND		hWnd;
		int nLeft,nTop,nWidth,nHeight;
		unsigned short uColorbit;//16,32
		unsigned short uDepthbit;//16,24,32
		unsigned short uStencilbit;//0,8
		unsigned short uTexturebit;//16,32
		unsigned short uDevMode;
		unsigned short uFreq;//60,70,75,80,85Hz
		unsigned short uAlphabit;//8 or 0
		unsigned short uWinWidth,uWinHeight,uWinTop,uWinLeft;//Window's area
		bool vSync;
		EAAMode aaMode;
	};


	/**
	设置清除屏幕BUFFER标志
	*/
	enum
	{
		CLEAR_BUF_COLOR =  1<<0,
		CLEAR_BUF_DEPTH = 1<<1,
		CLEAR_BUF_STENCIL = 1<<2,
	};


	enum
	{
		DRAW_POINTS,
		DRAW_LINES ,
		DRAW_LINE_LOOP,
		DRAW_LINE_STRIP ,
		DRAW_TRIANGLES ,
		DRAW_TRIANGLE_STRIP ,
		DRAW_TRIANGLE_FAN ,
		DRAW_QUADS  ,
		DRAW_QUAD_STRIP,
		DRAW_POLYGON
	};


	enum
	{
		VB_STATIC = 1<<0,
		VB_DYNAMIC = 1<<1,
		VB_WRITE = 1<<2,
		VB_READ = 1<<3,
		VB_COPY = 1<<4,

	};

	enum
	{
		VB_VERTEX_ARRAY,
		VB_ELEMENT_ARRAY,
		VB_BUFFER,
	};
	enum PIPE_TYPE
	{
		PIPE_COMMON=0,//非透明物体,可受全局光照
		PIPE_TRANSPARENT,//透明物体
		PIPE_LOCAL_LIGHT,//动态光照
		PIPE_LOCAL_LIGHT_TRANSPARENT,//透明物体的动态光源光照
		PIPE_PROJECT_SHADOW,
		PIPE_IMAGE_SHADOW,//Hardware Shadowmap
		PIPE_GLOW,
		PIPE_UNKNOWN,
		PIPE_MAX_NUMBER,
	};

	///阴影技术的实现
	enum SHADOWMAP_TECHNIQUE
	{
		SM_NONE=0,					//无阴影
		SM_POINT_DEFAULT,			//最原始的电光源实现
		SM_POINT_PSM,				//透视阴影贴图
		SM_DIR_CASCADED,			//方向光的平行分割法阴影贴图
		SM_END
	};
	enum//pipe flags
	{
		PIPE_GLOBAL_LIGHTING = 1<<0,
		PIPE_LOCAL_LIGHTING = 1<<1,
		PIPE_RENDERIMAGE = 1<<2,
		PIPE_MIRROR = 1<<3,
		PIPE_ENABLE_BLEND = 1<<4,
		PIPE_DISABLE_DEPTH_WRITE = 1<<5,
		PIPE_ENABLE_ALPHA_TEST = 1<<6,
		PIPE_ENABLE_STENCIL_TEST = 1<<7,
		PIPE_DISABLE_DEPTH_TEST = 1<<8,
		PIPE_ENABLE_STENCIL_WRITE = 1<<9,
		PIPE_ENABLE_SISSOR_TEST = 1<<10,
		PIPE_ENABLE_TWO_SIDE_STENCIL_TEST =1<<11,
		PIPE_ENABLE_DEPTH_BOUND_TEST = 1<<12,
		PIPE_ENABLE_HARDWARE_LIGHTING = 1<<13,
		PIPE_ENABLE_CLIP_PLANE = 1<<14,
		PIPE_DISABLE_COLOR_MASK = 1<<15,
		PIPE_ENABLE_PIPE_SHADER = 1<<16,
		PIPE_ENABLE_SIMPLE_DRAWING = 1<<17,//只使用PIPE自己的SHADER，简单绘制SUBMODEL里的网格
	};
	//////////////////////////////////////////////////////////////////////////
	//thread task flags
	enum ETaskState
	{
		TASK_OK = 0,
		TASK_WORKING,
		TASK_ERROR,
		TASK_CANCELED,
		//! io error code
		TASK_TOO_MANY,
		IOERR_SHADERLIB_FORBIDEN,
		IOERR_SHADERLIB_IOERR,
		IOERR_MODEL_IOERR,
		IOERR_ACTION_IOERR,
		IOERR_ACTOR_IOERR,
		IOERR_BODYPART_IOERR,
		IOERR_ACTOR_CLONE,
		IOERR_UNKNOWN,
	};	

	enum EResourceType
	{
		RES_Texture = 0,
		RES_Image,
		RES_StaticMesh,
		RES_Action,
		RES_ACTOR,
		RES_GEOMETRY,
		RES_BODYPART
	};

	class IEngineMonitor
	{
	public:
		virtual size_t GetResourceCount(EResourceType type)const = 0;
		virtual size_t GetGarbageCount(EResourceType type)const = 0;
		virtual size_t GetResourceFootPrint(EResourceType type)const = 0;
		virtual size_t GetGarbageFootPrint(EResourceType type)const = 0;
		virtual size_t GetAllocatedMemory(void)const = 0;
		virtual size_t GetAllocatedVideoMemory(void)const = 0;
		virtual void DumpResourceInfo(EResourceType type, const char* fileName)const = 0;

	protected:
		virtual ~IEngineMonitor(){}
	};

	enum ERuntimeMode
	{
		RUNTIME_DX7 = 0,
		RUNTIME_DX9
	};

	enum ETextureFormat
	{
		FMT_RGBA8 = 0,
		FMT_RGB8,
		FMT_D24S8,
		FMT_D24X8,
		FMT_D16,
		FMT_A8,
		FMT_RGBA16F,
	};

	enum ERenderTargetType
	{
		RT_COLOR = 0,
		RT_DEPTH
	};

	struct tDrawQuad
	{
		float x;
		float y;
		float width;
		float height;
		float u;
		float v;
		float uWidth;
		float vHeight;
		float color[4];
	};

	enum EShadowQuality
	{
		Shadow_Off = 0,
		Shadow_Hard,
		Shadow_Soft,
		Shadow_Fake
	};

#define ADAPTER_DESC_LEN 256
	struct tPerfData 
	{
		//<1000, no aa/af, no shadow
		//1000-1500 no aa/4xaf, hard shadow
		//1500-2000 2xaa/4xaf, hard shadow
		//2000-3000 2xaa/8xaf, hard shadow
		//>3000 4xaa/8xaf, soft shadow
		unsigned int fillrate; //MP/s

		unsigned int videoMem; //MB
		unsigned int sysMem; //MB
		unsigned int matrixOps; //M/s

		//<1500 disable cloth
		//>1500 enable cloth
		unsigned int cpuFrequency; //MHz

		bool mmx;
		bool sse;
		bool sse2;
		bool _3dnow;
		char adapterName[ADAPTER_DESC_LEN];
	};

	class ILevel;
	class ICamera;
	class IParticleVB;
	class IRenderStateManager;
	class IPerfMonitor;
	class IRenderTarget;
	class IFog;
	typedef int (*PipeSettingFunc)() ;

	enum EEngineEventType
	{
		EET_DeviceReset = 0
	};

	class IEngineEventHandler
	{
	public:
		virtual void HandleEvent(EEngineEventType type) = 0;
	};


	enum IMAGE_KIND
	{
		IMAGE_BMP=0,
		IMAGE_JPG,
		IMAGE_PNG,
		IMAGE_TGA,
		IMAGE_DDS,
		IMAGE_UNKONWN
	};
	enum IMAGE_ERROR
	{
		IMAGE_SUCCESS=0,
		FILENAME_ERROR, //文件名为空
		FILE_NOT_EXIST,
		READ_FILE_ERROR,
		BUFFER_SIZE_ERROR,
		IMAGE_KIND_UNKNOWN,
		TEMP_SAVE_JPG_FAILED,
		CAN_NOT_GET_FILE_SIZE,
		IMAGE_TOO_LAGRE,
		COPY_PIXEL_ERROR,
		SCALE_ERROR,

		IMAGE_ERROR_UNKNOWN
	};
	enum IMAGE_OPERAT
	{
		IMAGE_SCALE=0,
	};
	enum COMPRESS_TYPE
	{
		COMPRESS_JPEG=0,
		COMPRESS_DXT
	};

	enum IMG_PROCESS
	{
	};

	struct tImgProcessParam
	{
	};

	//图片处理类
	class IImage
	{
	public:
		/*得到image的信息，长宽，大小
		//filename:文件名
		//imagemode:文件类型，jpg,bmp,tga等等
		//w,h 供函数填充的长宽
		//infobufferlen 原始数据的长度(raw data)
		//jpgbuferlen 转换为jpg后数据的长度

		本函数实际上已经将图像读入内存，并且通过暂存Jpg到磁盘的方法获得jpg图像的大小
		*/
		virtual IMAGE_ERROR get_image_info(const char* filename, unsigned int& w, unsigned  int& h, long& jpgbuferlen)=0;

		/*缩放图像
		//tranmode操作的类型，目前只有缩放一种
		//orgw,orgh原始数据的长宽
		//desw,desh要缩放到的长宽
		//buffer原始Raw Data的数据
		//desbuffer变换后数据存放的内存
		//deslength为desbuffer内存的长度

		注意：这里缩放使用的数据以及获得的数据都是RawData，RawData数据长度计算的公试为：
		字节数=	长*宽*4 (4表示RGBA 四个分量)
		*/
		virtual IMAGE_ERROR tranform_image(IMAGE_OPERAT tranmode,unsigned int orgw,unsigned int orgh,unsigned int& desw, unsigned int& desh, unsigned char* buffer, unsigned char* desbuffer, unsigned int deslength)=0;

		/*获取图像数据原始
		filename为磁盘上的图像文件名，该文件名必须和传入get_image_info（）的文件名相同，否则不能获得图像内容
		buffer为保存RAW DATA的内存
		length为内存的长度，可以通过以上给出的公式计算
		*/
		virtual IMAGE_ERROR get_raw_data(const char* filename,unsigned char* buffer,unsigned int length)=0;

		/*
		获取压缩后的数据
		filename为磁盘上的图像文件名，该文件名必须和传入get_image_info（）的文件名相同，否则不能获得图像内容
		compressType为压缩类型，目前只支持jpg
		buffer为保存RAW DATA的内存
		length为内存的长度，可以通过以上给出的公式计算
		*/
		virtual IMAGE_ERROR get_compress_data(const char* filename,COMPRESS_TYPE compressType,unsigned char* buffer,unsigned int length)=0;

		/*
		从压缩格式到RawData的转换
		compressType压缩类型
		compressBuffer 压缩文件的数据
		compressBufferLen压缩文件数据的长度
		rawDataBuffer原始数据的内存
		rawWidth,rawHeight 原始数据的长宽
		*/
		virtual IMAGE_ERROR compressData2RawData(COMPRESS_TYPE compressType,const unsigned char* compressBuffer,unsigned int compressBufferLen,unsigned char* rawDataBuffer,unsigned int& rawWidth,unsigned int& rawHeight,long MaxRawBufferLen)=0;

		/*
		从RawData到 压缩格式的转换
		compressType压缩类型
		compressBuffer 压缩文件的数据
		MaxCompressBufferLen 压缩数据最大长度，如果超过此长度，会返回BUFFER_SIZE_ERROR,压缩完毕后会修改此变量为buffer的实际长度
		rawWidth/ rawHeight 压缩文件数据的长度
		rawDataBuffer原始数据的内存
		rawBufferLen 原始数据的长度，可以使用上面给出的公式计算
		*/
		virtual IMAGE_ERROR RawData2CompressData(COMPRESS_TYPE compressType,const unsigned char* rawDataBuffer,unsigned int rawWidth,unsigned int rawHeight,unsigned char* compressBuffer,long& MaxCompressBufferLen)=0;


		virtual IMAGE_ERROR SaveRaWToFile(const char* filename,const unsigned char* data,unsigned int width,unsigned int height)=0;
		/*
		得到目前内存中的图像是对应哪个磁盘文件
		*/
		virtual const char* GetCurrentFileName()=0;
		virtual IMAGE_ERROR loadImage(tImgProcessParam* ImgProcessParam)=0;
		virtual IMAGE_ERROR saveImage(tImgProcessParam* ImgProcessParam)=0;
		virtual IMAGE_ERROR processImage(tImgProcessParam* tmgProcessParam,tImgProcessParam* ImgProcessParam2=0)=0;


	};
	//add by liren 2010-8-25
	//!后处理
	class IPostProcessEffect : public IObject
	{
	public:
		//!添加一个阶段
		virtual void AddPhase(const char * pFileName) = 0;
		//!删除一个阶段
		virtual void DelPhase(const char * pFileName) = 0;
		//!键接
		virtual void LinkEffect() = 0;
		//!设置参数
		virtual void SetParamValue(const char * pName,void* pValue) = 0;
		//!判断一个阶段是否存在
		virtual bool HasPhase(const char *) = 0;
	};

	//nIOFlags 标志IO类型，目前只有2种，普通阻塞同步，优先阻塞同步
	enum
	{
		IO_SYC=0,
		IO_URGENT_SYC,
	};

	//!场景类型
	enum EPhySceneType
	{
		//!布料
		SCENE_CLOTH = 0,
		//!前端
		SCENE_FRONT,
		//!后端
		SCENE_BASE
	}; 

	//!碰撞面类型
	enum ECollisionPlaneType
	{
		//!OBB
		COLLISIONPLANE_OBB = 0,
		//!三角形面
		COLLISIONPLANE_TRIANGLEMESH,
		//!静态物体,道具?
		COLLISIONPLANE_STATIC
	};

	//!OBB碰撞信息
	struct tCollisionObbInfo
	{
		tCollisionObbInfo()
		{
			name = 0;

			worldMat[0] = worldMat[5] = worldMat[10] = worldMat[15] = 1;
			worldMat[1] = worldMat[2] = worldMat[3] = worldMat[4] = 0;
			worldMat[6] = worldMat[7] = worldMat[8] = worldMat[9] = 0;
			worldMat[11] = worldMat[12] = worldMat[13] = worldMat[14] = 0;

			lineVelocity[0]=lineVelocity[1]=lineVelocity[2]=0;
			angVelocity[0]=angVelocity[1]=angVelocity[2]=0;
			back_left_bottom[0]=back_left_bottom[1]=back_left_bottom[2]=0;
			front_right_top[0]=front_right_top[1]=front_right_top[2]=0;

			bUpdateSize = false;
			deltaTime = 0.0f;
			invalidNums = unCollisionTypeNums = 0;
		}

		//!碰撞物体ID
		unsigned int name;
		//!OBB矩阵
		float	 worldMat[16];
		//!线速度
		float	 lineVelocity[3];
		//!角速度
		float	 angVelocity[3];
		//!记录原始数据
		float	 back_left_bottom[3];
		float	 front_right_top[3];
		//!是否需要改变OBB大小
		bool		 bUpdateSize;
		//!时间,用于计算当前位置
		float    deltaTime;
		//!忽略碰撞物体ID列表。凡是在这个列表中的物体不检测该OBB和其的碰撞
		unsigned int invalidObjects[10000];
		int invalidNums;
		//!忽略碰撞类型
		int unCollisionTypes[1024];
		int unCollisionTypeNums;
	};

	//!静态网格信息
	struct tCollisionStaticMeshInfo
	{
		tCollisionStaticMeshInfo()
		{
			name = 0;
			vertexs = 0;
			max_vertex = 0;
			faces = 0;
			max_face = 0;
		}

		//!静态网格ID
		unsigned int name;
		//!顶点数组
		H3DVec3* vertexs;
		//!顶点个数
		int		 max_vertex;
		//!面索引数组
		int*	faces;
		//!面数目
		int      max_face;
	};

	//碰撞点结构
	struct tContactPoint
	{
		//碰撞点
		float point[3];
		//碰撞点所在面类型
		unsigned int planeType;
		//面索引
		int     faceIdx;
		//面法线
		float collNormal[3];
	};

	struct tCollisionResultInfo
	{
		tCollisionResultInfo()
		{
			collPointNums = 0;
			collisionPoints = 0;
		}
		//碰撞点数量
		int		 collPointNums;
		//碰撞点
		tContactPoint* collisionPoints;
		//最大碰撞点数量
		static const int maxCollisionPointsNum = 1024;
	};

	//镜头光参数
	struct tLensFlareParameters
	{
		tLensFlareParameters()
		{
			memset(color,0,sizeof(color));
			size = 0.0f;
			farFromSun = 0.0f;
			flareType = "Halo_Default";
			matName = "../resources/media/shaders/halo_default.xml";
		}
		float color[4];
		float size;
		float farFromSun;
		const char* flareType;
		const char* matName;
	};
	struct tLensEnv
	{
		tLensEnv()
		{
			minAngle = maxAngle = 0.0f;
			maxSunPixels = 10000;
			sunRangeDamping = angleDamping = 0.0f;
			sunPos[0]=sunPos[1]=sunPos[2]=0.0f;
		}
		float minAngle;
		float maxAngle;
		unsigned int maxSunPixels;
		float sunRangeDamping;
		float angleDamping;
		float sunPos[3];
	};
	
	//摄象机类型
	enum ECameraType
	{
		ECT_Render = 0,
		ECT_Culling = 1
	};

	//引擎使用者，某些针对编辑器的需求需要显示调用IRender::SetUser接口
	enum EngineUserDefine
	{
		EUD_UNKONWN=0,
		EUD_CLIENT,
		EUD_EDITOR
	};

	//INFO类型枚举
	enum InfoType
	{
		NONE_INFO		=0,   
		MODEL_INFO			,/// 模型
		ACTOR_INFO			,/// 角色
		TEXTURE_INFO		,/// 贴图
		MATINS_INFO			,/// 材质实例
		LPPLIGHT_INFO		,/// 灯光
		EFFECT_INFO			,/// 特效
		RENDERTARGET_INFO	,/// renderTarget
		POSTEFFECT_INFO		,/// 后处理
		BEAM_INFO			,/// 光柱
		RENDER_INFO			,/// 渲染 
		GENFX_INFO			,/// 生成fx
		CLOTH_INFO			,//	 布料
		LOGTYPENUM
	};
	//错误的种类
	enum ErrorType
	{
		WARNING_ERROR = 0,
		CRITICAL_ERROR,
		LOGERRNUM
	};
	//输出目标
	enum OutPutFlag
	{
		OutPut_File			= 1<<0,
		OutPut_Console		= 1<<1,
		OutPut_RenderWindow = 1<<2
	};

	//!IO线程Task执行状态监控，测试用例使用
	class ProcessIOLisenter;
	struct PrintScreenInfo
	{
		int width;
		int height;
		int bitPerPix;
		const void* pImageData;
	};
	class IRender
	{

	public:
		virtual ~IRender()=0{};


		virtual const char*				GetCoreVersionInfo()=0;
		virtual void*					GetWindowHandle()=0;
		virtual void					SetWorkingDirectory(const char* sDir)=0;

		///创建主窗口
		virtual int						CreateRenderWindow(const tWindowCreateInfoImp& info)=0;
		///创建附加窗口
		virtual int						CreateAddionalRenderWindow(HWND hwnd,int w,int h)=0;

		///设置当前活动的渲染窗口的ID，返回值小于0表示失败。该函数的作用是多窗口渲染的时候指定接下来的绘制 是绘制到哪个窗口上
		virtual int						SetCurrentRenderWindow(int windowID)=0;

		virtual void					GetCurrentWindowSetting(tWindowCreateInfoImp& info)=0;

		virtual bool					InitRenderWindow(const tWindowCreateInfoImp& info)=0;

		virtual void					SetWindowResource(void* pWindowHandle,void* pDisplayContextHandle,void* pOther)=0;

		virtual void					ChangeDisplaySetting(const tWindowCreateInfoImp& info)=0;
		virtual bool					GetCurrentWindowMode()=0;

		///窗口缩放，最后一个参数是窗口的ID,默认的-1表示是主窗口
		virtual bool					ResizeWindowForEditor(int w,int h,int windowID=-1)=0;
		virtual bool					ResizeWidnowEx(int w,int h,bool windowed,bool topmost,bool popup,bool maxbox,bool pad_win_frame_size=true,int windowID=-1)=0;

		///sssa2000 08.04.03  !强迫设备lost，用于vista下
		virtual bool					ResetDevice()=0;	
		///Set Gamma
		virtual unsigned int			SetGamma(float fGamma)=0;
		virtual float					GetGamma()const=0;

		virtual void					ResetContext()=0;

		//Render framework
		virtual void					FrameBegin()=0;
		virtual void					FrameEnd()=0;
		virtual void					SwapBuffer(bool bReallyPresent = true)=0;
		virtual unsigned int			GetClearFlags()=0;
		virtual void					SetClearFlags(unsigned int nFlags)=0;
		virtual void					ClearScreen()=0;
		virtual void					SetClearColor(const float *col)=0;
		/// 设置场景环境光颜色
		virtual void					SetAmbientColor(const float *col)=0;
		/// 设置角色环境光颜色			
		virtual void					SetActorAmbientColor(const float *col)=0;
		virtual void					SetWireMode(bool bWire)=0;
		virtual void					UpdateCamera()=0;
		//!创建物理场景
		virtual bool				    CreatePhyWorld(int& outId)=0;
		//!创建OBB
		virtual bool					CreateObbCollisionData(unsigned int name,IMoveObject* pModel,int phyId)=0;
		//!创建triangleMesh,参数是读取过后的碰撞点和索引
		virtual bool					CreateTriangleMesh(unsigned int name,const H3DVec3* points,const unsigned short* indexs,const H3DVec3* normals,int vertexNums,int triNums,int phyId)=0;
		//!加载ASE格式的triangleMesh。内存由外界分配.需要注意的是该接口需要调用2次,1次传出大小,1次填写数据.当传入的内存指针是0时填写大小
		virtual bool					LoadTriangleMesh(const char* aseName,int& vertexNums,int& triNums,H3DVec3* points,unsigned short* indexs,H3DVec3* normals)=0;
		//!释放碰撞数据
		virtual void					ReleaseCollisionData(unsigned int name,int phyId)=0;
		//!释放物理世界
		virtual void					ReleaseCollisionScene(int phyId) = 0;
		//!设置碰撞数据
		virtual void					SetCollisionData(const tCollisionObbInfo& obbInfo,int phyId)=0;
		//!更新物理引擎
		virtual void					UpdatePhx(int phyId,unsigned int interval)=0;//更新物理必须由外部进行
		//!老接口
		virtual void					UpdatePhx(unsigned int interval=0)=0;//更新物理必须由外部进行
		//!设置物理世界的属性,包括最小时间片,模拟时间(为负值表示取实际的渲染时间,为正值表示恒定模拟时间片,重力值
		virtual void					SetPhxPara(float fixedTime,float simTime,float gravity)=0;
		//!获取碰撞结果,传入一个物体ID,物理世界ID,返回和其发生碰撞的物体ID,类型,碰撞点,碰撞面,碰撞法线等信息
		virtual bool					GetCollisionResult(int phyId,unsigned int& collName0,int& collType0,unsigned int& collName1,int& collType1,tCollisionResultInfo& collInfo)=0;
		
		//!和某指定物体的射线查询.phxWorldId:物理世界id,objId:被查询的物体ID.返回1表示查询成功,0表示查询失败
		//目前只支持和桥梁类型的碰撞物体查询
		virtual int						RayTestSingObject(float x,float y,H3DVec3& collRes,unsigned int phxWorldId,unsigned int objId) = 0;
		
		//by sssa2000 08.04.08
		virtual void SetEnableAllPhy(bool b)=0;
		virtual bool GetEnableAllPhy()=0;
		//by lzp,释放掉物理世界
		virtual void ReleasePhxScene()=0;
		//获取切片数据,传入一段足够大的内存,返回实际填充的大小,idBufferSize表示数组元素个数
		virtual bool GetPhxWorldCopyInfo(int phyId,unsigned int* pIdBuffer,unsigned int idBufferSize,unsigned int& idRealSize,char* pBuffer,unsigned int bufferSize,unsigned int& realSize) const= 0;
		//设置切片数据,传入数据Buffer,buffer大小.idBufferSize表示数组元素个数
		virtual void SetPhxWorldCopyInfo(int phyId,const H3DI::IMoveObject*const * pIdBuffer,unsigned int idBufferSize,unsigned int idRealSize,const char* pBuffer,unsigned int bufferSize,unsigned int realSize) = 0;

		// camera functions
		virtual void					SetViewport(const unsigned short*vp)=0;
		virtual void					GetViewPort(unsigned short*vp)=0;

		virtual void					SetPerspective(const H3DMat4& mat) = 0;
		virtual void					GetPerspective(H3DMat4& mat) = 0;
		virtual void					SetViewMatrix(const H3DMat4& mat) = 0;
		virtual void					GetViewMatrix(H3DMat4& mat) = 0;
		virtual void					SetEyePosition(const H3DVec3& pos) = 0;
		virtual void					GetEyePosition(H3DVec3& pos) = 0;
		virtual void					LookAt(const H3DVec3& eyepos, const H3DVec3& at, const H3DVec3& up) = 0;

		virtual void					RotateDirection(float yaw_offset,float pitch_offset,float roll_offset)=0;
		virtual void					SetCameraRotation(float yaw,float pitch,float roll)=0;
		virtual void					GetRotateDir(float& yaw,float& pitch,float& roll)=0;

		virtual void					GetEyeDirection(H3DVec3& vec) = 0;
		virtual void					SetFrustum(float fov,float ratio,float fNear,float fFar,ECameraType camType = ECT_Render)=0;
		virtual void					GetFrustum(float& fov,float& ratio,float& fNear,float& fFar,ECameraType camType = ECT_Render)=0;
		//-------------------------------------------------------
		//add by sssa2000 08.11.27
		//以下2个函数是为了辅助调试添加的，其中传入的指针必须是分配好空间的，且不小于8的数组,函数会把指定的值复制到数组中
		//成功后，数组中前4个为 near,后4个为far 平面
		virtual void					GetCullFrustumCornerPoint(H3DVec3* p)=0;
		virtual void					GetRenderFrustumCornerPoit(H3DVec3* p)=0;
		//---------------------------------------------------------
	
		virtual void					SetFarDist(float fFar)=0;
		virtual int						IsAABBInFrustum(const float* boxWorld)=0;


		virtual IModel*					CreateModel(const char* sFileName,int nIOFlags=0)=0;
		virtual IModel*					CreateModel(sCreateOp& op,const char* sFileName,int nIOFlags=0)=0;

		virtual ISpecialEffect*			CreateSpe(const char* sFileName, int nIOFlags = 0) = 0;

		virtual IModel*					CreateModel(const char* sFileName, const H3DMat4& matLocate, IScene* pScene, int nLayer) = 0;
		virtual IModel*					CreateActor(const char* sActorName, bool bMale)=0;
		virtual IModel*					CreateActor(sCreateOp& op,const char* sActorName, bool bMale)=0;

		virtual IAvatarSkeletonModel*	CreateAvatarSkeletonModel(const char* sActorName, bool bMale)=0;
		virtual IAvatarSkeletonModel*	CreateAvatarSkeletonModel(sCreateOp& op,const char* sActorName, bool bMale)=0;

		virtual IModel*					CreateEquipment(const char* sEquipmentName)=0;
		virtual IReflectModel*			CreateReflectModel(const char* sFileName)=0;
		virtual void					CleanAllModels()=0;
		virtual unsigned int			RenderModel(IModel* pModel)=0;

		//draw index and vertex buffer
		virtual IVB*					GetDynamicVB()=0;

		virtual void					DrawIndex(PRIMITIVE_TYPE nTriangleType,unsigned int nElemNum,unsigned int nVertNum,unsigned int nNormalOffset,unsigned int nTexcoordOffset,unsigned int nColorOffset,unsigned int nTexcoordOffset2)=0;
	
		//shader functions

		virtual bool					OpenShaderLib(const char* sFileName,int nIOFlags=0)=0;
		virtual unsigned int 			OpenShaderLibAsyn(const char* sFileName,int scale, int compress)=0;
		virtual void					CleanShaderLib()=0;
		virtual void					ReloadAllShader()=0;
		virtual unsigned int			GetCurShaderLibNum()=0;
		virtual const char*				GetCurShaderLibShaderName(unsigned int n) = 0;
		virtual IShader*				GetShader(const char* sName)=0;
		virtual IShader*				GetShaderThreadSafe(const char* sName)=0;
		virtual void					SetShader(IShader* pShader)=0;
		virtual unsigned int			GetNumShaders()=0;
		virtual const char*				GetShaderName(unsigned int n)=0;
		virtual IShader*				GetShader(unsigned int n)=0;
		virtual bool					UpdateTexture(IShader* pShader,unsigned int nPass,unsigned int nStage,unsigned char* pTexBuffer,
			unsigned int x,unsigned int y,unsigned int z,unsigned int w,unsigned int h,unsigned int l)=0;
		virtual void					CopyTexture(IShader* pShader,unsigned int nPass,unsigned int nStage,
			unsigned int x,unsigned int y,unsigned int z,unsigned int w,unsigned int h,unsigned int l)=0;

		//从外部文件载入一个地形
		virtual ITerrain*				CreateTerrain(bool EditMode = false)=0;	

		virtual void					SetTerrainHorizonCulling(int nHorizonDist,int nTestDist)=0;
		virtual void					GetTerrainHorizonCulling(int& nHorizonDist,int& nTestDist)=0;
		virtual int						IsTerrainHorizonCulling()=0;
		virtual int						HorizonTestBBox(const float* box)=0;
		virtual void					RenderHorizon()=0;

		virtual ISpecialEffectManager* CreateEffectManager() = 0;

		//////////////////////////////////////////////////////////////////////////
		//INDOOR
		virtual IInDoor*				CreateInDoor(const char* sFileName)=0;

		//////////////////////////////////////////////////////////////////////////
		//
		//light
		
		virtual ILight*					CreateLight(LIGHT_TYPE type)=0;
		//将中的参数设置给地形的全局光照

		virtual IBillboard*				CreateBillboard(BILLBOARD_TYPE type,BILLBOARD_PROPERTY property)=0;



		//////////////////////////////////////////////////////////////////////////
		//Pipe Functions
		virtual void					PushModel(IModel* pModel)=0;
		//放入所有CBillboard,CUserObject
		virtual void					PushMoveObject(IMoveObject* pMoveObj)=0;
		virtual void					PushNewPipe(PIPE_TYPE type,unsigned int flags,ILight* pLight, PipeSettingFunc pStartFunc=0,PipeSettingFunc pEndFunc=0)=0;
		virtual void					ProcessCurrentPipe()=0;//对其中物体进行排序等操作,所有管道都需要此操作
		virtual unsigned int			RenderPushedPipes()=0;//绘制已经压入的所有PIPE 
		virtual unsigned int			RenderTransparentPipe()=0;
		virtual void					CleanPushedObjsAndSubModels()=0;
		virtual void					SetTransparentState()=0;
		virtual void					ClearTransparentState()=0;


		virtual void					GlareProcess(bool bUse,float explosure)=0;


		//pre-lighting interface by Garuda 20100308
		virtual void					PushObject(IMoveObject* pMoveObj) = 0;
		virtual void					Render() = 0;
		virtual void					EnableShadow(bool bEnable) = 0;
		virtual IPrePassLight*			CreatePrePassLight(LIGHT_TYPE type) = 0;

		//============================ FOG =========================

		virtual void					EnableGlobalFog()=0;
		virtual void					DisableGlobalFog()=0;
		virtual void					SetGlobalFogParam(FOG_TYPE type,const float* vec4Color,float fNear,float fFar,float fDensity)=0;


		/////////////////////////////// User Object ///////////////////////////////////////////

		virtual void					CreateHardcoreMoveObjectPtr(IMoveObject* pIObj)=0;
		virtual void					ReleaseHardcoreMoveObject(IMoveObject* pIObj)=0;

		//////////////////////////////////////// Particle VB //////////////////////////////////
		virtual unsigned int			GetMaxParticleNum()=0;
		virtual char*					LockParticleVB()=0;
		virtual void					UnLockParticleVB(int nParticleNum)=0;

		virtual void					DrawParticle(int nParticleNum, IShader* pIShader, IParticleVB* pVB, unsigned int offSet)=0;


		///////////////////////////////////OCCLUSIdON QUERY///////////////////////////////////////
		virtual int						OcclusionQuery(const float* boxWorld)=0;
		virtual int						OcclusionQuery(IModel* pModel)=0;

		/*
		某些显卡只支持16bit的索引数据, 为了减少处理上的麻烦, 客户端的索引buffer统一使用unsigned short格式
		*/
		virtual void					DrawIndex(PRIMITIVE_TYPE nTriangleType,unsigned int nElemNum,unsigned int nVertNum,unsigned int nNormalOffset,
			unsigned int nTexcoordOffset,unsigned int nColorOffset,unsigned int nTexcoordOffset2,void* pVBuffer,unsigned short* pEBuffer)=0;


		//-----------------异步IO接口------------------------

		// 异步创建一个模型，返回任务id
		// lod：lod级别
		// nPriority：任务优先级
		virtual unsigned int		CreateModelAsyn(const char* sFileName, sCreateOp& lod, int nPriority)=0;

		virtual unsigned int		CreateSpeAsyn(const char* sFileName, sCreateOp& lod, int nPriority) = 0;

		virtual unsigned int		CreateTextureFromFileAsyn(const char* filename, unsigned int numMips=0) = 0;

		virtual unsigned int		CreateNewShaderAsyn(const char* filename, const char* matName, int nPriority)=0;

		virtual unsigned int		LoadActionAsyn(const char* actName, H3DI::EActorType actorType, bool bMale, int nPriority)=0;


		// 获取异步创建的对象的接口
		virtual H3DI::IMoveObject*	GetModelAndFinishTask(unsigned int taskId) = 0;

		virtual H3DI::INewShader*	GetNewShaderAndFinishTask(unsigned int taskId)=0;

		virtual H3DI::ITexture*		GetTextureAndFinishTask(unsigned int taskId)=0;


		// 加载资源的异步接口

		// 异步加载actor bodypart
		virtual unsigned int	LoadBodypartAsyn(const char* fileName, EActorType actorType, sCreateOp& lod, int nPriority) = 0;

		virtual unsigned int	LoadAdornmentAsyn(const char* adornmentname, sCreateOp& lod, int nPriority) = 0;

		virtual unsigned int	LoadMaterialLodAsyn(IMoveObject* pModel, int nLod, int nPriority)=0;

		// 阻塞执行异步任务，直到某个任务完成
		// taskId ：直到完成的任务id，可以传0，则阻塞直到当前任务队列中所有任务完成
		virtual int		DoTaskImmediately(unsigned int taskId) = 0;

		virtual int		GetWaitingTaskCount() = 0;

		virtual int		CancelTask(unsigned int taskId) = 0;

		virtual int		QueryTaskState(unsigned int taskId) = 0;

		// 查询当前所有任务状态
		// idBuffer 填充任务id的buffer,可以为NULL，这时返回任务总数
		// stateBuffer 填充任务状态的buffer,可以为NULL，这时返回任务总数
		// nBufferSize idBuffer和stateBuffer的大小以int为单位，当该值小于当前总任务数量时，该函数仅任务总数
		// 返回值：填充到buffer中的结果数量,也就是当前的任务总数
		virtual int		QueryAllTaskState(unsigned int * idBuffer, int* stateBuffer, int nBufferSize) = 0;

		virtual void	UpdateEngineThread() = 0;	

		//!IO线程Task执行状态监控，测试用例使用
		virtual void	SetProcessIOLisenter(ProcessIOLisenter* lisenter) = 0;

		//--------------------------------------------------

		//!得到当前关卡,无用
		virtual ILevel* GetLevel(void)const = 0;
		//!创建相机
		virtual ICamera* CreateCamera(void) = 0;
		//!设置渲染相机
		virtual void SetRenderCamera(ICamera* pCam) = 0;
		//!得到渲染相机
		virtual H3DI::ICamera* GetRenderCamera(void)const = 0;
		//!设置culling相机
		virtual void SetCullingCamera(ICamera* pCam) = 0;
		//!得到culling相机
		virtual H3DI::ICamera* GetCullingCamera(void)const = 0;
		//!画AABB
		virtual void DrawAABB(const float* aabb, const float* color, float lineWidth)const = 0;
		//!画线段
		virtual void DrawSegment(const H3DVec3& begin, const H3DVec3& end, const float* color, float lineWidth)const = 0;

		//!创建粒子VB
		virtual IParticleVB* CreateParticleVB(void) = 0;
		//!push一个粒子进行渲染
		virtual void PushParticle(H3DI::IMoveObject* pObj) = 0;

		//!打开一个动作库
		virtual bool                    OpenActionLib(const char* fileName)const = 0;
		//!读取一个动作文件
		virtual bool                    LoadAction(const char* actName, H3DI::EActorType actorType, bool bMale) = 0;
		//!释放一个动作
		virtual bool                    ClearAction(const char* actName, H3DI::EActorType actorType, bool bMale) = 0;
		//!检查一个动作是否已存在
		virtual bool                    IsActionExist(const char* actName, H3DI::EActorType actorType, bool bMale) = 0;
		//!读取关卡文件
		virtual ILevel*                 LoadLevel(const char* fileName) = 0;
		//!push一个关卡进行渲染
		virtual void                    PushLevel(ILevel* p) = 0;
		//!渲染关卡的阴影
		virtual void                    RenderLevelShadowMap(ILevel*) = 0;
		//!执行命令,可扩展接口
		virtual void					Exec(unsigned int code, const char* argument, unsigned int argumentLength, char* buffer, unsigned int bufferLength) = 0;
		//!查询接口
		virtual void*					QueryInfo(int QueryCode,void* param1,void* param2,void* param3,void* param4,void* param5)=0;
		//!设置是否使用动作库,IRender初始化的时候调用一次即可,默认为不使用
		virtual void					SetUseActionLib(bool val) = 0;
		//!是否使用动作库
		virtual bool					UseActionLib(void)const = 0;
		//!设置是否合并Actor的Bodypart贴图,IRender初始化的时候调用一次即可,默认为不使用
		virtual void                    SetMergBodyPart(bool val) = 0;
		//!是否合并bodypart
		virtual bool                    MergBodyPart(void)const = 0;
		//!设置SkeletonModel的实现是否使用多轨动画,默认为不使用
		virtual void                    SetUseActionChannel(bool val) = 0;
		//!SkeletonModel的实现是否使用多轨动画
		virtual bool                    UseActionChannel(void)const = 0;
		//!在动作库模式下,读取一组动作
		virtual void                    PreLoadActions(const char** actNames, unsigned int actCount, ISkeletonModel* pSKL) = 0;
		//!在动作库模式下,清空前面读进来的所有动作，如果bOnlyClearUnUsed为true，只会清空未使用的动作。
		virtual void                     ClearAllActions(bool bOnlyClearUnUsed = true) = 0;
		//!重新读取动作库中的一个动作(用原来的文件名)
		virtual bool                     ReloadAction(const char* actName, ISkeletonModel* pSKL) = 0;

		//!设置是否开启布料模拟
		virtual void                     SetUseCloth(bool val) = 0;
		//!是否开启布料模拟
		virtual bool                     UseCloth(void)const = 0;
		//!设置是否优先使用三角形列表
		virtual void                     SetUseTriList(bool val) = 0;
		//!是否优先使用三角形列表
		virtual bool                     GetUseTriList(void)const = 0;


		//!设置贴图缩放参数
		virtual void                     SetImageScaleFactor(unsigned int) = 0;
		//!得到贴图缩放参数
		virtual unsigned int          GetImageScaleFactor(void)const = 0;
		//!清空无用的贴图,shader等资源
		virtual unsigned int          ClearMaterialLib(void) = 0;
		//!得到状态监视器
		virtual const IEngineMonitor*    GetEngineMonitor(void)const = 0; 
		//!设置是否优先读取二进制
		virtual void					  SetFavorBinary(bool val) = 0;
		//!是否优先读取二进制
		virtual bool                      FavorBinary(void)const = 0;
		//!得到运行时模式
		virtual ERuntimeMode       GetRuntimeMode(void)const = 0;
		//!push世界矩阵
		virtual void					  PushViewMatrix(void)const = 0;
		//!pop世界矩阵
		virtual void                      PopViewMatrix(void)const = 0;
		//!push投影矩阵
		virtual void                      PushProjectionMatrix(void)const = 0;
		//!pop投影矩阵
		virtual void                      PopProjectionMatrix(void)const = 0;
		//!得到渲染状态管理器
		virtual const IRenderStateManager* GetRenderStateManager(void)const = 0;
		//!创建一张贴图
		/**
		client创建了texture或者RT后,要执行addref操作,否则在清理内存的时候可能会把这个贴图删掉
		销毁前,要先执行delref,再执行release
		以下第一个函数是创建一个指定大小的texture，第二个是通过磁盘文件创建一个texture,第二个参数表示mipmap的等级 0表示自动生成
		*/
		virtual ITexture*               CreateTexture(unsigned int& width, unsigned int& height, ETextureFormat fmt, bool mipmap) = 0;
		virtual ITexture*               CreateTextureFromFile(const char* filename, unsigned int numMips=0) = 0;
		//!创建一个RT
		virtual IRenderTarget*      CreateRenderTarget(unsigned int& width, unsigned int& height, ETextureFormat fmt, ERenderTargetType type) = 0;
		//!设置是否将贴图压缩成DXT格式
		virtual void                      SetCompressTexture(bool res)const = 0;
		//!是否将贴图压缩成DXT格式
		virtual bool                      CompressTexture(void)const = 0;
		//!得到平行投影矩阵
		virtual void                       GetOrthoProjectionMatrix(float left, float right, float bottom, float top, float near, float far, H3DMat4& out)const = 0;
		//!修改当前view矩阵
		virtual void                       TranslateViewMatrix(float x, float y, float z)const = 0;
		//!旋转当前view矩阵
		virtual void                       RotateViewMatrix(float degree, float x, float y, float z)const = 0;
		//!得到屏幕坐标系下的坐标
		virtual void                       GetScreenPos(const H3DVec3& objPos, const H3DMat4& worldViewMat, const H3DMat4& projMat, 
			unsigned int x, unsigned int y, unsigned int width, unsigned height, 
			float minZ, float maxZ, H3DVec3& screenPos)const = 0;
		//!设置贴图参数
		virtual void                        SetTextureParams(bool scale, bool compress, bool mipmap)const = 0;
		//!得到贴图参数
		virtual void                        GetTextureParams(bool& scale, bool& compress, bool& mipmap)const = 0;
		//!设置全屏、窗口模式
		virtual void						ToWindowedMode()=0;
		virtual void						ToFullScreenMode()=0;
		//!设置全屏抗锯齿模式
		virtual void                         SetAAMode(EAAMode aa) = 0;
		//!得到全屏抗锯齿模式
		virtual EAAMode              GetAAMode(void)const = 0;
		//!得到支持的抗锯齿类型
		virtual unsigned int           GetSupportedAAMode(void)const = 0;
		//!设置各项异性过滤模式
		virtual void                          SetAFMode(EAFMode) = 0;
		//!得到各项异性过滤模式
		virtual EAFMode               GetAFMode(void)const = 0;
		//!得到支持的各项异性过滤模式
		virtual unsigned int           GetSupportedAFMode(void)const = 0;
		//!设置是否开启垂直同步
		virtual void                          SetVSync(bool val) = 0;
		//!是否开启垂直同步
		virtual bool                          GetVSync(void)const = 0;
		//!设置阴影模式
		virtual void                          SetShadowQuality(EShadowQuality q) = 0;
		//!得到阴影模式
		virtual EShadowQuality    GetShadowQuality(void)const = 0;
		//!设置是否开启布料
		virtual void                          EnableCloth(bool val) = 0;
		//!是否开启布料
		virtual bool                          ClothEnabled(void)const = 0;
		//!更新显示设置
		virtual void                         ApplyVideoSettings(void) = 0;
		virtual void						 ApplyVideoSettings2(void) = 0;
		//!得到当前的分辨率
		virtual void						 GetCurrentReslution(int& w,int& h)=0;
		//!得到profile数据
		virtual void                         GetPerfData(tPerfData& data)const = 0;
		//!设置重力
		virtual void                         SetGravity(const H3DVec3& g) = 0;
		//!得到重力
		virtual const H3DVec3&      GetGravity(void)const = 0;
		//!设置事件处理器
		virtual void                          SetEventHandler(IEngineEventHandler* pHandler) = 0;
		//!得到事件处理器
		virtual IEngineEventHandler* GetEventHandler(void)const = 0;

		//!抓屏
		virtual bool SaveScreenToFile(const char* )=0;
		//创建IImage
		virtual IImage* GetImageInterface(void)=0;

		virtual IPerfMonitor* GetPerfMonitor()=0;

		//by sssa2000 090330
		//为编辑器添加的新接口
		virtual void beginWireFrameDraw()=0;
		virtual void endWireFrameDraw()=0;
		virtual void drawPhy()=0;
		//add by liren
		//将地形放入管线
		virtual void PushTerrain(H3DI::ITerrain *pTerrain) = 0;
		//!add by liren

		//add by liren
		//在地形上创建一个面片
		virtual	IModel*			GenerateSmallPatch(float length,float width,ITerrain *pTerrain) = 0;
		//!add by liren
		//硬件选择
		//开启硬件选择，传入一个屏幕矩形，和选择方式,
		virtual	bool			BeginHardwareSelect(const int *pRect,bool bSelectFirst, int WindowID) = 0;
		//传入一物体和它相对的ID
		virtual void			PushHardwareSelectObject(IMoveObject *pobject,unsigned int nId) = 0;
		//处理物体的选择
		virtual	void			ProcessMoveObjectSelect() = 0;
		//!压入一个Id，适用于自定义顶点，线和VB等
		virtual void			PushSelectID(int ID) = 0;
		//!无用
		virtual int				GetSelectID(void)const = 0;
		//结束选择，返回结果
		virtual	int				EndHardwareSelect(unsigned int *pRetIds,int num) = 0;
		//!设置镜头光晕参数
		virtual void			SetLensParameters(const tLensEnv& lenEnv,const tLensFlareParameters* lensPara,unsigned int nums) = 0;
		//!设置太阳高度,默认支持一个太阳
		virtual void			SetSunHeight(float height)=0;
		//!设置太阳位置,编辑器用
		virtual void			SetSunPos(const H3DVec3& pos)=0;
		//!获取太阳位置,编辑器debug用
		virtual void			GetSunPos(H3DVec3& pos)=0;

		//雾(新渲染系统)
		virtual H3DI::IFog*					CreateFog() = 0;
		//设置全局雾（目前全局雾不需要创建）
		virtual void SetGlobalFog(float r,float g,float b,float density,float start,float fogmin)=0;
		//重新载入贴图
		virtual int ReloadTexture(const char* filename)=0;

		//后处理相关接口
		//添加删除后处理效果的接口
		virtual bool					AddPostProcess(const char *FileName) = 0;

		virtual bool					DelPostProcess(const char *FileName) = 0;
		//开启
		virtual void					EnablePostProcess(bool bEnable) = 0;
		//设置参数,后处理特效供外界可调的参数,用这个接口设置。
		//具体有哪些参数，每个参数什么意义，由相关文档提供。
		virtual void					SetPostProcessParams(const char* name,const void *pParmeValue) = 0;

		//设置后处理影响的窗口。
		virtual void					SetPostProcessWindowId(int)=0;
		//获得后处理影响的窗口。
		virtual int						GetPostProcessWindowId()=0;


		//设置世外场景的全局环境
		virtual void SetOutDoorEnvInfo(const OutDoorEnvInfo& info)=0;
		virtual void GetOutDoorEnvInfo(OutDoorEnvInfo* info)=0;

		//获得运行时信息
		virtual void GetRuntimeInfo(IRuntimeInfo* pRes)=0;

		//将焦平面距离，景深范围，最大弥散圆半径设置给引擎的摄相机
		virtual void SetFocalParam(float fFocalplane,float fDOFRange,float fConfusion) = 0;
		//得到焦平面距离，景深范围，最大弥散圆半径设置给引擎的摄相机
		virtual void GetFocalParam(float &fFocalplane,float &fDOFRange,float &fConfusion) = 0;


		//客户端有PushCamera和PopCamera需求，以下两个函数分别将景深参数压栈或弹出栈。
		virtual void PushFocalParam() = 0;
		virtual void PopFocalParam() = 0;
		//将一个模型添加到骨骼模型实例包
		virtual	void AddSkeletonModelToInstancing(H3DI::ISkeletonModel *pSkeletonModel) = 0;
		//处理模型添加到骨骼模型实例包
		virtual void ProcessSkinedInstancing() = 0;
		//得到场景深度图
		virtual IRenderTarget* GetSceneDepthUsedInPostprocess() = 0;

		//设置是否开启延迟光照绘制
		virtual void EnableLightPrePassRendering(bool b)=0;

		//给出一个材质实例文件名 以及材质球的名字得到INewShader
		virtual H3DI::INewShader* GetNewShader(const char* filename,const char* matName)=0;
		//得到错误代码
		virtual int GetEngineLastError()=0;

		//得到错误代码的描述
		virtual const char* GetErrorDesc(int errCode)=0;

		//添加一个高亮模型，高亮模型每帧都必须设置，如果不设置就没有模型被高亮
		virtual int AddHighLightModel(const H3DI::IModel* pModel)=0;

		virtual unsigned int GetRenderFrameCount() = 0;

		//设置次表面散射颜色
		virtual void		SetTransmissionColor(const float* col) = 0;
 		
		//可以设置景深参数的后处理设置参方式
 		virtual void					SetPostProcessParams1(const char* name,const void *pParmeValue) = 0;

		///设置引擎使用者
		virtual void					SetUser(EngineUserDefine u)=0;
		//开始DrawIndex
		virtual void					BegineDrawIndex() = 0;

		//结束DrawIndex
		virtual void					EndDrawIndex() = 0;

		///开始查询本帧显存用量
		virtual void BeginCurrentFrameVideoMemQuery()=0;

		///结束查询本帧显存用量
		virtual unsigned int EndCurrentFrameVideoMemQuery()=0;

		///设置是否开启2d绘制。
		virtual void Set2DMode(bool b)=0;

		///push 2d物体
		virtual void Push2DObj(IMoveObject* pMoveObj)=0;

		///Render 2d物体
		virtual void Render2DObj()=0;
		//创建一个后处理对象
		virtual IPostProcessEffect*		CreatePostProcessEffect()=0;
		//释放一个后处理对象
		virtual void					ReleasePostProcessEffect(IPostProcessEffect *pIEffect)=0;

		//得到默认的后处理对象
		virtual IPostProcessEffect*		GetDefaultPostProcessEffect()=0;

		//得到当前的后处理对象
		virtual IPostProcessEffect*		GetCurrentPostProcessEffect()=0;

		//设置当前的后处理对象
		virtual void					SetCurrentPostProcessEffect(IPostProcessEffect *pIEffect)=0;
		//得到当前地形
		virtual ITerrain*				GetActiveTerrain() = 0;
		//获得与光源绑定的体积光是否开启的标志
		virtual	bool					GetLightShaftEnable() = 0;
		//设置与光源绑定的体积光是否开启的标志
		virtual	void					SetLightShaftEnable(bool bEnable) = 0;
		//// !使用新材质系统Draw Index
		virtual void					DrawIndexNew(PRIMITIVE_TYPE nTriangleType,unsigned int nElemNum,unsigned int nVertNum,unsigned int nNormalOffset,unsigned int nTexcoordOffset,unsigned int nColorOffset,unsigned int nTexcoordOffset2)=0;
		///! 命令行
		virtual int						OnCommandLine(const char* commandLine) = 0;
		//使用硬件选择
		virtual void					SetUseHardWareSelection(bool buse) = 0;
		//获取是否使用硬件选择
		virtual bool					UseHardWareSelection() = 0;

		//获取全局的性能数据
		virtual void* GetGlobalPerfData(GLOBAL_PERFDATA_TYPE t)=0;

		/// 开关材质的动画效果
		virtual void EnableMaterialAnimation(bool b) = 0;

		// 设置当前渲染模式（普通、线框、普通+线框）
		virtual void					SetFillMode(EFILLMODE mode) = 0;
		// 设置线框的颜色
		virtual void					SetWireframeColor(const float* color)  = 0;

		/// 适应新材质INewShader的需求/// 设置DrawIndex需要使用的INewShader
		virtual void					SetNewShader(H3DI::INewShader* pShader) = 0;

		///开始设置当前绘制要使用的灯光
		virtual void BeginSetCurrentLight()=0;

		//设置当前绘制要使用的灯光
		//t：场景光还是人物光
		//pLight：光源指针
		//返回值：如果返回-1表示数量超过规定，设置不成功。返回大于0的值表示成功
		virtual int SetCurrentLight(H3DI::IPrePassLight* pLight)=0;

		///结束设置当前绘制要使用的灯光
		virtual void EndSetCurrentLight()=0;

		///获取当前绘制要使用的灯光的数量
		virtual int GetCurrentLightNum(H3DI::LightAffectParam t)=0;

		//开始向ViewPort中画东西
		virtual void BeginViewPort() = 0;
		//结束向ViewPort中画东西
		virtual void EndViewPort() = 0;
		
		//打开全局的参数库
		virtual int OpenPhxParaLib(const char** paraLibs,int bufferSize,int phxParaType) = 0;
		//获取指定名称的物理参数
		virtual int GetPhxParaFromLib(const char* pName,void** paraData,int bufferSize,int phxParaType) = 0;
		//将指定名称的物理参数加入到参数库
		//opType: 0,不覆盖 1,覆盖。返回0表示失败。返回1表示成功.有同名的需要提示是否覆盖
		virtual int AddPhxParaToLib(const char* pName,void** paraData,int bufferSize,int phxParaType,int opType) = 0;

		//获取鼠标点选时的射线方向,使用当前的渲染相机的参数
		//point和dir都是x、y、z三个分量
		virtual int GetMouseRayDir(int mouse_x,int mouse_y, H3DVec3* pos, H3DVec3* dir)=0;

		virtual int GetMouseRayDirEx(const H3DVec3& eye_position, const H3DVec3& camera_direction, const H3DVec3& camera_up, float f_near,
			float f_far, unsigned int screen_width, unsigned int screen_height, float fovX, int mouse_x,int mouse_y, H3DVec3* pos, H3DVec3* dir)=0;
		
		//读入包围体文件，返回值1表示成功，小于0不成功
		virtual int LoadCustomBoundingVolume (const char* filename)=0;

		//!生成一个fxinfo
		virtual IFxInfo* CreateAFxInfo()=0;
		//创建一个ILevel
		virtual	ILevel *CreateLevel(const char * name) = 0;

		// 将当前帧渲染到贴图
		// origPathName: 原贴图的路径名,用于获得格式，大小
		virtual bool RenderToTexture(const char* origPathName, const char* pathName) = 0;
		
		//输出Info日志
		virtual void OutPutLogInfo(H3DI::InfoType infoType,H3DI::OutPutFlag outFlag,const char* pStr) = 0;
		//输出Error日志
		virtual void OutPutLogError(H3DI::ErrorType errorType,H3DI::OutPutFlag outFlag,const char* pStr) = 0;
		//获得截屏数据
		virtual const PrintScreenInfo* GetPrintScreenInfo()=0;
		virtual void ReleasePrintScreenInfo(const PrintScreenInfo* pInfo)=0;
	};



	//!给粒子使用的VB
	class IParticleVB : public IObject
	{
	public:
		//!初始化,指定最大粒子个数
		virtual void Init(unsigned int particleCount) = 0;
		//!得到最大粒子格式
		virtual unsigned int GetMaxParticleCount(void)const = 0;
		/**
		//Particle的VB格式必须是position(float3) + color(unsigned int) + UV(float2)
		//	必须交错填充
		//	*/
		virtual void* Lock(unsigned int particleCount) = 0;
		virtual void UnLock(void) = 0;
	protected:
		virtual ~IParticleVB(){}
	};


	//为了调试level的octree以及oc用的条件
	//用来绘制满足条件的包围盒
	enum LEVEL_DEBUG_CONDITION
	{
		LDC_NONE_NODE=0,
		LDC_ALL_NODE,
		LDC_ALL_LEFE,
		LDC_ALL_OC_NODE,
		LDC_ALL_IN_FRUSTUM,
		LDC_ALL_HAVE_SCENENODE,
		LDC_ALL_PASS_OC_NODE
	};
	enum LEVEL_DEBUG_SET_CALC
	{
		LDC_INTERSECTION=0,
		LDC_UNION
	};
	enum LevelLayer
	{

		LL_DetailObj = 0,
		LL_SpeEffect,
		LL_Actor,
		LL_Light,
		LL_Particle,
	};
	//!关卡
	class ILevel : public IScene
	{
	public:
		//!得到AABB
		virtual void GetWorldAABB(float* pArray6)const = 0;
		//!设置环境光颜色
		virtual void SetAmbientColor(float r, float g, float b) = 0;
		//!读geometry
		virtual bool Load(const char* fileName) = 0;
		//!用相机culling
		virtual void CullByCamera(ICamera*) = 0;

		//by sssa2000 081203
		//获得调试信息
		virtual unsigned int GetOctreeAABBTestNum()=0;
		virtual unsigned int GetSubMeshOctreeSectionTestNum()=0;

		//by sssa2000 090216
		//Condition1和Condition2能够组合起来绘制满足2个条件的结点包围盒
		virtual void SetDebugCondition1(LEVEL_DEBUG_CONDITION ldc)=0;
		virtual void SetDebugCondition2(LEVEL_DEBUG_CONDITION ldc)=0;
		virtual void SetDebugCalc(LEVEL_DEBUG_SET_CALC ldc)=0;
		virtual void SetDrawOctreeLevel(int i)=0; //设置绘制octree的包围盒的层级。为-1时绘制所有层级
		//by sssa2000 090209
		virtual void EnableOccluder(bool b)=0;
		virtual bool IsOccluderEnable()=0;
		virtual int GetOccluderNumber()=0;
		virtual void DrawOccluder(int i)=0;
		virtual void DrawOccluderFrustum(int i,H3DVec3& viewPoint)=0;
		//根据场影中细节物体重新分割八叉树
		virtual void RestructOctree()=0;
		//在一个场景中添加后处理
		virtual void			AddPostProcess(const char* filename)=0;
		//在一个删除后处理
		virtual void			DelPostProcess(const char* filename)=0;
		//设置一个场景的后处理参数
		virtual void			SetPostProcessParam(const char *name,const void *pvalue,int sizeOfValue)=0;
		//设置一个场景的视口
		virtual	void			SetViewPort(const unsigned short *vp) = 0;
		//得到一个场景的视口,传入一个四个元素的数组
		virtual	void			GetViewPort(unsigned short *vp) = 0;
		//设置视矩阵
		virtual void			SetViewMatrix(const H3DMat4 &mat) = 0;
		//设置透视矩阵
		virtual void			SetPerspectiveMatrix(const H3DMat4 &mat) = 0;

		//视矩阵
		virtual void					GetViewMatrix(H3DMat4 &mat) = 0;
		//透视矩阵
		virtual void					GetPerspectiveMatrix(H3DMat4 &mat) = 0;
		virtual void					SetEyePosition(const H3DVec3& pos) = 0;
		virtual void					GetEyePosition(H3DVec3& pos) = 0;
		virtual void					LookAt(const H3DVec3& eyepos, const H3DVec3& at, const H3DVec3& up) = 0;

		virtual void					RotateDirection(float yaw_offset,float pitch_offset,float roll_offset)=0;
		virtual void					SetCameraRotation(float yaw,float pitch,float roll)=0;
		virtual void					GetRotateDir(float& yaw,float& pitch,float& roll)=0;

		virtual void					GetEyeDirection(H3DVec3& vec) = 0;
		virtual void					SetFrustum(float fov,float ratio,float fNear,float fFar,ECameraType camType = ECT_Render)=0;
		virtual void					GetFrustum(float& fov,float& ratio,float& fNear,float& fFar,ECameraType camType = ECT_Render)=0;
		virtual void					UpdateCamera()=0;

		/// 设置场景环境光颜色
		virtual void					SetAmbientColor(const float *col)=0;
		/// 设置角色环境光颜色			
		virtual void					SetActorAmbientColor(const float *col)=0;
		//设置次表面散射颜色
		virtual void					SetTransmissionColor(const float* col) = 0;
		/// 设置场景材质LOD
		virtual void					SetMaterialLod(int nLod)=0;
		/// 得到材质LOD			
		virtual int						GetMaterialLod()=0;

		virtual void					SetShadowFadeoutEnd(float fParam) = 0;

		// 影响lightmap颜色 lm' = lm * a + b
		// a, b均为float3
		virtual void				SetLightmapColorFactor(const float* a, const float* b) = 0;


	protected:
		virtual ~ILevel(){}
	};




	//!相机类
	class ICamera : public IMoveObject
	{
	public:
		//!得到向上的方向
		virtual const H3DVec3& GetUp(void) = 0;
		//!得到向右的方向
		virtual const H3DVec3& GetRight(void) = 0;
		//!从当前位置向position看
		virtual void LookAt(const H3DVec3& position) = 0;
		//!从eyePos向atPos看
		virtual void LookAt(const H3DVec3& eyePos, const H3DVec3& atPos, const H3DVec3& upVec) = 0;
		//!绕着前方向转,给角度
		virtual void Roll(float degree) = 0;
		//!绕着右方向转,给角度
		virtual void Yaw(float degree) = 0;
		//!绕着上方向转,给角度
		virtual void Pitch(float degree) = 0;
		//!绕着axis转degree角度
		virtual void Rotate(const H3DVec3& axis, float degree) = 0;
		//!向上移动step距离
		virtual void MoveUp(float step) = 0;
		//!向右移动step距离
		virtual void MoveRight(float step) = 0;
		//!向前移动step距离
		virtual void MoveFront(float step) = 0;
		//!得到view martix
		virtual const H3DMat4& GetViewMatrix(void)const = 0;
		//!得到投影matrix
		virtual const H3DMat4& GetProjectionMatrix(void)const = 0;
	protected:
		virtual ~ICamera(){}
	};

	
	//!雾
	class IFog : public IMoveObject
	{
	public:
		///得到包围体积
		virtual void GetBoundingVolume(H3DVec3* resMin,H3DVec3* resMax)=0;
		///设置雾对象的范围,使用包围盒的形式
		virtual void SetBoundingVolume(const H3DVec3& _min,const H3DVec3& _max)=0;
		///设置雾的颜色
		virtual void SetFogColor(float r,float g,float b,float a)=0;
		///得到雾的颜色
		virtual const H3DVec3& GetFogColor()=0;

		///设置雾的浓度
		virtual void SetFogDensity(float s)=0;
		///获得雾的浓度
		virtual float GetFogDensity()=0;

		///设置雾的起始点
		virtual void SetFogStart(float s)=0;
		///获得雾的起始点
		virtual float GetFogStart()=0;
	protected:
		virtual ~IFog(){}
	};


	//!预生成fx的信息
	class IFxInfo
	{
	public:
		virtual void Reset()=0;

		virtual void Release()=0;

		//!设置渲染环境是否需要排列组合
		virtual void SetRenderEnvCombination(bool b)=0;

		//!增加一个渲染环境，n为名字，num为数量
		//!返回值=1表示成功，如果不成功的话表示传入的渲染环境的名字不合法
		virtual int AddRenderEnvType(const char* n,int num)=0;

		//!增加一个宏，n是名字，v是值
		virtual void AddFxMacro(const char* name,const char* v)=0;

		//!设置渲染类型,前向还是延迟还是由材质确定
		//!0表示由材质决定，1表示强迫使用前向
		virtual void SetRenderType(int rendertype)=0;
	};
	
	//!IO线程Task执行状态监控，测试用例使用--begin
	//!任务状态的枚举
	enum THREAD_TASK_CONTEXT_STATE
	{
		THREAD_TASK_BEFORE_PARSE = 0,
		THREAD_TASK_AFTER_PARSE,
		THREAD_TASK_BEFORE_LOAD,
		THREAD_TASK_AFTER_LOAD,
	};

	//!在任务处理过程中，该任务的一些状况
	struct TaskContext 
	{
		//!当前任务的ID
		unsigned int		TaskId;

		//!当前任务的状态
		THREAD_TASK_CONTEXT_STATE	TaskState;
		
		//!当前任务已经加载了的相关资源的个数
		unsigned int		LoadedNum;

		//!当前任务是否出错
		bool				IsError;

		TaskContext(unsigned int taskId, THREAD_TASK_CONTEXT_STATE taskState, unsigned int loadedNum, bool isError): 
		TaskId(taskId),
		TaskState(taskState),
		LoadedNum(loadedNum),
		IsError(isError)
		{
		}

		TaskContext(): 
		TaskId(0),
		TaskState(THREAD_TASK_BEFORE_PARSE),
		LoadedNum(0),
		IsError(false)
		{
		}
	};

	//!IO处理监听器，用于监听在IO处理过程中，某时刻某一个任务的处理状态。
	class ProcessIOLisenter
	{
	public:
		//!通知ProcessIOLisenter正处于处理IO的阶段
		//!context是当时Task的上下文状况
		virtual void NotifyProcessIO(const TaskContext& context) = 0;

	};
	//!在任务处理过程中，该任务的一些状态--end


	IRender* CreateRenderer();

	void DeleteRenderer();

	//执行单元测试
	int DoTest(int argc, char **argv);

}

#endif//
