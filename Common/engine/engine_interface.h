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
		int geo_lod; //����lod����
		int mat_lod; //����lod����
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
		//��֡���Ƶ��������������� (unsigned int)
		TOTAL_TRIANGLE_NUM,
		//��ִ֡�е�����dip (unsigned int)
		TOTAL_DIP_NUM,
		//��֡������ƵĹ�Դ���� (unsigned int)
		TOTAL_LIGHT_NUM,
		///����ʹ�õ�Texture���� (unsigned int)
		TOTAL_TEXTURE_NUM,
		//����ʹ�õ�rt���� (unsigned int)
		TOTAL_RT_NUM,
		//������ģ������(unsigned int)
		TOTAL_MODEL_NUM,
		//����������Fx�л�����(unsigned int)
		TOTAL_FX_CHANGES,
		//����������BeginPass���ô���(unsigned int)
		TOTAL_BEGINPASS_NUM,
		//����������ShaderConst�ύ������(unsigned int)
		TOTAL_SC_NUM,
		//������˽��ShaderConst�ύ������(unsigned int)
		TOTAL_PRIVATE_SC_NUM,
		//����������͸������ĸ���(unsigned int)
		TOTAL_TRANSPARENT_NUM,
		//����������͸�������m_DIP(unsigned int)
		TOTAL_TRANSPARENT_DIP,

		//����ʹ�õ��ڴ����� (unsigned int �ֽ�)
		TOTAL_MEMORY_USEAGE,
		//����ʹ�õ��Դ����� (unsigned int �ֽ�)
		TOTAL_VIDEO_MEMORY_USAGE,
		//��ǰ����������� (float)
		FILLRATE_PERCENT,
		//��ǰ�Ķ���cache���аٷֱ� (float)
		VERTEX_CACHE_PERCENT,
		//��ǰ������cache���аٷֱ� (float)
		TEX_CACHE_PERCENT,
		//GPU ���е�ʱ��ٷֱ� (float)
		GPU_IDLE_PERCENT,
		//��Ⱦ״̬�л�����(unsigned int)
		TOTAL_RS_CHANGENUM,
		//Batches��(unsigned int)
		TOTAL_BATCHES,
		//Number of objects in video memory(unsigned int)
		TOTAL_WORKINGSET,
		//Number of objects in video memory (unsigned int�ֽ�)
		TOTAL_WORKINGSET_BYTES,
		//Total number of managed objects.(unsigned int)
		TOTAL_MANAGED,
		//Total number of bytes of managed objects.(unsigned int�ֽ�)
		TOTAL_MANAGED_BYTES,

		GLOBAL_PERFDATA_TYPE_END
	};

	enum MODEL_PERFDATA_TYPE
	{
		//��ģ�͵����������� (unsigned int)
		TRIANGLE_NUM=0,
		//��ģ�͵�dip���� (unsigned int)
		DIP_NUM,
		//��ģ�͵ĵ�vertex shaderָ���� (unsigned int)
		VS_INS_NUM,
		//��ģ�͵�geometry shaderָ���� (unsigned int)
		GS_INS_NUM,
		//��ģ�͵�pixel shaderָ���� (unsigned int)
		PS_INS_NUM,
		//��ģ���յ��ĵƹ����� (unsigned int)
		LIGHT_NUM,
		//��ģ��ʹ�õ���ͼ��(unsigned int )
		TEXTURE_NUM,
		//��ģ�ͻ������˶��ٸ�fx
		FX_NUM,
		//��ģ�ͻ������˶��ٸ�shaderconst
		SC_NUM,
		//��ģ��ռ�õ��ڴ���(unsigned int �ֽ�)
		MEMORY_USAGE,
		//��ģ��ռ�õ��Դ���(unsigned int �ֽ�)
		VIDEOMEM_USAGE,

		MODEL_PERFDATA_TYPE_END
	};

	enum EFILLMODE
	{
		FILL_NORMAL = 0,			//��ͨģʽ
		FILL_WIREFRAME,				//�߿�ģʽ
		FILL_NORMAL_WIREFRAME,		//��ͨ+�߿�ģʽ
		FILL_LIGHTMAP,				//����LIGHTMAPʱ��ֻ��LightMap��Ч��
		FILL_REALTIME_LIGHTING,				//ֻ������Ч��
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
	��������
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
	IMaterialΪ���в��ʵ�ͳһ�ӿڣ�����������Ĺ��������������ʶ��Ӵ˽ӿ�����
	*/
	class IMaterial: public IObject
	{
	public:
		virtual ~IMaterial()=0{};
		virtual const char*				GetName()=0;
		virtual MATERIAL_TYPE			GetType()=0;
	};

	///��������ö��
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

		///�õ�pass����
		virtual unsigned int GetPassNumber()=0;

		///�õ�ĳ��������ֵ,���������ͣ�����ֵΪ1��ʾ�ɹ� 0��ʾʧ��
		virtual int GetNodeVarValue_Float(const char* varName,float& res)=0;
		virtual int GetNodeVarValue_Int(const char* varName,int& res)=0;
		virtual int GetNodeVarValue_Float4(const char* varName,float& f1,float& f2,float& f3,float& f4)=0;
		virtual int GetNodeVarValue_Str(const char* varName,const char*& res)=0; //resΪ�ⲿ�����һ��ָ�룬�����ڲ����޸����ָ���ֵ
		virtual int GetNodeVarValue_Matrix44(const char* varName,float* mat)=0; //matΪ����16��Ԫ�ص�����,mat�Ŀռ���ʹ���߷���

		virtual int SetNodeVarValue_Float(const char* varName,float res)=0;
		virtual int SetNodeVarValue_Int(const char* varName,int res)=0;
		virtual int SetNodeVarValue_Float4(const char* varName,float f1,float f2,float f3,float f4)=0;
		virtual int SetNodeVarValue_Str(const char* varName,const char* res)=0;
		virtual int SetNodeVarValue_Matrix44(const char* varName,float* mat)=0; //matΪ����16��Ԫ�ص�����,mat�Ŀռ���ʹ���߷���

		virtual void GetMaterialInfo(MaterialInfo* mtlInfo) = 0;

		///������ͼ��Shader,����1��ʾ�ɹ���0��ʾʧ��
		virtual int SetTexture(const char* varName,H3DI::ITexture* pTex)=0;

		/// �õ��˲���ʹ�õ�ITexture��0��ʾû��
		virtual H3DI::ITexture* GetTexture(const char* varName) = 0;

		///����һ���������е��޸ģ��ָ���ʼֵ
		virtual int ResetVar(const char* varName)=0;
		///�õ�һ��shader���еı�������
		virtual int GetAllNodeVarNumber()=0;
		///�õ�һ���������ֵ������ַ���
		virtual const char* GetNodeVarType(const char* varName)=0;
		///�õ���������
		virtual const char* GetMaterialName()=0;


		///���������������ýӿڶԸò��ʵ����еģ��ڱ༭����ָ���� �����ܳ�����Ƶ��������� ����
		///��û�������˸ñ�־��������Ч����û�������Ĳ���������Ч

		///varName:�����Ĳ���ö��
		///f0��f1: �����ñ�����ֵ��= �����ı�����ǰֵ��f0+f1
		///����ֵ���ж��ٸ������ܵ�Ӱ��
		virtual int SetWaveformVar(WaveFormParam varName,float f0,float f1)=0; //���ղ�����ֵ=f0*v+f1

		///varName:�����Ĳ���ö��
		///v: �����ñ�����ֵ��= v
		///����ֵ���ж��ٸ������ܵ�Ӱ��
		virtual int SetWaveformVar(WaveFormParam varName,float v)=0;//���ղ�����ֵ=v
		
		virtual void AddRef()=0;
		virtual void DelRef()=0;
		virtual unsigned int GetRef()=0;

		//�Զ�lod1�� ���ȡ��Աȶȡ��߹ⷶΧ���߹�ǿ��
		virtual float GetBrightness_AutoLod1()=0;
		virtual float GetContrast_AutoLod1()=0;
		virtual float GetSpecluarRange_AutoLod1()=0;
		virtual float GetSpecluarIntensity_AutoLod1()=0;

		virtual void SetBrightness_AutoLod1(float v)=0;
		virtual void SetContrast_AutoLod1(float v)=0;
		virtual void SetSpecluarRange_AutoLod1(float v)=0;
		virtual void SetSpecluarIntensity_AutoLod1(float v)=0;

		///����
		virtual int Exec(int a,int b,void* c)=0;
	};
	/**
	IShaderΪ������Ⱦ�õ�SHADER���ɴ��ļ�*.shd�ж�ȡ����ȡ��RENDERCORE���𡣴˽ӿڿɵõ�SHADER�Լ�SHADER���������ڵ���Ϣ
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
		TEXTURE_1D,//һά��ͼ
		TEXTURE_2D,//��ά��ͼ
		TEXTURE_3D,//��ά��ͼ
		TEXTURE_CUBEMAP,//��������ͼ
		TEXTURE_RECT,//�����ζ�ά��ͼ
		TEXTURE_OFFSET,//������͹ƫ����ͼ
		TEXTURE_FLOAT,//������ͼ
		TEXTURE_RENDER//��ȾĿ����ͼ
	};
	/**
	ITexture�ӿڿ��Եõ�����SHADER������ͼ����Ϣ��GetHandle()�õ�����OPENGL ��ͼ�����������glBindTexture()ֱ�����á�
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

		//!lock��ͼ,�����û��Լ��������
		virtual void*                  Lock(unsigned int level, unsigned int& pitch) = 0;
		virtual void                    Unlock(void) = 0;
		virtual void					AddRef()=0;
		virtual void					DelRef()=0;
		//!����ͼ������ļ�,PNG��ʽ
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
	IBone������ϵͳ�еĹ�ͷ�����а�Χ����Χ����Ϣ��δ���롣�ں����汾�м���
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
	����ϵͳ������ʵʱ��Ⱦʱ�ļ��㣬ֻ��Ϊ�洢������ʼ״̬������
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
	����index buffer��ʽ��short, ��Ϊ�е��Կ���֧��32bit index
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
	����ʵ��������
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
	��������ʱ״̬
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
		//˵��entity���ڸ��߳��н������ݵĸ��£���Щ�������������ȴ��������
		//����Actor::~Actor, Actor::PostProcessing, etc...
		I_ENTITY_THREAD_PROCESSING=1<<7,
		I_ENTITY_CAST_SHADOW = 1 << 8,
		I_ENTITY_PLANT = 1 << 9,
		I_ENTITY_RENDERIN_REFLECTION = 1 << 10, //��ģ���ڷ�������Ⱦ
		I_ENTITY_NOT_WRITE_COLOR = 1 << 11, //��Ⱦʱ��д��ɫ��Ŀǰ���������ڲ�ʹ��
		I_ENTITY_RALATIVETOACTOR = 1 << 12, //��ģ�ͻ���ʹ�ý�ɫ�ƹ�(������)�����ɫ����һ�� 
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
		virtual unsigned int			Draw()=0;//����֮��͸��OBJECT��������Լ���
		virtual void*					GetAllInside(int n)=0;
		//�˶�����
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
		virtual void					SetLocationMatrix(const H3DMat4& mat)=0;//��������״̬�����Z�᷽����ת�Ƕ��Զ���0
		virtual void					SetOrgMatrix(const H3DMat4& mat)=0;//��������ԭʼ״̬�����
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

		//��ι�ϵ���ƣ�������IMoveObject
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
		///������������,����1��ʾ�ɹ���0��ʾʧ�ܡ�
		virtual int						ReloadAll()	= 0;

		/*������
		0����ͬ��ReloadAll
		1��Reload Geometry
		2��Reload ���ʣ�������ͼ��
		3��Reload ��ͼ

		����ֵ-1Ϊʧ�ܣ�����0������ʾreload�˼�����ͼ
		*/
		virtual int						ReloadFromDisk(int reloadContent)=0;
		///��ñ�����ʹ�õ��Դ�
		virtual unsigned int GetVideoMemUse()=0;

		///�����������
		virtual void* GetPerfData(MODEL_PERFDATA_TYPE t)=0;

		///���ڴ�����һ������ʵ����ģ�͵�һ�����񣬷���1��ʾ�ɹ���0��ʾ�Ҳ���������
		virtual int SetMeshMaterialTemplateFromMemByName(const char* meshName,void* pXmlDoc)=0;

		//��AABB�����Ƿ��ĳ�������ཻ��point��dir����x��y��z��������
		//����ֵΪ1��ʾ�ཻ
		virtual int RayHitTestWithAABB(const H3DVec3& point,const H3DVec3& dir)=0;

		//������ɫϵ��
		//f����ɫϵ�������飬arraysize����ɫϵ�����鳤��
		//����ֵ=1��ʾ�ɹ�������ֵС��0��ʾ���ɹ������ɹ���ԭ���ǲ�����û�ж�����ɫϵ��
		virtual int SetMaterialColorFactor(float* f,int arraysize)=0;

		/// ���ù���ɫ��ɫϵ��,Ҫ��������float[4]��Ӱ�췽���� (Mat_d*C0.rgb)+C1.rgb��fC0��Alpha���ڱ��Ͷȼ��㣬fC1��Alpha�������ȼ���
		/// meshPart��ʾģ�ͽ��ܱ�ɫ�������ID������һ��ģ�Ϳ�����MeshID����
		///     ����ǽ�ɫ����ʾ��װ��BodypartID��Ҽ�ID(BODYPART_NUM+�Ҽ�ID)����ֵΪ-1ʱ������ɫ��ģ�����еĲ��֡�
		/// bUpdateChildrenΪtrueʱ������ɫ��ģ�͵��ӽڵ㣨����Ҽ��ϵ���Ч��
		virtual int SetDiffuseColorFactor(float* fC0,int arraysizeC0, float* fC1, int arraysizeC1, int meshPart=-1, bool bUpdateChildren=true)=0;

		//Ϊģ��������Ⱦ������������EEntityFlag�İ�λ����Ľ��
		virtual unsigned int			GetFlags()=0;
		virtual void					SetFlags(unsigned int nFlags)=0;

		///���ò���lod,nLod=0��Ϊ���ϸ�ڣ�nLod=2Ϊ���ϸ��
		virtual void SetMaterialLod(int nLod)=0;
		virtual int GetMaterialLod()=0;

		virtual unsigned int ApplyMaterialLodAndFinishTask(unsigned int taskid)= 0;

		// �첽����lod��ͬ�����ýӿ�
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
		//��ײ�İ�Χ�е�ID
		int id;
		//��ײ�����������
		float x ,y ,z;
		//��ײ��Ĳ�������
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
	//�͹�����ص����ݼ���
	struct IAttachModelInfo
	{
		float m_rayOrg[3];
		float m_rayDir[3];
		float m_attachPos[3];
		float m_attachNormal[3];

		//����ҽӵ�BPTû�ж���,�������һ��
		float m_attachPosLocal[3];
		float m_attachNormalLocal[3];

		//����Ǳ��������,��Ҫ���ñ�־λ
		//-1:��ת����,0Ĭ��,1����ת����
		int m_bInverseRay;

		//��Ҳ����Ĺ�������
		//����
		float m_scaleX,m_scaleY,m_scaleZ;
		//�ƹҽӵ㷨�ߵ���ת
		float m_rotateAngle;
		//���ҽӵ��ƫ��
		float m_offX,m_offY,m_offZ;
		
		//�ҽӵ�����
		IBoneWeight m_boneWeights[3];
		int m_vertIndex[3];
		int m_phyVertIndex[3];
		//����Ȩ��
		float m_vertWeight[3];

		//�ҽӵ㴦�ĳ���
		float m_attachMat[16];

		//���ιҽӵ���������
		char m_meshName[256];
		//�ҽӵ�BodyPart��λ
		int m_bodyPart;

		//���ҽӵĹ���
		IModel* m_attachModel;

		//��̾���
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

	/// ģ����ص�LightMap����
	struct ILightMapInfo
	{
		H3DI::ITexture* m_pTex;	/// LIGHTMAP��ͼָ��

		float m_CoordBias[2]; /// UVƫ����Ϣ
		float m_CoordScale[2];/// UV������Ϣ

		float m_clrScale[3]; /// ��ɫ��ǿϵ��
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

		//���п���

		virtual void					SetGeometry(IGeometry* pGeom)=0;
		virtual IGeometry*				GetGeometry()=0;
		virtual void					RunGeomAnimation(bool bRun,float fStartTime)=0;//�������屾��ļ��ζ���

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


		//���ӷ�Χ
		virtual	float GetVisibleDist() = 0;
		virtual	void SetVisibleDist(float dist) = 0;

		//���һ��ģ�ͺŵĶ�����������ݣ�
		//pVertBuf��pIndexBuff�������������ָ�룬���ڴ�����ֵ
		//pVertNum,pIndexNum����������ĸ�������ǰpVertBuf��pIndexBuff�������ָ���ǣ����ض���������ĸ�����һ������´��붥��������ĸ�����
		//����ֵ��������Ķ�����������������ڵ���ʵ�ʵ�ģ�����������ʱ������,���򷵻ؼ�
		virtual bool GetVertexAndIndex( float *pVertBuf,unsigned int *pIndexBuff,int *pVertNum,int *pIndexNum ) = 0;

		///�����������ģ�͵Ĳ���,����1��ʾ�ɹ���0��ʾʧ�ܡ�
		virtual int ReloadMaterialInstance()=0;
		///��������fx
		virtual int ReloadFx()=0;

		///����ģ�͵�ģ�����ӡ�0.0-1.0�ĸ�������Ϊ0ʱ��ʾģ����ȫ������Ϊ1�Ǳ�ʾ��ȫ�����˶�ģ����0-1֮�������ʾ�����˶�ģ���ĳ̶ȡ�
		virtual void SetMotionBlurFactor(float fFactor) = 0;
		///�����ڵ���ѯ��״̬
		virtual void	SetUseOcclusionQuery(bool bVal) = 0;
		///��ȡ�Ƿ�ʹ���ڵ���ѯ��״̬
		virtual bool	UseOcclusionQuery() const = 0;
		///��ò�ѯ�����0��ʾ����ȫ�ڵ���
		virtual unsigned int GetOcclusionQueryResult() = 0;


		//////////////////////////////////////////////////////////////////////////
		//�������

		//����������2����ɫc0,c1�����յ���ɫ��c0*������ɫ+c1
		//����ֵ1��ʾ�ɹ���0��ʾʧ�ܡ�ʧ�ܵ�ԭ��������Ĳ��ʲ�֧�ָò���
		virtual int HightLight(float r0,float b0,float c0,float r1,float b1,float c1)=0;

		///�õ��²��ʣ������������id����0��ʼ
		virtual H3DI::INewShader* GetNewShaderByIndex(unsigned int i)=0;

		///�õ��²��ʣ����������������
		virtual H3DI::INewShader* GetNewShaderByName(const char* name)=0;

		///�����²��� ��Ӱ�쵽����ģ�͵�����mesh
		virtual int SetNewShader(H3DI::INewShader* p)=0;

		///ͨ��һ������ʵ�����ļ����Ͳ���ʵ�������� ��һ���������ø�����ģ�ͣ���Ӱ�쵽����ģ�͵�����mesh
		///����ֵ�Ǵ��ļ��еõ���INewShader,0��ʾʧ��
		virtual H3DI::INewShader* SetNewShader(const char* filename,const char* matballName)=0;


		///�����²��� ��һ���������ø�ĳ��mesh������0��ʾʧ�ܣ�������û�и�mesh
		virtual int SetMeshNewShaderByName(const char* meshName,H3DI::INewShader* p)=0;

		///ͨ��һ������ʵ�����ļ����Ͳ���ʵ�������� ��һ���������ø�ĳ��mesh
		///����ֵ�Ǵ��ļ��еõ���INewShader,0��ʾʧ��
		virtual H3DI::INewShader* SetMeshNewShaderByName(const char* meshName,const char* filename,const char* matballName)=0;

		///�����²��� ��һ���������ø�ĳ��mesh������0��ʾʧ�ܣ�������û�и�mesh
		virtual int SetMeshNewShaderByIndex(int meshIdx,H3DI::INewShader* p)=0;

		///ͨ��һ������ʵ�����ļ����Ͳ���ʵ�������� ��һ���������ø�ĳ��mesh
		///����ֵ�Ǵ��ļ��еõ���INewShader,0��ʾʧ��
		virtual H3DI::INewShader* SetMeshNewShaderByIndex(int meshIdx,const char* filename,const char* matballName)=0;

		///���ڴ�����һ������ģ���ģ�ͣ�ģ�͵����������ܵ�Ӱ�졣����1��ʾ�ɹ�
		virtual int SetMaterialTemplateFromMem(void* pXmlDoc)=0;

		///���ڴ�����һ������ģ���ģ�͵�һ�����񣬷���1��ʾ�ɹ���0��ʾ�Ҳ��������ֵ�����
		virtual int SetMeshMaterialTemplateFromMemByName(const char* meshName,void* pXmlDoc)=0;

		///���ڴ�����һ������ģ���ģ�͵�һ�����񣬷���1��ʾ�ɹ���0��ʾ�Ҳ���������
		virtual int SetMeshMaterialTemplateFromMemByIndex(int meshIdx,void* pXmlDoc)=0;

		///���ڴ�����һ������ʵ����ģ�͵�һ�����񣬷���1��ʾ�ɹ���0��ʾ�Ҳ���������
		virtual int SetMeshMaterialInstanceFromMemByName(int meshIdx,void* pXmlDoc)=0;	

		///���ڴ�����һ������ʵ����ģ�͵�һ�����񣬷���1��ʾ�ɹ���0��ʾ�Ҳ���������
		virtual int SetMeshMaterialInstanceFromMemByName(const char* meshName,void* pXmlDoc)=0;
		//////////////////////////////////////////////////////////////////////////
		//���½ӿڲ�Ҫʹ��

		///���������Ƿ���з���Ч��
		///����b:�Ƿ�������
		///����plane����һ��4��Ԫ�ص����飬�������ƽ��ķ���
		virtual void SetIsReflectionObj(bool b,float* plane)=0;

		///��ȡ�����Ƿ���з���Ч��
		///����:�Ƿ�������
		///����plane����һ��4��Ԫ�ص����飬�������ƽ��ķ���
		virtual bool GetIsReflectionObj(float* plane)=0;

		///���������Ƿ���뷴����Ⱦ
		virtual void SetCanBeReflection(bool b)=0;

		///��ȡ�����Ƿ���뷴����Ⱦ
		virtual bool GetCanBeReflection()=0;

		///���÷���Զƽ��
		///������Զƽ�����
		virtual void SetReflectionFarClipPlane(float dis)=0;

		///���������Ƿ�����������
		virtual void SetIsRefracionObj(bool b)=0;
		virtual bool GetIsRefracionObj()=0;

		///����������
		virtual void SetRefracionIndex(float f)=0;
		virtual float GetRefracionIndex()=0;

		//�༭�����ɹ�âʱ���õĽӿ�
		virtual void  Editor_GenerateMetalStar() = 0;
		//////////////////////////////////////////////////////////////////////////
		//��ȡ��â�ļ�����
		//	���أ���â����ֵ��
		//	������psize������Ͳ��������ع�â���ݴ�С��
		virtual void * Editor_GetMetalStarData (unsigned int* psize) = 0;//

		//���ܣ�����һ��������ģ���ϵİ�Χ������ײ����Ϣ
		//����
		//rayOrigin������������������ɵ����飬��ʾһ�����ߵ���ʼ��
		//rayDir������������������ɵ����飬��ʾһ�����ߵķ���
		//ModelBVTestInfo ��һ�������׵�ַ�����ڽ���ķ��ء�������ײ���İ�Χ�а��Ⱥ�˳��ID����ײ�����귵�ظ��ͻ��ˡ�����Ĵ�С����С��һ��ģ�͵İ�Χ�и�������Χ�и������������ṩһ�����еõ�
		//nResultBufferCount�������Ԫ�ظ�������ֹ�����������Խ��
		//����ֵ�����صĽ���ĸ���,���Ϊ��˵��û����ײ
		virtual int  RayTestWithBoundingVolumes(const float* rayOrigin, const float * rayDir, ModelBoundingVolumeTestInfo *pOut, int nResultBufferCount) const = 0;
		//��ȡ��Χ��ĸ���
		virtual int	 GetBoundingVolumesCount() = 0;

		//���ܣ�������
		//	//����
		//	RayOrg��������������
		//	RayDir���������߷���
		//	fOutDistance�����淵�صĽ���������ֵ����ײ�㵽�������ľ��롣
		//����ֵ��������ģ���Ƿ���ײ
		virtual bool  RayTestWithTriangles(const H3DVec3 & RayOrg, const H3DVec3 & RayDir,float & fOutDistance) = 0;

		//!������ؽӿ�
		//�������ߵõ��ҽ����ݼ�
		//�ڶ���������ʾ�Ƿ���Ҫת�����߿ռ�
		virtual int	  QueryAttachPoint(IAttachModelInfo& rayResInfo,bool bTransToLocal=true) = 0;
		
		//!�ҽӹ���.
		virtual int	  AttachModel(const IAttachModelInfo& rayInfo) = 0;

		//!ȡ���ҽ�
		virtual int	  DetachModel(const IAttachModelInfo& rayInfo) = 0;

		//!Ԥ����fx
		virtual int PreGenFx(H3DI::IFxInfo* p)=0;

		///!����LightMap��ͼ�ļ�����Info��,MeshIDΪ��ģ�͵���������
		virtual int SetLightMapInfo(unsigned int MeshID, const ILightMapInfo& info) = 0;

		/**
			lightmapSizeBuffer: mesh��Ӧ��lightmap size����geometry��mesh������һ��
			uvTexturePathName: ����Ԥ��uv��ֵĽ�����紫��"d:\\lightmapUVTest%d.bmp",��
								�����d:\\lightmapUVTest0.bmp, d:\\lightmapUVTest1.bmp���ļ���
								����ʱ��NULL
			bReadOnlyModified: ���ڷ����Ƿ��޸���lmm�ļ���ֻ�����ԣ�����ΪNULL
			����ֵ���ɹ�����true��ʧ�ܷ���false�����ʧ�ܣ������ø����lightmapsize�������������ֶ�չuv
		*/
		virtual bool GenerateLightmapUV(const int* lightmapSizeBuffer, const char* uvTexturePathName, int* bReadOnlyModified) = 0;

		///���ź���
		virtual void HelpFunction(int i,void* param0,void* param1=0,void* param2=0,void* param3=0,void* param4=0)=0;


	};

	class IReflectModel: public IModel
	{
	public:
		virtual void							SetPlane(const float* vec4PlaneEq)=0;
		virtual void                            GetPlane(float* vec4PlaneEq)=0;
	};
	/**
	��������ģʽ
	*/
	enum EActionTransitionMode
	{
		/**
		0�������ɵ�A1��ʼ�ڼ䣬�Ƿ����A1���粻����A1��A0,A1֮���ƾ�ն��һ�ι���ʱ��.
		�������A1������ʱ�������A1�Ķ���ʱ���ڣ����������ܳ��Ȳ���仯
		*/
		TRANSITION_NEXT_UPDATE = 1<<0,
		/**
		A0����ǰ0.3�뿪ʼ���ɵ�A1�ĵ�һ�壬���ʱ�����Ƿ����A0���粻���£��൱�����������ֵ
		*/
		TRANSITION_CURRENT_UPDATE	= 1<<1,//���巽ʽ��EActionTransitionMethodָ��
		/**
		A0������A1��ʼ���Ƿ���ΪA1�Ǿֲ�������
		��A1�Ǿֲ�������A1��ʼʱ��������λ�õ���A0���һ�������λ�ã�A1��һ��ĸ�����λ�á�
		��A1��ȫ�ֶ�����A1��ʼʱ������λ�õ���A1��һ��ĸ�����λ��
		*/
		TRANSITION_LOCALLY	= 1<<2,
		/**
		A0����ǰ0.3�뵽A1��һ������ڼ䣬�ŵ�λ�ò���
		*/
		TRANSITION_FIXED_FOOT = 1<<3           
	};
	//��������ʱ�Ĳ�ֵ��ʽ
	enum EActionTransitionMethod
	{
		//�ӵ�ǰ֡���ɵ�һ����̬֡,��A0��A1��0.3��
		TRANSITION_TO_STATIC = 0,
		//�ӵ�ǰ֡���ɵ�һ����̬֡,��A0��A1�ĵ�ǰʱ��
		TRANSITION_TO_DYNAMIC = 1,
	};
	/**
	һ�������������
	��춯�����Ի������Ӱ��һ����ɫ����̬
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
		���õ�һ��̬֡
		*/
		virtual int SetStaticFrame(const char* name) = 0;
		/**
		���þ�̬֡
		*/
		virtual int SetStaticFrame(unsigned int id, const char* name, float weight) = 0;
		/**
		���þ�̬֡����
		*/
		virtual void SetStaticSeq(const char** names, const float* intervals, unsigned int count, bool loop) = 0;
		/**
		���ö���֡����
		*/
		virtual void SetActionSeq(const char** names, unsigned int count, bool loop) = 0;
		/**
		���õ�һ����֡
		*/
		virtual int SetAction(const char* names, bool loop) = 0;
		virtual int SetNextAction(const char* names, bool loop) = 0;
		// ͬ������һ���첽���ص�action
		virtual unsigned int SetActionAndFinishTask(unsigned int taskId, bool loop)=0;
		virtual unsigned int SetNextActionAndFinishTask(unsigned int taskId, bool loop)=0;
		
		/**
		�õ���ǰ����
		*/
		virtual IAction* GetCurrAction(void) = 0;
		/**
		Clear all stuff
		*/
		virtual void Clear() = 0;
		/**
		�������ͨ����Ȩ��, ���м���ͨ����Ȩ�ػᱻ��һ��
		*/
		virtual void SetWeight(float) = 0;
		/**
		�õ�Ȩ��
		*/
		virtual float GetWeight(void)const = 0;
		/**
		���ö�������ʱ��
		*/
		virtual void SetTransitionTimeFromCurrent(float) = 0;

		virtual void SetTransitionTimeToNext(float) = 0;
		/**
		�õ���������ʱ��
		*/
		virtual float GetTransitionTimeFromCurrent(void)const = 0;

		virtual float GetTransitionTimeToNext(void)const = 0;
		/**
		���õ�ǰ����ʱ��,ֻ�ھ�֡����,��һ����֡,����֡����ģʽ��������
		*/
		virtual void SetCurrActionTime(float) = 0;
		/**
		�õ���ǰ����ʱ��
		*/
		virtual float GetCurrActionTime(void)const = 0;
		/**
		�õ���ǰ��������
		*/
		virtual float GetCurrActionLength(void)const = 0;
		/**
		ֻ�����ڹ��ɶ���
		*/
		virtual bool IsTransitingToNext(void)const = 0;

		virtual bool IsTransitingFromCurrent(void)const = 0;
		/**
		�Ƿ�ѭ��
		*/
		virtual bool IsLoop(void)const = 0;
		/**
		�Ƿ��ռ
		*/
		virtual bool IsDominating(void)const = 0;
		/**
		�õ�channel ID
		*/
		virtual unsigned int GetChannelID(void)const = 0;
		/**
		���ö�������ģʽ, Ĭ��ΪTRANSITION_SYNC
		*/
		virtual void SetTransitionMode(int mode) = 0;
		/**
		�õ���������ģʽ
		*/
		virtual int GetTransitionMode(void)const = 0;

		virtual void Draw(void)const =0;

		//�õ���ǰ���������֣�����ֵ��0��ʾû�е�ǰ������1����ʾ�ɹ���-1��ʾ�����buffer����̫С
		virtual int GetCurrentActionName(char* buffer,unsigned int bufferlen)=0;

		//�õ���һ�����������֣�����ֵ��0��ʾû��next������1����ʾ�ɹ���-1��ʾ�����buffer����̫С
		virtual int GetNextActionName(char* buffer,unsigned int bufferlen)=0;

		//�õ���һ�������Ƿ�ѭ��������-1��ʾû����һ������ ����0��ʾ��ѭ�� ����1��ʾѭ��
		virtual int GetIsNextActionLoop()=0;
		//�ڵ�ǰ������������ѭ������
		virtual	void SetActionLoop(bool) = 0;
		//�ڵ�ǰ��һ����������ѭ������
		virtual void SetNextActionLoop(bool)=0;
		//��������ʱ�Ĳ�ֵ��ʽ
		virtual void SetTrainsitionMethod(EActionTransitionMethod) = 0;
		//���õ�ǰ�����ۻ�λ��
		virtual void SetRootPos(const H3DVec3& pos) = 0;
		//��ȡ��ǰ�����ۻ�λ��
		virtual const H3DVec3& GetRootPos()const = 0;
		//���õ�ǰ�����Ƿ񲻱��ں�
		virtual void SetSkipBlend(bool) = 0;

	protected:
		virtual ~IAnimationChannel(){}
	};

	/**
	�������塣ISkeletonModel���Կ��ƹ������嵱ǰ�Ķ����������õ�����ÿ����ͷ�ĵ�ǰλ��/��ת״̬
	������Լ�������Ծ���ͬʱ���Եõ�ÿ����ͷ��ǰ�Ķ���IAnimation��
	*/


	/**
	channel mode:
	0 : ��һ��֡
	1 : ������֡
	2 : ��֡����
	3 : ����֡����
	4 : ��һ����֡
	5 : ֹͣ
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
	*	���༭����ӵĽӿ����ݽṹ,���ڱ༭���༭������������
	*/

	enum EPHXDATATYPE
	{
		//�����������ģ��
		PHXDATATYPE_BOUND,
		//���沼������ģ��
		PHXDATATYPE_CLOTH,
		//����ؽ�����,����ؽ����ݵ��ڱ������и���������ģ��
		PHXDATATYPE_JOINT,
		//��������
		PHXDATATYPE_CLOTHMESH,
		//
		PHXDATATYPE_COUNT
	};
	//��־λ,��ֵ��Ӧ��NxFlag
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
	//��־λ,�������־�޹�
	enum ECLOTHFLAG
	{
		CLOTH_FLAG_ATTACH_TO_COLLISIONSHAPE = 1<<0,
		CLOTH_FLAG_USE_CONSTRAIN = 1<<1
	};
	//��������
	enum EBOUNDTYPE
	{
		//!����
		BOUND_SPHERE = 0,
		//!����
		BOUND_CAPSULE,
		//!δ֪
		BOUND_UNKNOWN
	};
	//�����־λ
	enum EBOUNDFLAG
	{
		BOUND_FLAG_KINEMATIC = 1<<0,
		BOUND_FLAG_BE_ATTACHED = 1<<1
	};
	//�ؽ�����
	enum EJOINTTYPE
	{
		JOINT_SPHERICAL = 0,
		JOINT_DISTANCE
	};
	struct H3DClothMesh
	{
		//����
		const float* m_meshData;
		//�������
		int m_vertCount;
		//�����θ���
		int m_triCount;
		//��������.��С��triCount*3
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
		//��������
		char m_paraName[256];
		//���ϱ�־λ
		int m_clothFlag;
		//���������־λ
		unsigned int m_clothPhxFlag;
		//����ϵ��
		float m_bendingStiffness;
		//����ϵ��
		float m_stretchStiffness;
		//���
		float m_thickness;
		//˥��ϵ��
		float m_damping;
		//��������
		int m_iterations;
		//Ħ��ϵ��
		float m_friction;
		//�����ܶ�
		float m_clothDesity;
		//�ҽ���Ӧϵ��
		float m_attachResponse;
		//��ײ��Ӧϵ��
		float m_collResponse;
		//ģ����
		int m_hierarchLevel;
		//��ѹ
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
		//�ߴ�
		float m_dim[3];
		//��Χ��󶨵Ĺ���.Ŀǰ���ֻ֧��2��
		char m_parBoneName[4][256];
		//��Ӧ��Ȩ��
		float m_parBoneWeight[4];
		//��ײ������
		int m_boundType;
		//��־λ
		int m_boundFlag;
		//��̬
		float m_pos[3];
		float m_quat[4];
		//��������
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
		//������Ⱦ���󡣺��߼��������������ͬ
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
		�õ�ĳһ��ͨ���Ķ���, id�Ϸ�ֵΪ[0,3]
		*/
		virtual IAnimationChannel* GetAnmChannel(unsigned int id) = 0;
		/*
		�������ͨ��������
		*/
		virtual void          ClearAllAnmChannels(void) = 0;
		//by zhengchengjun 2011-11-25
		/*
		������Щ����ͨ��Ϊ��ռͨ��, buff=NULL�������ͨ����Ϊ�Ƕ�ռͨ��
		*/
		virtual void   SetDominatingChannel(int* buff, unsigned int buffLen) = 0;

		virtual unsigned int   GetDominatingChannel(int* buff, unsigned int buffLen)const = 0;

		virtual void  SetChannelModifier(IAnimationChannelModifier* p) = 0;

		virtual IAnimationChannelModifier*  GetChannelModifier(void)const = 0;

		virtual void ClearChannelModifier(void) = 0;

		virtual void LoadBodyBounds(const char* fileName) = 0;


		virtual unsigned int GetActionNames(const char** buff, unsigned int buffLen) = 0;
		virtual unsigned int GetActionNamesCopy(char* buff, unsigned int buffLen, unsigned int nameLen) = 0;

		//by sssa2000 090203 Ϊ�༭����ӽӿ�
		//���ƹ���
		virtual void DrawSkeleton()=0;
		virtual void CopyTo(ISkeletonModel *pModel)const = 0;
		//������������Ķ�����ʹ��ǰ����Ķ��������������������ĳ������,iBoneId�ǰ󶨵Ĺ���ID
		virtual bool	RelationAnimation(ISkeletonModel *pHorseModel,const char *animNameSelf,const char *animHorse,int iBoneId = 0) = 0;

		//�ڸ��¹���ģ�͵�ʱ��,�Ƿ�Ը�����ͷ���м���, Ĭ��ֵΪtrue
		//�����ѡ��Ϊfalse, ��ISkeletonModel��copy������Ҳ����Ҫ������ͷ����.
		virtual void	SetUpdateBones(bool bUpdateBones) = 0;

		//�����������,̫������,����������Բ��ϸ��µ�Ӱ��
		virtual void	SetMountMatrix(const H3DMat4& mountMatrix)=0;

		//������������Ա������,����ָ��������ʵ������
		virtual int		GetPhxEntityNames(const char** pNames,int num,int phxType)=0;
		//��������ʵ�������,���ǲ��ϲ���ʱ,������ǲ���������
		virtual void   SetPhxEntityPara(const char* pName,void* phxPara,int phxType) = 0;
		//��ȡ����ʵ�������,���ǲ��ϲ���ʱ,������ǲ���������
		virtual void	GetPhxEntityPara(const char* pName,void* phxPara,int phxType) = 0;
		//��ȡ�������,�������������,Ŀǰֻ֧�ֲ���
		virtual void   GetPhxParaByName(const char* paraName,void* phxPara,int phxType) = 0;
		//!�Ӳ�������ɾ����һ������,Ŀǰֻ֧�ֲ���
		virtual void   DelPhxParaByName(const char* paraName,int phxType) = 0;
		//�½�һ������ʵ��
		virtual void   CreatePhxEntity(const char* pName,void* phxPara,int phxType) = 0;
		//ɾ��һ������ʵ��
		virtual void   DelPhxEntity(const char* pName) = 0;
		//������������ģ��,������EPhxDataTypeָ��
		virtual void   SavePhxDataTemplate(const char* pName,int phxDataType) = 0;
		//�����������ݵ�bp3��,��ǰ����
		virtual void   SavePhxDataToBp3(const char* pFileName) = 0;
		//����.����clearCur�����Ƿ���Ҫ�������ǰ�Ѿ���ȡ�Ĳ���
		virtual void   LoadPhxDataTemplate(const char* pName,int phxDataType,bool clearCur) = 0;
		//��ȡ��ǰ���в��ϲ�����
		virtual int   GetAllPhxDataParas(const char** pNames,int bufferLen,int phxDataType) = 0;
		//�ں�������
		virtual void   BlendPhxResult() = 0;
		//��������
		virtual void   RenderPhxInfo() = 0;

		//���һ�������ڹ����ϵ���Ԫ�����ڶ�������֮�󣬽���ת���ӵ�������
		virtual void	AddQuatToBone(int index,const H3DQuat& quat) = 0;
		//������е���Ԫ��
		virtual void	ClearAdditionalQuat() = 0;
		//��ȡ���Ϲ�â�ļ�����
		//���أ���â����ֵ��
		//������psize������Ͳ��������ع�â���ݴ�С��
		virtual void *  Editor_GetClothMetalStarData (unsigned int* psize) = 0;
		//���Ź���,by lzp 2011-4-14
		virtual void    SetScaleInfo(const ScaleSkeletonInfo& sInfo)=0;
		virtual void	 ClearScaleInfo() = 0;

		//sssa2000 08.03.24:
		//��̬���ø����������
		virtual void                SetThisActorPhy(bool b)=0;
		//��ø����������״̬��ע�⣬������һ���� ����Ҫ��ʾ������һ��SetThisActorPhy������ÿ�ε�GetThisActorPhy������Ч
		virtual bool				GetThisActorPhy()=0;

		// ��ĳ��mesh�������򲹳�ֵ
		virtual void SetSortingOffset(const char* meshName, float offset) = 0;

		// ʹĳ��mesh������ʾ
		// bHightLight true : ���ø߹�Ч����false : �ָ�
		virtual void HightLightSubEntity(const char* subEntityName, bool bHightLight) = 0;

		//
		virtual void	UpdateCpuSkin(float t) = 0;

		//������Ƥ��Ԥ������̬
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
		//ʹ������ֱ
		IKUS_PLUMB = 1<<1,
		//ʹ�����ڵ�����
		IKUS_ONTERRAIN = 1<<2,
		//�������״̬
		IKUS_CHECKE = 1<<3,
	};

	enum EIKDebugState
	{
		//����Ľŵ����ϻ��ߣ�
		IK_DEBUG_LINE_FOOT_UP = 1<<1,
		//����Ľŵ׵ĵ������ϻ��ߣ�
		IK_DEBUG_LINE_GROUND_UP = 1<<2,
	};
	class IIKSkeletonModel: public ISkeletonModel
	{
	public:
		//�õ�IK���ĳ�ʼ�˵�
		virtual void	GetIKLine( int index,H3DVec3 &pPosBegine,H3DVec3 &pPosEnd ) = 0;
		//�õ�IK��������֮��ԭ�˵����ڵ�λ��
		virtual void	GetIKPos(int index ,H3DVec3 &begin,H3DVec3 &end ) = 0;

		//ͨ�������ĵľ����ж����Ƿ��ŵ�
		//phySceneId��������ID
		//phyObjId��������ID
		virtual bool			IsOnTerrain(const H3DVec3 &vPos,const H3DQuat &vQuat,float fEpsilon,bool bforceComputNormal,float &fFrontHeight,float &fBackHeight,H3DVec3& vFrontNormal,H3DVec3& vBackNormal,unsigned int phySceneId,unsigned int phyObjId) = 0;

		//virtual void			GetFeetNormal(const H3DMat4 &transform,H3DVec3 *pNormals) = 0;

		//�õ���ǰ���ڵ����ϵ���̬
		//vPos.x,vpos.y���ó���ǰ�����꣬�߶ȷ�����vPos.z��
		//qRetRot���㷵�ص���ת��Ԫ��
		//phySceneId��������ID
		//phyObjId��������ID
		virtual void			GetTransformByTerrain(H3DVec3 &vPos,H3DQuat &qRetRot,unsigned int phySceneId,unsigned int phyObjId) = 0;


		//����IK����ʱ�ı�־��IKUpdateState
		virtual void	SetIKUpdateState(unsigned int nState) = 0;


		//���õ��Ա�־ ȡֵ��EIKDebugState�İ�λ��
		virtual void	SetDebugState(unsigned int nState) = 0;



	};

	// actor����
	enum EActorType
	{
		ACTOR_HUMAN = 0,	// ��
		ACTOR_PET,			// ��
		ACTOR_TYPE_NUM,
	};

	/// ��ɫBodypartλ��
	enum EBodypartType
	{
		BODYPART_SKIN = 0,	// 0 Ƥ��
		BODYPART_EYE,		// 1 �۾�
		BODYPART_FACE,		// 2 ��
		BODYPART_HAIR,		// 3 ͷ��
		BODYPART_UPPER,		// 4 ����
		BODYPART_HAND,		// 5 ����
		BODYPART_PANTS,		// 6 ����
		BODYPART_STOCKING,	// 7 ����
		BODYPART_SHOES,		// 8 Ь
		BODYPART_SUIT,		// 9 ��װ
		BODYPART_ARM,		// a �첲
		BODYPART_NUM,
	};

	/// ����Bodypartλ��
	enum EPetBodypartType
	{
		PET_BODYPART_FACE = 0,	// 0 ͷ
		PET_BODYPART_BODY,		// 1 
		PET_BODYPART_NUM,
	};

	//! ����Ҽ�λ��
	enum EActorAdornmentPosition
	{
		ACTOR_ADORNMENT_LEFTWRIST = 0,		// 0 ������
		ACTOR_ADORNMENT_RIGHTWRIST,			// 1 ������
		ACTOR_ADORNMENT_TAIL,				// 2 β��
		ACTOR_ADORNMENT_LEFTHAND,			// 3 ���ֳ�
		ACTOR_ADORNMENT_RIGHTHAND,			// 4 ���ֳ�
		ACTOR_ADORNMENT_BACK,				// 5 ����
		ACTOR_ADORNMENT_HEADGEAR,			// 6 ͷ��
		ACTOR_ADORNMENT_FACEGEAR,			// 7 �沿
		ACTOR_ADORNMENT_EARRING,			// 8 ����
		ACTOR_ADORNMENT_NECKLACE,			// 9 ����
		ACTOR_ADORNMENT_BRACELET,			// 10 ����
		ACTOR_ADORNMENT_ANKLETS,			// 11 ����
		ACTOR_ADORNMENT_CHESTBADGER,		// 12 ����

		ACTOR_ADORNMENT_NUM,
	};
	//! ����Ҽ�λ��
	enum EPetAdornmentPosition
	{
		PET_ADORNMENT_BACK = 0,		// 0 ����
		PET_ADOENMENT_ANKLETS,		// 1 ����

		PET_ADORNMENT_NUM,
	};


	//!�ɻ�װ�Ĺ���ģ�ͣ��������γ���
	class IAvatarSkeletonModel:public ISkeletonModel
	{
	public:
		//!����bodypart��������bpt�ļ���·��
		virtual bool SetBodyPart(const char* bpt_path)=0;

		virtual unsigned int SetBodyPartAndFinishTask(unsigned int taskId)=0;

		//!���ùҼ�������0��λ�õ�����������1��spe�ļ���·��
		virtual bool SetAdornment(EPetAdornmentPosition adornmentposition, const char* adornmentname)=0;

		virtual unsigned int SetAdornmentAndFinishTask(EPetAdornmentPosition adornmentposition, unsigned int taskId) = 0;

		//! ���ùҼ��Ŀɼ���
		//! Ϊ��֤��ǰ���ݣ��Ҽ�Ĭ���ǿɼ���
		virtual void			SetAdornmentVisibility(EPetAdornmentPosition adornmentposition, bool inVisibility) = 0;

		virtual int GetSkeletonModels(IModel** pSkeletonModelVector,int vectorSize) = 0;

		virtual int GetAdornmentSkeletonModels(H3DI::IModel** pSkeletonModelVector, int vectorSize) = 0;

		//���������Ƿ�ʹ�ð�Χ��. ����ֵ1��ʾ�ɹ���С��0���ɹ�
		virtual int SetUseCustomBoundBox (bool b)=0;

		//���Ժ���
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
		//����ACTORλ�ã�����Z��Զ������Ϊ0
		virtual void			SetActorLocationMatrix(const H3DMat4& mat)=0;
		//��BODYPART�������ƴ��BODYPART֮��Ķ���ͷ���
		virtual void			PostProcessCreating()=0;

		//��̬����͸������
		virtual	void			SetThisActorClothSort(bool b)=0;

		virtual bool			GetThisActorClothSort()=0;	

		///by sssa2000 2008.04.25
		// ���ͷ�������ˣ���ô���øú�������
		virtual void			ResetActorHair()=0;

		//���Ժ���
		virtual void			DebugFunction(int i)=0;

		virtual int GetSkeletonModels(IModel** pSkeletonModelVector,int vectorSize) = 0;

		virtual int GetAdornmentSkeletonModels(H3DI::IModel** pSkeletonModelVector, int vectorSize) = 0;

		//���������Ƿ�ʹ�ð�Χ��. ����ֵ1��ʾ�ɹ���С��0���ɹ�
		virtual int SetUseCustomBoundBox (bool b)=0;

		//ͨ��bodpyart�����ֻ�ȡ��bodypart ��ǰ������������renderable�����в��ʡ���������䵽pResArray
		//�������Ҫ���صĲ����������ڵ����߷��������ĳ��ȣ�����ֵΪ-1
		//����ֵ������ʵ�����Ĳ��ʸ���
		//����bpName��bodypart�����֣�����104001003������ǹҼ� Ҳ����
		//����pResArray:�ɵ����߷����INewShader�����飬
		//����len:����ĳ���
		virtual int GetAllShaderByBodyPartName(const char* bpName,INewShader** pResArray,int arraylen)=0;

		//����bodypart���ֻ�ȡINewShader
		// ���ùҼ�
		virtual bool			SetAdornment(EActorAdornmentPosition adornmentposition, const char* adornmentname) = 0;

		virtual unsigned int	SetAdornmentAndFinishTask(EActorAdornmentPosition adornmentposition, unsigned int taskId) = 0;

		//! ���ùҼ��Ŀɼ���
		//! Ϊ��֤��ǰ���ݣ��Ҽ�Ĭ���ǿɼ���
		virtual void			SetAdornmentVisibility(EActorAdornmentPosition adornmentposition, bool inVisibility) = 0;
	};

	/**
	����ģ�塣��RenderCore�ɴ����ļ����롣�����IModel����������Դ�͹�������������û�ֻ��Ҫ��
	IGeometry�õ�IMesh��IMeshҲ������ISubModel�õ���
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
	�����õ����������ISkeleton���ݡ�ISkeletonֻ�������ϵͳ�ĳ�ʼ״̬��������ʵ�����㡣
	ͨ��ISkeleton���Եõ�����������Լ�����IBone�е���Ϣ��
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
		��ȡ��ǰactor����ʹ�õ�mesh
		pBuffer : ���ڴ��IMeshָ���buffer������ΪNULL�����ǽ�����mesh������
		bufferSize : buffer�Ĵ�С�����buffer�����󣬺�������0
		����ֵ:mesh������
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
	//��������
	enum EH3DBEAMTYPE
	{
		//������еĹ���
		E_H3D_BEAM_VOL,
		//��Ƭ����
		E_H3D_BEAM_BOARD,
		//�������
		E_H3D_BEAM_POST,
		//UE����
		E_H3D_BEAM_UE
	};
	//��߲����ṹ
	struct tGlareProperty
	{
		//�ߴ�
		float m_width;
		float m_height;
		//��ɫ
		float m_color[4];
		//��ͼ
		const char* m_pTextureName;
		//����lib
		const char* m_pShaderLib;
		//����ʵ����
		const char* m_pShaderInstanceName;
		//����Դ�ľ���
		float m_disToLight;
		//��ת�ٶ�
		float m_glareRotVel;
		//�Ƿ�ɼ�
		bool m_bVisable;
		//�Ƿ�����������ת
		bool m_bRotateWithCamera;
		//�Ƿ����������
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

		//	��ǿ,������ǿ��Ϊ�������ֱ�Ӱ�����ɫ�͸߹⣬�������͹⡢�ӳ���Ⱦֻʹ�õ�һ����ǿ��
		//	��ȡ��ǿindex=1ʱȡ�߹��ǿSpecIntensity,index=0ʱȥԭʼ��ǿintensity
		virtual void					SetIntensity(float intensity, float SpecIntensity=-1.0f) = 0;
		virtual float					GetIntensity(int index=0) const = 0;


		// �۹�Ƶ�����Ƕȣ���ǿ���ڽǿ�ʼ˥����������޹��ա���λΪ�Ƕ�
		virtual void					GetAngle(float* inner, float* outter) const = 0;
		virtual void					SetAngle(float inner, float outter) = 0;

		// ����������Ƿ������Ӱ�Լ���Ӱ����ɫ
		virtual bool					GetShadowEnable() const = 0;
		virtual void					SetShadowEnable(bool bEnable) = 0;

		virtual void					GetShadowColor(float* vec4) const = 0;
		virtual void					SetShadowColor(const float* col) = 0;

		// ˥����Χ����near��ʼ˥������far����
		virtual void					GetRange(float* nearRange, float* farRange) const = 0;
		virtual void					SetRange(float nearRange, float farRange) = 0;

		// ���ȼ�
		virtual int						GetPriority() const = 0;
		virtual void					SetPriority(int nPriority) = 0;

		// �Ƿ�ʹ��ͶӰ��ͼ
		virtual bool					GetProjTextureEnable() const = 0;
		virtual void					SetProjTextureEnable(bool bEnable) = 0;
		// ͶӰ��ͼ���ļ���
		virtual void					SetProjTextureName(const char* strFileName) = 0;

		// �Ƿ�ʹ�ù����ͼ
		virtual bool					GetFakeLightSpot() const = 0;
		virtual void					EnableFakeLightSpot(bool bEnable) = 0;
		// �����ͼ���ļ���
		virtual void					SetFakeLightSpotTexture(const char* strFileName) = 0;

		//����һ������
		virtual void CreateLightBeam(EH3DBEAMTYPE beamType = E_H3D_BEAM_VOL) = 0;
		//���ù�������
		virtual void SetLightBeamType(EH3DBEAMTYPE beamType) = 0;
		//�ͷŹ���.���ͷŵ���ǰ�Ѿ����������й�������
		virtual void ReleaseLightBeam() = 0;
		//����һ�����.����һ���ƹ���ж�����,�������ﷵ�ع�ߵ�����
		virtual int CreateGlare(const tGlareProperty& gPro) = 0;
		//�ͷŹ��
		virtual void ReleaseGlare(int glareIndex) = 0;
		//���ù������ؾ���
		virtual void SetBeamLocalMat(const H3DMat4& mat) = 0;
		//���ù�ߵ�����
		virtual void SetGlareProperty(int glareIndex,const tGlareProperty& gPro) = 0;
		//��ȡ��ߵ�����
		virtual void GetGlareProperty(int glareIndex,tGlareProperty& gPro) = 0;
		//���ù����Ŀɼ���
		virtual void SetBeamVisable(bool b) = 0;
		//����/ͣ�ù�Դ
		virtual void SetLightEnable(bool b) = 0;
		//
		virtual bool GetLightEnable() = 0;
		//���ù���������
		virtual void SetBeamBrightness(float t) = 0;
		//���ù������ھ���0.1~1��
		virtual void SetBeamInnerRadius(float t) = 0;
		//���ú��������ģ����(0~1)
		virtual void SetBeamBlurCoeff(float f) = 0;

		// ����˥����Χ����near��ʼ˥������far����
		virtual void GetBeamRange(float* nearRange, float* farRange) const = 0;
		virtual void SetBeamRange(float nearRange, float farRange) = 0;
		// ��������Ƕȣ���λΪ�Ƕ�
		virtual void GetBeamAngle(float* inner, float* outter) const = 0;
		virtual void SetBeamAngle(float inner, float outter) = 0;
		//===============================LightShaft===================================
		//add by liren 2010-11-2 
		//!������ر������
		virtual void SetLightShaftEnable(bool bEnable) = 0;
		//!�����������ɫ
		virtual void SetLightShaftColor(const float *pcolor) = 0;
		//!������������� 
		virtual void SetLightShaftDepth(float fDepth) = 0;
		//!������Ƿ���
		virtual bool GetLightShaftEnable() const = 0;
		//!��ȡ�������ɫ
		virtual void GetLightShaftColor(float *pColor) const = 0;
		//!��ȡ��������� 
		virtual float GetLightShaftDepth() const = 0;

		//!�����������ֵ
		virtual void SetLightShaftThreshold(float fThreshold) = 0;
		//!�����������ֵ
		virtual float GetLightShaftThreshold()const = 0;
		//!���������ǿ��
		virtual float GetLightShaftIntensity() const = 0;
		//!��ȡ�������ɫ
		virtual void SetLightShaftIntensity(float fIntensity) = 0;
		//===============================!LightShaft===================================

		//!���õƹ��GUID
		virtual void SetGUID(const char* szGUID) = 0;
	};
	///����һ�����ⳡ���Ļ�����Ϣ
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

		//���¼����ǵ������������ר�õ�
		//////////////////////////////////////////////////////////////////////////
		float m_EnvAmibentR;		//���廷����
		float m_EnvAmibentG;		//���廷����
		float m_EnvAmibentB;		//���廷����

		float m_HemiLightRangeX;	//���շ�Χ
		float m_HemiLightRangeY;	//���շ�Χ
		float m_HemiLightRangeZ;	//���շ�Χ

		/// ��־λ���Ƿ�ʹ����յ��
		bool bUse1stLight;
		bool bUse2ndLight;
		bool bUse3rdLight;
		bool bUse4thLight;

/////   ����һյ�ƾ�һ�������һ����ɫ����������Ϊ�ƹ����ɫ��ɫ���ƹ�߹���ɫ���ƹ⻷������ɫ�ˣ�
		float m_1stLightDirX;
		float m_1stLightDirY;
		float m_1stLightDirZ;

		float m_1stLightDiffuseR;
		float m_1stLightDiffuseG;
		float m_1stLightDiffuseB;


		float m_2ndLightDirX;		//����ĵڶ�յ��
		float m_2ndLightDirY;		//����ĵڶ�յ��
		float m_2ndLightDirZ;		//����ĵڶ�յ��

		float m_2ndLightColorR;
		float m_2ndLightColorG;
		float m_2ndLightColorB;

		float m_3rdLightDirX;		//����ĵ�3յ��
		float m_3rdLightDirY;		//����ĵ�3յ��
		float m_3rdLightDirZ;		//����ĵ�3յ��

		float m_3rdLightColorR;
		float m_3rdLightColorG;
		float m_3rdLightColorB;

		float m_4thLightDirX;		//����ĵ�4յ��
		float m_4thLightDirY;		//����ĵ�4յ��
		float m_4thLightDirZ;		//����ĵ�4յ��

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

		float m_2ndLightDirX;		//����ĵڶ�յ��
		float m_2ndLightDirY;		//����ĵڶ�յ��
		float m_2ndLightDirZ;		//����ĵڶ�յ��

		float m_2ndLightDiffuseR;	//����ĵڶ�յ��
		float m_2ndLightDiffuseG;	//����ĵڶ�յ��
		float m_2ndLightDiffuseB;	//����ĵڶ�յ��

		float m_2ndLightAmibentR;	//����ĵڶ�յ��
		float m_2ndLightAmibentG;	//����ĵڶ�յ��
		float m_2ndLightAmibentB;	//����ĵڶ�յ��
		*/
		//////////////////////////////////////////////////////////////////////////

		//����ķ�Χ
		float m_WorldMinX;
		float m_WorldMinY;
		float m_WorldMinZ;

		float m_WorldSizeX;
		float m_WorldSizeY;
		float m_WorldSizeZ;

		//��յ���ɫ
		float m_SkyColorR;
		float m_SkyColorG;
		float m_SkyColorB;

		//�ر���ɫ
		float m_GroundColorR;
		float m_GroundColorG;
		float m_GroundColorB;

		//ȫ����Ӱͼ·��
		const char* m_ShmPath;
		//�Ƿ���Ҫǿ������������Ӱͼ
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

	//����ʱ��Ϣ
	struct IRuntimeInfo
	{
		unsigned int AllTriangles;						//���������е�����������
		unsigned int ThisFrameTriangles;				//��֡�е���������Ŀ
		unsigned int AllModelNumber;					//���������е�ģ��������������͸��ģ�ͣ�
		unsigned int AllTransparentModelNumber;			//���������е�͸����ģ������
		unsigned int ThisFrameModelNumber;				//��֡�е�ģ����Ŀ������͸����
		unsigned int ThisFrameTransparentModelNumber;	//��֡�е�͸��ģ�͵�����
		unsigned int AllH3DShaderNumber;				//���е�h3dshader���������
		unsigned int ThisFrameH3DShaderNumber;			//��֡��ʹ�õ�h3dshader����
		unsigned int ThisFrameShaderChangedNumber;		//��֡��shader�л��Ĵ���
		unsigned int AllTextureNumber;					//���������е����������
		unsigned int RenderStateChangedNumber;			//��֡����Ⱦ״̬�ĸı�
		float AllTextureMemory;							//��������������ռ�õ��ڴ棨kb����ͬ��
		float ThisFrameTextureMemory;					//��֡����������ռ�õ��ڴ�
		float AllVertexBufferMemory;					//���������е�vbռ�õ��ڴ�
		float ThisFrameVertexBufferMemory;				//��֡��ʹ�õ�vbռ�õ��ڴ�
		float AllIndexBufferMemory;						//���������е�ibռ�õ��ڴ�
		float ThisFrameIndexBufferMemory;				//��֡��ʹ�õ�ibռ�õ��ڴ�
		float fps;										//fps

	};
	enum BILLBOARD_PROPERTY
	{
		SIMPLE_QUAD = 0,//���ı��Σ��������û�ָ��
		COMMON = 1<<0,//��billboard����Զָ��ͷ
		ROTATE=1<<1,//�澵ͷ��ת����ֱEYE DIR��ת��������תЧ��
		ZOCCLUDE=1<<2,//ֻ������Z�ڵ���ûʵ�֣�
		HALO=1<<3,//���Σ���С��SCENE SPACE���䣨ûʵ�֣�
		LENFLEAR=1<<4,//��ͷ�⣨ûʵ�֣�
		OPACITY = 1<<5,//��ûʵ�֣�
		CORRECT_ROT = 1<<6,//��EYE POS��VECPOS�����ߴ�ֱ, �����Ǽ���EYE DIR��ֱ
		AXIS_ROT = 1<<7,//�����ã�����Z�ᾡ����EYE��ֱ��Z��Ϊ mat[2] ,mat[6] , mat[10],���εĳ���Z�ᡣ��Ҫ�ڱ༭���ｨ��һ��RECT
		RADIUS_ROT = 1<<8,//����һ���뾶��BILLBOARD��һ����Ϊ������ת
		DIR_AXIS = 1<<9,//ֻ��һͷ�����billboard_axis����billboard_ray
	};

	enum BILLBOARD_TYPE
	{
		BILLBOARD_SINGLE,//����billboard
		BILLBOARD_FLARE,//��ûʵ�֣�
		BILLBOARD_RAY,//ģ�¹��������ߣ���ͼ������Ϲ�����ͼҪ��
		BILLBOARD_AXIS,//������billboard��
		BILLBOARD_HALO,//��ûʵ�֣�
	};
	/**
	billboard�����Դ���BILLBOARD��Ҳ���Դ���һ�� �ı�����Ƭ
	*/
	class IBillboard : public IMoveObject
	{
	public:
		virtual BILLBOARD_TYPE			GetBillboardType()const=0;
		virtual float					GetBillboardRotate()const=0;
		//billboard����ת��Ϊ�˸�����ʹ�á����λ����ž�ͷ�Ƕ�ת����ת��
		virtual void					SetBillboardRotate(float fRotate)=0;
		//��COLOR��32-24λ����͸����,ABGR
		virtual void					SetBillBoardColor(unsigned int col)=0;
		virtual unsigned int			GetBillBoardColor()const=0;

		virtual void					SetSize(float fWidth,float fHeight)=0;
		virtual void					GetSize(float &fWidth,float &fHeight)=0;
		//�����Կ���BILLBOARD����
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
		//���ֲ�ε��νڵ�ĳ���
		unsigned int nWidth,nLength,nPageWidth,nPageLength,nPatchWidth,nPatchLength,nLeafWidth,nLeafLength;
		//�ⲿ����������±������ɵ��γ�ʼ��ʱ������á���ʾ�����νڵ����Ĳ����еĲ����
		unsigned int nNumLevel,nPageLevel,nPatchLevel,nLeafLevel;
		//����ÿ�����ӵĵ�λ
		float fGridUnit;
		//�߶�ͼ�и߶���ʵ�ʵ����и߶ȵ����ű�����
		float fHeightScale;
		//�ⲿ���������������0����
		int	  iDataType;
		//Alpha��ͼ�ľ���
		int	  iAlphaPrecision;
	};

	//�õ��ڳ����������Ľ����������������CLIENT����RELEASE��ʱ�ͷ�
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
		//��һ��������볡����
		virtual void					AttachModel(IMoveObject* pObj,int nLayer)=0;

		//��һ������ӳ���ɾ��
		virtual void					DetachModel(IMoveObject* pObj)=0;

		//�������ƶ�ʱ������ʹ�����ڳ������ƶ��� ֻ��CLIENT֪��MODEL�Ƿ��ƶ���
		//������û���ƶ�ʱ����Ҫ���ô˺�����
		virtual void					MoveModel(IMoveObject* pObj)=0;	

		//!!!!!! ISceneSearch must be Released by CLIENT !!!!!!
		//use aabb to search
		//ʹ��AABB����
		virtual ISceneSearch*			FindObjects(const float* pAABB,const int* pLayers,int numLayer)=0;
		//ʹ��AABB��X��Yƽ����������������Z��Χ
		virtual ISceneSearch*			FindObjects2D(const float* pAABB,const int* pLayers,int numLayer)=0;
		//use IRender's camera to search
		virtual ISceneSearch*			FindObjects(IRender* pRenderer,const int* pLayers,int numLayer)=0;
		//��׶�����������ڸ���RENDER TO IMAGE����Ч�У���SPOT LIGHTING����Ҫ
		//virtual ISceneSearch			FindObjects(tClipPlanes[5],const int* pLayers,int numLayer)=0


		//����MATRIX�õ�CAMERA��Ϣ��δʵ��03-12-3)
		virtual void					SetCurrentCamera(const float* pViewMatrix,const float* pProjectMatrix)=0;
		//����λ�úͽǶȵõ�CAMERA��Ϣ��δʵ��03-12-3)
		virtual void					SetCurrentCamera(const float* vecEyePos,float fov,float ratio,float near, float far)=0;
		//����IRENDER�е�ǰ��CAMERA�����ó���CULLING CAMERA���Ƽ�ʹ��
		virtual void					SetCurrentCamera(IRender* pRenderer)=0;
	};
	//����ϸ�����������
	enum ETerrainObjectLayer
	{

		ETOL_SmallPatch = 0,
		//��
		ETOL_Grass,
		//ϸ������
		ETOL_Tree,
		//��̬��ӵ���������
		ETOL_Others,
		//��
		ETOL_Lights,
		//ϸ������
		ETOL_DetailObj,
		//��Ч
		ETOL_SpecialEffect,
		//������
		ETOL_LayerCount,
	};


	class ITerrain : public IScene
	{
	public :

		//�û����һ����Ϣ������Ϣ����һ�����Σ��߶ȶ�Ϊ0
		virtual bool					Load(tTerrainInfo *pInfo)=0;	
		virtual bool					Load(const char* sTerrainFileName, ISpecialEffectManager *m_pSpeManager)=0;
		virtual bool					Save(const char* sTerrainFileName)=0;
		//�õ����γ��������
		virtual const tTerrainInfo&		GetTerrainInfo()const=0;

		//�õ�Զɽ
		virtual	IModel*					GetMountainModel() = 0;

		//����ĳ��ɼ�
		virtual void							SetLayerVisable(ETerrainObjectLayer type,bool bVisable) = 0;

		//����Զ����
		virtual void							SetLayerDist(ETerrainObjectLayer type,float farDist,float nearDist) = 0;

		virtual bool					TurnOff()=0;//*
		//����LOD

		virtual void					SetFlags(unsigned int nFlags)=0;//*
		virtual unsigned int			GetFlags()const=0;//*
		//����
		virtual unsigned int			Render()=0;//*
		virtual unsigned int			RenderMinLOD()=0;//*
		virtual unsigned int			RenderPatchs(const float* boxAABB,float s0,float t0,float s1,float t1,IShader* pIShader,float fRotation)=0;//*
		virtual int 					RenderRect(const float* pAABB,float s0,float t0,float s1,float t1,IShader* pShader,const float* vec4Color,float fRotation)=0;//*


		//�õ�������������Ч����
		virtual int						GetSpecialEffectNum() = 0;
		//�õ���ǰ��׶�е���Ч
		virtual  void					GetVisableSpecialEffect(ISpecialEffect **pBuffer,int &num) = 0;
		//���β��ı�һ�㲻�õ���
		virtual void					ReCaculateAABB()=0;//*
		//�򿪺͹ر�LOD
		virtual void					EnableLOD(bool bLod)=0;
		virtual void					SetErrorPixel(int nErrPixel)=0;
		virtual int						GetErrPixel()const=0;
		//
		virtual bool					IsLODEnabled()=0;
		//�����������ε�ͼ�����������λ�á�һ�㣬�����ε���ʱ�Զ�����Ϊ���ε��е�Ϊ��0��0����������
		//��CAMERA��Խ��������ʱ����������г����е����ݣ����Σ�MODEL����ת��Ϊ��һ��TERRAIN������
		virtual void					SetCenter(float x,float y,float z)=0;

		virtual void					GetCenter(float& x,float& y,float& z)=0;

		//һ��ȱʡһ��Ϊ16 �����Ƽ��ı�
		virtual void					SetUnit(float unit)=0;
		virtual float					GetUnit()=0;

		//���õ����ϵ�����(δʵ�� RENDERCORE�ӿ�03-12-3)
		virtual void					SetGlobalLight(ILight* pLight)=0;
		virtual ILight*					GetGlobalLight()=0;



		virtual float					GetHeight(float x, float y)=0;

		//��UN FINISHED 03-12-3��
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
		// 		������
		// 			pPoints��������������ˮƽ�����ϵ����ꡣ����������ת�۴���������Ӧ��Ϊһ�飬�����洢��
		// 			num������ת�۵��������
		// 			pVertexBuf������ֵ�����ɵĶ������ݴ洢��ָ����ָ��Ŀռ���
		// 			ivbSize�� ����pVertexBuf��ָ�ռ�Ĵ�С�����ֽڵ�λ������ʵ�������ֽ���.
		//			pIndexBuf: ����ֵ�����ɵĶ����������ݴ洢��ָ����ָ��Ŀռ���
		// 			iIbSize�� pIndexBuf��ָ�ռ�Ĵ�С�����ֽڵ�λ������ʵ�������ֽ���.
		virtual void					GenerateTriangels( const float* pPoints, int num, void *pVertexBuf, int &vbSize, void *pIndexBuf, int &iIbSize ,float fUVScale) = 0;

		//����һ�����Σ�һ�����μ����ʱ���������α�Ϊ�Ǽ���״̬
		virtual void					Active() = 0;
		//�ж�һ�������Ƿ񱻼���
		virtual bool					IsActive() = 0;
		//�༭���ӿڣ�ֻ�ڱ༭��ģʽ�¿��Ե���

		//�߶�ͼ��size��(length+1)*(width+1)
		virtual float*					GetHeightMap() = 0;

		//�û������ø߶�ͼָ�룬��ֱ���޸��ڴ���ֵ����Ҫ���һ���޸������Ա�������Բ�����Ӧ�ĵ���Patch�����¸߶ȡ�
		//����ӿڴ����ĸ�������һ�����ε�X�������Сֵ��X��������ֵ��Y�������Сֵ��Y��������ֵ������������Ϊ��λ.������ʵ�ʵ��εĴ�СΪ��λ
		virtual	void					AddHeightMapDirtyRect(int left,int right,int top,int bottom) = 0;

		virtual	void					SetHeight(int x,int y,float fHeight) = 0;

		virtual	void					ShowWireFrame(bool b) = 0;

		virtual	void					SetLightMap(ITexture *pTexture) = 0;

		virtual bool					GetTriangleInfo(const float* pDir,const float* pPos,float* pVertexBuffer,int &row,int &col,int &ind1,int &ind2,int &ind3)=0;
		//����ĳ��PATCH��ĳ����ͼid
		virtual bool					SetPatchTexture(int iPatchIndex,int iTextureLayer,unsigned int nID) = 0;
		//�õ�ĳ��PATCH��ĳ����ͼid
		virtual unsigned int 			GetPatchTexture(int iPatchIndex,int iTextureLayer) = 0;
		//������ڲ���ͼ�б������һ����ͼ
		virtual bool					AddTextureToList(unsigned int nId,ITexture *pTex,float fUVTilingX,float fUVTilingY,float offsetX,float offsetY) = 0;

		virtual	bool					DeleteTextureFromList(unsigned int nId) = 0;

		virtual bool					UpdateTextureInList(unsigned int nId,ITexture *pTex,float fUVTilingX,float fUVTilingY,float offsetX,float offsetY) = 0;

		//�õ������ڲ���ͼ�б������һ����ͼ��Ϣ
		virtual ITexture				*GetTextureInfo(unsigned int nId,float& UVTilingXRet, float& pUVTilingYRet,float& pOffsetXRet, float& pOffsetYRet) = 0;
		//����AlphaMap�к�ͨ���Ĳ����ȷ���յ�ͨ��
		virtual void					GetAlphaLayerDifferen(int iPatchIndex,int &iTextureLayer0,int &iTextureLayer1,int &iTextureLayer2,int &iTextureLayer3,int &iTextureLayer4) = 0;

		virtual int						GetPatchTexNum(int iPatchIndex) = 0;

		//����һ��Patch����ͼ����
		virtual void					SetPatchTexNum(int iPatchIndex,int iTextureLayernum) = 0;
		//AlphaMap�Ľӿ�
		virtual unsigned int			*GetAlphaMap() = 0;

		virtual	void					AddAlphaMapDirtyRect(int left,int right,int top,int bottom) = 0;

		//һ����ռ���ٸ�AlphaMapP����
		virtual	void					SetAlphaMapPrecision(int precision) = 0;

		virtual	int						GetAlphaMapPrecision() = 0;

		virtual void					UpdateNormal() = 0;	


		//����ĳ��PATCH��AlphaMap
		virtual void					SetPatchAlphaMapPrecision(int iPatchIndex,int intprecision) = 0;
		virtual int						GetPatchAlphaMapPrecision(int iPatchInde) = 0;

		virtual unsigned int*			GetGlobalMap(int iPatchIndex,int intprecision) = 0;
		virtual	void					AddGlobalMapDirtyRect(int left,int right,int top,int bottom) = 0;


		//�õ��ݵطֲ����ݵ��ڴ�ָ��
		virtual unsigned short*			GetGrassMap() = 0;
		//�޸ĺ��趨�޸ķ�Χ
		virtual	void					AddGrassMapDirtyRect(int left,int right,int top,int bottom) = 0;

		//�ݴӵĽ�����Ϣ
		virtual void	SetGrassFadeOut(float fFadeOutStart,float fFadeOutEnd) = 0;
		//��òݴӵĽ�����Ϣ
		virtual void	GetGrassFadeOut(float& fFadeOutStart,float& fFadeOutEnd) = 0;

		//��õ�ǰ֡�Ĳݴ���Ⱦ��Ϣ,���ƵĴ����Ͳݵ�����
		virtual void	GetGrassRenderInfo(int &nDrawTimes, int &numGrass) = 0;

		virtual void					SetOutDoorEnvInfo(const H3DI::OutDoorEnvInfo& info) = 0;
		virtual void					GetOutDoorEnvInfo(H3DI::OutDoorEnvInfo* info) = 0;

	};

	class IInDoor:public IMoveObject
	{
	public:
		//��������ļ�
		virtual bool					Load(const char* sTerrainFileName)=0;
		virtual bool					TurnOff()=0;
		//Culling
		virtual void					Update()=0;
		//����
		virtual unsigned int			Render()=0;
		virtual int 					RenderRect(const float* pAABB,float s0,float t0,float s1,float t1,IShader* pShader,const float* vec4Color,float fRotation)=0;
		//����MATRIX�õ�CAMERA��Ϣ��δʵ��03-12-3)
		virtual void					SetCurrentCamera(const float* pViewMatrix,const float* pProjectMatrix)=0;
		//����λ�úͽǶȵõ�CAMERA��Ϣ��δʵ��03-12-3)
		virtual void					SetCurrentCamera(const float* vecEyePos,float fov,float ratio,float near, float far)=0;
		//����IRENDER�е�ǰ��CAMERA�����ó���CULLING CAMERA���Ƽ�ʹ��
		virtual void					SetCurrentCamera(IRender* pRenderer)=0;
		//���β��ı�һ�㲻�õ���
		virtual void					ReCaculateAABB()=0;
		//!!!!!! ISceneSearch must be Released by CLIENT !!!!!!
		//use aabb to search
		//ʹ��AABB����
		virtual void					ReCaculateBuffer()=0;
		virtual ISceneSearch*			FindObjects(const float* pAABB,const int* pLayers,int numLayer)=0;
		//ʹ��AABB��X��Yƽ����������������Z��Χ
		virtual ISceneSearch*			FindObjects2D(const float* pAABB,const int* pLayers,int numLayer)=0;
		//use IRender's camera to search
		virtual ISceneSearch*			FindObjects(IRender* pRenderer,const int* pLayers,int numLayer)=0;
		//��׶�����������ڸ���RENDER TO IMAGE����Ч�У���SPOT LIGHTING����Ҫ
		//virtual ISceneSearch			FindObjects(tClipPlanes[5],const int* pLayers,int numLayer)=0


		virtual float					GetHeight(float x, float y)=0;
		//��UN FINISHED 03-12-3��
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
	��ʾģʽ����
	*/
	enum
	{
		DEVMODE_DYNAMIC  ,//��ȫ��
		DEVMODE_TEST ,
		DEVMODE_FULLSCREEN ,//ȫ��
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
	���������ĻBUFFER��־
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
		PIPE_COMMON=0,//��͸������,����ȫ�ֹ���
		PIPE_TRANSPARENT,//͸������
		PIPE_LOCAL_LIGHT,//��̬����
		PIPE_LOCAL_LIGHT_TRANSPARENT,//͸������Ķ�̬��Դ����
		PIPE_PROJECT_SHADOW,
		PIPE_IMAGE_SHADOW,//Hardware Shadowmap
		PIPE_GLOW,
		PIPE_UNKNOWN,
		PIPE_MAX_NUMBER,
	};

	///��Ӱ������ʵ��
	enum SHADOWMAP_TECHNIQUE
	{
		SM_NONE=0,					//����Ӱ
		SM_POINT_DEFAULT,			//��ԭʼ�ĵ��Դʵ��
		SM_POINT_PSM,				//͸����Ӱ��ͼ
		SM_DIR_CASCADED,			//������ƽ�зָ��Ӱ��ͼ
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
		PIPE_ENABLE_SIMPLE_DRAWING = 1<<17,//ֻʹ��PIPE�Լ���SHADER���򵥻���SUBMODEL�������
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
		FILENAME_ERROR, //�ļ���Ϊ��
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

	//ͼƬ������
	class IImage
	{
	public:
		/*�õ�image����Ϣ��������С
		//filename:�ļ���
		//imagemode:�ļ����ͣ�jpg,bmp,tga�ȵ�
		//w,h ���������ĳ���
		//infobufferlen ԭʼ���ݵĳ���(raw data)
		//jpgbuferlen ת��Ϊjpg�����ݵĳ���

		������ʵ�����Ѿ���ͼ������ڴ棬����ͨ���ݴ�Jpg�����̵ķ������jpgͼ��Ĵ�С
		*/
		virtual IMAGE_ERROR get_image_info(const char* filename, unsigned int& w, unsigned  int& h, long& jpgbuferlen)=0;

		/*����ͼ��
		//tranmode���������ͣ�Ŀǰֻ������һ��
		//orgw,orghԭʼ���ݵĳ���
		//desw,deshҪ���ŵ��ĳ���
		//bufferԭʼRaw Data������
		//desbuffer�任�����ݴ�ŵ��ڴ�
		//deslengthΪdesbuffer�ڴ�ĳ���

		ע�⣺��������ʹ�õ������Լ���õ����ݶ���RawData��RawData���ݳ��ȼ���Ĺ���Ϊ��
		�ֽ���=	��*��*4 (4��ʾRGBA �ĸ�����)
		*/
		virtual IMAGE_ERROR tranform_image(IMAGE_OPERAT tranmode,unsigned int orgw,unsigned int orgh,unsigned int& desw, unsigned int& desh, unsigned char* buffer, unsigned char* desbuffer, unsigned int deslength)=0;

		/*��ȡͼ������ԭʼ
		filenameΪ�����ϵ�ͼ���ļ��������ļ�������ʹ���get_image_info�������ļ�����ͬ�������ܻ��ͼ������
		bufferΪ����RAW DATA���ڴ�
		lengthΪ�ڴ�ĳ��ȣ�����ͨ�����ϸ����Ĺ�ʽ����
		*/
		virtual IMAGE_ERROR get_raw_data(const char* filename,unsigned char* buffer,unsigned int length)=0;

		/*
		��ȡѹ���������
		filenameΪ�����ϵ�ͼ���ļ��������ļ�������ʹ���get_image_info�������ļ�����ͬ�������ܻ��ͼ������
		compressTypeΪѹ�����ͣ�Ŀǰֻ֧��jpg
		bufferΪ����RAW DATA���ڴ�
		lengthΪ�ڴ�ĳ��ȣ�����ͨ�����ϸ����Ĺ�ʽ����
		*/
		virtual IMAGE_ERROR get_compress_data(const char* filename,COMPRESS_TYPE compressType,unsigned char* buffer,unsigned int length)=0;

		/*
		��ѹ����ʽ��RawData��ת��
		compressTypeѹ������
		compressBuffer ѹ���ļ�������
		compressBufferLenѹ���ļ����ݵĳ���
		rawDataBufferԭʼ���ݵ��ڴ�
		rawWidth,rawHeight ԭʼ���ݵĳ���
		*/
		virtual IMAGE_ERROR compressData2RawData(COMPRESS_TYPE compressType,const unsigned char* compressBuffer,unsigned int compressBufferLen,unsigned char* rawDataBuffer,unsigned int& rawWidth,unsigned int& rawHeight,long MaxRawBufferLen)=0;

		/*
		��RawData�� ѹ����ʽ��ת��
		compressTypeѹ������
		compressBuffer ѹ���ļ�������
		MaxCompressBufferLen ѹ��������󳤶ȣ���������˳��ȣ��᷵��BUFFER_SIZE_ERROR,ѹ����Ϻ���޸Ĵ˱���Ϊbuffer��ʵ�ʳ���
		rawWidth/ rawHeight ѹ���ļ����ݵĳ���
		rawDataBufferԭʼ���ݵ��ڴ�
		rawBufferLen ԭʼ���ݵĳ��ȣ�����ʹ����������Ĺ�ʽ����
		*/
		virtual IMAGE_ERROR RawData2CompressData(COMPRESS_TYPE compressType,const unsigned char* rawDataBuffer,unsigned int rawWidth,unsigned int rawHeight,unsigned char* compressBuffer,long& MaxCompressBufferLen)=0;


		virtual IMAGE_ERROR SaveRaWToFile(const char* filename,const unsigned char* data,unsigned int width,unsigned int height)=0;
		/*
		�õ�Ŀǰ�ڴ��е�ͼ���Ƕ�Ӧ�ĸ������ļ�
		*/
		virtual const char* GetCurrentFileName()=0;
		virtual IMAGE_ERROR loadImage(tImgProcessParam* ImgProcessParam)=0;
		virtual IMAGE_ERROR saveImage(tImgProcessParam* ImgProcessParam)=0;
		virtual IMAGE_ERROR processImage(tImgProcessParam* tmgProcessParam,tImgProcessParam* ImgProcessParam2=0)=0;


	};
	//add by liren 2010-8-25
	//!����
	class IPostProcessEffect : public IObject
	{
	public:
		//!���һ���׶�
		virtual void AddPhase(const char * pFileName) = 0;
		//!ɾ��һ���׶�
		virtual void DelPhase(const char * pFileName) = 0;
		//!����
		virtual void LinkEffect() = 0;
		//!���ò���
		virtual void SetParamValue(const char * pName,void* pValue) = 0;
		//!�ж�һ���׶��Ƿ����
		virtual bool HasPhase(const char *) = 0;
	};

	//nIOFlags ��־IO���ͣ�Ŀǰֻ��2�֣���ͨ����ͬ������������ͬ��
	enum
	{
		IO_SYC=0,
		IO_URGENT_SYC,
	};

	//!��������
	enum EPhySceneType
	{
		//!����
		SCENE_CLOTH = 0,
		//!ǰ��
		SCENE_FRONT,
		//!���
		SCENE_BASE
	}; 

	//!��ײ������
	enum ECollisionPlaneType
	{
		//!OBB
		COLLISIONPLANE_OBB = 0,
		//!��������
		COLLISIONPLANE_TRIANGLEMESH,
		//!��̬����,����?
		COLLISIONPLANE_STATIC
	};

	//!OBB��ײ��Ϣ
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

		//!��ײ����ID
		unsigned int name;
		//!OBB����
		float	 worldMat[16];
		//!���ٶ�
		float	 lineVelocity[3];
		//!���ٶ�
		float	 angVelocity[3];
		//!��¼ԭʼ����
		float	 back_left_bottom[3];
		float	 front_right_top[3];
		//!�Ƿ���Ҫ�ı�OBB��С
		bool		 bUpdateSize;
		//!ʱ��,���ڼ��㵱ǰλ��
		float    deltaTime;
		//!������ײ����ID�б�����������б��е����岻����OBB�������ײ
		unsigned int invalidObjects[10000];
		int invalidNums;
		//!������ײ����
		int unCollisionTypes[1024];
		int unCollisionTypeNums;
	};

	//!��̬������Ϣ
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

		//!��̬����ID
		unsigned int name;
		//!��������
		H3DVec3* vertexs;
		//!�������
		int		 max_vertex;
		//!����������
		int*	faces;
		//!����Ŀ
		int      max_face;
	};

	//��ײ��ṹ
	struct tContactPoint
	{
		//��ײ��
		float point[3];
		//��ײ������������
		unsigned int planeType;
		//������
		int     faceIdx;
		//�淨��
		float collNormal[3];
	};

	struct tCollisionResultInfo
	{
		tCollisionResultInfo()
		{
			collPointNums = 0;
			collisionPoints = 0;
		}
		//��ײ������
		int		 collPointNums;
		//��ײ��
		tContactPoint* collisionPoints;
		//�����ײ������
		static const int maxCollisionPointsNum = 1024;
	};

	//��ͷ�����
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
	
	//���������
	enum ECameraType
	{
		ECT_Render = 0,
		ECT_Culling = 1
	};

	//����ʹ���ߣ�ĳЩ��Ա༭����������Ҫ��ʾ����IRender::SetUser�ӿ�
	enum EngineUserDefine
	{
		EUD_UNKONWN=0,
		EUD_CLIENT,
		EUD_EDITOR
	};

	//INFO����ö��
	enum InfoType
	{
		NONE_INFO		=0,   
		MODEL_INFO			,/// ģ��
		ACTOR_INFO			,/// ��ɫ
		TEXTURE_INFO		,/// ��ͼ
		MATINS_INFO			,/// ����ʵ��
		LPPLIGHT_INFO		,/// �ƹ�
		EFFECT_INFO			,/// ��Ч
		RENDERTARGET_INFO	,/// renderTarget
		POSTEFFECT_INFO		,/// ����
		BEAM_INFO			,/// ����
		RENDER_INFO			,/// ��Ⱦ 
		GENFX_INFO			,/// ����fx
		CLOTH_INFO			,//	 ����
		LOGTYPENUM
	};
	//���������
	enum ErrorType
	{
		WARNING_ERROR = 0,
		CRITICAL_ERROR,
		LOGERRNUM
	};
	//���Ŀ��
	enum OutPutFlag
	{
		OutPut_File			= 1<<0,
		OutPut_Console		= 1<<1,
		OutPut_RenderWindow = 1<<2
	};

	//!IO�߳�Taskִ��״̬��أ���������ʹ��
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

		///����������
		virtual int						CreateRenderWindow(const tWindowCreateInfoImp& info)=0;
		///�������Ӵ���
		virtual int						CreateAddionalRenderWindow(HWND hwnd,int w,int h)=0;

		///���õ�ǰ�����Ⱦ���ڵ�ID������ֵС��0��ʾʧ�ܡ��ú����������Ƕര����Ⱦ��ʱ��ָ���������Ļ��� �ǻ��Ƶ��ĸ�������
		virtual int						SetCurrentRenderWindow(int windowID)=0;

		virtual void					GetCurrentWindowSetting(tWindowCreateInfoImp& info)=0;

		virtual bool					InitRenderWindow(const tWindowCreateInfoImp& info)=0;

		virtual void					SetWindowResource(void* pWindowHandle,void* pDisplayContextHandle,void* pOther)=0;

		virtual void					ChangeDisplaySetting(const tWindowCreateInfoImp& info)=0;
		virtual bool					GetCurrentWindowMode()=0;

		///�������ţ����һ�������Ǵ��ڵ�ID,Ĭ�ϵ�-1��ʾ��������
		virtual bool					ResizeWindowForEditor(int w,int h,int windowID=-1)=0;
		virtual bool					ResizeWidnowEx(int w,int h,bool windowed,bool topmost,bool popup,bool maxbox,bool pad_win_frame_size=true,int windowID=-1)=0;

		///sssa2000 08.04.03  !ǿ���豸lost������vista��
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
		/// ���ó�����������ɫ
		virtual void					SetAmbientColor(const float *col)=0;
		/// ���ý�ɫ��������ɫ			
		virtual void					SetActorAmbientColor(const float *col)=0;
		virtual void					SetWireMode(bool bWire)=0;
		virtual void					UpdateCamera()=0;
		//!����������
		virtual bool				    CreatePhyWorld(int& outId)=0;
		//!����OBB
		virtual bool					CreateObbCollisionData(unsigned int name,IMoveObject* pModel,int phyId)=0;
		//!����triangleMesh,�����Ƕ�ȡ�������ײ�������
		virtual bool					CreateTriangleMesh(unsigned int name,const H3DVec3* points,const unsigned short* indexs,const H3DVec3* normals,int vertexNums,int triNums,int phyId)=0;
		//!����ASE��ʽ��triangleMesh���ڴ���������.��Ҫע����Ǹýӿ���Ҫ����2��,1�δ�����С,1����д����.��������ڴ�ָ����0ʱ��д��С
		virtual bool					LoadTriangleMesh(const char* aseName,int& vertexNums,int& triNums,H3DVec3* points,unsigned short* indexs,H3DVec3* normals)=0;
		//!�ͷ���ײ����
		virtual void					ReleaseCollisionData(unsigned int name,int phyId)=0;
		//!�ͷ���������
		virtual void					ReleaseCollisionScene(int phyId) = 0;
		//!������ײ����
		virtual void					SetCollisionData(const tCollisionObbInfo& obbInfo,int phyId)=0;
		//!������������
		virtual void					UpdatePhx(int phyId,unsigned int interval)=0;//��������������ⲿ����
		//!�Ͻӿ�
		virtual void					UpdatePhx(unsigned int interval=0)=0;//��������������ⲿ����
		//!�����������������,������Сʱ��Ƭ,ģ��ʱ��(Ϊ��ֵ��ʾȡʵ�ʵ���Ⱦʱ��,Ϊ��ֵ��ʾ�㶨ģ��ʱ��Ƭ,����ֵ
		virtual void					SetPhxPara(float fixedTime,float simTime,float gravity)=0;
		//!��ȡ��ײ���,����һ������ID,��������ID,���غ��䷢����ײ������ID,����,��ײ��,��ײ��,��ײ���ߵ���Ϣ
		virtual bool					GetCollisionResult(int phyId,unsigned int& collName0,int& collType0,unsigned int& collName1,int& collType1,tCollisionResultInfo& collInfo)=0;
		
		//!��ĳָ����������߲�ѯ.phxWorldId:��������id,objId:����ѯ������ID.����1��ʾ��ѯ�ɹ�,0��ʾ��ѯʧ��
		//Ŀǰֻ֧�ֺ��������͵���ײ�����ѯ
		virtual int						RayTestSingObject(float x,float y,H3DVec3& collRes,unsigned int phxWorldId,unsigned int objId) = 0;
		
		//by sssa2000 08.04.08
		virtual void SetEnableAllPhy(bool b)=0;
		virtual bool GetEnableAllPhy()=0;
		//by lzp,�ͷŵ���������
		virtual void ReleasePhxScene()=0;
		//��ȡ��Ƭ����,����һ���㹻����ڴ�,����ʵ�����Ĵ�С,idBufferSize��ʾ����Ԫ�ظ���
		virtual bool GetPhxWorldCopyInfo(int phyId,unsigned int* pIdBuffer,unsigned int idBufferSize,unsigned int& idRealSize,char* pBuffer,unsigned int bufferSize,unsigned int& realSize) const= 0;
		//������Ƭ����,��������Buffer,buffer��С.idBufferSize��ʾ����Ԫ�ظ���
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
		//����2��������Ϊ�˸���������ӵģ����д����ָ������Ƿ���ÿռ�ģ��Ҳ�С��8������,�������ָ����ֵ���Ƶ�������
		//�ɹ���������ǰ4��Ϊ near,��4��Ϊfar ƽ��
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

		//���ⲿ�ļ�����һ������
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
		//���еĲ������ø����ε�ȫ�ֹ���

		virtual IBillboard*				CreateBillboard(BILLBOARD_TYPE type,BILLBOARD_PROPERTY property)=0;



		//////////////////////////////////////////////////////////////////////////
		//Pipe Functions
		virtual void					PushModel(IModel* pModel)=0;
		//��������CBillboard,CUserObject
		virtual void					PushMoveObject(IMoveObject* pMoveObj)=0;
		virtual void					PushNewPipe(PIPE_TYPE type,unsigned int flags,ILight* pLight, PipeSettingFunc pStartFunc=0,PipeSettingFunc pEndFunc=0)=0;
		virtual void					ProcessCurrentPipe()=0;//�����������������Ȳ���,���йܵ�����Ҫ�˲���
		virtual unsigned int			RenderPushedPipes()=0;//�����Ѿ�ѹ�������PIPE 
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
		ĳЩ�Կ�ֻ֧��16bit����������, Ϊ�˼��ٴ����ϵ��鷳, �ͻ��˵�����bufferͳһʹ��unsigned short��ʽ
		*/
		virtual void					DrawIndex(PRIMITIVE_TYPE nTriangleType,unsigned int nElemNum,unsigned int nVertNum,unsigned int nNormalOffset,
			unsigned int nTexcoordOffset,unsigned int nColorOffset,unsigned int nTexcoordOffset2,void* pVBuffer,unsigned short* pEBuffer)=0;


		//-----------------�첽IO�ӿ�------------------------

		// �첽����һ��ģ�ͣ���������id
		// lod��lod����
		// nPriority���������ȼ�
		virtual unsigned int		CreateModelAsyn(const char* sFileName, sCreateOp& lod, int nPriority)=0;

		virtual unsigned int		CreateSpeAsyn(const char* sFileName, sCreateOp& lod, int nPriority) = 0;

		virtual unsigned int		CreateTextureFromFileAsyn(const char* filename, unsigned int numMips=0) = 0;

		virtual unsigned int		CreateNewShaderAsyn(const char* filename, const char* matName, int nPriority)=0;

		virtual unsigned int		LoadActionAsyn(const char* actName, H3DI::EActorType actorType, bool bMale, int nPriority)=0;


		// ��ȡ�첽�����Ķ���Ľӿ�
		virtual H3DI::IMoveObject*	GetModelAndFinishTask(unsigned int taskId) = 0;

		virtual H3DI::INewShader*	GetNewShaderAndFinishTask(unsigned int taskId)=0;

		virtual H3DI::ITexture*		GetTextureAndFinishTask(unsigned int taskId)=0;


		// ������Դ���첽�ӿ�

		// �첽����actor bodypart
		virtual unsigned int	LoadBodypartAsyn(const char* fileName, EActorType actorType, sCreateOp& lod, int nPriority) = 0;

		virtual unsigned int	LoadAdornmentAsyn(const char* adornmentname, sCreateOp& lod, int nPriority) = 0;

		virtual unsigned int	LoadMaterialLodAsyn(IMoveObject* pModel, int nLod, int nPriority)=0;

		// ����ִ���첽����ֱ��ĳ���������
		// taskId ��ֱ����ɵ�����id�����Դ�0��������ֱ����ǰ��������������������
		virtual int		DoTaskImmediately(unsigned int taskId) = 0;

		virtual int		GetWaitingTaskCount() = 0;

		virtual int		CancelTask(unsigned int taskId) = 0;

		virtual int		QueryTaskState(unsigned int taskId) = 0;

		// ��ѯ��ǰ��������״̬
		// idBuffer �������id��buffer,����ΪNULL����ʱ������������
		// stateBuffer �������״̬��buffer,����ΪNULL����ʱ������������
		// nBufferSize idBuffer��stateBuffer�Ĵ�С��intΪ��λ������ֵС�ڵ�ǰ����������ʱ���ú�������������
		// ����ֵ����䵽buffer�еĽ������,Ҳ���ǵ�ǰ����������
		virtual int		QueryAllTaskState(unsigned int * idBuffer, int* stateBuffer, int nBufferSize) = 0;

		virtual void	UpdateEngineThread() = 0;	

		//!IO�߳�Taskִ��״̬��أ���������ʹ��
		virtual void	SetProcessIOLisenter(ProcessIOLisenter* lisenter) = 0;

		//--------------------------------------------------

		//!�õ���ǰ�ؿ�,����
		virtual ILevel* GetLevel(void)const = 0;
		//!�������
		virtual ICamera* CreateCamera(void) = 0;
		//!������Ⱦ���
		virtual void SetRenderCamera(ICamera* pCam) = 0;
		//!�õ���Ⱦ���
		virtual H3DI::ICamera* GetRenderCamera(void)const = 0;
		//!����culling���
		virtual void SetCullingCamera(ICamera* pCam) = 0;
		//!�õ�culling���
		virtual H3DI::ICamera* GetCullingCamera(void)const = 0;
		//!��AABB
		virtual void DrawAABB(const float* aabb, const float* color, float lineWidth)const = 0;
		//!���߶�
		virtual void DrawSegment(const H3DVec3& begin, const H3DVec3& end, const float* color, float lineWidth)const = 0;

		//!��������VB
		virtual IParticleVB* CreateParticleVB(void) = 0;
		//!pushһ�����ӽ�����Ⱦ
		virtual void PushParticle(H3DI::IMoveObject* pObj) = 0;

		//!��һ��������
		virtual bool                    OpenActionLib(const char* fileName)const = 0;
		//!��ȡһ�������ļ�
		virtual bool                    LoadAction(const char* actName, H3DI::EActorType actorType, bool bMale) = 0;
		//!�ͷ�һ������
		virtual bool                    ClearAction(const char* actName, H3DI::EActorType actorType, bool bMale) = 0;
		//!���һ�������Ƿ��Ѵ���
		virtual bool                    IsActionExist(const char* actName, H3DI::EActorType actorType, bool bMale) = 0;
		//!��ȡ�ؿ��ļ�
		virtual ILevel*                 LoadLevel(const char* fileName) = 0;
		//!pushһ���ؿ�������Ⱦ
		virtual void                    PushLevel(ILevel* p) = 0;
		//!��Ⱦ�ؿ�����Ӱ
		virtual void                    RenderLevelShadowMap(ILevel*) = 0;
		//!ִ������,����չ�ӿ�
		virtual void					Exec(unsigned int code, const char* argument, unsigned int argumentLength, char* buffer, unsigned int bufferLength) = 0;
		//!��ѯ�ӿ�
		virtual void*					QueryInfo(int QueryCode,void* param1,void* param2,void* param3,void* param4,void* param5)=0;
		//!�����Ƿ�ʹ�ö�����,IRender��ʼ����ʱ�����һ�μ���,Ĭ��Ϊ��ʹ��
		virtual void					SetUseActionLib(bool val) = 0;
		//!�Ƿ�ʹ�ö�����
		virtual bool					UseActionLib(void)const = 0;
		//!�����Ƿ�ϲ�Actor��Bodypart��ͼ,IRender��ʼ����ʱ�����һ�μ���,Ĭ��Ϊ��ʹ��
		virtual void                    SetMergBodyPart(bool val) = 0;
		//!�Ƿ�ϲ�bodypart
		virtual bool                    MergBodyPart(void)const = 0;
		//!����SkeletonModel��ʵ���Ƿ�ʹ�ö�춯��,Ĭ��Ϊ��ʹ��
		virtual void                    SetUseActionChannel(bool val) = 0;
		//!SkeletonModel��ʵ���Ƿ�ʹ�ö�춯��
		virtual bool                    UseActionChannel(void)const = 0;
		//!�ڶ�����ģʽ��,��ȡһ�鶯��
		virtual void                    PreLoadActions(const char** actNames, unsigned int actCount, ISkeletonModel* pSKL) = 0;
		//!�ڶ�����ģʽ��,���ǰ������������ж��������bOnlyClearUnUsedΪtrue��ֻ�����δʹ�õĶ�����
		virtual void                     ClearAllActions(bool bOnlyClearUnUsed = true) = 0;
		//!���¶�ȡ�������е�һ������(��ԭ�����ļ���)
		virtual bool                     ReloadAction(const char* actName, ISkeletonModel* pSKL) = 0;

		//!�����Ƿ�������ģ��
		virtual void                     SetUseCloth(bool val) = 0;
		//!�Ƿ�������ģ��
		virtual bool                     UseCloth(void)const = 0;
		//!�����Ƿ�����ʹ���������б�
		virtual void                     SetUseTriList(bool val) = 0;
		//!�Ƿ�����ʹ���������б�
		virtual bool                     GetUseTriList(void)const = 0;


		//!������ͼ���Ų���
		virtual void                     SetImageScaleFactor(unsigned int) = 0;
		//!�õ���ͼ���Ų���
		virtual unsigned int          GetImageScaleFactor(void)const = 0;
		//!������õ���ͼ,shader����Դ
		virtual unsigned int          ClearMaterialLib(void) = 0;
		//!�õ�״̬������
		virtual const IEngineMonitor*    GetEngineMonitor(void)const = 0; 
		//!�����Ƿ����ȶ�ȡ������
		virtual void					  SetFavorBinary(bool val) = 0;
		//!�Ƿ����ȶ�ȡ������
		virtual bool                      FavorBinary(void)const = 0;
		//!�õ�����ʱģʽ
		virtual ERuntimeMode       GetRuntimeMode(void)const = 0;
		//!push�������
		virtual void					  PushViewMatrix(void)const = 0;
		//!pop�������
		virtual void                      PopViewMatrix(void)const = 0;
		//!pushͶӰ����
		virtual void                      PushProjectionMatrix(void)const = 0;
		//!popͶӰ����
		virtual void                      PopProjectionMatrix(void)const = 0;
		//!�õ���Ⱦ״̬������
		virtual const IRenderStateManager* GetRenderStateManager(void)const = 0;
		//!����һ����ͼ
		/**
		client������texture����RT��,Ҫִ��addref����,�����������ڴ��ʱ����ܻ�������ͼɾ��
		����ǰ,Ҫ��ִ��delref,��ִ��release
		���µ�һ�������Ǵ���һ��ָ����С��texture���ڶ�����ͨ�������ļ�����һ��texture,�ڶ���������ʾmipmap�ĵȼ� 0��ʾ�Զ�����
		*/
		virtual ITexture*               CreateTexture(unsigned int& width, unsigned int& height, ETextureFormat fmt, bool mipmap) = 0;
		virtual ITexture*               CreateTextureFromFile(const char* filename, unsigned int numMips=0) = 0;
		//!����һ��RT
		virtual IRenderTarget*      CreateRenderTarget(unsigned int& width, unsigned int& height, ETextureFormat fmt, ERenderTargetType type) = 0;
		//!�����Ƿ���ͼѹ����DXT��ʽ
		virtual void                      SetCompressTexture(bool res)const = 0;
		//!�Ƿ���ͼѹ����DXT��ʽ
		virtual bool                      CompressTexture(void)const = 0;
		//!�õ�ƽ��ͶӰ����
		virtual void                       GetOrthoProjectionMatrix(float left, float right, float bottom, float top, float near, float far, H3DMat4& out)const = 0;
		//!�޸ĵ�ǰview����
		virtual void                       TranslateViewMatrix(float x, float y, float z)const = 0;
		//!��ת��ǰview����
		virtual void                       RotateViewMatrix(float degree, float x, float y, float z)const = 0;
		//!�õ���Ļ����ϵ�µ�����
		virtual void                       GetScreenPos(const H3DVec3& objPos, const H3DMat4& worldViewMat, const H3DMat4& projMat, 
			unsigned int x, unsigned int y, unsigned int width, unsigned height, 
			float minZ, float maxZ, H3DVec3& screenPos)const = 0;
		//!������ͼ����
		virtual void                        SetTextureParams(bool scale, bool compress, bool mipmap)const = 0;
		//!�õ���ͼ����
		virtual void                        GetTextureParams(bool& scale, bool& compress, bool& mipmap)const = 0;
		//!����ȫ��������ģʽ
		virtual void						ToWindowedMode()=0;
		virtual void						ToFullScreenMode()=0;
		//!����ȫ�������ģʽ
		virtual void                         SetAAMode(EAAMode aa) = 0;
		//!�õ�ȫ�������ģʽ
		virtual EAAMode              GetAAMode(void)const = 0;
		//!�õ�֧�ֵĿ��������
		virtual unsigned int           GetSupportedAAMode(void)const = 0;
		//!���ø������Թ���ģʽ
		virtual void                          SetAFMode(EAFMode) = 0;
		//!�õ��������Թ���ģʽ
		virtual EAFMode               GetAFMode(void)const = 0;
		//!�õ�֧�ֵĸ������Թ���ģʽ
		virtual unsigned int           GetSupportedAFMode(void)const = 0;
		//!�����Ƿ�����ֱͬ��
		virtual void                          SetVSync(bool val) = 0;
		//!�Ƿ�����ֱͬ��
		virtual bool                          GetVSync(void)const = 0;
		//!������Ӱģʽ
		virtual void                          SetShadowQuality(EShadowQuality q) = 0;
		//!�õ���Ӱģʽ
		virtual EShadowQuality    GetShadowQuality(void)const = 0;
		//!�����Ƿ�������
		virtual void                          EnableCloth(bool val) = 0;
		//!�Ƿ�������
		virtual bool                          ClothEnabled(void)const = 0;
		//!������ʾ����
		virtual void                         ApplyVideoSettings(void) = 0;
		virtual void						 ApplyVideoSettings2(void) = 0;
		//!�õ���ǰ�ķֱ���
		virtual void						 GetCurrentReslution(int& w,int& h)=0;
		//!�õ�profile����
		virtual void                         GetPerfData(tPerfData& data)const = 0;
		//!��������
		virtual void                         SetGravity(const H3DVec3& g) = 0;
		//!�õ�����
		virtual const H3DVec3&      GetGravity(void)const = 0;
		//!�����¼�������
		virtual void                          SetEventHandler(IEngineEventHandler* pHandler) = 0;
		//!�õ��¼�������
		virtual IEngineEventHandler* GetEventHandler(void)const = 0;

		//!ץ��
		virtual bool SaveScreenToFile(const char* )=0;
		//����IImage
		virtual IImage* GetImageInterface(void)=0;

		virtual IPerfMonitor* GetPerfMonitor()=0;

		//by sssa2000 090330
		//Ϊ�༭����ӵ��½ӿ�
		virtual void beginWireFrameDraw()=0;
		virtual void endWireFrameDraw()=0;
		virtual void drawPhy()=0;
		//add by liren
		//�����η������
		virtual void PushTerrain(H3DI::ITerrain *pTerrain) = 0;
		//!add by liren

		//add by liren
		//�ڵ����ϴ���һ����Ƭ
		virtual	IModel*			GenerateSmallPatch(float length,float width,ITerrain *pTerrain) = 0;
		//!add by liren
		//Ӳ��ѡ��
		//����Ӳ��ѡ�񣬴���һ����Ļ���Σ���ѡ��ʽ,
		virtual	bool			BeginHardwareSelect(const int *pRect,bool bSelectFirst, int WindowID) = 0;
		//����һ���������Ե�ID
		virtual void			PushHardwareSelectObject(IMoveObject *pobject,unsigned int nId) = 0;
		//���������ѡ��
		virtual	void			ProcessMoveObjectSelect() = 0;
		//!ѹ��һ��Id���������Զ��嶥�㣬�ߺ�VB��
		virtual void			PushSelectID(int ID) = 0;
		//!����
		virtual int				GetSelectID(void)const = 0;
		//����ѡ�񣬷��ؽ��
		virtual	int				EndHardwareSelect(unsigned int *pRetIds,int num) = 0;
		//!���þ�ͷ���β���
		virtual void			SetLensParameters(const tLensEnv& lenEnv,const tLensFlareParameters* lensPara,unsigned int nums) = 0;
		//!����̫���߶�,Ĭ��֧��һ��̫��
		virtual void			SetSunHeight(float height)=0;
		//!����̫��λ��,�༭����
		virtual void			SetSunPos(const H3DVec3& pos)=0;
		//!��ȡ̫��λ��,�༭��debug��
		virtual void			GetSunPos(H3DVec3& pos)=0;

		//��(����Ⱦϵͳ)
		virtual H3DI::IFog*					CreateFog() = 0;
		//����ȫ����Ŀǰȫ������Ҫ������
		virtual void SetGlobalFog(float r,float g,float b,float density,float start,float fogmin)=0;
		//����������ͼ
		virtual int ReloadTexture(const char* filename)=0;

		//������ؽӿ�
		//���ɾ������Ч���Ľӿ�
		virtual bool					AddPostProcess(const char *FileName) = 0;

		virtual bool					DelPostProcess(const char *FileName) = 0;
		//����
		virtual void					EnablePostProcess(bool bEnable) = 0;
		//���ò���,������Ч�����ɵ��Ĳ���,������ӿ����á�
		//��������Щ������ÿ������ʲô���壬������ĵ��ṩ��
		virtual void					SetPostProcessParams(const char* name,const void *pParmeValue) = 0;

		//���ú���Ӱ��Ĵ��ڡ�
		virtual void					SetPostProcessWindowId(int)=0;
		//��ú���Ӱ��Ĵ��ڡ�
		virtual int						GetPostProcessWindowId()=0;


		//�������ⳡ����ȫ�ֻ���
		virtual void SetOutDoorEnvInfo(const OutDoorEnvInfo& info)=0;
		virtual void GetOutDoorEnvInfo(OutDoorEnvInfo* info)=0;

		//�������ʱ��Ϣ
		virtual void GetRuntimeInfo(IRuntimeInfo* pRes)=0;

		//����ƽ����룬���Χ�������ɢԲ�뾶���ø�����������
		virtual void SetFocalParam(float fFocalplane,float fDOFRange,float fConfusion) = 0;
		//�õ���ƽ����룬���Χ�������ɢԲ�뾶���ø�����������
		virtual void GetFocalParam(float &fFocalplane,float &fDOFRange,float &fConfusion) = 0;


		//�ͻ�����PushCamera��PopCamera�����������������ֱ𽫾������ѹջ�򵯳�ջ��
		virtual void PushFocalParam() = 0;
		virtual void PopFocalParam() = 0;
		//��һ��ģ����ӵ�����ģ��ʵ����
		virtual	void AddSkeletonModelToInstancing(H3DI::ISkeletonModel *pSkeletonModel) = 0;
		//����ģ����ӵ�����ģ��ʵ����
		virtual void ProcessSkinedInstancing() = 0;
		//�õ��������ͼ
		virtual IRenderTarget* GetSceneDepthUsedInPostprocess() = 0;

		//�����Ƿ����ӳٹ��ջ���
		virtual void EnableLightPrePassRendering(bool b)=0;

		//����һ������ʵ���ļ��� �Լ�����������ֵõ�INewShader
		virtual H3DI::INewShader* GetNewShader(const char* filename,const char* matName)=0;
		//�õ��������
		virtual int GetEngineLastError()=0;

		//�õ�������������
		virtual const char* GetErrorDesc(int errCode)=0;

		//���һ������ģ�ͣ�����ģ��ÿ֡���������ã���������þ�û��ģ�ͱ�����
		virtual int AddHighLightModel(const H3DI::IModel* pModel)=0;

		virtual unsigned int GetRenderFrameCount() = 0;

		//���ôα���ɢ����ɫ
		virtual void		SetTransmissionColor(const float* col) = 0;
 		
		//�������þ�������ĺ������òη�ʽ
 		virtual void					SetPostProcessParams1(const char* name,const void *pParmeValue) = 0;

		///��������ʹ����
		virtual void					SetUser(EngineUserDefine u)=0;
		//��ʼDrawIndex
		virtual void					BegineDrawIndex() = 0;

		//����DrawIndex
		virtual void					EndDrawIndex() = 0;

		///��ʼ��ѯ��֡�Դ�����
		virtual void BeginCurrentFrameVideoMemQuery()=0;

		///������ѯ��֡�Դ�����
		virtual unsigned int EndCurrentFrameVideoMemQuery()=0;

		///�����Ƿ���2d���ơ�
		virtual void Set2DMode(bool b)=0;

		///push 2d����
		virtual void Push2DObj(IMoveObject* pMoveObj)=0;

		///Render 2d����
		virtual void Render2DObj()=0;
		//����һ���������
		virtual IPostProcessEffect*		CreatePostProcessEffect()=0;
		//�ͷ�һ���������
		virtual void					ReleasePostProcessEffect(IPostProcessEffect *pIEffect)=0;

		//�õ�Ĭ�ϵĺ������
		virtual IPostProcessEffect*		GetDefaultPostProcessEffect()=0;

		//�õ���ǰ�ĺ������
		virtual IPostProcessEffect*		GetCurrentPostProcessEffect()=0;

		//���õ�ǰ�ĺ������
		virtual void					SetCurrentPostProcessEffect(IPostProcessEffect *pIEffect)=0;
		//�õ���ǰ����
		virtual ITerrain*				GetActiveTerrain() = 0;
		//������Դ�󶨵�������Ƿ����ı�־
		virtual	bool					GetLightShaftEnable() = 0;
		//�������Դ�󶨵�������Ƿ����ı�־
		virtual	void					SetLightShaftEnable(bool bEnable) = 0;
		//// !ʹ���²���ϵͳDraw Index
		virtual void					DrawIndexNew(PRIMITIVE_TYPE nTriangleType,unsigned int nElemNum,unsigned int nVertNum,unsigned int nNormalOffset,unsigned int nTexcoordOffset,unsigned int nColorOffset,unsigned int nTexcoordOffset2)=0;
		///! ������
		virtual int						OnCommandLine(const char* commandLine) = 0;
		//ʹ��Ӳ��ѡ��
		virtual void					SetUseHardWareSelection(bool buse) = 0;
		//��ȡ�Ƿ�ʹ��Ӳ��ѡ��
		virtual bool					UseHardWareSelection() = 0;

		//��ȡȫ�ֵ���������
		virtual void* GetGlobalPerfData(GLOBAL_PERFDATA_TYPE t)=0;

		/// ���ز��ʵĶ���Ч��
		virtual void EnableMaterialAnimation(bool b) = 0;

		// ���õ�ǰ��Ⱦģʽ����ͨ���߿���ͨ+�߿�
		virtual void					SetFillMode(EFILLMODE mode) = 0;
		// �����߿����ɫ
		virtual void					SetWireframeColor(const float* color)  = 0;

		/// ��Ӧ�²���INewShader������/// ����DrawIndex��Ҫʹ�õ�INewShader
		virtual void					SetNewShader(H3DI::INewShader* pShader) = 0;

		///��ʼ���õ�ǰ����Ҫʹ�õĵƹ�
		virtual void BeginSetCurrentLight()=0;

		//���õ�ǰ����Ҫʹ�õĵƹ�
		//t�������⻹�������
		//pLight����Դָ��
		//����ֵ���������-1��ʾ���������涨�����ò��ɹ������ش���0��ֵ��ʾ�ɹ�
		virtual int SetCurrentLight(H3DI::IPrePassLight* pLight)=0;

		///�������õ�ǰ����Ҫʹ�õĵƹ�
		virtual void EndSetCurrentLight()=0;

		///��ȡ��ǰ����Ҫʹ�õĵƹ������
		virtual int GetCurrentLightNum(H3DI::LightAffectParam t)=0;

		//��ʼ��ViewPort�л�����
		virtual void BeginViewPort() = 0;
		//������ViewPort�л�����
		virtual void EndViewPort() = 0;
		
		//��ȫ�ֵĲ�����
		virtual int OpenPhxParaLib(const char** paraLibs,int bufferSize,int phxParaType) = 0;
		//��ȡָ�����Ƶ��������
		virtual int GetPhxParaFromLib(const char* pName,void** paraData,int bufferSize,int phxParaType) = 0;
		//��ָ�����Ƶ�����������뵽������
		//opType: 0,������ 1,���ǡ�����0��ʾʧ�ܡ�����1��ʾ�ɹ�.��ͬ������Ҫ��ʾ�Ƿ񸲸�
		virtual int AddPhxParaToLib(const char* pName,void** paraData,int bufferSize,int phxParaType,int opType) = 0;

		//��ȡ����ѡʱ�����߷���,ʹ�õ�ǰ����Ⱦ����Ĳ���
		//point��dir����x��y��z��������
		virtual int GetMouseRayDir(int mouse_x,int mouse_y, H3DVec3* pos, H3DVec3* dir)=0;

		virtual int GetMouseRayDirEx(const H3DVec3& eye_position, const H3DVec3& camera_direction, const H3DVec3& camera_up, float f_near,
			float f_far, unsigned int screen_width, unsigned int screen_height, float fovX, int mouse_x,int mouse_y, H3DVec3* pos, H3DVec3* dir)=0;
		
		//�����Χ���ļ�������ֵ1��ʾ�ɹ���С��0���ɹ�
		virtual int LoadCustomBoundingVolume (const char* filename)=0;

		//!����һ��fxinfo
		virtual IFxInfo* CreateAFxInfo()=0;
		//����һ��ILevel
		virtual	ILevel *CreateLevel(const char * name) = 0;

		// ����ǰ֡��Ⱦ����ͼ
		// origPathName: ԭ��ͼ��·����,���ڻ�ø�ʽ����С
		virtual bool RenderToTexture(const char* origPathName, const char* pathName) = 0;
		
		//���Info��־
		virtual void OutPutLogInfo(H3DI::InfoType infoType,H3DI::OutPutFlag outFlag,const char* pStr) = 0;
		//���Error��־
		virtual void OutPutLogError(H3DI::ErrorType errorType,H3DI::OutPutFlag outFlag,const char* pStr) = 0;
		//��ý�������
		virtual const PrintScreenInfo* GetPrintScreenInfo()=0;
		virtual void ReleasePrintScreenInfo(const PrintScreenInfo* pInfo)=0;
	};



	//!������ʹ�õ�VB
	class IParticleVB : public IObject
	{
	public:
		//!��ʼ��,ָ��������Ӹ���
		virtual void Init(unsigned int particleCount) = 0;
		//!�õ�������Ӹ�ʽ
		virtual unsigned int GetMaxParticleCount(void)const = 0;
		/**
		//Particle��VB��ʽ������position(float3) + color(unsigned int) + UV(float2)
		//	���뽻�����
		//	*/
		virtual void* Lock(unsigned int particleCount) = 0;
		virtual void UnLock(void) = 0;
	protected:
		virtual ~IParticleVB(){}
	};


	//Ϊ�˵���level��octree�Լ�oc�õ�����
	//�����������������İ�Χ��
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
	//!�ؿ�
	class ILevel : public IScene
	{
	public:
		//!�õ�AABB
		virtual void GetWorldAABB(float* pArray6)const = 0;
		//!���û�������ɫ
		virtual void SetAmbientColor(float r, float g, float b) = 0;
		//!��geometry
		virtual bool Load(const char* fileName) = 0;
		//!�����culling
		virtual void CullByCamera(ICamera*) = 0;

		//by sssa2000 081203
		//��õ�����Ϣ
		virtual unsigned int GetOctreeAABBTestNum()=0;
		virtual unsigned int GetSubMeshOctreeSectionTestNum()=0;

		//by sssa2000 090216
		//Condition1��Condition2�ܹ����������������2�������Ľ���Χ��
		virtual void SetDebugCondition1(LEVEL_DEBUG_CONDITION ldc)=0;
		virtual void SetDebugCondition2(LEVEL_DEBUG_CONDITION ldc)=0;
		virtual void SetDebugCalc(LEVEL_DEBUG_SET_CALC ldc)=0;
		virtual void SetDrawOctreeLevel(int i)=0; //���û���octree�İ�Χ�еĲ㼶��Ϊ-1ʱ�������в㼶
		//by sssa2000 090209
		virtual void EnableOccluder(bool b)=0;
		virtual bool IsOccluderEnable()=0;
		virtual int GetOccluderNumber()=0;
		virtual void DrawOccluder(int i)=0;
		virtual void DrawOccluderFrustum(int i,H3DVec3& viewPoint)=0;
		//���ݳ�Ӱ��ϸ���������·ָ�˲���
		virtual void RestructOctree()=0;
		//��һ����������Ӻ���
		virtual void			AddPostProcess(const char* filename)=0;
		//��һ��ɾ������
		virtual void			DelPostProcess(const char* filename)=0;
		//����һ�������ĺ������
		virtual void			SetPostProcessParam(const char *name,const void *pvalue,int sizeOfValue)=0;
		//����һ���������ӿ�
		virtual	void			SetViewPort(const unsigned short *vp) = 0;
		//�õ�һ���������ӿ�,����һ���ĸ�Ԫ�ص�����
		virtual	void			GetViewPort(unsigned short *vp) = 0;
		//�����Ӿ���
		virtual void			SetViewMatrix(const H3DMat4 &mat) = 0;
		//����͸�Ӿ���
		virtual void			SetPerspectiveMatrix(const H3DMat4 &mat) = 0;

		//�Ӿ���
		virtual void					GetViewMatrix(H3DMat4 &mat) = 0;
		//͸�Ӿ���
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

		/// ���ó�����������ɫ
		virtual void					SetAmbientColor(const float *col)=0;
		/// ���ý�ɫ��������ɫ			
		virtual void					SetActorAmbientColor(const float *col)=0;
		//���ôα���ɢ����ɫ
		virtual void					SetTransmissionColor(const float* col) = 0;
		/// ���ó�������LOD
		virtual void					SetMaterialLod(int nLod)=0;
		/// �õ�����LOD			
		virtual int						GetMaterialLod()=0;

		virtual void					SetShadowFadeoutEnd(float fParam) = 0;

		// Ӱ��lightmap��ɫ lm' = lm * a + b
		// a, b��Ϊfloat3
		virtual void				SetLightmapColorFactor(const float* a, const float* b) = 0;


	protected:
		virtual ~ILevel(){}
	};




	//!�����
	class ICamera : public IMoveObject
	{
	public:
		//!�õ����ϵķ���
		virtual const H3DVec3& GetUp(void) = 0;
		//!�õ����ҵķ���
		virtual const H3DVec3& GetRight(void) = 0;
		//!�ӵ�ǰλ����position��
		virtual void LookAt(const H3DVec3& position) = 0;
		//!��eyePos��atPos��
		virtual void LookAt(const H3DVec3& eyePos, const H3DVec3& atPos, const H3DVec3& upVec) = 0;
		//!����ǰ����ת,���Ƕ�
		virtual void Roll(float degree) = 0;
		//!�����ҷ���ת,���Ƕ�
		virtual void Yaw(float degree) = 0;
		//!�����Ϸ���ת,���Ƕ�
		virtual void Pitch(float degree) = 0;
		//!����axisתdegree�Ƕ�
		virtual void Rotate(const H3DVec3& axis, float degree) = 0;
		//!�����ƶ�step����
		virtual void MoveUp(float step) = 0;
		//!�����ƶ�step����
		virtual void MoveRight(float step) = 0;
		//!��ǰ�ƶ�step����
		virtual void MoveFront(float step) = 0;
		//!�õ�view martix
		virtual const H3DMat4& GetViewMatrix(void)const = 0;
		//!�õ�ͶӰmatrix
		virtual const H3DMat4& GetProjectionMatrix(void)const = 0;
	protected:
		virtual ~ICamera(){}
	};

	
	//!��
	class IFog : public IMoveObject
	{
	public:
		///�õ���Χ���
		virtual void GetBoundingVolume(H3DVec3* resMin,H3DVec3* resMax)=0;
		///���������ķ�Χ,ʹ�ð�Χ�е���ʽ
		virtual void SetBoundingVolume(const H3DVec3& _min,const H3DVec3& _max)=0;
		///���������ɫ
		virtual void SetFogColor(float r,float g,float b,float a)=0;
		///�õ������ɫ
		virtual const H3DVec3& GetFogColor()=0;

		///�������Ũ��
		virtual void SetFogDensity(float s)=0;
		///������Ũ��
		virtual float GetFogDensity()=0;

		///���������ʼ��
		virtual void SetFogStart(float s)=0;
		///��������ʼ��
		virtual float GetFogStart()=0;
	protected:
		virtual ~IFog(){}
	};


	//!Ԥ����fx����Ϣ
	class IFxInfo
	{
	public:
		virtual void Reset()=0;

		virtual void Release()=0;

		//!������Ⱦ�����Ƿ���Ҫ�������
		virtual void SetRenderEnvCombination(bool b)=0;

		//!����һ����Ⱦ������nΪ���֣�numΪ����
		//!����ֵ=1��ʾ�ɹ���������ɹ��Ļ���ʾ�������Ⱦ���������ֲ��Ϸ�
		virtual int AddRenderEnvType(const char* n,int num)=0;

		//!����һ���꣬n�����֣�v��ֵ
		virtual void AddFxMacro(const char* name,const char* v)=0;

		//!������Ⱦ����,ǰ�����ӳٻ����ɲ���ȷ��
		//!0��ʾ�ɲ��ʾ�����1��ʾǿ��ʹ��ǰ��
		virtual void SetRenderType(int rendertype)=0;
	};
	
	//!IO�߳�Taskִ��״̬��أ���������ʹ��--begin
	//!����״̬��ö��
	enum THREAD_TASK_CONTEXT_STATE
	{
		THREAD_TASK_BEFORE_PARSE = 0,
		THREAD_TASK_AFTER_PARSE,
		THREAD_TASK_BEFORE_LOAD,
		THREAD_TASK_AFTER_LOAD,
	};

	//!������������У��������һЩ״��
	struct TaskContext 
	{
		//!��ǰ�����ID
		unsigned int		TaskId;

		//!��ǰ�����״̬
		THREAD_TASK_CONTEXT_STATE	TaskState;
		
		//!��ǰ�����Ѿ������˵������Դ�ĸ���
		unsigned int		LoadedNum;

		//!��ǰ�����Ƿ����
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

	//!IO��������������ڼ�����IO��������У�ĳʱ��ĳһ������Ĵ���״̬��
	class ProcessIOLisenter
	{
	public:
		//!֪ͨProcessIOLisenter�����ڴ���IO�Ľ׶�
		//!context�ǵ�ʱTask��������״��
		virtual void NotifyProcessIO(const TaskContext& context) = 0;

	};
	//!������������У��������һЩ״̬--end


	IRender* CreateRenderer();

	void DeleteRenderer();

	//ִ�е�Ԫ����
	int DoTest(int argc, char **argv);

}

#endif//
