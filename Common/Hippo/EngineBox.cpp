#include "EngineBox.h"
#include "ErrReport.h"
#include "engine_interface.h"
#include <string>

EngineBox::EngineBox():
m_dll(0),
m_pRenderer(0),
CreateRendererDX(0),
DeleteRendererDX(0)
{

}

EngineBox::~EngineBox()
{


	if(DeleteRendererDX)
		DeleteRendererDX();	

	if(m_dll)
	{
		FreeModule(m_dll);
	}
}

int EngineBox::Init(HWND hwnd,unsigned int width,unsigned int height)
{
#ifdef _DEBUG
	std::string dllname="Engine_d.dll";
#else
	std::string dllname="Engine.dll";
#endif
	m_dll = LoadLibraryA(dllname.c_str());
	if (!m_dll)
	{
		DWORD err=GetLastError();
		ReportErrWithLastErr(err,"Load Library Failed!:s",dllname.c_str());
		return -1;
	}

	CreateRendererDX = (CreateRenderPtr)GetProcAddress(m_dll,"CreateRenderer");
	DeleteRendererDX = (DeleteRenderPtr)GetProcAddress(m_dll,"DeleteRenderer");
	if (!CreateRendererDX || !DeleteRendererDX)
	{
		DWORD err=GetLastError();
		ReportErrWithLastErr(err,"GetProcAddress!:%s",dllname.c_str());
		return -1;
	}

	m_pRenderer = CreateRendererDX();
	if (!m_pRenderer)
	{
		ReportErr("Create IRender 失败");
		return -1;
	} 


	const char* sInfo = m_pRenderer->GetCoreVersionInfo();
	H3DI::tWindowCreateInfoImp info;
	m_pRenderer->GetCurrentWindowSetting(info);
	info.hWnd =hwnd;
	info.nWidth = width;
	info.nHeight = height;



	int res = m_pRenderer->CreateRenderWindow(info);
	if (res<0)
	{
		ReportErr("无法创建渲染窗口！");
		return -1;
	}

	m_pRenderer->SetUseActionLib(true);
	m_pRenderer->SetUseActionChannel(true);
	m_pRenderer->SetMergBodyPart(true);
	m_pRenderer->SetImageScaleFactor(0);
	m_pRenderer->SetUseTriList(true);


	float col[4]={0.5f,0.5f,0.5f,1.0};
	m_pRenderer->SetClearColor(col);

	return 1;
	//m_pRenderer->StartEngineThread(0);

}
