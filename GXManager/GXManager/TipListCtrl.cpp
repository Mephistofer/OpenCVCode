// TipListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TipListCtrl.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern int g_nhighlightFlag;

/////////////////////////////////////////////////////////////////////////////
// CTipListCtrl

CTipListCtrl::CTipListCtrl() : m_nItem(-1), m_nSubItem(-1), m_bEnableTips(FALSE),m_bEnableDrag(FALSE)
{
	m_nDownItem = -1;
	m_nDownSubItem = -1;
	m_nTestGroupId = -1;
	m_nItemHeight = 20;

	m_rgbTextBgrColor = RGB(0xFF,0xFF,0xFF);//显示颜色白色
	m_rgbTextColor = RGB(22,162,114);   //字体颜色设为淡绿色

	m_nFontHeight = 16;
	m_nFontWidth = 0;
	memset(m_check, 0, sizeof(BOOL)*CHECK_NUM);
	m_bEditFlag = FALSE;
	m_bDlgFlag = FALSE;
	m_nPosArrow = 0; //初始化必须为0， 否则第一次向上出问题 (yjzhang 2010-09-28)
	m_nPos = 0;
	m_rtT = CRect(0,0,0,0);
	m_bInsert = TRUE;
	m_nLeft = 30;
	//EnableTips();
}

CTipListCtrl::~CTipListCtrl()
{
}


BEGIN_MESSAGE_MAP(CTipListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CTipListCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_VSCROLL()
	//ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
	ON_WM_HSCROLL()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_NCCALCSIZE()
	ON_WM_CTLCOLOR()
	//ON_WM_MOUSEWHEEL()
	//ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CTipListCtrl message handlers

void CTipListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	try
	{	
		if(m_bEnableTips)
		{
			CString str=_T("");
			LVHITTESTINFO lvhti;	
			// 判断鼠标当前所在的位置(行, 列)
			lvhti.pt = point;	
			SubItemHitTest(&lvhti);	
			// 如果鼠标移动到另一个单元格内, 则进行处理; 否则, 不做处理
			if((lvhti.iItem != m_nItem) || (lvhti.iSubItem != m_nSubItem))
			{
				// 保存当前鼠标所在的(行,列)
				m_nItem = lvhti.iItem;
				m_nSubItem = lvhti.iSubItem;			
				// 如果鼠标移动到一个合法的单元格内,则显示新的提示信息
				// 否则, 不显示提示
				if((m_nItem != -1) && (m_nSubItem != -1))
				{
					//获得当前单元格的文字信息, 并设置为新的提示信息
					str = GetItemText(m_nItem ,m_nSubItem);				
					m_toolTip.AddTool(this, str);
					// 显示提示框
					m_toolTip.Pop();
				}	
				else
				{
					m_toolTip.AddTool(this, _T(""));
					m_toolTip.Pop();
				}
			}
		}
		CListCtrl::OnMouseMove(nFlags, point);
	}//try end
	catch (...)
	{
	}
}

BOOL CTipListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	try
	{
		if(::IsWindow(m_toolTip.GetSafeHwnd()))
		{
			m_toolTip.RelayEvent(pMsg);
		}	
		return CListCtrl::PreTranslateMessage(pMsg);
	}//try end
	catch (...)
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::PreTranslateMessage() catch an exception,GetLastError=[%d]",GetLastError());
		return FALSE;
	}
}


void CTipListCtrl::PreSubclassWindow() 
{	
	try
	{
		ModifyStyle(0,LVS_OWNERDRAWFIXED); //让List能够设置行高 (yjzhang 2010-08-26)
		HWND   hHeader;   
		GetDlgItem(0,&hHeader);			//HeaderCtrl作为ListCtrl的子窗口,并且ID为0 
		//GetHeaderCtrl()->m_hWnd;
		ASSERT(hHeader!=NULL);   
		m_wndMyHeader.SubclassWindow(hHeader);   //子类化 
		CListCtrl::PreSubclassWindow();
	}
	catch (...)
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::PreSubclassWindow() catch an exception,GetLastError=[%d]",GetLastError());
	}
}

void CTipListCtrl::OnDestroy() 
{
	CListCtrl::OnDestroy();
	// listctrl销毁时, 同时销毁 tooltipctrl
	m_toolTip.DestroyWindow();
	m_toolTip.Detach();
}

