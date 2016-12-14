
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

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtinyDlg 对话框



CtinyDlg::CtinyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtinyDlg::IDD, pParent)
	, isTerminal(false)
	, m_serial_closing(false)
	, m_scope_y(1)
	, m_datashow_acc_x(0)
	, m_datashow_acc_y(0)
	, m_datashow_acc_z(0)
	, m_datashow_gry_x(0)
	, m_datashow_gry_y(0)
	, m_datashow_gry_z(0)
	, m_datashow_hm_x(0)
	, m_datashow_hm_y(0)
	, m_datashow_hm_z(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtinyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMBAUDRATE, m_combo_combaudrate);
	DDX_Control(pDX, IDC_COMBO_COMNUM, m_combo_comnum);
	DDX_Control(pDX, IDC_BUTTON_OPENCOM, m_btn_opencom);
	DDX_Control(pDX, IDC_BUTTON_WRITEPARAM, m_btn_writeparam);
	DDX_Control(pDX, IDC_BUTTON_READPARAM, m_btn_readparam);
	DDX_Control(pDX, IDC_BUTTON_WRITEFLASH, m_btn_writeflash);
	DDX_Control(pDX, IDC_STATIC_COMSTATE, m_static_comstate);
	DDX_Control(pDX, IDC_ENABLE_SETHEIGHT, m_check_setheight);
	DDX_Control(pDX, IDC_ENABLE_AVOIDOBJECTION, m_check_avoidobjection);

	DDX_Text(pDX, IDC_DATASHOW_PWM1, m_datashow_pwm1);
	DDX_Text(pDX, IDC_DATASHOW_PWM2, m_datashow_pwm2);
	DDX_Text(pDX, IDC_DATASHOW_PWM3, m_datashow_pwm3);
	DDX_Text(pDX, IDC_DATASHOW_PWM4, m_datashow_pwm4);
	DDX_Text(pDX, IDC_DATASHOW_PWM5, m_datashow_pwm5);
	DDX_Text(pDX, IDC_DATASHOW_CONTROL1, m_datashow_control1);
	DDX_Text(pDX, IDC_DATASHOW_CONTROL2, m_datashow_control2);
	DDX_Text(pDX, IDC_DATASHOW_CONTROL3, m_datashow_control3);
	DDX_Text(pDX, IDC_DATASHOW_CONTROL4, m_datashow_control4);
	DDX_Text(pDX, IDC_DATASHOW_RADAEFUSIONDATA, m_datashow_fusiondata);
	DDX_Text(pDX, IDC_DATASHOW_EXPECTEDHEIGHT, m_datashow_height);

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
	DDX_Text(pDX, IDC_DATASHOW_ACCX, m_datashow_acc_x);
	DDX_Text(pDX, IDC_DATASHOW_ACCY, m_datashow_acc_y);
	DDX_Text(pDX, IDC_DATASHOW_ACCZ, m_datashow_acc_z);
	DDX_Text(pDX, IDC_DATASHOW_GRYX, m_datashow_gry_x);
	DDX_Text(pDX, IDC_DATASHOW_GRYY, m_datashow_gry_y);
	DDX_Text(pDX, IDC_DATASHOW_GRYZ, m_datashow_gry_z);
	DDX_Text(pDX, IDC_DATASHOW_HMX, m_datashow_hm_x);
	DDX_Text(pDX, IDC_DATASHOW_HMY, m_datashow_hm_y);
	DDX_Text(pDX, IDC_DATASHOW_HMZ, m_datashow_hm_z);
	DDX_Control(pDX, IDC_CHECK_AUTOSCOPE, m_check_autoscope);
}

BEGIN_MESSAGE_MAP(CtinyDlg, CDialogEx)
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
END_MESSAGE_MAP()


// CtinyDlg 消息处理程序

BOOL CtinyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
		CDialogEx::OnSysCommand(nID, lParam);
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
		CDialogEx::OnPaint();
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
	initCom();
	initIcon();
	initDataShow();
	initChartCtrl();
	initColorButton();

	UpdateData(FALSE);

	std::thread serial_thread_temp(&CtinyDlg::serialRead, this);
	serial_thread.swap(serial_thread_temp);

	SetTimer(0, 10, NULL);

	return true;
}


