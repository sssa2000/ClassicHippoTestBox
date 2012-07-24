// Copyright (C) 2004 Id Software, Inc.
//


#pragma hdrstop
//#include "vector.h"
//#include "../str.h"
#include "../dmathheader.h"
//#ifdef _WIN32
#pragma  warning(push)
#pragma  warning(disable : 4311)
#pragma  warning(disable : 4312)
//#endif
H3DVec2 vec2_origin( 0.0f, 0.0f );
H3DVec3 vec3_origin( 0.0f, 0.0f, 0.0f );
H3DVec3 vec3_unitX( 1.0f, 0.0f, 0.0f );
H3DVec3 vec3_unitY( 0.0f, 1.0f, 0.0f );
H3DVec3 vec3_unitZ( 0.0f, 0.0f, 1.0f );
H3DVec4 vec4_origin( 0.0f, 0.0f, 0.0f, 0.0f );
H3DVec5 vec5_origin( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
H3DVec6 vec6_origin( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f );
H3DVec6 vec6_infinity( H3DMath::INFINITY, H3DMath::INFINITY, H3DMath::INFINITY, H3DMath::INFINITY, H3DMath::INFINITY, H3DMath::INFINITY );


//===============================================================
//
//	H3DVec2
//
//===============================================================

/*
=============
H3DVec2::ToString
=============
*/
//const char *H3DVec2::ToString( int precision ) const {
//	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
//}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void H3DVec2::Lerp( const H3DVec2 &v1, const H3DVec2 &v2, const float l ) {
	if ( l <= 0.0f ) {
		(*this) = v1;
	} else if ( l >= 1.0f ) {
		(*this) = v2;
	} else {
		(*this) = v1 + l * ( v2 - v1 );
	}
}


//===============================================================
//
//	H3DVec3
//
//===============================================================

/*
=============
H3DVec3::ToYaw
=============
*/
float H3DVec3::ToYaw( void ) const {
	float yaw;
	
	if ( ( y == 0.0f ) && ( x == 0.0f ) ) {
		yaw = 0.0f;
	} else {
		yaw = RAD2DEG( atan2( y, x ) );
		if ( yaw < 0.0f ) {
			yaw += 360.0f;
		}
	}

	return yaw;
}

/*
=============
H3DVec3::ToPitch
=============
*/
float H3DVec3::ToPitch( void ) const {
	float	forward;
	float	pitch;
	
	if ( ( x == 0.0f ) && ( y == 0.0f ) ) {
		if ( z > 0.0f ) {
			pitch = 90.0f;
		} else {
			pitch = 270.0f;
		}
	} else {
		forward = ( float )H3DMath::Sqrt( x * x + y * y );
		pitch = RAD2DEG( atan2( z, forward ) );
		if ( pitch < 0.0f ) {
			pitch += 360.0f;
		}
	}

	return pitch;
}

/*
=============
H3DVec3::ToAngles
=============
*/
H3DAngles H3DVec3::ToAngles( void ) const {
	float forward;
	float yaw;
	float pitch;
	
	if ( ( x == 0.0f ) && ( y == 0.0f ) ) {
		yaw = 0.0f;
		if ( z > 0.0f ) {
			pitch = 90.0f;
		} else {
			pitch = 270.0f;
		}
	} else {
		yaw = RAD2DEG( atan2( y, x ) );
		if ( yaw < 0.0f ) {
			yaw += 360.0f;
		}

		forward = ( float )H3DMath::Sqrt( x * x + y * y );
		pitch = RAD2DEG( atan2( z, forward ) );
		if ( pitch < 0.0f ) {
			pitch += 360.0f;
		}
	}

	return H3DAngles( -pitch, yaw, 0.0f );
}

