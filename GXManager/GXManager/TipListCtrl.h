#if !defined(AFX_TIPLISTCTRL_H__07C518F5_7D5C_4FE4_8E74_1F020985A0E8__INCLUDED_)
#define AFX_TIPLISTCTRL_H__07C518F5_7D5C_4FE4_8E74_1F020985A0E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipListCtrl window
#include "CMyColorHeaderCtrl.h"

class CTipListCtrl : public CListCtrl
{
// Construction
public:
	enum {CHECK_NUM = 9000};
	enum COLOR {NORMAL, RED, GRAY};
	CTipListCtrl();
	CMyColorHeaderCtrl  m_wndMyHeader;
	void SetListHeaderHeight(double fwHeight);
	void SetListHeaderTextHeight(int nHeight);
	void SetListHeaderTextWidth(int nWidth);
	void SetListHeaderColor(int red, int green, int blue);
	void SetListHeaderTextColor(COLORREF rgb);
	void SetListTextColor(COLORREF rgb);
	void SetListTextBgrColor(COLORREF rgb);
	void SetItemHeight(UINT nHeight);
	void SetListTextFrontHeight(UINT nHeight);
	void SetEditFlag(BOOL bEdit);
	void SetDlgFlag(BOOL b);

	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	COLOR m_check[CHECK_NUM];
// Attributes
private:
	CToolTipCtrl	m_toolTip;
	int m_nItem;		// 鼠标所在的行
	int m_nSubItem;		// 鼠标所在的列
	BOOL m_bEnableTips;
	BOOL m_bEnableDrag; //启用列表ITEM拖动
	int m_nItemHeight;

	COLORREF m_rgbTextColor;   //文本颜色
	COLORREF m_rgbTextBgrColor;//文本背景色
	UINT m_nFontHeight;        //文本字体高度
	UINT m_nFontWidth;         //文本字体宽度

	CEdit m_edit; //提示数据
	BOOL m_bEditFlag;
	BOOL m_bDlgFlag;
	CFont m_EditFont; 
	UINT m_nPos;
	int m_nPosArrow;
	CRect m_rtT;
	BOOL m_bInsert;
// Operations
public:
	BOOL EnableTips();
	int m_nLeft;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipListCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	//}}AFX_VIRTUAL
	
// Implementation
public:
	int m_nTestGroupId;
	BOOL EnableItemDrag();
	int m_nDownItem;
	int m_nDownSubItem;
	virtual ~CTipListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTipListCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp); 
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//afx_msg void OnNcPaint();
	//}}AFX_MSG
	//afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPLISTCTRL_H__07C518F5_7D5C_4FE4_8E74_1F020985A0E8__INCLUDED_)