bool CtinyDlg::initCom()
{
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

	return true;
}


bool CtinyDlg::initDataShow()
{
	m_datashow_pwm1 = 0;
	m_datashow_pwm2 = 0;
	m_datashow_pwm3 = 0;
	m_datashow_pwm4 = 0;
	m_datashow_pwm5 = 0;
	m_datashow_control1 = 0;
	m_datashow_control2 = 0;
	m_datashow_control3 = 0;
	m_datashow_control4 = 0;
	m_datashow_height = 0;
	m_datashow_fusiondata = 0;

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

	if (m_serialport.isOpen())
	{
		m_serial_closing = true;
		Sleep(50);
		m_serialport.close();
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

	m_serialport.setPort(com_str.c_str());
	m_serialport.setBaudrate(baud);
	serial::Timeout serial_timeout = serial::Timeout::simpleTimeout(1000);
	m_serialport.setTimeout(serial_timeout);

	m_serialport.open();
	m_serial_closing = false;
	Sleep(100);

	if (m_serialport.isOpen())
	{
		m_btn_opencom.SetWindowText(_T("关闭串口"));
		m_static_comstate.SetWindowText(_T("端口已打开"));
		m_icon_comstate.SetIcon(m_hIcon_com_green);
		m_combo_combaudrate.EnableWindow(FALSE);
		m_combo_comnum.EnableWindow(FALSE);
		
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
			m_serialport.close();
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
	unsigned char RX_Data[DATA_SIZE_MAX] = { 0 };
	int16_t temp = 0;
	int delay_ms = 1;

	while (!isTerminal)
	{
		if (!m_serialport.isOpen()||(m_serial_closing))
		{
			Sleep(100);
			continue;
		}
		sum = 0;
		data_length = m_serialport.available();
		if (data_length)
		{
			unsigned char *data_buf_temp = new unsigned char[data_length];
			m_serialport.read(data_buf_temp, data_length);

			DataAnl(data_buf_temp, data_length, RX_Data);
			delete data_buf_temp;
		}
		
		/*if (data_length>DATA_SIZE_MAX)
		{
			unsigned char *data_buf_temp = new unsigned char[data_length];
			m_serialport.read(data_buf_temp, data_length);
			delete data_buf_temp;
			continue;
		}*/
		//if (data_length)
		//{
			
			/*if (*(data_buf + 2) == 0x03)
			{
				temp = data_buf[4];
				temp <<= 8;
				temp |= data_buf[5];
				m_showdata.pwm[0] = temp;

				temp = data_buf[6];
				temp <<= 8;
				temp |= data_buf[7];
				m_showdata.pwm[1] = temp;

				temp = data_buf[8];
				temp <<= 8;
				temp |= data_buf[9];
				m_showdata.pwm[2] = temp;

				temp = data_buf[10];
				temp <<= 8;
				temp |= data_buf[11];
				m_showdata.pwm[3] = temp;

				temp = data_buf[12];
				temp <<= 8;
				temp |= data_buf[13];
				m_showdata.pwm[4] = temp;

				temp = data_buf[14];
				temp <<= 8;
				temp |= data_buf[15];
				m_showdata.control[0] = temp;

				temp = data_buf[16];
				temp <<= 8;
				temp |= data_buf[17];
				m_showdata.control[1] = temp;

				temp = data_buf[18];
				temp <<= 8;
				temp |= data_buf[19];
				m_showdata.control[2] = temp;

				temp = data_buf[20];
				temp <<= 8;
				temp |= data_buf[21];
				m_showdata.control[3] = temp;

				temp = data_buf[22];
				temp <<= 8;
				temp |= data_buf[23];
				m_showdata.radar_fusion = temp;

				temp = data_buf[24];
				temp <<= 8;
				temp |= data_buf[25];
				m_showdata.excepted_height = temp;

				temp = data_buf[26];
				m_showdata.state = uint8_t(temp);
				
			}
			else if (*(data_buf + 2) == 0x01)
			{
				temp = data_buf[4];
				temp <<= 8;
				temp |= data_buf[5];
				m_param.pid_custom.p = temp;

				temp = data_buf[6];
				temp <<= 8;
				temp |= data_buf[7];
				m_param.pid_custom.i = temp;

				temp = data_buf[8];
				temp <<= 8;
				temp |= data_buf[9];
				m_param.pid_custom.d = temp;

				temp = data_buf[10];
				temp <<= 8;
				temp |= data_buf[11];
				m_param.excepted_height = (float)temp / 1000;

				temp = data_buf[12];
				temp <<= 8;
				temp |= data_buf[13];
				m_param.avoid_scope = (float)temp / 1000;

				temp = data_buf[14];
				temp <<= 8;
				temp |= data_buf[15];
				m_param.sensitivity = (float)temp / 1000;

				temp = data_buf[16];
				m_param.enable_height = temp;

				temp = data_buf[17];
				m_param.enable_avoidObj = temp;

				temp = data_buf[18];
				temp <<= 8;
				temp |= data_buf[19];
				m_param.rocker_mid[0] = temp;

				temp = data_buf[20];
				temp <<= 8;
				temp |= data_buf[21];
				m_param.rocker_mid[1] = temp;

				temp = data_buf[22];
				temp <<= 8;
				temp |= data_buf[23];
				m_param.rocker_mid[2] = temp;

				temp = data_buf[24];
				temp <<= 8;
				temp |= data_buf[25];
				m_param.rocker_mid[3] = temp;
			}*/
		//}
		
		//Sleep(delay_ms);
	}
}


void CtinyDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_serialport.isOpen())
	{
		m_serialport.close();
	}
	isTerminal = true;
	serial_thread.join();

	CDialogEx::OnClose();
}


