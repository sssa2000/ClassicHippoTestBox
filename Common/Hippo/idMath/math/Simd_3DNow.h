// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_SIMD_3DNOW_H__
#define __MATH_SIMD_3DNOW_H__

/*
===============================================================================

	3DNow! implementation of H3DSIMDProcessor

===============================================================================
*/

class H3DSIMD_3DNow : public H3DSIMD_MMX {
#ifdef _WIN32
public:
	virtual const char * VPCALL GetName( void ) const;

	virtual void VPCALL Memcpy( void *dst,			const void *src,		const int count );

#endif
};

#endif /* !__MATH_SIMD_3DNOW_H__ */
