
// QqLlkPlugDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QqLlkPlug.h"
#include "QqLlkPlugDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQqLlkPlugDlg �Ի���



CQqLlkPlugDlg::CQqLlkPlugDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_QQLLKPLUG_DIALOG, pParent)
	, m_autoStart(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQqLlkPlugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHK_STARTGAME, m_autoStart);
	DDX_Control(pDX, IDC_BTN_STARTGAME, m_btnStartGame);
}

BEGIN_MESSAGE_MAP(CQqLlkPlugDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_STARTGAME, &CQqLlkPlugDlg::OnBnClickedBtnStartgame)
	ON_BN_CLICKED(IDC_BTN_READSTARTFLAG, &CQqLlkPlugDlg::OnBnClickedBtnReadstartflag)
	ON_BN_CLICKED(IDC_BTN_READCHESSDATA, &CQqLlkPlugDlg::OnBnClickedBtnReadchessdata)
	ON_BN_CLICKED(IDC_BTN_SINGLECLEAR, &CQqLlkPlugDlg::OnBnClickedBtnSingleclear)
END_MESSAGE_MAP()


// CQqLlkPlugDlg ��Ϣ�������

BOOL CQqLlkPlugDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQqLlkPlugDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQqLlkPlugDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQqLlkPlugDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HWND CQqLlkPlugDlg::FindQqLlkWindows()
{
	return ::FindWindow(NULL, _T("QQ��Ϸ - ��������ɫ��"));
}

DWORD CQqLlkPlugDlg::GetGameStartFlag()
{
	HWND hwndLlk = FindQqLlkWindows();
	if (NULL == hwndLlk)
	{
		MessageBox(_T("���ȴ���������Ϸ."));
		return FAILURE;
	}
	//��ȡ����id
	DWORD lldProcessId;
	GetWindowThreadProcessId(hwndLlk , &lldProcessId);
	//��ָ������
	HANDLE handleLlkProcess = OpenProcess(PROCESS_ALL_ACCESS,NULL , lldProcessId);
	DWORD gameStartFlag;
	DWORD byteReadNum = 0 ;

	//0x0018A4C8,0x0018A4CC,
	ReadProcessMemory(handleLlkProcess, (LPCVOID)0x0018A4C8,&gameStartFlag,4 , &byteReadNum);
	if (0 == byteReadNum)
	{
		MessageBox(_T("���ֱ�ʶ��ȡʧ��."));
		return FAILURE;
	}
	//�رս��̾��
	CloseHandle(handleLlkProcess);
	return gameStartFlag;
}

void CQqLlkPlugDlg::StartGame()
{
	HWND hwndLlk = FindQqLlkWindows();
	if (NULL == hwndLlk)
	{
		MessageBox(_T("���ȴ���������Ϸ."));
		return;
	}

	RECT rectLlk;
	::GetWindowRect(hwndLlk, &rectLlk);

	POINT lastCurPoint;
	::GetCursorPos(&lastCurPoint);

	::SetCursorPos(rectLlk.left + START_BTN_X, rectLlk.top + START_BTN_Y);

	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(200);

	::SetCursorPos(lastCurPoint.x, lastCurPoint.y);
}



void CQqLlkPlugDlg::OnBnClickedBtnStartgame()
{
	StartGame();
	
	m_btnStartGame.EnableWindow(false);

}


void CQqLlkPlugDlg::OnBnClickedBtnReadstartflag()
{
	TCHAR temp[124] = { 0 };
	DWORD startFlag = 0;
	if (FAILURE == (startFlag = GetGameStartFlag()))
	{
		return;
	}
	_itow_s(startFlag, temp, 10);
	MessageBox(temp);
}


int CQqLlkPlugDlg::ReadChessData()
{
	HWND hwndLlk = FindQqLlkWindows();
	if (NULL == hwndLlk)
	{
		MessageBox(_T("���ȴ���������Ϸ."));
		return FAILURE;
	}
	//��ȡ����id
	DWORD lldProcessId;
	GetWindowThreadProcessId(hwndLlk, &lldProcessId);
	//��ָ������
	HANDLE handleLlkProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, lldProcessId);

	DWORD byteReadNum = 0;
	ReadProcessMemory(handleLlkProcess, (LPCVOID)0x00189F78/*���̻�ַ*/, m_chessData, 11*19, &byteReadNum);
	if (0 == byteReadNum)
	{
		MessageBox(_T("��ȡ��������ʧ��."));
		return FAILURE;
	}
	//�رս��̾��
	CloseHandle(handleLlkProcess);
	return SUCCESS;
}

void CQqLlkPlugDlg::OnBnClickedBtnReadchessdata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (FAILURE == ReadChessData())
	{
		return;
	}
	CString tmpString;
	TCHAR byte[2+1];
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 19; ++j)
		{
			memset(byte, sizeof(byte), 0);
			_itow_s(m_chessData[i][j], byte, 16);
			tmpString.Append(byte);
			tmpString.Append(_T(" "));

		}
		tmpString.Append(_T("\r\n"));

	}
	MessageBox(tmpString);
}

