// SortPage.cpp : 实现文件
//

#include "stdafx.h"
#include "MySurface.h"
#include "SortPage.h"
#include "afxdialogex.h"
#include "MySort.h"
#include <time.h>

using namespace std;

// CSortPage 对话框

IMPLEMENT_DYNAMIC(CSortPage, CPropertyPage)

CSortPage::CSortPage()
	: CPropertyPage(CSortPage::IDD)
	, m_editFilename(_T(""))
{

}

CSortPage::~CSortPage()
{
}

void CSortPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILENAME_EDIT, m_editFilename);
	DDX_Control(pDX, IDC_CHECK1, m_checkprice);
	DDX_Control(pDX, IDC_CHECK4, m_checkarea);
	DDX_Control(pDX, IDC_CHECK2, m_checkacs);
	DDX_Control(pDX, IDC_CHECK3, m_checkdes);
	DDX_Control(pDX, IDC_EDIT1, m_editTime);
}


BEGIN_MESSAGE_MAP(CSortPage, CPropertyPage)
	ON_BN_CLICKED(IDC_START_BUTTON, &CSortPage::OnBnClickedStartButton)
	

	ON_BN_CLICKED(IDC_BUTTON1, &CSortPage::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSortPage 消息处理程序


void CSortPage::OnBnClickedStartButton()
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
	if (1 == m_checkprice.GetCheck())   
    {   
        AreaOrPrice="总价";  
    };
	if (1 == m_checkarea.GetCheck())   
    {   
        AreaOrPrice="总面积";  
    };
	if (1 == m_checkacs.GetCheck())   
    {   
        Order="lts";  
    };
	if (1 == m_checkdes.GetCheck())   
    {   
        Order="stl";  
    };
	//此时FileIndex为文件个数
	//MySort函数实现
	//计时开始
	std::string usetime;
	time_t start=time(NULL);
	MySort(filePath,FileIndex,Order,AreaOrPrice);
	//计时结束
	time_t end=time(NULL);
	double timeuse=-difftime(start, end);
    stringstream ss;
    ss<<timeuse;
    ss>>usetime;
	IMCString=usetime.c_str();
	m_editResult=m_editResult+_T("排序总耗时为")+IMCString+_T("s。");
	//把m_editResult显示到窗体上
	m_editTime.SetWindowText(m_editResult);

}






//Order="lts";
//Order="stl";
//AreaOrPrice="总价";
//AreaOrPrice="总面积";







void CSortPage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_checkprice.SetCheck(0); 
	m_checkarea.SetCheck(0); 
	m_checkacs.SetCheck(0); 
	m_checkdes.SetCheck(0); 
}
