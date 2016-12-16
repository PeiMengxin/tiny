#pragma once

#include "tinyDlg.h"
#include "CoordinatePage.h"

// CtinySheet

class CtinySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CtinySheet)

public:
	CtinySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CtinySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CtinySheet();

	CtinyDlg m_page_tiny;
	CCoordinatePage m_page_coordinate;

protected:
	DECLARE_MESSAGE_MAP()
};


