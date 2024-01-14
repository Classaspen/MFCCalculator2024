
// MFCCalculatorDlg.h: 头文件
//

#pragma once
// 对话框数据

// CMFCCalculatorDlg 对话框
class CMFCCalculatorDlg : public CDialogEx
{
// 构造
public:
	CMFCCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CString m_csOpA;  //operator A
	CString m_csOpB;  //operator B
	int m_nOpType;    //type of operator
	bool m_bNew;
	bool m_NumNew = TRUE;

	void PressDigit(int Digit);  //数值键
	void PressOp(int nType);
	void Continuous_Calculation(int nType);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	// 计算结果显示
	CString m_csRes;
	afx_msg void OnBnClickedButtonA();
	afx_msg void OnBnClickedButtonS();
	afx_msg void OnBnClickedButtonM();
	afx_msg void OnBnClickedButtonD();
	afx_msg void OnBnClickedButtonCala();
	afx_msg void OnBnClickedButton10();
};
