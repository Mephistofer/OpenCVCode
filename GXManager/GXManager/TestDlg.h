#pragma once



// CTestDlg 对话框

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestDlg();
	CDataModelList * m_pDataModelList;

// 对话框数据
	enum { IDD = IDD_DIALOG_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
