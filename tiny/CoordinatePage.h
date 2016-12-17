#pragma once
#include "ChartCtrl/ChartCtrl.h"
#include "ChartCtrl/ChartLineSerie.h"
#include "ChartCtrl/ChartPointsSerie.h"
#include "datatransform.h"
#include "Param.h"

// CCoodinatePage �Ի���

#define COODINATE_WIDTH 500
#define COODINATE_HEIGHT 500
#define DATA_SIZE 25

class CCoordinatePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCoordinatePage)

public:
	CCoordinatePage();
	virtual ~CCoordinatePage();

// �Ի�������
	enum { IDD = IDD_COORDINATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CChartCtrl m_coodinate;
	CChartStandardAxis *m_pChartStandarAxisX;
	CChartStandardAxis *m_pChartStandarAxisY;
	std::vector <CChartLineSerie*> m_pChartLineSerie;
	std::vector <CChartPointsSerie*> m_pChartPointsSerie;
	std::vector <CChartPointsSerie*> m_pChartPointsSerie_Head;
	std::vector < COLORREF > ColorTable;
	ChartCtrlData m_chartctrldata;

	virtual BOOL OnInitDialog();
	bool init();
	bool initChartCtrl();
	void UpdateChartCtrlData();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	DataShow* m_showdata;
};
