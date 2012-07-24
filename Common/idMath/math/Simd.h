// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_SIMD_H__
#define __MATH_SIMD_H__
#include "idlib.h"
#include "math.h"


/*
===============================================================================

	Single Instruction Multiple Data (SIMD)

	For optimal use data should be aligned on a 16 byte boundary.
	All H3DSIMDProcessor routines are thread safe.

===============================================================================
*/

class H3DSIMD {
public:
	static void			Init( void );
	static void			InitProcessor( const char *module, bool forceGeneric );
	static void			Shutdown( void );
	static void			Test_f( );
};


/*
===============================================================================

	virtual base class for different SIMD processors

===============================================================================
*/

#ifdef _WIN32
#define VPCALL __fastcall
#else
#define VPCALL
#endif

class H3DVec2;
class H3DVec3;
class H3DVec4;
class H3DVec5;
class H3DVec6;
class H3DVecX;
class H3DMat2;
class H3DMat3;
class H3DMat4;
class H3DMat5;
class H3DMat6;
class H3DMatX;
class H3DPlane;
class H3DDrawVert;
class H3DJointQuat;
class H3DJointMat;
struct dominantTri_s;

const int MIXBUFFER_SAMPLES = 4096;

typedef enum {
	SPEAKER_LEFT = 0,
	SPEAKER_RIGHT,
	SPEAKER_CENTER,
	SPEAKER_LFE,
	SPEAKER_BACKLEFT,
	SPEAKER_BACKRIGHT
} speakerLabel;


class H3DSIMDProcessor {
public:
									H3DSIMDProcessor( void ) { cpuid = CPUID_NONE; }

	cpuid_t							cpuid;

	virtual const char * VPCALL		GetName( void ) const = 0;