void CtinyDlg::writeParam()
{
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
	if (serialSend(WRITE_PARAM))
	{
		MessageBox(_T("参数已写入！"), _T("提示"));
	}
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

	m_edit_pid_p_outerlayer = m_param.pid_position.p;
	m_edit_pid_i_outerlayer = m_param.pid_position.i;
	m_edit_pid_d_outerlayer = m_param.pid_position.d;

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

	/*if (m_serialport.isOpen())
	{
		serialSend(READ_DATA);
	}*/

	m_datashow_pwm1 = m_showdata.pwm[0];
	m_datashow_pwm2 = m_showdata.pwm[1];
	m_datashow_pwm3 = m_showdata.pwm[2];
	m_datashow_pwm4 = m_showdata.pwm[3];
	m_datashow_pwm5 = m_showdata.pwm[4];
	m_datashow_control1 = m_showdata.control[0];
	m_datashow_control2 = m_showdata.control[1];
	m_datashow_control3 = m_showdata.control[2];
	m_datashow_control4 = m_showdata.control[3];
	m_datashow_height = m_showdata.height;
	m_datashow_fusiondata = m_showdata.fusion_data;

	m_datashow_acc_x = m_showdata.sensor.VAL_ACC_X;
	m_datashow_acc_y = m_showdata.sensor.VAL_ACC_Y;
	m_datashow_acc_z = m_showdata.sensor.VAL_ACC_Z;
	m_datashow_gry_x = m_showdata.sensor.VAL_GYR_X;
	m_datashow_gry_y = m_showdata.sensor.VAL_GYR_Y;
	m_datashow_gry_z = m_showdata.sensor.VAL_GYR_Z;

	UpdateDataShow();

	UpdateChartCtrlData();

	if (!m_serialport.isOpen())
	{
		return;
	}
	sendCommand();

	CDialogEx::OnTimer(nIDEvent);
}


