// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_PLANE_H__
#define __MATH_PLANE_H__

/*
===============================================================================

	3D plane with equation: a * x + b * y + c * z + d = 0

===============================================================================
*/


class H3DVec3;
class H3DMat3;

#define	ON_EPSILON					0.1f
#define DEGENERATE_DIST_EPSILON		1e-4f

#define	SIDE_FRONT					0
#define	SIDE_BACK					1
#define	SIDE_ON						2
#define	SIDE_CROSS					3

// plane sides
#define PLANESIDE_FRONT				0
#define PLANESIDE_BACK				1
#define PLANESIDE_ON				2
#define PLANESIDE_CROSS				3

// plane types
#define PLANETYPE_X					0
#define PLANETYPE_Y					1
#define PLANETYPE_Z					2
#define PLANETYPE_NEGX				3
#define PLANETYPE_NEGY				4
#define PLANETYPE_NEGZ				5
#define PLANETYPE_TRUEAXIAL			6	// all types < 6 are true axial planes
#define PLANETYPE_ZEROX				6
#define PLANETYPE_ZEROY				7
#define PLANETYPE_ZEROZ				8
#define PLANETYPE_NONAXIAL			9

class H3DPlane {
public:
					H3DPlane( void );
					H3DPlane( float a, float b, float c, float d );
					H3DPlane( const H3DVec3 &normal, const float dist );

	float			operator[]( int index ) const;
	float &			operator[]( int index );
	H3DPlane			operator-() const;						// flips plane
	H3DPlane &		operator=( const H3DVec3 &v );			// sets normal and sets H3DPlane::d to zero
	H3DPlane			operator+( const H3DPlane &p ) const;	// add plane equations
	H3DPlane			operator-( const H3DPlane &p ) const;	// subtract plane equations
	H3DPlane &		operator*=( const H3DMat3 &m );			// Normal() *= m

	bool			Compare( const H3DPlane &p ) const;						// exact compare, no epsilon
	bool			Compare( const H3DPlane &p, const float epsilon ) const;	// compare with epsilon
	bool			Compare( const H3DPlane &p, const float normalEps, const float distEps ) const;	// compare with epsilon
	bool			operator==(	const H3DPlane &p ) const;					// exact compare, no epsilon
	bool			operator!=(	const H3DPlane &p ) const;					// exact compare, no epsilon

	void			Zero( void );							// zero plane
	void			SetNormal( const H3DVec3 &normal );		// sets the normal
	const H3DVec3 &	Normal( void ) const;					// reference to const normal
	H3DVec3 &		Normal( void );							// reference to normal
	float			Normalize( bool fixDegenerate = true );	// only normalizes the plane normal, does not adjust d
	bool			FixDegenerateNormal( void );			// fix degenerate normal
	bool			FixDegeneracies( float distEpsilon );	// fix degenerate normal and dist
	float			Dist( void ) const;						// returns: -d
	void			SetDist( const float dist );			// sets: d = -dist
	int				Type( void ) const;						// returns plane type

	bool			FromPoints( const H3DVec3 &p1, const H3DVec3 &p2, const H3DVec3 &p3, bool fixDegenerate = true );
	bool			FromVecs( const H3DVec3 &dir1, const H3DVec3 &dir2, const H3DVec3 &p, bool fixDegenerate = true );
	void			FitThroughPoint( const H3DVec3 &p );	// assumes normal is valid
	bool			HeightFit( const H3DVec3 *points, const int numPoints );
	H3DPlane			Translate( const H3DVec3 &translation ) const;
	H3DPlane &		TranslateSelf( const H3DVec3 &translation );
	H3DPlane			Rotate( const H3DVec3 &origin, const H3DMat3 &axis ) const;
	H3DPlane &		RotateSelf( const H3DVec3 &origin, const H3DMat3 &axis );

	float			Distance( const H3DVec3 &v ) const;
	int				Side( const H3DVec3 &v, const float epsilon = 0.0f ) const;

	bool			LineIntersection( const H3DVec3 &start, const H3DVec3 &end ) const;
					// intersection point is start + dir * scale
	bool			RayIntersection( const H3DVec3 &start, const H3DVec3 &dir, float &scale ) const;
	bool			PlaneIntersection( const H3DPlane &plane, H3DVec3 &start, H3DVec3 &dir ) const;

	int				GetDimension( void ) const;

