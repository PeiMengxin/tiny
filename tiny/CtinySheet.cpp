// CtinySheet.cpp : 实现文件
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
	this->AddPage(&m_page_tiny);
	this->AddPage(&m_page_coordinate);
}

CtinySheet::~CtinySheet()
{
	m_page_tiny.OnOK();
}


BEGIN_MESSAGE_MAP(CtinySheet, CPropertySheet)
END_MESSAGE_MAP()


// CtinySheet 消息处理程序
