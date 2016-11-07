
// tinyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "tiny.h"
#include "tinyDlg.h"
#include "afxdialogex.h"

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
	DDX_Text(pDX, IDC_DATASHOW_RADAEFUSIONDATA, m_datashow_radarfusiondata);
	DDX_Text(pDX, IDC_DATASHOW_EXPECTEDHEIGHT, m_datashow_expectedheight);

	DDX_Text(pDX, IDC_DATASETTING_ROCKERMID1, m_edit_rockermid1);
	DDX_Text(pDX, IDC_DATASETTING_ROCKERMID2, m_edit_rockermid2);
	DDX_Text(pDX, IDC_DATASETTING_ROCKERMID3, m_edit_rockermid3);
	DDX_Text(pDX, IDC_DATASETTING_ROCKERMID4, m_edit_rockermid4);
	DDX_Text(pDX, IDC_DATASETTING_EXPECTEDHEIGHT, m_edit_exceptheight);
	DDX_Text(pDX, IDC_DATASETTING_AVOIDSCOPE, m_edit_avoidscope);
	DDX_Text(pDX, IDC_DATASETTING_SENSITIVITY, m_edit_sensitivity);
	DDX_Text(pDX, IDC_DATASETTING_PID_P, m_edit_pid_p);
	DDX_Text(pDX, IDC_DATASETTING_PID_I, m_edit_pid_i);
	DDX_Text(pDX, IDC_DATASETTING_PID_D, m_edit_pid_d);

	DDX_Control(pDX, IDC_ICON_STATE, m_icon_state);
	DDX_Control(pDX, IDC_ICON_COMSTATE, m_icon_comstate);
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

	UpdateData(FALSE);

	std::thread serial_thread_temp(&CtinyDlg::serialRead, this);
	serial_thread.swap(serial_thread_temp);

	SetTimer(0, 20, NULL);

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
	m_datashow_expectedheight = 0;
	m_datashow_radarfusiondata = 0;

	m_edit_pid_p = 0;
	m_edit_pid_i = 0;
	m_edit_pid_d = 0;
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
#define DATA_SIZE_MAX 50
	size_t data_length = 0;
	unsigned char sum = 0;
	unsigned char data_buf[DATA_SIZE_MAX] = { 0 };
	int16_t temp = 0;
	int delay_ms = 5;

	while (!isTerminal)
	{
		if (!m_serialport.isOpen()||(m_serial_closing))
		{
			Sleep(100);
			continue;
		}
		sum = 0;
		data_length = m_serialport.available();
		if (data_length>DATA_SIZE_MAX)
		{
			unsigned char *data_buf_temp = new unsigned char[data_length];
			m_serialport.read(data_buf_temp, data_length);
			delete data_buf_temp;
			continue;
		}
		if (data_length)
		{
			m_serialport.read(data_buf, data_length);
			for (size_t i = 0; i < (data_length - 1); i++)
			{
				sum += *(data_buf + i);
			}

			if (!(sum == *(data_buf + data_length - 1)))
				continue;		//判断sum
			if (!(*(data_buf) == 0xAA && *(data_buf + 1) == 0xAF))
				continue;		//判断帧头
			if (*(data_buf + 2) == 0x03)
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
				m_param.pid_p = temp;

				temp = data_buf[6];
				temp <<= 8;
				temp |= data_buf[7];
				m_param.pid_i = temp;

				temp = data_buf[8];
				temp <<= 8;
				temp |= data_buf[9];
				m_param.pid_d = temp;

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
			}
		}
		
		Sleep(delay_ms);
	}
	//cout << "thread quit" << endl;
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
	m_param.pid_p = m_edit_pid_p;
	m_param.pid_i = m_edit_pid_i;
	m_param.pid_d = m_edit_pid_d;
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
	m_edit_pid_p = m_param.pid_p;
	m_edit_pid_i = m_param.pid_i;
	m_edit_pid_d = m_param.pid_d;
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

	if (m_serialport.isOpen())
	{
		serialSend(READ_DATA);
	}

	m_datashow_pwm1 = m_showdata.pwm[0];
	m_datashow_pwm2 = m_showdata.pwm[1];
	m_datashow_pwm3 = m_showdata.pwm[2];
	m_datashow_pwm4 = m_showdata.pwm[3];
	m_datashow_pwm5 = m_showdata.pwm[4];
	m_datashow_control1 = m_showdata.control[0];
	m_datashow_control2 = m_showdata.control[1];
	m_datashow_control3 = m_showdata.control[2];
	m_datashow_control4 = m_showdata.control[3];
	m_datashow_expectedheight = m_showdata.excepted_height;
	m_datashow_radarfusiondata = m_showdata.radar_fusion;

	UpdateDataShow();

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

	cstr_temp.Format(_T("%.2f"), m_datashow_radarfusiondata);
	GetDlgItem(IDC_DATASHOW_RADAEFUSIONDATA)->SetWindowText(cstr_temp);

	cstr_temp.Format(_T("%.2f"), m_datashow_expectedheight);
	GetDlgItem(IDC_DATASHOW_EXPECTEDHEIGHT)->SetWindowText(cstr_temp);

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

	m_icon_comstate.SetIcon(m_hIcon_com_black);
	m_icon_state.SetIcon(m_hIcon_indicator_black);
}


bool CtinyDlg::serialSend(SerialSendOrder sendOrder)
{
	if (!m_serialport.isOpen())
	{
		MessageBox(_T("串口未打开!"), _T("提示"));
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

			data_to_send[_cnt++] = uint16_t(m_param.pid_p) / 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_p) % 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_i) / 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_i) % 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_d) / 256;
			data_to_send[_cnt++] = uint16_t(m_param.pid_d) % 256;
			
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

			break;
		}

		case CtinyDlg::READ_PARAM:
		{
			data_to_send[_cnt++] = 0x01;
			data_to_send[_cnt++] = 0;

			break;
		}

		case CtinyDlg::WRITE_FLASH:
		{
			data_to_send[_cnt++] = 0x02;
			data_to_send[_cnt++] = 0;

			break;
		}

		case CtinyDlg::READ_DATA:
		{
			data_to_send[_cnt++] = 0x03;
			data_to_send[_cnt++] = 0;

			break;
		}

		default:
			break;
	}

	data_to_send[3] = _cnt - 4;
	for (i = 0; i < _cnt; i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	
	m_serialport.write(data_to_send, _cnt);

	return true;
}
