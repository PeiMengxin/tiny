
// tinyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "tiny.h"
#include "tinyDlg.h"
#include "afxdialogex.h"
#include "datatransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CPropertyPage
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CPropertyPage(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CPropertyPage)
END_MESSAGE_MAP()


// CtinyDlg 对话框



CtinyDlg::CtinyDlg(/*CWnd* pParent /*=NULL*/)
	: CPropertyPage(CtinyDlg::IDD/*, pParent*/)
	, isTerminal(false)
	, m_serial_closing(false)
	, m_scope_y(100)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtinyDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMBAUDRATE, m_combo_combaudrate);
	DDX_Control(pDX, IDC_COMBO_COMNUM, m_combo_comnum);
	DDX_Control(pDX, IDC_BUTTON_OPENCOM, m_btn_opencom);
	DDX_Control(pDX, IDC_BUTTON_WRITEPARAM, m_btn_writeparam);
	DDX_Control(pDX, IDC_BUTTON_READPARAM, m_btn_readparam);
	DDX_Control(pDX, IDC_BUTTON_WRITEFLASH, m_btn_writeflash);
	DDX_Control(pDX, IDC_STATIC_COMSTATE, m_static_comstate);
	DDX_Control(pDX, IDC_ENABLE_SETHEIGHT, m_check_setheight);
	DDX_Control(pDX, IDC_ENABLE_AVOIDOBJECTION, m_check_avoidobjection);

	DDX_Text(pDX, IDC_DATASETTING_ROCKERMID1, m_edit_rockermid1);
	DDX_Text(pDX, IDC_DATASETTING_ROCKERMID2, m_edit_rockermid2);
	DDX_Text(pDX, IDC_DATASETTING_ROCKERMID3, m_edit_rockermid3);
	DDX_Text(pDX, IDC_DATASETTING_ROCKERMID4, m_edit_rockermid4);
	DDX_Text(pDX, IDC_DATASETTING_EXPECTEDHEIGHT, m_edit_exceptheight);
	DDX_Text(pDX, IDC_DATASETTING_AVOIDSCOPE, m_edit_avoidscope);
	DDX_Text(pDX, IDC_DATASETTING_SENSITIVITY, m_edit_sensitivity);
	DDX_Text(pDX, IDC_DATASETTING_PID_P_CUSTOM, m_edit_pid_p_custom);
	DDX_Text(pDX, IDC_DATASETTING_PID_I_CUSTOM, m_edit_pid_i_custom);
	DDX_Text(pDX, IDC_DATASETTING_PID_D_CUSTOM, m_edit_pid_d_custom);
	DDX_Text(pDX, IDC_DATASETTING_PID_P_OUTERLAYER, m_edit_pid_p_outerlayer);
	DDX_Text(pDX, IDC_DATASETTING_PID_I_OUTERLAYER, m_edit_pid_i_outerlayer);
	DDX_Text(pDX, IDC_DATASETTING_PID_D_OUTERLAYER, m_edit_pid_d_outerlayer);
	DDX_Text(pDX, IDC_DATASETTING_PID_P_INNERLAYER, m_edit_pid_p_innerlayer);
	DDX_Text(pDX, IDC_DATASETTING_PID_I_INNERLAYER, m_edit_pid_i_innerlayer);
	DDX_Text(pDX, IDC_DATASETTING_PID_D_INNERLAYER, m_edit_pid_d_innerlayer);
	DDX_Text(pDX, IDC_DATASETTING_PID_P_POSITION, m_edit_pid_p_position);
	DDX_Text(pDX, IDC_DATASETTING_PID_I_POSITION, m_edit_pid_i_position);
	DDX_Text(pDX, IDC_DATASETTING_PID_D_POSITION, m_edit_pid_d_position);
	DDX_Text(pDX, IDC_DATASETTING_PID_P_HEIGHT, m_edit_pid_p_height);
	DDX_Text(pDX, IDC_DATASETTING_PID_I_HEIGHT, m_edit_pid_i_height);
	DDX_Text(pDX, IDC_DATASETTING_PID_D_HEIGHT, m_edit_pid_d_height);

	DDX_Control(pDX, IDC_ICON_STATE, m_icon_state);
	DDX_Control(pDX, IDC_ICON_COMSTATE, m_icon_comstate);
	DDX_Control(pDX, IDC_CUSTOM1, m_chartctrl);
	DDX_Control(pDX, IDC_BUTTON_COLOR_FUSIONDATA, m_btn_color_fusiondata);
	DDX_Control(pDX, IDC_CHECK_FUSIONDATA, m_check_fusiondata);
	DDX_Control(pDX, IDC_CHECK_EXCEPTEDHEIGHT, m_check_height);
	DDX_Control(pDX, IDC_BUTTON_COLOR_EXCEPTEDHEIGHT, m_btn_color_height);
	DDX_Control(pDX, IDC_CHECK_AUTOSCOPE, m_check_autoscope);
	DDX_Control(pDX, IDC_CHECK_ACC, m_check_acc);
	DDX_Control(pDX, IDC_CHECK_GRY, m_check_gry);
	DDX_Control(pDX, IDC_CHECK_HM, m_check_hm);
	DDX_Control(pDX, IDC_CHECK_ANGLE, m_check_angle);
}

