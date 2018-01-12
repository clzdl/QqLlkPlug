
// QqLlkPlugDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "GameData.h"
#include "GameConstants.h"
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

	BOOL m_autoStart;   //
	afx_msg void OnBnClickedBtnStartgame();
	afx_msg void OnBnClickedBtnReadstartflag();

	// ���ְ�ť
	CButton m_btnStartGame;
	//��������
	byte m_chessData[CHESS_V_NUM][CHESS_H_NUM];//a[y][x]

	afx_msg void OnBnClickedBtnReadchessdata();
	afx_msg void OnBnClickedBtnSingleclear();
};