void CtinyDlg::UpdateDataShow()
{
	CStringW cstr_temp;

	cstr_temp.Format(_T("%d"), m_datashow_pwm1);
	GetDlgItem(IDC_DATASHOW_PWM1)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_pwm2);
	GetDlgItem(IDC_DATASHOW_PWM2)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_pwm3);
	GetDlgItem(IDC_DATASHOW_PWM3)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_pwm4);
	GetDlgItem(IDC_DATASHOW_PWM4)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_pwm5);
	GetDlgItem(IDC_DATASHOW_PWM5)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_control1);
	GetDlgItem(IDC_DATASHOW_CONTROL1)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_control2);
	GetDlgItem(IDC_DATASHOW_CONTROL2)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_control3);
	GetDlgItem(IDC_DATASHOW_CONTROL3)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_control4);
	GetDlgItem(IDC_DATASHOW_CONTROL4)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%.2f"), m_datashow_fusiondata);
	GetDlgItem(IDC_DATASHOW_RADAEFUSIONDATA)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%.2f"), m_datashow_height);
	GetDlgItem(IDC_DATASHOW_EXPECTEDHEIGHT)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_acc_x);
	GetDlgItem(IDC_DATASHOW_ACCX)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_acc_y);
	GetDlgItem(IDC_DATASHOW_ACCY)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_acc_z);
	GetDlgItem(IDC_DATASHOW_ACCZ)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_gry_x);
	GetDlgItem(IDC_DATASHOW_GRYX)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_gry_y);
	GetDlgItem(IDC_DATASHOW_GRYY)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_gry_z);
	GetDlgItem(IDC_DATASHOW_GRYZ)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_hm_x);
	GetDlgItem(IDC_DATASHOW_HMX)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_hm_y);
	GetDlgItem(IDC_DATASHOW_HMY)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%d"), m_datashow_hm_z);
	GetDlgItem(IDC_DATASHOW_HMZ)->SetWindowText(cstr_temp);

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
	if (!m_serialport.isOpen())
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
			data_to_send[_cnt++] = 0x00;
			data_to_send[_cnt++] = 0;

			data_to_send[_cnt++] = uint16_t(m_param.pid_custom.p) / 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_custom.p) % 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_custom.i) / 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_custom.i) % 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_custom.d) / 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_custom.d) % 256;
			
			uint16_t temp = 0;
			temp = m_param.excepted_height * 1000;
			data_to_send[_cnt++] = temp / 256;
			data_to_send[_cnt++] = temp % 256;

			temp = m_param.avoid_scope * 1000;
			data_to_send[_cnt++] = temp / 256;
			data_to_send[_cnt++] = temp % 256;

			temp = m_param.sensitivity * 1000;
			data_to_send[_cnt++] = temp / 256;
			data_to_send[_cnt++] = temp % 256;

			data_to_send[_cnt++] = m_param.enable_height;
			data_to_send[_cnt++] = m_param.enable_avoidObj;

			temp = m_param.rocker_mid[0];
			data_to_send[_cnt++] = temp / 256;
			data_to_send[_cnt++] = temp % 256;
			temp = m_param.rocker_mid[1];
			data_to_send[_cnt++] = temp / 256;
			data_to_send[_cnt++] = temp % 256;
			temp = m_param.rocker_mid[2];
			data_to_send[_cnt++] = temp / 256;
			data_to_send[_cnt++] = temp % 256;
			temp = m_param.rocker_mid[3];
			data_to_send[_cnt++] = temp / 256;
			data_to_send[_cnt++] = temp % 256;

			for (i = 0; i < _cnt; i++)
				sum += data_to_send[i];
			data_to_send[_cnt++] = sum;

			break;
		}

		case CtinyDlg::READ_PARAM:
		{
			data_to_send[_cnt++] = 0x01;
			data_to_send[_cnt++] = 0;

			for (i = 0; i < _cnt; i++)
				sum += data_to_send[i];
			data_to_send[_cnt++] = sum;

			break;
		}

		case CtinyDlg::WRITE_FLASH:
		{
			data_to_send[_cnt++] = 0x02;
			data_to_send[_cnt++] = 0;

			for (i = 0; i < _cnt; i++)
				sum += data_to_send[i];
			data_to_send[_cnt++] = sum;

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

		case CtinyDlg::SEND_COMMAND:
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
	
	m_serialport.write(data_to_send, _cnt);

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

	for (size_t i = 0; i < 100; i++)
	{
		m_count++;
		m_chartctrldata_fusiondata.x.push_back(m_count);
		m_chartctrldata_fusiondata.y.push_back(sin((double)m_chartctrldata_fusiondata.x[i] * 3.1415926 / 100));

		m_chartctrldata_height.x.push_back(m_count);
		m_chartctrldata_height.y.push_back(sin((double)m_chartctrldata_fusiondata.x[i] * 3.1415926 / 100));
	}

	m_chartctrl.EnableRefresh(false);
	m_chartctrl.RemoveAllSeries();
	m_pChartStandarAxisX->SetMinMax(m_chartctrldata_fusiondata.x[0], m_chartctrldata_fusiondata.x[m_chartctrldata_fusiondata.x.size() - 1]+20);
	m_pChartStandarAxisY->SetMinMax(-1*m_scope_y, m_scope_y);
	m_pChartLineSerie_fusiondata = m_chartctrl.CreateLineSerie();
	m_pChartLineSerie_fusiondata->SetWidth(2);
	m_pChartLineSerie_fusiondata->SetColor(RGB(0, 255, 0));
	m_pChartLineSerie_fusiondata->AddPoints(m_chartctrldata_fusiondata.x.data(), m_chartctrldata_fusiondata.y.data(), 100);

	m_pChartLineSerie_height = m_chartctrl.CreateLineSerie();
	m_pChartLineSerie_height->SetWidth(2);
	m_pChartLineSerie_height->SetColor(RGB(255, 0, 0));
	m_pChartLineSerie_height->AddPoints(m_chartctrldata_height.x.data(), m_chartctrldata_height.y.data(), 100);

	m_chartctrl.EnableRefresh(true);

	m_check_height.SetCheck(true);
	m_check_fusiondata.SetCheck(true);

	return true;
}