BEGIN_MESSAGE_MAP(CtinyDlg, CPropertyPage)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM, &CtinyDlg::OnBnClickedButtonOpencom)
	ON_BN_CLICKED(IDC_BUTTON_WRITEPARAM, &CtinyDlg::OnBnClickedButtonWriteparam)
	ON_BN_CLICKED(IDC_BUTTON_READPARAM, &CtinyDlg::OnBnClickedButtonReadparam)
	ON_BN_CLICKED(IDC_BUTTON_WRITEFLASH, &CtinyDlg::OnBnClickedButtonWriteflash)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_MESSAGE(CPN_SELENDOK, OnSelEndOK)
	ON_MESSAGE(CPN_SELENDCANCEL, OnSelEndCancel)
	ON_MESSAGE(CPN_SELCHANGE, OnSelChange)
	ON_MESSAGE(CPN_CLOSEUP, OnCloseUp)
	ON_MESSAGE(CPN_DROPDOWN, OnDropDown)
	ON_BN_CLICKED(IDC_CHECK_FUSIONDATA, &CtinyDlg::OnBnClickedCheckFusiondata)
	ON_BN_CLICKED(IDC_CHECK_EXCEPTEDHEIGHT, &CtinyDlg::OnBnClickedCheckHeight)
	ON_BN_CLICKED(IDC_BUTTON_ZOOMIN, &CtinyDlg::OnBnClickedButtonZoomin)
	ON_BN_CLICKED(IDC_BUTTON_ZOOMOUT, &CtinyDlg::OnBnClickedButtonZoomout)
	ON_BN_CLICKED(IDC_CHECK_AUTOSCOPE, &CtinyDlg::OnBnClickedCheckAutoscope)
	ON_BN_CLICKED(IDC_CHECK_ACC, &CtinyDlg::OnBnClickedCheckAcc)
	ON_BN_CLICKED(IDC_CHECK_GRY, &CtinyDlg::OnBnClickedCheckGry)
	ON_BN_CLICKED(IDC_CHECK_HM, &CtinyDlg::OnBnClickedCheckHm)
	ON_BN_CLICKED(IDC_CHECK_ANGLE, &CtinyDlg::OnBnClickedCheckAngle)
END_MESSAGE_MAP()


// CtinyDlg 消息处理程序

BOOL CtinyDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtinyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CPropertyPage::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtinyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPropertyPage::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtinyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



bool CtinyDlg::init()
{
	m_showdata = DataShow::GetInstance();

	initCom();
	initSerial();
	initIcon();
	initDataShow();
	initColorTable(ColorTable);
	initLineName();
	initChartCtrl();
	initColorButton();

	UpdateData(FALSE);

	std::thread serial_thread_temp(&CtinyDlg::serialRead, this);
	serial_thread.swap(serial_thread_temp);

	SetTimer(0, 20, NULL);

	return true;
}


bool CtinyDlg::initCom()
{
	initFile();
	m_combo_combaudrate.InsertString(0, _T("4800"));
	m_combo_combaudrate.InsertString(1, _T("9600"));
	m_combo_combaudrate.InsertString(2, _T("115200"));
	m_combo_combaudrate.InsertString(3, _T("230400"));
	detectCom();

	m_static_comstate.SetWindowText(_T("端口已关闭"));

	if (m_combo_comnum.GetCount() == 0)
	{
		return false;
	}

	m_combo_combaudrate.SetCurSel(2);
	m_combo_comnum.SetCurSel(0);

	/*std::fstream _file;
	_file.open(FILENAME, std::ios::in);*/
	
	char ComNum_char[10], ComBaudrate_char[10];
	int res = GetPrivateProfileStringA("sec1", "comnum", "COM12", ComNum_char, sizeof(ComNum_char), FILENAME);
	res = GetPrivateProfileStringA("sec1", "combaudrate", "115200", ComBaudrate_char, sizeof(ComBaudrate_char), FILENAME);

	std::string ComNum_string(ComNum_char);
	std::string ComBaudrate_string(ComBaudrate_char);

	CString temp_cstring;
	for (size_t i = 0; i < m_combo_comnum.GetCount(); i++)
	{
		USES_CONVERSION;
		m_combo_comnum.GetLBText(i, temp_cstring);
		std::string com_str(W2A(temp_cstring));

		if (com_str.compare(ComNum_string) == 0)
		{
			m_combo_comnum.SetCurSel(i);
			break;
		}
	}

	for (size_t i = 0; i < m_combo_combaudrate.GetCount(); i++)
	{
		USES_CONVERSION;
		m_combo_combaudrate.GetLBText(i, temp_cstring);
		std::string combaudrate_str(W2A(temp_cstring));

		if (combaudrate_str.compare(ComBaudrate_string) == 0)
		{
			m_combo_combaudrate.SetCurSel(i);
			break;
		}
	}

	return true;
}


bool CtinyDlg::initDataShow()
{
	m_edit_pid_p_custom = 0;
	m_edit_pid_i_custom = 0;
	m_edit_pid_d_custom = 0;

	m_edit_pid_p_height = 0;
	m_edit_pid_i_height = 0;
	m_edit_pid_d_height = 0;

	m_edit_pid_p_position = 0;
	m_edit_pid_i_position = 0;
	m_edit_pid_d_position = 0;

	m_edit_pid_p_innerlayer = 0;
	m_edit_pid_i_innerlayer = 0;
	m_edit_pid_d_innerlayer = 0;

	m_edit_pid_p_outerlayer = 0;
	m_edit_pid_i_outerlayer = 0;
	m_edit_pid_d_outerlayer = 0;

	m_edit_rockermid1 = 0;
	m_edit_rockermid2 = 0;
	m_edit_rockermid3 = 0;
	m_edit_rockermid4 = 0;
	m_edit_avoidscope = 0;
	m_edit_sensitivity = 0;
	m_edit_exceptheight = 0;

	return true;
}

