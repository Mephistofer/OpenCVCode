// CMyColorHeaderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "CMyColorHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyColorHeaderCtrl

CMyColorHeaderCtrl::CMyColorHeaderCtrl()
{
	m_fwHeight = 1.5;
	m_nHeaderTextHeight = 15;
	m_nHeaderTextWidth = 0;
	m_rgbHeaderText = RGB(22,62,114); //深蓝色
	//m_rgbHeaderText = RGB(255,62,114); //深蓝色
    //m_redHeader = 202,m_greenHeader = 221, m_blueHeader = 241;//起始颜色RGB	--深蓝色
	m_redHeader = 195,m_greenHeader =221, m_blueHeader = 253;//起始颜色RGB	--深蓝色
}

CMyColorHeaderCtrl::~CMyColorHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyColorHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CMyColorHeaderCtrl)
	ON_WM_PAINT()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyColorHeaderCtrl message handlers

void CMyColorHeaderCtrl::OnPaint() 
{
	try
	{ 	
		CPaintDC dc(this); // device context for painting 

		int nItem; 
		nItem = GetItemCount();//得到有几个单元 
		CRect tRect;
		CRect rtListHead;
		GetItemRect(0, &tRect);
		rtListHead = tRect;
		GetItemRect(nItem-1, &tRect);
		rtListHead.right = tRect.right; 

		CDC* pDC=&dc;

		//画布定义
		CBitmap bmpCanvas;
		CBitmap Bitmap;
		CBitmap* pOldBitmap;
		CDC ParentMemDC;	
		ParentMemDC.CreateCompatibleDC(pDC);
		bmpCanvas.CreateCompatibleBitmap(pDC,rtListHead.Width(),rtListHead.Height());
		pOldBitmap = ParentMemDC.SelectObject(&bmpCanvas); 

		CBrush brush; 
		brush.CreateSolidBrush(MANAGER_BLACK);//创建画刷
		CBrush* pOldBrush = ParentMemDC.SelectObject(&brush);
		ParentMemDC.FillRect(&rtListHead,&brush); //填充背景 
		ParentMemDC.SelectObject(pOldBrush);
		//brush.DeleteObject();
	
		for(int i = 0; i<=nItem ;i ++) 
		{ 				 
			int R = m_redHeader;
			int G = m_greenHeader;
			int B = m_blueHeader;
			
			if (i == nItem)
			{   //防止移动list出现黑顶 (yjzhang 2010-09-27)
				GetItemRect(i-1, &tRect);
				CRect nRect(tRect);
				nRect.left = nRect.right;
				nRect.right = 5000; // (yjzhang 2011-03-08)
				
				nRect.left++;//留出分割线的地方 
				//绘制立体背景 
				for(int j = tRect.top;j<=tRect.bottom;j++) 
				{ 
					nRect.bottom = nRect.top+1; 
					CBrush _brush; 
					_brush.CreateSolidBrush(RGB(R,G,B));//创建画刷 
					ParentMemDC.SelectObject(&_brush);
					ParentMemDC.FillRect(&nRect,&_brush); //填充背景 
					_brush.DeleteObject(); //释放画刷 
					if (j < tRect.bottom/2)
					{
						R-=3;G-=3;B-=3; 
					}
					else
					{
						R+=2;G+=2;B+=2;
					}
					nRect.top = nRect.bottom; 
				} 
				break;				
			}
			
			GetItemRect(i,&tRect);//得到Item的尺寸 
			
			CRect nRect(tRect);//拷贝尺寸到新的容器中
			nRect.left++;//留出分割线的地方 
			//绘制立体背景 
			for(int j = tRect.top;j<=tRect.bottom;j++) 
			{ 
				nRect.bottom = nRect.top+1; 
				CBrush _brush; 
				_brush.CreateSolidBrush(RGB(R,G,B));//创建画刷 
				ParentMemDC.SelectObject(&_brush);
				ParentMemDC.FillRect(&nRect,&_brush); //填充背景 
				_brush.DeleteObject(); //释放画刷 
				if (j < tRect.bottom/2)
				{
					R-=3;G-=3;B-=3; 
				}
				else
				{
					R+=2;G+=2;B+=2;
				}
				nRect.top = nRect.bottom; 
			} 
			ParentMemDC.SetBkMode(TRANSPARENT); 
			tRect.top+=4; 
			CFont nFont ,* nOldFont; 
			ParentMemDC.SetTextColor(m_rgbHeaderText);	
			
			nFont.CreateFont(m_nHeaderTextHeight, // nHeight 
				m_nHeaderTextWidth, // nWidth 
				0, // nEscapement 
				0, // nOrientation 
				700, // nWeight 
				FALSE, // bItalic 
				FALSE, // bUnderline 
				0, // cStrikeOut 
				GB2312_CHARSET/*ANSI_CHARSET*/, // nCharSet 
				OUT_DEFAULT_PRECIS, // nOutPrecision 
				CLIP_DEFAULT_PRECIS, // nClipPrecision 
				DEFAULT_QUALITY, // nQuality 
				DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
				_T("宋体")); // lpszFac 
			nOldFont = ParentMemDC.SelectObject(&nFont); 
			
			//取文字信息
			HDITEM hdi;
			TCHAR  lpBuffer[256];
			hdi.mask = HDI_TEXT;
			hdi.pszText = lpBuffer;
			hdi.cchTextMax = 256;
			GetItem(i,&hdi);
			ParentMemDC.DrawText(hdi.pszText,&tRect,DT_CENTER); 
			ParentMemDC.SelectObject(nOldFont); 
			nFont.DeleteObject(); //释放字体 			
		} 

		//复制图片到屏幕
		pDC->BitBlt(rtListHead.left, rtListHead.top, rtListHead.Width(), rtListHead.Height(), &ParentMemDC, 0, 0, SRCCOPY);
		ReleaseDC(&ParentMemDC);	

	}//try end
	catch (...)
	{
		
	}

}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：处理Header的高度
输入参数：----         
输出参数：----
返    回：LRESULT
***************************************************************************/

