// StatisticDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GXManager.h"
#include "StatisticDlg.h"


// CStatisticDlg 对话框

IMPLEMENT_DYNAMIC(CStatisticDlg, CDialog)

CStatisticDlg::CStatisticDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticDlg::IDD, pParent)
{

}

CStatisticDlg::~CStatisticDlg()
{
}

void CStatisticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STA_BUILD, m_comboxBuild);
	DDX_Control(pDX, IDC_COMBO_STA_YEAR, m_comboxYear);
	DDX_Control(pDX, IDC_COMBO_STA_MONTH, m_comboxMonth);
	DDX_Control(pDX, IDC_LIST_STATISTIC, m_listStatistic);
	DDX_Control(pDX, IDC_BUTTON_STATIC_PRINT, m_buttPrint);
}


BEGIN_MESSAGE_MAP(CStatisticDlg, CDialog)	
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_CBN_CLOSEUP(IDC_COMBO_STA_BUILD, &CStatisticDlg::OnCbnCloseupComboStaBuild)
	ON_CBN_CLOSEUP(IDC_COMBO_STA_YEAR, &CStatisticDlg::OnCbnCloseupComboStaYear)
	ON_CBN_CLOSEUP(IDC_COMBO_STA_MONTH, &CStatisticDlg::OnCbnCloseupComboStaMonth)
	ON_BN_CLICKED(IDC_BUTTON_STATIC_PRINT, &CStatisticDlg::OnBnClickedButtonStaticPrint)
END_MESSAGE_MAP()