void CtinyDlg::detectCom()
{
	HANDLE hCom;
	int num = 0;
	int count = 0;
	CString str;
	m_combo_comnum.ResetContent();
	BOOL flag = FALSE;
	for (int i = 1; i <= 16; i++)
	{//此程序支持16个串口
		str.Format(_T("\\\\.\\COM%d"), i);
		hCom = CreateFile(str, 0, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (INVALID_HANDLE_VALUE != hCom)
		{//能打开该串口，则添加该串口
			CloseHandle(hCom);
			str = str.Mid(4);
			m_combo_comnum.InsertString(count, str);
			count++;
			if (flag == FALSE)
			{
				flag = TRUE;
				num = i;
			}
		}
	}

	m_combo_comnum.SetCurSel(0);
}


void CtinyDlg::OnBnClickedButtonOpencom()
{
	// TODO:  在此添加控件通知处理程序代码

	if (m_serial_instance->serial_port.isOpen())
	{
		m_serial_closing = true;
		Sleep(50);
		m_serial_instance->serial_port.close();
		Sleep(50);

		m_btn_opencom.SetWindowText(_T("打开串口"));
		m_static_comstate.SetWindowText(_T("端口已关闭"));
		m_icon_comstate.SetIcon(m_hIcon_com_black);
		m_combo_combaudrate.EnableWindow(TRUE);
		m_combo_comnum.EnableWindow(TRUE);

		return;
	}

	CString temp_cstring;

	int idx = m_combo_combaudrate.GetCurSel();
	m_combo_combaudrate.GetLBText(idx, temp_cstring);
	USES_CONVERSION;
	std::string baud_str(W2A(temp_cstring));

	idx = m_combo_comnum.GetCurSel();
	m_combo_comnum.GetLBText(idx, temp_cstring);
	std::string com_str(W2A(temp_cstring));

	std::stringstream ss;
	ss << baud_str;
	uint32_t baud = 0;
	ss >> baud;
	ss.clear();

	m_serial_instance->serial_port.setPort(com_str.c_str());
	m_serial_instance->serial_port.setBaudrate(baud);
	serial::Timeout serial_timeout = serial::Timeout::simpleTimeout(1000);
	m_serial_instance->serial_port.setTimeout(serial_timeout);

	m_serial_instance->serial_port.open();
	m_serial_closing = false;
	Sleep(100);

	if (m_serial_instance->serial_port.isOpen())
	{
		m_btn_opencom.SetWindowText(_T("关闭串口"));
		m_static_comstate.SetWindowText(_T("端口已打开"));
		m_icon_comstate.SetIcon(m_hIcon_com_green);
		m_combo_combaudrate.EnableWindow(FALSE);
		m_combo_comnum.EnableWindow(FALSE);

		saveCom();

		return;
	}
}


void CtinyDlg::OnBnClickedButtonWriteparam()
{
	// TODO:  在此添加控件通知处理程序代码

	this->writeParam();

}


void CtinyDlg::OnBnClickedButtonReadparam()
{
	// TODO:  在此添加控件通知处理程序代码

	this->readParam();

}


void CtinyDlg::OnBnClickedButtonWriteflash()
{
	// TODO:  在此添加控件通知处理程序代码

	this->writeFlash();

}

#define USE_DEVICECHANGE 0

BOOL CtinyDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
{
#if USE_DEVICECHANGE

	switch (nEventType)
	{
		case DBT_DEVICEREMOVECOMPLETE://移除设备，关闭串口  
		{
			m_serial_instance->serial_port.close();
		}
		break;
		case DBT_DEVICEARRIVAL://添加设备，打开串口  
		{
			detectCom();
		}
		break;
		default:
			break;
	}

#endif // USE_DEVICECHANGE
	return TRUE;
}


void CtinyDlg::serialRead()
{
	size_t data_length = 0;
	unsigned char sum = 0;
	unsigned char RX_Data[COM_DATA_SIZE_MAX] = { 0 };

	int delay_ms = 1;

	while (!isTerminal)
	{
		if (!m_serial_instance->serial_port.isOpen() || (m_serial_closing))
		{
			Sleep(100);
			continue;
		}
		/*g_coodata_x = m_count % 200;
		g_coodata_y = m_count % 300;
		*/
		sum = 0;
		data_length = m_serial_instance->serial_port.available();
		if (data_length)
		{
			unsigned char *data_buf_temp = new unsigned char[data_length];
			m_serial_instance->serial_port.read(data_buf_temp, data_length);

			DataAnl(data_buf_temp, data_length, RX_Data);

			delete data_buf_temp;
		}

		Sleep(delay_ms);
	}
}


void CtinyDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	OnOK();

	CPropertyPage::OnClose();
}


void CtinyDlg::writeParam()
{
	INT_PTR nRes;
	nRes = MessageBox(_T("确认写入吗？"), _T("写入参数"), MB_OKCANCEL | MB_ICONQUESTION);
	if (nRes == IDCANCEL)
	{
		return;
	}

	UpdateData(TRUE);
	m_param.avoid_scope = m_edit_avoidscope;
	m_param.pid_custom.p = m_edit_pid_p_custom;
	m_param.pid_custom.i = m_edit_pid_i_custom;
	m_param.pid_custom.d = m_edit_pid_d_custom;
	m_param.pid_height.p = m_edit_pid_p_height;
	m_param.pid_height.i = m_edit_pid_i_height;
	m_param.pid_height.d = m_edit_pid_d_height;
	m_param.pid_position.p = m_edit_pid_p_position;
	m_param.pid_position.i = m_edit_pid_i_position;
	m_param.pid_position.d = m_edit_pid_d_position;
	m_param.pid_innerlayer.p = m_edit_pid_p_innerlayer;
	m_param.pid_innerlayer.i = m_edit_pid_i_innerlayer;
	m_param.pid_innerlayer.d = m_edit_pid_d_innerlayer;
	m_param.pid_outerlayer.p = m_edit_pid_p_outerlayer;
	m_param.pid_outerlayer.i = m_edit_pid_i_outerlayer;
	m_param.pid_outerlayer.d = m_edit_pid_d_outerlayer;
	m_param.rocker_mid[0] = m_edit_rockermid1;
	m_param.rocker_mid[1] = m_edit_rockermid2;
	m_param.rocker_mid[2] = m_edit_rockermid3;
	m_param.rocker_mid[3] = m_edit_rockermid4;
	m_param.sensitivity = m_edit_sensitivity;
	m_param.excepted_height = m_edit_exceptheight;
	m_param.enable_height = m_check_setheight.GetCheck();
	m_param.enable_avoidObj = m_check_avoidobjection.GetCheck();

	// TODO

	serialSend(PID_1);
	serialSend(PID_2);
	serialSend(PID_1);
	serialSend(PID_2);

	sendCommand(WRITE_PARAM);
	sendCommand(WRITE_PARAM);
	/*if (serialSend(WRITE_PARAM))
	{
	MessageBox(_T("参数已写入！"), _T("提示"));
	}*/
}


