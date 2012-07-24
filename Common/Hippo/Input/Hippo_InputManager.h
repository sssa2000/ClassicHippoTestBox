/********************************************************************
	created:	2011/11/23
	created:	23:11:2011   1:04
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\Input\InputManager.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork\Input
	file base:	InputManager
	file ext:	h
	author:		sssa2000
	
	purpose:	input manager的职责是将windows消息转化为逻辑数据，也就是记录一帧中所有的按键、鼠标消息，
				将这些信息以逻辑接口的形式提供给外面。所有需要键盘鼠标信息的类，来inputmanager中查询。

				用户也可以直接使用inputmanager，同样也可以用自定义回调自己处理
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
	//!有的数据需要每帧都重置
	void ResetPerFrame();

	//!消息处理函数，返回0表示对该消息不感兴趣，返回1表示已经处理，不需要默认消息处理函数再处理
	virtual int HandleMsg(HippoContexInfo* pStage,HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam);

	//!是否按下了某个按键
	bool IsKeyDown(int key);

	bool IsMouseRButtonDown(){return m_bMouseRButtonDown;}
	bool IsMouseLButtonDown(){return m_bMouseLButtonDown;}
	bool IsMouseMButtonDown(){return m_bMouseMButtonDown;}
	
	//!获取鼠标左键按下时窗口坐标下的位置
	void GetMouseLKeyDownPos_Wnd(int* outDeltaX,int* outDeltaY);
	
	//!获取鼠标左键按下时屏幕坐标下的位置
	void GetMouseLKeyDownPos_Screen(int* outDeltaX,int* outDeltaY);

	//!获取当前鼠标的位置，窗口坐标系下
	void GetCurrentMousePos_Wnd(int* outDeltaX,int* outDeltaY);

	//!获取鼠标滚轮滚动的距离
	int GetWheelDelta();

	//!得到是否正在左键拖拽
	bool IsLeftKeyDraging();

	//!得到是否正在右键拖拽
	bool IsRightKeyDraging();

	//!得到本帧鼠标左键拖拽移动的距离(屏幕空间)
	int GetMouseLDragDelta(int* outDeltaX,int* outDeltaY);
	
	//!得到本帧鼠标右键拖拽移动的距离(屏幕空间)
	int GetMouseRDragDelta(int* outDeltaX,int* outDeltaY);

	//!得到左键拖拽开始的鼠标位置
	int GetLeftKeyDragingBeginPoint_Wnd(int* outDeltaX,int* outDeltaY);
	int GetLeftKeyDragingBeginPoint_Screen(int* outDeltaX,int* outDeltaY);

protected:
private:


	//!处理键盘的消息。返回0表示没有处理希望用默认消息处理函数处理；返回1表示已经处理，不希望再经过默认的处理
	int ProcessKeyBoardMsg(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	//!处理鼠标的消息。返回0表示没有处理希望用默认消息处理函数处理；返回1表示已经处理，不希望再经过默认的处理
	int ProcessMouseMsg(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	//!返回1表示已经处理，不希望再经过默认的处理
	int OnMouseLeftKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int OnMouseLeftKeyUp(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	int OnMouseRightKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int OnMouseRightKeyUp(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	int OnMouseMiddleKeyDown(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int OnMouseMiddleKeyUp(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	int OnMouseWheel(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	int OnMouseMove(HippoContexInfo* pStage,HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	//!记录一帧中的按键输入,1表示按下状态
	//int m_KeyInputRecord[CAM_MAX_KEYS];
	bool m_Keys[256];
	bool m_MouseButtons[5];
	
	//!记录有多少个键位于按下状态
	int m_cKeysDown;

	//!记录左键是否处于按下状态
	bool m_bMouseLButtonDown;

	//!记录中键是否处于按下状态
	bool m_bMouseMButtonDown;

	//!记录右键是否处于按下状态
	bool m_bMouseRButtonDown;

	//!记录鼠标左键按下时在窗口坐标下的位置
	int m_MousePosX_LeftKeyDown_Wnd;
	int m_MousePosY_LeftKeyDown_Wnd;

	//!记录鼠标左键按下时在屏幕坐标下的位置
	int m_MousePosX_LeftKeyDown_Screen;
	int m_MousePosY_LeftKeyDown_Screen;

	//!记录鼠标指针当前在窗口坐标下的位置
	int m_MousePosX_Wnd;
	int m_MousePosY_Wnd;

	//!记录左键拖拽时上一帧鼠标的位置(整个屏幕上的位置，非窗口坐标系)
	int m_LastLDrag_ScreenPosX;
	int m_LastLDrag_ScreenPosY;

	//!左键拖拽时的起始位置（窗口坐标）
	int m_LDragBeginPointX_Wnd;
	int m_LDragBeginPointY_Wnd;

	//!左键拖拽时的起始位置（屏幕坐标）
	int m_LDragBeginPointX_Screen;
	int m_LDragBeginPointY_Screen;

	//!记录右键拖拽时上一帧鼠标的位置(整个屏幕上的位置，非窗口坐标系)
	int m_LastRDrag_ScreenPosX;
	int m_LastRDrag_ScreenPosY;

	//!记录的鼠标拖拽移动的距离
	int m_MouseLeftDragDeltaX;
	int m_MouseLeftDragDeltaY;
	int m_MouseRightDragDeltaX;
	int m_MouseRightDragDeltaY;

	//!记录本次鼠标滚轮移动的距离
	int m_nMouseWheelDelta;

	//is left key draging
	bool m_bLeftDraging;
	bool m_bRightDraging;


};