
// tinyDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <sstream>
#include <serial/serial.h>
#include "Param.h"

// CtinyDlg 对话框
class CtinyDlg : public CDialogEx
{
// 构造
public:
	CtinyDlg(CWnd* pParent = NULL);	// 标准构造函数

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
	

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_combo_combaudrate;
	CComboBox m_combo_comnum;

	int m_datashow_pwm1;
	int m_datashow_pwm2;
	int m_datashow_pwm3;
	int m_datashow_pwm4;
	int m_datashow_pwm5;
	int m_datashow_control1;
	int m_datashow_control2;
	int m_datashow_control3;
	int m_datashow_control4;
	float m_datashow_radarfusiondata;
	float m_datashow_expectedheight;

	CButton m_btn_opencom;
	CButton m_btn_writeparam;
	CButton m_btn_readparam;
	CButton m_btn_writeflash;
	CStatic m_static_comstate;
	
	int m_edit_pid_p;
	int m_edit_pid_i;
	int m_edit_pid_d;
	int m_edit_rockermid1;
	int m_edit_rockermid2;
	int m_edit_rockermid3;
	int m_edit_rockermid4;
	float m_edit_exceptheight;
	float m_edit_avoidscope;
	float m_edit_sensitivity;

	serial::Serial m_serialport;
	Param m_param;
	DataShow m_showdata;

	bool isTerminal;

	std::thread serial_thread;

public:
	bool init();
	bool initCom();
	bool initDataShow();
	void detectCom();
	void serialRead();

	afx_msg void OnBnClickedButtonOpencom();
	afx_msg void OnBnClickedButtonWriteparam();
	afx_msg void OnBnClickedButtonReadparam();
	afx_msg void OnBnClickedButtonWriteflash();
	afx_msg void OnClose();
	void writeParam();
	void readParam();
	void writeFlash();
	CButton m_check_setheight;
	CButton m_check_avoidobjection;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void UpdateDataShow();
	void initIcon();
	CStatic m_icon_state;
	CStatic m_icon_comstate;
};