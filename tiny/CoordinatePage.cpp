// CoodinatePage.cpp : 实现文件
//

#include "stdafx.h"
#include "tiny.h"
#include "CoordinatePage.h"
#include "afxdialogex.h"

// CCoodinatePage 对话框

IMPLEMENT_DYNAMIC(CCoordinatePage, CPropertyPage)

CCoordinatePage::CCoordinatePage()
	: CPropertyPage(CCoordinatePage::IDD)
	, m_axis_xmin(-100)
	, m_axis_xmax(500)
	, m_axis_ymin(-100)
	, m_axis_ymax(500)
{

}

CCoordinatePage::~CCoordinatePage()
{
}

void CCoordinatePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Coodinate, m_chartctrl_coodinate);
	DDX_Control(pDX, IDC_CHECK_COOR_ID0, m_check_coor_id0);
	DDX_Control(pDX, IDC_CHECK_COOR_ID1, m_check_coor_id1);
	DDX_Control(pDX, IDC_CHECK_COOR_ID2, m_check_coor_id2);
	DDX_Control(pDX, IDC_CHECK_LONGTRAJ, m_check_longtraj);
	DDX_Text(pDX, IDC_EDIT_AXIS_XMIN, m_axis_xmin);
	DDX_Text(pDX, IDC_EDIT_AXIS_XMAX, m_axis_xmax);
	DDX_Text(pDX, IDC_EDIT_AXIS_YMIN, m_axis_ymin);
	DDX_Text(pDX, IDC_EDIT_AXIS_YMAX, m_axis_ymax);
	DDX_Control(pDX, IDC_ICON_OBSTACLE, m_icon_obstacle);
	DDX_Control(pDX, IDC_CHECK_RADARMODEL, m_check_radarmodel);
	DDX_Control(pDX, IDC_BUTTON_SETAXISSCOPE, m_button_setaxisscope);
}


BEGIN_MESSAGE_MAP(CCoordinatePage, CPropertyPage)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_COOR_ID0, &CCoordinatePage::OnBnClickedCheckCoorId0)
	ON_BN_CLICKED(IDC_CHECK_COOR_ID1, &CCoordinatePage::OnBnClickedCheckCoorId1)
	ON_BN_CLICKED(IDC_CHECK_COOR_ID2, &CCoordinatePage::OnBnClickedCheckCoorId2)
	ON_BN_CLICKED(IDC_CHECK_LONGTRAJ, &CCoordinatePage::OnBnClickedCheckLongtraj)
	ON_BN_CLICKED(IDC_BUTTON_SETAXISSCOPE, &CCoordinatePage::OnBnClickedButtonSetaxisscope)
	ON_BN_CLICKED(IDC_CHECK_RADARMODEL, &CCoordinatePage::OnBnClickedCheckRadarmodel)
END_MESSAGE_MAP()


// CCoodinatePage 消息处理程序


BOOL CCoordinatePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	/*CButton *pokbutton = (CButton *)GetDlgItem(IDOK);

	pokbutton->ModifyStyle(BS_DEFPUSHBUTTON, 0);*/

	init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


bool CCoordinatePage::init()
{
	m_showdata = DataShow::GetInstance();

	initIcon();

	initLineName();
	initColorTable(ColorTable);
	initChartCtrl();

	SetTimer(0, 20, NULL);

	return true;
}

