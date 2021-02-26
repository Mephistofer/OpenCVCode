#pragma once
#include "afxwin.h"

// CPersonInfoDlg 对话框

class CPersonInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPersonInfoDlg)

public:
	CPersonInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPersonInfoDlg();
	void SetParentWnd(CWnd* p);

// 对话框数据
	enum { IDD = IDD_GXMANAGER_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editName;
	CEdit m_editTel;
	CEdit m_editWork;
	CEdit m_editRemark;
	CEdit m_editRent;
	//CStatic m_staticNo1;
	//CStatic m_staticNo2;
	CString m_strName;
	CString m_strTel;
	CString m_strWork;
	CString m_strRemark;
	CString m_strNo;
	CString m_strRent;

	CDataModelList * m_pDataModelList;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CFont m_editFont;
	CFont m_StaticFont;
	CWnd * m_pParent;
	
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedEditOk();
	BOOL ModifyXML(CString strPath, CString cstrType);
	CComboBox m_comboBuild1;
	CComboBox m_comboBuild2;	
	CString m_strComboEdit1;
	CString m_strComboEdit2;
//	afx_msg void OnEnSetfocusEditPersonInfoName();
	afx_msg void OnCbnCloseupComboBuild1();
	afx_msg void OnCbnCloseupComboBuild2();
	afx_msg void OnPaint();
	CEdit m_editHouseNum;
};