	const H3DVec4 &	ToVec4( void ) const;
	H3DVec4 &		ToVec4( void );
	const float *	ToFloatPtr( void ) const;
	float *			ToFloatPtr( void );
	const char *	ToString( int precision = 2 ) const;

private:
	float			a;
	float			b;
	float			c;
	float			d;
};

extern H3DPlane plane_origin;
#define plane_zero plane_origin

ID_INLINE H3DPlane::H3DPlane( void ) {
}

ID_INLINE H3DPlane::H3DPlane( float a, float b, float c, float d ) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

ID_INLINE H3DPlane::H3DPlane( const H3DVec3 &normal, const float dist ) {
	this->a = normal.x;
	this->b = normal.y;
	this->c = normal.z;
	this->d = -dist;
}

ID_INLINE float H3DPlane::operator[]( int index ) const {
	return ( &a )[ index ];
}

ID_INLINE float& H3DPlane::operator[]( int index ) {
	return ( &a )[ index ];
}

ID_INLINE H3DPlane H3DPlane::operator-() const {
	return H3DPlane( -a, -b, -c, -d );
}

ID_INLINE H3DPlane &H3DPlane::operator=( const H3DVec3 &v ) { 
	a = v.x;
	b = v.y;
	c = v.z;
	d = 0;
	return *this;
}

ID_INLINE H3DPlane H3DPlane::operator+( const H3DPlane &p ) const {
	return H3DPlane( a + p.a, b + p.b, c + p.c, d + p.d );
}

ID_INLINE H3DPlane H3DPlane::operator-( const H3DPlane &p ) const {
	return H3DPlane( a - p.a, b - p.b, c - p.c, d - p.d );
}

ID_INLINE H3DPlane &H3DPlane::operator*=( const H3DMat3 &m ) {
	Normal() *= m;
	return *this;
}

ID_INLINE bool H3DPlane::Compare( const H3DPlane &p ) const {
	return ( a == p.a && b == p.b && c == p.c && d == p.d );
}

