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
	DDX_Control(pDX, IDC_Coodinate, m_coodinate);
}


BEGIN_MESSAGE_MAP(CCoordinatePage, CPropertyPage)
	ON_WM_TIMER()
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

	initColorTable(ColorTable);
	initChartCtrl();

	SetTimer(0, 20, NULL);

	return true;
}

bool CCoordinatePage::initChartCtrl()
{
	int m_count = 0;

	m_coodinate.SetBackColor(RGB(0, 0, 0));

	m_pChartStandarAxisY = m_coodinate.CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pChartStandarAxisX = m_coodinate.CreateStandardAxis(CChartCtrl::BottomAxis);
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
		m_chartctrldata.x.push_back(0);
		m_chartctrldata.y.push_back(0);
	}

	m_coodinate.EnableRefresh(false);
	m_coodinate.RemoveAllSeries();
	m_pChartStandarAxisX->SetMinMax(-1 * COODINATE_WIDTH, COODINATE_WIDTH);
	m_pChartStandarAxisY->SetMinMax(-1 * COODINATE_HEIGHT, COODINATE_HEIGHT);

	/*m_pChartPointsSerie.push_back(m_coodinate.CreatePointsSerie());
	m_pChartPointsSerie[0]->AddPoints(m_chartctrldata.x.data(), m_chartctrldata.y.data(), DATA_SIZE);

	m_pChartPointsSerie[0]->SetColor(ColorTable[0]);
	m_pChartPointsSerie[0]->SetPointSize(5, 5);*/

	m_pChartPointsSerie_Head.push_back(m_coodinate.CreatePointsSerie());
	m_pChartPointsSerie_Head[0]->AddPoint(0, 0);

	m_pChartPointsSerie_Head[0]->SetColor(ColorTable[0]);
	m_pChartPointsSerie_Head[0]->SetPointSize(15, 15);

	m_pChartLineSerie.push_back(m_coodinate.CreateLineSerie());
	m_pChartLineSerie[0]->AddPoints(m_chartctrldata.x.data(), m_chartctrldata.y.data(), DATA_SIZE);

	m_pChartLineSerie[0]->SetColor(ColorTable[0]);
	m_pChartLineSerie[0]->SetWidth(5);

	m_pChartLineSerie[0]->SetSeriesOrdering(poNoOrdering);

	m_coodinate.EnableRefresh(true);

	return true;
}


void CCoordinatePage::UpdateChartCtrlData()
{
	m_coodinate.EnableRefresh(false);
	
	//m_pChartPointsSerie[0]->ClearSerie();
	m_pChartPointsSerie_Head[0]->ClearSerie();
	m_pChartLineSerie[0]->ClearSerie();

	m_chartctrldata.x.push_back(m_showdata->angle.Roll);
	m_chartctrldata.y.push_back(m_showdata->angle.Yaw);
	m_chartctrldata.x.erase(m_chartctrldata.x.begin());
	m_chartctrldata.y.erase(m_chartctrldata.y.begin());

	//m_pChartPointsSerie[0]->AddPoints(m_chartctrldata.x.data(), m_chartctrldata.y.data(), DATA_SIZE);
	m_pChartPointsSerie_Head[0]->AddPoint(m_showdata->angle.Roll, m_showdata->angle.Yaw);
	m_pChartLineSerie[0]->AddPoints(m_chartctrldata.x.data(), m_chartctrldata.y.data(), DATA_SIZE);
	/*m_pChartPointsSerie[0]->AddPoint(m_showdata->angle.Roll, m_showdata->angle.Yaw);
	m_pChartPointsSerie[0]->RemovePointsFromBegin(0);*/

	m_coodinate.EnableRefresh(true);
}

void CCoordinatePage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	UpdateChartCtrlData();

	CStringW cstr_temp;

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.id);
	GetDlgItem(IDC_STATIC_ID)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.x);
	GetDlgItem(IDC_STATIC_X)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->coodinate.y);
	GetDlgItem(IDC_STATIC_Y)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Pitch);
	GetDlgItem(IDC_STATIC_ANGLE_PITCH)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Roll);
	GetDlgItem(IDC_STATIC_ANGLE_ROLL)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Yaw);
	GetDlgItem(IDC_STATIC_ANGLE_YAW)->SetWindowText(cstr_temp);

	CPropertyPage::OnTimer(nIDEvent);
}
