#ifndef _IDLIB
#define _IDLIB
//#define ID_INLINE inline
#include "cpuid.h"

#ifdef __GNUC__
#define id_attribute(x) __attribute__(x)
#else
#define id_attribute(x)  
#endif



#ifdef _DEBUG
void AssertFailed( const char *file, int line, const char *expression );
#undef assert
#define assert( X )		if ( X ) { } else AssertFailed( __FILE__, __LINE__, #X )
#endif

//inline void assert(bool init)
//{
//	__asm
//	{
//		int 3;
//	}
//};
/*
===============================================================================

	Types and defines used throughout the engine.

===============================================================================
*/

typedef unsigned char			byte;		// 8 bits
typedef unsigned short			word;		// 16 bits
typedef unsigned int			dword;		// 32 bits
typedef unsigned int			uint32;
typedef unsigned long			ulong;

typedef int						qhandle_t;



#ifndef NULL
#define NULL					0
#endif

#ifndef BIT
#define BIT( num )				( 1 << ( num ) )
#endif

#define	MAX_STRING_CHARS		1024		// max length of a string

// maximum world size
#define MAX_WORLD_COORD			( 128 * 1024 )
#define MIN_WORLD_COORD			( -128 * 1024 )
#define MAX_WORLD_SIZE			( MAX_WORLD_COORD - MIN_WORLD_COORD )

enum cpuid_t
{
	CPUID_NONE							= 0x00000,
	CPUID_UNSUPPORTED					= 0x00001,	// unsupported (386/486)
	CPUID_GENERIC						= 0x00002,	// unrecognized processor
	CPUID_INTEL							= 0x00004,	// Intel
	CPUID_AMD							= 0x00008,	// AMD
	CPUID_MMX							= 0x00010,	// Multi Media Extensions
	CPUID_3DNOW							= 0x00020,	// 3DNow!
	CPUID_SSE							= 0x00040,	// Streaming SIMD Extensions
	CPUID_SSE2							= 0x00080,	// Streaming SIMD Extensions 2
	CPUID_SSE3							= 0x00100,	// Streaming SIMD Extentions 3 aka Prescott's New Instructions
	CPUID_ALTIVEC						= 0x00200,	// AltiVec
	CPUID_HTT							= 0x01000,	// Hyper-Threading Technology
	CPUID_CMOV							= 0x02000,	// Conditional Move (CMOV) and fast floating point comparison (FCOMI) instructions
	CPUID_FTZ							= 0x04000,	// Flush-To-Zero mode (denormal results are flushed to zero)
	CPUID_DAZ							= 0x08000	// Denormals-Are-Zero mode (denormal source operands are set to zero)
};

inline int get_doom_cpuid(int feature)//from MSDN's cpuid
{


	int id =CPUID_NONE;
	if (feature==0)
		return CPUID_NONE;

	if (feature&_CPU_FEATURE_MMX)
		id = CPUID_MMX;
	if (feature&_CPU_FEATURE_SSE)
		id|= CPUID_SSE;
	if (feature&_CPU_FEATURE_SSE2)
		id|=CPUID_SSE2;
	if (feature&_CPU_FEATURE_SSE3)
		id|=CPUID_SSE3;
	if (feature&_CPU_FEATURE_3DNOW)
		id|=CPUID_3DNOW;
//	if (checks&_CPU_FEATURE_MMX)
//		id|=CPUID_MMX;
//	if (checks&_CPU_FEATURE_MMX)
//		id|=CPUID_MMX;
	return id;
};



#endif
