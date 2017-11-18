#pragma once
#include "afxwin.h"
#include <string>
#include <sstream>
#include "MySort.h"
using namespace std;

// CSortPage �Ի���

class CSortPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSortPage)

public:
	CSortPage();
	virtual ~CSortPage();

// �Ի�������
	enum { IDD = IDD_SORT_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartButton();
	afx_msg void OnBnClickedButton1();
	CButton m_checkprice;
	CButton m_checkarea;
	CButton m_checkacs;
	CButton m_checkdes;
	CEdit m_editTime;

	CString m_editFilename;

	int FileIndex;
	CString IMCString;//������
	CString m_editResult;
	std::string filePath[30];
	std::string RawFilename;
	std::string Order;
	std::string AreaOrPrice;
	std::string fileTmp;
};