/*
=============
H3DVec3::ToPolar
=============
*/
idPolar3 H3DVec3::ToPolar( void ) const {
	float forward;
	float yaw;
	float pitch;
	
	if ( ( x == 0.0f ) && ( y == 0.0f ) ) {
		yaw = 0.0f;
		if ( z > 0.0f ) {
			pitch = 90.0f;
		} else {
			pitch = 270.0f;
		}
	} else {
		yaw = RAD2DEG( atan2( y, x ) );
		if ( yaw < 0.0f ) {
			yaw += 360.0f;
		}

		forward = ( float )H3DMath::Sqrt( x * x + y * y );
		pitch = RAD2DEG( atan2( z, forward ) );
		if ( pitch < 0.0f ) {
			pitch += 360.0f;
		}
	}
	return idPolar3( H3DMath::Sqrt( x * x + y * y + z * z ), yaw, -pitch );
}

/*
=============
H3DVec3::ToMat3
=============
*/
H3DMat3 H3DVec3::ToMat3( void ) const {
	H3DMat3	mat;
	float	d;

	mat[0] = *this;
	d = x * x + y * y;
	if ( !d ) {
		mat[1][0] = 1.0f;
		mat[1][1] = 0.0f;
		mat[1][2] = 0.0f;
	} else {
		d = H3DMath::InvSqrt( d );
		mat[1][0] = -y * d;
		mat[1][1] = x * d;
		mat[1][2] = 0.0f;
	}
	mat[2] = Cross( mat[1] );

	return mat;
}

/*
=============
H3DVec3::ToString
=============
*/
//const char *H3DVec3::ToString( int precision ) const {
//	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
//}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void H3DVec3::Lerp( const H3DVec3 &v1, const H3DVec3 &v2, const float l ) {
	if ( l <= 0.0f ) {
		(*this) = v1;
	} else if ( l >= 1.0f ) {
		(*this) = v2;
	} else {
		(*this) = v1 + l * ( v2 - v1 );
	}
}

/*
=============
SLerp

Spherical linear interpolation from v1 to v2.
Vectors are expected to be normalized.
=============
*/
#define LERP_DELTA 1e-6

void H3DVec3::SLerp( const H3DVec3 &v1, const H3DVec3 &v2, const float t ) {
	float omega, cosom, sinom, scale0, scale1;

	if ( t <= 0.0f ) {
		(*this) = v1;
		return;
	} else if ( t >= 1.0f ) {
		(*this) = v2;
		return;
	}

	//cosom = v1 * v2;
	cosom = v1.Dot(v2);
	if ( ( 1.0f - cosom ) > LERP_DELTA ) {
		omega = acos( cosom );
		sinom = sin( omega );
		scale0 = sin( ( 1.0f - t ) * omega ) / sinom;
		scale1 = sin( t * omega ) / sinom;
	} else {
		scale0 = 1.0f - t;
		scale1 = t;
	}

	(*this) = ( v1 * scale0 + v2 * scale1 );
}

/*
=============
ProjectSelfOntoSphere

Projects the z component onto a sphere.
=============
*/
void H3DVec3::ProjectSelfOntoSphere( const float radius ) {
	float rsqr = radius * radius;
	float len = Length();
	if ( len  < rsqr * 0.5f ) {
		z = sqrt( rsqr - len );
	} else {
		z = rsqr / ( 2.0f * sqrt( len ) );
	}
}



//===============================================================
//
//	H3DVec4
//
//===============================================================

/*
=============
H3DVec4::ToString
=============
*/
//const char *H3DVec4::ToString( int precision ) const {
//	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
//}

/*
=============
Lerp

Linearly inperpolates one vector to another.
=============
*/
void H3DVec4::Lerp( const H3DVec4 &v1, const H3DVec4 &v2, const float l ) {
	if ( l <= 0.0f ) {
		(*this) = v1;
	} else if ( l >= 1.0f ) {
		(*this) = v2;
	} else {
		(*this) = v1 + l * ( v2 - v1 );
	}
}


//===============================================================
//
//	H3DVec5
//
//===============================================================

/*
=============
H3DVec5::ToString
=============
*/
//const char *H3DVec5::ToString( int precision ) const {
//	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
//}

/*
=============
H3DVec5::Lerp
=============
*/
void H3DVec5::Lerp( const H3DVec5 &v1, const H3DVec5 &v2, const float l ) {
	if ( l <= 0.0f ) {
		(*this) = v1;
	} else if ( l >= 1.0f ) {
		(*this) = v2;
	} else {
		x = v1.x + l * ( v2.x - v1.x );
		y = v1.y + l * ( v2.y - v1.y );
		z = v1.z + l * ( v2.z - v1.z );
		s = v1.s + l * ( v2.s - v1.s );
		t = v1.t + l * ( v2.t - v1.t );
	}
}


