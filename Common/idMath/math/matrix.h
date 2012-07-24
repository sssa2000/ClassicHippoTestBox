// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_MATRIX_H__
#define __MATH_MATRIX_H__

/*
===============================================================================

  Matrix classes, all matrices are row-major except H3DMat3

===============================================================================
*/

#define MATRIX_INVERSE_EPSILON		1e-14
#define MATRIX_EPSILON				1e-6

class H3DAngles;
class H3DQuat;
class H3DCQuat;
class H3DRotation;
class H3DMat4;

//===============================================================
//
//	H3DMat2 - 2x2 matrix
//
//===============================================================

class H3DMat2 {
public:
					H3DMat2( void );
					explicit H3DMat2( const H3DVec2 &x, const H3DVec2 &y );
					explicit H3DMat2( const float xx, const float xy, const float yx, const float yy );
					explicit H3DMat2( const float src[ 2 ][ 2 ] );

	const H3DVec2 &	operator[]( int index ) const;
	H3DVec2 &		operator[]( int index );
	H3DMat2			operator-() const;
	H3DMat2			operator*( const float a ) const;
	H3DVec2			operator*( const H3DVec2 &vec ) const;
	H3DMat2			operator*( const H3DMat2 &a ) const;
	H3DMat2			operator+( const H3DMat2 &a ) const;
	H3DMat2			operator-( const H3DMat2 &a ) const;
	H3DMat2 &		operator*=( const float a );
	H3DMat2 &		operator*=( const H3DMat2 &a );
	H3DMat2 &		operator+=( const H3DMat2 &a );
	H3DMat2 &		operator-=( const H3DMat2 &a );

	friend H3DMat2	operator*( const float a, const H3DMat2 &mat );
	friend H3DVec2	operator*( const H3DVec2 &vec, const H3DMat2 &mat );
	friend H3DVec2 &	operator*=( H3DVec2 &vec, const H3DMat2 &mat );

	bool			Compare( const H3DMat2 &a ) const;						// exact compare, no epsilon
	bool			Compare( const H3DMat2 &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const H3DMat2 &a ) const;					// exact compare, no epsilon
	bool			operator!=( const H3DMat2 &a ) const;					// exact compare, no epsilon

	void			Zero( void );
	void			Identity( void );
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;

	float			Trace( void ) const;
	float			Determinant( void ) const;
	H3DMat2			Transpose( void ) const;	// returns transpose
	H3DMat2 &		TransposeSelf( void );
	H3DMat2			Inverse( void ) const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf( void );		// returns false if determinant is zero
	H3DMat2			InverseFast( void ) const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf( void );	// returns false if determinant is zero

	int				GetDimension( void ) const;

	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

	static const H3DMat2& GetIdentity(void)
	{
		const static H3DMat2 mat2_identity( H3DVec2( 1, 0), H3DVec2( 0, 1));
		return mat2_identity;
	}

	static const H3DMat2& GetZero(void)
	{
		const static H3DMat2 mat2_zero( H3DVec2( 0, 0), H3DVec2( 0, 0));
		return mat2_zero;
	}

private:
	H3DVec2			mat[ 2 ];
	//static H3DMat2 GetIdentity();
	//static H3DMat2 mat2_zero;
};

//extern H3DMat2 mat2_zero;
//extern H3DMat2 GetIdentity();
//#define mat2_default	GetIdentity()

ID_INLINE H3DMat2::H3DMat2( void ) {
}

ID_INLINE H3DMat2::H3DMat2( const H3DVec2 &x, const H3DVec2 &y ) {
	mat[ 0 ].x = x.x; mat[ 0 ].y = x.y;
	mat[ 1 ].x = y.x; mat[ 1 ].y = y.y;
}

ID_INLINE H3DMat2::H3DMat2( const float xx, const float xy, const float yx, const float yy ) {
	mat[ 0 ].x = xx; mat[ 0 ].y = xy;
	mat[ 1 ].x = yx; mat[ 1 ].y = yy;
}

ID_INLINE H3DMat2::H3DMat2( const float src[ 2 ][ 2 ] ) {
	memcpy( mat, src, 2 * 2 * sizeof( float ) );
}

ID_INLINE const H3DVec2 &H3DMat2::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 2 ) );
	return mat[ index ];
}

ID_INLINE H3DVec2 &H3DMat2::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 2 ) );
	return mat[ index ];
}

ID_INLINE H3DMat2 H3DMat2::operator-() const {
	return H3DMat2(	-mat[0][0], -mat[0][1],
					-mat[1][0], -mat[1][1] );
}

ID_INLINE H3DVec2 H3DMat2::operator*( const H3DVec2 &vec ) const {
	return H3DVec2(
		mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y,
		mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y );
}

ID_INLINE H3DMat2 H3DMat2::operator*( const H3DMat2 &a ) const {
	return H3DMat2(
		mat[0].x * a[0].x + mat[0].y * a[1].x,
		mat[0].x * a[0].y + mat[0].y * a[1].y,
		mat[1].x * a[0].x + mat[1].y * a[1].x,
		mat[1].x * a[0].y + mat[1].y * a[1].y );
}

ID_INLINE H3DMat2 H3DMat2::operator*( const float a ) const {
	return H3DMat2(
		mat[0].x * a, mat[0].y * a, 
		mat[1].x * a, mat[1].y * a );
}

ID_INLINE H3DMat2 H3DMat2::operator+( const H3DMat2 &a ) const {
	return H3DMat2(
		mat[0].x + a[0].x, mat[0].y + a[0].y, 
		mat[1].x + a[1].x, mat[1].y + a[1].y );
}
    
ID_INLINE H3DMat2 H3DMat2::operator-( const H3DMat2 &a ) const {
	return H3DMat2(
		mat[0].x - a[0].x, mat[0].y - a[0].y,
		mat[1].x - a[1].x, mat[1].y - a[1].y );
}

ID_INLINE H3DMat2 &H3DMat2::operator*=( const float a ) {
	mat[0].x *= a; mat[0].y *= a;
	mat[1].x *= a; mat[1].y *= a;

    return *this;
}

ID_INLINE H3DMat2 &H3DMat2::operator*=( const H3DMat2 &a ) {
	float x, y;
	x = mat[0].x; y = mat[0].y;
	mat[0].x = x * a[0].x + y * a[1].x;
	mat[0].y = x * a[0].y + y * a[1].y;
	x = mat[1].x; y = mat[1].y;
	mat[1].x = x * a[0].x + y * a[1].x;
	mat[1].y = x * a[0].y + y * a[1].y;
	return *this;
}

ID_INLINE H3DMat2 &H3DMat2::operator+=( const H3DMat2 &a ) {
	mat[0].x += a[0].x; mat[0].y += a[0].y;
	mat[1].x += a[1].x; mat[1].y += a[1].y;

    return *this;
}

ID_INLINE H3DMat2 &H3DMat2::operator-=( const H3DMat2 &a ) {
	mat[0].x -= a[0].x; mat[0].y -= a[0].y;
	mat[1].x -= a[1].x; mat[1].y -= a[1].y;

    return *this;
}

ID_INLINE H3DVec2 operator*( const H3DVec2 &vec, const H3DMat2 &mat ) {
	return mat * vec;
}

ID_INLINE H3DMat2 operator*( const float a, H3DMat2 const &mat ) {
	return mat * a;
}

ID_INLINE H3DVec2 &operator*=( H3DVec2 &vec, const H3DMat2 &mat ) {
	vec = mat * vec;
	return vec;
}

ID_INLINE bool H3DMat2::Compare( const H3DMat2 &a ) const {
	if ( mat[0].Compare( a[0] ) &&
		mat[1].Compare( a[1] ) ) {
		return true;
	}
	return false;
}

ID_INLINE bool H3DMat2::Compare( const H3DMat2 &a, const float epsilon ) const {
	if ( mat[0].Compare( a[0], epsilon ) &&
		mat[1].Compare( a[1], epsilon ) ) {
		return true;
	}
	return false;
}

ID_INLINE bool H3DMat2::operator==( const H3DMat2 &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DMat2::operator!=( const H3DMat2 &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DMat2::Zero( void ) {
	mat[0].Zero();
	mat[1].Zero();
}

ID_INLINE void H3DMat2::Identity( void ) {
	*this = GetIdentity();
}

ID_INLINE bool H3DMat2::IsIdentity( const float epsilon ) const {
	const static H3DMat2 identity(H3DVec2(1.0f, 0.0f), H3DVec2(0.0f, 1.0f));
	return Compare( identity, epsilon );
}

ID_INLINE bool H3DMat2::IsSymmetric( const float epsilon ) const {
	return ( H3DMath::Fabs( mat[0][1] - mat[1][0] ) < epsilon );
}

ID_INLINE bool H3DMat2::IsDiagonal( const float epsilon ) const {
	if ( H3DMath::Fabs( mat[0][1] ) > epsilon ||
		H3DMath::Fabs( mat[1][0] ) > epsilon ) {
		return false;
	}
	return true;
}

ID_INLINE float H3DMat2::Trace( void ) const {
	return ( mat[0][0] + mat[1][1] );
}

ID_INLINE float H3DMat2::Determinant( void ) const {
	return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

ID_INLINE H3DMat2 H3DMat2::Transpose( void ) const {
	return H3DMat2(	mat[0][0], mat[1][0],
					mat[0][1], mat[1][1] );
}

ID_INLINE H3DMat2 &H3DMat2::TransposeSelf( void ) {
	float tmp;

	tmp = mat[0][1];
	mat[0][1] = mat[1][0];
	mat[1][0] = tmp;

	return *this;
}

ID_INLINE H3DMat2 H3DMat2::Inverse( void ) const {
	H3DMat2 invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

ID_INLINE H3DMat2 H3DMat2::InverseFast( void ) const {
	H3DMat2 invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

ID_INLINE int H3DMat2::GetDimension( void ) const {
	return 4;
}

ID_INLINE const float *H3DMat2::ToFloatPtr( void ) const {
	return mat[0].ToFloatPtr();
}

ID_INLINE float *H3DMat2::ToFloatPtr( void ) {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	H3DMat3 - 3x3 matrix
//
//	NOTE:	matrix is column-major
//
//===============================================================

class H3DMat3 {
public:
					H3DMat3( void );
					explicit H3DMat3( const H3DVec3 &x, const H3DVec3 &y, const H3DVec3 &z );
					explicit H3DMat3( const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz );
					explicit H3DMat3( const float src[ 3 ][ 3 ] );

	const H3DVec3 &	operator[]( int index ) const;
	H3DVec3 &		operator[]( int index );
	H3DMat3			operator-() const;
	H3DMat3			operator*( const float a ) const;
	H3DVec3			operator*( const H3DVec3 &vec ) const;
	H3DMat3			operator*( const H3DMat3 &a ) const;
	H3DMat3			operator+( const H3DMat3 &a ) const;
	H3DMat3			operator-( const H3DMat3 &a ) const;
	H3DMat3 &		operator*=( const float a );
	H3DMat3 &		operator*=( const H3DMat3 &a );
	H3DMat3 &		operator+=( const H3DMat3 &a );
	H3DMat3 &		operator-=( const H3DMat3 &a );

	friend H3DMat3	operator*( const float a, const H3DMat3 &mat );
	friend H3DVec3	operator*( const H3DVec3 &vec, const H3DMat3 &mat );
	friend H3DVec3 &	operator*=( H3DVec3 &vec, const H3DMat3 &mat );

	bool			Compare( const H3DMat3 &a ) const;						// exact compare, no epsilon
	bool			Compare( const H3DMat3 &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const H3DMat3 &a ) const;					// exact compare, no epsilon
	bool			operator!=( const H3DMat3 &a ) const;					// exact compare, no epsilon

	void			Zero( void );
	void			Identity( void );
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsRotated( void ) const;

	void			ProjectVector( const H3DVec3 &src, H3DVec3 &dst ) const;
	void			UnprojectVector( const H3DVec3 &src, H3DVec3 &dst ) const;

	bool			FixDegeneracies( void );	// fix degenerate axial cases
	bool			FixDenormals( void );		// change tiny numbers to zero

	float			Trace( void ) const;
	float			Determinant( void ) const;
	H3DMat3			OrthoNormalize( void ) const;
	H3DMat3 &		OrthoNormalizeSelf( void );
	H3DMat3			Transpose( void ) const;	// returns transpose
	H3DMat3 &		TransposeSelf( void );
	H3DMat3			Inverse( void ) const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf( void );		// returns false if determinant is zero
	H3DMat3			InverseFast( void ) const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf( void );	// returns false if determinant is zero
	H3DMat3			TransposeMultiply( const H3DMat3 &b ) const;

	H3DMat3			InertiaTranslate( const float mass, const H3DVec3 &centerOfMass, const H3DVec3 &translation ) const;
	H3DMat3 &		InertiaTranslateSelf( const float mass, const H3DVec3 &centerOfMass, const H3DVec3 &translation );
	H3DMat3			InertiaRotate( const H3DMat3 &rotation ) const;
	H3DMat3 &		InertiaRotateSelf( const H3DMat3 &rotation );

	int				GetDimension( void ) const;

	H3DAngles		ToAngles( void ) const;
	H3DQuat			ToQuat( void ) const;
	H3DCQuat			ToCQuat( void ) const;
	H3DRotation		ToRotation( void ) const;
	H3DMat4			ToMat4( void ) const;
	H3DVec3			ToAngularVelocity( void ) const;
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

	friend void		TransposeMultiply( const H3DMat3 &inv, const H3DMat3 &b, H3DMat3 &dst );
	friend H3DMat3	SkewSymmetric( H3DVec3 const &src );

	//=========added by wh===============
	void Scale(const H3DVec3& scale);

	static const H3DMat3& GetIdentity(void)
	{
		const static H3DMat3 mat3_identity( H3DVec3( 1, 0, 0 ), H3DVec3( 0, 1, 0), H3DVec3( 0, 0, 1));
		return mat3_identity;
	}

	static const H3DMat3& GetZero(void)
	{
		const static H3DMat3 mat3_zero( H3DVec3( 0, 0, 0 ), H3DVec3( 0, 0, 0 ), H3DVec3( 0, 0, 0 ));
		return mat3_zero;
	}

private:
	H3DVec3			mat[ 3 ];
	//static H3DMat3 mat3_zero;
	//static H3DMat3 GetIdentity();
};

//extern H3DMat3 mat3_zero;
//extern H3DMat3 GetIdentity();
//#define mat3_default	GetIdentity()

ID_INLINE void H3DMat3::Scale(const H3DVec3& scale)
{
	Identity();
	mat[0].x = scale.x;
	mat[1].y = scale.y;
	mat[2].z = scale.z;
}
ID_INLINE H3DMat3::H3DMat3( void ) {
}

ID_INLINE H3DMat3::H3DMat3( const H3DVec3 &x, const H3DVec3 &y, const H3DVec3 &z ) {
	mat[ 0 ].x = x.x; mat[ 0 ].y = x.y; mat[ 0 ].z = x.z;
	mat[ 1 ].x = y.x; mat[ 1 ].y = y.y; mat[ 1 ].z = y.z;
	mat[ 2 ].x = z.x; mat[ 2 ].y = z.y; mat[ 2 ].z = z.z;
}

ID_INLINE H3DMat3::H3DMat3( const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz ) {
	mat[ 0 ].x = xx; mat[ 0 ].y = xy; mat[ 0 ].z = xz;
	mat[ 1 ].x = yx; mat[ 1 ].y = yy; mat[ 1 ].z = yz;
	mat[ 2 ].x = zx; mat[ 2 ].y = zy; mat[ 2 ].z = zz;
}

ID_INLINE H3DMat3::H3DMat3( const float src[ 3 ][ 3 ] ) {
	memcpy( mat, src, 3 * 3 * sizeof( float ) );
}

ID_INLINE const H3DVec3 &H3DMat3::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 3 ) );
	return mat[ index ];
}

ID_INLINE H3DVec3 &H3DMat3::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 3 ) );
	return mat[ index ];
}

