#if !defined(AFX_CMYCOLORHEADERCTRL_H__2E71C8EB_7F95_4D2C_8597_9925918B8843__INCLUDED_)
#define AFX_CMYCOLORHEADERCTRL_H__2E71C8EB_7F95_4D2C_8597_9925918B8843__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyColorHeaderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyColorHeaderCtrl window

class CMyColorHeaderCtrl : public CHeaderCtrl
{
// Construction
public:
	CMyColorHeaderCtrl();
	void SetListHeaderHeight(double fwHeight);
	void SetListHeaderTextHeight(int nHeight);
	void SetListHeaderTextWidth(int nWidth);
	void SetListHeaderTextColor(COLORREF rgb);
	void SetListHeaderColor(int red, int green, int blue);
	CString GetHeaderText(int nCol);

private:
	double m_fwHeight;          //title高度
	int    m_nHeaderTextHeight; //title文字的高度
	int    m_nHeaderTextWidth;  //title文字的宽度
	COLORREF m_rgbHeaderText;   //title文字的颜色
	int    m_redHeader;
	int    m_greenHeader;
	int    m_blueHeader;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyColorHeaderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyColorHeaderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyColorHeaderCtrl)
	afx_msg void OnPaint();
	afx_msg LRESULT OnLayout( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYCOLORHEADERCTRL_H__2E71C8EB_7F95_4D2C_8597_9925918B8843__INCLUDED_)
