#pragma once
#include "afxwin.h"
#include <string>
#include <sstream>
#include "MyDelete.h"
using namespace std;

// CDeletePage �Ի���

class CDeletePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDeletePage)

public:
	CDeletePage();
	virtual ~CDeletePage();

// �Ի�������
	enum { IDD = IDD_DELETE_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
