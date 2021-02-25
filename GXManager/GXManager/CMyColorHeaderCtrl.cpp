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
	m_rgbHeaderText = RGB(22,62,114); //����ɫ
	//m_rgbHeaderText = RGB(255,62,114); //����ɫ
    //m_redHeader = 202,m_greenHeader = 221, m_blueHeader = 241;//��ʼ��ɫRGB	--����ɫ
	m_redHeader = 195,m_greenHeader =221, m_blueHeader = 253;//��ʼ��ɫRGB	--����ɫ
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
		nItem = GetItemCount();//�õ��м�����Ԫ 
		CRect tRect;
		CRect rtListHead;
		GetItemRect(0, &tRect);
		rtListHead = tRect;
		GetItemRect(nItem-1, &tRect);
		rtListHead.right = tRect.right; 

		CDC* pDC=&dc;

		//��������
		CBitmap bmpCanvas;
		CBitmap Bitmap;
		CBitmap* pOldBitmap;
		CDC ParentMemDC;	
		ParentMemDC.CreateCompatibleDC(pDC);
		bmpCanvas.CreateCompatibleBitmap(pDC,rtListHead.Width(),rtListHead.Height());
		pOldBitmap = ParentMemDC.SelectObject(&bmpCanvas); 

		CBrush brush; 
		brush.CreateSolidBrush(MANAGER_BLACK);//������ˢ
		CBrush* pOldBrush = ParentMemDC.SelectObject(&brush);
		ParentMemDC.FillRect(&rtListHead,&brush); //��䱳�� 
		ParentMemDC.SelectObject(pOldBrush);
		//brush.DeleteObject();
	
		for(int i = 0; i<=nItem ;i ++) 
		{ 				 
			int R = m_redHeader;
			int G = m_greenHeader;
			int B = m_blueHeader;
			
			if (i == nItem)
			{   //��ֹ�ƶ�list���ֺڶ� (yjzhang 2010-09-27)
				GetItemRect(i-1, &tRect);
				CRect nRect(tRect);
				nRect.left = nRect.right;
				nRect.right = 5000; // (yjzhang 2011-03-08)
				
				nRect.left++;//�����ָ��ߵĵط� 
				//�������屳�� 
				for(int j = tRect.top;j<=tRect.bottom;j++) 
				{ 
					nRect.bottom = nRect.top+1; 
					CBrush _brush; 
					_brush.CreateSolidBrush(RGB(R,G,B));//������ˢ 
					ParentMemDC.SelectObject(&_brush);
					ParentMemDC.FillRect(&nRect,&_brush); //��䱳�� 
					_brush.DeleteObject(); //�ͷŻ�ˢ 
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
			
			GetItemRect(i,&tRect);//�õ�Item�ĳߴ� 
			
			CRect nRect(tRect);//�����ߴ絽�µ�������
			nRect.left++;//�����ָ��ߵĵط� 
			//�������屳�� 
			for(int j = tRect.top;j<=tRect.bottom;j++) 
			{ 
				nRect.bottom = nRect.top+1; 
				CBrush _brush; 
				_brush.CreateSolidBrush(RGB(R,G,B));//������ˢ 
				ParentMemDC.SelectObject(&_brush);
				ParentMemDC.FillRect(&nRect,&_brush); //��䱳�� 
				_brush.DeleteObject(); //�ͷŻ�ˢ 
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
				_T("����")); // lpszFac 
			nOldFont = ParentMemDC.SelectObject(&nFont); 
			
			//ȡ������Ϣ
			HDITEM hdi;
			TCHAR  lpBuffer[256];
			hdi.mask = HDI_TEXT;
			hdi.pszText = lpBuffer;
			hdi.cchTextMax = 256;
			GetItem(i,&hdi);
			ParentMemDC.DrawText(hdi.pszText,&tRect,DT_CENTER); 
			ParentMemDC.SelectObject(nOldFont); 
			nFont.DeleteObject(); //�ͷ����� 			
		} 

		//����ͼƬ����Ļ
		pDC->BitBlt(rtListHead.left, rtListHead.top, rtListHead.Width(), rtListHead.Height(), &ParentMemDC, 0, 0, SRCCOPY);
		ReleaseDC(&ParentMemDC);	

	}//try end
	catch (...)
	{
		
	}

}

/***************************************************************************
�������ߣ�yjzhang
�������ڣ�2010-08-25
�������ܣ�����Header�ĸ߶�
���������----         
���������----
��    �أ�LRESULT
***************************************************************************/

LRESULT CMyColorHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )
{
	try
	{
		LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 	
		HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam; 	
		RECT *prc = hdl.prc; 	
		WINDOWPOS *pwpos = hdl.pwpos; 	
		int nHeight = (int)(pwpos->cy * m_fwHeight); //�ı�߶�,m_HeightΪ����	
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
�������ߣ�yjzhang
�������ڣ�2010-08-25
�������ܣ�����List��Header�߶�
���������ԭHeader*fwHeight          
���������----
��    �أ�void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderHeight(double fwHeight)
{
	m_fwHeight = fwHeight;
}

/***************************************************************************
�������ߣ�yjzhang
�������ڣ�2010-08-25
�������ܣ�����Header���ֵĸ߶�
���������----          
���������----
��    �أ�void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderTextHeight(int nHeight)
{
	m_nHeaderTextHeight = nHeight;
}

/***************************************************************************
�������ߣ�yjzhang
�������ڣ�2010-08-25
�������ܣ�����Header���ֵĿ��
���������----          
���������----
��    �أ�void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderTextWidth(int nWidth)
{
	m_nHeaderTextWidth = nWidth;
}

/***************************************************************************
�������ߣ�yjzhang
�������ڣ�2010-08-25
�������ܣ�����Header���ֵ���ɫ
���������----          
���������----
��    �أ�void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderTextColor(COLORREF rgb)
{
	m_rgbHeaderText = rgb;
}

/***************************************************************************
�������ߣ�yjzhang
�������ڣ�2010-08-25
�������ܣ�����Header����ɫ
���������----
���������----
��    �أ�void
***************************************************************************/
void CMyColorHeaderCtrl::SetListHeaderColor(int red, int green, int blue)
{
	m_redHeader = red;
	m_greenHeader = green;
	m_greenHeader = blue;
}

/***************************************************************************
�������ߣ�yjzhang
�������ڣ�2010-10-12
�������ܣ���ö�Ӧ�е�header��
���������col --- �к�
���������----
��    �أ�CString
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