// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_VECTOR_H__
#define __MATH_VECTOR_H__

/*
===============================================================================

  Vector classes

===============================================================================
*/
#include "idlib.h"
#include <memory.h>
#include "math.h"
//#include "../heap.h"
#include "simd_generic.h"
#include "random.h"
#define VECTOR_EPSILON		0.001f



#pragma  warning(disable : 4311)

class H3DAngles;
class idPolar3;
class H3DMat3;

//===============================================================
//
//	H3DVec2 - 2D vector
//
//===============================================================

class H3DVec2 {
public:
	float			x;
	float			y;

					H3DVec2( void );
					explicit H3DVec2( const float x, const float y );

	void 			Set( const float x, const float y );
	void			Zero( void );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	H3DVec2			operator-() const;
	float			operator*( const H3DVec2 &a ) const;
	H3DVec2			operator*( const float a ) const;
	H3DVec2			operator/( const float a ) const;
	H3DVec2			operator+( const H3DVec2 &a ) const;
	H3DVec2			operator-( const H3DVec2 &a ) const;
	H3DVec2 &		operator+=( const H3DVec2 &a );
	H3DVec2 &		operator-=( const H3DVec2 &a );
	H3DVec2 &		operator/=( const H3DVec2 &a );
	H3DVec2 &		operator/=( const float a );
	H3DVec2 &		operator*=( const float a );

	friend H3DVec2	operator*( const float a, const H3DVec2 b );

	bool			Compare( const H3DVec2 &a ) const;							// exact compare, no epsilon
	bool			Compare( const H3DVec2 &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const H3DVec2 &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const H3DVec2 &a ) const;						// exact compare, no epsilon

	float			Length( void ) const;
	float			LengthFast( void ) const;
	float			LengthSqr( void ) const;
	float			Normalize( void );			// returns length
	float			NormalizeFast( void );		// returns length
	H3DVec2 &		Truncate( float length );	// cap length
	void			Clamp( const H3DVec2 &min, const H3DVec2 &max );
	void			Snap( void );				// snap to closest integer value
	void			SnapInt( void );			// snap towards integer (floor)

	int				GetDimension( void ) const;

	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

	void			Lerp( const H3DVec2 &v1, const H3DVec2 &v2, const float l );

	//================by wh================
	float Dot(const H3DVec2& input)const
	{
		return x*input.x+y*input.y;
	}

	H3DVec2& MultiplySelf(const H3DVec2& input)
	{
		x *= input.x;
		y *= input.y;
		return *this;
	}

	H3DVec2 Multiply(const H3DVec2& input)const
	{
		return H3DVec2(x*input.x, y*input.y);
	}
	//================by wh end================
};

extern H3DVec2 vec2_origin;
#define vec2_zero vec2_origin

ID_INLINE H3DVec2::H3DVec2( void ) {
}

ID_INLINE H3DVec2::H3DVec2( const float x, const float y ) {
	this->x = x;
	this->y = y;
}

ID_INLINE void H3DVec2::Set( const float x, const float y ) {
	this->x = x;
	this->y = y;
}

ID_INLINE void H3DVec2::Zero( void ) {
	x = y = 0.0f;
}

ID_INLINE bool H3DVec2::Compare( const H3DVec2 &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) );
}

ID_INLINE bool H3DVec2::Compare( const H3DVec2 &a, const float epsilon ) const {
	if ( H3DMath::Fabs( x - a.x ) > epsilon ) {
		return false;
	}
			
	if ( H3DMath::Fabs( y - a.y ) > epsilon ) {
		return false;
	}

	return true;
}

ID_INLINE bool H3DVec2::operator==( const H3DVec2 &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DVec2::operator!=( const H3DVec2 &a ) const {
	return !Compare( a );
}

ID_INLINE float H3DVec2::operator[]( int index ) const {
	return ( &x )[ index ];
}

ID_INLINE float& H3DVec2::operator[]( int index ) {
	return ( &x )[ index ];
}

ID_INLINE float H3DVec2::Length( void ) const {
	return ( float )H3DMath::Sqrt( x * x + y * y );
}

ID_INLINE float H3DVec2::LengthFast( void ) const {
	float sqrLength;

	sqrLength = x * x + y * y;
	return sqrLength * H3DMath::RSqrt( sqrLength );
}

ID_INLINE float H3DVec2::LengthSqr( void ) const {
	return ( x * x + y * y );
}

ID_INLINE float H3DVec2::Normalize( void ) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y;
	invLength = H3DMath::InvSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	return invLength * sqrLength;
}

ID_INLINE float H3DVec2::NormalizeFast( void ) {
	float lengthSqr, invLength;

	lengthSqr = x * x + y * y;
	invLength = H3DMath::RSqrt( lengthSqr );
	x *= invLength;
	y *= invLength;
	return invLength * lengthSqr;
}

ID_INLINE H3DVec2 &H3DVec2::Truncate( float length ) {
	float length2;
	float ilength;

	if ( !length ) {
		Zero();
	}
	else {
		length2 = LengthSqr();
		if ( length2 > length * length ) {
			ilength = length * H3DMath::InvSqrt( length2 );
			x *= ilength;
			y *= ilength;
		}
	}

	return *this;
}

ID_INLINE void H3DVec2::Clamp( const H3DVec2 &min, const H3DVec2 &max ) {
	if ( x < min.x ) {
		x = min.x;
	} else if ( x > max.x ) {
		x = max.x;
	}
	if ( y < min.y ) {
		y = min.y;
	} else if ( y > max.y ) {
		y = max.y;
	}
}

ID_INLINE void H3DVec2::Snap( void ) {
	x = floor( x + 0.5f );
	y = floor( y + 0.5f );
}

ID_INLINE void H3DVec2::SnapInt( void ) {
	x = float( int( x ) );
	y = float( int( y ) );
}

ID_INLINE H3DVec2 H3DVec2::operator-() const {
	return H3DVec2( -x, -y );
}
	
ID_INLINE H3DVec2 H3DVec2::operator-( const H3DVec2 &a ) const {
	return H3DVec2( x - a.x, y - a.y );
}

ID_INLINE float H3DVec2::operator*( const H3DVec2 &a ) const {
	return x * a.x + y * a.y;
}

ID_INLINE H3DVec2 H3DVec2::operator*( const float a ) const {
	return H3DVec2( x * a, y * a );
}

ID_INLINE H3DVec2 H3DVec2::operator/( const float a ) const {
	float inva = 1.0f / a;
	return H3DVec2( x * inva, y * inva );
}

ID_INLINE H3DVec2 operator*( const float a, const H3DVec2 b ) {
	return H3DVec2( b.x * a, b.y * a );
}

ID_INLINE H3DVec2 H3DVec2::operator+( const H3DVec2 &a ) const {
	return H3DVec2( x + a.x, y + a.y );
}

ID_INLINE H3DVec2 &H3DVec2::operator+=( const H3DVec2 &a ) {
	x += a.x;
	y += a.y;

	return *this;
}