CBeeLine CQqLlkPlugDlg::CalcHLine(CBeePoint p)
{
	CBeeLine hLine(horizontal);
	
	CBeePoint begP(p);
	CBeePoint endP(p);
	//��->��
	for (int i = p.m_x - 1; i >= 0; --i)
	{
		if (m_chessData[p.m_y][i] == 0x00/* || m_chessData[p.m_y][i] == p.m_value*/)
		{
			begP.m_x = i;
		}
		else 
		{
			break;
		}
	}
	//��-> ��
	for (int i = p.m_x + 1; i < CHESS_H_NUM; ++i)
	{
		if (m_chessData[p.m_y][i] == 0x00/* || m_chessData[p.m_y][i] == p.m_value*/)
		{
			endP.m_x = i;
		}
		else
		{
			break;
		}
	}
	hLine.m_start = begP;
	hLine.m_end = endP;

	return hLine;
}

CBeeLine CQqLlkPlugDlg::CalcVLine(CBeePoint p)
{
	CBeeLine vLine(vertical);

	CBeePoint begP = p;
	CBeePoint endP = p;
	//��->��
	for (int i = p.m_y - 1; i >= 0; --i)
	{
		if (m_chessData[i][p.m_x] == 0x00/* || m_chessData[i][p.m_x] == p.m_value*/)
		{
			begP.m_y = i;
		}
		else
		{
			break;
		}
	}
	//��->��
	for (int i = p.m_y + 1; i < CHESS_V_NUM; ++i)
	{
		if (m_chessData[i][p.m_x] == 0x00/* || m_chessData[i][p.m_x] == p.m_value*/)
		{
			endP.m_y = i;
		}
		else
		{
			break;
		}
	}
	vLine.m_start = begP;
	vLine.m_end = endP;

	return vLine;
}

void CQqLlkPlugDlg::ClearPair()
{
	for (int v1 = 0; v1 < CHESS_V_NUM; ++v1)
	{
		for (int h1 = 0; h1 < CHESS_H_NUM; ++h1)
		{
			CBeePoint p1(h1,v1);
			p1.m_value = m_chessData[v1][h1];
			if (p1.m_value == 0x00)
				continue;


			CBeeLine hLine4P1 = CalcHLine(p1);
			CBeeLine vLine4P1 = CalcVLine(p1);
			for (int v2 = v1; v2 < CHESS_V_NUM; ++v2)
			{
				for (int h2 = 0; h2 < CHESS_H_NUM; ++h2)
				{
					CBeePoint p2(h2,v2);
					p2.m_value = m_chessData[v2][h2];
					if (p2.m_value == 0x00 || p1.m_value != p2.m_value)
						continue;

					if ( p1.IsSamePoint(p2) )
					{//ͬһ��
						continue;
					}

					CBeeLine hLine4P2 = CalcHLine(p2);
					CBeeLine vLine4P2 = CalcVLine(p2);

					if (hLine4P1.IsCoincide(hLine4P2) || vLine4P1.IsCoincide(vLine4P2))
					{///����
						ClickPair(p1, p2);
						return;
					}
					else if (hLine4P1.IsVerticalIntersect(vLine4P2)) 
					{
						ClickPair(p1, p2);
						return;
					}
					else if (vLine4P1.IsVerticalIntersect(hLine4P2))
					{
						ClickPair(p1, p2);
						return;
					}


					//hLine4P1  hLine4P2 �Ƿ����ƽ���ཻ��
					if (hLine4P1.IsParallelIntersect(hLine4P2))
					{
						int tmpBegX = max(hLine4P1.m_start.m_x, hLine4P2.m_start.m_x);
						int tmpEndX = min(hLine4P1.m_end.m_x, hLine4P2.m_end.m_x);

						for (int i = tmpBegX; i <= tmpEndX; ++i)
						{
							CBeePoint tmpP(i, hLine4P1.m_start.m_y);
							//��P1ˮƽ��Ϊ��׼����ȡ�������ֱ��ֱ��
							tmpP.m_value = m_chessData[i][hLine4P1.m_start.m_y];
							CBeeLine tmpVLine = CalcVLine(tmpP);
							if (tmpVLine.IsVerticalIntersect(hLine4P2))
							{///����
								ClickPair(p1, p2);
								return;
							}
						}
					}

					//vLine4P2  vLine4P2 �Ƿ����ƽ���ཻ��
					if (vLine4P1.IsParallelIntersect(vLine4P2))
					{
						int tmpBegY = max(vLine4P1.m_start.m_y, vLine4P2.m_start.m_y);
						int tmpEndY = min(vLine4P1.m_end.m_y, vLine4P2.m_end.m_y);

						for (int i = tmpBegY; i <= tmpEndY; ++i)
						{
							//��P1��ֱ��Ϊ��׼����ȡ�����ˮƽ��ֱ��
							CBeePoint tmpP(vLine4P1.m_start.m_x, i);

							tmpP.m_value = m_chessData[vLine4P1.m_start.m_x][i];
							CBeeLine tmpHLine = CalcHLine(tmpP);
							//����ȷ��tmpHLine �������߿�ʼ
							if (tmpHLine.IsVerticalIntersect(vLine4P2))
							{///����
								ClickPair(p1, p2);
								return;
							}
						}
					}


				}
			}
		}
	}
}

void CQqLlkPlugDlg::ClickPair(CBeePoint p1, CBeePoint p2)
{
	HWND hwnd = FindQqLlkWindows();
	int lparam;
	//���p1
	lparam = ((p1.m_y * 35 + 192) << 16) + (p1.m_x * 31 + 21);
	::SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	::SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);//
	
											   //���p2								   
	lparam = ((p2.m_y * 35 + 192) << 16) + (p2.m_x * 31 + 21);
	::SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	::SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);//


}


void CQqLlkPlugDlg::OnBnClickedBtnSingleclear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (FAILURE == ReadChessData())
	{
		return;
	}
	ClearPair();
}