ID_INLINE H3DMat3 H3DMat3::operator-() const {
	return H3DMat3(	-mat[0][0], -mat[0][1], -mat[0][2],
					-mat[1][0], -mat[1][1], -mat[1][2],
					-mat[2][0], -mat[2][1], -mat[2][2] );
}

ID_INLINE H3DVec3 H3DMat3::operator*( const H3DVec3 &vec ) const {
	return H3DVec3(
		mat[ 0 ].x * vec.x + mat[ 1 ].x * vec.y + mat[ 2 ].x * vec.z,
		mat[ 0 ].y * vec.x + mat[ 1 ].y * vec.y + mat[ 2 ].y * vec.z,
		mat[ 0 ].z * vec.x + mat[ 1 ].z * vec.y + mat[ 2 ].z * vec.z );
}

ID_INLINE H3DMat3 H3DMat3::operator*( const H3DMat3 &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	H3DMat3 dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 3 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 3 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 3 + j ];
			dstPtr++;
		}
		m1Ptr += 3;
	}
	return dst;
}

ID_INLINE H3DMat3 H3DMat3::operator*( const float a ) const {
	return H3DMat3(
		mat[0].x * a, mat[0].y * a, mat[0].z * a,
		mat[1].x * a, mat[1].y * a, mat[1].z * a,
		mat[2].x * a, mat[2].y * a, mat[2].z * a );
}

ID_INLINE H3DMat3 H3DMat3::operator+( const H3DMat3 &a ) const {
	return H3DMat3(
		mat[0].x + a[0].x, mat[0].y + a[0].y, mat[0].z + a[0].z,
		mat[1].x + a[1].x, mat[1].y + a[1].y, mat[1].z + a[1].z,
		mat[2].x + a[2].x, mat[2].y + a[2].y, mat[2].z + a[2].z );
}
    
ID_INLINE H3DMat3 H3DMat3::operator-( const H3DMat3 &a ) const {
	return H3DMat3(
		mat[0].x - a[0].x, mat[0].y - a[0].y, mat[0].z - a[0].z,
		mat[1].x - a[1].x, mat[1].y - a[1].y, mat[1].z - a[1].z,
		mat[2].x - a[2].x, mat[2].y - a[2].y, mat[2].z - a[2].z );
}

ID_INLINE H3DMat3 &H3DMat3::operator*=( const float a ) {
	mat[0].x *= a; mat[0].y *= a; mat[0].z *= a;
	mat[1].x *= a; mat[1].y *= a; mat[1].z *= a; 
	mat[2].x *= a; mat[2].y *= a; mat[2].z *= a;

    return *this;
}

ID_INLINE H3DMat3 &H3DMat3::operator*=( const H3DMat3 &a ) {
	int i, j;
	const float *m2Ptr;
	float *m1Ptr, dst[3];

	m1Ptr = reinterpret_cast<float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);

	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			dst[j]  = m1Ptr[0] * m2Ptr[ 0 * 3 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 3 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 3 + j ];
		}
		m1Ptr[0] = dst[0]; m1Ptr[1] = dst[1]; m1Ptr[2] = dst[2];
		m1Ptr += 3;
	}
	return *this;
}

ID_INLINE H3DMat3 &H3DMat3::operator+=( const H3DMat3 &a ) {
	mat[0].x += a[0].x; mat[0].y += a[0].y; mat[0].z += a[0].z;
	mat[1].x += a[1].x; mat[1].y += a[1].y; mat[1].z += a[1].z;
	mat[2].x += a[2].x; mat[2].y += a[2].y; mat[2].z += a[2].z;

    return *this;
}

ID_INLINE H3DMat3 &H3DMat3::operator-=( const H3DMat3 &a ) {
	mat[0].x -= a[0].x; mat[0].y -= a[0].y; mat[0].z -= a[0].z;
	mat[1].x -= a[1].x; mat[1].y -= a[1].y; mat[1].z -= a[1].z;
	mat[2].x -= a[2].x; mat[2].y -= a[2].y; mat[2].z -= a[2].z;

    return *this;
}

ID_INLINE H3DVec3 operator*( const H3DVec3 &vec, const H3DMat3 &mat ) {
	return mat * vec;
}

ID_INLINE H3DMat3 operator*( const float a, const H3DMat3 &mat ) {
	return mat * a;
}

ID_INLINE H3DVec3 &operator*=( H3DVec3 &vec, const H3DMat3 &mat ) {
	float x = mat[ 0 ].x * vec.x + mat[ 1 ].x * vec.y + mat[ 2 ].x * vec.z;
	float y = mat[ 0 ].y * vec.x + mat[ 1 ].y * vec.y + mat[ 2 ].y * vec.z;
	vec.z = mat[ 0 ].z * vec.x + mat[ 1 ].z * vec.y + mat[ 2 ].z * vec.z;
	vec.x = x;
	vec.y = y;
	return vec;
}

ID_INLINE bool H3DMat3::Compare( const H3DMat3 &a ) const {
	if ( mat[0].Compare( a[0] ) &&
		mat[1].Compare( a[1] ) &&
		mat[2].Compare( a[2] ) ) {
		return true;
	}
	return false;
}

ID_INLINE bool H3DMat3::Compare( const H3DMat3 &a, const float epsilon ) const {
	if ( mat[0].Compare( a[0], epsilon ) &&
		mat[1].Compare( a[1], epsilon ) &&
		mat[2].Compare( a[2], epsilon ) ) {
		return true;
	}
	return false;
}

ID_INLINE bool H3DMat3::operator==( const H3DMat3 &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DMat3::operator!=( const H3DMat3 &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DMat3::Zero( void ) {
	memset( mat, 0, sizeof( H3DMat3 ) );
}

ID_INLINE void H3DMat3::Identity( void ) {
	//static H3DMat3
	*this = GetIdentity();
}

ID_INLINE bool H3DMat3::IsIdentity( const float epsilon ) const {
	return Compare( GetIdentity(), epsilon );
}

ID_INLINE bool H3DMat3::IsSymmetric( const float epsilon ) const {
	if ( H3DMath::Fabs( mat[0][1] - mat[1][0] ) > epsilon ) {
		return false;
	}
	if ( H3DMath::Fabs( mat[0][2] - mat[2][0] ) > epsilon ) {
		return false;
	}
	if ( H3DMath::Fabs( mat[1][2] - mat[2][1] ) > epsilon ) {
		return false;
	}
	return true;
}

ID_INLINE bool H3DMat3::IsDiagonal( const float epsilon ) const {
	if ( H3DMath::Fabs( mat[0][1] ) > epsilon ||
		H3DMath::Fabs( mat[0][2] ) > epsilon ||
		H3DMath::Fabs( mat[1][0] ) > epsilon ||
		H3DMath::Fabs( mat[1][2] ) > epsilon ||
		H3DMath::Fabs( mat[2][0] ) > epsilon ||
		H3DMath::Fabs( mat[2][1] ) > epsilon ) {
		return false;
	}
	return true;
}

ID_INLINE bool H3DMat3::IsRotated( void ) const {
	return !Compare( GetIdentity() );
}

ID_INLINE void H3DMat3::ProjectVector( const H3DVec3 &src, H3DVec3 &dst ) const {
	//dst.x = src * mat[ 0 ];
	//dst.y = src * mat[ 1 ];
	//dst.z = src * mat[ 2 ];
	dst.x = src.Dot(mat[ 0 ]);
	dst.y = src.Dot(mat[ 1 ]);
	dst.z = src.Dot(mat[ 2 ]);
}

ID_INLINE void H3DMat3::UnprojectVector( const H3DVec3 &src, H3DVec3 &dst ) const {
	dst = mat[ 0 ] * src.x + mat[ 1 ] * src.y + mat[ 2 ] * src.z;
}

ID_INLINE bool H3DMat3::FixDegeneracies( void ) {
	bool r = mat[0].FixDegenerateNormal();
	r |= mat[1].FixDegenerateNormal();
	r |= mat[2].FixDegenerateNormal();
	return r;
}

ID_INLINE bool H3DMat3::FixDenormals( void ) {
	bool r = mat[0].FixDenormals();
	r |= mat[1].FixDenormals();
	r |= mat[2].FixDenormals();
	return r;
}

ID_INLINE float H3DMat3::Trace( void ) const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] );
}

ID_INLINE H3DMat3 H3DMat3::OrthoNormalize( void ) const {
	H3DMat3 ortho;

	ortho = *this;
	ortho[ 0 ].Normalize();
	ortho[ 2 ].Cross( mat[ 0 ], mat[ 1 ] );
	ortho[ 2 ].Normalize();
	ortho[ 1 ].Cross( mat[ 2 ], mat[ 0 ] );
	ortho[ 1 ].Normalize();
	return ortho;
}

ID_INLINE H3DMat3 &H3DMat3::OrthoNormalizeSelf( void ) {
	mat[ 0 ].Normalize();
	mat[ 2 ].Cross( mat[ 0 ], mat[ 1 ] );
	mat[ 2 ].Normalize();
	mat[ 1 ].Cross( mat[ 2 ], mat[ 0 ] );
	mat[ 1 ].Normalize();
	return *this;
}

ID_INLINE H3DMat3 H3DMat3::Transpose( void ) const {
	return H3DMat3(	mat[0][0], mat[1][0], mat[2][0],
					mat[0][1], mat[1][1], mat[2][1],
					mat[0][2], mat[1][2], mat[2][2] );
}

ID_INLINE H3DMat3 &H3DMat3::TransposeSelf( void ) {
	float tmp0, tmp1, tmp2;

	tmp0 = mat[0][1];
	mat[0][1] = mat[1][0];
	mat[1][0] = tmp0;
	tmp1 = mat[0][2];
	mat[0][2] = mat[2][0];
	mat[2][0] = tmp1;
	tmp2 = mat[1][2];
	mat[1][2] = mat[2][1];
	mat[2][1] = tmp2;

	return *this;
}

