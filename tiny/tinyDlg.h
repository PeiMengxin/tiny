
// tinyDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <Dbt.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <sstream>
#include <serial/serial.h>
#include "Param.h"
#include "ChartCtrl/ChartAxis.h"
#include "ChartCtrl/ChartLineSerie.h"
#include "ChartCtrl/ChartLegend.h"
#include "ColorButton/ColorButton.h"
#include "SerialSingleton.h"

#define SHOW_DATA_SIZE 300
#define SHOW_DATA_SIZE_MARGIN 50

// CtinyDlg 对话框
class CtinyDlg : public CPropertyPage
{
	typedef enum SerialSendOrder
	{
		WRITE_PARAM = 0,
		READ_PARAM,
		WRITE_FLASH,
		READ_DATA,
		SEND_COMMAND
	};

	enum DataName
	{
		ACC_X = 0,
		ACC_Y,
		ACC_Z,
		GRY_X,
		GRY_Y,
		GRY_Z,
		HM_X,
		HM_Y,
		HM_Z,
		ANGLE_PITCH,
		ANGLE_ROLL,
		ANGLE_YAW,
		FUSIONDATA,
		HEIGHT,

		END
	};

	// 构造
public:
	CtinyDlg(/*CWnd* pParent = NULL*/);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_TINY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;
	HICON m_hIcon_indicator_black;
	HICON m_hIcon_indicator_green;
	HICON m_hIcon_indicator_yellow;
	HICON m_hIcon_indicator_red;
	HICON m_hIcon_com_black;
	HICON m_hIcon_com_green;
	HICON m_hIcon_zoom_out;
	HICON m_hIcon_zoom_in;


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonOpencom();
	afx_msg void OnBnClickedButtonWriteparam();
	afx_msg void OnBnClickedButtonReadparam();
	afx_msg void OnBnClickedButtonWriteflash();
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();

	afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
	afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
	afx_msg LONG OnSelChange(UINT lParam, LONG wParam);
	afx_msg LONG OnCloseUp(UINT lParam, LONG wParam);
	afx_msg LONG OnDropDown(UINT lParam, LONG wParam);

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_combo_combaudrate;
	CComboBox m_combo_comnum;

	CButton m_btn_opencom;
	CButton m_btn_writeparam;
	CButton m_btn_readparam;
	CButton m_btn_writeflash;
	CButton m_check_setheight;
	CButton m_check_avoidobjection;

	CStatic m_icon_state;
	CStatic m_icon_comstate;
	CStatic m_static_comstate;

	int m_edit_pid_p_custom;
	int m_edit_pid_i_custom;
	int m_edit_pid_d_custom;

	int m_edit_pid_p_outerlayer;
	int m_edit_pid_i_outerlayer;
	int m_edit_pid_d_outerlayer;

	int m_edit_pid_p_innerlayer;
	int m_edit_pid_i_innerlayer;
	int m_edit_pid_d_innerlayer;

	int m_edit_pid_p_height;
	int m_edit_pid_i_height;
	int m_edit_pid_d_height;

	int m_edit_pid_p_position;
	int m_edit_pid_i_position;
	int m_edit_pid_d_position;

	int m_edit_rockermid1;
	int m_edit_rockermid2;
	int m_edit_rockermid3;
	int m_edit_rockermid4;
	float m_edit_exceptheight;
	float m_edit_avoidscope;
	float m_edit_sensitivity;

	bool isTerminal;
	bool m_serial_closing;

	SerialSingleton* m_serial_instance;
	Param m_param;
	DataShow* m_showdata;
	int m_count;

	std::thread serial_thread;

	bool init();
	bool initCom();
	void initIcon();
	bool initDataShow();

	void detectCom();
	void serialRead();
	bool serialSend(SerialSendOrder sendOrder);

	void writeParam();
	void readParam();
	void writeFlash();

	void UpdateDataShow();

public:
	CChartCtrl m_chartctrl;
	CChartStandardAxis *m_pChartStandarAxisX;
	CChartStandardAxis *m_pChartStandarAxisY;
	CChartLineSerie *m_pChartLineSerie_fusiondata;
	CChartLineSerie *m_pChartLineSerie_height;

	std::vector <CChartLineSerie*> m_pChartLineSerie;
	std::vector < COLORREF > ColorTable;
	int m_scope_y;

private:
	bool initChartCtrl();
public:
	void UpdateChartCtrlData();
	CColorButton m_btn_color_fusiondata;
	CColorButton m_btn_color_height;
	bool initColorButton();
	COLORREF m_color;
	CButton m_check_fusiondata;
	CButton m_check_height;
	afx_msg void OnBnClickedCheckFusiondata();
	afx_msg void OnBnClickedCheckHeight();

	afx_msg void OnBnClickedButtonZoomin();
	afx_msg void OnBnClickedButtonZoomout();
	
	void sendCommand();
	void DataAnl(unsigned char* data_buf_temp, int len, unsigned char* RX_Data);
	void FrameAnl(unsigned char* RX_Data, int len);
	CButton m_check_autoscope;
	afx_msg void OnBnClickedCheckAutoscope();
	afx_msg void OnBnClickedCheckAcc();
	afx_msg void OnBnClickedCheckGry();
	afx_msg void OnBnClickedCheckHm();
	CButton m_check_acc;
	CButton m_check_gry;
	CButton m_check_hm;
	bool initSerial();
	bool initLineName();
	virtual void OnOK();
	CButton m_check_angle;
	std::vector<TChartString> LineName;
	afx_msg void OnBnClickedCheckAngle();
};