BOOL CTipListCtrl::EnableTips()
{
	try
	{	
		EnableToolTips(TRUE);
		// 创建tooltip控件
		m_bEnableTips = m_toolTip.Create(this, TTS_ALWAYSTIP);	
		if(m_bEnableTips)
		{
			m_toolTip.Activate(TRUE);
			m_toolTip.SetDelayTime(TTDT_INITIAL, 0);
		}	
		return m_bEnableTips;
	}//try end
	catch (...)
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::EnableTips() catch an exception,GetLastError=[%d]",GetLastError());
		return FALSE;
	}

}

// 
// void CTipListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	try
// 	{	
// 		NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
// 		*pResult = CDRF_DODEFAULT;
// 		if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
// 		{
// 			*pResult = CDRF_NOTIFYITEMDRAW;
// 		}
// 		else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
// 		{				
// 			*pResult = CDRF_NOTIFYSUBITEMDRAW;
// 		}
// 		else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
// 		{	
// 			int nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );//ZJAT_0002
// 			COLORREF clrNewTextColor, clrNewBkColor;  			
// 			clrNewTextColor = m_rgbTextColor;
// 			//ZJAT_0002 BEGIN
// 			clrNewBkColor = m_rgbTextClickBgrColor;//显示颜色为品蓝	
// 			pLVCD->clrText = clrNewTextColor;
// 			if(GetItemState(nItem,LVIS_FOCUSED)==LVIS_FOCUSED /* &&g_nhighlightFlag ==1*/)
// 			{
// 				pLVCD->clrTextBk = clrNewBkColor;
// 			}
// 			//ZJAT_0002 END
// 			*pResult = CDRF_DODEFAULT;       
// 		}
// 	}//try end
// 	catch (...)
// 	{
// 		tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::OnNMCustomdraw catch an exception,GetLastError=[%d]",GetLastError());		
// 	}
// }


/*----------------------------------设置启用列表拖动标志-------------------------------------
AUTHOR:weisun 
DateTime:20100106
函数功能:设置启用列表拖动标志
参数说明：无
返回值说明：无
-------------------------------------------------------------------------------------------------*/
BOOL CTipListCtrl::EnableItemDrag()
{
	try
	{
		m_bEnableDrag = TRUE;
		return TRUE;
	}
	catch (...)
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::EnableItemDrag() Catch An Exception,GetLastError=[%d]",GetLastError());
		return FALSE;
	}
}


void CTipListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	ModifyStyle(WS_HSCROLL | WS_VSCROLL,0,0);			//禁用水平滚动条和垂直滚动条
//DEL 	CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
//DEL }
//DEL 
//DEL void CTipListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	if((nSBCode == SB_PAGEDOWN) || (nSBCode == SB_PAGEUP) || (nSBCode == SB_LINEDOWN) || (nSBCode == SB_LINEUP))   
//DEL 	 {   
//DEL 		  LockWindowUpdate();   
//DEL 		  CListCtrl::OnVScroll(nSBCode,  nPos,  pScrollBar);   
//DEL 		  UnlockWindowUpdate();   
//DEL 		  return;   
//DEL 	 }   
//DEL 	 CListCtrl::OnVScroll(nSBCode,  nPos,  pScrollBar);
// 
//  	CSize   sizeClient; 
//  	CSize   sizeSb; 
// 	//GetClientSize(sizeClient,   sizeSb); 
// 
//  	BOOL   hasHorzBar(FALSE); 
//  	BOOL   hasVertBar(FALSE); 
//  //	CheckScrollBars(hasHorzBar,hasVertBar); 
//  	if   (hasHorzBar) 
// 	lpncsp-> rgrc[0].bottom   +=   GetSystemMetrics(SM_CYHSCROLL); 
//  	else 
//  	lpncsp-> rgrc[0].bottom   +=   GetSystemMetrics(SM_CYHSCROLL)-sizeSb.cy; 

    CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);  
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-09-28
函数功能：响应滚动条
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//垂直滚动时发送给父窗口DLG隐藏ITM=-1的按钮
	
	//::SendMessage(GetParent()->m_hWnd,WM_MOVEBUTTON,NULL,NULL);
	try
	{	
		CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
		
		SCROLLINFO   scroinf; 
		this-> GetScrollInfo(SB_VERT, &scroinf, SIF_ALL);	
		int nMaxPos = scroinf.nMax - scroinf.nPage + 1;
		
		//AfxMessageBox("kk");
		if (m_edit.m_hWnd != NULL)
		{
			CRect rt, rt2;
			m_edit.GetWindowRect(rt);
			
			GetWindowRect(rt2);
			rt.top -= rt2.top+2 ;
			rt.bottom -= rt2.top+2;
			rt.left -= rt2.left+2;
			rt.right -= rt2.left+2;
			
			if (nSBCode == SB_PAGEDOWN )
			{
				rt.top -= m_nItemHeight * (scroinf.nPos - m_nPosArrow);
				rt.bottom -=m_nItemHeight* (scroinf.nPos - m_nPosArrow);			
			}
			
			if (nSBCode == SB_PAGEUP)
			{
				rt.top += m_nItemHeight* (m_nPosArrow-scroinf.nPos);
				rt.bottom +=m_nItemHeight* (m_nPosArrow - scroinf.nPos);			
			}
			
			if (nSBCode == SB_LINEDOWN && scroinf.nPos <=  nMaxPos && m_nPosArrow != scroinf.nPos)
			{			
				rt.top -= m_nItemHeight;
				rt.bottom -=m_nItemHeight;
			}
			
			if(nSBCode == SB_LINEUP && (scroinf.nPos >= scroinf.nMin &&m_nPosArrow != scroinf.nPos))
			{
				rt.top += m_nItemHeight;
				rt.bottom +=m_nItemHeight;
			}
			int n;
			(nPos > m_nPos) ? n = nPos - m_nPos : n = m_nPos - nPos;
			
			if (nSBCode == SB_THUMBTRACK && n == 1)
			{
				if (nPos > m_nPos)
				{
					rt.top -= m_nItemHeight;
					rt.bottom -=m_nItemHeight;
				}
				else 
				{
					rt.top += m_nItemHeight;
					rt.bottom +=m_nItemHeight;
				}
			}
			
			m_nPosArrow = scroinf.nPos;
			if (nSBCode != SB_THUMBPOSITION && nSBCode != SB_ENDSCROLL)
				m_nPos = nPos;
			
			m_edit.MoveWindow(rt);
		}
		Invalidate();
	}
	catch (...)
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::OnVScroll() catch an exception,GetLastError=[%d]",GetLastError());
	}
}

void CTipListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//::SendMessage(GetParent()->m_hWnd,WM_MOVEBUTTON,NULL,NULL);

	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}