bool CCoordinatePage::initChartCtrl()
{
	int m_count = 0;
	ChartCtrlData chartctrldata;

	m_chartctrl_coodinate.SetBackColor(RGB(0, 0, 0));

	m_pChartStandarAxisY = m_chartctrl_coodinate.CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pChartStandarAxisX = m_chartctrl_coodinate.CreateStandardAxis(CChartCtrl::BottomAxis);
	//m_pChartStandarAxisY->SetInverted(true);
	m_pChartStandarAxisX->SetAutomatic(false);
	m_pChartStandarAxisY->SetAutomatic(false);
	m_pChartStandarAxisX->SetAxisColor(RGB(255, 255, 255));
	m_pChartStandarAxisY->SetAxisColor(RGB(255, 255, 255));
	m_pChartStandarAxisX->SetTextColor(RGB(255, 255, 255));
	m_pChartStandarAxisY->SetTextColor(RGB(255, 255, 255));
	//m_pChartStandarAxisX->SetTextColor(m_chartctrl.GetBackColor());

	for (size_t i = 0; i < DATA_SIZE; i++)
	{
		m_count++;
		chartctrldata.x.push_back(0);
		chartctrldata.y.push_back(0);
	}

	m_chartctrl_coodinate.EnableRefresh(false);
	m_chartctrl_coodinate.RemoveAllSeries();
	m_pChartStandarAxisX->SetMinMax(m_axis_xmin, m_axis_xmax);
	m_pChartStandarAxisY->SetMinMax(m_axis_ymin, m_axis_ymax);
	m_pChartStandarAxisX->SetTickIncrement(false, 50);
	m_pChartStandarAxisY->SetTickIncrement(false, 50);

	m_chartctrl_coodinate.GetLegend()->SetVisible(true);
	m_chartctrl_coodinate.GetLegend()->EnableShadow(false);

	for (size_t i = 0; i < ID_NUM; i++)
	{
		m_pChartPointsSerie_Head.push_back(m_chartctrl_coodinate.CreatePointsSerie());
		m_pChartPointsSerie_Head[i]->AddPoint(0, 0);

		m_pChartPointsSerie_Head[i]->SetColor(ColorTable[i]);
		m_pChartPointsSerie_Head[i]->SetPointSize(10, 10);
		m_pChartPointsSerie_Head[i]->SetPointType(CChartPointsSerie::ptRectangle);
		m_pChartPointsSerie_Head[i]->SetVisible(false);

		m_pChartLineSerie.push_back(m_chartctrl_coodinate.CreateLineSerie());
		m_pChartLineSerie[i]->AddPoints(chartctrldata.x.data(), chartctrldata.y.data(), DATA_SIZE);
		m_pChartLineSerie[i]->SetName(LineName[i]);
		m_pChartLineSerie[i]->SetColor(ColorTable[i]);
		m_pChartLineSerie[i]->SetWidth(3);
		m_pChartLineSerie[i]->SetSeriesOrdering(poNoOrdering);
		m_pChartLineSerie[i]->SetVisible(false);
	}
	
	m_pChartLineSerie[0]->SetVisible(true);
	m_pChartPointsSerie_Head[0]->SetVisible(true);
	m_check_coor_id0.SetCheck(1);

	m_chartctrl_coodinate.EnableRefresh(true);

	return true;
}


bool CCoordinatePage::initLineName()
{
	LineName.push_back(_T("ID0"));
	LineName.push_back(_T("ID1"));
	LineName.push_back(_T("ID2"));

	return true;
}

