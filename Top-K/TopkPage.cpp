// TopkPage.cpp : 实现文件
//

#include "stdafx.h"
#include "MySurface.h"
#include "TopkPage.h"
#include "afxdialogex.h"
#include "MyTopK.h"
#include <time.h>

using namespace std;

// CTopkPage 对话框


IMPLEMENT_DYNAMIC(CTopkPage, CPropertyPage)

CTopkPage::CTopkPage()
	: CPropertyPage(CTopkPage::IDD)
	, m_editFilename(_T(""))
	, m_editK(0)
	, m_editResult(_T(""))
{

}

CTopkPage::~CTopkPage()
{
};


//自己定义的对象的初始化



void CTopkPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_editFilename);
	DDX_Text(pDX, IDC_EDIT2, m_editK);
	DDX_Text(pDX, IDC_EDIT3, m_editResult);
	DDX_Control(pDX, IDC_RESULT_EDIT, m_editResultShow);
}


BEGIN_MESSAGE_MAP(CTopkPage, CPropertyPage)

	ON_BN_CLICKED(IDC_DESCEND_RADIO, &CTopkPage::OnBnClickedDescendRadio)
	ON_BN_CLICKED(IDC_ASCEND_RADIO, &CTopkPage::OnBnClickedAscendRadio)
	ON_EN_CHANGE(IDC_EDIT2, &CTopkPage::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_START_BUTTON, &CTopkPage::OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_PRICE_RADIO, &CTopkPage::OnBnClickedPriceRadio)
	ON_BN_CLICKED(IDC_AREA_RADIO, &CTopkPage::OnBnClickedAreaRadio)
	ON_EN_CHANGE(IDC_RESULT_EDIT, &CTopkPage::OnEnChangeResultEdit)
END_MESSAGE_MAP()


// CTopkPage 消息处理程序




void CTopkPage::OnBnClickedDescendRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	Order="lts";
}


void CTopkPage::OnBnClickedAscendRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	Order="stl";
}


void CTopkPage::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void CTopkPage::OnBnClickedStartButton()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	int i=0;
	FileIndex=0;
	RawFilename="";
	m_editResult=_T("");

	//得到带空格的文件字符串RawFilename（未分割）
	setlocale(LC_ALL,"chs");
	wchar_t wch[255];
	char temp1[255];
	wcscpy(wch,m_editFilename.GetString());
	wcstombs(temp1,wch,254);
	RawFilename.append(temp1);

	//将RawFilename分割
	stringstream strstm(RawFilename);
	while (strstm>>filePath[FileIndex]){ 
		filePath[FileIndex]="dataset//"+filePath[FileIndex]+".txt";
		FileIndex=FileIndex+1;
	};

	MyTopKResult=new string[m_editK+1];
	m_editResultShow.SetWindowText(m_editResult);
	//此时FileIndex为文件个数

	//计时开始
	time_t start=time(NULL);
	MyTopK(m_editK,FileIndex,filePath,Order,AreaOrPrice,MyTopKResult);

	//计时结束
	time_t end=time(NULL);
	double timeuse=-difftime(start, end);
    stringstream ss;
    ss<<timeuse;
    ss>>usetime;

	//把记录转成CString并添到m_editResult
	for (i=0;i<m_editK;i++){
		IMCString=MyTopKResult[i].c_str();
		m_editResult=m_editResult+IMCString+_T("\r\n");}
	IMCString=usetime.c_str();
	m_editResult=m_editResult+_T("查询总耗时为")+IMCString+_T("s。");
	//把m_editResult显示到窗体上
	m_editResultShow.SetWindowText(m_editResult);
	delete []MyTopKResult;
	//IMCString=usetime.c_str();
}


void CTopkPage::OnBnClickedPriceRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	AreaOrPrice="总价";
}


void CTopkPage::OnBnClickedAreaRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	AreaOrPrice="总面积";
}


void CTopkPage::OnEnChangeResultEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
