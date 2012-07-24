#include "idlib.h"

/*
===============================================================================

	Assertion

===============================================================================
*/
#include <stdio.h>
void AssertFailed( const char *file, int line, const char *expression )
{
	printf( "\n\nASSERTION FAILED!\n%s(%d): '%s'\n", file, line, expression );

	__asm int 0x03

}
