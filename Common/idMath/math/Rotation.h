// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_ROTATION_H__
#define __MATH_ROTATION_H__

/*
===============================================================================

	Describes a complete rotation in degrees about an abritray axis.
	A local rotation matrix is stored for fast rotation of multiple points.

===============================================================================
*/


class H3DAngles;
class H3DQuat;
class H3DMat3;

class H3DRotation {

	friend class H3DAngles;
	friend class H3DQuat;
	friend class H3DMat3;

public:
						H3DRotation( void );
						H3DRotation( const H3DVec3 &rotationOrigin, const H3DVec3 &rotationVec, const float rotationAngle );

	void				Set( const H3DVec3 &rotationOrigin, const H3DVec3 &rotationVec, const float rotationAngle );
	void				SetOrigin( const H3DVec3 &rotationOrigin );
	void				SetVec( const H3DVec3 &rotationVec );					// has to be normalized
	void				SetVec( const float x, const float y, const float z );	// has to be normalized
	void				SetAngle( const float rotationAngle );
	void				Scale( const float s );
	void				ReCalculateMatrix( void );
	const H3DVec3 &		GetOrigin( void ) const;
	const H3DVec3 &		GetVec( void ) const;
	float				GetAngle( void ) const;

	H3DRotation			operator-() const;										// flips rotation
	H3DRotation			operator*( const float s ) const;						// scale rotation
	H3DRotation			operator/( const float s ) const;						// scale rotation
	H3DRotation &		operator*=( const float s );							// scale rotation
	H3DRotation &		operator/=( const float s );							// scale rotation
	H3DVec3				operator*( const H3DVec3 &v ) const;						// rotate vector

	friend H3DRotation	operator*( const float s, const H3DRotation &r );		// scale rotation
	friend H3DVec3		operator*( const H3DVec3 &v, const H3DRotation &r );		// rotate vector
	friend H3DVec3 &		operator*=( H3DVec3 &v, const H3DRotation &r );			// rotate vector

	H3DAngles			ToAngles( void ) const;
	H3DQuat				ToQuat( void ) const;
	const H3DMat3 &		ToMat3( void ) const;
	H3DMat4				ToMat4( void ) const;
	H3DVec3				ToAngularVelocity( void ) const;

	void				RotatePoint( H3DVec3 &point ) const;

	void				Normalize180( void );
	void				Normalize360( void );

private:
	H3DVec3				origin;			// origin of rotation
	H3DVec3				vec;			// normalized vector to rotate around
	float				angle;			// angle of rotation in degrees
	mutable H3DMat3		axis;			// rotation axis
	mutable bool		axisValid;		// true if rotation axis is valid
};


ID_INLINE H3DRotation::H3DRotation( void ) {
}

ID_INLINE H3DRotation::H3DRotation( const H3DVec3 &rotationOrigin, const H3DVec3 &rotationVec, const float rotationAngle ) {
	origin = rotationOrigin;
	vec = rotationVec;
	angle = rotationAngle;
	axisValid = false;
}

ID_INLINE void H3DRotation::Set( const H3DVec3 &rotationOrigin, const H3DVec3 &rotationVec, const float rotationAngle ) {
	origin = rotationOrigin;
	vec = rotationVec;
	angle = rotationAngle;
	axisValid = false;
}

ID_INLINE void H3DRotation::SetOrigin( const H3DVec3 &rotationOrigin ) {
	origin = rotationOrigin;
}

ID_INLINE void H3DRotation::SetVec( const H3DVec3 &rotationVec ) {
	vec = rotationVec;
	axisValid = false;
}

ID_INLINE void H3DRotation::SetVec( float x, float y, float z ) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	axisValid = false;
}

ID_INLINE void H3DRotation::SetAngle( const float rotationAngle ) {
	angle = rotationAngle;
	axisValid = false;
}

ID_INLINE void H3DRotation::Scale( const float s ) {
	angle *= s;
	axisValid = false;
}

ID_INLINE void H3DRotation::ReCalculateMatrix( void ) {
	axisValid = false;
	ToMat3();
}

ID_INLINE const H3DVec3 &H3DRotation::GetOrigin( void ) const {
	return origin;
}

ID_INLINE const H3DVec3 &H3DRotation::GetVec( void ) const  {
	return vec;
}

ID_INLINE float H3DRotation::GetAngle( void ) const  {
	return angle;
}

ID_INLINE H3DRotation H3DRotation::operator-() const {
	return H3DRotation( origin, vec, -angle );
}

ID_INLINE H3DRotation H3DRotation::operator*( const float s ) const {
	return H3DRotation( origin, vec, angle * s );
}

ID_INLINE H3DRotation H3DRotation::operator/( const float s ) const {
	assert( s != 0.0f );
	return H3DRotation( origin, vec, angle / s );
}

ID_INLINE H3DRotation &H3DRotation::operator*=( const float s ) {
	angle *= s;
	axisValid = false;
	return *this;
}

ID_INLINE H3DRotation &H3DRotation::operator/=( const float s ) {
	assert( s != 0.0f );
	angle /= s;
	axisValid = false;
	return *this;
}

ID_INLINE H3DVec3 H3DRotation::operator*( const H3DVec3 &v ) const {
	if ( !axisValid ) {
		ToMat3();
	}
	return ((v - origin) * axis + origin);
}

ID_INLINE H3DRotation operator*( const float s, const H3DRotation &r ) {
	return r * s;
}

ID_INLINE H3DVec3 operator*( const H3DVec3 &v, const H3DRotation &r ) {
	return r * v;
}

ID_INLINE H3DVec3 &operator*=( H3DVec3 &v, const H3DRotation &r ) {
	v = r * v;
	return v;
}

ID_INLINE void H3DRotation::RotatePoint( H3DVec3 &point ) const {
	if ( !axisValid ) {
		ToMat3();
	}
	point = ((point - origin) * axis + origin);
}

#endif /* !__MATH_ROTATION_H__ */
