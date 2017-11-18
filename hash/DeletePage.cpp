// DeletePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySurface.h"
#include "DeletePage.h"
#include "afxdialogex.h"
#include "MyDelete.h"
#include <time.h>

using namespace std;

// CDeletePage �Ի���

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


// CDeletePage ��Ϣ�������


void CDeletePage::OnBnClickedStartButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);

	FileIndex=0;
	RawFilename="";

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
	//MyDelete����ʵ��
	//��ʱ��ʼ
	std::string usetime;
	time_t start=time(NULL);
	MyDelete(filePath,FileIndex);
	//��ʱ����
	time_t end=time(NULL);
	double timeuse=-difftime(start, end);
    stringstream ss;
    ss<<timeuse;
    ss>>usetime;
	IMCString=usetime.c_str();
	m_editResult=m_editResult+_T("ɾ���ܺ�ʱΪ")+IMCString+_T("s��");
	//��m_editResult��ʾ��������
	m_editTime.SetWindowText(m_editResult);
}