void CCoordinatePage::UpdateChartCtrlData()
{
	int state = m_check_radarmodel.GetCheck();

	if (state == 1)
	{
		m_chartctrl_coodinate.EnableRefresh(false);
		
		if (!m_check_longtraj.GetCheck())
		{
			m_pChartLineSerie[0]->RemovePointsFromBegin(1);
			m_pChartLineSerie[1]->RemovePointsFromBegin(1);
			m_pChartLineSerie[2]->RemovePointsFromBegin(1);
		}

		m_pChartLineSerie[0]->AddPoint(m_showdata->coodinate.x, m_showdata->coodinate.y);
		m_pChartLineSerie[1]->AddPoint(m_showdata->hopecoor.x, m_showdata->hopecoor.y);
		m_pChartLineSerie[2]->AddPoint(m_showdata->originalQR.x, m_showdata->originalQR.y);

		m_pChartPointsSerie_Head[0]->ClearSerie();
		m_pChartPointsSerie_Head[0]->AddPoint(m_showdata->coodinate.x, m_showdata->coodinate.y);
		m_pChartPointsSerie_Head[1]->ClearSerie();
		m_pChartPointsSerie_Head[1]->AddPoint(m_showdata->hopecoor.x, m_showdata->hopecoor.y);
		m_pChartPointsSerie_Head[2]->ClearSerie();
		m_pChartPointsSerie_Head[2]->AddPoint(m_showdata->originalQR.x, m_showdata->originalQR.y);

		/*m_pChartStandarAxisX->SetMinMax(m_showdata->coodinate.x - 500, m_showdata->coodinate.x + 500);
		m_pChartStandarAxisY->SetMinMax(m_showdata->coodinate.y - 500, m_showdata->coodinate.y + 500);*/

		m_pChartStandarAxisX->SetMinMax(m_showdata->coodinate.x + m_axis_xmin, m_showdata->coodinate.x + m_axis_xmax);
		m_pChartStandarAxisY->SetMinMax(m_showdata->coodinate.y + m_axis_ymin, m_showdata->coodinate.y + m_axis_ymax);

		m_chartctrl_coodinate.EnableRefresh(true);
	}
	else
	{
		m_chartctrl_coodinate.EnableRefresh(false);

		if (!m_check_longtraj.GetCheck())
		{
			m_pChartLineSerie[0]->RemovePointsFromBegin(1);
			m_pChartLineSerie[1]->RemovePointsFromBegin(1);
			m_pChartLineSerie[2]->RemovePointsFromBegin(1);
		}

		m_pChartLineSerie[0]->AddPoint(m_showdata->coodinate.x, m_showdata->coodinate.y);
		m_pChartLineSerie[1]->AddPoint(m_showdata->hopecoor.x, m_showdata->hopecoor.y);
		m_pChartLineSerie[2]->AddPoint(m_showdata->originalQR.x, m_showdata->originalQR.y);

		m_pChartPointsSerie_Head[0]->ClearSerie();
		m_pChartPointsSerie_Head[0]->AddPoint(m_showdata->coodinate.x, m_showdata->coodinate.y);
		m_pChartPointsSerie_Head[1]->ClearSerie();
		m_pChartPointsSerie_Head[1]->AddPoint(m_showdata->hopecoor.x, m_showdata->hopecoor.y);
		m_pChartPointsSerie_Head[2]->ClearSerie();
		m_pChartPointsSerie_Head[2]->AddPoint(m_showdata->originalQR.x, m_showdata->originalQR.y);

		m_chartctrl_coodinate.EnableRefresh(true);
	}
}

void CCoordinatePage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	UpdateChartCtrlData();

	CStringW cstr_temp;

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.id);
	GetDlgItem(IDC_CHECK_COOR_ID0)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.x);
	GetDlgItem(IDC_STATIC_ID0_X)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.y);
	GetDlgItem(IDC_STATIC_ID0_Y)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), 0);
	GetDlgItem(IDC_CHECK_COOR_ID1)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->hopecoor.x);
	GetDlgItem(IDC_STATIC_ID1_X)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->hopecoor.y);
	GetDlgItem(IDC_STATIC_ID1_Y)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), 0);
	GetDlgItem(IDC_CHECK_COOR_ID2)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->originalQR.x);
	GetDlgItem(IDC_STATIC_ID2_X)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->originalQR.y);
	GetDlgItem(IDC_STATIC_ID2_Y)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Pitch);
	GetDlgItem(IDC_STATIC_ANGLE_PITCH)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Roll);
	GetDlgItem(IDC_STATIC_ANGLE_ROLL)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Yaw);
	GetDlgItem(IDC_STATIC_ANGLE_YAW)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->originalQR.z);
	GetDlgItem(IDC_STATIC_ANGLE_HEIGHT)->SetWindowText(cstr_temp);

	if (m_showdata->obstacle)
	{
		m_icon_obstacle.SetIcon(m_hIcon_indicator_red);
	}
	else
	{
		m_icon_obstacle.SetIcon(m_hIcon_indicator_green);
	}

	switch (m_showdata->obstacle)
	{
		case 0:
		{
			m_icon_obstacle.SetIcon(m_hIcon_indicator_red);
			break;
		}
		case 1:
		{
			m_icon_obstacle.SetIcon(m_hIcon_indicator_green);
			break;
		}
		case 2:
		{
			m_icon_obstacle.SetIcon(m_hIcon_indicator_yellow);
			break;
		}
		case 3:
		{
			m_icon_obstacle.SetIcon(m_hIcon_indicator_black);
			break;
		}
		default:
			break;
	}

	CPropertyPage::OnTimer(nIDEvent);
}


