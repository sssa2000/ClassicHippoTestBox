// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_QUAT_H__
#define __MATH_QUAT_H__

/*
===============================================================================

	H3DQuat

===============================================================================
*/


class H3DVec3;
class H3DAngles;
class H3DRotation;
class H3DMat3;
class H3DMat4;
class H3DCQuat;

class H3DQuat {
public:
	float			x;
	float			y;
	float			z;
	float			w;

					H3DQuat( void );
					H3DQuat( float x, float y, float z, float w );

	void 			Set( float x, float y, float z, float w );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	H3DQuat			operator-() const;
	H3DQuat &		operator=( const H3DQuat &a );
	H3DQuat			operator+( const H3DQuat &a ) const;
	H3DQuat &		operator+=( const H3DQuat &a );
	H3DQuat			operator-( const H3DQuat &a ) const;
	H3DQuat &		operator-=( const H3DQuat &a );
	H3DQuat			operator*( const H3DQuat &a ) const;
	H3DVec3			operator*( const H3DVec3 &a ) const;
	H3DQuat			operator*( float a ) const;
	H3DQuat &		operator*=( const H3DQuat &a );
	H3DQuat &		operator*=( float a );

	friend H3DQuat	operator*( const float a, const H3DQuat &b );
	friend H3DVec3	operator*( const H3DVec3 &a, const H3DQuat &b );

	bool			Compare( const H3DQuat &a ) const;						// exact compare, no epsilon
	bool			Compare( const H3DQuat &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const H3DQuat &a ) const;					// exact compare, no epsilon
	bool			operator!=(	const H3DQuat &a ) const;					// exact compare, no epsilon

	H3DQuat			Inverse( void ) const;
	float			Length( void ) const;
	H3DQuat &		Normalize( void );

	float			CalcW( void ) const;
	int				GetDimension( void ) const;

	H3DAngles		ToAngles( void ) const;
	H3DRotation		ToRotation( void ) const;
	H3DMat3			ToMat3( void ) const;
	H3DMat4			ToMat4( void ) const;
	H3DCQuat			ToCQuat( void ) const;
	H3DVec3			ToAngularVelocity( void ) const;
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

	H3DQuat &		Slerp( const H3DQuat &from, const H3DQuat &to, float t );
	//======by wh============
	void Identity()
	{
		Set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void FromAngleAxis(float degree, const H3DVec3& axis);

	void GetRotationTo(const H3DVec3& From, const H3DVec3& To);

	static const H3DQuat& GetIdentity(void)
	{
		const static H3DQuat quat_identity(0.0f, 0.0f, 0.0f, 1.0f);
		return quat_identity;
	}

	void StripX(const H3DVec3& input);//将input选转到YZ平面
	void StripY(const H3DVec3& input);//将input选转到XZ平面
	void StripZ(const H3DVec3& input);//将input选转到XY平面
	//======by wh end============

	//=========by bird ======================
	static H3DQuat Squad (float fT,
		const H3DQuat& rkP, const H3DQuat& rkA,
		const H3DQuat& rkB, const H3DQuat& rkQ);

	static H3DQuat Lerp(const H3DQuat &q1,const H3DQuat &q2,float t);

	static H3DQuat QslerpNoInvert(const H3DQuat &q1,const H3DQuat &q2,float t);
	
	H3DQuat Loga () const;

	H3DQuat Exp() const;


	//=========by bird end===================
};

//extern H3DQuat quat_identity;

ID_INLINE H3DQuat::H3DQuat( void ) {
}

ID_INLINE H3DQuat::H3DQuat( float x, float y, float z, float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

ID_INLINE float H3DQuat::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
}

ID_INLINE float& H3DQuat::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 4 ) );
	return ( &x )[ index ];
}

ID_INLINE H3DQuat H3DQuat::operator-() const {
	return H3DQuat( -x, -y, -z, -w );
}

ID_INLINE H3DQuat &H3DQuat::operator=( const H3DQuat &a ) {
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;

	return *this;
}

ID_INLINE H3DQuat H3DQuat::operator+( const H3DQuat &a ) const {
	return H3DQuat( x + a.x, y + a.y, z + a.z, w + a.w );
}

