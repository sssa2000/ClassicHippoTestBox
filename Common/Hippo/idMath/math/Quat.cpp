// Copyright (C) 2004 Id Software, Inc.
//

#include "../dmathheader.h"
#pragma hdrstop

//H3DQuat quat_identity(0.0f, 0.0f, 0.0f, 1.0f);
/*
=====================
H3DQuat::ToAngles
=====================
*/
H3DAngles H3DQuat::ToAngles( void ) const {
	return ToMat3().ToAngles();
}

/*
=====================
H3DQuat::ToRotation
=====================
*/
H3DRotation H3DQuat::ToRotation( void ) const {
	H3DVec3 vec;
	float angle;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	angle = H3DMath::ACos( w );
	if ( angle == 0.0f ) {
		vec.Set( 0.0f, 0.0f, 1.0f );
	} else {
		//vec *= (1.0f / sin( angle ));
		vec.Normalize();
		vec.FixDegenerateNormal();
		angle *= 2.0f * H3DMath::M_RAD2DEG;
	}
	return H3DRotation( vec3_origin, vec, angle );
}

void H3DQuat::FromAngleAxis(float degree, const H3DVec3& axis)
{
	H3DVec3 temp = axis;
	temp.Normalize();
	x = temp.x;
	y = temp.y;
	z = temp.z;
	float Half = H3DMath::M_DEG2RAD*degree*0.5f;
	w = H3DMath::Cos(Half);
	float HalfSin = H3DMath::Sin(Half);
	x *= HalfSin;
	y *= HalfSin;
	z *= HalfSin;
}

void H3DQuat::GetRotationTo(const H3DVec3& From, const H3DVec3& To)
{
	H3DVec3 tempFrom = From;
	H3DVec3 tempTo = To;
	tempFrom.Normalize();
	tempTo.Normalize();

	H3DVec3 Cross = tempFrom.Cross(tempTo);

	float d = tempFrom.Dot(tempTo);
	if (d>=1.0f)
	{
		Identity();
	}
	else if (d<=-0.999f)//when From = -To
	{
		if (fabs(From.x)>=0.01f)
		{
			Cross.Set((From.y+From.z)/From.x, -1.0f, -1.0f);//choose an arbitrary axis perpendicular to From
			Cross.Normalize();
		}
		else if (fabs(From.y)>=0.01f)
		{
			Cross.Set(-1.0f, (From.x+From.z)/From.y, -1.0f);//choose an arbitrary axis perpendicular to From
			Cross.Normalize();
		}
		else
		{
			Cross.Set(-1.0f, -1.0f, (From.x+From.y)/From.z);//choose an arbitrary axis perpendicular to From
			Cross.Normalize();
		}

		float Half = H3DMath::M_DEG2RAD*90.0f;//we rotate 180 degrees
		w = H3DMath::Cos(Half);
		float HalfSin = H3DMath::Sin(Half);
		x = HalfSin*Cross.x;
		y = HalfSin*Cross.y;
		z = HalfSin*Cross.z;
	}
	else
	{
		float s = H3DMath::Sqrt( (1.0f+d)*2.0f );
		float invs = 1.0f/s;
		x = Cross.x * invs;
		y = Cross.y * invs;
		z = Cross.z * invs;
		w = s*0.5f;
	}
}


/*
=====================
H3DQuat::ToMat3
=====================
*/
H3DMat3 H3DQuat::ToMat3( void ) const {
	H3DMat3	mat;
	float	wx, wy, wz;
	float	xx, yy, yz;
	float	xy, xz, zz;
	float	x2, y2, z2;

	x2 = x + x;
	y2 = y + y;
	z2 = z + z;

	xx = x * x2;
	xy = x * y2;
	xz = x * z2;

	yy = y * y2;
	yz = y * z2;
	zz = z * z2;

	wx = w * x2;
	wy = w * y2;
	wz = w * z2;

	mat[ 0 ][ 0 ] = 1.0f - ( yy + zz );
	mat[ 0 ][ 1 ] = xy - wz;
	mat[ 0 ][ 2 ] = xz + wy;

	mat[ 1 ][ 0 ] = xy + wz;
	mat[ 1 ][ 1 ] = 1.0f - ( xx + zz );
	mat[ 1 ][ 2 ] = yz - wx;

	mat[ 2 ][ 0 ] = xz - wy;
	mat[ 2 ][ 1 ] = yz + wx;
	mat[ 2 ][ 2 ] = 1.0f - ( xx + yy );

	return mat;
}

/*
=====================
H3DQuat::ToMat4
=====================
*/
H3DMat4 H3DQuat::ToMat4( void ) const {
	return ToMat3().ToMat4();
}

/*
=====================
H3DQuat::ToCQuat
=====================
*/
H3DCQuat H3DQuat::ToCQuat( void ) const {
	if ( w < 0.0f ) {
		return H3DCQuat( -x, -y, -z );
	}
	return H3DCQuat( x, y, z );
}

/*
============
H3DQuat::ToAngularVelocity
============
*/
H3DVec3 H3DQuat::ToAngularVelocity( void ) const {
	H3DVec3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.Normalize();
	return vec * H3DMath::ACos( w );
}

/*
=============
H3DQuat::ToString
=============
*/
//const char *H3DQuat::ToString( int precision ) const {
//	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
//}

