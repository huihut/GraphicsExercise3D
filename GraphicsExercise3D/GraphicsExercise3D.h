
// GraphicsExercise3D.h : GraphicsExercise3D 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CGraphicsExercise3DApp:
// 有关此类的实现，请参阅 GraphicsExercise3D.cpp
//

class CGraphicsExercise3DApp : public CWinAppEx
{
public:
	CGraphicsExercise3DApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphicsExercise3DApp theApp;