ID_INLINE H3DMat3 H3DMat3::Inverse( void ) const {
	H3DMat3 invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

ID_INLINE H3DMat3 H3DMat3::InverseFast( void ) const {
	H3DMat3 invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

ID_INLINE H3DMat3 H3DMat3::TransposeMultiply( const H3DMat3 &b ) const {
	return H3DMat3(	mat[0].x * b[0].x + mat[1].x * b[1].x + mat[2].x * b[2].x,
					mat[0].x * b[0].y + mat[1].x * b[1].y + mat[2].x * b[2].y,
					mat[0].x * b[0].z + mat[1].x * b[1].z + mat[2].x * b[2].z,
					mat[0].y * b[0].x + mat[1].y * b[1].x + mat[2].y * b[2].x,
					mat[0].y * b[0].y + mat[1].y * b[1].y + mat[2].y * b[2].y,
					mat[0].y * b[0].z + mat[1].y * b[1].z + mat[2].y * b[2].z,
					mat[0].z * b[0].x + mat[1].z * b[1].x + mat[2].z * b[2].x,
					mat[0].z * b[0].y + mat[1].z * b[1].y + mat[2].z * b[2].y,
					mat[0].z * b[0].z + mat[1].z * b[1].z + mat[2].z * b[2].z );
}

ID_INLINE void TransposeMultiply( const H3DMat3 &transpose, const H3DMat3 &b, H3DMat3 &dst ) {
	dst[0].x = transpose[0].x * b[0].x + transpose[1].x * b[1].x + transpose[2].x * b[2].x;
	dst[0].y = transpose[0].x * b[0].y + transpose[1].x * b[1].y + transpose[2].x * b[2].y;
	dst[0].z = transpose[0].x * b[0].z + transpose[1].x * b[1].z + transpose[2].x * b[2].z;
	dst[1].x = transpose[0].y * b[0].x + transpose[1].y * b[1].x + transpose[2].y * b[2].x;
	dst[1].y = transpose[0].y * b[0].y + transpose[1].y * b[1].y + transpose[2].y * b[2].y;
	dst[1].z = transpose[0].y * b[0].z + transpose[1].y * b[1].z + transpose[2].y * b[2].z;
	dst[2].x = transpose[0].z * b[0].x + transpose[1].z * b[1].x + transpose[2].z * b[2].x;
	dst[2].y = transpose[0].z * b[0].y + transpose[1].z * b[1].y + transpose[2].z * b[2].y;
	dst[2].z = transpose[0].z * b[0].z + transpose[1].z * b[1].z + transpose[2].z * b[2].z;
}

ID_INLINE H3DMat3 SkewSymmetric( H3DVec3 const &src ) {
	return H3DMat3( 0.0f, -src.z,  src.y, src.z,   0.0f, -src.x, -src.y,  src.x,   0.0f );
}

ID_INLINE int H3DMat3::GetDimension( void ) const {
	return 9;
}

ID_INLINE const float *H3DMat3::ToFloatPtr( void ) const {
	return mat[0].ToFloatPtr();
}

ID_INLINE float *H3DMat3::ToFloatPtr( void ) {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	H3DMat4 - 4x4 matrix
//
//===============================================================

//extern MyClass theClass;

class H3DMat4 {
public:
					H3DMat4( void );
					explicit H3DMat4( const H3DVec4 &x, const H3DVec4 &y, const H3DVec4 &z, const H3DVec4 &w );
					explicit H3DMat4(const float xx, const float xy, const float xz, const float xw,
									const float yx, const float yy, const float yz, const float yw,
									const float zx, const float zy, const float zz, const float zw,
									const float wx, const float wy, const float wz, const float ww );
					explicit H3DMat4( const H3DMat3 &rotation, const H3DVec3 &translation );
					explicit H3DMat4( const float src[ 4 ][ 4 ] );

	const H3DVec4 &	operator[]( int index ) const;
	H3DVec4 &		operator[]( int index );
	H3DMat4			operator*( const float a ) const;
	H3DVec4			operator*( const H3DVec4 &vec ) const;
	H3DVec3			operator*( const H3DVec3 &vec ) const;
	H3DMat4			operator*( const H3DMat4 &a ) const;
	H3DMat4			operator+( const H3DMat4 &a ) const;
	H3DMat4			operator-( const H3DMat4 &a ) const;
	H3DMat4 &		operator*=( const float a );
	H3DMat4 &		operator*=( const H3DMat4 &a );
	H3DMat4 &		operator+=( const H3DMat4 &a );
	H3DMat4 &		operator-=( const H3DMat4 &a );

	friend H3DMat4	operator*( const float a, const H3DMat4 &mat );
	friend H3DVec4	operator*( const H3DVec4 &vec, const H3DMat4 &mat );
	friend H3DVec3	operator*( const H3DVec3 &vec, const H3DMat4 &mat );
	friend H3DVec4 &	operator*=( H3DVec4 &vec, const H3DMat4 &mat );
	friend H3DVec3 &	operator*=( H3DVec3 &vec, const H3DMat4 &mat );

	bool			Compare( const H3DMat4 &a ) const;						// exact compare, no epsilon
	bool			Compare( const H3DMat4 &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const H3DMat4 &a ) const;					// exact compare, no epsilon
	bool			operator!=( const H3DMat4 &a ) const;					// exact compare, no epsilon

	void			Zero( void );
	void			Identity( void );
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsRotated( void ) const;

	void			ProjectVector( const H3DVec4 &src, H3DVec4 &dst ) const;
	void			UnprojectVector( const H3DVec4 &src, H3DVec4 &dst ) const;

	float			Trace( void ) const;
	float			Determinant( void ) const;
	H3DMat4			Transpose( void ) const;	// returns transpose
	H3DMat4 &		TransposeSelf( void );
	H3DMat4			Inverse( void ) const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf( void );		// returns false if determinant is zero
	H3DMat4			InverseFast( void ) const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf( void );	// returns false if determinant is zero
	H3DMat4			TransposeMultiply( const H3DMat4 &b ) const;

	int				GetDimension( void ) const;

	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

	//=============by wh================
	void ToFloatsColumnMajor(float* pOut)const;
	
	void ToFloatsRowMajor(float* pOut)const;
	
	void FromFloatsColumnMajor(const float* pOut);
	
	void FromFloatsRowMajor(const float* pOut);

	void Decompose(H3DVec3& scale, H3DQuat& rotation, H3DVec3& position)const;

	//transformation order is scale->rotation->translation
	void Compose(const H3DVec3& scale, const H3DQuat& rotation, const H3DVec3& translation);

	void Compose(const H3DQuat& rotation, const H3DVec3& translation);

	void DecomposeAffine(H3DVec3& scale, H3DQuat& rotation, H3DVec3& position)const;

	static const H3DMat4& GetIdentity(void)
	{
		ALIGN16(const static H3DMat4 mat4_identity( H3DVec4( 1, 0, 0, 0 ), H3DVec4( 0, 1, 0, 0 ), H3DVec4( 0, 0, 1, 0 ), H3DVec4( 0, 0, 0, 1 ) ));
		return mat4_identity;
	}

	static const H3DMat4& GetZero(void)
	{
		ALIGN16(const static H3DMat4 mat4_zero( H3DVec4( 0, 0, 0, 0 ), H3DVec4( 0, 0, 0, 0 ), H3DVec4( 0, 0, 0, 0 ), H3DVec4( 0, 0, 0, 0 ) ));
		return mat4_zero;
	}

	void GetTranslation(H3DVec3& pos)const;

	void GetScale(H3DVec3& scale)const;

	void GetRotation(H3DQuat& rotation)const;

	void RemoveScale(void);

	H3DVec3 Rotate(const H3DVec3& input)const;

	void Multiply(const H3DMat4& left, const H3DMat4& right);
	//=============by wh end===============
	//=================add by bird==========
	explicit H3DMat4( const float angle_x, const float angle_y, const float angle_z);

private:
	H3DVec4			mat[ 4 ];
	//static H3DMat4 mat4_zero;
	//static H3DMat4 GetIdentity();
};

//extern H3DMat4 mat4_zero;
//extern H3DMat4 GetIdentity();
//#define mat4_default	GetIdentity()

ID_INLINE void H3DMat4::ToFloatsRowMajor(float* pOut16)const
{
	for (uint32 i=0; i<4; ++i)
	{
		pOut16[4*i] = mat[i].x;
		pOut16[4*i+1] = mat[i].y;
		pOut16[4*i+2] = mat[i].z;
		pOut16[4*i+3] = mat[i].w;
	}
	
}

ID_INLINE void H3DMat4::ToFloatsColumnMajor(float* pOut16)const
{
	for (uint32 i=0; i<4; ++i)
	{
		pOut16[i] = mat[i].x;
		pOut16[i+4] = mat[i].y;
		pOut16[i+8] = mat[i].z;
		pOut16[i+12] = mat[i].w;
	}
}

ID_INLINE void H3DMat4::FromFloatsRowMajor(const float* pIn16)
{
	for (uint32 i=0; i<4; ++i)
	{
		mat[i].x = pIn16[4*i] ;
		mat[i].y = pIn16[4*i+1] ;
		mat[i].z = pIn16[4*i+2] ;
		mat[i].w = pIn16[4*i+3] ;
	}

}


ID_INLINE void H3DMat4::FromFloatsColumnMajor(const float* pIn16)
{
	for (uint32 i=0; i<4; ++i)
	{
		mat[i].x = pIn16[i];
		mat[i].y = pIn16[i+4];
		mat[i].z = pIn16[i+8];
		mat[i].w = pIn16[i+12];
	}

}
ID_INLINE H3DMat4::H3DMat4( void ) {
}

ID_INLINE H3DMat4::H3DMat4( const H3DVec4 &x, const H3DVec4 &y, const H3DVec4 &z, const H3DVec4 &w ) {
	mat[ 0 ] = x;
	mat[ 1 ] = y;
	mat[ 2 ] = z;
	mat[ 3 ] = w;
}

ID_INLINE H3DMat4::H3DMat4( const float xx, const float xy, const float xz, const float xw,
							const float yx, const float yy, const float yz, const float yw,
							const float zx, const float zy, const float zz, const float zw,
							const float wx, const float wy, const float wz, const float ww ) {
	mat[0][0] = xx; mat[0][1] = xy; mat[0][2] = xz; mat[0][3] = xw;
	mat[1][0] = yx; mat[1][1] = yy; mat[1][2] = yz; mat[1][3] = yw;
	mat[2][0] = zx; mat[2][1] = zy; mat[2][2] = zz; mat[2][3] = zw;
	mat[3][0] = wx; mat[3][1] = wy; mat[3][2] = wz; mat[3][3] = ww;
}

ID_INLINE H3DMat4::H3DMat4( const H3DMat3 &rotation, const H3DVec3 &translation ) {
	// NOTE: H3DMat3 is transposed because it is column-major
	mat[ 0 ][ 0 ] = rotation[0][0];
	mat[ 0 ][ 1 ] = rotation[1][0];
	mat[ 0 ][ 2 ] = rotation[2][0];
	mat[ 0 ][ 3 ] = translation[0];
	mat[ 1 ][ 0 ] = rotation[0][1];
	mat[ 1 ][ 1 ] = rotation[1][1];
	mat[ 1 ][ 2 ] = rotation[2][1];
	mat[ 1 ][ 3 ] = translation[1];
	mat[ 2 ][ 0 ] = rotation[0][2];
	mat[ 2 ][ 1 ] = rotation[1][2];
	mat[ 2 ][ 2 ] = rotation[2][2];
	mat[ 2 ][ 3 ] = translation[2];
	mat[ 3 ][ 0 ] = 0.0f;
	mat[ 3 ][ 1 ] = 0.0f;
	mat[ 3 ][ 2 ] = 0.0f;
	mat[ 3 ][ 3 ] = 1.0f;
}

ID_INLINE H3DMat4::H3DMat4( const float src[ 4 ][ 4 ] ) {
	memcpy( mat, src, 4 * 4 * sizeof( float ) );
}

ID_INLINE const H3DVec4 &H3DMat4::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 4 ) );
	return mat[ index ];
}

ID_INLINE H3DVec4 &H3DMat4::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 4 ) );
	return mat[ index ];
}

ID_INLINE H3DMat4 H3DMat4::operator*( const float a ) const {
	return H3DMat4(
		mat[0].x * a, mat[0].y * a, mat[0].z * a, mat[0].w * a,
		mat[1].x * a, mat[1].y * a, mat[1].z * a, mat[1].w * a,
		mat[2].x * a, mat[2].y * a, mat[2].z * a, mat[2].w * a,
		mat[3].x * a, mat[3].y * a, mat[3].z * a, mat[3].w * a );
}

ID_INLINE H3DVec4 H3DMat4::operator*( const H3DVec4 &vec ) const {
	return H3DVec4(
		mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w * vec.w,
		mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w * vec.w,
		mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w * vec.w,
		mat[ 3 ].x * vec.x + mat[ 3 ].y * vec.y + mat[ 3 ].z * vec.z + mat[ 3 ].w * vec.w );
}

ID_INLINE H3DVec3 H3DMat4::operator*( const H3DVec3 &vec ) const {
	float s = mat[ 3 ].x * vec.x + mat[ 3 ].y * vec.y + mat[ 3 ].z * vec.z + mat[ 3 ].w;
	if ( s == 0.0f ) {
		return H3DVec3( 0.0f, 0.0f, 0.0f );
	}
	if ( s == 1.0f ) {
		return H3DVec3(
			mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w,
			mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w,
			mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w );
	}
	else {
		float invS = 1.0f / s;
		return H3DVec3(
			(mat[ 0 ].x * vec.x + mat[ 0 ].y * vec.y + mat[ 0 ].z * vec.z + mat[ 0 ].w) * invS,
			(mat[ 1 ].x * vec.x + mat[ 1 ].y * vec.y + mat[ 1 ].z * vec.z + mat[ 1 ].w) * invS,
			(mat[ 2 ].x * vec.x + mat[ 2 ].y * vec.y + mat[ 2 ].z * vec.z + mat[ 2 ].w) * invS );
	}
}

ID_INLINE void H3DMat4::Multiply(const H3DMat4& left, const H3DMat4& right)
{
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;

	m1Ptr = reinterpret_cast<const float *>(&left);
	m2Ptr = reinterpret_cast<const float *>(&right);
	dstPtr = reinterpret_cast<float *>(this);

	for ( i = 0; i < 4; i++ ) {
		for ( j = 0; j < 4; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 4 + j ]
			+ m1Ptr[1] * m2Ptr[ 1 * 4 + j ]
			+ m1Ptr[2] * m2Ptr[ 2 * 4 + j ]
			+ m1Ptr[3] * m2Ptr[ 3 * 4 + j ];
			dstPtr++;
		}
		m1Ptr += 4;
	}
}

ID_INLINE H3DMat4 H3DMat4::operator*( const H3DMat4 &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	H3DMat4 dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 4; i++ ) {
		for ( j = 0; j < 4; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 4 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 4 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 4 + j ]
					+ m1Ptr[3] * m2Ptr[ 3 * 4 + j ];
			dstPtr++;
		}
		m1Ptr += 4;
	}
	return dst;
}

ID_INLINE H3DMat4 H3DMat4::operator+( const H3DMat4 &a ) const {
	return H3DMat4( 
		mat[0].x + a[0].x, mat[0].y + a[0].y, mat[0].z + a[0].z, mat[0].w + a[0].w,
		mat[1].x + a[1].x, mat[1].y + a[1].y, mat[1].z + a[1].z, mat[1].w + a[1].w,
		mat[2].x + a[2].x, mat[2].y + a[2].y, mat[2].z + a[2].z, mat[2].w + a[2].w,
		mat[3].x + a[3].x, mat[3].y + a[3].y, mat[3].z + a[3].z, mat[3].w + a[3].w );
}
    
ID_INLINE H3DMat4 H3DMat4::operator-( const H3DMat4 &a ) const {
	return H3DMat4( 
		mat[0].x - a[0].x, mat[0].y - a[0].y, mat[0].z - a[0].z, mat[0].w - a[0].w,
		mat[1].x - a[1].x, mat[1].y - a[1].y, mat[1].z - a[1].z, mat[1].w - a[1].w,
		mat[2].x - a[2].x, mat[2].y - a[2].y, mat[2].z - a[2].z, mat[2].w - a[2].w,
		mat[3].x - a[3].x, mat[3].y - a[3].y, mat[3].z - a[3].z, mat[3].w - a[3].w );
}

ID_INLINE H3DMat4 &H3DMat4::operator*=( const float a ) {
	mat[0].x *= a; mat[0].y *= a; mat[0].z *= a; mat[0].w *= a;
	mat[1].x *= a; mat[1].y *= a; mat[1].z *= a; mat[1].w *= a;
	mat[2].x *= a; mat[2].y *= a; mat[2].z *= a; mat[2].w *= a;
	mat[3].x *= a; mat[3].y *= a; mat[3].z *= a; mat[3].w *= a;
    return *this;
}

ID_INLINE H3DMat4 &H3DMat4::operator*=( const H3DMat4 &a ) {
	*this = (*this) * a;
	return *this;
}

ID_INLINE H3DMat4 &H3DMat4::operator+=( const H3DMat4 &a ) {
	mat[0].x += a[0].x; mat[0].y += a[0].y; mat[0].z += a[0].z; mat[0].w += a[0].w;
	mat[1].x += a[1].x; mat[1].y += a[1].y; mat[1].z += a[1].z; mat[1].w += a[1].w;
	mat[2].x += a[2].x; mat[2].y += a[2].y; mat[2].z += a[2].z; mat[2].w += a[2].w;
	mat[3].x += a[3].x; mat[3].y += a[3].y; mat[3].z += a[3].z; mat[3].w += a[3].w;
    return *this;
}

ID_INLINE H3DMat4 &H3DMat4::operator-=( const H3DMat4 &a ) {
	mat[0].x -= a[0].x; mat[0].y -= a[0].y; mat[0].z -= a[0].z; mat[0].w -= a[0].w;
	mat[1].x -= a[1].x; mat[1].y -= a[1].y; mat[1].z -= a[1].z; mat[1].w -= a[1].w;
	mat[2].x -= a[2].x; mat[2].y -= a[2].y; mat[2].z -= a[2].z; mat[2].w -= a[2].w;
	mat[3].x -= a[3].x; mat[3].y -= a[3].y; mat[3].z -= a[3].z; mat[3].w -= a[3].w;
    return *this;
}

ID_INLINE H3DMat4 operator*( const float a, const H3DMat4 &mat ) {
	return mat * a;
}

ID_INLINE H3DVec4 operator*( const H3DVec4 &vec, const H3DMat4 &mat ) {
	return mat * vec;
}

ID_INLINE H3DVec3 operator*( const H3DVec3 &vec, const H3DMat4 &mat ) {
	return mat * vec;
}

ID_INLINE H3DVec4 &operator*=( H3DVec4 &vec, const H3DMat4 &mat ) {
	vec = mat * vec;
	return vec;
}

ID_INLINE H3DVec3 &operator*=( H3DVec3 &vec, const H3DMat4 &mat ) {
	vec = mat * vec;
	return vec;
}

