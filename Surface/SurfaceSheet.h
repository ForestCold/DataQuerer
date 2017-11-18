#pragma once



// CSurfaceSheet

#include "TopkPage.h"
#include "IndexPage.h"
#include "SortPage.h"
#include "DeletePage.h"

class CSurfaceSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSurfaceSheet)
private:
	CTopkPage m_topkPage;
	CIndexPage m_indexPage;
	CSortPage m_sortPage;
	CDeletePage m_deletePage;
public:
	CSurfaceSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSurfaceSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSurfaceSheet();

protected:
	DECLARE_MESSAGE_MAP()
};


