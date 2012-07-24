// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_SIMD_SSE3_H__
#define __MATH_SIMD_SSE3_H__

/*
===============================================================================

	SSE3 implementation of H3DSIMDProcessor

===============================================================================
*/

class H3DSIMD_SSE3 : public H3DSIMD_SSE2 {
#ifdef _WIN32
public:
	virtual const char * VPCALL GetName( void ) const;

	virtual void VPCALL TransformVerts( H3DDrawVert *verts, const int numVerts, const H3DJointMat *joints, const H3DVec4 *weights, const int *index, const int numWeights );

#endif
};

#endif /* !__MATH_SIMD_SSE3_H__ */