ID_INLINE bool H3DMat4::Compare( const H3DMat4 &a ) const {
	dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 4*4; i++ ) {
		if ( ptr1[i] != ptr2[i] ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DMat4::Compare( const H3DMat4 &a, const float epsilon ) const {
	dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 4*4; i++ ) {
		if ( H3DMath::Fabs( ptr1[i] - ptr2[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DMat4::operator==( const H3DMat4 &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DMat4::operator!=( const H3DMat4 &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DMat4::Zero( void ) {
	memset( mat, 0, sizeof( H3DMat4 ) );
}

ID_INLINE void H3DMat4::Identity( void ) {
	*this = GetIdentity();
}

ID_INLINE bool H3DMat4::IsIdentity( const float epsilon ) const {
	return Compare( GetIdentity(), epsilon );
}

ID_INLINE bool H3DMat4::IsSymmetric( const float epsilon ) const {
	for ( int i = 1; i < 4; i++ ) {
		for ( int j = 0; j < i; j++ ) {
			if ( H3DMath::Fabs( mat[i][j] - mat[j][i] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool H3DMat4::IsDiagonal( const float epsilon ) const {
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i != j && H3DMath::Fabs( mat[i][j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool H3DMat4::IsRotated( void ) const {
	if ( !mat[ 0 ][ 1 ] && !mat[ 0 ][ 2 ] &&
		!mat[ 1 ][ 0 ] && !mat[ 1 ][ 2 ] &&
		!mat[ 2 ][ 0 ] && !mat[ 2 ][ 1 ] ) {
		return false;
	}
	return true;
}

ID_INLINE void H3DMat4::ProjectVector( const H3DVec4 &src, H3DVec4 &dst ) const {
	dst.x = src * mat[ 0 ];
	dst.y = src * mat[ 1 ];
	dst.z = src * mat[ 2 ];
	dst.w = src * mat[ 3 ];
}

ID_INLINE void H3DMat4::UnprojectVector( const H3DVec4 &src, H3DVec4 &dst ) const {
	dst = mat[ 0 ] * src.x + mat[ 1 ] * src.y + mat[ 2 ] * src.z + mat[ 3 ] * src.w;
}

ID_INLINE float H3DMat4::Trace( void ) const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3] );
}

ID_INLINE H3DMat4 H3DMat4::Inverse( void ) const {
	H3DMat4 invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

ID_INLINE H3DMat4 H3DMat4::InverseFast( void ) const {
	H3DMat4 invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

ID_INLINE H3DMat4 H3DMat3::ToMat4( void ) const {
	// NOTE: H3DMat3 is transposed because it is column-major
	return H3DMat4(	mat[0][0],	mat[1][0],	mat[2][0],	0.0f,
					mat[0][1],	mat[1][1],	mat[2][1],	0.0f,
					mat[0][2],	mat[1][2],	mat[2][2],	0.0f,
					0.0f,		0.0f,		0.0f,		1.0f );
}

ID_INLINE int H3DMat4::GetDimension( void ) const {
	return 16;
}

ID_INLINE const float *H3DMat4::ToFloatPtr( void ) const {
	return mat[0].ToFloatPtr();
}

ID_INLINE float *H3DMat4::ToFloatPtr( void ) {
	return mat[0].ToFloatPtr();
}

ID_INLINE H3DMat4::H3DMat4( const float angle_x, const float angle_y, const float angle_z) {
	float A = cos(angle_x);
	float B = sin(angle_x);
	float C = cos(angle_y);
	float D = sin(angle_y);
	float E = cos(angle_z);
	float F = sin(angle_z);

	float AD = A * D;
	float BD = B * D;

	mat[0][0] = C * E;
	mat[0][1] = -C * F;
	mat[0][2] = D;
	mat[0][3] = 0.0f;
	mat[1][0] = BD * E + A * F;
	mat[1][1] = -BD * F + A * E;
	mat[1][2] = -B * C;
	mat[1][3] = 0.0f;
	mat[2][0] = -AD * E + B * F;
	mat[2][1] = AD * F + B * E;
	mat[2][2] = A * C;
	mat[2][3] = 0.0f;
	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;
}


//===============================================================
//
//	H3DMat5 - 5x5 matrix
//
//===============================================================

class H3DMat5 {
public:
					H3DMat5( void );
					explicit H3DMat5( const H3DVec5 &v0, const H3DVec5 &v1, const H3DVec5 &v2, const H3DVec5 &v3, const H3DVec5 &v4 );
					explicit H3DMat5( const float src[ 5 ][ 5 ] );

	const H3DVec5 &	operator[]( int index ) const;
	H3DVec5 &		operator[]( int index );
	H3DMat5			operator*( const float a ) const;
	H3DVec5			operator*( const H3DVec5 &vec ) const;
	H3DMat5			operator*( const H3DMat5 &a ) const;
	H3DMat5			operator+( const H3DMat5 &a ) const;
	H3DMat5			operator-( const H3DMat5 &a ) const;
	H3DMat5 &		operator*=( const float a );
	H3DMat5 &		operator*=( const H3DMat5 &a );
	H3DMat5 &		operator+=( const H3DMat5 &a );
	H3DMat5 &		operator-=( const H3DMat5 &a );

	friend H3DMat5	operator*( const float a, const H3DMat5 &mat );
	friend H3DVec5	operator*( const H3DVec5 &vec, const H3DMat5 &mat );
	friend H3DVec5 &	operator*=( H3DVec5 &vec, const H3DMat5 &mat );

	bool			Compare( const H3DMat5 &a ) const;						// exact compare, no epsilon
	bool			Compare( const H3DMat5 &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const H3DMat5 &a ) const;					// exact compare, no epsilon
	bool			operator!=( const H3DMat5 &a ) const;					// exact compare, no epsilon

	void			Zero( void );
	void			Identity( void );
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;

	float			Trace( void ) const;
	float			Determinant( void ) const;
	H3DMat5			Transpose( void ) const;	// returns transpose
	H3DMat5 &		TransposeSelf( void );
	H3DMat5			Inverse( void ) const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf( void );		// returns false if determinant is zero
	H3DMat5			InverseFast( void ) const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf( void );	// returns false if determinant is zero

	int				GetDimension( void ) const;

	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;

	static const H3DMat5& GetIdentity(void)
	{
		const static H3DMat5 mat5_identity( H3DVec5( 1, 0, 0, 0, 0 ), H3DVec5( 0, 1, 0, 0, 0 ), H3DVec5( 0, 0, 1, 0, 0 ), H3DVec5( 0, 0, 0, 1, 0 ), H3DVec5( 0, 0, 0, 0, 1 ) );
		return mat5_identity;
	}

	static const H3DMat5& GetZero(void)
	{
		const static H3DMat5 mat5_zero( H3DVec5( 0, 0, 0, 0, 0 ), H3DVec5( 0, 0, 0, 0, 0 ), H3DVec5( 0, 0, 0, 0, 0 ), H3DVec5( 0, 0, 0, 0, 0 ), H3DVec5( 0, 0, 0, 0, 0 ) );
		return mat5_zero;
	}

private:
	H3DVec5			mat[ 5 ];
	//static H3DMat5 mat5_zero;
	//static H3DMat5 GetIdentity();
};

//extern H3DMat5 mat5_zero;
//extern H3DMat5 GetIdentity();
//#define mat5_default	GetIdentity()

ID_INLINE H3DMat5::H3DMat5( void ) {
}

ID_INLINE H3DMat5::H3DMat5( const float src[ 5 ][ 5 ] ) {
	memcpy( mat, src, 5 * 5 * sizeof( float ) );
}

ID_INLINE H3DMat5::H3DMat5( const H3DVec5 &v0, const H3DVec5 &v1, const H3DVec5 &v2, const H3DVec5 &v3, const H3DVec5 &v4 ) {
	mat[0] = v0;
	mat[1] = v1;
	mat[2] = v2;
	mat[3] = v3;
	mat[4] = v4;
}

ID_INLINE const H3DVec5 &H3DMat5::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 5 ) );
	return mat[ index ];
}

ID_INLINE H3DVec5 &H3DMat5::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 5 ) );
	return mat[ index ];
}

ID_INLINE H3DMat5 H3DMat5::operator*( const H3DMat5 &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	H3DMat5 dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 5; i++ ) {
		for ( j = 0; j < 5; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 5 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 5 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 5 + j ]
					+ m1Ptr[3] * m2Ptr[ 3 * 5 + j ]
					+ m1Ptr[4] * m2Ptr[ 4 * 5 + j ];
			dstPtr++;
		}
		m1Ptr += 5;
	}
	return dst;
}

ID_INLINE H3DMat5 H3DMat5::operator*( const float a ) const {
	return H3DMat5(
		H3DVec5( mat[0][0] * a, mat[0][1] * a, mat[0][2] * a, mat[0][3] * a, mat[0][4] * a ),
		H3DVec5( mat[1][0] * a, mat[1][1] * a, mat[1][2] * a, mat[1][3] * a, mat[1][4] * a ),
		H3DVec5( mat[2][0] * a, mat[2][1] * a, mat[2][2] * a, mat[2][3] * a, mat[2][4] * a ),
		H3DVec5( mat[3][0] * a, mat[3][1] * a, mat[3][2] * a, mat[3][3] * a, mat[3][4] * a ),
		H3DVec5( mat[4][0] * a, mat[4][1] * a, mat[4][2] * a, mat[4][3] * a, mat[4][4] * a ) );
}

ID_INLINE H3DVec5 H3DMat5::operator*( const H3DVec5 &vec ) const {
	return H3DVec5(
		mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3] * vec[3] + mat[0][4] * vec[4],
		mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3] * vec[3] + mat[1][4] * vec[4],
		mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3] * vec[3] + mat[2][4] * vec[4],
		mat[3][0] * vec[0] + mat[3][1] * vec[1] + mat[3][2] * vec[2] + mat[3][3] * vec[3] + mat[3][4] * vec[4],
		mat[4][0] * vec[0] + mat[4][1] * vec[1] + mat[4][2] * vec[2] + mat[4][3] * vec[3] + mat[4][4] * vec[4] );
}

ID_INLINE H3DMat5 H3DMat5::operator+( const H3DMat5 &a ) const {
	return H3DMat5(
		H3DVec5( mat[0][0] + a[0][0], mat[0][1] + a[0][1], mat[0][2] + a[0][2], mat[0][3] + a[0][3], mat[0][4] + a[0][4] ),
		H3DVec5( mat[1][0] + a[1][0], mat[1][1] + a[1][1], mat[1][2] + a[1][2], mat[1][3] + a[1][3], mat[1][4] + a[1][4] ),
		H3DVec5( mat[2][0] + a[2][0], mat[2][1] + a[2][1], mat[2][2] + a[2][2], mat[2][3] + a[2][3], mat[2][4] + a[2][4] ),
		H3DVec5( mat[3][0] + a[3][0], mat[3][1] + a[3][1], mat[3][2] + a[3][2], mat[3][3] + a[3][3], mat[3][4] + a[3][4] ),
		H3DVec5( mat[4][0] + a[4][0], mat[4][1] + a[4][1], mat[4][2] + a[4][2], mat[4][3] + a[4][3], mat[4][4] + a[4][4] ) );
}

ID_INLINE H3DMat5 H3DMat5::operator-( const H3DMat5 &a ) const {
	return H3DMat5(
		H3DVec5( mat[0][0] - a[0][0], mat[0][1] - a[0][1], mat[0][2] - a[0][2], mat[0][3] - a[0][3], mat[0][4] - a[0][4] ),
		H3DVec5( mat[1][0] - a[1][0], mat[1][1] - a[1][1], mat[1][2] - a[1][2], mat[1][3] - a[1][3], mat[1][4] - a[1][4] ),
		H3DVec5( mat[2][0] - a[2][0], mat[2][1] - a[2][1], mat[2][2] - a[2][2], mat[2][3] - a[2][3], mat[2][4] - a[2][4] ),
		H3DVec5( mat[3][0] - a[3][0], mat[3][1] - a[3][1], mat[3][2] - a[3][2], mat[3][3] - a[3][3], mat[3][4] - a[3][4] ),
		H3DVec5( mat[4][0] - a[4][0], mat[4][1] - a[4][1], mat[4][2] - a[4][2], mat[4][3] - a[4][3], mat[4][4] - a[4][4] ) );
}

ID_INLINE H3DMat5 &H3DMat5::operator*=( const float a ) {
	mat[0][0] *= a; mat[0][1] *= a; mat[0][2] *= a; mat[0][3] *= a; mat[0][4] *= a;
	mat[1][0] *= a; mat[1][1] *= a; mat[1][2] *= a; mat[1][3] *= a; mat[1][4] *= a;
	mat[2][0] *= a; mat[2][1] *= a; mat[2][2] *= a; mat[2][3] *= a; mat[2][4] *= a;
	mat[3][0] *= a; mat[3][1] *= a; mat[3][2] *= a; mat[3][3] *= a; mat[3][4] *= a;
	mat[4][0] *= a; mat[4][1] *= a; mat[4][2] *= a; mat[4][3] *= a; mat[4][4] *= a;
	return *this;
}

ID_INLINE H3DMat5 &H3DMat5::operator*=( const H3DMat5 &a ) {
	*this = *this * a;
	return *this;
}

ID_INLINE H3DMat5 &H3DMat5::operator+=( const H3DMat5 &a ) {
	mat[0][0] += a[0][0]; mat[0][1] += a[0][1]; mat[0][2] += a[0][2]; mat[0][3] += a[0][3]; mat[0][4] += a[0][4];
	mat[1][0] += a[1][0]; mat[1][1] += a[1][1]; mat[1][2] += a[1][2]; mat[1][3] += a[1][3]; mat[1][4] += a[1][4];
	mat[2][0] += a[2][0]; mat[2][1] += a[2][1]; mat[2][2] += a[2][2]; mat[2][3] += a[2][3]; mat[2][4] += a[2][4];
	mat[3][0] += a[3][0]; mat[3][1] += a[3][1]; mat[3][2] += a[3][2]; mat[3][3] += a[3][3]; mat[3][4] += a[3][4];
	mat[4][0] += a[4][0]; mat[4][1] += a[4][1]; mat[4][2] += a[4][2]; mat[4][3] += a[4][3]; mat[4][4] += a[4][4];
	return *this;
}

ID_INLINE H3DMat5 &H3DMat5::operator-=( const H3DMat5 &a ) {
	mat[0][0] -= a[0][0]; mat[0][1] -= a[0][1]; mat[0][2] -= a[0][2]; mat[0][3] -= a[0][3]; mat[0][4] -= a[0][4];
	mat[1][0] -= a[1][0]; mat[1][1] -= a[1][1]; mat[1][2] -= a[1][2]; mat[1][3] -= a[1][3]; mat[1][4] -= a[1][4];
	mat[2][0] -= a[2][0]; mat[2][1] -= a[2][1]; mat[2][2] -= a[2][2]; mat[2][3] -= a[2][3]; mat[2][4] -= a[2][4];
	mat[3][0] -= a[3][0]; mat[3][1] -= a[3][1]; mat[3][2] -= a[3][2]; mat[3][3] -= a[3][3]; mat[3][4] -= a[3][4];
	mat[4][0] -= a[4][0]; mat[4][1] -= a[4][1]; mat[4][2] -= a[4][2]; mat[4][3] -= a[4][3]; mat[4][4] -= a[4][4];
	return *this;
}

ID_INLINE H3DVec5 operator*( const H3DVec5 &vec, const H3DMat5 &mat ) {
	return mat * vec;
}

ID_INLINE H3DMat5 operator*( const float a, H3DMat5 const &mat ) {
	return mat * a;
}

ID_INLINE H3DVec5 &operator*=( H3DVec5 &vec, const H3DMat5 &mat ) {
	vec = mat * vec;
	return vec;
}

ID_INLINE bool H3DMat5::Compare( const H3DMat5 &a ) const {
	dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 5*5; i++ ) {
		if ( ptr1[i] != ptr2[i] ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DMat5::Compare( const H3DMat5 &a, const float epsilon ) const {
	dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 5*5; i++ ) {
		if ( H3DMath::Fabs( ptr1[i] - ptr2[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DMat5::operator==( const H3DMat5 &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DMat5::operator!=( const H3DMat5 &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DMat5::Zero( void ) {
	memset( mat, 0, sizeof( H3DMat5 ) );
}

ID_INLINE void H3DMat5::Identity( void ) {
	*this = GetIdentity();
}

ID_INLINE bool H3DMat5::IsIdentity( const float epsilon ) const {
	return Compare( GetIdentity(), epsilon );
}

ID_INLINE bool H3DMat5::IsSymmetric( const float epsilon ) const {
	for ( int i = 1; i < 5; i++ ) {
		for ( int j = 0; j < i; j++ ) {
			if ( H3DMath::Fabs( mat[i][j] - mat[j][i] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool H3DMat5::IsDiagonal( const float epsilon ) const {
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			if ( i != j && H3DMath::Fabs( mat[i][j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE float H3DMat5::Trace( void ) const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3] + mat[4][4] );
}

ID_INLINE H3DMat5 H3DMat5::Inverse( void ) const {
	H3DMat5 invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

ID_INLINE H3DMat5 H3DMat5::InverseFast( void ) const {
	H3DMat5 invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

ID_INLINE int H3DMat5::GetDimension( void ) const {
	return 25;
}

ID_INLINE const float *H3DMat5::ToFloatPtr( void ) const {
	return mat[0].ToFloatPtr();
}

ID_INLINE float *H3DMat5::ToFloatPtr( void ) {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	H3DMat6 - 6x6 matrix
//
//===============================================================

class H3DMat6 {
public:
					H3DMat6( void );
					explicit H3DMat6( const H3DVec6 &v0, const H3DVec6 &v1, const H3DVec6 &v2, const H3DVec6 &v3, const H3DVec6 &v4, const H3DVec6 &v5 );
					explicit H3DMat6( const H3DMat3 &m0, const H3DMat3 &m1, const H3DMat3 &m2, const H3DMat3 &m3 );
					explicit H3DMat6( const float src[ 6 ][ 6 ] );

	const H3DVec6 &	operator[]( int index ) const;
	H3DVec6 &		operator[]( int index );
	H3DMat6			operator*( const float a ) const;
	H3DVec6			operator*( const H3DVec6 &vec ) const;
	H3DMat6			operator*( const H3DMat6 &a ) const;
	H3DMat6			operator+( const H3DMat6 &a ) const;
	H3DMat6			operator-( const H3DMat6 &a ) const;
	H3DMat6 &		operator*=( const float a );
	H3DMat6 &		operator*=( const H3DMat6 &a );
	H3DMat6 &		operator+=( const H3DMat6 &a );
	H3DMat6 &		operator-=( const H3DMat6 &a );

	friend H3DMat6	operator*( const float a, const H3DMat6 &mat );
	friend H3DVec6	operator*( const H3DVec6 &vec, const H3DMat6 &mat );
	friend H3DVec6 &	operator*=( H3DVec6 &vec, const H3DMat6 &mat );

	bool			Compare( const H3DMat6 &a ) const;						// exact compare, no epsilon
	bool			Compare( const H3DMat6 &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==( const H3DMat6 &a ) const;					// exact compare, no epsilon
	bool			operator!=( const H3DMat6 &a ) const;					// exact compare, no epsilon

	void			Zero( void );
	void			Identity( void );
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;

	H3DMat3			SubMat3( int n ) const;
	float			Trace( void ) const;
	float			Determinant( void ) const;
	H3DMat6			Transpose( void ) const;	// returns transpose
	H3DMat6 &		TransposeSelf( void );
	H3DMat6			Inverse( void ) const;		// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf( void );		// returns false if determinant is zero
	H3DMat6			InverseFast( void ) const;	// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf( void );	// returns false if determinant is zero

	int				GetDimension( void ) const;

	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;


	static const H3DMat6& GetIdentity(void)
	{
		const static H3DMat6 mat6_identity( H3DVec6( 1, 0, 0, 0, 0, 0 ), H3DVec6( 0, 1, 0, 0, 0, 0 ), H3DVec6( 0, 0, 1, 0, 0, 0 ), H3DVec6( 0, 0, 0, 1, 0, 0 ), H3DVec6( 0, 0, 0, 0, 1, 0 ), H3DVec6( 0, 0, 0, 0, 0, 1 ) );
		return mat6_identity;
	}

	static const H3DMat6& GetZero(void)
	{
		const static H3DMat6 mat6_zero( H3DVec6( 0, 0, 0, 0, 0, 0 ), H3DVec6( 0, 0, 0, 0, 0, 0 ), H3DVec6( 0, 0, 0, 0, 0, 0 ), H3DVec6( 0, 0, 0, 0, 0, 0 ), H3DVec6( 0, 0, 0, 0, 0, 0 ), H3DVec6( 0, 0, 0, 0, 0, 0 ) );
		return mat6_zero;
	}

private:
	H3DVec6			mat[ 6 ];
	//static H3DMat6 mat6_zero;
	//static H3DMat6 GetIdentity();
};

//extern H3DMat6 mat6_zero;
//extern H3DMat6 GetIdentity();
//#define mat6_default	GetIdentity()

ID_INLINE H3DMat6::H3DMat6( void ) {
}

ID_INLINE H3DMat6::H3DMat6( const H3DMat3 &m0, const H3DMat3 &m1, const H3DMat3 &m2, const H3DMat3 &m3 ) {
	mat[0] = H3DVec6( m0[0][0], m0[0][1], m0[0][2], m1[0][0], m1[0][1], m1[0][2] );
	mat[1] = H3DVec6( m0[1][0], m0[1][1], m0[1][2], m1[1][0], m1[1][1], m1[1][2] );
	mat[2] = H3DVec6( m0[2][0], m0[2][1], m0[2][2], m1[2][0], m1[2][1], m1[2][2] );
	mat[3] = H3DVec6( m2[0][0], m2[0][1], m2[0][2], m3[0][0], m3[0][1], m3[0][2] );
	mat[4] = H3DVec6( m2[1][0], m2[1][1], m2[1][2], m3[1][0], m3[1][1], m3[1][2] );
	mat[5] = H3DVec6( m2[2][0], m2[2][1], m2[2][2], m3[2][0], m3[2][1], m3[2][2] );
}

ID_INLINE H3DMat6::H3DMat6( const H3DVec6 &v0, const H3DVec6 &v1, const H3DVec6 &v2, const H3DVec6 &v3, const H3DVec6 &v4, const H3DVec6 &v5 ) {
	mat[0] = v0;
	mat[1] = v1;
	mat[2] = v2;
	mat[3] = v3;
	mat[4] = v4;
	mat[5] = v5;
}

ID_INLINE H3DMat6::H3DMat6( const float src[ 6 ][ 6 ] ) {
	memcpy( mat, src, 6 * 6 * sizeof( float ) );
}

ID_INLINE const H3DVec6 &H3DMat6::operator[]( int index ) const {
	//assert( ( index >= 0 ) && ( index < 6 ) );
	return mat[ index ];
}

ID_INLINE H3DVec6 &H3DMat6::operator[]( int index ) {
	//assert( ( index >= 0 ) && ( index < 6 ) );
	return mat[ index ];
}

ID_INLINE H3DMat6 H3DMat6::operator*( const H3DMat6 &a ) const {
	int i, j;
	const float *m1Ptr, *m2Ptr;
	float *dstPtr;
	H3DMat6 dst;

	m1Ptr = reinterpret_cast<const float *>(this);
	m2Ptr = reinterpret_cast<const float *>(&a);
	dstPtr = reinterpret_cast<float *>(&dst);

	for ( i = 0; i < 6; i++ ) {
		for ( j = 0; j < 6; j++ ) {
			*dstPtr = m1Ptr[0] * m2Ptr[ 0 * 6 + j ]
					+ m1Ptr[1] * m2Ptr[ 1 * 6 + j ]
					+ m1Ptr[2] * m2Ptr[ 2 * 6 + j ]
					+ m1Ptr[3] * m2Ptr[ 3 * 6 + j ]
					+ m1Ptr[4] * m2Ptr[ 4 * 6 + j ]
					+ m1Ptr[5] * m2Ptr[ 5 * 6 + j ];
			dstPtr++;
		}
		m1Ptr += 6;
	}
	return dst;
}

ID_INLINE H3DMat6 H3DMat6::operator*( const float a ) const {
	return H3DMat6(
		H3DVec6( mat[0][0] * a, mat[0][1] * a, mat[0][2] * a, mat[0][3] * a, mat[0][4] * a, mat[0][5] * a ),
		H3DVec6( mat[1][0] * a, mat[1][1] * a, mat[1][2] * a, mat[1][3] * a, mat[1][4] * a, mat[1][5] * a ),
		H3DVec6( mat[2][0] * a, mat[2][1] * a, mat[2][2] * a, mat[2][3] * a, mat[2][4] * a, mat[2][5] * a ),
		H3DVec6( mat[3][0] * a, mat[3][1] * a, mat[3][2] * a, mat[3][3] * a, mat[3][4] * a, mat[3][5] * a ),
		H3DVec6( mat[4][0] * a, mat[4][1] * a, mat[4][2] * a, mat[4][3] * a, mat[4][4] * a, mat[4][5] * a ),
		H3DVec6( mat[5][0] * a, mat[5][1] * a, mat[5][2] * a, mat[5][3] * a, mat[5][4] * a, mat[5][5] * a ) );
}

ID_INLINE H3DVec6 H3DMat6::operator*( const H3DVec6 &vec ) const {
	return H3DVec6(
		mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3] * vec[3] + mat[0][4] * vec[4] + mat[0][5] * vec[5],
		mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3] * vec[3] + mat[1][4] * vec[4] + mat[1][5] * vec[5],
		mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3] * vec[3] + mat[2][4] * vec[4] + mat[2][5] * vec[5],
		mat[3][0] * vec[0] + mat[3][1] * vec[1] + mat[3][2] * vec[2] + mat[3][3] * vec[3] + mat[3][4] * vec[4] + mat[3][5] * vec[5],
		mat[4][0] * vec[0] + mat[4][1] * vec[1] + mat[4][2] * vec[2] + mat[4][3] * vec[3] + mat[4][4] * vec[4] + mat[4][5] * vec[5],
		mat[5][0] * vec[0] + mat[5][1] * vec[1] + mat[5][2] * vec[2] + mat[5][3] * vec[3] + mat[5][4] * vec[4] + mat[5][5] * vec[5] );
}

ID_INLINE H3DMat6 H3DMat6::operator+( const H3DMat6 &a ) const {
	return H3DMat6(
		H3DVec6( mat[0][0] + a[0][0], mat[0][1] + a[0][1], mat[0][2] + a[0][2], mat[0][3] + a[0][3], mat[0][4] + a[0][4], mat[0][5] + a[0][5] ),
		H3DVec6( mat[1][0] + a[1][0], mat[1][1] + a[1][1], mat[1][2] + a[1][2], mat[1][3] + a[1][3], mat[1][4] + a[1][4], mat[1][5] + a[1][5] ),
		H3DVec6( mat[2][0] + a[2][0], mat[2][1] + a[2][1], mat[2][2] + a[2][2], mat[2][3] + a[2][3], mat[2][4] + a[2][4], mat[2][5] + a[2][5] ),
		H3DVec6( mat[3][0] + a[3][0], mat[3][1] + a[3][1], mat[3][2] + a[3][2], mat[3][3] + a[3][3], mat[3][4] + a[3][4], mat[3][5] + a[3][5] ),
		H3DVec6( mat[4][0] + a[4][0], mat[4][1] + a[4][1], mat[4][2] + a[4][2], mat[4][3] + a[4][3], mat[4][4] + a[4][4], mat[4][5] + a[4][5] ),
		H3DVec6( mat[5][0] + a[5][0], mat[5][1] + a[5][1], mat[5][2] + a[5][2], mat[5][3] + a[5][3], mat[5][4] + a[5][4], mat[5][5] + a[5][5] ) );
}

ID_INLINE H3DMat6 H3DMat6::operator-( const H3DMat6 &a ) const {
	return H3DMat6(
		H3DVec6( mat[0][0] - a[0][0], mat[0][1] - a[0][1], mat[0][2] - a[0][2], mat[0][3] - a[0][3], mat[0][4] - a[0][4], mat[0][5] - a[0][5] ),
		H3DVec6( mat[1][0] - a[1][0], mat[1][1] - a[1][1], mat[1][2] - a[1][2], mat[1][3] - a[1][3], mat[1][4] - a[1][4], mat[1][5] - a[1][5] ),
		H3DVec6( mat[2][0] - a[2][0], mat[2][1] - a[2][1], mat[2][2] - a[2][2], mat[2][3] - a[2][3], mat[2][4] - a[2][4], mat[2][5] - a[2][5] ),
		H3DVec6( mat[3][0] - a[3][0], mat[3][1] - a[3][1], mat[3][2] - a[3][2], mat[3][3] - a[3][3], mat[3][4] - a[3][4], mat[3][5] - a[3][5] ),
		H3DVec6( mat[4][0] - a[4][0], mat[4][1] - a[4][1], mat[4][2] - a[4][2], mat[4][3] - a[4][3], mat[4][4] - a[4][4], mat[4][5] - a[4][5] ),
		H3DVec6( mat[5][0] - a[5][0], mat[5][1] - a[5][1], mat[5][2] - a[5][2], mat[5][3] - a[5][3], mat[5][4] - a[5][4], mat[5][5] - a[5][5] ) );
}

ID_INLINE H3DMat6 &H3DMat6::operator*=( const float a ) {
	mat[0][0] *= a; mat[0][1] *= a; mat[0][2] *= a; mat[0][3] *= a; mat[0][4] *= a; mat[0][5] *= a;
	mat[1][0] *= a; mat[1][1] *= a; mat[1][2] *= a; mat[1][3] *= a; mat[1][4] *= a; mat[1][5] *= a;
	mat[2][0] *= a; mat[2][1] *= a; mat[2][2] *= a; mat[2][3] *= a; mat[2][4] *= a; mat[2][5] *= a;
	mat[3][0] *= a; mat[3][1] *= a; mat[3][2] *= a; mat[3][3] *= a; mat[3][4] *= a; mat[3][5] *= a;
	mat[4][0] *= a; mat[4][1] *= a; mat[4][2] *= a; mat[4][3] *= a; mat[4][4] *= a; mat[4][5] *= a;
	mat[5][0] *= a; mat[5][1] *= a; mat[5][2] *= a; mat[5][3] *= a; mat[5][4] *= a; mat[5][5] *= a;
	return *this;
}

ID_INLINE H3DMat6 &H3DMat6::operator*=( const H3DMat6 &a ) {
	*this = *this * a;
	return *this;
}

ID_INLINE H3DMat6 &H3DMat6::operator+=( const H3DMat6 &a ) {
	mat[0][0] += a[0][0]; mat[0][1] += a[0][1]; mat[0][2] += a[0][2]; mat[0][3] += a[0][3]; mat[0][4] += a[0][4]; mat[0][5] += a[0][5];
	mat[1][0] += a[1][0]; mat[1][1] += a[1][1]; mat[1][2] += a[1][2]; mat[1][3] += a[1][3]; mat[1][4] += a[1][4]; mat[1][5] += a[1][5];
	mat[2][0] += a[2][0]; mat[2][1] += a[2][1]; mat[2][2] += a[2][2]; mat[2][3] += a[2][3]; mat[2][4] += a[2][4]; mat[2][5] += a[2][5];
	mat[3][0] += a[3][0]; mat[3][1] += a[3][1]; mat[3][2] += a[3][2]; mat[3][3] += a[3][3]; mat[3][4] += a[3][4]; mat[3][5] += a[3][5];
	mat[4][0] += a[4][0]; mat[4][1] += a[4][1]; mat[4][2] += a[4][2]; mat[4][3] += a[4][3]; mat[4][4] += a[4][4]; mat[4][5] += a[4][5];
	mat[5][0] += a[5][0]; mat[5][1] += a[5][1]; mat[5][2] += a[5][2]; mat[5][3] += a[5][3]; mat[5][4] += a[5][4]; mat[5][5] += a[5][5];
	return *this;
}

ID_INLINE H3DMat6 &H3DMat6::operator-=( const H3DMat6 &a ) {
	mat[0][0] -= a[0][0]; mat[0][1] -= a[0][1]; mat[0][2] -= a[0][2]; mat[0][3] -= a[0][3]; mat[0][4] -= a[0][4]; mat[0][5] -= a[0][5];
	mat[1][0] -= a[1][0]; mat[1][1] -= a[1][1]; mat[1][2] -= a[1][2]; mat[1][3] -= a[1][3]; mat[1][4] -= a[1][4]; mat[1][5] -= a[1][5];
	mat[2][0] -= a[2][0]; mat[2][1] -= a[2][1]; mat[2][2] -= a[2][2]; mat[2][3] -= a[2][3]; mat[2][4] -= a[2][4]; mat[2][5] -= a[2][5];
	mat[3][0] -= a[3][0]; mat[3][1] -= a[3][1]; mat[3][2] -= a[3][2]; mat[3][3] -= a[3][3]; mat[3][4] -= a[3][4]; mat[3][5] -= a[3][5];
	mat[4][0] -= a[4][0]; mat[4][1] -= a[4][1]; mat[4][2] -= a[4][2]; mat[4][3] -= a[4][3]; mat[4][4] -= a[4][4]; mat[4][5] -= a[4][5];
	mat[5][0] -= a[5][0]; mat[5][1] -= a[5][1]; mat[5][2] -= a[5][2]; mat[5][3] -= a[5][3]; mat[5][4] -= a[5][4]; mat[5][5] -= a[5][5];
	return *this;
}

ID_INLINE H3DVec6 operator*( const H3DVec6 &vec, const H3DMat6 &mat ) {
	return mat * vec;
}

ID_INLINE H3DMat6 operator*( const float a, H3DMat6 const &mat ) {
	return mat * a;
}

ID_INLINE H3DVec6 &operator*=( H3DVec6 &vec, const H3DMat6 &mat ) {
	vec = mat * vec;
	return vec;
}

ID_INLINE bool H3DMat6::Compare( const H3DMat6 &a ) const {
	dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 6*6; i++ ) {
		if ( ptr1[i] != ptr2[i] ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DMat6::Compare( const H3DMat6 &a, const float epsilon ) const {
	dword i;
	const float *ptr1, *ptr2;

	ptr1 = reinterpret_cast<const float *>(mat);
	ptr2 = reinterpret_cast<const float *>(a.mat);
	for ( i = 0; i < 6*6; i++ ) {
		if ( H3DMath::Fabs( ptr1[i] - ptr2[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DMat6::operator==( const H3DMat6 &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DMat6::operator!=( const H3DMat6 &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DMat6::Zero( void ) {
	memset( mat, 0, sizeof( H3DMat6 ) );
}

ID_INLINE void H3DMat6::Identity( void ) {
	*this = GetIdentity();
}

ID_INLINE bool H3DMat6::IsIdentity( const float epsilon ) const {
	return Compare( GetIdentity(), epsilon );
}

ID_INLINE bool H3DMat6::IsSymmetric( const float epsilon ) const {
	for ( int i = 1; i < 6; i++ ) {
		for ( int j = 0; j < i; j++ ) {
			if ( H3DMath::Fabs( mat[i][j] - mat[j][i] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool H3DMat6::IsDiagonal( const float epsilon ) const {
	for ( int i = 0; i < 6; i++ ) {
		for ( int j = 0; j < 6; j++ ) {
			if ( i != j && H3DMath::Fabs( mat[i][j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE H3DMat3 H3DMat6::SubMat3( int n ) const {
	assert( n >= 0 && n < 4 );
	int b0 = ((n & 2) >> 1) * 3;
	int b1 = (n & 1) * 3;
	return H3DMat3(
		mat[b0 + 0][b1 + 0], mat[b0 + 0][b1 + 1], mat[b0 + 0][b1 + 2],
		mat[b0 + 1][b1 + 0], mat[b0 + 1][b1 + 1], mat[b0 + 1][b1 + 2],
		mat[b0 + 2][b1 + 0], mat[b0 + 2][b1 + 1], mat[b0 + 2][b1 + 2] );
}

ID_INLINE float H3DMat6::Trace( void ) const {
	return ( mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3] + mat[4][4] + mat[5][5] );
}

ID_INLINE H3DMat6 H3DMat6::Inverse( void ) const {
	H3DMat6 invMat;

	invMat = *this;
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

ID_INLINE H3DMat6 H3DMat6::InverseFast( void ) const {
	H3DMat6 invMat;

	invMat = *this;
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

ID_INLINE int H3DMat6::GetDimension( void ) const {
	return 36;
}

ID_INLINE const float *H3DMat6::ToFloatPtr( void ) const {
	return mat[0].ToFloatPtr();
}

ID_INLINE float *H3DMat6::ToFloatPtr( void ) {
	return mat[0].ToFloatPtr();
}


//===============================================================
//
//	H3DMatX - arbitrary sized dense real matrix
//
//  The matrix lives on 16 byte aligned and 16 byte padded memory.
//
//	NOTE: due to the temporary memory pool H3DMatX cannot be used by multiple threads.
//
//===============================================================

#define MATX_MAX_TEMP		1024
#define MATX_QUAD( x )		( ( ( ( x ) + 3 ) & ~3 ) * sizeof( float ) )
#define MATX_CLEAREND()		int s = numRows * numColumns; while( s < ( ( s + 3 ) & ~3 ) ) { mat[s++] = 0.0f; }
#define MATX_ALLOCA( n )	( (float *) _alloca16( MATX_QUAD( n ) ) )
#define MATX_SIMD

class H3DMatX {
public:
					H3DMatX( void );
					explicit H3DMatX( int rows, int columns );
					explicit H3DMatX( int rows, int columns, float *src );
					~H3DMatX( void );

	void			Set( int rows, int columns, const float *src );
	void			Set( const H3DMat3 &m1, const H3DMat3 &m2 );
	void			Set( const H3DMat3 &m1, const H3DMat3 &m2, const H3DMat3 &m3, const H3DMat3 &m4 );

	const float *	operator[]( int index ) const;
	float *			operator[]( int index );
	H3DMatX &		operator=( const H3DMatX &a );
	H3DMatX			operator*( const float a ) const;
	H3DVecX			operator*( const H3DVecX &vec ) const;
	H3DMatX			operator*( const H3DMatX &a ) const;
	H3DMatX			operator+( const H3DMatX &a ) const;
	H3DMatX			operator-( const H3DMatX &a ) const;
	H3DMatX &		operator*=( const float a );
	H3DMatX &		operator*=( const H3DMatX &a );
	H3DMatX &		operator+=( const H3DMatX &a );
	H3DMatX &		operator-=( const H3DMatX &a );

	friend H3DMatX	operator*( const float a, const H3DMatX &m );
	friend H3DVecX	operator*( const H3DVecX &vec, const H3DMatX &m );
	friend H3DVecX &	operator*=( H3DVecX &vec, const H3DMatX &m );

	bool			Compare( const H3DMatX &a ) const;								// exact compare, no epsilon
	bool			Compare( const H3DMatX &a, const float epsilon ) const;			// compare with epsilon
	bool			operator==( const H3DMatX &a ) const;							// exact compare, no epsilon
	bool			operator!=( const H3DMatX &a ) const;							// exact compare, no epsilon

	void			SetSize( int rows, int columns );								// set the number of rows/columns
	void			ChangeSize( int rows, int columns, bool makeZero = false );		// change the size keeping data intact where possible
	int				GetNumRows( void ) const { return numRows; }					// get the number of rows
	int				GetNumColumns( void ) const { return numColumns; }				// get the number of columns
	void			SetData( int rows, int columns, float *data );					// set float array pointer
	void			Zero( void );													// clear matrix
	void			Zero( int rows, int columns );									// set size and clear matrix
	void			Identity( void );												// clear to identity matrix
	void			Identity( int rows, int columns );								// set size and clear to identity matrix
	void			Diag( const H3DVecX &v );										// create diagonal matrix from vector
	void			Random( int seed, float l = 0.0f, float u = 1.0f );				// fill matrix with random values
	void			Random( int rows, int columns, int seed, float l = 0.0f, float u = 1.0f );
	void			Negate( void );													// (*this) = - (*this)
	void			Clamp( float min, float max );									// clamp all values
	H3DMatX &		SwapRows( int r1, int r2 );										// swap rows
	H3DMatX &		SwapColumns( int r1, int r2 );									// swap columns
	H3DMatX &		SwapRowsColumns( int r1, int r2 );								// swap rows and columns
	H3DMatX &		RemoveRow( int r );												// remove a row
	H3DMatX &		RemoveColumn( int r );											// remove a column
	H3DMatX &		RemoveRowColumn( int r );										// remove a row and column
	void			ClearUpperTriangle( void );										// clear the upper triangle
	void			ClearLowerTriangle( void );										// clear the lower triangle
	void			SquareSubMatrix( const H3DMatX &m, int size );					// get square sub-matrix from 0,0 to size,size
	float			MaxDifference( const H3DMatX &m ) const;							// return maximum element difference between this and m

	bool			IsSquare( void ) const { return ( numRows == numColumns ); }
	bool			IsZero( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsIdentity( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsTriDiagonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetric( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsOrthogonal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsOrthonormal( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsPMatrix( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsZMatrix( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsPositiveDefinite( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetricPositiveDefinite( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsPositiveSemiDefinite( const float epsilon = MATRIX_EPSILON ) const;
	bool			IsSymmetricPositiveSemiDefinite( const float epsilon = MATRIX_EPSILON ) const;

	float			Trace( void ) const;											// returns product of diagonal elements
	float			Determinant( void ) const;										// returns determinant of matrix
	H3DMatX			Transpose( void ) const;										// returns transpose
	H3DMatX &		TransposeSelf( void );											// transposes the matrix itself
	H3DMatX			Inverse( void ) const;											// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseSelf( void );											// returns false if determinant is zero
	H3DMatX			InverseFast( void ) const;										// returns the inverse ( m * m.Inverse() = identity )
	bool			InverseFastSelf( void );										// returns false if determinant is zero

	bool			LowerTriangularInverse( void );									// in-place inversion, returns false if determinant is zero
	bool			UpperTriangularInverse( void );									// in-place inversion, returns false if determinant is zero

	H3DVecX			Multiply( const H3DVecX &vec ) const;							// (*this) * vec
	H3DVecX			TransposeMultiply( const H3DVecX &vec ) const;					// this->Transpose() * vec

	H3DMatX			Multiply( const H3DMatX &a ) const;								// (*this) * a
	H3DMatX			TransposeMultiply( const H3DMatX &a ) const;						// this->Transpose() * a

	void			Multiply( H3DVecX &dst, const H3DVecX &vec ) const;				// dst = (*this) * vec
	void			MultiplyAdd( H3DVecX &dst, const H3DVecX &vec ) const;			// dst += (*this) * vec
	void			MultiplySub( H3DVecX &dst, const H3DVecX &vec ) const;			// dst -= (*this) * vec
	void			TransposeMultiply( H3DVecX &dst, const H3DVecX &vec ) const;		// dst = this->Transpose() * vec
	void			TransposeMultiplyAdd( H3DVecX &dst, const H3DVecX &vec ) const;	// dst += this->Transpose() * vec
	void			TransposeMultiplySub( H3DVecX &dst, const H3DVecX &vec ) const;	// dst -= this->Transpose() * vec

	void			Multiply( H3DMatX &dst, const H3DMatX &a ) const;					// dst = (*this) * a
	void			TransposeMultiply( H3DMatX &dst, const H3DMatX &a ) const;		// dst = this->Transpose() * a

	int				GetDimension( void ) const;										// returns total number of values in matrix

	const H3DVec6 &	SubVec6( int row ) const;										// interpret beginning of row as a const H3DVec6
	H3DVec6 &		SubVec6( int row );												// interpret beginning of row as an H3DVec6
	const H3DVecX	SubVecX( int row ) const;										// interpret complete row as a const H3DVecX
	H3DVecX			SubVecX( int row );												// interpret complete row as an H3DVecX
	const float *	ToFloatPtr( void ) const;										// pointer to const matrix float array
	float *			ToFloatPtr( void );												// pointer to matrix float array
	//const char *	ToString( int precision = 2 ) const;

	void			Update_RankOne( const H3DVecX &v, const H3DVecX &w, float alpha );
	void			Update_RankOneSymmetric( const H3DVecX &v, float alpha );
	void			Update_RowColumn( const H3DVecX &v, const H3DVecX &w, int r );
	void			Update_RowColumnSymmetric( const H3DVecX &v, int r );
	void			Update_Increment( const H3DVecX &v, const H3DVecX &w );
	void			Update_IncrementSymmetric( const H3DVecX &v );
	void			Update_Decrement( int r );

	bool			Inverse_GaussJordan( void );					// invert in-place with Gauss-Jordan elimination
	bool			Inverse_UpdateRankOne( const H3DVecX &v, const H3DVecX &w, float alpha );
	bool			Inverse_UpdateRowColumn( const H3DVecX &v, const H3DVecX &w, int r );
	bool			Inverse_UpdateIncrement( const H3DVecX &v, const H3DVecX &w );
	bool			Inverse_UpdateDecrement( const H3DVecX &v, const H3DVecX &w, int r );
	void			Inverse_Solve( H3DVecX &x, const H3DVecX &b ) const;

	bool			LU_Factor( int *index, float *det = 0 );		// factor in-place: L * U
	bool			LU_UpdateRankOne( const H3DVecX &v, const H3DVecX &w, float alpha, int *index );
	bool			LU_UpdateRowColumn( const H3DVecX &v, const H3DVecX &w, int r, int *index );
	bool			LU_UpdateIncrement( const H3DVecX &v, const H3DVecX &w, int *index );
	bool			LU_UpdateDecrement( const H3DVecX &v, const H3DVecX &w, const H3DVecX &u, int r, int *index );
	void			LU_Solve( H3DVecX &x, const H3DVecX &b, const int *index ) const;
	void			LU_Inverse( H3DMatX &inv, const int *index ) const;
	void			LU_UnpackFactors( H3DMatX &L, H3DMatX &U ) const;
	void			LU_MultiplyFactors( H3DMatX &m, const int *index ) const;

	bool			QR_Factor( H3DVecX &c, H3DVecX &d );				// factor in-place: Q * R
	bool			QR_UpdateRankOne( H3DMatX &R, const H3DVecX &v, const H3DVecX &w, float alpha );
	bool			QR_UpdateRowColumn( H3DMatX &R, const H3DVecX &v, const H3DVecX &w, int r );
	bool			QR_UpdateIncrement( H3DMatX &R, const H3DVecX &v, const H3DVecX &w );
	bool			QR_UpdateDecrement( H3DMatX &R, const H3DVecX &v, const H3DVecX &w, int r );
	void			QR_Solve( H3DVecX &x, const H3DVecX &b, const H3DVecX &c, const H3DVecX &d ) const;
	void			QR_Solve( H3DVecX &x, const H3DVecX &b, const H3DMatX &R ) const;
	void			QR_Inverse( H3DMatX &inv, const H3DVecX &c, const H3DVecX &d ) const;
	void			QR_UnpackFactors( H3DMatX &Q, H3DMatX &R, const H3DVecX &c, const H3DVecX &d ) const;
	void			QR_MultiplyFactors( H3DMatX &m, const H3DVecX &c, const H3DVecX &d ) const;

	bool			SVD_Factor( H3DVecX &w, H3DMatX &V );				// factor in-place: U * Diag(w) * V.Transpose()
	void			SVD_Solve( H3DVecX &x, const H3DVecX &b, const H3DVecX &w, const H3DMatX &V ) const;
	void			SVD_Inverse( H3DMatX &inv, const H3DVecX &w, const H3DMatX &V ) const;
	void			SVD_MultiplyFactors( H3DMatX &m, const H3DVecX &w, const H3DMatX &V ) const;

	bool			Cholesky_Factor( void );						// factor in-place: L * L.Transpose()
	bool			Cholesky_UpdateRankOne( const H3DVecX &v, float alpha, int offset = 0 );
	bool			Cholesky_UpdateRowColumn( const H3DVecX &v, int r );
	bool			Cholesky_UpdateIncrement( const H3DVecX &v );
	bool			Cholesky_UpdateDecrement( const H3DVecX &v, int r );
	void			Cholesky_Solve( H3DVecX &x, const H3DVecX &b ) const;
	void			Cholesky_Inverse( H3DMatX &inv ) const;
	void			Cholesky_MultiplyFactors( H3DMatX &m ) const;

	bool			LDLT_Factor( void );							// factor in-place: L * D * L.Transpose()
	bool			LDLT_UpdateRankOne( const H3DVecX &v, float alpha, int offset = 0 );
	bool			LDLT_UpdateRowColumn( const H3DVecX &v, int r );
	bool			LDLT_UpdateIncrement( const H3DVecX &v );
	bool			LDLT_UpdateDecrement( const H3DVecX &v, int r );
	void			LDLT_Solve( H3DVecX &x, const H3DVecX &b ) const;
	void			LDLT_Inverse( H3DMatX &inv ) const;
	void			LDLT_UnpackFactors( H3DMatX &L, H3DMatX &D ) const;
	void			LDLT_MultiplyFactors( H3DMatX &m ) const;

	void			TriDiagonal_ClearTriangles( void );
	bool			TriDiagonal_Solve( H3DVecX &x, const H3DVecX &b ) const;
	void			TriDiagonal_Inverse( H3DMatX &inv ) const;

	bool			Eigen_SolveSymmetricTriDiagonal( H3DVecX &eigenValues );
	bool			Eigen_SolveSymmetric( H3DVecX &eigenValues );
	bool			Eigen_Solve( H3DVecX &realEigenValues, H3DVecX &imaginaryEigenValues );
	void			Eigen_SortIncreasing( H3DVecX &eigenValues );
	void			Eigen_SortDecreasing( H3DVecX &eigenValues );

	static void		Test( void );

private:
	int				numRows;				// number of rows
	int				numColumns;				// number of columns
	int				alloced;				// floats allocated, if -1 then mat points to data set with SetData
	float *			mat;					// memory the matrix is stored

	static float	temp[MATX_MAX_TEMP+4];	// used to store intermediate results
	static float *	tempPtr;				// pointer to 16 byte aligned temporary memory
	static int		tempIndex;				// index into memory pool, wraps around

private:
	void			SetTempSize( int rows, int columns );
	float			DeterminantGeneric( void ) const;
	bool			InverseSelfGeneric( void );
	void			QR_Rotate( H3DMatX &R, int i, float a, float b );
	float			Pythag( float a, float b ) const;
	void			SVD_BiDiag( H3DVecX &w, H3DVecX &rv1, float &anorm );
	void			SVD_InitialWV( H3DVecX &w, H3DMatX &V, H3DVecX &rv1 );
	void			HouseholderReduction( H3DVecX &diag, H3DVecX &subd );
	bool			QL( H3DVecX &diag, H3DVecX &subd );
	void			HessenbergReduction( H3DMatX &H );
	void			ComplexDivision( float xr, float xi, float yr, float yi, float &cdivr, float &cdivi );
	bool			HessenbergToRealSchur( H3DMatX &H, H3DVecX &realEigenValues, H3DVecX &imaginaryEigenValues );
};

ID_INLINE H3DMatX::H3DMatX( void ) {
	numRows = numColumns = alloced = 0;
	mat = 0;
}

ID_INLINE H3DMatX::~H3DMatX( void ) {
	// if not temp memory
	if ( mat != 0 && ( mat < H3DMatX::tempPtr || mat > H3DMatX::tempPtr + MATX_MAX_TEMP ) && alloced != -1 ) {
		Mem_Free16( mat );
	}
}

ID_INLINE H3DMatX::H3DMatX( int rows, int columns ) {
	numRows = numColumns = alloced = 0;
	mat = 0;
	SetSize( rows, columns );
}

ID_INLINE H3DMatX::H3DMatX( int rows, int columns, float *src ) {
	numRows = numColumns = alloced = 0;
	mat = 0;
	SetData( rows, columns, src );
}

ID_INLINE void H3DMatX::Set( int rows, int columns, const float *src ) {
	SetSize( rows, columns );
	memcpy( this->mat, src, rows * columns * sizeof( float ) );
}

ID_INLINE void H3DMatX::Set( const H3DMat3 &m1, const H3DMat3 &m2 ) {
	int i, j;

	SetSize( 3, 6 );
	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			mat[(i+0) * numColumns + (j+0)] = m1[i][j];
			mat[(i+0) * numColumns + (j+3)] = m2[i][j];
		}
	}
}

ID_INLINE void H3DMatX::Set( const H3DMat3 &m1, const H3DMat3 &m2, const H3DMat3 &m3, const H3DMat3 &m4 ) {
	int i, j;

	SetSize( 6, 6 );
	for ( i = 0; i < 3; i++ ) {
		for ( j = 0; j < 3; j++ ) {
			mat[(i+0) * numColumns + (j+0)] = m1[i][j];
			mat[(i+0) * numColumns + (j+3)] = m2[i][j];
			mat[(i+3) * numColumns + (j+0)] = m3[i][j];
			mat[(i+3) * numColumns + (j+3)] = m4[i][j];
		}
	}
}

ID_INLINE const float *H3DMatX::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < numRows ) );
	return mat + index * numColumns;
}

ID_INLINE float *H3DMatX::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < numRows ) );
	return mat + index * numColumns;
}

ID_INLINE H3DMatX &H3DMatX::operator=( const H3DMatX &a ) {
	SetSize( a.numRows, a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Copy16( mat, a.mat, a.numRows * a.numColumns );
#else
	memcpy( mat, a.mat, a.numRows * a.numColumns * sizeof( float ) );
#endif
	H3DMatX::tempIndex = 0;
	return *this;
}

ID_INLINE H3DMatX H3DMatX::operator*( const float a ) const {
	H3DMatX m;

	m.SetTempSize( numRows, numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Mul16( m.mat, mat, a, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		m.mat[i] = mat[i] * a;
	}
#endif
	return m;
}

ID_INLINE H3DVecX H3DMatX::operator*( const H3DVecX &vec ) const {
	H3DVecX dst;

	assert( numColumns == vec.GetSize() );

	dst.SetTempSize( numRows );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyVecX( dst, *this, vec );
#else
	Multiply( dst, vec );
#endif
	return dst;
}

ID_INLINE H3DMatX H3DMatX::operator*( const H3DMatX &a ) const {
	H3DMatX dst;

	assert( numColumns == a.numRows );

	dst.SetTempSize( numRows, a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyMatX( dst, *this, a );
#else
	Multiply( dst, a );
#endif
	return dst;
}

ID_INLINE H3DMatX H3DMatX::operator+( const H3DMatX &a ) const {
	H3DMatX m;

	assert( numRows == a.numRows && numColumns == a.numColumns );
	m.SetTempSize( numRows, numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Add16( m.mat, mat, a.mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		m.mat[i] = mat[i] + a.mat[i];
	}
#endif
	return m;
}

ID_INLINE H3DMatX H3DMatX::operator-( const H3DMatX &a ) const {
	H3DMatX m;

	assert( numRows == a.numRows && numColumns == a.numColumns );
	m.SetTempSize( numRows, numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Sub16( m.mat, mat, a.mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		m.mat[i] = mat[i] - a.mat[i];
	}
#endif
	return m;
}

ID_INLINE H3DMatX &H3DMatX::operator*=( const float a ) {
#ifdef MATX_SIMD
	SIMDProcessor->MulAssign16( mat, a, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] *= a;
	}
#endif
	H3DMatX::tempIndex = 0;
	return *this;
}

ID_INLINE H3DMatX &H3DMatX::operator*=( const H3DMatX &a ) {
	*this = *this * a;
	H3DMatX::tempIndex = 0;
	return *this;
}

ID_INLINE H3DMatX &H3DMatX::operator+=( const H3DMatX &a ) {
	assert( numRows == a.numRows && numColumns == a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->AddAssign16( mat, a.mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] += a.mat[i];
	}
#endif
	H3DMatX::tempIndex = 0;
	return *this;
}

ID_INLINE H3DMatX &H3DMatX::operator-=( const H3DMatX &a ) {
	assert( numRows == a.numRows && numColumns == a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->SubAssign16( mat, a.mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] -= a.mat[i];
	}
#endif
	H3DMatX::tempIndex = 0;
	return *this;
}

ID_INLINE H3DMatX operator*( const float a, H3DMatX const &m ) {
	return m * a;
}

ID_INLINE H3DVecX operator*( const H3DVecX &vec, const H3DMatX &m ) {
	return m * vec;
}

ID_INLINE H3DVecX &operator*=( H3DVecX &vec, const H3DMatX &m ) {
	vec = m * vec;
	return vec;
}

ID_INLINE bool H3DMatX::Compare( const H3DMatX &a ) const {
	int i, s;

	assert( numRows == a.numRows && numColumns == a.numColumns );

	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		if ( mat[i] != a.mat[i] ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DMatX::Compare( const H3DMatX &a, const float epsilon ) const {
	int i, s;

	assert( numRows == a.numRows && numColumns == a.numColumns );

	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		if ( H3DMath::Fabs( mat[i] - a.mat[i] ) > epsilon ) {
			return false;
		}
	}
	return true;
}

ID_INLINE bool H3DMatX::operator==( const H3DMatX &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DMatX::operator!=( const H3DMatX &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DMatX::SetSize( int rows, int columns ) {
	assert( mat < H3DMatX::tempPtr || mat > H3DMatX::tempPtr + MATX_MAX_TEMP );
	int alloc = ( rows * columns + 3 ) & ~3;
	if ( alloc > alloced && alloced != -1 ) {
		if ( mat != 0 ) {
			Mem_Free16( mat );
		}
		mat = (float *) Mem_Alloc16( alloc * sizeof( float ) );
		alloced = alloc;
	}
	numRows = rows;
	numColumns = columns;
	MATX_CLEAREND();
}

ID_INLINE void H3DMatX::SetTempSize( int rows, int columns ) {
	int newSize;

	newSize = ( rows * columns + 3 ) & ~3;
	assert( newSize < MATX_MAX_TEMP );
	if ( H3DMatX::tempIndex + newSize > MATX_MAX_TEMP ) {
		H3DMatX::tempIndex = 0;
	}
	mat = H3DMatX::tempPtr + H3DMatX::tempIndex;
	H3DMatX::tempIndex += newSize;
	alloced = newSize;
	numRows = rows;
	numColumns = columns;
	MATX_CLEAREND();
}

ID_INLINE void H3DMatX::SetData( int rows, int columns, float *data ) {
	assert( mat < H3DMatX::tempPtr || mat > H3DMatX::tempPtr + MATX_MAX_TEMP );
	if ( mat != 0 && alloced != -1 ) {
		Mem_Free16( mat );
	}
	assert( ( ( (int) data ) & 15 ) == 0 ); // data must be 16 byte aligned
	mat = data;
	alloced = -1;
	numRows = rows;
	numColumns = columns;
	MATX_CLEAREND();
}

ID_INLINE void H3DMatX::Zero( void ) {
#ifdef MATX_SIMD
	SIMDProcessor->Zero16( mat, numRows * numColumns );
#else
	memset( mat, 0, numRows * numColumns * sizeof( float ) );
#endif
}

ID_INLINE void H3DMatX::Zero( int rows, int columns ) {
	SetSize( rows, columns );
#ifdef MATX_SIMD
	SIMDProcessor->Zero16( mat, numRows * numColumns );
#else
	memset( mat, 0, rows * columns * sizeof( float ) );
#endif
}

ID_INLINE void H3DMatX::Identity( void ) {
	assert( numRows == numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->Zero16( mat, numRows * numColumns );
#else
	memset( mat, 0, numRows * numColumns * sizeof( float ) );
#endif
	for ( int i = 0; i < numRows; i++ ) {
		mat[i * numColumns + i] = 1.0f;
	}
}

ID_INLINE void H3DMatX::Identity( int rows, int columns ) {
	assert( rows == columns );
	SetSize( rows, columns );
	H3DMatX::Identity();
}

ID_INLINE void H3DMatX::Diag( const H3DVecX &v ) {
	Zero( v.GetSize(), v.GetSize() );
	for ( int i = 0; i < v.GetSize(); i++ ) {
		mat[i * numColumns + i] = v[i];
	}
}

ID_INLINE void H3DMatX::Random( int seed, float l, float u ) {
	int i, s;
	float c;
	H3DRandom rnd(seed);

	c = u - l;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] = l + rnd.RandomFloat() * c;
	}
}

ID_INLINE void H3DMatX::Random( int rows, int columns, int seed, float l, float u ) {
	int i, s;
	float c;
	H3DRandom rnd(seed);

	SetSize( rows, columns );
	c = u - l;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] = l + rnd.RandomFloat() * c;
	}
}

ID_INLINE void H3DMatX::Negate( void ) {
#ifdef MATX_SIMD
	SIMDProcessor->Negate16( mat, numRows * numColumns );
#else
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		mat[i] = -mat[i];
	}
#endif
}

ID_INLINE void H3DMatX::Clamp( float min, float max ) {
	int i, s;
	s = numRows * numColumns;
	for ( i = 0; i < s; i++ ) {
		if ( mat[i] < min ) {
			mat[i] = min;
		} else if ( mat[i] > max ) {
			mat[i] = max;
		}
	}
}

ID_INLINE H3DMatX &H3DMatX::SwapRows( int r1, int r2 ) {
	float *ptr;

	ptr = (float *) _alloca16( numColumns * sizeof( float ) );
	memcpy( ptr, mat + r1 * numColumns, numColumns * sizeof( float ) );
	memcpy( mat + r1 * numColumns, mat + r2 * numColumns, numColumns * sizeof( float ) );
	memcpy( mat + r2 * numColumns, ptr, numColumns * sizeof( float ) );

	return *this;
}

ID_INLINE H3DMatX &H3DMatX::SwapColumns( int r1, int r2 ) {
	int i;
	float tmp, *ptr;

	for ( i = 0; i < numRows; i++ ) {
		ptr = mat + i * numColumns;
		tmp = ptr[r1];
		ptr[r1] = ptr[r2];
		ptr[r2] = tmp;
	}

	return *this;
}

ID_INLINE H3DMatX &H3DMatX::SwapRowsColumns( int r1, int r2 ) {

	SwapRows( r1, r2 );
	SwapColumns( r1, r2 );
	return *this;
}

ID_INLINE void H3DMatX::ClearUpperTriangle( void ) {
	assert( numRows == numColumns );
	for ( int i = numRows-2; i >= 0; i-- ) {
		memset( mat + i * numColumns + i + 1, 0, (numColumns - 1 - i) * sizeof(float) );
	}
}

ID_INLINE void H3DMatX::ClearLowerTriangle( void ) {
	assert( numRows == numColumns );
	for ( int i = 1; i < numRows; i++ ) {
		memset( mat + i * numColumns, 0, i * sizeof(float) );
	}
}

ID_INLINE void H3DMatX::SquareSubMatrix( const H3DMatX &m, int size ) {
	int i;
	assert( size <= m.numRows && size <= m.numColumns );
	SetSize( size, size );
	for ( i = 0; i < size; i++ ) {
		memcpy( mat + i * numColumns, m.mat + i * m.numColumns, size * sizeof( float ) );
	}
}

ID_INLINE float H3DMatX::MaxDifference( const H3DMatX &m ) const {
	int i, j;
	float diff, maxDiff;

	assert( numRows == m.numRows && numColumns == m.numColumns );

	maxDiff = -1.0f;
	for ( i = 0; i < numRows; i++ ) {
		for ( j = 0; j < numColumns; j++ ) {
			diff = H3DMath::Fabs( mat[ i * numColumns + j ] - m[i][j] );
			if ( maxDiff < 0.0f || diff > maxDiff ) {
				maxDiff = diff;
			}
		}
	}
	return maxDiff;
}

ID_INLINE bool H3DMatX::IsZero( const float epsilon ) const {
	// returns true if (*this) == Zero
	for ( int i = 0; i < numRows; i++ ) {
		for ( int j = 0; j < numColumns; j++ ) {
			if ( H3DMath::Fabs( mat[i * numColumns + j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool H3DMatX::IsIdentity( const float epsilon ) const {
	// returns true if (*this) == Identity
	assert( numRows == numColumns );
	for ( int i = 0; i < numRows; i++ ) {
		for ( int j = 0; j < numColumns; j++ ) {
			if ( H3DMath::Fabs( mat[i * numColumns + j] - (float)( i == j ) ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool H3DMatX::IsDiagonal( const float epsilon ) const {
	// returns true if all elements are zero except for the elements on the diagonal
	assert( numRows == numColumns );
	for ( int i = 0; i < numRows; i++ ) {
		for ( int j = 0; j < numColumns; j++ ) {
			if ( i != j && H3DMath::Fabs( mat[i * numColumns + j] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool H3DMatX::IsTriDiagonal( const float epsilon ) const {
	// returns true if all elements are zero except for the elements on the diagonal plus or minus one column

	if ( numRows != numColumns ) {
		return false;
	}
	for ( int i = 0; i < numRows-2; i++ ) {
		for ( int j = i+2; j < numColumns; j++ ) {
			if ( H3DMath::Fabs( (*this)[i][j] ) > epsilon ) {
				return false;
			}
			if ( H3DMath::Fabs( (*this)[j][i] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE bool H3DMatX::IsSymmetric( const float epsilon ) const {
	// (*this)[i][j] == (*this)[j][i]
	if ( numRows != numColumns ) {
		return false;
	}
	for ( int i = 0; i < numRows; i++ ) {
		for ( int j = 0; j < numColumns; j++ ) {
			if ( H3DMath::Fabs( mat[ i * numColumns + j ] - mat[ j * numColumns + i ] ) > epsilon ) {
				return false;
			}
		}
	}
	return true;
}

ID_INLINE float H3DMatX::Trace( void ) const {
	float trace = 0.0f;

	assert( numRows == numColumns );

	// sum of elements on the diagonal
	for ( int i = 0; i < numRows; i++ ) {
		trace += mat[i * numRows + i];
	}
	return trace;
}

ID_INLINE float H3DMatX::Determinant( void ) const {

	assert( numRows == numColumns );

	switch( numRows ) {
		case 1:
			return mat[0];
		case 2:
			return reinterpret_cast<const H3DMat2 *>(mat)->Determinant();
		case 3:
			return reinterpret_cast<const H3DMat3 *>(mat)->Determinant();
		case 4:
			return reinterpret_cast<const H3DMat4 *>(mat)->Determinant();
		case 5:
			return reinterpret_cast<const H3DMat5 *>(mat)->Determinant();
		case 6:
			return reinterpret_cast<const H3DMat6 *>(mat)->Determinant();
		default:
			return DeterminantGeneric();
	}
	return 0.0f;
}

ID_INLINE H3DMatX H3DMatX::Transpose( void ) const {
	H3DMatX transpose;
	int i, j;

	transpose.SetTempSize( numColumns, numRows );

	for ( i = 0; i < numRows; i++ ) {
		for ( j = 0; j < numColumns; j++ ) {
			transpose.mat[j * transpose.numColumns + i] = mat[i * numColumns + j];
		}
	}

	return transpose;
}

ID_INLINE H3DMatX &H3DMatX::TransposeSelf( void ) {
	*this = Transpose();
	return *this;
}

ID_INLINE H3DMatX H3DMatX::Inverse( void ) const {
	H3DMatX invMat;

	invMat.SetTempSize( numRows, numColumns );
	memcpy( invMat.mat, mat, numRows * numColumns * sizeof( float ) );
	int r = invMat.InverseSelf();
	assert( r );
	return invMat;
}

ID_INLINE bool H3DMatX::InverseSelf( void ) {

	assert( numRows == numColumns );

	switch( numRows ) {
		case 1:
			if ( H3DMath::Fabs( mat[0] ) < MATRIX_INVERSE_EPSILON ) {
				return false;
			}
			mat[0] = 1.0f / mat[0];
			return true;
		case 2:
			return reinterpret_cast<H3DMat2 *>(mat)->InverseSelf();
		case 3:
			return reinterpret_cast<H3DMat3 *>(mat)->InverseSelf();
		case 4:
			return reinterpret_cast<H3DMat4 *>(mat)->InverseSelf();
		case 5:
			return reinterpret_cast<H3DMat5 *>(mat)->InverseSelf();
		case 6:
			return reinterpret_cast<H3DMat6 *>(mat)->InverseSelf();
		default:
			return InverseSelfGeneric();
	}
	return false;
}

ID_INLINE H3DMatX H3DMatX::InverseFast( void ) const {
	H3DMatX invMat;

	invMat.SetTempSize( numRows, numColumns );
	memcpy( invMat.mat, mat, numRows * numColumns * sizeof( float ) );
	int r = invMat.InverseFastSelf();
	assert( r );
	return invMat;
}

ID_INLINE bool H3DMatX::InverseFastSelf( void ) {

	assert( numRows == numColumns );

	switch( numRows ) {
		case 1:
			if ( H3DMath::Fabs( mat[0] ) < MATRIX_INVERSE_EPSILON ) {
				return false;
			}
			mat[0] = 1.0f / mat[0];
			return true;
		case 2:
			return reinterpret_cast<H3DMat2 *>(mat)->InverseFastSelf();
		case 3:
			return reinterpret_cast<H3DMat3 *>(mat)->InverseFastSelf();
		case 4:
			return reinterpret_cast<H3DMat4 *>(mat)->InverseFastSelf();
		case 5:
			return reinterpret_cast<H3DMat5 *>(mat)->InverseFastSelf();
		case 6:
			return reinterpret_cast<H3DMat6 *>(mat)->InverseFastSelf();
		default:
			return InverseSelfGeneric();
	}
	return false;
}

ID_INLINE H3DVecX H3DMatX::Multiply( const H3DVecX &vec ) const {
	H3DVecX dst;

	assert( numColumns == vec.GetSize() );

	dst.SetTempSize( numRows );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyVecX( dst, *this, vec );
#else
	Multiply( dst, vec );
#endif
	return dst;
}

ID_INLINE H3DMatX H3DMatX::Multiply( const H3DMatX &a ) const {
	H3DMatX dst;

	assert( numColumns == a.numRows );

	dst.SetTempSize( numRows, a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyMatX( dst, *this, a );
#else
	Multiply( dst, a );
#endif
	return dst;
}

ID_INLINE H3DVecX H3DMatX::TransposeMultiply( const H3DVecX &vec ) const {
	H3DVecX dst;

	assert( numRows == vec.GetSize() );

	dst.SetTempSize( numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyVecX( dst, *this, vec );
#else
	TransposeMultiply( dst, vec );
#endif
	return dst;
}

ID_INLINE H3DMatX H3DMatX::TransposeMultiply( const H3DMatX &a ) const {
	H3DMatX dst;

	assert( numRows == a.numRows );

	dst.SetTempSize( numColumns, a.numColumns );
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyMatX( dst, *this, a );
#else
	TransposeMultiply( dst, a );
#endif
	return dst;
}

ID_INLINE void H3DMatX::Multiply( H3DVecX &dst, const H3DVecX &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	mPtr = mat;
	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numRows; i++ ) {
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numColumns; j++ ) {
			sum += mPtr[j] * vPtr[j];
		}
		dstPtr[i] = sum;
		mPtr += numColumns;
	}
#endif
}

ID_INLINE void H3DMatX::MultiplyAdd( H3DVecX &dst, const H3DVecX &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyAddVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	mPtr = mat;
	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numRows; i++ ) {
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numColumns; j++ ) {
			sum += mPtr[j] * vPtr[j];
		}
		dstPtr[i] += sum;
		mPtr += numColumns;
	}
#endif
}

ID_INLINE void H3DMatX::MultiplySub( H3DVecX &dst, const H3DVecX &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplySubVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	mPtr = mat;
	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numRows; i++ ) {
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numColumns; j++ ) {
			sum += mPtr[j] * vPtr[j];
		}
		dstPtr[i] -= sum;
		mPtr += numColumns;
	}
#endif
}

ID_INLINE void H3DMatX::TransposeMultiply( H3DVecX &dst, const H3DVecX &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numColumns; i++ ) {
		mPtr = mat + i;
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numRows; j++ ) {
			mPtr += numColumns;
			sum += mPtr[0] * vPtr[j];
		}
		dstPtr[i] = sum;
	}
#endif
}

ID_INLINE void H3DMatX::TransposeMultiplyAdd( H3DVecX &dst, const H3DVecX &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyAddVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numColumns; i++ ) {
		mPtr = mat + i;
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numRows; j++ ) {
			mPtr += numColumns;
			sum += mPtr[0] * vPtr[j];
		}
		dstPtr[i] += sum;
	}
#endif
}

ID_INLINE void H3DMatX::TransposeMultiplySub( H3DVecX &dst, const H3DVecX &vec ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplySubVecX( dst, *this, vec );
#else
	int i, j;
	const float *mPtr, *vPtr;
	float *dstPtr;

	vPtr = vec.ToFloatPtr();
	dstPtr = dst.ToFloatPtr();
	for ( i = 0; i < numColumns; i++ ) {
		mPtr = mat + i;
		float sum = mPtr[0] * vPtr[0];
		for ( j = 1; j < numRows; j++ ) {
			mPtr += numColumns;
			sum += mPtr[0] * vPtr[j];
		}
		dstPtr[i] -= sum;
	}
#endif
}

ID_INLINE void H3DMatX::Multiply( H3DMatX &dst, const H3DMatX &a ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_MultiplyMatX( dst, *this, a );
#else
	int i, j, k, l, n;
	float *dstPtr;
	const float *m1Ptr, *m2Ptr;
	double sum;

	assert( numColumns == a.numRows );

	dstPtr = dst.ToFloatPtr();
	m1Ptr = ToFloatPtr();
	m2Ptr = a.ToFloatPtr();
	k = numRows;
	l = a.GetNumColumns();

	for ( i = 0; i < k; i++ ) {
		for ( j = 0; j < l; j++ ) {
			m2Ptr = a.ToFloatPtr() + j;
			sum = m1Ptr[0] * m2Ptr[0];
			for ( n = 1; n < numColumns; n++ ) {
				m2Ptr += l;
				sum += m1Ptr[n] * m2Ptr[0];
			}
			*dstPtr++ = sum;
		}
		m1Ptr += numColumns;
	}
#endif
}

ID_INLINE void H3DMatX::TransposeMultiply( H3DMatX &dst, const H3DMatX &a ) const {
#ifdef MATX_SIMD
	SIMDProcessor->MatX_TransposeMultiplyMatX( dst, *this, a );
#else
	int i, j, k, l, n;
	float *dstPtr;
	const float *m1Ptr, *m2Ptr;
	double sum;

	assert( numRows == a.numRows );

	dstPtr = dst.ToFloatPtr();
	m1Ptr = ToFloatPtr();
	k = numColumns;
	l = a.numColumns;

	for ( i = 0; i < k; i++ ) {
		for ( j = 0; j < l; j++ ) {
			m1Ptr = ToFloatPtr() + i;
			m2Ptr = a.ToFloatPtr() + j;
			sum = m1Ptr[0] * m2Ptr[0];
			for ( n = 1; n < numRows; n++ ) {
				m1Ptr += numColumns;
				m2Ptr += a.numColumns;
				sum += m1Ptr[0] * m2Ptr[0];
			}
			*dstPtr++ = sum;
		}
	}
#endif
}

ID_INLINE int H3DMatX::GetDimension( void ) const {
	return numRows * numColumns;
}

ID_INLINE const H3DVec6 &H3DMatX::SubVec6( int row ) const {
	assert( numColumns >= 6 && row >= 0 && row < numRows );
	return *reinterpret_cast<const H3DVec6 *>(mat + row * numColumns);
}

ID_INLINE H3DVec6 &H3DMatX::SubVec6( int row ) {
	assert( numColumns >= 6 && row >= 0 && row < numRows );
	return *reinterpret_cast<H3DVec6 *>(mat + row * numColumns);
}

ID_INLINE const H3DVecX H3DMatX::SubVecX( int row ) const {
	H3DVecX v;
	assert( row >= 0 && row < numRows );
	v.SetData( numColumns, mat + row * numColumns );
	return v;
}

ID_INLINE H3DVecX H3DMatX::SubVecX( int row ) {
	H3DVecX v;
	assert( row >= 0 && row < numRows );
	v.SetData( numColumns, mat + row * numColumns );
	return v;
}

ID_INLINE const float *H3DMatX::ToFloatPtr( void ) const {
	return mat;
}

ID_INLINE float *H3DMatX::ToFloatPtr( void ) {
	return mat;
}

#endif /* !__MATH_MATRIX_H__ */
