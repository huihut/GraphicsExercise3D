
// GraphicsExercise3D.h : GraphicsExercise3D Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGraphicsExercise3DApp:
// �йش����ʵ�֣������ GraphicsExercise3D.cpp
//

class CGraphicsExercise3DApp : public CWinAppEx
{
public:
	CGraphicsExercise3DApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphicsExercise3DApp theApp;
