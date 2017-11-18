#pragma once
#include "afxwin.h"
#include "afxwin.h"
#include <string>
#include <sstream>
#include "MyIndex.h"
#include "bptree.h"
using namespace std;

// CIndexPage 对话框

class CIndexPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CIndexPage)

public:
	CIndexPage();
	virtual ~CIndexPage();

// 对话框数据
	enum { IDD = IDD_INDEX_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearchButton();
	afx_msg void OnBnClickedIndexButton();
	CEdit m_editResultShow;
	
	CString m_editFilename;
	CString m_editKeyword;
	CButton m_checkPrice;
	CButton m_checkArea;
	CButton m_checkAddress;
	CButton m_checkEstate;
	CButton m_checkYear;
	
	int FileIndex;
	int WordIndex;
	CString m_editResult;
	CString IMCString;
	std::string filePath[30];
	std::string RawFilename;
	std::string RawKeyword;
	std::string Keyword;
	std::string KeywordList[6];
	std::string Myresult;
	bool IndexType[6];
	afx_msg void OnBnClickedChooseButton();

};
