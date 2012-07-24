// Copyright (C) 2004 Id Software, Inc.
//

#ifndef __MATH_RANDOM_H__
#define __MATH_RANDOM_H__

/*
===============================================================================

	Random number generator

===============================================================================
*/

class H3DRandom {
public:
						H3DRandom( int seed = 0 );

	void				SetSeed( int seed );
	int					GetSeed( void ) const;

	int					RandomInt( void );			// random integer in the range [0, MAX_RAND]
	int					RandomInt( int max );		// random integer in the range [0, max[
	float				RandomFloat( void );		// random number in the range [0.0f, 1.0f]
	float				CRandomFloat( void );		// random number in the range [-1.0f, 1.0f]

	static const int	MAX_RAND = 0x7fff;

private:
	int					seed;
};

ID_INLINE H3DRandom::H3DRandom( int seed ) {
	this->seed = seed;
}

ID_INLINE void H3DRandom::SetSeed( int seed ) {
	this->seed = seed;
}

ID_INLINE int H3DRandom::GetSeed( void ) const {
	return seed;
}

ID_INLINE int H3DRandom::RandomInt( void ) {
	seed = 69069 * seed + 1;
	return ( seed & H3DRandom::MAX_RAND );
}

ID_INLINE int H3DRandom::RandomInt( int max ) {
	if ( max == 0 ) {
		return 0;			// avoid divide by zero error
	}
	return RandomInt() % max;
}

ID_INLINE float H3DRandom::RandomFloat( void ) {
	return ( RandomInt() / ( float )( H3DRandom::MAX_RAND + 1 ) );
}

ID_INLINE float H3DRandom::CRandomFloat( void ) {
	return ( 2.0f * ( RandomFloat() - 0.5f ) );
}


/*
===============================================================================

	Random number generator

===============================================================================
*/

class idRandom2 {
public:
							idRandom2( unsigned long seed = 0 );

	void					SetSeed( unsigned long seed );
	unsigned long			GetSeed( void ) const;

	int						RandomInt( void );			// random integer in the range [0, MAX_RAND]
	int						RandomInt( int max );		// random integer in the range [0, max]
	float					RandomFloat( void );		// random number in the range [0.0f, 1.0f]
	float					CRandomFloat( void );		// random number in the range [-1.0f, 1.0f]

	static const int		MAX_RAND = 0x7fff;

private:
	unsigned long			seed;

	static const unsigned long	IEEE_ONE = 0x3f800000;
	static const unsigned long	IEEE_MASK = 0x007fffff;
};

ID_INLINE idRandom2::idRandom2( unsigned long seed ) {
	this->seed = seed;
}

ID_INLINE void idRandom2::SetSeed( unsigned long seed ) {
	this->seed = seed;
}

ID_INLINE unsigned long idRandom2::GetSeed( void ) const {
	return seed;
}

ID_INLINE int idRandom2::RandomInt( void ) {
	seed = 1664525L * seed + 1013904223L;
	return ( (int) seed & idRandom2::MAX_RAND );
}

ID_INLINE int idRandom2::RandomInt( int max ) {
	if ( max == 0 ) {
		return 0;		// avoid divide by zero error
	}
	return ( RandomInt() >> ( 16 - H3DMath::BitsForInteger( max ) ) ) % max;
}

ID_INLINE float idRandom2::RandomFloat( void ) {
	unsigned long i;
	seed = 1664525L * seed + 1013904223L;
	i = idRandom2::IEEE_ONE | ( seed & idRandom2::IEEE_MASK );
	return ( ( *(float *)&i ) - 1.0f );
}

ID_INLINE float idRandom2::CRandomFloat( void ) {
	unsigned long i;
	seed = 1664525L * seed + 1013904223L;
	i = idRandom2::IEEE_ONE | ( seed & idRandom2::IEEE_MASK );
	return ( 2.0f * ( *(float *)&i ) - 3.0f );
}

#endif /* !__MATH_RANDOM_H__ */