void CtinyDlg::UpdateChartCtrlData()
{
	m_count++;
	m_chartctrldata_fusiondata.x.erase(m_chartctrldata_fusiondata.x.begin());
	m_chartctrldata_fusiondata.y.erase(m_chartctrldata_fusiondata.y.begin());

	m_chartctrldata_fusiondata.x.push_back(m_count);
	m_chartctrldata_fusiondata.y.push_back(m_showdata.sensor.VAL_ACC_X);

	m_chartctrldata_height.x.erase(m_chartctrldata_height.x.begin());
	m_chartctrldata_height.y.erase(m_chartctrldata_height.y.begin());

	m_chartctrldata_height.x.push_back(m_count);
	m_chartctrldata_height.y.push_back(m_showdata.height);

	m_chartctrl.EnableRefresh(false);

	m_pChartLineSerie_fusiondata->AddPoint(m_chartctrldata_fusiondata.x[m_chartctrldata_fusiondata.x.size() - 1], m_chartctrldata_fusiondata.y[m_chartctrldata_fusiondata.y.size() - 1]);
	m_pChartLineSerie_fusiondata->RemovePointsFromBegin(0);

	m_pChartLineSerie_height->AddPoint(m_chartctrldata_height.x[m_chartctrldata_height.x.size() - 1], m_chartctrldata_height.y[m_chartctrldata_height.y.size() - 1]);
	m_pChartLineSerie_height->RemovePointsFromBegin(0);

	m_pChartStandarAxisX->SetMinMax(m_chartctrldata_fusiondata.x[0], m_chartctrldata_fusiondata.x[m_chartctrldata_fusiondata.x.size() - 1] + 20);

	m_chartctrl.EnableRefresh(true);
}


bool CtinyDlg::initColorButton()
{
	m_btn_color_fusiondata.Color = RGB(0, 255, 0);
	m_btn_color_fusiondata.DefaultColor = RGB(0, 255, 0);
	m_btn_color_fusiondata.TrackSelection = TRUE;
	m_btn_color_fusiondata.CustomText = _T("更多颜色...");
	m_btn_color_fusiondata.DefaultText = _T("自动");

	m_btn_color_height.Color = RGB(255,0,0);
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

	m_pChartLineSerie_height->SetColor(m_btn_color_height.GetColor());
	m_pChartLineSerie_fusiondata->SetColor(m_btn_color_fusiondata.GetColor());

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

	if (state==0)
	{
		m_pChartLineSerie_fusiondata->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie_fusiondata->SetVisible(true);
	}

}