// CStatisticDlg 消息处理程序
BOOL CStatisticDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_editFont.CreateFont(16, // nHeight 
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
		_T("楷体_GB2312")); // lpszFac 

	m_StaticFont.CreateFont(14, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		700, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		GB2312_CHARSET,//GB2312_CHARSET/*ANSI_CHARSET*/, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("宋体")); // lpszFac 

	m_comboxYear.SetFont(&m_editFont);
	m_comboxMonth.SetFont(&m_editFont);
	m_comboxBuild.SetFont(&m_editFont);
	InitStatisticList();

	return TRUE;
}
void CStatisticDlg::InitStatisticList(void)
{
	DWORD dwStyle = m_listStatistic.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮
	dwStyle |= LVS_EX_GRIDLINES;//网格线
	dwStyle |= LVS_EX_SUBITEMIMAGES;

	m_listStatistic.SetExtendedStyle(dwStyle);

	m_listStatistic.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_listStatistic.InsertColumn(1, _T("房号"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(2, _T("姓名"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(3, _T("实用电度数"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(4, _T("电费(元)"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(5, _T("实用水方数"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(6, _T("水费(元)"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(7, _T("实用天然气方数"), LVCFMT_CENTER, 150);
	m_listStatistic.InsertColumn(8, _T("天然气费(元)"), LVCFMT_CENTER, 150);
	m_listStatistic.InsertColumn(9, _T("房租(元)"), LVCFMT_CENTER, 110);
	m_listStatistic.InsertColumn(10, _T( "杂费(元)"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(11, _T( "合计(元)"), LVCFMT_CENTER, 110);	
	m_listStatistic.InsertColumn(12, _T( "备注"), LVCFMT_CENTER, 100);
	m_listStatistic.SetItemHeight(25);
	m_listStatistic.SetListHeaderHeight(1.2);		
	m_listStatistic.SetListHeaderTextHeight(16);
	m_listStatistic.m_nLeft = 10;

	//初始化栋数	
	for ( POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL;)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);

		m_comboxBuild.AddString(GetTitleLastNum(pData->GetTitle()));
	}
	m_comboxBuild.AddString(_T("全部"));
	m_comboxBuild.AddString(_T("3栋下"));
	m_comboxBuild.AddString(_T("3栋上"));
	m_comboxBuild.SetCurSel(0);

	//初始化年
	CString strTemp;
	SYSTEMTIME syTime;
	GetLocalTime(&syTime);
	WORD Year = syTime.wYear;
	if (syTime.wDay >= 20 && syTime.wMonth==12)
	{
		strTemp.Format(_T("%d"), Year+1);
		m_comboxYear.AddString(strTemp);
	}
	for (int i = Year; i >= 2011; i--)
	{
		strTemp.Format(_T("%d"), i);
		m_comboxYear.AddString(strTemp);
	}


	m_comboxYear.SetCurSel(0);

	//初始化月
	for (int i = 1; i <= 12; i++)
	{
		strTemp.Format(_T("%d"), i);
		m_comboxMonth.AddString(strTemp);
	}
	WORD Month = syTime.wMonth;
	if (syTime.wDay >= 20 && syTime.wMonth==12)
	{
		m_comboxMonth.SetCurSel(0);	
	}
	else
	{
		m_comboxMonth.SetCurSel(Month-1);
	}


	UpdateModelList();

	UpdateList();
	ShowWindow(SW_MAXIMIZE);
}

void CStatisticDlg::UpdateList()
{
	m_strBuildingCheck = _T("build");
	m_strSearchTime = _T("D");
	CString strTemp;
	if (m_comboxBuild.GetCurSel() != CB_ERR)
	{
		m_comboxBuild.GetLBText(m_comboxBuild.GetCurSel(), strTemp);
	}
	else
	{
		return;
	}
	
	if (strTemp != _T("全部") && strTemp != _T("3栋下") && strTemp != _T("3栋上"))
	{
		m_strBuildingCheck += strTemp;
		m_strBuilding = strTemp+_T("栋");
	}
	else
	{
		m_strBuildingCheck = strTemp;
		m_strBuilding = strTemp;
	}
	if (m_comboxYear.GetCurSel() != CB_ERR)
	{
		m_comboxYear.GetLBText(m_comboxYear.GetCurSel(), strTemp);
		m_strSearchTime += strTemp;
	}
	else
	{
		return;
	}
	m_comboxMonth.GetLBText(m_comboxMonth.GetCurSel(), strTemp);
	strTemp.Format(_T("%02d"), _wtoi(strTemp));
	m_strSearchTime += strTemp;

	CString strTotal;
	double fTotal = 0.0;
	double fLineTotal = 0.0;
	CString strOtherTotal;
	double fOtherTotal = 0.0;
	double fLineOtherTotal = 0.0;
	CString strWaterFundTotal;
	double fWaterFundTotal = 0.0;
	double fLineWaterFundTotal = 0.0;
	CString strElecFundTotal;
	double fElecFundTotal = 0.0;
	double fLineElecFundTotal = 0.0;
	CString strWaterNumTotal;
	double fWaterNumTotal = 0.0;
	double fLineWaterNumTotal = 0.0;
	CString strElecNumTotal;
	double fElecNumTotal = 0.0;
	double fLineElecNumTotal = 0.0;

	CString strGasFundTotal;
	double fGasFundTotal = 0.0;
	double fLineGasFundTotal = 0.0;
	CString strGasNumTotal;
	double fGasNumTotal = 0.0;
	double fLineGasNumTotal = 0.0;

	double fLineRent = 0.0;
	double fRentTotal = 0.0;
	CString strRentTotal;

	double fTemp1 = 0.0;
	double fTemp2 = 0.0;

	int nRow = 0;
	CString strTempthree;
	INT iTemp = 0;
	int nTotalNum = 0;
	for ( POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL;)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);
		if (m_strBuildingCheck != _T("全部"))
		{
			if (m_strBuildingCheck.Compare(_T("3栋下")) == 0 || m_strBuildingCheck.Compare(_T("3栋上")) == 0)
			{
				if (pData->GetTitle() != _T("build3"))
				{
					continue;
				}
			}
			else if (m_strBuildingCheck != pData->GetTitle())
			{
				continue;
			}			
		}
		for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL; )
		{
			CDataBuildInfoModel * pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);			
			strTempthree = GetHouseLastNum(pBuildData->GetNO());
			if (m_strBuildingCheck.Compare(_T("3栋下")) == 0)
			{
				iTemp = StrToInt(strTempthree);
				if(iTemp > 800)
				{
					break; //后面一定没有数据了
				}
			}
			else if (m_strBuildingCheck.Compare(_T("3栋上")) == 0)
			{
				iTemp = StrToInt(strTempthree);
				if(iTemp <= 800)
				{
					continue; //后面有
				}
			}
			m_listStatistic.InsertItem(nRow, _T(""), -1);
			m_listStatistic.SetItemText(nRow, 1, pBuildData->GetNO());
			for (POSITION pos = pBuildData->m_ptrRentInfoList.GetHeadPosition(); pos != NULL;)
			{
				CDataRentInfoModel *pRentData = pBuildData->m_ptrRentInfoList.GetNext(pos);
				if (pRentData->GetTitle() != m_strSearchTime)
				{
					continue;
				}

				//名字
				m_listStatistic.SetItemText(nRow, 2, pRentData->GetName());

				//实用电数
				fTemp1 = _wtof(pRentData->GetNowElec());
				fTemp2 = _wtof(pRentData->GetPreElec());
				fLineElecNumTotal = fTemp1 - fTemp2;
				fElecNumTotal += fLineElecNumTotal;
				strTemp.Format(_T("%.2f"),fLineElecNumTotal);
				m_listStatistic.SetItemText(nRow, 3, strTemp);

				//电费
				fLineElecFundTotal = fLineElecNumTotal * _wtof(pRentData->GetPerMonthElec());
				fElecFundTotal += fLineElecFundTotal;
				strTemp.Format(_T("%.2f"),fLineElecFundTotal);
				m_listStatistic.SetItemText(nRow, 4, strTemp);

				//实用水数
				fTemp1 = _wtof(pRentData->GetNowWater());
				fTemp2 = _wtof(pRentData->GetPreWater());
				fLineWaterNumTotal = fTemp1 - fTemp2;
				fWaterNumTotal += fLineWaterNumTotal;
				strTemp.Format(_T("%.2f"),fLineWaterNumTotal);
				m_listStatistic.SetItemText(nRow, 5, strTemp);

				//水费
				fLineWaterFundTotal = fLineWaterNumTotal * _wtof(pRentData->GetPerMonthWater());
				fWaterFundTotal += fLineWaterFundTotal;
				strTemp.Format(_T("%.2f"),fLineWaterFundTotal);
				m_listStatistic.SetItemText(nRow, 6, strTemp);


				//实用天然
				fTemp1 = _wtof(pRentData->GetNowGas());
				fTemp2 = _wtof(pRentData->GetPreGas());
				fLineGasNumTotal = fTemp1 - fTemp2;
				fGasNumTotal += fLineGasNumTotal;
				strTemp.Format(_T("%.2f"), fLineGasNumTotal);
				m_listStatistic.SetItemText(nRow, 7, strTemp);

				//天然气费
				fLineGasFundTotal = fLineGasNumTotal * _wtof(pRentData->GetPerMonthGas());
				fGasFundTotal += fLineGasFundTotal;
				strTemp.Format(_T("%.2f"), fLineGasFundTotal);
				m_listStatistic.SetItemText(nRow, 8, strTemp);

				//房租费
				fLineRent = _wtof(pRentData->GetRent());
				fRentTotal += fLineRent;
				m_listStatistic.SetItemText(nRow, 9, pRentData->GetRent());

				//杂费
				fLineOtherTotal = 0.0;
				//fLineOtherTotal = fLineRent + fLineElecFundTotal + fLineWaterFundTotal;
				//fTemp1 = _wtof(pRentData->GetSanitation());
				//fLineOtherTotal += fTemp1;
				fTemp1 = _wtof(pRentData->GetParking());
				fLineOtherTotal += fTemp1;
				fTemp1 = _wtof(pRentData->GetTV());
				fLineOtherTotal += fTemp1;
				fTemp1 = _wtof(pRentData->GetBodyFund());
				fLineOtherTotal += fTemp1;
				fTemp1 = _wtof(pRentData->GetOther());
				fLineOtherTotal += fTemp1;
				//fTemp1 = _wtof(pRentData->GetPump());
				//fLineOtherTotal += fTemp1;
				fTemp1 = _wtof(pRentData->GetManager());
				fLineOtherTotal += fTemp1;

				fTemp1 = _wtof(pRentData->GetWuGuanFei());
				fLineOtherTotal += fTemp1;

				fOtherTotal += fLineOtherTotal;
				strTemp.Format(_T("%.2f"), fLineOtherTotal);
				m_listStatistic.SetItemText(nRow, 10, strTemp);

				//总金额
				fLineTotal = _wtof(pRentData->GetTotal());
				fTotal += fLineTotal;
				m_listStatistic.SetItemText(nRow, 11, pRentData->GetTotal());

				//备注
				m_listStatistic.SetItemText(nRow, 12, pRentData->GetRemark());
			}
			nRow++;
			nTotalNum++;
		}		
	}
	g_nTotalNum = nTotalNum; //用于统计需要打印多少数据 yjzhang 2012-07-01
	strTotal.Format(_T("%.2f"), fTotal);
	strRentTotal.Format(_T("%.2f"), fRentTotal);
	strOtherTotal.Format(_T("%.2f"), fOtherTotal);
	strWaterFundTotal.Format(_T("%.2f"), fWaterFundTotal);
	strWaterNumTotal.Format(_T("%.2f"), fWaterNumTotal);
	strElecFundTotal.Format(_T("%.2f"), fElecFundTotal);
	strElecNumTotal.Format(_T("%.2f"), fElecNumTotal);

	strGasFundTotal.Format(_T("%.2f"), fGasFundTotal);
	strGasNumTotal.Format(_T("%.2f"), fGasNumTotal);

	m_listStatistic.InsertItem(nRow, _T(""), -1);
	for (int i = 1; i < 10; i++)
	{
	    m_listStatistic.SetItemText(nRow, i, _T("---------------"));
	}
	nRow++;

	m_listStatistic.InsertItem(nRow, _T(""), -1);
    m_listStatistic.SetItemText(nRow, 1, _T("统计信息"));
	m_listStatistic.SetItemText(nRow, 3, _T("总电度数"));
	m_listStatistic.SetItemText(nRow, 4, _T("总电费(元)"));
	m_listStatistic.SetItemText(nRow, 5, _T("总水方数"));
	m_listStatistic.SetItemText(nRow, 6, _T("总水费(元)"));

	m_listStatistic.SetItemText(nRow, 7, _T("总天然气方数"));
	m_listStatistic.SetItemText(nRow, 8, _T("总天然气费(元)"));


	m_listStatistic.SetItemText(nRow, 9, _T("总房租费(元)"));
	m_listStatistic.SetItemText(nRow, 10, _T("总杂费(元)"));
	m_listStatistic.SetItemText(nRow++, 11, _T("合计(元)"));

	m_listStatistic.InsertItem(nRow, _T(""), -1);
	m_listStatistic.SetItemText(nRow, 1, m_strBuilding);
	//m_listStatistic.SetItemText(nRow, 2, _T("------------"));
	m_listStatistic.SetItemText(nRow, 3, strElecNumTotal);
	m_listStatistic.SetItemText(nRow, 4, strElecFundTotal);
	m_listStatistic.SetItemText(nRow, 5, strWaterNumTotal);
	m_listStatistic.SetItemText(nRow, 6, strWaterFundTotal);

	m_listStatistic.SetItemText(nRow, 7, strGasNumTotal);
	m_listStatistic.SetItemText(nRow, 8, strGasFundTotal);

	m_listStatistic.SetItemText(nRow, 9, strRentTotal);
	m_listStatistic.SetItemText(nRow, 10, strOtherTotal);
	m_listStatistic.SetItemText(nRow++, 11, strTotal);
}

void CStatisticDlg::OnPaint()
{
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

	//整个画板填充背景色
	CBrush  brushFrame(MANAGER_CREAM);
	//画边框和背景
	CBrush* pOldBrush = ParentMemDC.SelectObject(&brushFrame);
	ParentMemDC.FillRect(rect,&brushFrame);
	ParentMemDC.SelectObject(pOldBrush);

	//复制图片到屏幕
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &ParentMemDC, 0, 0, SRCCOPY);
	ParentMemDC.SelectObject(pOldBitmap);
	ReleaseDC(&ParentMemDC);
}

void CStatisticDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	try
	{
		if (m_listStatistic.m_hWnd==NULL)
		{
			return;
		}
		CRect cr;
		GetClientRect(&cr);
		int left = cr.left + 25;
		int top = cr.top + 50;
		int right = cr.right - 25 ;
		int bottom = cr.bottom - 25;

		int nLength = right - left;
		int nHeight = bottom - top;

		m_listStatistic.MoveWindow(CRect(left, top, right, bottom));	

		if (nLength-920 < 100)
		{
			m_listStatistic.SetColumnWidth(12, 300);
		}
		else
		{
			m_listStatistic.SetColumnWidth(12, nLength-920);
		}


		//m_listStatistic.Invalidate(FALSE);
	}
	catch (...)
	{
	}
}

HBRUSH CStatisticDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC) //静态文本
	{
		pDC->SetBkMode(TRANSPARENT); 
		return  (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(MANAGER_BLUE);
	}	
	return hbr;
}

void CStatisticDlg::OnCbnCloseupComboStaBuild()
{
	m_listStatistic.DeleteAllItems();
	UpdateList();
	m_listStatistic.SetFocus();
}

void CStatisticDlg::OnCbnCloseupComboStaYear()
{
	m_listStatistic.DeleteAllItems();
	UpdateList();
	m_listStatistic.SetFocus();
}

void CStatisticDlg::OnCbnCloseupComboStaMonth()
{
	m_listStatistic.DeleteAllItems();
	UpdateList();
	m_listStatistic.SetFocus();
}


void CStatisticDlg::OnBnClickedButtonStaticPrint()
{
	//CTestDlg tdlg;
	//tdlg.m_pDataModelList = m_pDataModelList;
	//tdlg.DoModal();
	//return;

	CString TotalRealElec;
	CString TotalRealWater;
	CString TotalRealGas;
	CString TotalElec;
	CString TotalWater;
	CString TotalGas;
	CString TotalRent;
	CString TotalOther;
	CString Total;
	double fTotalRealElec = 0.0;
	double fTotalRealWater = 0.0;
	double fTotalRealGas = 0.0;
	double fTotalElec = 0.0;
	double fTotalWater = 0.0;
	double fTotalGas = 0.0;
	double fTotalRent = 0.0;
	double fTotalOther = 0.0;
	double fTotal = 0.0;
	CDataRentInfoModel *pInfoModel  = new CDataRentInfoModel[g_nTotalNum];
	CString strTempNo;
	int iTemp = 0;
	int nRow = 0;
	for ( POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL;)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);
		if (m_strBuildingCheck != _T("全部"))
		{
			if (m_strBuildingCheck.Compare(_T("3栋下")) == 0 || m_strBuildingCheck.Compare(_T("3栋上")) == 0)
			{
				if (pData->GetTitle() != _T("build3"))
				{
					continue;
				}
			}
			else if (m_strBuildingCheck != pData->GetTitle())
			{
				continue;
			}			
		}

		for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL;)
		{
			CDataBuildInfoModel * pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);
			strTempNo = GetHouseLastNum(pBuildData->GetNO());
			if (m_strBuildingCheck.Compare(_T("3栋下")) == 0)
			{
				iTemp = StrToInt(strTempNo);
				if(iTemp > 800)
				{
					break; //后面一定没有数据了
				}
			}
			else if (m_strBuildingCheck.Compare(_T("3栋上")) == 0)
			{
				iTemp = StrToInt(strTempNo);
				if(iTemp <= 800)
				{
					continue; //后面有
				}
			}

			pInfoModel[nRow].m_strNo = pBuildData->GetNO();
			for (POSITION pos = pBuildData->m_ptrRentInfoList.GetHeadPosition(); pos != NULL;)
			{
				CDataRentInfoModel *pRentData = pBuildData->m_ptrRentInfoList.GetNext(pos);
				if (pRentData->GetTitle() != m_strSearchTime)
				{
					continue;
				}	

				pInfoModel[nRow].SetPerMonthElec(pRentData->GetPerMonthElec());
				pInfoModel[nRow].SetRealElec(pRentData->GetRealElec());
				fTotalRealElec += _wtof(pRentData->GetRealElec());
				pInfoModel[nRow].SetTotalElec(pRentData->GetTotalElec());
				fTotalElec += _wtof(pRentData->GetTotalElec());

				pInfoModel[nRow].SetPerMonthWater(pRentData->GetPerMonthWater());
				pInfoModel[nRow].SetRealWater(pRentData->GetRealWater());
				fTotalRealWater += _wtof(pRentData->GetRealWater());
				pInfoModel[nRow].SetTotalWater(pRentData->GetTotalWater());
				fTotalWater += _wtof(pRentData->GetTotalWater());

				pInfoModel[nRow].SetPerMonthGas(pRentData->GetPerMonthGas());
				pInfoModel[nRow].SetRealGas(pRentData->GetRealGas());
				fTotalRealGas += _wtof(pRentData->GetRealGas());
				pInfoModel[nRow].SetTotalGas(pRentData->GetTotalGas());
				fTotalGas += _wtof(pRentData->GetTotalGas());

				//pInfoModel[nRow].SetSanitation(pRentData->GetSanitation());
				//fTotalOther += _wtof(pRentData->GetSanitation());

				pInfoModel[nRow].SetManager(pRentData->GetManager());
				fTotalOther += _wtof(pRentData->GetManager());
				pInfoModel[nRow].SetTV(pRentData->GetTV());
				fTotalOther += _wtof(pRentData->GetTV());
				//pInfoModel[nRow].SetParking(pRentData->GetParking());
				//fTotalOther += _wtof(pRentData->GetParking());
				//pInfoModel[nRow].SetPump(pRentData->GetPump());
				//fTotalOther += _wtof(pRentData->GetPump());
				pInfoModel[nRow].SetBodyFund(pRentData->GetBodyFund());
				fTotalOther += _wtof(pRentData->GetBodyFund());

				pInfoModel[nRow].SetWuGuanFei(pRentData->GetWuGuanFei());
				fTotalOther += _wtof(pRentData->GetWuGuanFei());

				pInfoModel[nRow].SetOther(pRentData->GetOther());
				fTotalOther += _wtof(pRentData->GetOther());
				pInfoModel[nRow].SetRent(pRentData->GetRent());
				fTotalRent += _wtof(pRentData->GetRent());
				pInfoModel[nRow].SetTotal(pRentData->GetTotal());
				fTotal += _wtof(pRentData->GetTotal());
			}
			nRow++; //重要
		}
	}	

	CPoint Origin(0, 40);
	int nHight = 18;
	int nWidth[ALL_ROW];
	for (int i = 0; i < ALL_ROW; i++)
	{
		nWidth[i] = 60;
	}
	nWidth[0] = 40;
	nWidth[3] = 40;
	nWidth[8] = 60;
	nWidth[9] = 48;
	//nWidth[10] = 48;
	nWidth[11] = 48;
	nWidth[12] = 48;
	nWidth[13] = 48;
	nWidth[14] = 60;
	nWidth[15] = 65;
	nWidth[16] = 70;
	//nWidth[17] = 80;
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

	TCHAR szprinter[800];	
	TCHAR *szDevice,*szDriver,*szOutput;	

	//定义一个打印作业	
	static DOCINFO di={sizeof(DOCINFO),_T("printer"),NULL};	

	//得到设备字符串存入数组szprinter中	
	//GetProfileString(_T("windows"),_T("device"),_T(",,,"),szprinter,80);
	g_cfg.getStaticPrinterAddr(szprinter);
	//	GetProfileString("MCI Extensions.BAK","aif",",,,",szprinter,80);

	//将设备字符串分解	
	WCHAR *pszResult = NULL; 
	//szDevice=wcstok_s(szprinter,_T(","), &pszResult);
	if(NULL != (szDevice=wcstok_s(szprinter,_T(","), &pszResult)) &&		
		NULL != (szDriver=wcstok_s(pszResult,_T(","), &pszResult)) &&		
		NULL != (szOutput=wcstok_s(pszResult,_T(","), &pszResult)))
	{
		CDC ParentMemDC;
		//创建一个打印机设备句柄		
		if((ParentMemDC.CreateDC(szDriver,szDevice,szOutput,NULL))!=0)			
		{	
			ParentMemDC.SetMapMode(MM_ISOTROPIC);
			ParentMemDC.SetViewportOrg(0, 0);
			ParentMemDC.SetViewportExt(215, 215);
			ParentMemDC.SetWindowOrg(0,0);
			ParentMemDC.SetWindowExt(100, 100);
			if(ParentMemDC.StartDoc(&di)>0) //开始执行一个打印作业			
			{	
				for (int k = 1; k <= nPage; k++)
				{
					ParentMemDC.StartPage(); //打印机走纸,开始打印				
					ParentMemDC.SaveDC(); //保存打印机设备句柄	
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
					ParentMemDC.TextOut(x, y, _T("月电费"));
					x += nWidth[2];
					ParentMemDC.TextOut(x, y, _T("水 单"));
					x += nWidth[3];
					ParentMemDC.TextOut(x, y, _T("实用方数"));
					x += nWidth[4];
					ParentMemDC.TextOut(x, y, _T("月水费"));
					x += nWidth[5];

					ParentMemDC.TextOut(x, y, _T("天然气单"));
					x += nWidth[6];
					ParentMemDC.TextOut(x, y, _T("实用方数"));
					x += nWidth[7];
					ParentMemDC.TextOut(x, y, _T("月然气费"));
					x += nWidth[8];

					ParentMemDC.TextOut(x, y, _T("安泰费"));
					x += nWidth[9];
					ParentMemDC.TextOut(x, y, _T("管理费"));
					x += nWidth[10];
					ParentMemDC.TextOut(x, y, _T("电视费"));
					//x += nWidth[8];
					//ParentMemDC.TextOut(x, y, _T("停车费"));
					//x += nWidth[9];
					//ParentMemDC.TextOut(x, y, _T("水泵加压"));
					x += nWidth[11];
					ParentMemDC.TextOut(x, y, _T("维修费"));
					x += nWidth[12];
					ParentMemDC.TextOut(x, y, _T(" 其他"));
					x += nWidth[13];
					ParentMemDC.TextOut(x, y, _T(" 房  租"));
					x += nWidth[14]; 
					ParentMemDC.TextOut(x, y, _T("  合  计"));
					x += nWidth[15];
					ParentMemDC.TextOut(x, y, _T("  房   号"));
					x += nWidth[16];
					//ParentMemDC.TextOut(x, y, _T("  备   注"));

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
						int nOffset = 95;
						x = Origin.x+3;
						y += nHight*2;
						ParentMemDC.TextOut(x, y, _T("统计信息"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("总电度数"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("总电费(元)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("总水方数"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("总水费(元)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("总天然气方数"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("总天然气费(元)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("总房租(元)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("总杂费(元)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("总收入(元)"));
						y += nHight;
						pointS = Origin;
						pointS.y = y;
						pointE = CPoint(Origin.x + nWidthTotal, pointS.y);
						ParentMemDC.MoveTo(pointS);
						ParentMemDC.LineTo(pointE);
						x = Origin.x+3;
						y += nHight;
						ParentMemDC.TextOut(x, y, m_strBuilding); //显示是哪栋 yjzhang 2012-07-01
						x += nOffset;
						TotalRealElec.Format(_T("%.2f"), fTotalRealElec);
						ParentMemDC.TextOut(x, y, TotalRealElec);
						x += nOffset;
						TotalElec.Format(_T("%.2f"), fTotalElec);
						ParentMemDC.TextOut(x, y, TotalElec);
						x += nOffset;
						TotalRealWater.Format(_T("%.2f"), fTotalRealWater);
						ParentMemDC.TextOut(x, y, TotalRealWater);
						x += nOffset;
						TotalWater.Format(_T("%.2f"), fTotalWater);
						ParentMemDC.TextOut(x, y, TotalWater);
						x += nOffset;

						TotalRealGas.Format(_T("%.2f"), fTotalRealGas);
						ParentMemDC.TextOut(x, y, TotalRealGas);
						x += nOffset;
						TotalGas.Format(_T("%.2f"), fTotalGas);
						ParentMemDC.TextOut(x, y, TotalGas);
						x += nOffset;


						TotalRent.Format(_T("%.2f"), fTotalRent);
						ParentMemDC.TextOut(x, y, TotalRent);
						x += nOffset;
						TotalOther.Format(_T("%.2f"), fTotalOther);
						ParentMemDC.TextOut(x, y, TotalOther);
						x += nOffset;
						Total.Format(_T("%.2f"), fTotal);
						ParentMemDC.TextOut(x, y, Total);
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
					x = Origin.x+3 + 260;
					y = Origin.y  - 30;
					CString strFrontTitle;
					int nMonth = _wtoi(m_strSearchTime.Right(2));
					int nYear= _wtoi(m_strSearchTime.Mid(1,4)); //获得年份 yjzhang 2012-07-01
					strFrontTitle.Format(_T("深圳宝安国雄物业管理处%d年%02d月收入统计表(%s)"), nYear, nMonth, m_strBuilding);
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
					ParentMemDC.SelectObject(OldFont);

					//double angel = (90/180.0)*3.1415926;
					//RotateAnyAngle(ParentMemDC,792, 401, angel);

					//复制图片到屏幕
					//pDC->BitBlt(rect.left, rect.top, rect.Height(),rect.Width(), &ParentMemDC, 0, 0, SRCCOPY);
					//pDC->BitBlt(rect.left, rect.top, rect.Width(),rect.Height(), &ParentMemDC, 0, 0, SRCCOPY);
				
					ParentMemDC.SelectObject(oldPan);
					ParentMemDC.SelectObject(OldFont);

					ParentMemDC.RestoreDC(-1); //恢复打印机设备句柄				
					ParentMemDC.EndPage(); //打印机停纸,停止打印
				}				
			    ParentMemDC.EndDoc(); //结束一个打印作业				
				//MessageBox(_T("打印成功!"),_T("提示"),MB_ICONINFORMATION);
		    }			
			//用API函数DeleteDC销毁一个打印机设备句柄			
			ParentMemDC.DeleteDC();	
		}
		else
		{
			MessageBox(_T("打开打印机失败!"));
		}
    }
	else			
	{	
		MessageBox(_T("没有默认打印机,或者没有安装打印机!"));
	} 
	delete [] pInfoModel;	
}

void CStatisticDlg::UpdateModelList()
{
	CString strRealElec;
	CString strRealWater;
	CString strRealGas;
	CString strElec;
	CString strWater;
	CString strGas;

	double fRealElec = 0.0;
	double fRealWater = 0.0;
	double fRealGas = 0.0;
	double fElec = 0.0;
	double fWater = 0.0;
	double fGas = 0.0;
	double fTemp = 0.0;

	int nRow = 0;
	for ( POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL;)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);
		for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL; nRow++)
		{
			CDataBuildInfoModel * pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);
			for (POSITION pos = pBuildData->m_ptrRentInfoList.GetHeadPosition(); pos != NULL;)
			{
				CDataRentInfoModel *pRentData = pBuildData->m_ptrRentInfoList.GetNext(pos);

				fRealElec = _wtof(pRentData->GetNowElec());
				fTemp = _wtof(pRentData->GetPreElec());
				fRealElec = fRealElec - fTemp;
				strRealElec.Format(_T("%.2f"), fRealElec);
				pRentData->SetRealElec(strRealElec);
				
				fTemp = _wtof(pRentData->GetPerMonthElec());
				fElec = fRealElec*fTemp;
				strElec.Format(_T("%.2f"), fElec);
				pRentData->SetTotalElec(strElec);

				fRealWater = _wtof(pRentData->GetNowWater());
				fTemp = _wtof(pRentData->GetPreWater());
				fRealWater = fRealWater - fTemp;
				strRealWater.Format(_T("%.2f"), fRealWater);
				pRentData->SetRealWater(strRealWater);

				fTemp = _wtof(pRentData->GetPerMonthWater());
				fWater = fRealWater*fTemp;
				strWater.Format(_T("%.2f"), fWater);
				pRentData->SetTotalWater(strWater);		


				fRealGas = _wtof(pRentData->GetNowGas());
				fTemp = _wtof(pRentData->GetPreGas());
				fRealGas = fRealGas - fTemp;
				strRealGas.Format(_T("%.2f"), fRealGas);
				pRentData->SetRealGas(strRealGas);

				fTemp = _wtof(pRentData->GetPerMonthGas());
				fGas = fRealGas*fTemp;
				strGas.Format(_T("%.2f"), fGas);
				pRentData->SetTotalGas(strGas);

			}
		}
	}
}
