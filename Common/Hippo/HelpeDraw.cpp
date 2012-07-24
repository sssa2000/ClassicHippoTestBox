#include "HelpeDraw.h"
#include "idMath/dMathHeader.h"
#include "engine_interface.h"


void HelpeDraw::DrawHelpGird(H3DI::IRender* pRenderer)
{
	H3DVec3 b(0,0,0),x(100,0,0),y(0,100,0),z(0,0,100);
	float c[4] = {1,0,0,0};
	c[0] = 1;c[1] = c[2] = 1;

	for (float  i=-5.f;i<5.f;i+=0.5f)
	{
		b[0] = i;b[1] = -5;b[2] = 0;
		x[0] = i;x[1] = 5;x[2] = 0;
		y[0] = -5;y[1] = i;y[2] = 0;
		z[0]=  5;z[1] = i;z[2] = 0;
		pRenderer->DrawSegment(b, x, c, 1);
		pRenderer->DrawSegment(y, z, c, 1);
	}

	c[0] = 1;c[1] =c[2] = 0;
	b[0] = b[1] = b[2] = 0;
	x[0] = 100;x[1] = x[2] = 0;
	y[0] = 0;y[1] = 100;y[2] = 0;
	z[0] = 0;z[1] = 0;z[2] = 100;
	pRenderer->DrawSegment(b, x, c, 5);
	c[0]=0;c[1]=1;
	pRenderer->DrawSegment(b, y, c, 5);
	c[2]=1;c[1]=0;
	pRenderer->DrawSegment(b, z, c, 5);
}