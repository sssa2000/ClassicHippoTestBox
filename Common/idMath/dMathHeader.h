#ifndef _DOOM_MATH_HEADER
#define _DOOM_MATH_HEADER


#include <assert.h>
#include <malloc.h>
#pragma warning( push )

#pragma warning(disable : 4100)				// unreferenced formal parameter
#pragma warning(disable : 4244)				// conversion to smaller type, possible loss of data
#pragma warning(disable : 4714)				// function marked as __forceinline not inlined
#pragma warning(disable : 4311)				//  pointer truncation from 'void *' to 'int'
#pragma warning(disable : 4312)				// conversion from 'int' to 'void *' of greater size
#pragma warning(disable : 4267)				// conversion from 'size_t' to 'int', possible loss of data


// Win32
#if defined(WIN32) || defined(_WIN32)

#define	BUILD_STRING					"win-x86"
#define BUILD_OS_ID						0
#define	CPUSTRING						"x86"
#define CPU_EASYARGS					1

#define ALIGN16( x )					__declspec(align(16)) x
#define PACKED

#define _alloca16( x )					((void *)((((int)_alloca( (x)+15 )) + 15) & ~15))

#define PATHSEPERATOR_STR				"\\"
#define PATHSEPERATOR_CHAR				'\\'

#define ID_INLINE						__forceinline
#define ID_STATIC_TEMPLATE				static

#define assertmem( x, y )				assert( _CrtIsValidPointer( x, y, true ) )

typedef int glIndex_t;
typedef struct dominantTri_s {
	glIndex_t					v2, v3;
	float						normalizationScale[3];
} dominantTri_t;


template< class type >
ID_INLINE void idSwap( type &a, type &b ) {
	type c = a;
	a = b;
	b = c;
}

#include "heap.h"
#include "math/math.h"
#include "math/vector.H"
#include "math/angles.h"
#include <float.h>
#include "math/quat.h"
#include "math/matrix.h"
#include "math/rotation.h"
#include "str.h"
#include "math/plane.h"

#pragma warning( pop )

#endif//WIN32



#endif