void CtinyDlg::OnBnClickedCheckHeight()
{
	// TODO:  在此添加控件通知处理程序代码

	int state = m_check_height.GetCheck();

	if (state == 0)
	{
		m_pChartLineSerie_height->SetVisible(false);
	}
	else
	{
		m_pChartLineSerie_height->SetVisible(true);
	}
}


void CtinyDlg::OnBnClickedButtonZoomin()
{
	// TODO:  在此添加控件通知处理程序代码

	m_scope_y *= 2;
	m_pChartStandarAxisY->SetMinMax(-1 * m_scope_y, m_scope_y);

}


void CtinyDlg::OnBnClickedButtonZoomout()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_scope_y>2)
	{
		m_scope_y /= 2;
		m_pChartStandarAxisY->SetMinMax(-1 * m_scope_y, m_scope_y);
	}
	
}



void CtinyDlg::sendCommand()
{
	serialSend(SEND_COMMAND);
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
			if (rxcnt <= (DATA_SIZE_MAX - 1))
			{
				FrameAnl(RX_Data, rxcnt + 1);
			}
			rxstate = 0;
		}
	}
}

void CtinyDlg::FrameAnl(unsigned char* RX_Data, int len)
{
	unsigned char sum = 0;
	for (size_t i = 0; i < (len - 1); i++)
	{
		sum += *(RX_Data + i);
	}

	if (sum == *(RX_Data + len - 1))
	{
		switch (RX_Data[2])
		{
			case 1://status
			{
				/*m_showdata.sensor.VAL_ACC_X = ((float)(BytetoUint(RX_Data, 4))) / 100;
				m_showdata.sensor.VAL_ACC_Y = ((float)(BytetoUint(RX_Data, 6))) / 100;
				m_showdata.sensor.VAL_ACC_Z = ((float)(BytetoUint(RX_Data, 8))) / 100;*/
				break;
			}
			case 2://senser
			{
				m_showdata.sensor.VAL_ACC_X = BytetoUint(RX_Data, 4);
				m_showdata.sensor.VAL_ACC_Y = BytetoUint(RX_Data, 6);
				m_showdata.sensor.VAL_ACC_Z = BytetoUint(RX_Data, 8);
				m_showdata.sensor.VAL_GYR_X = BytetoUint(RX_Data, 10);
				m_showdata.sensor.VAL_GYR_Y = BytetoUint(RX_Data, 12);
				m_showdata.sensor.VAL_GYR_Z = BytetoUint(RX_Data, 14);
				break;
			}
			case 3:
			{

				break;
			}
			case 4://GPS
			{
				m_showdata.gps.latitude = ((double)Bytetoint(RX_Data, 4)) / 10000000;
				m_showdata.gps.longitude = ((double)Bytetoint(RX_Data, 8)) / 10000000;
				m_showdata.gps.elevation = ((float)Bytetoint(RX_Data, 12)) / 100;
				m_showdata.height = m_showdata.gps.elevation;
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
				m_showdata.sensor.VAL_ACC_X = BytetoUint(RX_Data, 4);
				m_showdata.sensor.VAL_ACC_Y = BytetoUint(RX_Data, 6);
				m_showdata.sensor.VAL_ACC_Z = BytetoUint(RX_Data, 8);
				m_showdata.sensor.VAL_GYR_X = BytetoUint(RX_Data, 10);
				m_showdata.sensor.VAL_GYR_Y = BytetoUint(RX_Data, 12);
				m_showdata.sensor.VAL_GYR_Z = BytetoUint(RX_Data, 14);
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
		m_scope_y = fabs(maxval) > fabs(minval) ? fabs(maxval) : fabs(minval);
		
		m_pChartStandarAxisY->SetAutomatic(false);

		m_pChartStandarAxisY->SetMinMax(-1 * m_scope_y, m_scope_y);
	}
	else
	{
		m_pChartStandarAxisY->SetAutomatic(true);
	}
}