void CtinyDlg::readParam()
{
	// TODO
	/*if (!serialSend(READ_PARAM))
	{
	return;
	}
	Sleep(100);*/
	m_edit_pid_p_custom = m_param.pid_custom.p;
	m_edit_pid_i_custom = m_param.pid_custom.i;
	m_edit_pid_d_custom = m_param.pid_custom.d;

	m_edit_pid_p_height = m_param.pid_height.p;
	m_edit_pid_i_height = m_param.pid_height.i;
	m_edit_pid_d_height = m_param.pid_height.d;

	m_edit_pid_p_position = m_param.pid_position.p;
	m_edit_pid_i_position = m_param.pid_position.i;
	m_edit_pid_d_position = m_param.pid_position.d;

	m_edit_pid_p_innerlayer = m_param.pid_innerlayer.p;
	m_edit_pid_i_innerlayer = m_param.pid_innerlayer.i;
	m_edit_pid_d_innerlayer = m_param.pid_innerlayer.d;

	m_edit_pid_p_outerlayer = m_param.pid_outerlayer.p;
	m_edit_pid_i_outerlayer = m_param.pid_outerlayer.i;
	m_edit_pid_d_outerlayer = m_param.pid_outerlayer.d;

	m_edit_rockermid1 = m_param.rocker_mid[0];
	m_edit_rockermid2 = m_param.rocker_mid[1];
	m_edit_rockermid3 = m_param.rocker_mid[2];
	m_edit_rockermid4 = m_param.rocker_mid[3];
	m_edit_exceptheight = m_param.excepted_height;
	m_edit_avoidscope = m_param.avoid_scope;
	m_edit_sensitivity = m_param.sensitivity;

	m_check_setheight.SetCheck(m_param.enable_height);
	m_check_avoidobjection.SetCheck(m_param.enable_avoidObj);

	UpdateData(FALSE);

}


void CtinyDlg::writeFlash()
{
	// TODO
	if (serialSend(WRITE_FLASH))
	{
		MessageBox(_T("参数已写入！"), _T("提示"));
	}
}


void CtinyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	UpdateDataShow();

	UpdateChartCtrlData();

	if (!m_serial_instance->serial_port.isOpen())
	{
		return;
	}
	sendCommand(HEART_BEAT);

	CPropertyPage::OnTimer(nIDEvent);
}


void CtinyDlg::UpdateDataShow()
{
	CStringW cstr_temp;

	cstr_temp.Format(_T("%d"), m_showdata->pwm[0]);
	GetDlgItem(IDC_DATASHOW_PWM1)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->pwm[1]);
	GetDlgItem(IDC_DATASHOW_PWM2)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->pwm[2]);
	GetDlgItem(IDC_DATASHOW_PWM3)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->pwm[3]);
	GetDlgItem(IDC_DATASHOW_PWM4)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->pwm[4]);
	GetDlgItem(IDC_DATASHOW_PWM5)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->control[0]);
	GetDlgItem(IDC_DATASHOW_CONTROL1)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->control[1]);
	GetDlgItem(IDC_DATASHOW_CONTROL2)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->control[2]);
	GetDlgItem(IDC_DATASHOW_CONTROL3)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->control[3]);
	GetDlgItem(IDC_DATASHOW_CONTROL4)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%.2f"), m_showdata->fusion_data);
	GetDlgItem(IDC_DATASHOW_RADAEFUSIONDATA)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%.2f"), m_showdata->height);
	GetDlgItem(IDC_DATASHOW_EXPECTEDHEIGHT)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->sensor.acc_x);
	GetDlgItem(IDC_DATASHOW_ACCX)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->sensor.acc_y);
	GetDlgItem(IDC_DATASHOW_ACCY)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->sensor.acc_z);
	GetDlgItem(IDC_DATASHOW_ACCZ)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->sensor.gry_x);
	GetDlgItem(IDC_DATASHOW_GRYX)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->sensor.gry_y);
	GetDlgItem(IDC_DATASHOW_GRYY)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->sensor.gry_z);
	GetDlgItem(IDC_DATASHOW_GRYZ)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->sensor.hm_x);
	GetDlgItem(IDC_DATASHOW_HMX)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->sensor.hm_y);
	GetDlgItem(IDC_DATASHOW_HMY)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->sensor.hm_z);
	GetDlgItem(IDC_DATASHOW_HMZ)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Pitch);
	GetDlgItem(IDC_DATASHOW_ANGLE_PITCH)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Roll);
	GetDlgItem(IDC_DATASHOW_ANGLE_ROLL)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_showdata->angle.Yaw);
	GetDlgItem(IDC_DATASHOW_ANGLE_YAW)->SetWindowText(cstr_temp);

	m_icon_state.SetIcon(m_hIcon_indicator_red);
}


void CtinyDlg::initIcon()
{
	m_hIcon_indicator_black = AfxGetApp()->LoadIcon(IDI_ICON_INDICATOR_BLACK);
	m_hIcon_indicator_green = AfxGetApp()->LoadIcon(IDI_ICON_INDICATOR_GREEN);
	m_hIcon_indicator_yellow = AfxGetApp()->LoadIcon(IDI_ICON_INDICATOR_YELLOW);
	m_hIcon_indicator_red = AfxGetApp()->LoadIcon(IDI_ICON_INDICATOR_RED);
	m_hIcon_com_green = AfxGetApp()->LoadIcon(IDI_ICON_COM_GREEN);
	m_hIcon_com_black = AfxGetApp()->LoadIcon(IDI_ICON_COM_BLACK);
	m_hIcon_zoom_in = AfxGetApp()->LoadIcon(IDI_ICON_ZOOMIN);
	m_hIcon_zoom_out = AfxGetApp()->LoadIcon(IDI_ICON_ZOOMOUT);

	m_icon_comstate.SetIcon(m_hIcon_com_black);
	m_icon_state.SetIcon(m_hIcon_indicator_black);

	((CButton *)GetDlgItem(IDC_BUTTON_ZOOMIN))->SetIcon(m_hIcon_zoom_in);
	((CButton *)GetDlgItem(IDC_BUTTON_ZOOMOUT))->SetIcon(m_hIcon_zoom_out);
}


