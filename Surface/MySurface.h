
// MySurface.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMySurfaceApp:
// �йش����ʵ�֣������ MySurface.cpp
//

class CMySurfaceApp : public CWinApp
{
public:
	CMySurfaceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMySurfaceApp theApp;