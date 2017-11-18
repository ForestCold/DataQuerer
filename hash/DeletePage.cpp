// DeletePage.cpp : 实现文件
//

#include "stdafx.h"
#include "MySurface.h"
#include "DeletePage.h"
#include "afxdialogex.h"
#include "MyDelete.h"
#include <time.h>

using namespace std;

// CDeletePage 对话框

IMPLEMENT_DYNAMIC(CDeletePage, CPropertyPage)

CDeletePage::CDeletePage()
	: CPropertyPage(CDeletePage::IDD)
	, m_editFilename(_T(""))
{

}

CDeletePage::~CDeletePage()
{
}

void CDeletePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILENAME_EDIT, m_editFilename);
	DDX_Control(pDX, IDC_EDIT1, m_editTime);
}


BEGIN_MESSAGE_MAP(CDeletePage, CPropertyPage)
	ON_BN_CLICKED(IDC_START_BUTTON, &CDeletePage::OnBnClickedStartButton)
END_MESSAGE_MAP()


// CDeletePage 消息处理程序


void CDeletePage::OnBnClickedStartButton()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);

	FileIndex=0;
	RawFilename="";

	//得到带空格的文件字符串RawFilename（未分割）
	setlocale(LC_ALL,"chs");
	wchar_t wch[255];
	char temp[255];
	wcscpy(wch,m_editFilename.GetString());
	wcstombs(temp,wch,254);
	RawFilename.append(temp);

	//将RawFilename分割
	stringstream strstm(RawFilename);
	while (strstm>>filePath[FileIndex]){ 
		filePath[FileIndex]="dataset//"+filePath[FileIndex]+".txt";
		FileIndex=FileIndex+1;
	};


	//此时FileIndex为文件个数
	//MyDelete函数实现
	//计时开始
	std::string usetime;
	time_t start=time(NULL);
	MyDelete(filePath,FileIndex);
	//计时结束
	time_t end=time(NULL);
	double timeuse=-difftime(start, end);
    stringstream ss;
    ss<<timeuse;
    ss>>usetime;
	IMCString=usetime.c_str();
	m_editResult=m_editResult+_T("删除总耗时为")+IMCString+_T("s。");
	//把m_editResult显示到窗体上
	m_editTime.SetWindowText(m_editResult);
}
