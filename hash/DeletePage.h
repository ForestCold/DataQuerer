#pragma once
#include "afxwin.h"
#include <string>
#include <sstream>
#include "MyDelete.h"
using namespace std;

// CDeletePage 对话框

class CDeletePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDeletePage)

public:
	CDeletePage();
	virtual ~CDeletePage();

// 对话框数据
	enum { IDD = IDD_DELETE_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartButton();

	CString m_editFilename;

	int FileIndex;
	CString IMCString;
	CString m_editResult;
	std::string filePath[30];
	std::string RawFilename;
	CEdit m_editTime;
};
