#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TestDlg.h"

#define TYPE_ALL  0
#define TYPE_1    1
#define TYPE_2    2
#define TYPE_3    3

//#define ALL_COL  36
//#define ALL_ROW  17

// CStatisticDlg �Ի���

class CStatisticDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatisticDlg)

public:
	CStatisticDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatisticDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_STATISTIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboxBuild;
	CComboBox m_comboxYear;
	CComboBox m_comboxMonth;
	CTipListCtrl m_listStatistic;
	CDataModelList * m_pDataModelList;
	CFont m_editFont;
	CFont m_StaticFont;
	CString m_strSearchTime;
	CString m_strBuilding; //���ڼ�¼��ӡ����ʲô���� yjzhang 2012-07-01
	CString m_strBuildingCheck; //���ڼ�¼��Ҫ��ӡ��Щ����
private:
	void InitStatisticList(void);
	void UpdateList();
	void UpdateModelList();
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnCloseupComboStaBuild();
	afx_msg void OnCbnCloseupComboStaYear();
	afx_msg void OnCbnCloseupComboStaMonth();
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnBnClickedButtonStaticPrint();
	CButton  m_buttPrint;
	afx_msg void OnBnClickedButton2();
};