LRESULT CMyColorHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )
{
	try
	{
		LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 	
		HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam; 	
		RECT *prc = hdl.prc; 	
		WINDOWPOS *pwpos = hdl.pwpos; 	
		int nHeight = (int)(pwpos->cy * m_fwHeight); //改变高度,m_Height为倍数	
		pwpos->cy = nHeight;	
		prc->top = nHeight; 
		return lResult; 
	}
	catch(...)
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CMyColorHeaderCtrl::OnLayout() catch an exception,GetLastError=[%d]",GetLastError());
		return 0;
	}
		

	
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置List的Header高度
输入参数：原Header*fwHeight          
输出参数：----
返    回：void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderHeight(double fwHeight)
{
	m_fwHeight = fwHeight;
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置Header文字的高度
输入参数：----          
输出参数：----
返    回：void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderTextHeight(int nHeight)
{
	m_nHeaderTextHeight = nHeight;
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置Header文字的宽度
输入参数：----          
输出参数：----
返    回：void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderTextWidth(int nWidth)
{
	m_nHeaderTextWidth = nWidth;
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置Header文字的颜色
输入参数：----          
输出参数：----
返    回：void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderTextColor(COLORREF rgb)
{
	m_rgbHeaderText = rgb;
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-08-25
函数功能：设置Header的颜色
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderColor(int red, int green, int blue)
{
	m_redHeader = red;
	m_greenHeader = green;
	m_greenHeader = blue;
}

/***************************************************************************
创建作者：yjzhang
创建日期：2010-10-12
函数功能：获得对应列的header名
输入参数：col --- 列号
输出参数：----
返    回：CString
***************************************************************************/
CString CMyColorHeaderCtrl::GetHeaderText(int nCol)
{
	try 
	{
		CString str;
		HDITEM hdi;
		TCHAR  lpBuffer[256];
		hdi.mask = HDI_TEXT;
		hdi.pszText = lpBuffer;
		hdi.cchTextMax = 256;
		GetItem(nCol,&hdi);
		str.Format(_T("%s"), hdi.pszText);
		return str;
	}
	catch(...)
	{
		//tracelog(LOG_ERR,MID_ZJMANAGER,"CMyColorHeaderCtrl::GetHeaderText() catch an exception,GetLastError=[%d]",GetLastError());
	    return _T("");
	}


}