/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置Header的高度
输入参数：----          
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetListHeaderHeight(double fwHeigt)
{
	m_wndMyHeader.SetListHeaderHeight(fwHeigt);
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置Header文本的高度
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetListHeaderTextHeight(int nHeight)
{
	m_wndMyHeader.SetListHeaderTextHeight(nHeight);
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置Header文本的高度
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetListHeaderTextWidth(int nWidth)
{
	m_wndMyHeader.SetListHeaderTextWidth(nWidth);
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置Header的颜色
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetListHeaderColor(int red, int green, int blue)
{
	m_wndMyHeader.SetListHeaderColor(red, green, blue);
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置Header文本的颜色
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetListHeaderTextColor(COLORREF rgb)
{
	m_wndMyHeader.SetListHeaderTextColor(rgb);
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置文本的颜色
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetListTextColor(COLORREF rgb)
{
	m_rgbTextColor = rgb;
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置文本点击后的背景
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetListTextBgrColor(COLORREF rgb)
{
	m_rgbTextBgrColor = rgb;
}


/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-26
函数功能：设置文本每一行的高度
输入参数：----          
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetItemHeight(UINT nHeight)
{
	try
	{
		m_nItemHeight = nHeight;
		CRect rcWin;
		GetWindowRect(&rcWin);
		WINDOWPOS wp;
		wp.hwnd = m_hWnd;
		wp.cx = rcWin.Width();
		wp.cy = rcWin.Height();
		wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
		SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
	}
	catch (...)
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::SetItemHeight() catch an exception,GetLastError=[%d]",GetLastError());
	}
}

void  CTipListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{	
	lpMeasureItemStruct->itemHeight = m_nItemHeight;	
} 

void CTipListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-10-14
函数功能：设置text文本的字体高度
输入参数：nHeight --- 字体的高度
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetListTextFrontHeight(UINT nHeight)
{
	m_nFontHeight = nHeight;
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-10-14
函数功能：设置编辑框标志
输入参数：bEdit --- TRUE为存在，FALSE为不存在
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetEditFlag(BOOL bEdit)
{
	m_bEditFlag = bEdit;
}

/*----------------------------------响应鼠标左键被弹起事件-------------------------------------
AUTHOR:weisun 
DateTime:20100106
函数功能:响应鼠标左键被弹起事件
参数说明：无
返回值说明：无
-------------------------------------------------------------------------------------------------*/
void CTipListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	try
	{
		if (m_bEnableDrag)
		{
			LVHITTESTINFO lvhti;	
			lvhti.pt = point;	
			SubItemHitTest(&lvhti);	
			int nUpItem = lvhti.iItem;
			int nUpSubItem = lvhti.iSubItem;
			int i = 0;
			if((nUpItem != -1) && (m_nDownItem != -1) && (nUpItem != m_nDownItem))
			{
				CString	strDownItemText = GetItemText(m_nDownItem,0);
				CString strUpItemText = GetItemText(nUpItem,0);
				CString strItemText = _T("");
				if (nUpItem > m_nDownItem)
				{
					SetItemText(nUpItem,0,strDownItemText);
					for (i= m_nDownItem;i < nUpItem;i++)
					{
						if (i+1 == nUpItem)
							strItemText = strUpItemText;
						else
							strItemText = GetItemText(i+1,0);
						
						SetItemText(i,0,strItemText);
					}
				}
				else
				{
					SetItemText(nUpItem,0,strDownItemText);
					for (i= m_nDownItem;i > nUpItem;i--)
					{
						if (i-1 == nUpItem)
							strItemText = strUpItemText;
						else
							strItemText = GetItemText(i-1,0);
						
						SetItemText(i,0,strItemText);
					}
				}
			}
		}
		CListCtrl::OnLButtonUp(nFlags, point);
	}
	catch (...) 
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::OnLButtonUp() Catch An Exception,GetLastError=[%d]",GetLastError());
	}
}


void CTipListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	try
	{
		TCHAR lpBuffer[256];
		
		LV_ITEM lvi;
		
		lvi.mask = LVIF_TEXT | LVIF_PARAM ;
		lvi.iItem = lpDrawItemStruct->itemID ;
		lvi.iSubItem = 0;
		lvi.pszText = lpBuffer ;
		lvi.cchTextMax = sizeof(lpBuffer);
		VERIFY(GetItem(&lvi));
		
		LV_COLUMN lvc, lvcprev ;
		::ZeroMemory(&lvc, sizeof(lvc));
		::ZeroMemory(&lvcprev, sizeof(lvcprev));
		lvc.mask = LVCF_WIDTH | LVCF_FMT;
		lvcprev.mask = LVCF_WIDTH | LVCF_FMT;
		
		CDC* pDC;
		pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
		CRect rtClient;
		GetClientRect(&rtClient);
		CRect rcItem; 
		CRect rt1, rt2;
		BOOL bTag = FALSE;		
		
		for (int nCol=0; GetColumn(nCol, &lvc); nCol++)
		{
			if ( nCol > 0 )
			{
				// Get Previous Column Width in order to move the next display item
				GetColumn(nCol-1, &lvcprev) ;
				lpDrawItemStruct->rcItem.left += lvcprev.cx ;
				lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left;
			}
			
			
			if (!GetSubItemRect(lpDrawItemStruct->itemID,nCol,LVIR_LABEL,rcItem))  
				continue;  
			
			::ZeroMemory(&lvi, sizeof(lvi));
			lvi.iItem = lpDrawItemStruct->itemID;
			lvi.mask = LVIF_TEXT | LVIF_PARAM;
			lvi.iSubItem = nCol;
			lvi.pszText = lpBuffer;
			lvi.cchTextMax = sizeof(lpBuffer);
			VERIFY(GetItem(&lvi));
			CRect rcTemp;
			rcTemp = rcItem;
			
			if (nCol==0)
			{
				rcTemp.left -=2;
			}		
			
			COLORREF color;
			if ( lpDrawItemStruct->itemState & ODS_SELECTED )
			{
				//rcTemp.bottom -=10;
				//m_ErrDlg.m_nSelect = lvi.iItem;
				pDC->FillSolidRect(&rcTemp, MANAGER_CLICK/*GetSysColor(COLOR_HIGHLIGHT)*/) ;
				pDC->SetTextColor(MANAGER_WHITE);
			}
			else
			{
				pDC->FillSolidRect(rcTemp,m_rgbTextBgrColor);
				color = MANAGER_BLACK;
				pDC->SetTextColor(color); //为了换肤 (yjzhang 2010-09-18)
			}
			
			pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
			
			UINT uFormat = DT_LEFT; //字体排在中间
			
			TEXTMETRIC metric;
			pDC->GetTextMetrics(&metric);
			int ofst;
			ofst = rcItem.Height() - metric.tmHeight;
			rcItem.OffsetRect(0,ofst/2);
			
			if (m_check[lvi.iItem] == RED)
			{
				color = MANAGER_RED; //故障时红的颜色 (yjzhang 2010-08-25)
				pDC->SetTextColor(color);
			}
			
			if (m_check[lvi.iItem] == GRAY)
			{
				color = RGB(200,200,200); //无效时灰的颜色 (yjzhang 2010-09-19)
				pDC->SetTextColor(color);
			}
			CFont * nOldFont;
			if (m_EditFont.m_hObject == NULL)
			{
				m_EditFont.CreateFont(m_nFontHeight, // nHeight 
					0, // nWidth 
					0, // nEscapement 
					0, // nOrientation 
					400, // nWeight 
					FALSE, // bItalic 
					FALSE, // bUnderline 
					0, // cStrikeOut 
					GB2312_CHARSET/*ANSI_CHARSET*/, // nCharSet 
					OUT_DEFAULT_PRECIS, // nOutPrecision 
					CLIP_DEFAULT_PRECIS, // nClipPrecision 
					DEFAULT_QUALITY, // nQuality 
					DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
					_T("宋体")); // lpszFac 
			}
				//m_EditFont.CreateFont(m_nFontHeight,0,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("宋体"));//创建字体
			nOldFont = pDC->SelectObject(&m_EditFont);
			rcItem.top -= 1;   //向上偏移一个像素
			rcItem.left += m_nLeft; //向右偏移m_nLeft像素
			DrawText(lpDrawItemStruct->hDC, lpBuffer, wcslen(lpBuffer),
				&rcItem, uFormat);
			CString str;
			str.Format(_T("%s"),lpBuffer);
			
			if (str == "硬件版本号")
			{
				rt1 = rcItem;
				rt1.top -=4;
				rt1.bottom -= 4;
				rt1.right += 1;
				rt1.left -=1;
				
				bTag = TRUE;
			}
			if (nCol == 2 && bTag)
			{
				int n = str.Replace(_T(" "), _T("\r\n"));
				bTag = FALSE;
				rt2 = rcItem;
				rt2.top -=4;
				rt2.bottom -= 4;
				rt2.right += 1;
				rt2.left = rt1.left;
				rt2.bottom = rt2.bottom + rt2.Height()*n - n;
				rt1.bottom = rt2.bottom;
				
				if (m_bInsert)
				{
					m_bInsert = FALSE;
					int nRow = lvi.iItem + 1;
					for (int k = 0; k < n; k++)
					{
						nRow = InsertItem(nRow, _T(""), -1);
					}
					
				}
				//rt2.left -=1;
				//m_ErrDlg.SetStaticTextColor(color);
				//m_ErrDlg.SetStaticFont(&m_EditFont);
				//m_ErrDlg.MoveWindow(rt2);
				
				//m_ErrDlg.SetErrTitle(rt1, "硬件版本号");
				//rtT.left = m_ErrDlg.m_startPoint.x;
				//rtT.right = 
				//	if (m_rtT == CRect(0,0,0,0))
				{
					m_rtT = rt2;
					m_rtT.left = rt1.Width();
					m_rtT.right = rt2.Width();			
				}
				
				//m_ErrDlg.SetErrNum(m_rtT,str);
				
			}	
			//SetBkColor(MANAGER_WHITE);
			
			pDC->SelectObject(nOldFont);
			//nFont.DeleteObject();		
			pDC->SelectStockObject(SYSTEM_FONT);		
	}
	if (m_bDlgFlag)
	{
		//m_ErrDlg.ShowWindow(SW_SHOW);
		//m_ErrDlg.Invalidate();
	}
	}
	catch (...) 
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::DrawItem() Catch An Exception,GetLastError=[%d]",GetLastError());
	}
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-10-14
函数功能：响应鼠标左键按下消息
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//m_ErrDlg.m_bBgr = FALSE;
	try
	{
		LVHITTESTINFO lvhti;	
		lvhti.pt = point;	
		SubItemHitTest(&lvhti);	
		
		if (m_bEnableDrag)
		{			
			m_nDownItem = lvhti.iItem;
			m_nDownSubItem = lvhti.iSubItem;
		}
		
		CRect rtEdit(0,0,1,1);
		if(m_edit.m_hWnd == NULL)
		{
			m_edit.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE|ES_READONLY|ES_WANTRETURN, rtEdit, this, IDC_LIST_EDIT);
			//	m_edit.		

			m_edit.SetFont(&m_EditFont);
		}
		m_edit.ShowWindow(SW_HIDE);
		
		if (m_bEditFlag && m_wndMyHeader.GetHeaderText(lvhti.iSubItem) == "硬件版本号" && lvhti.iItem != -1)
		{
			CRect rt;
			GetSubItemRect(lvhti.iItem, lvhti.iSubItem+1, LVIR_BOUNDS, rtEdit);
			//GetSubItemRect(lvhti.iItem, lvhti.iSubItem+2, LVIR_BOUNDS, rt);
			rtEdit.right = rtEdit.left + 170;		
			
			TCHAR szDate[256] = {'\0'};
			GetItemText(lvhti.iItem, lvhti.iSubItem, (LPTSTR)szDate, 256);
			CString str;
			str.Format(_T("%s"), szDate);
			int n = str.Replace(_T(" "), _T("\r\n"));		
			
			m_edit.SetWindowText(str);
			
			rtEdit.bottom = rtEdit.bottom + m_nFontHeight*n;
			m_edit.MoveWindow(rtEdit);
			m_edit.ShowWindow(SW_SHOW);
		}		
		CListCtrl::OnLButtonDown(nFlags, point);
	}
	catch (...)
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CTipListCtrl::OnLButtonDown() Catch An Exception,GetLastError=[%d]",GetLastError());
	}
}


