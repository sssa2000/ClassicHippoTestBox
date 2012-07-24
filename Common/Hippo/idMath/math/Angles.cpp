// Copyright (C) 2004 Id Software, Inc.
//


#pragma hdrstop
#include "../dmathheader.h"
H3DAngles ang_zero( 0.0f, 0.0f, 0.0f );


/*
=================
H3DAngles::Normalize360

returns angles normalized to the range [0 <= angle < 360]
=================
*/
H3DAngles& H3DAngles::Normalize360( void ) {
	int i;

	for ( i = 0; i < 3; i++ ) {
		if ( ( (*this)[i] >= 360.0f ) || ( (*this)[i] < 0.0f ) ) {
			(*this)[i] -= floor( (*this)[i] / 360.0f ) * 360.0f;

			if ( (*this)[i] >= 360.0f ) {
				(*this)[i] -= 360.0f;
			}
			if ( (*this)[i] < 0.0f ) {
				(*this)[i] += 360.0f;
			}
		}
	}

	return *this;
}

/*
=================
H3DAngles::Normalize180

returns angles normalized to the range [-180 < angle <= 180]
=================
*/
H3DAngles& H3DAngles::Normalize180( void ) {
	Normalize360();

	if ( pitch > 180.0f ) {
		pitch -= 360.0f;
	}
	
	if ( yaw > 180.0f ) {
		yaw -= 360.0f;
	}

	if ( roll > 180.0f ) {
		roll -= 360.0f;
	}
	return *this;
}

/*
=================
H3DAngles::ToVectors
=================
*/
void H3DAngles::ToVectors( H3DVec3 *forward, H3DVec3 *right, H3DVec3 *up ) const {
	float sr, sp, sy, cr, cp, cy;
	
	H3DMath::SinCos( DEG2RAD( yaw ), sy, cy );
	H3DMath::SinCos( DEG2RAD( pitch ), sp, cp );
	H3DMath::SinCos( DEG2RAD( roll ), sr, cr );

	if ( forward ) {
		forward->Set( cp * cy, cp * sy, -sp );
	}

	if ( right ) {
		right->Set( -sr * sp * cy + cr * sy, -sr * sp * sy + -cr * cy, -sr * cp );
	}

	if ( up ) {
		up->Set( cr * sp * cy + -sr * -sy, cr * sp * sy + -sr * cy, cr * cp );
	}
}

/*
=================
H3DAngles::ToForward
=================
*/
H3DVec3 H3DAngles::ToForward( void ) const {
	float sp, sy, cp, cy;
	
	H3DMath::SinCos( DEG2RAD( yaw ), sy, cy );
	H3DMath::SinCos( DEG2RAD( pitch ), sp, cp );

	return H3DVec3( cp * cy, cp * sy, -sp );
}

/*
=================
H3DAngles::ToQuat
=================
*/
H3DQuat H3DAngles::ToQuat( void ) const {
	float sx, cx, sy, cy, sz, cz;
	float sxcy, cxcy, sxsy, cxsy;

	H3DMath::SinCos( DEG2RAD( yaw ) * 0.5f, sz, cz );
	H3DMath::SinCos( DEG2RAD( pitch ) * 0.5f, sy, cy );
	H3DMath::SinCos( DEG2RAD( roll ) * 0.5f, sx, cx );

	sxcy = sx * cy;
	cxcy = cx * cy;
	sxsy = sx * sy;
	cxsy = cx * sy;

	return H3DQuat( cxsy*sz - sxcy*cz, -cxsy*cz - sxcy*sz, sxsy*cz - cxcy*sz, cxcy*cz + sxsy*sz );
}

/*
=================
H3DAngles::ToRotation
=================
*/
H3DRotation H3DAngles::ToRotation( void ) const {
	H3DVec3 vec;
	float angle, w;
	float sx, cx, sy, cy, sz, cz;
	float sxcy, cxcy, sxsy, cxsy;

	if ( pitch == 0.0f ) {
		if ( yaw == 0.0f ) {
			return H3DRotation( vec3_origin, H3DVec3( -1.0f, 0.0f, 0.0f ), roll );
		}
		if ( roll == 0.0f ) {
			return H3DRotation( vec3_origin, H3DVec3( 0.0f, 0.0f, -1.0f ), yaw );
		}
	} else if ( yaw == 0.0f && roll == 0.0f ) {
		return H3DRotation( vec3_origin, H3DVec3( 0.0f, -1.0f, 0.0f ), pitch );
	}

	H3DMath::SinCos( DEG2RAD( yaw ) * 0.5f, sz, cz );
	H3DMath::SinCos( DEG2RAD( pitch ) * 0.5f, sy, cy );
	H3DMath::SinCos( DEG2RAD( roll ) * 0.5f, sx, cx );

	sxcy = sx * cy;
	cxcy = cx * cy;
	sxsy = sx * sy;
	cxsy = cx * sy;

	vec.x =  cxsy * sz - sxcy * cz;
	vec.y = -cxsy * cz - sxcy * sz;
	vec.z =  sxsy * cz - cxcy * sz;
	w =		 cxcy * cz + sxsy * sz;
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

/*
=================
H3DAngles::ToMat3
=================
*/
H3DMat3 H3DAngles::ToMat3( void ) const {
	H3DMat3 mat;
	float sr, sp, sy, cr, cp, cy;

	H3DMath::SinCos( DEG2RAD( yaw ), sy, cy );
	H3DMath::SinCos( DEG2RAD( pitch ), sp, cp );
	H3DMath::SinCos( DEG2RAD( roll ), sr, cr );

	mat[ 0 ].Set( cp * cy, cp * sy, -sp );
	mat[ 1 ].Set( sr * sp * cy + cr * -sy, sr * sp * sy + cr * cy, sr * cp );
	mat[ 2 ].Set( cr * sp * cy + -sr * -sy, cr * sp * sy + -sr * cy, cr * cp );

	return mat;
}

/*
=================
H3DAngles::ToMat4
=================
*/
H3DMat4 H3DAngles::ToMat4( void ) const {
	return ToMat3().ToMat4();
}

/*
=================
H3DAngles::ToAngularVelocity
=================
*/
H3DVec3 H3DAngles::ToAngularVelocity( void ) const {
	H3DRotation rotation = H3DAngles::ToRotation();
	return rotation.GetVec() * DEG2RAD( rotation.GetAngle() );
}

/*
=============
H3DAngles::ToString
=============
*/
//const char *H3DAngles::ToString( int precision ) const {
//	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
//}
