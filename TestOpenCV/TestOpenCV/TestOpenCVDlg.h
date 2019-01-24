
// TestOpenCVDlg.h: 头文件
//

#pragma once


// CTestOpenCVDlg 对话框
class CTestOpenCVDlg : public CDialogEx
{
// 构造
public:
	CTestOpenCVDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTOPENCV_DIALOG };
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
public:
	afx_msg void OnBnClickedButtonPic();
	CEdit m_editPicPath;
	CEdit m_editVedioPath;
	afx_msg void OnBnClickedButtonPicPathChoose();
	afx_msg void OnBnClickedButtonVedioPathChoose();
private:
	CString m_strPicPathName;
	CString m_strVedioPathName;
public:
	afx_msg void OnBnClickedButtonVedio();
};
