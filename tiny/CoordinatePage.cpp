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
}


BEGIN_MESSAGE_MAP(CCoordinatePage, CPropertyPage)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_COOR_ID0, &CCoordinatePage::OnBnClickedCheckCoorId0)
	ON_BN_CLICKED(IDC_CHECK_COOR_ID1, &CCoordinatePage::OnBnClickedCheckCoorId1)
	ON_BN_CLICKED(IDC_CHECK_COOR_ID2, &CCoordinatePage::OnBnClickedCheckCoorId2)
END_MESSAGE_MAP()


// CCoodinatePage 消息处理程序


BOOL CCoordinatePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


bool CCoordinatePage::init()
{
	m_showdata = DataShow::GetInstance();

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
	m_pChartStandarAxisX->SetMinMax(-50, COODINATE_WIDTH);
	m_pChartStandarAxisY->SetMinMax(-1 * COODINATE_HEIGHT, 50);
	m_pChartStandarAxisX->SetTickIncrement(false, 50);
	m_pChartStandarAxisY->SetTickIncrement(false, 50);

	m_chartctrl_coodinate.GetLegend()->SetVisible(true);
	m_chartctrl_coodinate.GetLegend()->EnableShadow(false);

	for (size_t i = 0; i < ID_NUM; i++)
	{
		m_pChartPointsSerie_Head.push_back(m_chartctrl_coodinate.CreatePointsSerie());
		m_pChartPointsSerie_Head[i]->AddPoint(0, 0);

		m_pChartPointsSerie_Head[i]->SetColor(ColorTable[i]);
		m_pChartPointsSerie_Head[i]->SetPointSize(15, 15);
		m_pChartPointsSerie_Head[i]->SetPointType(CChartPointsSerie::ptRectangle);
		m_pChartPointsSerie_Head[i]->SetVisible(false);

		m_pChartLineSerie.push_back(m_chartctrl_coodinate.CreateLineSerie());
		m_pChartLineSerie[i]->AddPoints(chartctrldata.x.data(), chartctrldata.y.data(), DATA_SIZE);
		m_pChartLineSerie[i]->SetName(LineName[i]);
		m_pChartLineSerie[i]->SetColor(ColorTable[i]);
		m_pChartLineSerie[i]->SetWidth(5);
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
	m_chartctrl_coodinate.EnableRefresh(false);
	
	m_pChartLineSerie[0]->RemovePointsFromBegin(1);
	m_pChartLineSerie[0]->AddPoint(m_showdata->coodinate.x, m_showdata->coodinate.y);
	
	m_pChartPointsSerie_Head[0]->ClearSerie();
	m_pChartPointsSerie_Head[0]->AddPoint(m_showdata->coodinate.x, m_showdata->coodinate.y);
	
	m_chartctrl_coodinate.EnableRefresh(true);
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

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.x);
	GetDlgItem(IDC_STATIC_ID1_X)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.y);
	GetDlgItem(IDC_STATIC_ID1_Y)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), 0);
	GetDlgItem(IDC_CHECK_COOR_ID2)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.x);
	GetDlgItem(IDC_STATIC_ID2_X)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.y);
	GetDlgItem(IDC_STATIC_ID2_Y)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Pitch);
	GetDlgItem(IDC_STATIC_ANGLE_PITCH)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Roll);
	GetDlgItem(IDC_STATIC_ANGLE_ROLL)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Yaw);
	GetDlgItem(IDC_STATIC_ANGLE_YAW)->SetWindowText(cstr_temp);

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
