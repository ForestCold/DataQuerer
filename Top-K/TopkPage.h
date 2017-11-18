#pragma once
#include "afxwin.h"
#include <string>
#include <sstream>
#include "MyTopK.h"
using namespace std;

// CTopkPage 对话框

class CTopkPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTopkPage)

public:
	CTopkPage();
	virtual ~CTopkPage();

// 对话框数据
	enum { IDD = IDD_TOPK_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedPriceRadio();
	afx_msg void OnBnClickedAreaRadio();
	afx_msg void OnBnClickedDescendRadio();
	afx_msg void OnBnClickedAscendRadio();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedStartButton();
	CEdit m_editResultShow;
	
	CString m_editFilename;
	int m_editK;

	int FileIndex;
	CString m_editResult;
	CString IMCString;
	std::string Order;
	std::string AreaOrPrice;
	std::string filePath[30];
	std::string RawFilename;
	std::string *MyTopKResult;
	afx_msg void OnEnChangeResultEdit();
	string usetime;
};
