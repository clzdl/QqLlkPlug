
// QqLlkPlugDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "GameData.h"
#include "GameConstants.h"
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

	BOOL m_autoStart;   //
	afx_msg void OnBnClickedBtnStartgame();
	afx_msg void OnBnClickedBtnReadstartflag();

	// 开局按钮
	CButton m_btnStartGame;
	//棋盘数据
	byte m_chessData[CHESS_V_NUM][CHESS_H_NUM];//a[y][x]

	afx_msg void OnBnClickedBtnReadchessdata();
	afx_msg void OnBnClickedBtnSingleclear();
};
