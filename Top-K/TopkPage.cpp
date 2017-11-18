// TopkPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySurface.h"
#include "TopkPage.h"
#include "afxdialogex.h"
#include "MyTopK.h"
#include <time.h>

using namespace std;

// CTopkPage �Ի���


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


//�Լ�����Ķ���ĳ�ʼ��



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


// CTopkPage ��Ϣ�������




void CTopkPage::OnBnClickedDescendRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Order="lts";
}


void CTopkPage::OnBnClickedAscendRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Order="stl";
}


void CTopkPage::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



void CTopkPage::OnBnClickedStartButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);

	int i=0;
	FileIndex=0;
	RawFilename="";
	m_editResult=_T("");

	//�õ����ո���ļ��ַ���RawFilename��δ�ָ
	setlocale(LC_ALL,"chs");
	wchar_t wch[255];
	char temp1[255];
	wcscpy(wch,m_editFilename.GetString());
	wcstombs(temp1,wch,254);
	RawFilename.append(temp1);

	//��RawFilename�ָ�
	stringstream strstm(RawFilename);
	while (strstm>>filePath[FileIndex]){ 
		filePath[FileIndex]="dataset//"+filePath[FileIndex]+".txt";
		FileIndex=FileIndex+1;
	};

	MyTopKResult=new string[m_editK+1];
	m_editResultShow.SetWindowText(m_editResult);
	//��ʱFileIndexΪ�ļ�����

	//��ʱ��ʼ
	time_t start=time(NULL);
	MyTopK(m_editK,FileIndex,filePath,Order,AreaOrPrice,MyTopKResult);

	//��ʱ����
	time_t end=time(NULL);
	double timeuse=-difftime(start, end);
    stringstream ss;
    ss<<timeuse;
    ss>>usetime;

	//�Ѽ�¼ת��CString����m_editResult
	for (i=0;i<m_editK;i++){
		IMCString=MyTopKResult[i].c_str();
		m_editResult=m_editResult+IMCString+_T("\r\n");}
	IMCString=usetime.c_str();
	m_editResult=m_editResult+_T("��ѯ�ܺ�ʱΪ")+IMCString+_T("s��");
	//��m_editResult��ʾ��������
	m_editResultShow.SetWindowText(m_editResult);
	delete []MyTopKResult;
	//IMCString=usetime.c_str();
}


void CTopkPage::OnBnClickedPriceRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AreaOrPrice="�ܼ�";
}


void CTopkPage::OnBnClickedAreaRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AreaOrPrice="�����";
}


void CTopkPage::OnEnChangeResultEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
