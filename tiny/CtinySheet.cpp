// CtinySheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tiny.h"
#include "CtinySheet.h"


// CtinySheet

IMPLEMENT_DYNAMIC(CtinySheet, CPropertySheet)

CtinySheet::CtinySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CtinySheet::CtinySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	this->m_psh.dwFlags &= ~(PSH_HASHELP);
	this->m_psh.dwFlags &= ~(PSH_NOMARGIN);
	this->m_psh.dwFlags |= PSH_NOAPPLYNOW;
	m_page_coordinate.m_psp.dwFlags &= ~(PSP_HASHELP);
	m_page_tiny.m_psp.dwFlags &= ~(PSP_HASHELP);

	this->AddPage(&m_page_tiny);
	this->AddPage(&m_page_coordinate);
}

CtinySheet::~CtinySheet()
{
	
}


BEGIN_MESSAGE_MAP(CtinySheet, CPropertySheet)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CtinySheet ��Ϣ�������


void CtinySheet::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//m_page_tiny.OnOK();
	CPropertySheet::OnClose();
}


BOOL CtinySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  �ڴ��������ר�ô���

	CWnd* pWnd = GetDlgItem(IDOK);
	if (pWnd && pWnd->GetSafeHwnd())
	{
		pWnd->ModifyStyle(BS_DEFPUSHBUTTON, 0);
		pWnd->ShowWindow(FALSE);
		pWnd->EnableWindow(FALSE);
		
	}

	pWnd = GetDlgItem(IDCANCEL);
	if (pWnd && pWnd->GetSafeHwnd())
	{
		pWnd->ModifyStyle(BS_DEFPUSHBUTTON, 0);
		pWnd->ShowWindow(FALSE);
		pWnd->EnableWindow(FALSE);
	}

	return bResult;
}
