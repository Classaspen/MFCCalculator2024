﻿
// MFCCalculatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCCalculator.h"
#include "MFCCalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int OP_TYPE_ADD = 1;
const int OP_TYPE_SUB = 2;
const int OP_TYPE_MUL = 3;
const int OP_TYPE_DIV = 4; 
const int OP_TYPE_NONE = 0;   //没有进行按键操作


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


// CMFCCalculatorDlg 对话框



CMFCCalculatorDlg::CMFCCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCALCULATOR_DIALOG, pParent)
	, m_csRes(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RES, m_csRes);
}

BEGIN_MESSAGE_MAP(CMFCCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &CMFCCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_A, &CMFCCalculatorDlg::OnBnClickedButtonA)
	ON_BN_CLICKED(IDC_BUTTON_S, &CMFCCalculatorDlg::OnBnClickedButtonS)
	ON_BN_CLICKED(IDC_BUTTON_M, &CMFCCalculatorDlg::OnBnClickedButtonM)
	ON_BN_CLICKED(IDC_BUTTON_D, &CMFCCalculatorDlg::OnBnClickedButtonD)
	ON_BN_CLICKED(IDC_BUTTON_AMOUNT, &CMFCCalculatorDlg::OnBnClickedButtonCala)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFCCalculatorDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CMFCCalculatorDlg 消息处理程序

BOOL CMFCCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	m_nOpType = OP_TYPE_NONE;
	m_csRes = _T("0");     //如果要进行小数计算，变成0.0
	m_bNew = true;
	UpdateData(FALSE);   
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCCalculatorDlg::OnPaint()
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
HCURSOR CMFCCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCalculatorDlg::OnBnClickedButton1()
{
	PressDigit(1);
}


void CMFCCalculatorDlg::OnBnClickedButton2()
{
	PressDigit(2);
}


void CMFCCalculatorDlg::OnBnClickedButton3()
{
	PressDigit(3);
}


void CMFCCalculatorDlg::OnBnClickedButton4()
{
	PressDigit(4);
}

void CMFCCalculatorDlg::OnBnClickedButton5()
{
	PressDigit(5);
}


void CMFCCalculatorDlg::OnBnClickedButton6()
{
	PressDigit(6);
}


void CMFCCalculatorDlg::OnBnClickedButton7()
{
	PressDigit(7);
}


void CMFCCalculatorDlg::OnBnClickedButton8()
{
	PressDigit(8);
}


void CMFCCalculatorDlg::OnBnClickedButton9()
{
	PressDigit(9);
}


void CMFCCalculatorDlg::OnBnClickedButton0()
{
	PressDigit(0);
}


void CMFCCalculatorDlg::PressDigit(int nDigit)
{
	if (m_bNew) {
		m_bNew = false;
		m_csRes = _T("0");
	}
	else
		UpdateData(TRUE);
	
	UpdateData(TRUE);
	CString str;
	str.Format(_T("%d"), nDigit);

	if (m_csRes == CString(_T("0"))) 
		m_csRes = _T("");

	m_csRes += str;

	UpdateData(FALSE);

}


void CMFCCalculatorDlg::PressOp(int nType)
{
	m_nOpType = nType;
	m_csOpA = m_csRes;
	m_csRes = _T("0");
	UpdateData(FALSE);

}


void CMFCCalculatorDlg::OnBnClickedButtonA()
{
	PressOp(OP_TYPE_ADD);
}


void CMFCCalculatorDlg::OnBnClickedButtonS()
{
	PressOp(OP_TYPE_SUB);
}


void CMFCCalculatorDlg::OnBnClickedButtonM()
{
	PressOp(OP_TYPE_MUL);
}


void CMFCCalculatorDlg::OnBnClickedButtonD()
{
	PressOp(OP_TYPE_DIV);
}


void CMFCCalculatorDlg::OnBnClickedButtonCala()
{
	m_csOpB = m_csRes;
	int nOpA = _tstoi(m_csOpA);
	int nOpB = _tstoi(m_csOpB);
	int nRes = 0;
	switch (m_nOpType)
	{
	case OP_TYPE_ADD:
		nRes = nOpA + nOpB;
		break;
	case OP_TYPE_SUB:
		nRes = nOpA - nOpB;
		break;
	case OP_TYPE_MUL:
		nRes = nOpA * nOpB;
		break;
	case OP_TYPE_DIV:
		nRes = nOpA / nOpB;
		break;
	}

	m_csRes.Format(_T("%d"), nRes);
	UpdateData(FALSE);
	m_nOpType = OP_TYPE_NONE;
	m_bNew = true;





}


void CMFCCalculatorDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
}