void CCoordinatePage::OnBnClickedCheckCoorId0()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_coor_id0.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[0]->SetVisible(false);
		m_pChartPointsSerie_Head[0]->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie[0]->SetVisible(true);
		m_pChartPointsSerie_Head[0]->SetVisible(true);
	}
}


void CCoordinatePage::OnBnClickedCheckCoorId1()
{
	// TODO:  在此添加控件通知处理程序代码
	int state = m_check_coor_id1.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[1]->SetVisible(false);
		m_pChartPointsSerie_Head[1]->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie[1]->SetVisible(true);
		m_pChartPointsSerie_Head[1]->SetVisible(true);
	}
}


void CCoordinatePage::OnBnClickedCheckCoorId2()
{
	// TODO:  在此添加控件通知处理程序代码
	int state = m_check_coor_id2.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[2]->SetVisible(false);
		m_pChartPointsSerie_Head[2]->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie[2]->SetVisible(true);
		m_pChartPointsSerie_Head[2]->SetVisible(true);
	}
}


void CCoordinatePage::OnBnClickedCheckLongtraj()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_longtraj.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[0]->ClearSerie();
		m_pChartLineSerie[1]->ClearSerie();
		m_pChartLineSerie[2]->ClearSerie();
		for (size_t i = 0; i < DATA_SIZE; i++)
		{
			m_pChartLineSerie[0]->AddPoint(m_showdata->coodinate.x, m_showdata->coodinate.y);
			m_pChartLineSerie[1]->AddPoint(m_showdata->hopecoor.x, m_showdata->hopecoor.y);
			m_pChartLineSerie[2]->AddPoint(m_showdata->originalQR.x, m_showdata->originalQR.y);
		}
	}
	
}


void CCoordinatePage::OnBnClickedButtonSetaxisscope()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);

	m_pChartStandarAxisX->SetMinMax(m_axis_xmin, m_axis_xmax);
	m_pChartStandarAxisY->SetMinMax(m_axis_ymin, m_axis_ymax);
}


bool CCoordinatePage::initIcon()
{
	m_hIcon_indicator_black = AfxGetApp()->LoadIcon(IDI_ICON_INDICATOR_BLACK);
	m_hIcon_indicator_green = AfxGetApp()->LoadIcon(IDI_ICON_INDICATOR_GREEN);
	m_hIcon_indicator_yellow = AfxGetApp()->LoadIcon(IDI_ICON_INDICATOR_YELLOW);
	m_hIcon_indicator_red = AfxGetApp()->LoadIcon(IDI_ICON_INDICATOR_RED);

	m_icon_obstacle.SetIcon(m_hIcon_indicator_green);

	return true;
}


void CCoordinatePage::OnBnClickedCheckRadarmodel()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_radarmodel.GetCheck();

	if (state == 0)
	{
		/*m_pChartStandarAxisX->SetTickIncrement(true, 100);
		m_pChartStandarAxisY->SetTickIncrement(true, 100);*/
		//m_button_setaxisscope.EnableWindow(true);
		OnBnClickedButtonSetaxisscope();
	}
	else
	{
		/*m_pChartStandarAxisX->SetTickIncrement(false, 100);
		m_pChartStandarAxisY->SetTickIncrement(false, 100);*/

		//m_button_setaxisscope.EnableWindow(false);
	}
}