ID_INLINE H3DVec2 &H3DVec2::operator/=( const H3DVec2 &a ) {
	x /= a.x;
	y /= a.y;

	return *this;
}

ID_INLINE H3DVec2 &H3DVec2::operator/=( const float a ) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;

	return *this;
}

ID_INLINE H3DVec2 &H3DVec2::operator-=( const H3DVec2 &a ) {
	x -= a.x;
	y -= a.y;

	return *this;
}

ID_INLINE H3DVec2 &H3DVec2::operator*=( const float a ) {
	x *= a;
	y *= a;

	return *this;
}

ID_INLINE int H3DVec2::GetDimension( void ) const {
	return 2;
}

ID_INLINE const float *H3DVec2::ToFloatPtr( void ) const {
	return &x;
}

ID_INLINE float *H3DVec2::ToFloatPtr( void ) {
	return &x;
}


//===============================================================
//
//	H3DVec3 - 3D vector
//
//===============================================================

class H3DVec3 {
public:	
	float			x;
	float			y;
	float			z;

					H3DVec3( void );
					explicit H3DVec3( const float x, const float y, const float z );

	void 			Set( const float x, const float y, const float z );
	void			Zero( void );

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	H3DVec3			operator-() const;
	H3DVec3 &		operator=( const H3DVec3 &a );		// required because of a msvc 6 & 7 bug
	//float			operator*( const H3DVec3 &a ) const; //avoid confusion between dot and multiply
	H3DVec3			operator*( const float a ) const;
	H3DVec3			operator/( const float a ) const;
	H3DVec3			operator+( const H3DVec3 &a ) const;
	H3DVec3			operator-( const H3DVec3 &a ) const;
	H3DVec3 &		operator+=( const H3DVec3 &a );
	H3DVec3 &		operator-=( const H3DVec3 &a );
	H3DVec3 &		operator/=( const H3DVec3 &a );
	H3DVec3 &		operator/=( const float a );
	H3DVec3 &		operator*=( const float a );

	friend H3DVec3	operator*( const float a, const H3DVec3 b );

	bool			Compare( const H3DVec3 &a ) const;							// exact compare, no epsilon
	bool			Compare( const H3DVec3 &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const H3DVec3 &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const H3DVec3 &a ) const;						// exact compare, no epsilon

	bool			FixDegenerateNormal( void );	// fix degenerate axial cases
	bool			FixDenormals( void );			// change tiny numbers to zero

	H3DVec3			Cross( const H3DVec3 &a ) const;
	H3DVec3 &		Cross( const H3DVec3 &a, const H3DVec3 &b );
	float			Length( void ) const;
	float			LengthSqr( void ) const;
	float			LengthFast( void ) const;
	float			Normalize( void );				// returns length
	float			NormalizeFast( void );			// returns length
	H3DVec3 &		Truncate( float length );		// cap length
	void			Clamp( const H3DVec3 &min, const H3DVec3 &max );
	void			Snap( void );					// snap to closest integer value
	void			SnapInt( void );				// snap towards integer (floor)

	int				GetDimension( void ) const;

	float			ToYaw( void ) const;
	float			ToPitch( void ) const;
	H3DAngles		ToAngles( void ) const;
	idPolar3		ToPolar( void ) const;
	H3DMat3			ToMat3( void ) const;		// vector should be normalized
	const H3DVec2 &	ToVec2( void ) const;
	H3DVec2 &		ToVec2( void );
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

	void			NormalVectors( H3DVec3 &left, H3DVec3 &down ) const;	// vector should be normalized
	void			OrthogonalBasis( H3DVec3 &left, H3DVec3 &up ) const;

	void			ProjectOntoPlane( const H3DVec3 &normal, const float overBounce = 1.0f );
	bool			ProjectAlongPlane( const H3DVec3 &normal, const float epsilon, const float overBounce = 1.0f );
	void			ProjectSelfOntoSphere( const float radius );

	void			Lerp( const H3DVec3 &v1, const H3DVec3 &v2, const float l );
	void			SLerp( const H3DVec3 &v1, const H3DVec3 &v2, const float l );


	//================by wh================
	float Dot(const H3DVec3& input)const
	{
		return x*input.x+y*input.y+z*input.z;
	}

	H3DVec3& MultiplySelf(const H3DVec3& input)
	{
		x *= input.x;
		y *= input.y;
		z *= input.z;
		return *this;
	}

	H3DVec3 Multiply(const H3DVec3& input)const
	{
		return H3DVec3(x*input.x, y*input.y, z*input.z);
	}
	//================by wh end================
};

extern H3DVec3 vec3_origin;
extern H3DVec3 vec3_unitX;
extern H3DVec3 vec3_unitY;
extern H3DVec3 vec3_unitZ;
#define vec3_zero vec3_origin

ID_INLINE H3DVec3::H3DVec3( void ) {
}

ID_INLINE H3DVec3::H3DVec3( const float x, const float y, const float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

ID_INLINE float H3DVec3::operator[]( const int index ) const {
	return ( &x )[ index ];
}

ID_INLINE float &H3DVec3::operator[]( const int index ) {
	return ( &x )[ index ];
}

ID_INLINE void H3DVec3::Set( const float x, const float y, const float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

ID_INLINE void H3DVec3::Zero( void ) {
	x = y = z = 0.0f;
}

ID_INLINE H3DVec3 H3DVec3::operator-() const {
	return H3DVec3( -x, -y, -z );
}

ID_INLINE H3DVec3 &H3DVec3::operator=( const H3DVec3 &a ) {
	x = a.x;
	y = a.y;
	z = a.z;
	return *this;
}

ID_INLINE H3DVec3 H3DVec3::operator-( const H3DVec3 &a ) const {
	return H3DVec3( x - a.x, y - a.y, z - a.z );
}

//ID_INLINE float H3DVec3::operator*( const H3DVec3 &a ) const {
//	return x * a.x + y * a.y + z * a.z;
//}

ID_INLINE H3DVec3 H3DVec3::operator*( const float a ) const {
	return H3DVec3( x * a, y * a, z * a );
}

ID_INLINE H3DVec3 H3DVec3::operator/( const float a ) const {
	float inva = 1.0f / a;
	return H3DVec3( x * inva, y * inva, z * inva );
}

ID_INLINE H3DVec3 operator*( const float a, const H3DVec3 b ) {
	return H3DVec3( b.x * a, b.y * a, b.z * a );
}

ID_INLINE H3DVec3 H3DVec3::operator+( const H3DVec3 &a ) const {
	return H3DVec3( x + a.x, y + a.y, z + a.z );
}

ID_INLINE H3DVec3 &H3DVec3::operator+=( const H3DVec3 &a ) {
	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
}

ID_INLINE H3DVec3 &H3DVec3::operator/=( const H3DVec3 &a ) {
	x /= a.x;
	y /= a.y;
	z /= a.z;

	return *this;
}

ID_INLINE H3DVec3 &H3DVec3::operator/=( const float a ) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;
	z *= inva;

	return *this;
}

ID_INLINE H3DVec3 &H3DVec3::operator-=( const H3DVec3 &a ) {
	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;
}

ID_INLINE H3DVec3 &H3DVec3::operator*=( const float a ) {
	x *= a;
	y *= a;
	z *= a;

	return *this;
}

ID_INLINE bool H3DVec3::Compare( const H3DVec3 &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) );
}

