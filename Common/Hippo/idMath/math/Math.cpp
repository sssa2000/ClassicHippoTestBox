// Copyright (C) 2004 Id Software, Inc.
//

//#include "../precompiled.h"
#include "../dmathheader.h"
#pragma hdrstop


const float	H3DMath::PI				= 3.14159265358979323846f;
const float	H3DMath::TWO_PI			= 2.0f * PI;
const float	H3DMath::HALF_PI			= 0.5f * PI;
const float	H3DMath::ONEFOURTH_PI	= 0.25f * PI;
const float H3DMath::E				= 2.71828182845904523536f;
const float H3DMath::SQRT_TWO		= 1.41421356237309504880f;
const float H3DMath::SQRT_THREE		= 1.73205080756887729352f;
const float	H3DMath::SQRT_1OVER2		= 0.70710678118654752440f;
const float	H3DMath::SQRT_1OVER3		= 0.57735026918962576450f;
const float	H3DMath::M_DEG2RAD		= PI / 180.0f;
const float	H3DMath::M_RAD2DEG		= 180.0f / PI;
const float	H3DMath::M_SEC2MS		= 1000.0f;
const float	H3DMath::M_MS2SEC		= 0.001f;
const float	H3DMath::INFINITY		= 1e30f;
//const float H3DMath::FLT_EPSILON		= 1.192092896e-07f;

bool		H3DMath::initialized		= false;
dword		H3DMath::iSqrt[SQRT_TABLE_SIZE];		// inverse square root lookup table

const static bool mathInited(H3DMath::Init());
/*
===============
H3DMath::Init
===============
*/
bool H3DMath::Init( void ) {
    union _flint fi, fo;

    for ( int i = 0; i < SQRT_TABLE_SIZE; i++ ) {
        fi.i	 = ((EXP_BIAS-1) << EXP_POS) | (i << LOOKUP_POS);
        fo.f	 = (float)( 1.0 / sqrt( fi.f ) );
        iSqrt[i] = ((dword)(((fo.i + (1<<(SEED_POS-2))) >> SEED_POS) & 0xFF))<<SEED_POS;
    }
    
	iSqrt[SQRT_TABLE_SIZE / 2] = ((dword)(0xFF))<<(SEED_POS); 

	initialized = true;

	return true;
}

/*
================
H3DMath::FloatToBits
================
*/
int H3DMath::FloatToBits( float f, int exponentBits, int mantissaBits ) {
	int i, sign, exponent, mantissa, value;

	assert( exponentBits >= 2 && exponentBits <= 8 );
	assert( mantissaBits >= 2 && mantissaBits <= 23 );

	int maxBits = ( ( ( 1 << ( exponentBits - 1 ) ) - 1 ) << mantissaBits ) | ( ( 1 << mantissaBits ) - 1 );
	int minBits = ( ( ( 1 <<   exponentBits       ) - 2 ) << mantissaBits ) | 1;

	float max = BitsToFloat( maxBits, exponentBits, mantissaBits );
	float min = BitsToFloat( minBits, exponentBits, mantissaBits );

	if ( f >= 0.0f ) {
		if ( f >= max ) {
			return maxBits;
		} else if ( f <= min ) {
			return minBits;
		}
	} else {
		if ( f <= -max ) {
			return ( maxBits | ( 1 << ( exponentBits + mantissaBits ) ) );
		} else if ( f >= -min ) {
			return ( minBits | ( 1 << ( exponentBits + mantissaBits ) ) );
		}
	}

	exponentBits--;
	i = *reinterpret_cast<int *>(&f);
	sign = ( i >> IEEE_FLT_SIGN_BIT ) & 1;
	exponent = ( ( i >> IEEE_FLT_MANTISSA_BITS ) & ( ( 1 << IEEE_FLT_EXPONENT_BITS ) - 1 ) ) - IEEE_FLT_EXPONENT_BIAS;
	mantissa = i & ( ( 1 << IEEE_FLT_MANTISSA_BITS ) - 1 );
	value = sign << ( 1 + exponentBits + mantissaBits );
	value |= ( ( INTSIGNBITSET( exponent ) << exponentBits ) | ( abs( exponent ) & ( ( 1 << exponentBits ) - 1 ) ) ) << mantissaBits;
	value |= mantissa >> ( IEEE_FLT_MANTISSA_BITS - mantissaBits );
	return value;
}

/*
================
H3DMath::BitsToFloat
================
*/
float H3DMath::BitsToFloat( int i, int exponentBits, int mantissaBits ) {
	static int exponentSign[2] = { 1, -1 };
	int sign, exponent, mantissa, value;

	assert( exponentBits >= 2 && exponentBits <= 8 );
	assert( mantissaBits >= 2 && mantissaBits <= 23 );

	exponentBits--;
	sign = i >> ( 1 + exponentBits + mantissaBits );
	exponent = ( ( i >> mantissaBits ) & ( ( 1 << exponentBits ) - 1 ) ) * exponentSign[( i >> ( exponentBits + mantissaBits ) ) & 1];
	mantissa = ( i & ( ( 1 << mantissaBits ) - 1 ) ) << ( IEEE_FLT_MANTISSA_BITS - mantissaBits );
	value = sign << IEEE_FLT_SIGN_BIT | ( exponent + IEEE_FLT_EXPONENT_BIAS ) << IEEE_FLT_MANTISSA_BITS | mantissa;
	return *reinterpret_cast<float *>(&value);
}