bool CtinyDlg::serialSend(SerialSendOrder sendOrder)
{
	if (!m_serial_instance->serial_port.isOpen())
	{
		MessageBox(_T("    串口未打开!"), _T("提示"));
		return false;
	}

	int _cnt = 0, i = 0, sum = 0;
	unsigned char data_to_send[50];

	data_to_send[_cnt++] = 0xAA;
	data_to_send[_cnt++] = 0xAF;

	switch (sendOrder)
	{
		case CtinyDlg::WRITE_PARAM:
		{
			
			break;
		}

		case CtinyDlg::READ_PARAM:
		{
			
			break;
		}

		case CtinyDlg::WRITE_FLASH:
		{
	
			break;
		}

		case CtinyDlg::READ_DATA:
		{
		
			break;
		}

		case CtinyDlg::HEART_BEAT:
		{
			break;
		}

		case CtinyDlg::PID_1:
		{
			data_to_send[2] = (byte)0x10;
			data_to_send[3] = (byte)18;
			data_to_send[4] = (byte)(m_param.pid_outerlayer.p / 256);
			data_to_send[5] = (byte)(m_param.pid_outerlayer.p % 256);
			data_to_send[6] = (byte)(m_param.pid_outerlayer.i / 256);
			data_to_send[7] = (byte)(m_param.pid_outerlayer.i % 256);
			data_to_send[8] = (byte)(m_param.pid_outerlayer.d / 256);
			data_to_send[9] = (byte)(m_param.pid_outerlayer.d % 256);

			data_to_send[10] = (byte)(m_param.pid_innerlayer.p / 256);
			data_to_send[11] = (byte)(m_param.pid_innerlayer.p % 256);
			data_to_send[12] = (byte)(m_param.pid_innerlayer.i / 256);
			data_to_send[13] = (byte)(m_param.pid_innerlayer.i % 256);
			data_to_send[14] = (byte)(m_param.pid_innerlayer.d / 256);
			data_to_send[15] = (byte)(m_param.pid_innerlayer.d % 256);

			data_to_send[16] = (byte)(m_param.pid_custom.p / 256);
			data_to_send[17] = (byte)(m_param.pid_custom.p % 256);
			data_to_send[18] = (byte)(m_param.pid_custom.i / 256);
			data_to_send[19] = (byte)(m_param.pid_custom.i % 256);
			data_to_send[20] = (byte)(m_param.pid_custom.d / 256);
			data_to_send[21] = (byte)(m_param.pid_custom.d % 256);

			for (int i = 0; i < 22; i++) 
				sum += data_to_send[i];
			data_to_send[22] = sum;

			m_serial_instance->serial_port.write(data_to_send, 23);
			break;
		}

		case CtinyDlg::PID_2:
		{
			data_to_send[2] = (byte)0x11;
			data_to_send[3] = (byte)18;
			data_to_send[4] = (byte)(m_param.pid_height.p / 256);
			data_to_send[5] = (byte)(m_param.pid_height.p % 256);
			data_to_send[6] = (byte)(m_param.pid_height.i / 256);
			data_to_send[7] = (byte)(m_param.pid_height.i % 256);
			data_to_send[8] = (byte)(m_param.pid_height.d / 256);
			data_to_send[9] = (byte)(m_param.pid_height.d % 256);

			for (int i = 0; i < 22; i++) 
				sum += data_to_send[i];
			data_to_send[22] = sum;

			m_serial_instance->serial_port.write(data_to_send, 23);
			break;
		}

		default:
			break;
	}

	//data_to_send[3] = _cnt - 4;

	return true;
}


bool CtinyDlg::initChartCtrl()
{
	m_count = 0;
	m_chartctrl.SetBackColor(RGB(0, 0, 0));

	m_pChartStandarAxisY = m_chartctrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	m_pChartStandarAxisX = m_chartctrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	m_pChartStandarAxisX->SetAutomatic(false);
	m_pChartStandarAxisY->SetAutomatic(false);
	m_pChartStandarAxisX->SetAxisColor(RGB(255, 255, 255));
	m_pChartStandarAxisY->SetAxisColor(RGB(255, 255, 255));
	m_pChartStandarAxisX->SetTextColor(RGB(255, 255, 255));
	m_pChartStandarAxisY->SetTextColor(RGB(255, 255, 255));
	//m_pChartStandarAxisX->SetTextColor(m_chartctrl.GetBackColor());

	ChartCtrlData m_chartctrldata;
	for (size_t i = 0; i < SHOW_DATA_SIZE; i++)
	{
		m_count++;
		m_chartctrldata.x.push_back(m_count);
		m_chartctrldata.y.push_back(sin((double)m_chartctrldata.x[i] * 3.1415926 / 100));
	}

	m_chartctrl.EnableRefresh(false);
	m_chartctrl.RemoveAllSeries();
	m_pChartStandarAxisX->SetMinMax(m_count - SHOW_DATA_SIZE, m_count + SHOW_DATA_SIZE_MARGIN);
	m_pChartStandarAxisY->SetMinMax(-1 * m_scope_y, m_scope_y);

	m_chartctrl.GetLegend()->SetVisible(true);
	m_chartctrl.GetLegend()->EnableShadow(false);

	for (size_t i = DataName::ACC_X; i < DataName::END; i++)
	{
		m_pChartLineSerie.push_back(m_chartctrl.CreateLineSerie());
		m_pChartLineSerie[i]->SetName(LineName[i]);
		m_pChartLineSerie[i]->SetWidth(2);
		m_pChartLineSerie[i]->SetColor(ColorTable[i]);
		m_pChartLineSerie[i]->AddPoints(m_chartctrldata.x.data(), m_chartctrldata.y.data(), SHOW_DATA_SIZE);
		m_pChartLineSerie[i]->SetVisible(false);
	}

	m_pChartLineSerie[DataName::ANGLE_PITCH]->SetVisible(true);
	m_pChartLineSerie[DataName::ANGLE_ROLL]->SetVisible(true);
	m_pChartLineSerie[DataName::ANGLE_YAW]->SetVisible(true);

	m_check_angle.SetCheck(1);

	m_chartctrl.EnableRefresh(true);

	return true;
}


