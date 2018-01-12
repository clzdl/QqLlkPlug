
// QqLlkPlugDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QqLlkPlug.h"
#include "QqLlkPlugDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CQqLlkPlugDlg 对话框



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


// CQqLlkPlugDlg 消息处理程序

BOOL CQqLlkPlugDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQqLlkPlugDlg::OnPaint()
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
HCURSOR CQqLlkPlugDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HWND CQqLlkPlugDlg::FindQqLlkWindows()
{
	return ::FindWindow(NULL, _T("QQ游戏 - 连连看角色版"));
}

DWORD CQqLlkPlugDlg::GetGameStartFlag()
{
	HWND hwndLlk = FindQqLlkWindows();
	if (NULL == hwndLlk)
	{
		MessageBox(_T("请先打开连连看游戏."));
		return FAILURE;
	}
	//获取进程id
	DWORD lldProcessId;
	GetWindowThreadProcessId(hwndLlk , &lldProcessId);
	//打开指定进程
	HANDLE handleLlkProcess = OpenProcess(PROCESS_ALL_ACCESS,NULL , lldProcessId);
	DWORD gameStartFlag;
	DWORD byteReadNum = 0 ;

	//0x0018A4C8,0x0018A4CC,
	ReadProcessMemory(handleLlkProcess, (LPCVOID)0x0018A4C8,&gameStartFlag,4 , &byteReadNum);
	if (0 == byteReadNum)
	{
		MessageBox(_T("开局标识读取失败."));
		return FAILURE;
	}
	//关闭进程句柄
	CloseHandle(handleLlkProcess);
	return gameStartFlag;
}

void CQqLlkPlugDlg::StartGame()
{
	HWND hwndLlk = FindQqLlkWindows();
	if (NULL == hwndLlk)
	{
		MessageBox(_T("请先打开连连看游戏."));
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
		MessageBox(_T("请先打开连连看游戏."));
		return FAILURE;
	}
	//获取进程id
	DWORD lldProcessId;
	GetWindowThreadProcessId(hwndLlk, &lldProcessId);
	//打开指定进程
	HANDLE handleLlkProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, lldProcessId);

	DWORD byteReadNum = 0;
	ReadProcessMemory(handleLlkProcess, (LPCVOID)0x00189F78/*棋盘基址*/, m_chessData, 11*19, &byteReadNum);
	if (0 == byteReadNum)
	{
		MessageBox(_T("读取棋盘数据失败."));
		return FAILURE;
	}
	//关闭进程句柄
	CloseHandle(handleLlkProcess);
	return SUCCESS;
}

void CQqLlkPlugDlg::OnBnClickedBtnReadchessdata()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//右->左
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
	//左-> 右
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
	//下->上
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
	//上->下
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
					{//同一点
						continue;
					}

					CBeeLine hLine4P2 = CalcHLine(p2);
					CBeeLine vLine4P2 = CalcVLine(p2);

					if (hLine4P1.IsCoincide(hLine4P2) || vLine4P1.IsCoincide(vLine4P2))
					{///可消
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


					//hLine4P1  hLine4P2 是否存在平行相交线
					if (hLine4P1.IsParallelIntersect(hLine4P2))
					{
						int tmpBegX = max(hLine4P1.m_start.m_x, hLine4P2.m_start.m_x);
						int tmpEndX = min(hLine4P1.m_end.m_x, hLine4P2.m_end.m_x);

						for (int i = tmpBegX; i <= tmpEndX; ++i)
						{
							CBeePoint tmpP(i, hLine4P1.m_start.m_y);
							//以P1水平线为基准，获取各点的竖直垂直线
							tmpP.m_value = m_chessData[i][hLine4P1.m_start.m_y];
							CBeeLine tmpVLine = CalcVLine(tmpP);
							if (tmpVLine.IsVerticalIntersect(hLine4P2))
							{///可消
								ClickPair(p1, p2);
								return;
							}
						}
					}

					//vLine4P2  vLine4P2 是否存在平行相交线
					if (vLine4P1.IsParallelIntersect(vLine4P2))
					{
						int tmpBegY = max(vLine4P1.m_start.m_y, vLine4P2.m_start.m_y);
						int tmpEndY = min(vLine4P1.m_end.m_y, vLine4P2.m_end.m_y);

						for (int i = tmpBegY; i <= tmpEndY; ++i)
						{
							//以P1垂直线为基准，获取各点的水平垂直线
							CBeePoint tmpP(vLine4P1.m_start.m_x, i);

							tmpP.m_value = m_chessData[vLine4P1.m_start.m_x][i];
							CBeeLine tmpHLine = CalcHLine(tmpP);
							//不能确定tmpHLine 从那条线开始
							if (tmpHLine.IsVerticalIntersect(vLine4P2))
							{///可消
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
	//点击p1
	lparam = ((p1.m_y * 35 + 192) << 16) + (p1.m_x * 31 + 21);
	::SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	::SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);//
	
											   //点击p2								   
	lparam = ((p2.m_y * 35 + 192) << 16) + (p2.m_x * 31 + 21);
	::SendMessage(hwnd, WM_LBUTTONDOWN, 0, lparam);//
	::SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);//


}


void CQqLlkPlugDlg::OnBnClickedBtnSingleclear()
{
	// TODO: 在此添加控件通知处理程序代码
	if (FAILURE == ReadChessData())
	{
		return;
	}
	ClearPair();
}