ID_INLINE bool H3DPlane::Compare( const H3DPlane &p, const float epsilon ) const {
	if ( H3DMath::Fabs( a - p.a ) > epsilon ) {
		return false;
	}
			
	if ( H3DMath::Fabs( b - p.b ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( c - p.c ) > epsilon ) {
		return false;
	}

	if ( H3DMath::Fabs( d - p.d ) > epsilon ) {
		return false;
	}

	return true;
}

ID_INLINE bool H3DPlane::Compare( const H3DPlane &p, const float normalEps, const float distEps ) const {
	if ( H3DMath::Fabs( d - p.d ) > distEps ) {
		return false;
	}
	if ( !Normal().Compare( p.Normal(), normalEps ) ) {
		return false;
	}
	return true;
}

ID_INLINE bool H3DPlane::operator==( const H3DPlane &p ) const {
	return Compare( p );
}

ID_INLINE bool H3DPlane::operator!=( const H3DPlane &p ) const {
	return !Compare( p );
}

ID_INLINE void H3DPlane::Zero( void ) {
	a = b = c = d = 0.0f;
}

ID_INLINE void H3DPlane::SetNormal( const H3DVec3 &normal ) {
	a = normal.x;
	b = normal.y;
	c = normal.z;
}

ID_INLINE const H3DVec3 &H3DPlane::Normal( void ) const {
	return *reinterpret_cast<const H3DVec3 *>(&a);
}

ID_INLINE H3DVec3 &H3DPlane::Normal( void ) {
	return *reinterpret_cast<H3DVec3 *>(&a);
}

ID_INLINE float H3DPlane::Normalize( bool fixDegenerate ) {
	float length = reinterpret_cast<H3DVec3 *>(&a)->Normalize();

	if ( fixDegenerate ) {
		FixDegenerateNormal();
	}
	return length;
}

ID_INLINE bool H3DPlane::FixDegenerateNormal( void ) {
	return Normal().FixDegenerateNormal();
}

ID_INLINE bool H3DPlane::FixDegeneracies( float distEpsilon ) {
	bool fixedNormal = FixDegenerateNormal();
	// only fix dist if the normal was degenerate
	if ( fixedNormal ) {
		if ( H3DMath::Fabs( d - H3DMath::Rint( d ) ) < distEpsilon ) {
			d = H3DMath::Rint( d );
		}
	}
	return fixedNormal;
}

ID_INLINE float H3DPlane::Dist( void ) const {
	return -d;
}

ID_INLINE void H3DPlane::SetDist( const float dist ) {
	d = -dist;
}

ID_INLINE bool H3DPlane::FromPoints( const H3DVec3 &p1, const H3DVec3 &p2, const H3DVec3 &p3, bool fixDegenerate ) {
	Normal() = (p1 - p2).Cross( p3 - p2 );
	if ( Normalize( fixDegenerate ) == 0.0f ) {
		return false;
	}
	//d = -( Normal() * p2 );
	d = -( Normal().Dot(p2) );
	return true;
}

ID_INLINE bool H3DPlane::FromVecs( const H3DVec3 &dir1, const H3DVec3 &dir2, const H3DVec3 &p, bool fixDegenerate ) {
	Normal() = dir1.Cross( dir2 );
	if ( Normalize( fixDegenerate ) == 0.0f ) {
		return false;
	}
	//d = -( Normal() * p );
	d = -( Normal().Dot(p) );
	return true;
}

ID_INLINE void H3DPlane::FitThroughPoint( const H3DVec3 &p ) {
	//d = -( Normal() * p );
	d = -( Normal().Dot(p) );
}

ID_INLINE H3DPlane H3DPlane::Translate( const H3DVec3 &translation ) const {
	//return H3DPlane( a, b, c, d - translation * Normal() );
	return H3DPlane( a, b, c, d - translation.Dot(Normal()));
}

ID_INLINE H3DPlane &H3DPlane::TranslateSelf( const H3DVec3 &translation ) {
	//d -= translation * Normal();
	d -= translation.Dot(Normal());
	return *this;
}

ID_INLINE H3DPlane H3DPlane::Rotate( const H3DVec3 &origin, const H3DMat3 &axis ) const {
	H3DPlane p;
	p.Normal() = Normal() * axis;
	//p.d = d + origin * Normal() - origin * p.Normal();
	p.d = d + origin.Dot(Normal()) - origin.Dot(p.Normal());
	return p;
}

ID_INLINE H3DPlane &H3DPlane::RotateSelf( const H3DVec3 &origin, const H3DMat3 &axis ) {
	//d += origin * Normal();
	d += origin.Dot(Normal());
	Normal() *= axis;
	//d -= origin * Normal();
	d -= origin.Dot(Normal());
	return *this;
}

ID_INLINE float H3DPlane::Distance( const H3DVec3 &v ) const {
	return a * v.x + b * v.y + c * v.z + d;
}

ID_INLINE int H3DPlane::Side( const H3DVec3 &v, const float epsilon ) const {
	float dist = Distance( v );
	if ( dist > epsilon ) {
		return PLANESIDE_FRONT;
	}
	else if ( dist < -epsilon ) {
		return PLANESIDE_BACK;
	}
	else {
		return PLANESIDE_ON;
	}
}

ID_INLINE bool H3DPlane::LineIntersection( const H3DVec3 &start, const H3DVec3 &end ) const {
	float d1, d2, fraction;

	//d1 = Normal() * start + d;
	//d2 = Normal() * end + d;
	d1 = Normal().Dot(start) + d;
	d2 = Normal().Dot(end) + d;
	if ( d1 == d2 ) {
		return false;
	}
	if ( d1 > 0.0f && d2 > 0.0f ) {
		return false;
	}
	if ( d1 < 0.0f && d2 < 0.0f ) {
		return false;
	}
	fraction = ( d1 / ( d1 - d2 ) );
	return ( fraction >= 0.0f && fraction <= 1.0f );
}

ID_INLINE bool H3DPlane::RayIntersection( const H3DVec3 &start, const H3DVec3 &dir, float &scale ) const {
	float d1, d2;

	//d1 = Normal() * start + d;
	//d2 = Normal() * dir;
	d1 = Normal().Dot(start) + d;
	d2 = Normal().Dot(dir);
	if ( d2 == 0.0f ) {
		return false;
	}
	scale = -( d1 / d2 );
	return true;
}

ID_INLINE int H3DPlane::GetDimension( void ) const {
	return 4;
}

ID_INLINE const H3DVec4 &H3DPlane::ToVec4( void ) const {
	return *reinterpret_cast<const H3DVec4 *>(&a);
}

ID_INLINE H3DVec4 &H3DPlane::ToVec4( void ) {
	return *reinterpret_cast<H3DVec4 *>(&a);
}

ID_INLINE const float *H3DPlane::ToFloatPtr( void ) const {
	return reinterpret_cast<const float *>(&a);
}

ID_INLINE float *H3DPlane::ToFloatPtr( void ) {
	return reinterpret_cast<float *>(&a);
}

#endif /* !__MATH_PLANE_H__ */