void CtinyDlg::UpdateChartCtrlData()
{
	m_count++;

	m_chartctrl.EnableRefresh(false);

	m_pChartLineSerie[DataName::ACC_X]->AddPoint(m_count, m_showdata->sensor.acc_x);
	m_pChartLineSerie[DataName::ACC_Y]->AddPoint(m_count, m_showdata->sensor.acc_y);
	m_pChartLineSerie[DataName::ACC_Z]->AddPoint(m_count, m_showdata->sensor.acc_z);
	m_pChartLineSerie[DataName::GRY_X]->AddPoint(m_count, m_showdata->sensor.gry_x);
	m_pChartLineSerie[DataName::GRY_Y]->AddPoint(m_count, m_showdata->sensor.gry_y);
	m_pChartLineSerie[DataName::GRY_Z]->AddPoint(m_count, m_showdata->sensor.gry_z);
	m_pChartLineSerie[DataName::HM_X]->AddPoint(m_count, m_showdata->sensor.hm_x);
	m_pChartLineSerie[DataName::HM_Y]->AddPoint(m_count, m_showdata->sensor.hm_y);
	m_pChartLineSerie[DataName::HM_Z]->AddPoint(m_count, m_showdata->sensor.hm_z);
	m_pChartLineSerie[DataName::FUSIONDATA]->AddPoint(m_count, m_showdata->fusion_data);
	m_pChartLineSerie[DataName::HEIGHT]->AddPoint(m_count, m_showdata->height);
	m_pChartLineSerie[DataName::ANGLE_PITCH]->AddPoint(m_count, m_showdata->angle.Pitch);
	m_pChartLineSerie[DataName::ANGLE_ROLL]->AddPoint(m_count, m_showdata->angle.Roll);
	m_pChartLineSerie[DataName::ANGLE_YAW]->AddPoint(m_count, m_showdata->angle.Yaw);


	for (size_t i = DataName::ACC_X; i < DataName::END; i++)
	{
		m_pChartLineSerie[i]->RemovePointsFromBegin(1);
	}

	m_pChartStandarAxisX->SetMinMax(m_count - SHOW_DATA_SIZE, m_count + SHOW_DATA_SIZE_MARGIN);

	m_chartctrl.EnableRefresh(true);
}


bool CtinyDlg::initColorButton()
{
	m_btn_color_fusiondata.Color = RGB(0, 255, 0);
	m_btn_color_fusiondata.DefaultColor = RGB(0, 255, 0);
	m_btn_color_fusiondata.TrackSelection = TRUE;
	m_btn_color_fusiondata.CustomText = _T("更多颜色...");
	m_btn_color_fusiondata.DefaultText = _T("自动");

	m_btn_color_height.Color = RGB(255, 0, 0);
	m_btn_color_height.DefaultColor = RGB(255, 0, 0);
	m_btn_color_height.TrackSelection = TRUE;
	m_btn_color_height.CustomText = _T("更多颜色...");
	m_btn_color_height.DefaultText = _T("自动");

	m_color = m_btn_color_fusiondata.GetColor();

	return true;
}

LONG CtinyDlg::OnSelEndOK(UINT lParam, LONG /*wParam*/)
{
	TRACE0("Selection ended OK\n");

	m_pChartLineSerie[DataName::HEIGHT]->SetColor(m_btn_color_height.GetColor());
	m_pChartLineSerie[DataName::FUSIONDATA]->SetColor(m_btn_color_fusiondata.GetColor());

	return TRUE;
}

LONG CtinyDlg::OnSelEndCancel(UINT /*lParam*/, LONG /*wParam*/)
{
	TRACE0("Selection cancelled\n");
	return TRUE;
}

LONG CtinyDlg::OnSelChange(UINT /*lParam*/, LONG /*wParam*/)
{
	TRACE0("Selection changed\n");
	return TRUE;
}

LONG CtinyDlg::OnCloseUp(UINT /*lParam*/, LONG /*wParam*/)
{
	TRACE0("Colour picker close up\n");
	return TRUE;
}

LONG CtinyDlg::OnDropDown(UINT /*lParam*/, LONG /*wParam*/)
{
	TRACE0("Colour picker drop down\n");
	return TRUE;
}


void CtinyDlg::OnBnClickedCheckFusiondata()
{
	// TODO:  在此添加控件通知处理程序代码
	int state = m_check_fusiondata.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[DataName::FUSIONDATA]->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie[DataName::FUSIONDATA]->SetVisible(true);
	}

}


void CtinyDlg::OnBnClickedCheckHeight()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_height.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[DataName::HEIGHT]->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie[DataName::HEIGHT]->SetVisible(true);
	}
}


void CtinyDlg::OnBnClickedButtonZoomout()
{
	// TODO:  在此添加控件通知处理程序代码

	m_scope_y *= 2;
	m_pChartStandarAxisY->SetMinMax(-1 * m_scope_y, m_scope_y);

}


void CtinyDlg::OnBnClickedButtonZoomin()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_scope_y > 2)
	{
		m_scope_y /= 2;
		m_pChartStandarAxisY->SetMinMax(-1 * m_scope_y, m_scope_y);
	}

}

