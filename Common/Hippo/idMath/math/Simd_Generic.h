// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_SIMD_GENERIC_H__
#define __MATH_SIMD_GENERIC_H__
#include "simd.h"
/*
===============================================================================

	Generic implementation of H3DSIMDProcessor

===============================================================================
*/

class H3DSIMD_Generic : public H3DSIMDProcessor {
public:
	virtual const char * VPCALL GetName( void ) const;

	virtual void VPCALL Add( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL Add( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL Sub( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL Sub( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL Mul( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL Mul( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL Div( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL Div( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL MulAdd( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL MulAdd( float *dst,			const float *src0,		const float *src1,		const int count );
	virtual void VPCALL MulSub( float *dst,			const float constant,	const float *src,		const int count );
	virtual void VPCALL MulSub( float *dst,			const float *src0,		const float *src1,		const int count );

	virtual void VPCALL Dot( float *dst,			const H3DVec3 &constant,	const H3DVec3 *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const H3DVec3 &constant,	const H3DPlane *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const H3DVec3 &constant,	const H3DDrawVert *src,	const int count );
	virtual void VPCALL Dot( float *dst,			const H3DPlane &constant,const H3DVec3 *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const H3DPlane &constant,const H3DPlane *src,		const int count );
	virtual void VPCALL Dot( float *dst,			const H3DPlane &constant,const H3DDrawVert *src,	const int count );
	virtual void VPCALL Dot( float *dst,			const H3DVec3 *src0,		const H3DVec3 *src1,		const int count );
	virtual void VPCALL Dot( float &dot,			const float *src1,		const float *src2,		const int count );

	virtual void VPCALL CmpGT( byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGT( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGE( byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpGE( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLT( byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLT( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLE( byte *dst,			const float *src0,		const float constant,	const int count );
	virtual void VPCALL CmpLE( byte *dst,			const byte bitNum,		const float *src0,		const float constant,	const int count );

	virtual void VPCALL MinMax( float &min,			float &max,				const float *src,		const int count );
	virtual	void VPCALL MinMax( H3DVec2 &min,		H3DVec2 &max,			const H3DVec2 *src,		const int count );
	virtual void VPCALL MinMax( H3DVec3 &min,		H3DVec3 &max,			const H3DVec3 *src,		const int count );
	virtual	void VPCALL MinMax( H3DVec3 &min,		H3DVec3 &max,			const H3DDrawVert *src,	const int count );
	virtual	void VPCALL MinMax( H3DVec3 &min,		H3DVec3 &max,			const H3DDrawVert *src,	const int *indexes,		const int count );

	virtual void VPCALL Clamp( float *dst,			const float *src,		const float min,		const float max,		const int count );
	virtual void VPCALL ClampMin( float *dst,		const float *src,		const float min,		const int count );
	virtual void VPCALL ClampMax( float *dst,		const float *src,		const float max,		const int count );

	virtual void VPCALL Memcpy( void *dst,			const void *src,		const int count );
	virtual void VPCALL Memset( void *dst,			const int val,			const int count );

	virtual void VPCALL Zero16( float *dst,			const int count );
	virtual void VPCALL Negate16( float *dst,		const int count );
	virtual void VPCALL Copy16( float *dst,			const float *src,		const int count );
	virtual void VPCALL Add16( float *dst,			const float *src1,		const float *src2,		const int count );
	virtual void VPCALL Sub16( float *dst,			const float *src1,		const float *src2,		const int count );
	virtual void VPCALL Mul16( float *dst,			const float *src1,		const float constant,	const int count );
	virtual void VPCALL AddAssign16( float *dst,	const float *src,		const int count );
	virtual void VPCALL SubAssign16( float *dst,	const float *src,		const int count );
	virtual void VPCALL MulAssign16( float *dst,	const float constant,	const int count );

	virtual void VPCALL MatX_MultiplyVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec );
	virtual void VPCALL MatX_MultiplyAddVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec );
	virtual void VPCALL MatX_MultiplySubVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec );
	virtual void VPCALL MatX_TransposeMultiplyVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec );
	virtual void VPCALL MatX_TransposeMultiplyAddVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec );
	virtual void VPCALL MatX_TransposeMultiplySubVecX( H3DVecX &dst, const H3DMatX &mat, const H3DVecX &vec );
	virtual void VPCALL MatX_MultiplyMatX( H3DMatX &dst, const H3DMatX &m1, const H3DMatX &m2 );
	virtual void VPCALL MatX_TransposeMultiplyMatX( H3DMatX &dst, const H3DMatX &m1, const H3DMatX &m2 );
	virtual void VPCALL MatX_LowerTriangularSolve( const H3DMatX &L, float *x, const float *b, const int n, int skip = 0 );
	virtual void VPCALL MatX_LowerTriangularSolveTranspose( const H3DMatX &L, float *x, const float *b, const int n );
	virtual bool VPCALL MatX_LDLTFactor( H3DMatX &mat, H3DVecX &invDiag, const int n );

	virtual void VPCALL BlendJoints( H3DJointQuat *joints, const H3DJointQuat *blendJoints, const float lerp, const int *index, const int numJoints );
	virtual void VPCALL ConvertJointQuatsToJointMats( H3DJointMat *jointMats, const H3DJointQuat *jointQuats, const int numJoints );
	virtual void VPCALL ConvertJointMatsToJointQuats( H3DJointQuat *jointQuats, const H3DJointMat *jointMats, const int numJoints );
	virtual void VPCALL TransformJoints( H3DJointMat *jointMats, const int *parents, const int firstJoint, const int lastJoint );
	virtual void VPCALL UntransformJoints( H3DJointMat *jointMats, const int *parents, const int firstJoint, const int lastJoint );
	virtual void VPCALL TransformVerts( H3DDrawVert *verts, const int numVerts, const H3DJointMat *joints, const H3DVec4 *weights, const int *index, const int numWeights );
	virtual void VPCALL TracePointCull( byte *cullBits, byte &totalOr, const float radius, const H3DPlane *planes, const H3DDrawVert *verts, const int numVerts );
	virtual void VPCALL DecalPointCull( byte *cullBits, const H3DPlane *planes, const H3DDrawVert *verts, const int numVerts );
	virtual void VPCALL OverlayPointCull( byte *cullBits, H3DVec2 *texCoords, const H3DPlane *planes, const H3DDrawVert *verts, const int numVerts );
	virtual void VPCALL DeriveTriPlanes( H3DPlane *planes, const H3DDrawVert *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual void VPCALL DeriveTangents( H3DPlane *planes, H3DDrawVert *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual void VPCALL DeriveUnsmoothedTangents( H3DDrawVert *verts, const dominantTri_s *dominantTris, const int numVerts );
	virtual void VPCALL NormalizeTangents( H3DDrawVert *verts, const int numVerts );
	virtual void VPCALL CreateTextureSpaceLightVectors( H3DVec3 *lightVectors, const H3DVec3 &lightOrigin, const H3DDrawVert *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual void VPCALL CreateSpecularTextureCoords( H3DVec4 *texCoords, const H3DVec3 &lightOrigin, const H3DVec3 &viewOrigin, const H3DDrawVert *verts, const int numVerts, const int *indexes, const int numIndexes );
	virtual int  VPCALL CreateShadowCache( H3DVec4 *vertexCache, int *vertRemap, const H3DVec3 &lightOrigin, const H3DDrawVert *verts, const int numVerts );
	virtual int  VPCALL CreateVertexProgramShadowCache( H3DVec4 *vertexCache, const H3DDrawVert *verts, const int numVerts );

	virtual void VPCALL UpSamplePCMTo44kHz( float *dest, const short *pcm, const int numSamples, const int kHz, const int numChannels );
	virtual void VPCALL UpSampleOGGTo44kHz( float *dest, const float * const *ogg, const int numSamples, const int kHz, const int numChannels );
	virtual void VPCALL MixSoundTwoSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] );
	virtual void VPCALL MixSoundTwoSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[2], const float currentV[2] );
	virtual void VPCALL MixSoundSixSpeakerMono( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] );
	virtual void VPCALL MixSoundSixSpeakerStereo( float *mixBuffer, const float *samples, const int numSamples, const float lastV[6], const float currentV[6] );
	virtual void VPCALL MixedSoundToSamples( short *samples, const float *mixBuffer, const int numSamples );
};

#endif /* !__MATH_SIMD_GENERIC_H__ */
