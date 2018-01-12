
// QqLlkPlugDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "GameData.h"
#include "GameConstants.h"
#include "afxcmn.h"
// CQqLlkPlugDlg �Ի���
class CQqLlkPlugDlg : public CDialogEx
{
// ����
public:
	CQqLlkPlugDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QQLLKPLUG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
	//��ȡ���������ھ��
	HWND FindQqLlkWindows();

	//��ȡ��Ϸ���ֱ�ʶ
	DWORD GetGameStartFlag();

	//��ȡ������
	DWORD GetChessDataNum();

	//ȡ������ʱ
	void CancelCountDown();

	//������Ϸ
	void StartGame();

	//��ȡ��������
	int ReadChessData();

	//�����p��ˮƽ��ͨ��
	CBeeLine CalcHLine(CBeePoint p);
	//�����p��������ͨ��
	CBeeLine CalcVLine(CBeePoint p);
	//����һ��
	void ClearPair();
	//ģ����һ�԰�ť
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


	// ���ְ�ť
	CButton m_btnStartGame;
	//��������
	byte m_chessData[CHESS_V_NUM][CHESS_H_NUM];//a[y][x]
	BOOL m_autoStart;   //�Զ����ֱ�ʶ
	// ��Ϸ�ö���ʶ
	BOOL m_gameTop;
	
	// �һ��ٶ�
	BOOL m_speed;
	
	CSliderCtrl m_sliderSpeed;
	///��Ϸ�һ��ٶ�
	DWORD m_gameSpeed;  
	CButton m_ctrlSpeed;
	// �Զ��һ�
	BOOL m_autoHangUp;
	
	
};
