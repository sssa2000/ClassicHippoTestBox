// Copyright (C) 2004 Id Software, Inc.
//

#include "../dmathheader.h"
#pragma hdrstop
#pragma warning( push )

#pragma warning(disable : 4100)				// unreferenced formal parameter
#pragma warning(disable : 4244)				// conversion to smaller type, possible loss of data
#pragma warning(disable : 4714)				// function marked as __forceinline not inlined
#pragma warning(disable : 4311)				//  pointer truncation from 'void *' to 'int'
#pragma warning(disable : 4312)				// conversion from 'int' to 'void *' of greater size
#pragma warning(disable : 4267)				// conversion from 'size_t' to 'int', possible loss of data
H3DPlane plane_origin( 0.0f, 0.0f, 0.0f, 0.0f );

/*
================
H3DPlane::Type
================
*/
int H3DPlane::Type( void ) const {
	if ( Normal()[0] == 0.0f ) {
		if ( Normal()[1] == 0.0f ) {
			return Normal()[2] > 0.0f ? PLANETYPE_Z : PLANETYPE_NEGZ;
		}
		else if ( Normal()[2] == 0.0f ) {
			return Normal()[1] > 0.0f ? PLANETYPE_Y : PLANETYPE_NEGY;
		}
		else {
			return PLANETYPE_ZEROX;
		}
	}
	else if ( Normal()[1] == 0.0f ) {
		if ( Normal()[2] == 0.0f ) {
			return Normal()[0] > 0.0f ? PLANETYPE_X : PLANETYPE_NEGX;
		}
		else {
			return PLANETYPE_ZEROY;
		}
	}
	else if ( Normal()[2] == 0.0f ) {
		return PLANETYPE_ZEROZ;
	}
	else {
		return PLANETYPE_NONAXIAL;
	}
}

/*
================
H3DPlane::HeightFit
================
*/
bool H3DPlane::HeightFit( const H3DVec3 *points, const int numPoints ) {
	int i;
	float sumXX = 0.0f, sumXY = 0.0f, sumXZ = 0.0f;
	float sumYY = 0.0f, sumYZ = 0.0f;
	H3DVec3 sum, average, dir;

	if ( numPoints == 1 ) {
		a = 0.0f;
		b = 0.0f;
		c = 1.0f;
		d = -points[0].z;
		return true;
	}
	if ( numPoints == 2 ) {
		dir = points[1] - points[0];
		Normal() = dir.Cross( H3DVec3( 0, 0, 1 ) ).Cross( dir );
		Normalize();
		d = -( Normal().Dot(points[0]) );
		return true;
	}

	sum.Zero();
	for ( i = 0; i < numPoints; i++) {
		sum += points[i];
	}
	average = sum / numPoints;

	for ( i = 0; i < numPoints; i++ ) {
		dir = points[i] - average;
		sumXX += dir.x * dir.x;
		sumXY += dir.x * dir.y;
		sumXZ += dir.x * dir.z;
		sumYY += dir.y * dir.y;
		sumYZ += dir.y * dir.z;
	}

	H3DMat2 m( sumXX, sumXY, sumXY, sumYY );
	if ( !m.InverseSelf() ) {
		return false;
	}

	a = - sumXZ * m[0][0] - sumYZ * m[0][1];
	b = - sumXZ * m[1][0] - sumYZ * m[1][1];
	c = 1.0f;
	Normalize();
	d = -( a * average.x + b * average.y + c * average.z );
	return true;
}

/*
================
H3DPlane::PlaneIntersection
================
*/
bool H3DPlane::PlaneIntersection( const H3DPlane &plane, H3DVec3 &start, H3DVec3 &dir ) const {
	double n00, n01, n11, det, invDet, f0, f1;

	n00 = Normal().LengthSqr();
	n01 = Normal().Dot(plane.Normal());
	n11 = plane.Normal().LengthSqr();
	det = n00 * n11 - n01 * n01;

	if ( H3DMath::Fabs(det) < 1e-6f ) {
		return false;
	}

	invDet = 1.0f / det;
	f0 = ( n01 * plane.d - n11 * d ) * invDet;
	f1 = ( n01 * d - n00 * plane.d ) * invDet;

	dir = Normal().Cross( plane.Normal() );
	start = f0 * Normal() + f1 * plane.Normal();
	return true;
}

/*
=============
H3DPlane::ToString
=============
*/
const char *H3DPlane::ToString( int precision ) const {
	return H3DStr::FloatArrayToString( ToFloatPtr(), GetDimension(), precision );
}
#pragma warning (pop)
