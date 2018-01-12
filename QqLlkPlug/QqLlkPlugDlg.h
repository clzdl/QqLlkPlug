
// QqLlkPlugDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "GameData.h"
#include "GameConstants.h"
#include "afxcmn.h"
// CQqLlkPlugDlg 对话框
class CQqLlkPlugDlg : public CDialogEx
{
// 构造
public:
	CQqLlkPlugDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QQLLKPLUG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
	//获取练练看窗口句柄
	HWND FindQqLlkWindows();

	//获取游戏开局标识
	DWORD GetGameStartFlag();

	//获取棋子数
	DWORD GetChessDataNum();

	//取消倒计时
	void CancelCountDown();

	//开局游戏
	void StartGame();

	//读取棋盘数据
	int ReadChessData();

	//计算点p的水平联通线
	CBeeLine CalcHLine(CBeePoint p);
	//计算点p的纵向联通线
	CBeeLine CalcVLine(CBeePoint p);
	//消除一对
	void ClearPair();
	//模拟点击一对按钮
	void ClickPair(CBeePoint p1, CBeePoint p2);
public:

	
	afx_msg void OnBnClickedBtnStartgame();
	afx_msg void OnBnClickedBtnReadstartflag();


	afx_msg void OnBnClickedBtnReadchessdata();
	afx_msg void OnBnClickedBtnSingleclear();
	afx_msg void OnBnClickedBtnReadchessnumber();
	afx_msg void OnBnClickedBtnCountdown();
	afx_msg void OnBnClickedChkSpeed();
	afx_msg void OnNMReleasedcaptureSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedChkGametop();
	afx_msg void OnBnClickedChkHangUp();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedChkStartgame();


	// 开局按钮
	CButton m_btnStartGame;
	//棋盘数据
	byte m_chessData[CHESS_V_NUM][CHESS_H_NUM];//a[y][x]
	BOOL m_autoStart;   //自动开局标识
	// 游戏置顶标识
	BOOL m_gameTop;
	
	// 挂机速度
	BOOL m_speed;
	
	CSliderCtrl m_sliderSpeed;
	///游戏挂机速度
	DWORD m_gameSpeed;  
	CButton m_ctrlSpeed;
	// 自动挂机
	BOOL m_autoHangUp;
	
	
};