HBRUSH CTipListCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CListCtrl::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (nCtlColor == CTLCOLOR_STATIC) //静态文本
	{
		//pDC->SetTextColor(MANAGER_FRAME);
		
		pDC->SetBkColor(MANAGER_WHITE);//字体背景色
		
		return CreateSolidBrush(MANAGER_WHITE); //控件背景色
		
	}
	return hbr;	
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-10-14
函数功能：设置多行list存在条件
输入参数：b --- TRUE为存在，FALSE为不存在
输出参数：----
返    回：void
***************************************************************************/
void CTipListCtrl::SetDlgFlag(BOOL b)
{
	m_bDlgFlag = b;
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-10-14
函数功能：响应鼠标滚轮事件
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
//void CTipListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	if (m_bDlgFlag)
//	{
//		//m_ErrDlg.ShowWindow(SW_HIDE);
//		CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
//		//m_ErrDlg.ShowWindow(SW_SHOW);
//	}
//	else
//	{
//		CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
//	}
//}

// void CTipListCtrl::OnNcPaint()
// {
// 	// TODO: Add your message handler code here
// 	Default();
// // 	CRect rcWnd;
// // 	GetClientRect(&rcWnd);
// // 	rcWnd.bottom +=3;
// // 	rcWnd.right +=5;
// // 	
//  	CWindowDC MyDC(this);
// 	MyDC.SetBkColor(TRANSPARENT);
// // 	COLORREF crPen = MANAGER_FRAME;
// // 	CPen aPen;
// // 	aPen.CreatePen(PS_SOLID, 4, crPen);
// // 	CPen* pOldPen = MyDC.SelectObject(&aPen);
// // 	CBrush* pOldBrush = static_cast<CBrush*>(MyDC.SelectStockObject(NULL_BRUSH));
// // 	
// // 	MyDC.Rectangle(&rcWnd);
// // 	MyDC.SelectObject(pOldPen);
// //  	MyDC.SelectObject(pOldBrush);
// 	CListCtrl::OnNcPaint();
// 	// do not call CListCtrl::OnNcPaint() for painting messages
// }