void CtinyDlg::sendCommand(SerialSendOrder serialOrder)
{
	if (!m_serial_instance->serial_port.isOpen())
	{
		MessageBox(_T("    串口未打开!"), _T("提示"));
		return;
	}

	int _cnt = 0, i = 0, sum = 0;
	unsigned char data_to_send[50];

	data_to_send[_cnt++] = 0xAA;
	data_to_send[_cnt++] = 0xAF;

	switch (serialOrder)
	{
		case CtinyDlg::WRITE_PARAM:
		{
			data_to_send[_cnt++] = 0x01;
			data_to_send[_cnt++] = 0x01;
			data_to_send[_cnt++] = 0xA3;
			data_to_send[_cnt++] = 0xA3;

			for (i = 0; i < 5; i++)
				sum += data_to_send[i];
			data_to_send[5] = sum;

			break;
		}

		case CtinyDlg::READ_PARAM:
		{

			break;
		}

		case CtinyDlg::WRITE_FLASH:
		{


			break;
		}

		case CtinyDlg::READ_DATA:
		{
			data_to_send[_cnt++] = 0x03;
			data_to_send[_cnt++] = 0;

			for (i = 0; i < _cnt; i++)
				sum += data_to_send[i];
			data_to_send[_cnt++] = sum;

			break;
		}

		case CtinyDlg::HEART_BEAT:
		{
			data_to_send[_cnt++] = 0x01;
			data_to_send[_cnt++] = 0x01;
			data_to_send[_cnt++] = 0xff;
			data_to_send[_cnt++] = 0xff;

			for (i = 0; i < 5; i++)
				sum += data_to_send[i];
			data_to_send[5] = sum;

			break;
		}

		default:
			break;
	}

	//data_to_send[3] = _cnt - 4;

	m_serial_instance->serial_port.write(data_to_send, _cnt);
}

void CtinyDlg::DataAnl(unsigned char* data_buf_temp, int len, unsigned char* RX_Data)
{
	int rxstate = 0;
	int rxlen = 0;
	int rxcnt = 0;

	for (int i = 0; i < len; i++)
	{
		if (rxstate == 0)
		{
			if (data_buf_temp[i] == (byte)0xaa)
			{
				rxstate = 1;
				RX_Data[0] = (byte)0xaa;
			}
		}
		else if (rxstate == 1)
		{
			if (data_buf_temp[i] == (byte)0xaa)
			{
				rxstate = 2;
				RX_Data[1] = (byte)0xaa;
			}
			else
				rxstate = 0;
		}
		else if (rxstate == 2)
		{
			rxstate = 3;
			RX_Data[2] = data_buf_temp[i];
		}
		else if (rxstate == 3)
		{
			if (data_buf_temp[i] > 45)
				rxstate = 0;
			else
			{
				rxstate = 4;
				RX_Data[3] = data_buf_temp[i];
				rxlen = RX_Data[3];
				if (rxlen < 0)
					rxlen = -rxlen;
				rxcnt = 4;
			}
		}
		else if (rxstate == 4)
		{
			rxlen--;
			RX_Data[rxcnt] = data_buf_temp[i];
			rxcnt++;
			if (rxlen <= 0)
				rxstate = 5;
		}
		else if (rxstate == 5)
		{
			RX_Data[rxcnt] = data_buf_temp[i];
			if (rxcnt <= (COM_DATA_SIZE_MAX - 1))
			{
				FrameAnl(RX_Data, rxcnt + 1);
			}
			rxstate = 0;
		}
	}
}

void CtinyDlg::FrameAnl(unsigned char* RX_Data, int len)
{
	static char init;
	static float offx, offy;
	unsigned char sum = 0;
	for (int i = 0; i < (len - 1); i++)
	{
		sum += *(RX_Data + i);
	}

	if (sum == *(RX_Data + len - 1))
	{
		switch (RX_Data[2])
		{
			case 1://status
			{
				m_showdata->angle.Roll = ((float)(BytetoUint(RX_Data, 4))) / 100;
				m_showdata->angle.Pitch = ((float)(BytetoUint(RX_Data, 6))) / 100;
				m_showdata->angle.Yaw = ((float)(BytetoUint(RX_Data, 8))) / 100;

				m_showdata->coodinate.id = BytetoUint(RX_Data, 17);
				m_showdata->coodinate.x = ((float)BytetoUint(RX_Data, 19)) / 10 - offx*0;
				m_showdata->coodinate.y = ((float)BytetoUint(RX_Data, 21)) / 10- offy*0;
				m_showdata->coodinate.z = ((float)BytetoUint(RX_Data, 23)) / 10 - offx * 0;
				m_showdata->hopecoor.x = ((float)BytetoUint(RX_Data, 25)) / 10 - offy * 0;
				m_showdata->hopecoor.y = ((float)BytetoUint(RX_Data, 27)) / 10 - offy * 0;
				m_showdata->hopecoor.z = ((float)BytetoUint(RX_Data, 29)) / 10 - offy * 0;
				m_showdata->originalQR.x = ((float)BytetoUint(RX_Data, 31)) / 10 - offy * 0;
				m_showdata->originalQR.y = ((float)BytetoUint(RX_Data, 33)) / 10 - offy * 0;
				m_showdata->originalQR.z = ((float)BytetoUint(RX_Data, 35)) / 10 - offy * 0;
				m_showdata->obstacle = (bool)(RX_Data[37]);
				if (!init)
				{
					init = 1;
					offx = m_showdata->coodinate.x;
					offy = m_showdata->coodinate.y;
				}
				break;
			}
			case 2://senser
			{
				m_showdata->sensor.acc_x = BytetoUint(RX_Data, 4);
				m_showdata->sensor.acc_y = BytetoUint(RX_Data, 6);
				m_showdata->sensor.acc_z = BytetoUint(RX_Data, 8);
				m_showdata->sensor.gry_x = BytetoUint(RX_Data, 10);
				m_showdata->sensor.gry_y = BytetoUint(RX_Data, 12);
				m_showdata->sensor.gry_z = BytetoUint(RX_Data, 14);
				break;
			}
			case 3:
			{

				break;
			}
			case 4://GPS
			{
				m_showdata->gps.latitude = ((double)Bytetoint(RX_Data, 4)) / 10000000;
				m_showdata->gps.longitude = ((double)Bytetoint(RX_Data, 8)) / 10000000;
				m_showdata->gps.elevation = ((float)Bytetoint(RX_Data, 12)) / 100;
				m_showdata->height = m_showdata->gps.elevation;
				break;
			}
			case 5://votage
			{

				break;
			}
			case 6://pid1
			{
				m_param.pid_outerlayer.p = BytetoUint(RX_Data, 4);
				m_param.pid_outerlayer.i = BytetoUint(RX_Data, 6);
				m_param.pid_outerlayer.d = BytetoUint(RX_Data, 8);
				m_param.pid_innerlayer.p = BytetoUint(RX_Data, 10);
				m_param.pid_innerlayer.i = BytetoUint(RX_Data, 12);
				m_param.pid_innerlayer.d = BytetoUint(RX_Data, 14);
				m_param.pid_custom.p = BytetoUint(RX_Data, 16);
				m_param.pid_custom.i = BytetoUint(RX_Data, 18);
				m_param.pid_custom.d = BytetoUint(RX_Data, 20);
				break;
			}
			case 7://pid2
			{

				break;
			}
			case 8://sensor
			{
				m_showdata->sensor.acc_x = BytetoUint(RX_Data, 4);
				m_showdata->sensor.acc_y = BytetoUint(RX_Data, 6);
				m_showdata->sensor.acc_z = BytetoUint(RX_Data, 8);
				m_showdata->sensor.gry_x = BytetoUint(RX_Data, 10);
				m_showdata->sensor.gry_y = BytetoUint(RX_Data, 12);
				m_showdata->sensor.gry_z = BytetoUint(RX_Data, 14);
				break;
			}
			default:
				break;
		}
	}

}