	virtual void VPCALL Add( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL Add( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL Sub( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL Sub( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL Mul( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL Mul( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL Div( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL Div( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL MulAdd( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL MulAdd( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;
	virtual void VPCALL MulSub( float *dst,			const float constant,	const float *src,		const int count ) = 0;
	virtual void VPCALL MulSub( float *dst,			const float *src0,		const float *src1,		const int count ) = 0;

	virtual	void VPCALL Dot( float *dst,			const H3DVec3 &constant,	const H3DVec3 *src,		const int count ) = 0;
	virtual	void VPCALL Dot( float *dst,			const H3DVec3 &constant,	const H3DPlane *src,		const int count ) = 0;
	virtual void VPCALL Dot( float *dst,			const H3DVec3 &constant,	const H3DDrawVert *src,	const int count ) = 0;
	virtual	void VPCALL Dot( float *dst,			const H3DPlane &constant,const H3DVec3 *src,		const int count ) = 0;
	virtual	void VPCALL Dot( float *dst,			const H3DPlane &constant,const H3DPlane *src,		const int count ) = 0;
	virtual void VPCALL Dot( float *dst,			const H3DPlane &constant,const H3DDrawVert *src,	const int count ) = 0;
	virtual	void VPCALL Dot( float *dst,			const H3DVec3 *src0,		const H3DVec3 *src1,		const int count ) = 0;
	virtual void VPCALL Dot( float &dot,			const float *src1,		const float *src2,		const int count ) = 0;

	virtual	void VPCALL CmpGT( byte *dst,			const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpGT( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpGE( byte *dst,			const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpGE( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpLT( byte *dst,			const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpLT( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpLE( byte *dst,			const float *src0,		const float constant,	const int count ) = 0;
	virtual	void VPCALL CmpLE( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count ) = 0;

	virtual	void VPCALL MinMax( float &min,			float &max,				const float *src,		const int count ) = 0;
	virtual	void VPCALL MinMax( H3DVec2 &min,		H3DVec2 &max,			const H3DVec2 *src,		const int count ) = 0;
	virtual	void VPCALL MinMax( H3DVec3 &min,		H3DVec3 &max,			const H3DVec3 *src,		const int count ) = 0;
	virtual	void VPCALL MinMax( H3DVec3 &min,		H3DVec3 &max,			const H3DDrawVert *src,	const int count ) = 0;
	virtual	void VPCALL MinMax( H3DVec3 &min,		H3DVec3 &max,			const H3DDrawVert *src,	const int *indexes,		const int count ) = 0;

	virtual	void VPCALL Clamp( float *dst,			const float *src,		const float min,		const float max,		const int count ) = 0;
	virtual	void VPCALL ClampMin( float *dst,		const float *src,		const float min,		const int count ) = 0;
	virtual	void VPCALL ClampMax( float *dst,		const float *src,		const float max,		const int count ) = 0;

	virtual void VPCALL Memcpy( void *dst,			const void *src,		const int count ) = 0;
	virtual void VPCALL Memset( void *dst,			const int val,			const int count ) = 0;

	// these assume 16 byte aligned and 16 byte padded memory
	virtual void VPCALL Zero16( float *dst,			const int count ) = 0;
	virtual void VPCALL Negate16( float *dst,		const int count ) = 0;
	virtual void VPCALL Copy16( float *dst,			const float *src,		const int count ) = 0;
	virtual void VPCALL Add16( float *dst,			const float *src1,		const float *src2,		const int count ) = 0;
	virtual void VPCALL Sub16( float *dst,			const float *src1,		const float *src2,		const int count ) = 0;
	virtual void VPCALL Mul16( float *dst,			const float *src1,		const float constant,	const int count ) = 0;
	virtual void VPCALL AddAssign16( float *dst,	const float *src,		const int count ) = 0;
	virtual void VPCALL SubAssign16( float *dst,	const float *src,		const int count ) = 0;
	virtual void VPCALL MulAssign16( float *dst,	const float constant,	const int count ) = 0;

	// H3DMatX operations
	virtual void VPCALL MatX_MultiplyVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec ) = 0;
	virtual void VPCALL MatX_MultiplyAddVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec ) = 0;
	virtual void VPCALL MatX_MultiplySubVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec ) = 0;
	virtual void VPCALL MatX_TransposeMultiplyVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec ) = 0;
	virtual void VPCALL MatX_TransposeMultiplyAddVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec ) = 0;
	virtual void VPCALL MatX_TransposeMultiplySubVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec ) = 0;
	virtual void VPCALL MatX_MultiplyMatX( H3DMatX &dst, const H3DMatX &m1, const H3DMatX &m2 ) = 0;
	virtual void VPCALL MatX_TransposeMultiplyMatX( H3DMatX &dst, const H3DMatX &m1, const H3DMatX &m2 ) = 0;
	virtual void VPCALL MatX_LowerTriangularSolve( const H3DMatX &L, float *x, const float *b, const int n, int skip = 0 ) = 0;
	virtual void VPCALL MatX_LowerTriangularSolveTranspose( const H3DMatX &L, float *x, const float *b, const int n ) = 0;
	virtual bool VPCALL MatX_LDLTFactor( H3DMatX &mat, H3DVecX &invDiag, const int n ) = 0;

	// rendering
	virtual void VPCALL BlendJoints( H3DJointQuat *joints, const H3DJointQuat *blendJoints, const float lerp, const int *index, const int numJoints ) = 0;
	virtual void VPCALL ConvertJointQuatsToJointMats( H3DJointMat *jointMats, const H3DJointQuat *jointQuats, const int numJoints ) = 0;
	virtual void VPCALL ConvertJointMatsToJointQuats( H3DJointQuat *jointQuats, const H3DJointMat *jointMats, const int numJoints ) = 0;
	virtual void VPCALL TransformJoints( H3DJointMat *jointMats, const int *parents, const int firstJoint, const int lastJoint ) = 0;
	virtual void VPCALL UntransformJoints( H3DJointMat *jointMats, const int *parents, const int firstJoint, const int lastJoint ) = 0;
	virtual void VPCALL TransformVerts( H3DDrawVert *verts, const int numVerts, const H3DJointMat *joints, const H3DVec4 *weights, const int *index, const int numWeights ) = 0;
	virtual void VPCALL TracePointCull( byte *cullBits, byte &totalOr, const float radius, const H3DPlane *planes, const H3DDrawVert *verts, const int numVerts ) = 0;
	virtual void VPCALL DecalPointCull( byte *cullBits, const H3DPlane *planes, const H3DDrawVert *verts, const int numVerts ) = 0;
	virtual void VPCALL OverlayPointCull( byte *cullBits, H3DVec2 *texCoords, const H3DPlane *planes, const H3DDrawVert *verts, const int numVerts ) = 0;
	virtual void VPCALL DeriveTriPlanes( H3DPlane *planes, const H3DDrawVert *verts, const int numVerts, const int *indexes, const int numIndexes ) = 0;
	virtual void VPCALL DeriveTangents( H3DPlane *planes, H3DDrawVert *verts, const int numVerts, const int *indexes, const int numIndexes ) = 0;
	virtual void VPCALL DeriveUnsmoothedTangents( H3DDrawVert *verts, const dominantTri_s *dominantTris, const int numVerts ) = 0;
	virtual void VPCALL NormalizeTangents( H3DDrawVert *verts, const int numVerts ) = 0;
	virtual void VPCALL CreateTextureSpaceLightVectors( H3DVec3 *lightVectors, const H3DVec3 &lightOrigin, const H3DDrawVert *verts, const int numVerts, const int *indexes, const int numIndexes ) = 0;
	virtual void VPCALL CreateSpecularTextureCoords( H3DVec4 *texCoords, const H3DVec3 &lightOrigin, const H3DVec3 &viewOrigin, const H3DDrawVert *verts, const int numVerts, const int *indexes, const int numIndexes ) = 0;
	virtual int  VPCALL CreateShadowCache( H3DVec4 *vertexCache, int *vertRemap, const H3DVec3 &lightOrigin, const H3DDrawVert *verts, const int numVerts ) = 0;
	virtual int  VPCALL CreateVertexProgramShadowCache( H3DVec4 *vertexCache, const H3DDrawVert *verts, const int numVerts ) = 0;

	// sound mixing
	virtual void VPCALL UpSamplePCMTo44kHz( float *dest, const short *pcm, const int numSamples, const int kHz, const int numChannels ) = 0;
	virtual void VPCALL UpSampleOGGTo44kHz( float *dest, const float * const *ogg, const int numSamples, const int kHz, const int numChannels ) = 0;
	virtual void VPCALL MixSoundTwoSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] ) = 0;
	virtual void VPCALL MixSoundTwoSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] ) = 0;
	virtual void VPCALL MixSoundSixSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] ) = 0;
	virtual void VPCALL MixSoundSixSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] ) = 0;
	virtual void VPCALL MixedSoundToSamples( short *samples, const float *mixBuffer, const int numSamples ) = 0;
};

// pointer to SIMD processor
extern H3DSIMDProcessor *SIMDProcessor;

#endif /* !__MATH_SIMD_H__ */