/*
=====================
H3DQuat::Slerp

Spherical linear interpolation between two H3DQuats.
=====================
*/
H3DQuat &H3DQuat::Slerp( const H3DQuat &from, const H3DQuat &to, float t ) {
	H3DQuat	temp;
	float	omega, cosom, sinom, scale0, scale1;

	if ( t <= 0.0f ) {
		*this = from;
		return *this;
	}

	if ( t >= 1.0f ) {
		*this = to;
		return *this;
	}

	if ( from == to ) {
		*this = to;
		return *this;
	}

	cosom = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;
	if ( cosom < 0.0f ) {
		temp = -to;
		cosom = -cosom;
	} else {
		temp = to;
	}

	if ( ( 1.0f - cosom ) > 1e-6f ) {
#if 0
		omega = acos( cosom );
		sinom = 1.0f / sin( omega );
		scale0 = sin( ( 1.0f - t ) * omega ) * sinom;
		scale1 = sin( t * omega ) * sinom;
#else
		scale0 = 1.0f - cosom * cosom;
		sinom = H3DMath::InvSqrt( scale0 );
		omega = H3DMath::ATan16( scale0 * sinom, cosom );
		scale0 = H3DMath::Sin16( ( 1.0f - t ) * omega ) * sinom;
		scale1 = H3DMath::Sin16( t * omega ) * sinom;
#endif
	} else {
		scale0 = 1.0f - t;
		scale1 = t;
	}

	*this = ( scale0 * from ) + ( scale1 * temp );
	return *this;
}

/*
=============
H3DCQuat::ToAngles
=============
*/
H3DAngles H3DCQuat::ToAngles( void ) const {
	return ToQuat().ToAngles();
}

/*
=============
H3DCQuat::ToRotation
=============
*/
H3DRotation H3DCQuat::ToRotation( void ) const {
	return ToQuat().ToRotation();
}

/*
=============
H3DCQuat::ToMat3
=============
*/
H3DMat3 H3DCQuat::ToMat3( void ) const {
	return ToQuat().ToMat3();
}

/*
=============
H3DCQuat::ToMat4
=============
*/
H3DMat4 H3DCQuat::ToMat4( void ) const {
	return ToQuat().ToMat4();
}

void H3DQuat::StripX(const H3DVec3& input)//将input选转到YZ平面
{
	H3DVec3 tmp(input);
	tmp.x = 0.0f;
	tmp.Normalize();
	GetRotationTo(input, tmp);
}

void H3DQuat::StripY(const H3DVec3& input)//将input选转到XZ平面
{
	H3DVec3 tmp(input);
	tmp.y = 0.0f;
	tmp.Normalize();
	GetRotationTo(input, tmp);
}

void H3DQuat::StripZ(const H3DVec3& input)//将input选转到XY平面
{
	H3DVec3 tmp(input);
	tmp.z = 0.0f;
	tmp.Normalize();
	GetRotationTo(input, tmp);
}

H3DQuat H3DQuat::QslerpNoInvert(const H3DQuat &q1,const H3DQuat &q2,float t)
{
	float dot = q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;

	if (dot > -0.95f && dot < 0.95f)
	{
		float angle = static_cast<float>(acos(dot));
		float sina,sinat,sinaomt;
		sina = static_cast<float>(sin(angle));
		sinat = static_cast<float>(sin(angle*t));
		sinaomt = static_cast<float>(sin(angle*(1-t)));
		return (q1*sinaomt+q2*sinat)*(1/sina);
	}
	/*
	if the angle is small, use linear interpolation
	*/
	else
	{
		return Lerp(q1,q2,t);
	}
}

H3DQuat H3DQuat::Squad (float fT,
							  const H3DQuat& rkP, const H3DQuat& rkA,
							  const H3DQuat& rkB, const H3DQuat& rkQ)
{
	H3DQuat c,d;
	c = QslerpNoInvert(rkP,rkQ,fT);
	d = QslerpNoInvert(rkA,rkB,fT);
	return QslerpNoInvert(c,d,2*fT*(1-fT));
}

H3DQuat H3DQuat::Lerp(const H3DQuat &q1,const H3DQuat &q2,float t)
{
	H3DQuat ret;
	ret = q1 + t*(q2-q1);
	/*
	return value must be normalized
	*/
	ret.Normalize();
	return ret;
}

H3DQuat H3DQuat::Loga() const
{
	float a = static_cast<float>(acos(w));
	float sina = static_cast<float>(sin(a));
	H3DQuat ret;
	ret.w = 0;
	if (sina > 0)
	{
		ret.x = a*x/sina;
		ret.y = a*y/sina;
		ret.z = a*z/sina;
	}
	else
	{
		ret.x=ret.y=ret.z=0;
	}
	return ret;
}

H3DQuat H3DQuat::Exp() const
{
	float a = static_cast<float>(sqrt(x*x + y*y + z*z));
	float sina = static_cast<float>(sin(a));
	float cosa = static_cast<float>(cos(a));
	H3DQuat ret;

	ret.w = cosa;
	if(a > 0)
	{
		ret.x = sina * x / a;
		ret.y = sina * y / a;
		ret.z = sina * z / a;
	}
	else
	{
		ret.x = ret.y = ret.z = 0;
	}

	return ret;
}


/*
=============
H3DCQuat::ToString
=============
*/
//const char *H3DCQuat::ToString( int precision ) const {
//	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
//}
