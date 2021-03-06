// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GXManager.h"
#include "TestDlg.h"
#include "math.h"


// CTestDlg 对话框

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

void CTestDlg::OnPaint()
{

	CDataRentInfoModel *pInfoModel  = new CDataRentInfoModel[g_nTotalNum];
	int nRow = 0;
	for ( POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL;)
	{
		
		CDataModel * pData = m_pDataModelList->GetNext(pos);
		for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL; nRow++)
		{
			CDataBuildInfoModel * pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);
			pInfoModel[nRow].m_strNo = pBuildData->GetNO();
			for (POSITION pos = pBuildData->m_ptrRentInfoList.GetHeadPosition(); pos != NULL;)
			{
				CDataRentInfoModel *pRentData = pBuildData->m_ptrRentInfoList.GetNext(pos);
				if (pRentData->GetTitle() != _T("D201104"))
				{
					continue;
				}	

				pInfoModel[nRow].SetPerMonthElec(pRentData->GetPerMonthElec());
				pInfoModel[nRow].SetRealElec(pRentData->GetRealElec());
				pInfoModel[nRow].SetTotalElec(pRentData->GetTotalElec());
				pInfoModel[nRow].SetPerMonthWater(pRentData->GetPerMonthWater());
				pInfoModel[nRow].SetRealWater(pRentData->GetRealWater());
				pInfoModel[nRow].SetTotalWater(pRentData->GetTotalWater());

				pInfoModel[nRow].SetPerMonthGas(pRentData->GetPerMonthGas());
				pInfoModel[nRow].SetRealGas(pRentData->GetRealGas());
				pInfoModel[nRow].SetTotalGas(pRentData->GetTotalGas());

			    //pInfoModel[nRow].SetSanitation(pRentData->GetSanitation());
				pInfoModel[nRow].SetManager(pRentData->GetManager());
				pInfoModel[nRow].SetTV(pRentData->GetTV());
				pInfoModel[nRow].SetParking(pRentData->GetParking());
				//pInfoModel[nRow].SetPump(pRentData->GetPump());
				pInfoModel[nRow].SetBodyFund(pRentData->GetBodyFund());
				pInfoModel[nRow].SetOther(pRentData->GetOther());
				pInfoModel[nRow].SetRent(pRentData->GetRent());
				pInfoModel[nRow].SetTotal(pRentData->GetTotal());
				pInfoModel[nRow].SetWuGuanFei(pRentData->GetWuGuanFei());
			}
		}
	}
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);

	CDC* pDC=&dc;		

	//画布定义
	CBitmap bmpCanvas;
	CBitmap Bitmap;
	CBitmap* pOldBitmap;		

	CDC ParentMemDC;	
	ParentMemDC.CreateCompatibleDC(pDC);
	bmpCanvas.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	pOldBitmap = ParentMemDC.SelectObject(&bmpCanvas); 
	ParentMemDC.SetMapMode(MM_ISOTROPIC);
	ParentMemDC.SetViewportOrg(0, 0);
	ParentMemDC.SetWindowOrg(0,0);

	ParentMemDC.SetViewportExt(10, 10);
	ParentMemDC.SetWindowExt(10, 10);
	
	CPoint Origin(0, 40);
	int nHight = 18;
	int nWidth[ALL_ROW];
	for (int i = 0; i < 17; i++)
	{
		nWidth[i] = 60;
	}
	nWidth[0] = 40;
	nWidth[3] = 40;
	nWidth[6] = 48;
	nWidth[7] = 48;
	nWidth[8] = 48;
	nWidth[9] = 48;
	nWidth[12] = 48;
	nWidth[13] = 60;
	nWidth[14] = 65;
	nWidth[15] = 70;
	nWidth[16] = 80;
	int nFirstAdd = 0;
	int nHightTotal = ALL_COL*nHight;
	int nWidthTotal = 0;
	for (int i = 0; i < ALL_ROW; i++)
	{
		nWidthTotal += nWidth[i];
	}
	int nTotalNum = g_nTotalNum + 3;
	int nPage = nTotalNum%(ALL_COL-1) ? (nTotalNum/(ALL_COL-1)+1) :nTotalNum/(ALL_COL-1);
	UINT nNum = 0;
	for (int k = 1; k <= 1; k++)
	{
		//整个画板填充背景色
		CBrush  brushFrame(MANAGER_WHITE);
		//画边框和背景
		CBrush* pOldBrush = ParentMemDC.SelectObject(&brushFrame);
		ParentMemDC.FillRect(rect,&brushFrame);

		CPen cPen, *oldPan;
		cPen.CreatePen(PS_SOLID,0,MANAGER_BLACK);
		oldPan = ParentMemDC.SelectObject(&cPen);

		CFont  editFontTital;
		editFontTital.CreateFont(12, // nHeight 
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
		CFont *OldFont = ParentMemDC.SelectObject(&editFontTital);

		CFont numTotal;
		numTotal.CreateFont(14,
			0, // nWidth 
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

		CPoint pointS,pointE;
		pointS = Origin;
		pointE = CPoint(Origin.x + nWidthTotal, Origin.y);
		ParentMemDC.MoveTo(pointS);
		ParentMemDC.LineTo(pointE);

		pointS.y += nHight + nFirstAdd;
		pointE.y += nHight + nFirstAdd;
		ParentMemDC.MoveTo(pointS);
		ParentMemDC.LineTo(pointE);

		int nDrawRow = 0;
		if (k == nPage)
		{
			nDrawRow = g_nTotalNum - (k-1)*(ALL_COL-1);
		}
		else
		{
			nDrawRow = ALL_COL-1;
		}

		for (int i = 0; i < nDrawRow; i++)
		{
			pointS.y += nHight;
			pointE.y += nHight;
			ParentMemDC.MoveTo(pointS);
			ParentMemDC.LineTo(pointE);
		}

		pointS = Origin;
		if (k == nPage)
		{
			int nCol = g_nTotalNum - (k-1)*(ALL_COL-1) + 1;
			pointE = CPoint(Origin.x, Origin.y + nCol*nHight + nFirstAdd);
		}
		else
		{
		    pointE = CPoint(Origin.x, Origin.y + nHightTotal + nFirstAdd);
		}

		ParentMemDC.MoveTo(pointS);
		ParentMemDC.LineTo(pointE);
		for (int i = 0; i < ALL_ROW; i++)
		{
			pointS.x += nWidth[i];
			pointE.x += nWidth[i];
			ParentMemDC.MoveTo(pointS);
			ParentMemDC.LineTo(pointE);
		}
		int x = Origin.x + 5;
		int y = Origin.y + 4;
		ParentMemDC.TextOut(x, y, _T("电 单"));
		x += nWidth[0];
		ParentMemDC.TextOut(x, y, _T("实用度数"));
		x += nWidth[1];
		ParentMemDC.TextOut(x, y, _T("本月电费"));
		x += nWidth[2];
		ParentMemDC.TextOut(x, y, _T("水 单"));
		x += nWidth[3];
		ParentMemDC.TextOut(x, y, _T("实用方数"));
		x += nWidth[4];
		ParentMemDC.TextOut(x, y, _T("本月水费"));
		x += nWidth[5];
		ParentMemDC.TextOut(x, y, _T("安泰物业费"));
		x += nWidth[6];
		ParentMemDC.TextOut(x, y, _T("管理成本费"));
		x += nWidth[7];
		ParentMemDC.TextOut(x, y, _T("电视费"));
		//x += nWidth[8];
		//ParentMemDC.TextOut(x, y, _T("停车费"));
		//x += nWidth[9];
		//ParentMemDC.TextOut(x, y, _T("水泵加压"));
		x += nWidth[10];
		ParentMemDC.TextOut(x, y, _T("维修费"));
		x += nWidth[11];
		ParentMemDC.TextOut(x, y, _T(" 其他"));
		x += nWidth[12];
		ParentMemDC.TextOut(x, y, _T(" 房  租"));
		x += nWidth[13]; 
		ParentMemDC.TextOut(x, y, _T("  合  计"));
		x += nWidth[14];
		ParentMemDC.TextOut(x, y, _T("  房   号"));
		x += nWidth[15];
		ParentMemDC.TextOut(x, y, _T("  备   注"));

		for (int i = 0; (i < ALL_COL-1) && (nNum < g_nTotalNum); i++, nNum++)
		{
			x = Origin.x+3;
			y += nHight;
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetPerMonthElec());
			x += nWidth[0];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetRealElec());
			x += nWidth[1];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetTotalElec());
			x += nWidth[2];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetPerMonthWater());
			x += nWidth[3];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetRealWater());
			x += nWidth[4];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetTotalWater());
			x += nWidth[5];

			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetPerMonthGas());
			x += nWidth[6];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetRealGas());
			x += nWidth[7];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetTotalGas());
			x += nWidth[8];
			//ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetSanitation());
			//x += nWidth[6];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetWuGuanFei());
			x += nWidth[9];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetManager());
			x += nWidth[10];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetTV());
			x += nWidth[11];
			//ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetParking());
			//x += nWidth[12];
			//ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetPump());
			//x += nWidth[10];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetBodyFund());
			x += nWidth[12];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetOther());
			x += nWidth[13];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetRent());
			x += nWidth[14];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].GetTotal());
			x += nWidth[15];
			ParentMemDC.TextOut(x, y, pInfoModel[nNum].m_strNo);
		}
		if (nNum == g_nTotalNum)
		{
			x = Origin.x+3;
			y += nHight*2;
			ParentMemDC.TextOut(x, y, _T("统计信息"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("总电度数"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("总电费(元)"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("总水方数"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("总水费(元)"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("总房租(元)"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("总收入(元)"));
			y += nHight;
			pointS = Origin;
			pointS.y = y;
			pointE = CPoint(Origin.x + nWidthTotal, pointS.y);
			ParentMemDC.MoveTo(pointS);
			ParentMemDC.LineTo(pointE);
			x = Origin.x+3;
			y += nHight;
			x += 150;
			ParentMemDC.TextOut(x, y, _T("12344.6"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("2323.23"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("231313.23"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("1313.33"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("123435.33"));
			x += 150;
			ParentMemDC.TextOut(x, y, _T("121345.45"));
		}

		editFontTital.DeleteObject();		
		editFontTital.CreateFont(20, // nHeight 
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
		//CFont *OldFont = 
		ParentMemDC.SelectObject(&editFontTital);
		x = Origin.x + 130;
		y = Origin.y  - 55;
		CString strFrontTitle;
		strFrontTitle.Format( _T(" 深圳市宝安区国雄物业管理处"));
		ParentMemDC.TextOut(x, y, strFrontTitle);

		editFontTital.DeleteObject();
		editFontTital.CreateFont(12, // nHeight 
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
		ParentMemDC.SelectObject(&editFontTital);

		x = Origin.x + 908;
		y = Origin.y + nHightTotal+ 3;
		CString strPage;
		strPage.Format(_T("第 %d 页"), k);
		ParentMemDC.TextOut(x, y, strPage);

		editFontTital.DeleteObject();

		ParentMemDC.SelectObject(oldPan);
		ParentMemDC.SelectObject(pOldBrush);
		ParentMemDC.SelectObject(OldFont);

		double angel = (90/180.0)*3.1415926;
		//RotateAnyAngle(ParentMemDC,rect.Width(),rect.Height(),angel);

		//复制图片到屏幕
		//pDC->BitBlt(rect.left, rect.top, rect.Height(),rect.Width(), &ParentMemDC, 0, 0, SRCCOPY);
		pDC->BitBlt(rect.left, rect.top, rect.Width(),rect.Height(), &ParentMemDC, 0, 0, SRCCOPY);
		
		
	}
	ParentMemDC.SelectObject(pOldBitmap);
	ParentMemDC.DeleteDC();
	delete [] pInfoModel;
}