ID_INLINE H3DQuat& H3DQuat::operator+=( const H3DQuat &a ) {
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

ID_INLINE H3DQuat H3DQuat::operator-( const H3DQuat &a ) const {
	return H3DQuat( x - a.x, y - a.y, z - a.z, w - a.w );
}

ID_INLINE H3DQuat& H3DQuat::operator-=( const H3DQuat &a ) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

ID_INLINE H3DQuat H3DQuat::operator*( const H3DQuat &a ) const {
	return H3DQuat(	w*a.x + x*a.w + y*a.z - z*a.y,
					w*a.y + y*a.w + z*a.x - x*a.z,
					w*a.z + z*a.w + x*a.y - y*a.x,
					w*a.w - x*a.x - y*a.y - z*a.z );
}

ID_INLINE H3DVec3 H3DQuat::operator*( const H3DVec3 &a ) const {
#if 0
	// it's faster to do the conversion to a 3x3 matrix and multiply the vector by this 3x3 matrix
	return ( ToMat3() * a );
#else
	// result = this->Inverse() * H3DQuat( a.x, a.y, a.z, 0.0f ) * (*this)

	//float xxzz = x*x - z*z;
	//float wwyy = w*w - y*y;

	//float xw2 = x*w*2.0f;
	//float xy2 = x*y*2.0f;
	//float xz2 = x*z*2.0f;
	//float yw2 = y*w*2.0f;
	//float yz2 = y*z*2.0f;
	//float zw2 = z*w*2.0f;

	//return H3DVec3(
	//	(xxzz + wwyy)*a.x		+ (xy2 + zw2)*a.y		+ (xz2 - yw2)*a.z,
	//	(xy2 - zw2)*a.x			+ (xxzz - wwyy)*a.y		+ (yz2 + xw2)*a.z,
	//	(xz2 + yw2)*a.x			+ (yz2 - xw2)*a.y		+ (wwyy - xxzz)*a.z
	//);

	H3DVec3 uv, uuv; 
	H3DVec3 qvec(x, y, z);
	uv = qvec.Cross(a); 
	uuv = qvec.Cross(uv); 
	uv *= (2.0f * w); 
	uuv *= 2.0f; 

	return a + uv + uuv;
#endif
}

ID_INLINE H3DQuat H3DQuat::operator*( float a ) const {
	return H3DQuat( x * a, y * a, z * a, w * a );
}

ID_INLINE H3DQuat operator*( const float a, const H3DQuat &b ) {
	return b * a;
}

ID_INLINE H3DVec3 operator*( const H3DVec3 &a, const H3DQuat &b ) {
	return b * a;
}

ID_INLINE H3DQuat& H3DQuat::operator*=( const H3DQuat &a ) {
	*this = *this * a;

	return *this;
}

ID_INLINE H3DQuat& H3DQuat::operator*=( float a ) {
	x *= a;
	y *= a;
	z *= a;
	w *= a;

	return *this;
}

ID_INLINE bool H3DQuat::Compare( const H3DQuat &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) && ( w == a.w ) );
}

ID_INLINE bool H3DQuat::Compare( const H3DQuat &a, const float epsilon ) const {
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

ID_INLINE bool H3DQuat::operator==( const H3DQuat &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DQuat::operator!=( const H3DQuat &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DQuat::Set( float x, float y, float z, float w ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

ID_INLINE H3DQuat H3DQuat::Inverse( void ) const {
	return H3DQuat( -x, -y, -z, w );
}

ID_INLINE float H3DQuat::Length( void ) const {
	float len;

	len = x * x + y * y + z * z + w * w;
	return H3DMath::Sqrt( len );
}

ID_INLINE H3DQuat& H3DQuat::Normalize( void ) {
	float len;
	float ilength;

	len = this->Length();
	if ( len ) {
		ilength = 1 / len;
		x *= ilength;
		y *= ilength;
		z *= ilength;
		w *= ilength;
	}
	return *this;
}

ID_INLINE float H3DQuat::CalcW( void ) const {
	// take the absolute value because floating point rounding may cause the dot of x,y,z to be larger than 1
	return sqrt( fabs( 1.0f - ( x * x + y * y + z * z ) ) );
}

ID_INLINE int H3DQuat::GetDimension( void ) const {
	return 4;
}

ID_INLINE const float *H3DQuat::ToFloatPtr( void ) const {
	return &x;
}

ID_INLINE float *H3DQuat::ToFloatPtr( void ) {
	return &x;
}


/*
===============================================================================

	Compressed H3DQuat

===============================================================================
*/

class H3DCQuat {
public:
	float			x;
	float			y;
	float			z;

					H3DCQuat( void );
					H3DCQuat( float x, float y, float z );

	void 			Set( float x, float y, float z );

	float			operator[]( int index ) const;
	float &			operator[]( int index );

	bool			Compare( const H3DCQuat &a ) const;						// exact compare, no epsilon
	bool			Compare( const H3DCQuat &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const H3DCQuat &a ) const;					// exact compare, no epsilon
	bool			operator!=(	const H3DCQuat &a ) const;					// exact compare, no epsilon

	int				GetDimension( void ) const;

	H3DAngles		ToAngles( void ) const;
	H3DRotation		ToRotation( void ) const;
	H3DMat3			ToMat3( void ) const;
	H3DMat4			ToMat4( void ) const;
	H3DQuat			ToQuat( void ) const;
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;
};

ID_INLINE H3DCQuat::H3DCQuat( void ) {
}

ID_INLINE H3DCQuat::H3DCQuat( float x, float y, float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

ID_INLINE void H3DCQuat::Set( float x, float y, float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

ID_INLINE float H3DCQuat::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
}

ID_INLINE float& H3DCQuat::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &x )[ index ];
}

ID_INLINE bool H3DCQuat::Compare( const H3DCQuat &a ) const {
	return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) );
}

ID_INLINE bool H3DCQuat::Compare( const H3DCQuat &a, const float epsilon ) const {
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

ID_INLINE bool H3DCQuat::operator==( const H3DCQuat &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DCQuat::operator!=( const H3DCQuat &a ) const {
	return !Compare( a );
}

ID_INLINE int H3DCQuat::GetDimension( void ) const {
	return 3;
}

ID_INLINE H3DQuat H3DCQuat::ToQuat( void ) const {
	// take the absolute value because floating point rounding may cause the dot of x,y,z to be larger than 1
	return H3DQuat( x, y, z, sqrt( fabs( 1.0f - ( x * x + y * y + z * z ) ) ) );
}

ID_INLINE const float *H3DCQuat::ToFloatPtr( void ) const {
	return &x;
}

ID_INLINE float *H3DCQuat::ToFloatPtr( void ) {
	return &x;
}

#endif /* !__MATH_QUAT_H__ */