ID_INLINE bool H3DVec3::Compare( const H3DVec3 &a, const float epsilon ) const {
	if ( H3DMath::Fabs( x - a.x ) > epsilon ) {
		return false;
	}
			
	if ( H3DMath::Fabs( y - a.y ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( z - a.z ) > epsilon ) {
		return false;
	}

	return true;
}

ID_INLINE bool H3DVec3::operator==( const H3DVec3 &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DVec3::operator!=( const H3DVec3 &a ) const {
	return !Compare( a );
}

ID_INLINE float H3DVec3::NormalizeFast( void ) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z;
	invLength = H3DMath::RSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	z *= invLength;
	return invLength * sqrLength;
}

ID_INLINE bool H3DVec3::FixDegenerateNormal( void ) {
	if ( x == 0.0f ) {
		if ( y == 0.0f ) {
			if ( z > 0.0f ) {
				if ( z != 1.0f ) {
					z = 1.0f;
					return true;
				}
			} else {
				if ( z != -1.0f ) {
					z = -1.0f;
					return true;
				}
			}
			return false;
		} else if ( z == 0.0f ) {
			if ( y > 0.0f ) {
				if ( y != 1.0f ) {
					y = 1.0f;
					return true;
				}
			} else {
				if ( y != -1.0f ) {
					y = -1.0f;
					return true;
				}
			}
			return false;
		}
	} else if ( y == 0.0f ) {
		if ( z == 0.0f ) {
			if ( x > 0.0f ) {
				if ( x != 1.0f ) {
					x = 1.0f;
					return true;
				}
			} else {
				if ( x != -1.0f ) {
					x = -1.0f;
					return true;
				}
			}
			return false;
		}
	}
	if ( H3DMath::Fabs( x ) == 1.0f ) {
		if ( y != 0.0f || z != 0.0f ) {
			y = z = 0.0f;
			return true;
		}
		return false;
	} else if ( H3DMath::Fabs( y ) == 1.0f ) {
		if ( x != 0.0f || z != 0.0f ) {
			x = z = 0.0f;
			return true;
		}
		return false;
	} else if ( H3DMath::Fabs( z ) == 1.0f ) {
		if ( x != 0.0f || y != 0.0f ) {
			x = y = 0.0f;
			return true;
		}
		return false;
	}
	return false;
}

ID_INLINE bool H3DVec3::FixDenormals( void ) {
	bool denormal = false;
	if ( fabs( x ) < 1e-30f ) {
		x = 0.0f;
		denormal = true;
	}
	if ( fabs( y ) < 1e-30f ) {
		y = 0.0f;
		denormal = true;
	}
	if ( fabs( z ) < 1e-30f ) {
		z = 0.0f;
		denormal = true;
	}
	return denormal;
}

ID_INLINE H3DVec3 H3DVec3::Cross( const H3DVec3 &a ) const {
	return H3DVec3( y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x );
}

ID_INLINE H3DVec3 &H3DVec3::Cross( const H3DVec3 &a, const H3DVec3 &b ) {
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;

	return *this;
}

ID_INLINE float H3DVec3::Length( void ) const {
	return ( float )H3DMath::Sqrt( x * x + y * y + z * z );
}

ID_INLINE float H3DVec3::LengthSqr( void ) const {
	return ( x * x + y * y + z * z );
}

ID_INLINE float H3DVec3::LengthFast( void ) const {
	float sqrLength;

	sqrLength = x * x + y * y + z * z;
	return sqrLength * H3DMath::RSqrt( sqrLength );
}

ID_INLINE float H3DVec3::Normalize( void ) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z;
	invLength = H3DMath::InvSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	z *= invLength;
	return invLength * sqrLength;
}

ID_INLINE H3DVec3 &H3DVec3::Truncate( float length ) {
	float length2;
	float ilength;

	if ( !length ) {
		Zero();
	}
	else {
		length2 = LengthSqr();
		if ( length2 > length * length ) {
			ilength = length * H3DMath::InvSqrt( length2 );
			x *= ilength;
			y *= ilength;
			z *= ilength;
		}
	}

	return *this;
}

ID_INLINE void H3DVec3::Clamp( const H3DVec3 &min, const H3DVec3 &max ) {
	if ( x < min.x ) {
		x = min.x;
	} else if ( x > max.x ) {
		x = max.x;
	}
	if ( y < min.y ) {
		y = min.y;
	} else if ( y > max.y ) {
		y = max.y;
	}
	if ( z < min.z ) {
		z = min.z;
	} else if ( z > max.z ) {
		z = max.z;
	}
}

ID_INLINE void H3DVec3::Snap( void ) {
	x = floor( x + 0.5f );
	y = floor( y + 0.5f );
	z = floor( z + 0.5f );
}

ID_INLINE void H3DVec3::SnapInt( void ) {
	x = float( int( x ) );
	y = float( int( y ) );
	z = float( int( z ) );
}

ID_INLINE int H3DVec3::GetDimension( void ) const {
	return 3;
}

ID_INLINE const H3DVec2 &H3DVec3::ToVec2( void ) const {
	return *reinterpret_cast<const H3DVec2 *>(this);
}

ID_INLINE H3DVec2 &H3DVec3::ToVec2( void ) {
	return *reinterpret_cast<H3DVec2 *>(this);
}

ID_INLINE const float *H3DVec3::ToFloatPtr( void ) const {
	return &x;
}

ID_INLINE float *H3DVec3::ToFloatPtr( void ) {
	return &x;
}

ID_INLINE void H3DVec3::NormalVectors( H3DVec3 &left, H3DVec3 &down ) const {
	float d;

	d = x * x + y * y;
	if ( !d ) {
		left[0] = 1;
		left[1] = 0;
		left[2] = 0;
	} else {
		d = H3DMath::InvSqrt( d );
		left[0] = -y * d;
		left[1] = x * d;
		left[2] = 0;
	}
	down = left.Cross( *this );
}

ID_INLINE void H3DVec3::OrthogonalBasis( H3DVec3 &left, H3DVec3 &up ) const {
	float l, s;

	if ( H3DMath::Fabs( z ) > 0.7f ) {
		l = y * y + z * z;
		s = H3DMath::InvSqrt( l );
		up[0] = 0;
		up[1] = z * s;
		up[2] = -y * s;
		left[0] = l * s;
		left[1] = -x * up[2];
		left[2] = x * up[1];
	}
	else {
		l = x * x + y * y;
		s = H3DMath::InvSqrt( l );
		left[0] = -y * s;
		left[1] = x * s;
		left[2] = 0;
		up[0] = -z * left[1];
		up[1] = z * left[0];
		up[2] = l * s;
	}
}