//===============================================================
//
//	H3DVec6
//
//===============================================================

/*
=============
H3DVec6::ToString
=============
*/
//const char *H3DVec6::ToString( int precision ) const {
//	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
//}


//===============================================================
//
//	H3DVecX
//
//===============================================================

float	H3DVecX::temp[VECX_MAX_TEMP+4];
float *	H3DVecX::tempPtr = (float *) ( ( (int) H3DVecX::temp + 15 ) & ~15 );
int		H3DVecX::tempIndex = 0;

/*
=============
H3DVecX::ToString
=============
*/
//const char *H3DVecX::ToString( int precision ) const {
//	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
//}


// by wh
// from <geometric tools for computer graphics>
float TrianglePointMinDistance(const H3DVec3& v0, const H3DVec3& v1, const H3DVec3& v2, const H3DVec3& P, H3DVec3& minDistTriPoint)
{
	H3DVec3 e0 = v1-v0;
	H3DVec3 e1 = v2-v0;
	H3DVec3 vecD = v0-P;
	float a = e0.LengthSqr();
	float b = e0.Dot(e1);
	float c = e1.LengthSqr();
	float d = e0.Dot(vecD);
	float e = e1.Dot(vecD);
	float f = vecD.LengthSqr();

	float det = a*c-b*b;
	float s = b*e-c*d;
	float t = b*d-a*e;
	if (s+t<=det)
	{
		if (s<0)
		{
			if (t<0)
			{	//reg 4
				if (d<0)
				{
					t = 0;
					if (a<0)
					{
						s = 0;
					}
					else if (a+d<0)
					{
						s=1;
					}
					else
					{
						s = -d/a;
					}
				}
				else
				{
					s = 0;
					if (c<0)
					{
						t=0;
					}
					else if (c+e<0)
					{
						t=1;
					}
					else
					{
						t=-e/c;
					}
				}
			}
			else
			{  //reg3
				s = 0;
				t = (e >= 0 ? 0 : (-e>=c ? 1:-e/c));
			}
		}
		else
		{
			if (t<0)
			{  //reg5
				t = 0;
				s = (d >= 0 ? 0 : (-d>=a ? 1:-d/a));
			}
			else
			{	//reg0
				float invDet = 1/det;
				s *= invDet;
				t *= invDet;
			}
		}
	}
	else
	{
		if (s<0)
		{	//reg2
			float tmp0 = b+d;
			float tmp1 = c+e;
			if (tmp1>tmp0)
			{
				float numer = tmp1-tmp0;
				float denom = a-2*b+c;
				s = (numer>=denom?1:numer/denom);
				t=1-s;
			}
			else
			{
				s=0;
				t = (tmp1<=0 ? 1 : (e>=0 ? 0 : -e/c));
			}
		}
		else if (t<0)
		{	//reg 6
			if (a+d>0)
			{
				t=0;
				if (a*d>0)
				{
					s=0;
				}
				else if (d/a<-1)
				{
					s=1;
				}
				else
				{
					s=-d/a;
				}
			}
			else
			{
				float tmp0 = b+d-e-c;
				float tmp1 = a-2*b+c;// gauranted greater than zero
				if (tmp0<0)
				{
					s = 0;
				}
				else if (tmp0>tmp1)
				{
					s=1;
				}
				else
				{
					s=tmp0/tmp1;
				}

				t=1-s;
			}
		}
		else
		{	//reg1
			float numer = c+e-b-d;
			if (numer<=0)
			{
				s = 0;
			}
			else
			{
				float denom = a-2*b+c;
				s = (numer>=denom ? 1:numer/denom);
			}
			t = 1-s;
		}
	}

	minDistTriPoint = v0+s*e0+t*e1;
	vecD = minDistTriPoint-P;
	return vecD.Length();
}

#pragma  warning(pop)
