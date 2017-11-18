// SurfaceSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "MySurface.h"
#include "SurfaceSheet.h"


// CSurfaceSheet

IMPLEMENT_DYNAMIC(CSurfaceSheet, CPropertySheet)

CSurfaceSheet::CSurfaceSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_topkPage);
	AddPage(&m_indexPage);
	AddPage(&m_sortPage);
	AddPage(&m_deletePage);
}

CSurfaceSheet::CSurfaceSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_topkPage);
	AddPage(&m_indexPage);
	AddPage(&m_sortPage);
	AddPage(&m_deletePage);
}

CSurfaceSheet::~CSurfaceSheet()
{
}


BEGIN_MESSAGE_MAP(CSurfaceSheet, CPropertySheet)
END_MESSAGE_MAP()


// CSurfaceSheet 消息处理程序