ID_INLINE void H3DVec3::ProjectOntoPlane( const H3DVec3 &normal, const float overBounce ) {
	float backoff;
	
	//backoff = *this * normal;
	backoff = Dot(normal);
	
	if ( overBounce != 1.0 ) {
		if ( backoff < 0 ) {
			backoff *= overBounce;
		} else {
			backoff /= overBounce;
		}
	}

	*this -= backoff * normal;
}

ID_INLINE bool H3DVec3::ProjectAlongPlane( const H3DVec3 &normal, const float epsilon, const float overBounce ) {
	H3DVec3 cross;
	float len;

	cross = this->Cross( normal ).Cross( (*this) );
	// normalize so a fixed epsilon can be used
	cross.Normalize();
	//len = normal * cross;
	len = normal.Dot(cross);
	if ( H3DMath::Fabs( len ) < epsilon ) {
		return false;
	}
	//cross *= overBounce * ( normal * (*this) ) / len;
	cross *= overBounce * ( normal.Dot(*this) ) / len;
	(*this) -= cross;
	return true;
}


//===============================================================
//
//	H3DVec4 - 4D vector
//
//===============================================================

class H3DVec4 {
public:	
	float			x;
	float			y;
	float			z;
	float			w;

					H3DVec4( void );
					explicit H3DVec4( const float x, const float y, const float z, const float w );

	void 			Set( const float x, const float y, const float z, const float w );
	void			Zero( void );

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	H3DVec4			operator-() const;
	float			operator*( const H3DVec4 &a ) const;
	H3DVec4			operator*( const float a ) const;
	H3DVec4			operator/( const float a ) const;
	H3DVec4			operator+( const H3DVec4 &a ) const;
	H3DVec4			operator-( const H3DVec4 &a ) const;
	H3DVec4 &		operator+=( const H3DVec4 &a );
	H3DVec4 &		operator-=( const H3DVec4 &a );
	H3DVec4 &		operator/=( const H3DVec4 &a );
	H3DVec4 &		operator/=( const float a );
	H3DVec4 &		operator*=( const float a );

	friend H3DVec4	operator*( const float a, const H3DVec4 b );

	bool			Compare( const H3DVec4 &a ) const;							// exact compare, no epsilon
	bool			Compare( const H3DVec4 &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const H3DVec4 &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const H3DVec4 &a ) const;						// exact compare, no epsilon

	float			Length( void ) const;
	float			LengthSqr( void ) const;
	float			Normalize( void );			// returns length
	float			NormalizeFast( void );		// returns length

	int				GetDimension( void ) const;

	const H3DVec2 &	ToVec2( void ) const;
	H3DVec2 &		ToVec2( void );
	const H3DVec3 &	ToVec3( void ) const;
	H3DVec3 &		ToVec3( void );
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

	void			Lerp( const H3DVec4 &v1, const H3DVec4 &v2, const float l );

	//============by bird
	H3DVec4 Multiply(const H3DVec4& input)const
	{
		return H3DVec4(x*input.x, y*input.y, z*input.z, w*input.w);
	}
	//================end
};

extern H3DVec4 vec4_origin;
#define vec4_zero vec4_origin

ID_INLINE H3DVec4::H3DVec4( void ) {
}