void CtinyDlg::OnBnClickedCheckAutoscope()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_autoscope.GetCheck();

	if (state == 0)
	{
		double maxval = 0;
		double minval = 0;
		m_pChartStandarAxisY->GetMinMax(minval, maxval);
		m_scope_y = int(fabs(maxval) > fabs(minval) ? fabs(maxval) : fabs(minval));

		m_pChartStandarAxisY->SetAutomatic(false);

		m_pChartStandarAxisY->SetMinMax(-1 * m_scope_y, m_scope_y);
	}
	else
	{
		m_pChartStandarAxisY->SetAutomatic(true);
	}
}


void CtinyDlg::OnBnClickedCheckAcc()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_acc.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[DataName::ACC_X]->SetVisible(false);
		m_pChartLineSerie[DataName::ACC_Y]->SetVisible(false);
		m_pChartLineSerie[DataName::ACC_Z]->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie[DataName::ACC_X]->SetVisible(true);
		m_pChartLineSerie[DataName::ACC_Y]->SetVisible(true);
		m_pChartLineSerie[DataName::ACC_Z]->SetVisible(true);
	}
}


void CtinyDlg::OnBnClickedCheckGry()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_gry.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[DataName::GRY_X]->SetVisible(false);
		m_pChartLineSerie[DataName::GRY_Y]->SetVisible(false);
		m_pChartLineSerie[DataName::GRY_Z]->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie[DataName::GRY_X]->SetVisible(true);
		m_pChartLineSerie[DataName::GRY_Y]->SetVisible(true);
		m_pChartLineSerie[DataName::GRY_Z]->SetVisible(true);
	}
}


void CtinyDlg::OnBnClickedCheckHm()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_hm.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[DataName::HM_X]->SetVisible(false);
		m_pChartLineSerie[DataName::HM_Y]->SetVisible(false);
		m_pChartLineSerie[DataName::HM_Z]->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie[DataName::HM_X]->SetVisible(true);
		m_pChartLineSerie[DataName::HM_Y]->SetVisible(true);
		m_pChartLineSerie[DataName::HM_Z]->SetVisible(true);
	}
}

bool CtinyDlg::initFile()
{
	std::fstream _file;
	_file.open(FILENAME, std::ios::in);
	if (!_file)
	{
		_file.close();
		_file.open(FILENAME, std::ios::out);
		_file << "[sec1]" << std::endl;
		_file << "comnum=" << "COM1" << std::endl;
		_file << "combaudrate=" << "115200" << std::endl;
		_file.close();
	}

	return true;
}

bool CtinyDlg::initSerial()
{
	m_serial_instance = SerialSingleton::GetInstance();
	m_serial_instance->serial_port;
	return true;
}


bool CtinyDlg::initLineName()
{
	LineName.push_back(_T("AX"));
	LineName.push_back(_T("AY"));
	LineName.push_back(_T("AZ"));
	LineName.push_back(_T("GX"));
	LineName.push_back(_T("GY"));
	LineName.push_back(_T("GZ"));
	LineName.push_back(_T("HX"));
	LineName.push_back(_T("HY"));
	LineName.push_back(_T("HZ"));
	LineName.push_back(_T("Pit"));
	LineName.push_back(_T("Rol"));
	LineName.push_back(_T("Yaw"));
	LineName.push_back(_T("FD"));
	LineName.push_back(_T("Hei"));

	return true;
}

void CtinyDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	isTerminal = true;
	serial_thread.join();

	if (m_serial_instance)
	{
		if (m_serial_instance->serial_port.isOpen())
		{
			m_serial_instance->serial_port.close();
			Sleep(30);
		}
	}
	
	CPropertyPage::OnOK();
}


void CtinyDlg::OnBnClickedCheckAngle()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_angle.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie[DataName::ANGLE_PITCH]->SetVisible(false);
		m_pChartLineSerie[DataName::ANGLE_ROLL]->SetVisible(false);
		m_pChartLineSerie[DataName::ANGLE_YAW]->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie[DataName::ANGLE_PITCH]->SetVisible(true);
		m_pChartLineSerie[DataName::ANGLE_ROLL]->SetVisible(true);
		m_pChartLineSerie[DataName::ANGLE_YAW]->SetVisible(true);
	}
}

void CtinyDlg::saveCom()
{
	std::fstream _file;
	_file.open(FILENAME, std::ios::out);
	if (_file)
	{
		_file << "[sec1]" << std::endl;
		_file << "comnum=" << m_serial_instance->serial_port.getPort() << std::endl;
		_file << "combaudrate=" << m_serial_instance->serial_port.getBaudrate() << std::endl;
		_file.close();
	}
	
}
