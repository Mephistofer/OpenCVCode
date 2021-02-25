
// GXManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "PersonInfoDlg.h"
#include "PrintInfoDlg.h"
#include "StatisticDlg.h"
#include "InsertInfoDlg.h"

// CGXManagerDlg �Ի���
class CGXManagerDlg : public CDialog
{
// ����
public:
	CGXManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void InitCtrlListMain(void);

// �Ի�������
	enum { IDD = IDD_GXMANAGER_DIALOG };

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
public:
	CTipListCtrl m_ctrListMain;
	CButton m_buttEdit;
	CButton m_buttPrint;
	CDataModelList m_DataModelList;
private:
	BOOL AddNodeToXML();
	BOOL InitListXML(CString cstrXMLFile, CDataModelList * pList);
	HRESULT SortXMLFile(CString cstrXMLFile);
	CFont m_editFont;
	
	UINT m_nListRow;
	UINT m_nListCol;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnHdnBegindragListMain(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnHdnEndtrackListMain(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnHdnTrackListMain(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedEdit();
	afx_msg void OnLvnItemchangedListMain(NMHDR *pNMHDR, LRESULT *pResult);
	void UpdateListFirst(void);
	void UpdateList(void);
	afx_msg void OnBnClickedPrint();
	CButton m_buttStatistic;
	afx_msg void OnBnClickedStatistic();
	afx_msg void OnBnClickedInsert();
	CButton m_buttInsert;
	afx_msg void OnBnClickedDelete();
	CButton m_buttDelete;
};


