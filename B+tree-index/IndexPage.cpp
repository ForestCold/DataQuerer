// IndexPage.cpp : 实现文件
//

#include "stdafx.h"
#include "MySurface.h"
#include "IndexPage.h"
#include "afxdialogex.h"
#include "MyIndex.h"
#include <time.h>

using namespace std;

// CIndexPage 对话框

IMPLEMENT_DYNAMIC(CIndexPage, CPropertyPage)

CIndexPage::CIndexPage()
	: CPropertyPage(CIndexPage::IDD)
	, m_editFilename(_T(""))
	, m_editKeyword(_T(""))
{

}

CIndexPage::~CIndexPage()
{
}

void CIndexPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILENAME_EDIT, m_editFilename);
	DDX_Text(pDX, IDC_KEYWORD_EDIT, m_editKeyword);
	DDX_Control(pDX, IDC_EDIT2, m_editResultShow);
	DDX_Control(pDX, IDC_PRICE_CHECK, m_checkPrice);
	DDX_Control(pDX, IDC_AREA_CHECK, m_checkArea);
	DDX_Control(pDX, IDC_ADDRESS_CHECK, m_checkAddress);
	DDX_Control(pDX, IDC_ESTATE_CHECK, m_checkEstate);
	DDX_Control(pDX, IDC_YEAR_CHECK, m_checkYear);
}


BEGIN_MESSAGE_MAP(CIndexPage, CPropertyPage)
	ON_BN_CLICKED(IDC_SEARCH_BUTTON, &CIndexPage::OnBnClickedSearchButton)
	ON_BN_CLICKED(IDC_INDEX_BUTTON, &CIndexPage::OnBnClickedIndexButton)
	ON_BN_CLICKED(IDC_CHOOSE_BUTTON, &CIndexPage::OnBnClickedChooseButton)
END_MESSAGE_MAP()


// CIndexPage 消息处理程序


void CIndexPage::OnBnClickedSearchButton()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);

	WordIndex=0;
	RawKeyword="";
	Keyword="";
	m_editResult=_T("");
	std::string usetime="";

	//得到字符串RawKeyword
	setlocale(LC_ALL,"chs");
	wchar_t wch[255];
	char temp[255];
	wcscpy(wch,m_editKeyword.GetString());
	wcstombs(temp,wch,254);
	RawKeyword.append(temp);

	//将RawKeyword分割
	stringstream strstm(RawKeyword);
	while (strstm>>KeywordList[WordIndex]){ 
		Keyword=Keyword+KeywordList[WordIndex];
		WordIndex=WordIndex+1;
	};
	//计时开始
	time_t start=time(NULL);
	MyIndex(filePath,FileIndex,Keyword,IndexType,Myresult);
	//计时结束
	time_t end=time(NULL);
	double timeuse=-difftime(start, end);
    stringstream ss;
    ss<<timeuse;
    ss>>usetime;
	m_editResult=Myresult.c_str();
	IMCString=usetime.c_str();
	m_editResult=m_editResult+_T("查询总耗时为")+IMCString+_T("s。");
	//此时FileIndex为文件个数
	//MyIndex Search部分函数实现

	//string转CString
	//IMCString=Order.c_str();
	//m_editResult=IMCString+_T("\r\n")+m_editResult

	//把m_editResult显示到窗体上
	m_editResultShow.SetWindowText(m_editResult);
}


void CIndexPage::OnBnClickedIndexButton()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);

	if(1==m_checkPrice.GetCheck()){
	IndexType[3]=true;};
	if(1==m_checkArea.GetCheck()){
	IndexType[4]=true;};
	if(1==m_checkAddress.GetCheck()){
	IndexType[1]=true;};
	if(1==m_checkEstate.GetCheck()){
	IndexType[2]=true;};
	if(1==m_checkYear.GetCheck()){
	IndexType[5]=true;};
	
	FileIndex=0;
	RawFilename="";
	m_editResult=_T("");

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
	//MyIndex Index部分函数实现

	
}




void CIndexPage::OnBnClickedChooseButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_checkPrice.SetCheck(0);
	m_checkArea.SetCheck(0);
	m_checkAddress.SetCheck(0);
	m_checkEstate.SetCheck(0);
	m_checkYear.SetCheck(0);
	for (int i=0;i<6;i++){
		IndexType[i]=false;}
}



