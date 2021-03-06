#pragma once
#include "ChartCtrl/ChartCtrl.h"
#include "ChartCtrl/ChartLineSerie.h"
#include "ChartCtrl/ChartPointsSerie.h"
#include "datatransform.h"
#include "Param.h"
#include "afxwin.h"

// CCoodinatePage 对话框

#define DATA_SIZE 15
#define ID_NUM 3

class CCoordinatePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCoordinatePage)

public:
	CCoordinatePage();
	virtual ~CCoordinatePage();

// 对话框数据
	enum { IDD = IDD_COORDINATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon_indicator_black;
	HICON m_hIcon_indicator_green;
	HICON m_hIcon_indicator_yellow;
	HICON m_hIcon_indicator_red;

	CChartCtrl m_chartctrl_coodinate;
	CChartStandardAxis *m_pChartStandarAxisX;
	CChartStandardAxis *m_pChartStandarAxisY;
	std::vector <CChartLineSerie*> m_pChartLineSerie;
	std::vector <CChartPointsSerie*> m_pChartPointsSerie_Head;
	std::vector < COLORREF > ColorTable;
	std::vector<TChartString> LineName;

	virtual BOOL OnInitDialog();
	bool init();
	bool initChartCtrl();
	bool initLineName();
	void UpdateChartCtrlData();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	DataShow* m_showdata;
	CButton m_check_coor_id0;
	CButton m_check_coor_id1;
	CButton m_check_coor_id2;
	afx_msg void OnBnClickedCheckCoorId0();
	afx_msg void OnBnClickedCheckCoorId1();
	afx_msg void OnBnClickedCheckCoorId2();
	CButton m_check_longtraj;
	afx_msg void OnBnClickedCheckLongtraj();
	afx_msg void OnBnClickedButtonSetaxisscope();
	double m_axis_xmin;
	double m_axis_xmax;
	double m_axis_ymin;
	double m_axis_ymax;
	CStatic m_icon_obstacle;
	bool initIcon();
};
