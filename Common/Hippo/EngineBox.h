/********************************************************************
	created:	2011/10/20
	created:	20:10:2011   23:35
	filename: 	f:\TestHippo\TestHippo\EngineBox.h
	file path:	f:\TestHippo\TestHippo
	file base:	EngineBox
	file ext:	h
	author:		sssa2000
	
	purpose:	
*********************************************************************/
#pragma once

#include <Windows.h>

namespace H3DI
{
	class IRender;
	class IActor;
	class IModel;
	class ILevel;
};

typedef H3DI::IRender* (*CreateRenderPtr)();
typedef void (*DeleteRenderPtr)();


class EngineBox
{
public:
	EngineBox();
	~EngineBox();

	int Init(HWND hwnd,unsigned int width,unsigned int height);
	H3DI::IRender* m_pRenderer;

private:

	CreateRenderPtr CreateRendererDX;
	DeleteRenderPtr DeleteRendererDX;

	HMODULE m_dll;



};
