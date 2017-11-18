// IndexPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySurface.h"
#include "IndexPage.h"
#include "afxdialogex.h"
#include "MyIndex.h"
#include <time.h>

using namespace std;

// CIndexPage �Ի���

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


// CIndexPage ��Ϣ�������


void CIndexPage::OnBnClickedSearchButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);

	WordIndex=0;
	RawKeyword="";
	Keyword="";
	m_editResult=_T("");
	std::string usetime="";

	//�õ��ַ���RawKeyword
	setlocale(LC_ALL,"chs");
	wchar_t wch[255];
	char temp[255];
	wcscpy(wch,m_editKeyword.GetString());
	wcstombs(temp,wch,254);
	RawKeyword.append(temp);

	//��RawKeyword�ָ�
	stringstream strstm(RawKeyword);
	while (strstm>>KeywordList[WordIndex]){ 
		Keyword=Keyword+KeywordList[WordIndex];
		WordIndex=WordIndex+1;
	};
	//��ʱ��ʼ
	time_t start=time(NULL);
	MyIndex(filePath,FileIndex,Keyword,IndexType,Myresult);
	//��ʱ����
	time_t end=time(NULL);
	double timeuse=-difftime(start, end);
    stringstream ss;
    ss<<timeuse;
    ss>>usetime;
	m_editResult=Myresult.c_str();
	IMCString=usetime.c_str();
	m_editResult=m_editResult+_T("��ѯ�ܺ�ʱΪ")+IMCString+_T("s��");
	//��ʱFileIndexΪ�ļ�����
	//MyIndex Search���ֺ���ʵ��

	//stringתCString
	//IMCString=Order.c_str();
	//m_editResult=IMCString+_T("\r\n")+m_editResult

	//��m_editResult��ʾ��������
	m_editResultShow.SetWindowText(m_editResult);
}


void CIndexPage::OnBnClickedIndexButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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

	//�õ����ո���ļ��ַ���RawFilename��δ�ָ
	setlocale(LC_ALL,"chs");
	wchar_t wch[255];
	char temp[255];
	wcscpy(wch,m_editFilename.GetString());
	wcstombs(temp,wch,254);
	RawFilename.append(temp);

	//��RawFilename�ָ�
	stringstream strstm(RawFilename);
	while (strstm>>filePath[FileIndex]){ 
		filePath[FileIndex]="dataset//"+filePath[FileIndex]+".txt";
		FileIndex=FileIndex+1;
	};


	//��ʱFileIndexΪ�ļ�����
	//MyIndex Index���ֺ���ʵ��

	
}




void CIndexPage::OnBnClickedChooseButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_checkPrice.SetCheck(0);
	m_checkArea.SetCheck(0);
	m_checkAddress.SetCheck(0);
	m_checkEstate.SetCheck(0);
	m_checkYear.SetCheck(0);
	for (int i=0;i<6;i++){
		IndexType[i]=false;}
}