ID_INLINE H3DVec4::H3DVec4( const float x, const float y, const float z, const float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

ID_INLINE void H3DVec4::Set( const float x, const float y, const float z, const float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

ID_INLINE void H3DVec4::Zero( void ) {
	x = y = z = w = 0.0f;
}

ID_INLINE float H3DVec4::operator[]( int index ) const {
	return ( &x )[ index ];
}

ID_INLINE float& H3DVec4::operator[]( int index ) {
	return ( &x )[ index ];
}

ID_INLINE H3DVec4 H3DVec4::operator-() const {
	return H3DVec4( -x, -y, -z, -w );
}

ID_INLINE H3DVec4 H3DVec4::operator-( const H3DVec4 &a ) const {
	return H3DVec4( x - a.x, y - a.y, z - a.z, w - a.w );
}

ID_INLINE float H3DVec4::operator*( const H3DVec4 &a ) const {
	return x * a.x + y * a.y + z * a.z + w * a.w;
}

ID_INLINE H3DVec4 H3DVec4::operator*( const float a ) const {
	return H3DVec4( x * a, y * a, z * a, w * a );
}

ID_INLINE H3DVec4 H3DVec4::operator/( const float a ) const {
	float inva = 1.0f / a;
	return H3DVec4( x * inva, y * inva, z * inva, w * inva );
}

ID_INLINE H3DVec4 operator*( const float a, const H3DVec4 b ) {
	return H3DVec4( b.x * a, b.y * a, b.z * a, b.w * a );
}

ID_INLINE H3DVec4 H3DVec4::operator+( const H3DVec4 &a ) const {
	return H3DVec4( x + a.x, y + a.y, z + a.z, w + a.w );
}

ID_INLINE H3DVec4 &H3DVec4::operator+=( const H3DVec4 &a ) {
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

ID_INLINE H3DVec4 &H3DVec4::operator/=( const H3DVec4 &a ) {
	x /= a.x;
	y /= a.y;
	z /= a.z;
	w /= a.w;

	return *this;
}

ID_INLINE H3DVec4 &H3DVec4::operator/=( const float a ) {
	float inva = 1.0f / a;
	x *= inva;
	y *= inva;
	z *= inva;
	w *= inva;

	return *this;
}

ID_INLINE H3DVec4 &H3DVec4::operator-=( const H3DVec4 &a ) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

ID_INLINE H3DVec4 &H3DVec4::operator*=( const float a ) {
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
}

ID_INLINE bool H3DVec4::Compare( const H3DVec4 &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) && w == a.w );
}

ID_INLINE bool H3DVec4::Compare( const H3DVec4 &a, const float epsilon ) const {
	if ( H3DMath::Fabs( x - a.x ) > epsilon ) {
		return false;
	}
			
	if ( H3DMath::Fabs( y - a.y ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( z - a.z ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( w - a.w ) > epsilon ) {
		return false;
	}

	return true;
}

ID_INLINE bool H3DVec4::operator==( const H3DVec4 &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DVec4::operator!=( const H3DVec4 &a ) const {
	return !Compare( a );
}

ID_INLINE float H3DVec4::Length( void ) const {
	return ( float )H3DMath::Sqrt( x * x + y * y + z * z + w * w );
}

ID_INLINE float H3DVec4::LengthSqr( void ) const {
	return ( x * x + y * y + z * z + w * w );
}

ID_INLINE float H3DVec4::Normalize( void ) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z + w * w;
	invLength = H3DMath::InvSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	z *= invLength;
	w *= invLength;
	return invLength * sqrLength;
}

ID_INLINE float H3DVec4::NormalizeFast( void ) {
	float sqrLength, invLength;

	sqrLength = x * x + y * y + z * z + w * w;
	invLength = H3DMath::RSqrt( sqrLength );
	x *= invLength;
	y *= invLength;
	z *= invLength;
	w *= invLength;
	return invLength * sqrLength;
}

ID_INLINE int H3DVec4::GetDimension( void ) const {
	return 4;
}

ID_INLINE const H3DVec2 &H3DVec4::ToVec2( void ) const {
	return *reinterpret_cast<const H3DVec2 *>(this);
}

ID_INLINE H3DVec2 &H3DVec4::ToVec2( void ) {
	return *reinterpret_cast<H3DVec2 *>(this);
}

ID_INLINE const H3DVec3 &H3DVec4::ToVec3( void ) const {
	return *reinterpret_cast<const H3DVec3 *>(this);
}

ID_INLINE H3DVec3 &H3DVec4::ToVec3( void ) {
	return *reinterpret_cast<H3DVec3 *>(this);
}

ID_INLINE const float *H3DVec4::ToFloatPtr( void ) const {
	return &x;
}

ID_INLINE float *H3DVec4::ToFloatPtr( void ) {
	return &x;
}


//===============================================================
//
//	H3DVec5 - 5D vector
//
//===============================================================

class H3DVec5 {
public:
	float			x;
	float			y;
	float			z;
	float			s;
	float			t;

					H3DVec5( void );
					explicit H3DVec5( const H3DVec3 &xyz, const H3DVec2 &st );
					explicit H3DVec5( const float x, const float y, const float z, const float s, const float t );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	H3DVec5 &		operator=( const H3DVec3 &a );

	int				GetDimension( void ) const;

	const H3DVec3 &	ToVec3( void ) const;
	H3DVec3 &		ToVec3( void );
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

	void			Lerp( const H3DVec5 &v1, const H3DVec5 &v2, const float l );
};

extern H3DVec5 vec5_origin;
#define vec5_zero vec5_origin

ID_INLINE H3DVec5::H3DVec5( void ) {
}

ID_INLINE H3DVec5::H3DVec5( const H3DVec3 &xyz, const H3DVec2 &st ) {
	x = xyz.x;
	y = xyz.y;
	z = xyz.z;
	s = st[0];
	t = st[1];
}

ID_INLINE H3DVec5::H3DVec5( const float x, const float y, const float z, const float s, const float t ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->s = s;
	this->t = t;
}

ID_INLINE float H3DVec5::operator[]( int index ) const {
	return ( &x )[ index ];
}

ID_INLINE float& H3DVec5::operator[]( int index ) {
	return ( &x )[ index ];
}

ID_INLINE H3DVec5 &H3DVec5::operator=( const H3DVec3 &a ) { 
	x = a.x;
	y = a.y;
	z = a.z;
	s = t = 0;
	return *this;
}

ID_INLINE int H3DVec5::GetDimension( void ) const {
	return 5;
}

ID_INLINE const H3DVec3 &H3DVec5::ToVec3( void ) const {
	return *reinterpret_cast<const H3DVec3 *>(this);
}

ID_INLINE H3DVec3 &H3DVec5::ToVec3( void ) {
	return *reinterpret_cast<H3DVec3 *>(this);
}

ID_INLINE const float *H3DVec5::ToFloatPtr( void ) const {
	return &x;
}

ID_INLINE float *H3DVec5::ToFloatPtr( void ) {
	return &x;
}


//===============================================================
//
//	H3DVec6 - 6D vector
//
//===============================================================

class H3DVec6 {
public:	
					H3DVec6( void );
					explicit H3DVec6( const float *a );
					explicit H3DVec6( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 );

	void 			Set( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 );
	void			Zero( void );

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	H3DVec6			operator-() const;
	H3DVec6			operator*( const float a ) const;
	H3DVec6			operator/( const float a ) const;
	float			operator*( const H3DVec6 &a ) const;
	H3DVec6			operator-( const H3DVec6 &a ) const;
	H3DVec6			operator+( const H3DVec6 &a ) const;
	H3DVec6 &		operator*=( const float a );
	H3DVec6 &		operator/=( const float a );
	H3DVec6 &		operator+=( const H3DVec6 &a );
	H3DVec6 &		operator-=( const H3DVec6 &a );

	friend H3DVec6	operator*( const float a, const H3DVec6 b );

	bool			Compare( const H3DVec6 &a ) const;							// exact compare, no epsilon
	bool			Compare( const H3DVec6 &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const H3DVec6 &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const H3DVec6 &a ) const;						// exact compare, no epsilon

	float			Length( void ) const;
	float			LengthSqr( void ) const;
	float			Normalize( void );			// returns length
	float			NormalizeFast( void );		// returns length

	int				GetDimension( void ) const;

	const H3DVec3 &	SubVec3( int index ) const;
	H3DVec3 &		SubVec3( int index );
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

private:
	float			p[6];
};

extern H3DVec6 vec6_origin;
#define vec6_zero vec6_origin
extern H3DVec6 vec6_infinity;

ID_INLINE H3DVec6::H3DVec6( void ) {
}

ID_INLINE H3DVec6::H3DVec6( const float *a ) {
	memcpy( p, a, 6 * sizeof( float ) );
}

ID_INLINE H3DVec6::H3DVec6( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 ) {
	p[0] = a1;
	p[1] = a2;
	p[2] = a3;
	p[3] = a4;
	p[4] = a5;
	p[5] = a6;
}

ID_INLINE H3DVec6 H3DVec6::operator-() const {
	return H3DVec6( -p[0], -p[1], -p[2], -p[3], -p[4], -p[5] );
}

ID_INLINE float H3DVec6::operator[]( const int index ) const {
	return p[index];
}

ID_INLINE float &H3DVec6::operator[]( const int index ) {
	return p[index];
}

ID_INLINE H3DVec6 H3DVec6::operator*( const float a ) const {
	return H3DVec6( p[0]*a, p[1]*a, p[2]*a, p[3]*a, p[4]*a, p[5]*a );
}

ID_INLINE float H3DVec6::operator*( const H3DVec6 &a ) const {
	return p[0] * a[0] + p[1] * a[1] + p[2] * a[2] + p[3] * a[3] + p[4] * a[4] + p[5] * a[5];
}

ID_INLINE H3DVec6 H3DVec6::operator/( const float a ) const {
	float inva;

	assert( a != 0.0f );
	inva = 1.0f / a;
	return H3DVec6( p[0]*inva, p[1]*inva, p[2]*inva, p[3]*inva, p[4]*inva, p[5]*inva );
}

ID_INLINE H3DVec6 H3DVec6::operator+( const H3DVec6 &a ) const {
	return H3DVec6( p[0] + a[0], p[1] + a[1], p[2] + a[2], p[3] + a[3], p[4] + a[4], p[5] + a[5] );
}

ID_INLINE H3DVec6 H3DVec6::operator-( const H3DVec6 &a ) const {
	return H3DVec6( p[0] - a[0], p[1] - a[1], p[2] - a[2], p[3] - a[3], p[4] - a[4], p[5] - a[5] );
}

ID_INLINE H3DVec6 &H3DVec6::operator*=( const float a ) {
	p[0] *= a;
	p[1] *= a;
	p[2] *= a;
	p[3] *= a;
	p[4] *= a;
	p[5] *= a;
	return *this;
}

ID_INLINE H3DVec6 &H3DVec6::operator/=( const float a ) {
	float inva;

	assert( a != 0.0f );
	inva = 1.0f / a;
	p[0] *= inva;
	p[1] *= inva;
	p[2] *= inva;
	p[3] *= inva;
	p[4] *= inva;
	p[5] *= inva;
	return *this;
}

ID_INLINE H3DVec6 &H3DVec6::operator+=( const H3DVec6 &a ) {
	p[0] += a[0];
	p[1] += a[1];
	p[2] += a[2];
	p[3] += a[3];
	p[4] += a[4];
	p[5] += a[5];
	return *this;
}

ID_INLINE H3DVec6 &H3DVec6::operator-=( const H3DVec6 &a ) {
	p[0] -= a[0];
	p[1] -= a[1];
	p[2] -= a[2];
	p[3] -= a[3];
	p[4] -= a[4];
	p[5] -= a[5];
	return *this;
}

ID_INLINE H3DVec6 operator*( const float a, const H3DVec6 b ) {
	return b * a;
}

ID_INLINE bool H3DVec6::Compare( const H3DVec6 &a ) const {
	return ( ( p[0] == a[0] ) && ( p[1] == a[1] ) && ( p[2] == a[2] ) &&
			( p[3] == a[3] ) && ( p[4] == a[4] ) && ( p[5] == a[5] ) );
}

ID_INLINE bool H3DVec6::Compare( const H3DVec6 &a, const float epsilon ) const {
	if ( H3DMath::Fabs( p[0] - a[0] ) > epsilon ) {
		return false;
	}
			
	if ( H3DMath::Fabs( p[1] - a[1] ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( p[2] - a[2] ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( p[3] - a[3] ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( p[4] - a[4] ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( p[5] - a[5] ) > epsilon ) {
		return false;
	}

	return true;
}

ID_INLINE bool H3DVec6::operator==( const H3DVec6 &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DVec6::operator!=( const H3DVec6 &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DVec6::Set( const float a1, const float a2, const float a3, const float a4, const float a5, const float a6 ) {
	p[0] = a1;
	p[1] = a2;
	p[2] = a3;
	p[3] = a4;
	p[4] = a5;
	p[5] = a6;
}

ID_INLINE void H3DVec6::Zero( void ) {
	p[0] = p[1] = p[2] = p[3] = p[4] = p[5] = 0.0f;
}

ID_INLINE float H3DVec6::Length( void ) const {
	return ( float )H3DMath::Sqrt( p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4] + p[5] * p[5] );
}

ID_INLINE float H3DVec6::LengthSqr( void ) const {
	return ( p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4] + p[5] * p[5] );
}

ID_INLINE float H3DVec6::Normalize( void ) {
	float sqrLength, invLength;

	sqrLength = p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4] + p[5] * p[5];
	invLength = H3DMath::InvSqrt( sqrLength );
	p[0] *= invLength;
	p[1] *= invLength;
	p[2] *= invLength;
	p[3] *= invLength;
	p[4] *= invLength;
	p[5] *= invLength;
	return invLength * sqrLength;
}

ID_INLINE float H3DVec6::NormalizeFast( void ) {
	float sqrLength, invLength;

	sqrLength = p[0] * p[0] + p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4] + p[5] * p[5];
	invLength = H3DMath::RSqrt( sqrLength );
	p[0] *= invLength;
	p[1] *= invLength;
	p[2] *= invLength;
	p[3] *= invLength;
	p[4] *= invLength;
	p[5] *= invLength;
	return invLength * sqrLength;
}

ID_INLINE int H3DVec6::GetDimension( void ) const {
	return 6;
}

ID_INLINE const H3DVec3 &H3DVec6::SubVec3( int index ) const {
	return *reinterpret_cast<const H3DVec3 *>(p + index * 3);
}

ID_INLINE H3DVec3 &H3DVec6::SubVec3( int index ) {
	return *reinterpret_cast<H3DVec3 *>(p + index * 3);
}

ID_INLINE const float *H3DVec6::ToFloatPtr( void ) const {
	return p;
}

ID_INLINE float *H3DVec6::ToFloatPtr( void ) {
	return p;
}


//===============================================================
//
//	H3DVecX - arbitrary sized vector
//
//  The vector lives on 16 byte aligned and 16 byte padded memory.
//
//	NOTE: due to the temporary memory pool H3DVecX cannot be used by multiple threads
//
//===============================================================

#define VECX_MAX_TEMP		1024
#define VECX_QUAD( x )		( ( ( ( x ) + 3 ) & ~3 ) * sizeof( float ) )
#define VECX_CLEAREND()		int s = size; while( s < ( ( s + 3) & ~3 ) ) { p[s++] = 0.0f; }
#define VECX_ALLOCA( n )	( (float *) _alloca16( VECX_QUAD( n ) ) )
#define VECX_SIMD

class H3DVecX {
	friend class H3DMatX;

public:	
					H3DVecX( void );
					explicit H3DVecX( int length );
					explicit H3DVecX( int length, float *data );
					~H3DVecX( void );

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	H3DVecX			operator-() const;
	H3DVecX &		operator=( const H3DVecX &a );
	H3DVecX			operator*( const float a ) const;
	H3DVecX			operator/( const float a ) const;
	float			operator*( const H3DVecX &a ) const;
	H3DVecX			operator-( const H3DVecX &a ) const;
	H3DVecX			operator+( const H3DVecX &a ) const;
	H3DVecX &		operator*=( const float a );
	H3DVecX &		operator/=( const float a );
	H3DVecX &		operator+=( const H3DVecX &a );
	H3DVecX &		operator-=( const H3DVecX &a );

	friend H3DVecX	operator*( const float a, const H3DVecX b );

	bool			Compare( const H3DVecX &a ) const;							// exact compare, no epsilon
	bool			Compare( const H3DVecX &a, const float epsilon ) const;		// compare with epsilon
	bool			operator==(	const H3DVecX &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const H3DVecX &a ) const;						// exact compare, no epsilon

	void			SetSize( int size );
	void			ChangeSize( int size, bool makeZero = false );
	int				GetSize( void ) const { return size; }
	void			SetData( int length, float *data );
	void			Zero( void );
	void			Zero( int length );
	void			Random( int seed, float l = 0.0f, float u = 1.0f );
	void			Random( int length, int seed, float l = 0.0f, float u = 1.0f );
	void			Negate( void );
	void			Clamp( float min, float max );
	H3DVecX &		SwapElements( int e1, int e2 );

	float			Length( void ) const;
	float			LengthSqr( void ) const;
	H3DVecX			Normalize( void ) const;
	float			NormalizeSelf( void );

	int				GetDimension( void ) const;

	const H3DVec3 &	SubVec3( int index ) const;
	H3DVec3 &		SubVec3( int index );
	const H3DVec6 &	SubVec6( int index ) const;
	H3DVec6 &		SubVec6( int index );
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

private:
	int				size;					// size of the vector
	int				alloced;				// if -1 p points to data set with SetData
	float *			p;						// memory the vector is stored

	static float	temp[VECX_MAX_TEMP+4];	// used to store intermediate results
	static float *	tempPtr;				// pointer to 16 byte aligned temporary memory
	static int		tempIndex;				// index into memory pool, wraps around

private:
	void			SetTempSize( int size );
};


ID_INLINE H3DVecX::H3DVecX( void ) {
	size = alloced = 0;
	p = (float*)NULL;
}

ID_INLINE H3DVecX::H3DVecX( int length ) {
	size = alloced = 0;
	p = (float*)NULL;
	SetSize( length );
}

ID_INLINE H3DVecX::H3DVecX( int length, float *data ) {
	size = alloced = 0;
	p = (float*)NULL;
	SetData( length, data );
}

ID_INLINE H3DVecX::~H3DVecX( void ) {
	// if not temp memory
	if ( p && ( p < H3DVecX::tempPtr || p >= H3DVecX::tempPtr + VECX_MAX_TEMP ) && alloced != -1 ) {
		Mem_Free16( p );
	}
}

ID_INLINE float H3DVecX::operator[]( const int index ) const {
	assert( index >= 0 && index < size );
	return p[index];
}

ID_INLINE float &H3DVecX::operator[]( const int index ) {
	assert( index >= 0 && index < size );
	return p[index];
}

ID_INLINE H3DVecX H3DVecX::operator-() const {
	int i;
	H3DVecX m;

	m.SetTempSize( size );
	for ( i = 0; i < size; i++ ) {
		m.p[i] = -p[i];
	}
	return m;
}

ID_INLINE H3DVecX &H3DVecX::operator=( const H3DVecX &a ) { 
	SetSize( a.size );
#ifdef VECX_SIMD
	SIMDProcessor->Copy16( p, a.p, a.size );
#else
	memcpy( p, a.p, a.size * sizeof( float ) );
#endif
	H3DVecX::tempIndex = 0;
	return *this;
}

ID_INLINE H3DVecX H3DVecX::operator+( const H3DVecX &a ) const {
	H3DVecX m;

	assert( size == a.size );
	m.SetTempSize( size );
#ifdef VECX_SIMD
	SIMDProcessor->Add16( m.p, p, a.p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		m.p[i] = p[i] + a.p[i];
	}
#endif
	return m;
}

ID_INLINE H3DVecX H3DVecX::operator-( const H3DVecX &a ) const {
	H3DVecX m;

	assert( size == a.size );
	m.SetTempSize( size );
#ifdef VECX_SIMD
	SIMDProcessor->Sub16( m.p, p, a.p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		m.p[i] = p[i] - a.p[i];
	}
#endif
	return m;
}

ID_INLINE H3DVecX &H3DVecX::operator+=( const H3DVecX &a ) {
	assert( size == a.size );
#ifdef VECX_SIMD
	SIMDProcessor->AddAssign16( p, a.p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		p[i] += a.p[i];
	}
#endif
	H3DVecX::tempIndex = 0;
	return *this;
}

ID_INLINE H3DVecX &H3DVecX::operator-=( const H3DVecX &a ) {
	assert( size == a.size );
#ifdef VECX_SIMD
	SIMDProcessor->SubAssign16( p, a.p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		p[i] -= a.p[i];
	}
#endif
	H3DVecX::tempIndex = 0;
	return *this;
}

ID_INLINE H3DVecX H3DVecX::operator*( const float a ) const {
	H3DVecX m;

	m.SetTempSize( size );
#ifdef VECX_SIMD
	SIMDProcessor->Mul16( m.p, p, a, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		m.p[i] = p[i] * a;
	}
#endif
	return m;
}

ID_INLINE H3DVecX &H3DVecX::operator*=( const float a ) {
#ifdef VECX_SIMD
	SIMDProcessor->MulAssign16( p, a, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		p[i] *= a;
	}
#endif
	return *this;
}

ID_INLINE H3DVecX H3DVecX::operator/( const float a ) const {
	assert( a != 0.0f );
	return (*this) * ( 1.0f / a );
}

ID_INLINE H3DVecX &H3DVecX::operator/=( const float a ) {
	assert( a != 0.0f );
	(*this) *= ( 1.0f / a );
	return *this;
}

ID_INLINE H3DVecX operator*( const float a, const H3DVecX b ) {
	return b * a;
}

ID_INLINE float H3DVecX::operator*( const H3DVecX &a ) const {
	int i;
	float sum = 0.0f;

	assert( size == a.size );
	for ( i = 0; i < size; i++ ) {
		sum += p[i] * a.p[i];
	}
	return sum;
}

ID_INLINE bool H3DVecX::Compare( const H3DVecX &a ) const {
	int i;

	assert( size == a.size );
	for ( i = 0; i < size; i++ ) {
		if ( p[i] != a.p[i] ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DVecX::Compare( const H3DVecX &a, const float epsilon ) const {
	int i;

	assert( size == a.size );
	for ( i = 0; i < size; i++ ) {
		if ( H3DMath::Fabs( p[i] - a.p[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DVecX::operator==( const H3DVecX &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DVecX::operator!=( const H3DVecX &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DVecX::SetSize( int newSize ) {
	int alloc = ( newSize + 3 ) & ~3;
	if ( alloc > alloced && alloced != -1 ) {
		if ( p ) {
			Mem_Free16( p );
		}
		p = (float *) Mem_Alloc16( alloc * sizeof( float ) );
		alloced = alloc;
	}
	size = newSize;
	VECX_CLEAREND();
}

ID_INLINE void H3DVecX::ChangeSize( int newSize, bool makeZero ) {
	int alloc = ( newSize + 3 ) & ~3;
	if ( alloc > alloced && alloced != -1 ) {
		float *oldVec = p;
		p = (float *) Mem_Alloc16( alloc * sizeof( float ) );
		alloced = alloc;
		if ( oldVec ) {
			for ( int i = 0; i < size; i++ ) {
				p[i] = oldVec[i];
			}
			Mem_Free16( oldVec );
		}
		if ( makeZero ) {
			// zero any new elements
			for ( int i = size; i < newSize; i++ ) {
				p[i] = 0.0f;
			}
		}
	}
	size = newSize;
	VECX_CLEAREND();
}

ID_INLINE void H3DVecX::SetTempSize( int newSize ) {

	size = newSize;
	alloced = ( newSize + 3 ) & ~3;
	assert( alloced < VECX_MAX_TEMP );
	if ( H3DVecX::tempIndex + alloced > VECX_MAX_TEMP ) {
		H3DVecX::tempIndex = 0;
	}
	p = H3DVecX::tempPtr + H3DVecX::tempIndex;
	H3DVecX::tempIndex += alloced;
	VECX_CLEAREND();
}

ID_INLINE void H3DVecX::SetData( int length, float *data ) {
	if ( p && ( p < H3DVecX::tempPtr || p >= H3DVecX::tempPtr + VECX_MAX_TEMP ) && alloced != -1 ) {
		Mem_Free16( p );
	}
	assert( ( ( (int) data ) & 15 ) == 0 ); // data must be 16 byte aligned
	p = data;
	size = length;
	alloced = -1;
	VECX_CLEAREND();
}

ID_INLINE void H3DVecX::Zero( void ) {
#ifdef VECX_SIMD
	SIMDProcessor->Zero16( p, size );
#else
	memset( p, 0, size * sizeof( float ) );
#endif
}

ID_INLINE void H3DVecX::Zero( int length ) {
	SetSize( length );
#ifdef VECX_SIMD
	SIMDProcessor->Zero16( p, length );
#else
	memset( p, 0, size * sizeof( float ) );
#endif
}

ID_INLINE void H3DVecX::Random( int seed, float l, float u ) {
	int i;
	float c;
	H3DRandom rnd( seed );

	c = u - l;
	for ( i = 0; i < size; i++ ) {
		p[i] = l + rnd.RandomFloat() * c;
	}
}

ID_INLINE void H3DVecX::Random( int length, int seed, float l, float u ) {
	int i;
	float c;
	H3DRandom rnd( seed );

	SetSize( length );
	c = u - l;
	for ( i = 0; i < size; i++ ) {
		p[i] = l + rnd.RandomFloat() * c;
	}
}

ID_INLINE void H3DVecX::Negate( void ) {
#ifdef VECX_SIMD
	SIMDProcessor->Negate16( p, size );
#else
	int i;
	for ( i = 0; i < size; i++ ) {
		p[i] = -p[i];
	}
#endif
}

ID_INLINE void H3DVecX::Clamp( float min, float max ) {
	int i;
	for ( i = 0; i < size; i++ ) {
		if ( p[i] < min ) {
			p[i] = min;
		} else if ( p[i] > max ) {
			p[i] = max;
		}
	}
}

ID_INLINE H3DVecX &H3DVecX::SwapElements( int e1, int e2 ) {
	float tmp;
	tmp = p[e1];
	p[e1] = p[e2];
	p[e2] = tmp;
	return *this;
}

ID_INLINE float H3DVecX::Length( void ) const {
	int i;
	float sum = 0.0f;

	for ( i = 0; i < size; i++ ) {
		sum += p[i] * p[i];
	}
	return H3DMath::Sqrt( sum );
}

ID_INLINE float H3DVecX::LengthSqr( void ) const {
	int i;
	float sum = 0.0f;

	for ( i = 0; i < size; i++ ) {
		sum += p[i] * p[i];
	}
	return sum;
}

ID_INLINE H3DVecX H3DVecX::Normalize( void ) const {
	int i;
	H3DVecX m;
	float invSqrt, sum = 0.0f;

	m.SetTempSize( size );
	for ( i = 0; i < size; i++ ) {
		sum += p[i] * p[i];
	}
	invSqrt = H3DMath::InvSqrt( sum );
	for ( i = 0; i < size; i++ ) {
		m.p[i] = p[i] * invSqrt;
	}
	return m;
}

ID_INLINE float H3DVecX::NormalizeSelf( void ) {
	float invSqrt, sum = 0.0f;
	int i;
	for ( i = 0; i < size; i++ ) {
		sum += p[i] * p[i];
	}
	invSqrt = H3DMath::InvSqrt( sum );
	for ( i = 0; i < size; i++ ) {
		p[i] *= invSqrt;
	}
	return invSqrt * sum;
}

ID_INLINE int H3DVecX::GetDimension( void ) const {
	return size;
}

ID_INLINE H3DVec3 &H3DVecX::SubVec3( int index ) {
	assert( index >= 0 && index * 3 + 3 <= size );
	return *reinterpret_cast<H3DVec3 *>(p + index * 3);
}

ID_INLINE const H3DVec3 &H3DVecX::SubVec3( int index ) const {
	assert( index >= 0 && index * 3 + 3 <= size );
	return *reinterpret_cast<const H3DVec3 *>(p + index * 3);
}

ID_INLINE H3DVec6 &H3DVecX::SubVec6( int index ) {
	assert( index >= 0 && index * 6 + 6 <= size );
	return *reinterpret_cast<H3DVec6 *>(p + index * 6);
}

ID_INLINE const H3DVec6 &H3DVecX::SubVec6( int index ) const {
	assert( index >= 0 && index * 6 + 6 <= size );
	return *reinterpret_cast<const H3DVec6 *>(p + index * 6);
}

ID_INLINE const float *H3DVecX::ToFloatPtr( void ) const {
	return p;
}

ID_INLINE float *H3DVecX::ToFloatPtr( void ) {
	return p;
}


//===============================================================
//
//	idPolar3
//
//===============================================================

class idPolar3 {
public:	
	float			radius, theta, phi;

					idPolar3( void );
					explicit idPolar3( const float radius, const float theta, const float phi );

	void 			Set( const float radius, const float theta, const float phi );

	float			operator[]( const int index ) const;
	float &			operator[]( const int index );
	idPolar3		operator-() const;
	idPolar3 &		operator=( const idPolar3 &a );

	H3DVec3			ToVec3( void ) const;
};

ID_INLINE idPolar3::idPolar3( void ) {
}

ID_INLINE idPolar3::idPolar3( const float radius, const float theta, const float phi ) {
	assert( radius > 0 );
	this->radius = radius;
	this->theta = theta;
	this->phi = phi;
}
	
ID_INLINE void idPolar3::Set( const float radius, const float theta, const float phi ) {
	assert( radius > 0 );
	this->radius = radius;
	this->theta = theta;
	this->phi = phi;
}

ID_INLINE float idPolar3::operator[]( const int index ) const {
	return ( &radius )[ index ];
}

ID_INLINE float &idPolar3::operator[]( const int index ) {
	return ( &radius )[ index ];
}

ID_INLINE idPolar3 idPolar3::operator-() const {
	return idPolar3( radius, -theta, -phi );
}

ID_INLINE idPolar3 &idPolar3::operator=( const idPolar3 &a ) { 
	radius = a.radius;
	theta = a.theta;
	phi = a.phi;
	return *this;
}

ID_INLINE H3DVec3 idPolar3::ToVec3( void ) const {
	float sp, cp, st, ct;
	H3DMath::SinCos( phi, sp, cp );
	H3DMath::SinCos( theta, st, ct );
 	return H3DVec3( cp * radius * ct, cp * radius * st, radius * sp );
}

// by wh
// from <geometric tools for computer graphics>
float TrianglePointMinDistance(const H3DVec3& v0, const H3DVec3& v1, const H3DVec3& v2, const H3DVec3& P, H3DVec3& minDistTriPoint);
/*
===============================================================================

	Old 3D vector macros, should no longer be used.

===============================================================================
*/

#define DotProduct( a, b)			((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VectorSubtract( a, b, c )	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd( a, b, c )		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define	VectorScale( v, s, o )		((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA( v, s, b, o )		((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorCopy( a, b )			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])


#endif /* !__MATH_VECTOR_H__ */
