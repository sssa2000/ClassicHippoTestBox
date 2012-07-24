/********************************************************************
	created:	2011/11/23
	created:	23:11:2011   1:04
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\Input\InputManager.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\Input
	file base:	InputManager
	file ext:	h
	author:		sssa2000
	
	purpose:	input manager��ְ���ǽ�windows��Ϣת��Ϊ�߼����ݣ�Ҳ���Ǽ�¼һ֡�����еİ����������Ϣ��
				����Щ��Ϣ���߼��ӿڵ���ʽ�ṩ�����档������Ҫ���������Ϣ���࣬��inputmanager�в�ѯ��

				�û�Ҳ����ֱ��ʹ��inputmanager��ͬ��Ҳ�������Զ���ص��Լ�����
*********************************************************************/
#pragma once
#include <windows.h>
#include <vector>

class CameraBase;
class HippoContexInfo;

class Hippo_InputManager
{
public:
	Hippo_InputManager();
	~Hippo_InputManager();

	void Init();
	//!�е�������Ҫÿ֡������
	void ResetPerFrame();

	//!��Ϣ������������0��ʾ�Ը���Ϣ������Ȥ������1��ʾ�Ѿ���������ҪĬ����Ϣ�������ٴ���
	virtual int HandleMsg(HippoContexInfo* pStage,HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam);

	//!�Ƿ�����ĳ������
	bool IsKeyDown(int key);

	bool IsMouseRButtonDown(){return m_bMouseRButtonDown;}
	bool IsMouseLButtonDown(){return m_bMouseLButtonDown;}
	bool IsMouseMButtonDown(){return m_bMouseMButtonDown;}
	
	//!��ȡ����������ʱ���������µ�λ��
	void GetMouseLKeyDownPos_Wnd(int* outDeltaX,int* outDeltaY);
	
	//!��ȡ����������ʱ��Ļ�����µ�λ��
	void GetMouseLKeyDownPos_Screen(int* outDeltaX,int* outDeltaY);

	//!��ȡ��ǰ����λ�ã���������ϵ��
	void GetCurrentMousePos_Wnd(int* outDeltaX,int* outDeltaY);

	//!��ȡ�����ֹ����ľ���
	int GetWheelDelta();

	//!�õ��Ƿ����������ק
	bool IsLeftKeyDraging();

	//!�õ��Ƿ������Ҽ���ק
	bool IsRightKeyDraging();

	//!�õ���֡��������ק�ƶ��ľ���(��Ļ�ռ�)
	int GetMouseLDragDelta(int* outDeltaX,int* outDeltaY);
	
	//!�õ���֡����Ҽ���ק�ƶ��ľ���(��Ļ�ռ�)
	int GetMouseRDragDelta(int* outDeltaX,int* outDeltaY);

	//!�õ������ק��ʼ�����λ��
	int GetLeftKeyDragingBeginPoint_Wnd(int* outDeltaX,int* outDeltaY);
	int GetLeftKeyDragingBeginPoint_Screen(int* outDeltaX,int* outDeltaY);

protected:
private:


	//!������̵���Ϣ������0��ʾû�д���ϣ����Ĭ����Ϣ��������������1��ʾ�Ѿ�������ϣ���پ���Ĭ�ϵĴ���
	int ProcessKeyBoardMsg(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	//!����������Ϣ������0��ʾû�д���ϣ����Ĭ����Ϣ��������������1��ʾ�Ѿ�������ϣ���پ���Ĭ�ϵĴ���
	int ProcessMouseMsg(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	//!����1��ʾ�Ѿ�������ϣ���پ���Ĭ�ϵĴ���
	int OnMouseLeftKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int OnMouseLeftKeyUp(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	int OnMouseRightKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int OnMouseRightKeyUp(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	int OnMouseMiddleKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int OnMouseMiddleKeyUp(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	int OnMouseWheel(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int OnMouseMove(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	//!��¼һ֡�еİ�������,1��ʾ����״̬
	//int m_KeyInputRecord[CAM_MAX_KEYS];
	bool m_Keys[256];
	bool m_MouseButtons[5];
	
	//!��¼�ж��ٸ���λ�ڰ���״̬
	int m_cKeysDown;

	//!��¼����Ƿ��ڰ���״̬
	bool m_bMouseLButtonDown;

	//!��¼�м��Ƿ��ڰ���״̬
	bool m_bMouseMButtonDown;

	//!��¼�Ҽ��Ƿ��ڰ���״̬
	bool m_bMouseRButtonDown;

	//!��¼����������ʱ�ڴ��������µ�λ��
	int m_MousePosX_LeftKeyDown_Wnd;
	int m_MousePosY_LeftKeyDown_Wnd;

	//!��¼����������ʱ����Ļ�����µ�λ��
	int m_MousePosX_LeftKeyDown_Screen;
	int m_MousePosY_LeftKeyDown_Screen;

	//!��¼���ָ�뵱ǰ�ڴ��������µ�λ��
	int m_MousePosX_Wnd;
	int m_MousePosY_Wnd;

	//!��¼�����קʱ��һ֡����λ��(������Ļ�ϵ�λ�ã��Ǵ�������ϵ)
	int m_LastLDrag_ScreenPosX;
	int m_LastLDrag_ScreenPosY;

	//!�����קʱ����ʼλ�ã��������꣩
	int m_LDragBeginPointX_Wnd;
	int m_LDragBeginPointY_Wnd;

	//!�����קʱ����ʼλ�ã���Ļ���꣩
	int m_LDragBeginPointX_Screen;
	int m_LDragBeginPointY_Screen;

	//!��¼�Ҽ���קʱ��һ֡����λ��(������Ļ�ϵ�λ�ã��Ǵ�������ϵ)
	int m_LastRDrag_ScreenPosX;
	int m_LastRDrag_ScreenPosY;

	//!��¼�������ק�ƶ��ľ���
	int m_MouseLeftDragDeltaX;
	int m_MouseLeftDragDeltaY;
	int m_MouseRightDragDeltaX;
	int m_MouseRightDragDeltaY;

	//!��¼�����������ƶ��ľ���
	int m_nMouseWheelDelta;

	//is left key draging
	bool m_bLeftDraging;
	bool m_bRightDraging;


};