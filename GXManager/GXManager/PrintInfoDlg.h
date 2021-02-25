#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "TestDlg.h"


// PrintInfoDlg 对话框

class PrintInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(PrintInfoDlg)

public:
	PrintInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PrintInfoDlg();
	void SetParentWnd(CWnd * p);
private:
	CFont m_editFont;
	CFont m_StaticFont;
	CWnd * m_pParent;

// 对话框数据
	enum { IDD = IDD_GXMANAGER_PRINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	void ClickArrow(BOOL b);

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboBuild1;
	CComboBox m_comboBuild2;
	CDateTimeCtrl m_dtTime;
	CEdit m_editName;
	//CEdit m_editSanitation;
	CEdit m_editTV;
	CEdit m_editRent;
	//CEdit m_editParking;
	CEdit m_editBodyFund;
	CEdit m_editRemark;
	CEdit m_editPreElec;
	CEdit m_editNowElec;
	CEdit m_editPerMonthElec;
	CEdit m_editPreWater;
	CEdit m_editNowWater;
	CEdit m_editPerMonthWater;
	CEdit m_editWuGuanFei;
	CDataModelList * m_pDataModelList;

	CString m_strName;
	CString m_strNo;
	CString m_strRent;
	CString m_strComboEdit1;
	CString m_strComboEdit2;
	CString m_strComboRentMonth;
	CString m_strTotal;
	CString m_strRealElec;
	CString m_strRealWater;
	CString m_strRealGas;
	CString m_strTotalElec;
	CString m_strTotalWater;
	CString m_strTotalGas;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnCloseupComboPrintBuild1();
	afx_msg void OnCbnCloseupComboPrintBuild2();
	CEdit m_editMaker;
	void InitPrintDlg(void);
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonPrint();
	HRESULT SaveXML(CString cstrXMLFile, CString strNO);
	HRESULT SaveData();
	CComboBox m_comboRentMonth;
	BOOL PrintList(void);
	CEdit m_editOther;
	void NumToBig(CString strTotal, CString& strBigTotal);
	//CEdit m_editPump;
	CEdit m_editManager;
	afx_msg void OnBnClickedButtonPre();
	afx_msg void OnBnClickedButtonNext();
	void DialogShow(CDataBuildInfoModel * pBuildData);
	afx_msg void OnCbnCloseupComboMonth();
	CEdit m_editPreGas;
	CEdit m_editNowGas;
	CEdit m_editPerMonthGas;
};
