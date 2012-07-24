// Copyright (C) 2004 Id Software, Inc.
//
#include "../dmathheader.h"
#include "DrawVert.h"
#pragma hdrstop


/*
=============
H3DDrawVert::Normalize
=============
*/
void H3DDrawVert::Normalize( void ) {
	normal.Normalize();
	tangents[1].Cross( normal, tangents[0] );
	tangents[1].Normalize();
	tangents[0].Cross( tangents[1], normal );
	tangents[0].Normalize();
}
