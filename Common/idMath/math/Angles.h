// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_ANGLES_H__
#define __MATH_ANGLES_H__

/*
===============================================================================

	Euler angles

===============================================================================
*/

// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

class H3DVec3;
class H3DQuat;
class H3DRotation;
class H3DMat3;
class H3DMat4;

class H3DAngles {
public:
	float			pitch;
	float			yaw;
	float			roll;

					H3DAngles( void );
					H3DAngles( float pitch, float yaw, float roll );
					explicit H3DAngles( const H3DVec3 &v );

	void 			Set( float pitch, float yaw, float roll );
	H3DAngles &		Zero( void );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	H3DAngles		operator-() const;			// negate angles, in general not the inverse rotation
	H3DAngles &		operator=( const H3DAngles &a );
	H3DAngles		operator+( const H3DAngles &a ) const;
	H3DAngles &		operator+=( const H3DAngles &a );
	H3DAngles		operator-( const H3DAngles &a ) const;
	H3DAngles &		operator-=( const H3DAngles &a );
	H3DAngles		operator*( const float a ) const;
	H3DAngles &		operator*=( const float a );
	H3DAngles		operator/( const float a ) const;
	H3DAngles &		operator/=( const float a );

	friend H3DAngles	operator*( const float a, const H3DAngles &b );

	bool			Compare( const H3DAngles &a ) const;							// exact compare, no epsilon
	bool			Compare( const H3DAngles &a, const float epsilon ) const;	// compare with epsilon
	bool			operator==(	const H3DAngles &a ) const;						// exact compare, no epsilon
	bool			operator!=(	const H3DAngles &a ) const;						// exact compare, no epsilon

	H3DAngles &		Normalize360( void );	// normalizes 'this'
	H3DAngles &		Normalize180( void );	// normalizes 'this'

	void			Clamp( const H3DAngles &min, const H3DAngles &max );

	int				GetDimension( void ) const;

	void			ToVectors( H3DVec3 *forward, H3DVec3 *right = 0, H3DVec3 *up = 0 ) const;
	H3DVec3			ToForward( void ) const;
	H3DQuat			ToQuat( void ) const;
	H3DRotation		ToRotation( void ) const;
	H3DMat3			ToMat3( void ) const;
	H3DMat4			ToMat4( void ) const;
	H3DVec3			ToAngularVelocity( void ) const;
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	//const char *	ToString( int precision = 2 ) const;
};

extern H3DAngles ang_zero;

ID_INLINE H3DAngles::H3DAngles( void ) {
}

ID_INLINE H3DAngles::H3DAngles( float pitch, float yaw, float roll ) {
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

ID_INLINE H3DAngles::H3DAngles( const H3DVec3 &v ) {
	this->pitch = v[0];
	this->yaw	= v[1];
	this->roll	= v[2];
}

ID_INLINE void H3DAngles::Set( float pitch, float yaw, float roll ) {
	this->pitch = pitch;
	this->yaw	= yaw;
	this->roll	= roll;
}

ID_INLINE H3DAngles &H3DAngles::Zero( void ) {
	pitch = yaw = roll = 0.0f;
	return *this;
}

ID_INLINE float H3DAngles::operator[]( int index ) const {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

ID_INLINE float &H3DAngles::operator[]( int index ) {
	assert( ( index >= 0 ) && ( index < 3 ) );
	return ( &pitch )[ index ];
}

ID_INLINE H3DAngles H3DAngles::operator-() const {
	return H3DAngles( -pitch, -yaw, -roll );
}

ID_INLINE H3DAngles &H3DAngles::operator=( const H3DAngles &a ) {
	pitch	= a.pitch;
	yaw		= a.yaw;
	roll	= a.roll;
	return *this;
}

ID_INLINE H3DAngles H3DAngles::operator+( const H3DAngles &a ) const {
	return H3DAngles( pitch + a.pitch, yaw + a.yaw, roll + a.roll );
}

ID_INLINE H3DAngles& H3DAngles::operator+=( const H3DAngles &a ) {
	pitch	+= a.pitch;
	yaw		+= a.yaw;
	roll	+= a.roll;

	return *this;
}

ID_INLINE H3DAngles H3DAngles::operator-( const H3DAngles &a ) const {
	return H3DAngles( pitch - a.pitch, yaw - a.yaw, roll - a.roll );
}

ID_INLINE H3DAngles& H3DAngles::operator-=( const H3DAngles &a ) {
	pitch	-= a.pitch;
	yaw		-= a.yaw;
	roll	-= a.roll;

	return *this;
}

ID_INLINE H3DAngles H3DAngles::operator*( const float a ) const {
	return H3DAngles( pitch * a, yaw * a, roll * a );
}

ID_INLINE H3DAngles& H3DAngles::operator*=( float a ) {
	pitch	*= a;
	yaw		*= a;
	roll	*= a;
	return *this;
}

ID_INLINE H3DAngles H3DAngles::operator/( const float a ) const {
	float inva = 1.0f / a;
	return H3DAngles( pitch * inva, yaw * inva, roll * inva );
}

ID_INLINE H3DAngles& H3DAngles::operator/=( float a ) {
	float inva = 1.0f / a;
	pitch	*= inva;
	yaw		*= inva;
	roll	*= inva;
	return *this;
}

ID_INLINE H3DAngles operator*( const float a, const H3DAngles &b ) {
	return H3DAngles( a * b.pitch, a * b.yaw, a * b.roll );
}

ID_INLINE bool H3DAngles::Compare( const H3DAngles &a ) const {
	return ( ( a.pitch == pitch ) && ( a.yaw == yaw ) && ( a.roll == roll ) );
}

ID_INLINE bool H3DAngles::Compare( const H3DAngles &a, const float epsilon ) const {
	if ( H3DMath::Fabs( pitch - a.pitch ) > epsilon ) {
		return false;
	}
			
	if ( H3DMath::Fabs( yaw - a.yaw ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( roll - a.roll ) > epsilon ) {
		return false;
	}

	return true;
}

ID_INLINE bool H3DAngles::operator==( const H3DAngles &a ) const {
	return Compare( a );
}

ID_INLINE bool H3DAngles::operator!=( const H3DAngles &a ) const {
	return !Compare( a );
}

ID_INLINE void H3DAngles::Clamp( const H3DAngles &min, const H3DAngles &max ) {
	if ( pitch < min.pitch ) {
		pitch = min.pitch;
	} else if ( pitch > max.pitch ) {
		pitch = max.pitch;
	}
	if ( yaw < min.yaw ) {
		yaw = min.yaw;
	} else if ( yaw > max.yaw ) {
		yaw = max.yaw;
	}
	if ( roll < min.roll ) {
		roll = min.roll;
	} else if ( roll > max.roll ) {
		roll = max.roll;
	}
}

ID_INLINE int H3DAngles::GetDimension( void ) const {
	return 3;
}

ID_INLINE const float *H3DAngles::ToFloatPtr( void ) const {
	return &pitch;
}

ID_INLINE float *H3DAngles::ToFloatPtr( void ) {
	return &pitch;
}

#endif /* !__MATH_ANGLES_H__ */
