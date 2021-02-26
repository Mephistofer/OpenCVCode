// StatisticDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GXManager.h"
#include "StatisticDlg.h"


// CStatisticDlg �Ի���

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


// CStatisticDlg ��Ϣ�������
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
		_T("����_GB2312")); // lpszFac 

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
		_T("����")); // lpszFac 

	m_comboxYear.SetFont(&m_editFont);
	m_comboxMonth.SetFont(&m_editFont);
	m_comboxBuild.SetFont(&m_editFont);
	InitStatisticList();

	return TRUE;
}
void CStatisticDlg::InitStatisticList(void)
{
	DWORD dwStyle = m_listStatistic.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и���
	dwStyle |= LVS_EX_GRIDLINES;//������
	dwStyle |= LVS_EX_SUBITEMIMAGES;

	m_listStatistic.SetExtendedStyle(dwStyle);

	m_listStatistic.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_listStatistic.InsertColumn(1, _T("����"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(2, _T("����"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(3, _T("ʵ�õ����"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(4, _T("���(Ԫ)"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(5, _T("ʵ��ˮ����"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(6, _T("ˮ��(Ԫ)"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(7, _T("ʵ����Ȼ������"), LVCFMT_CENTER, 150);
	m_listStatistic.InsertColumn(8, _T("��Ȼ����(Ԫ)"), LVCFMT_CENTER, 150);
	m_listStatistic.InsertColumn(9, _T("����(Ԫ)"), LVCFMT_CENTER, 110);
	m_listStatistic.InsertColumn(10, _T( "�ӷ�(Ԫ)"), LVCFMT_CENTER, 100);
	m_listStatistic.InsertColumn(11, _T( "�ϼ�(Ԫ)"), LVCFMT_CENTER, 110);	
	m_listStatistic.InsertColumn(12, _T( "��ע"), LVCFMT_CENTER, 100);
	m_listStatistic.SetItemHeight(25);
	m_listStatistic.SetListHeaderHeight(1.2);		
	m_listStatistic.SetListHeaderTextHeight(16);
	m_listStatistic.m_nLeft = 10;

	//��ʼ������	
	for ( POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL;)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);

		m_comboxBuild.AddString(GetTitleLastNum(pData->GetTitle()));
	}
	m_comboxBuild.AddString(_T("ȫ��"));
	m_comboxBuild.AddString(_T("3����"));
	m_comboxBuild.AddString(_T("3����"));
	m_comboxBuild.SetCurSel(0);

	//��ʼ����
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

	//��ʼ����
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
	
	if (strTemp != _T("ȫ��") && strTemp != _T("3����") && strTemp != _T("3����"))
	{
		m_strBuildingCheck += strTemp;
		m_strBuilding = strTemp+_T("��");
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
		if (m_strBuildingCheck != _T("ȫ��"))
		{
			if (m_strBuildingCheck.Compare(_T("3����")) == 0 || m_strBuildingCheck.Compare(_T("3����")) == 0)
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
			if (m_strBuildingCheck.Compare(_T("3����")) == 0)
			{
				iTemp = StrToInt(strTempthree);
				if(iTemp > 800)
				{
					break; //����һ��û��������
				}
			}
			else if (m_strBuildingCheck.Compare(_T("3����")) == 0)
			{
				iTemp = StrToInt(strTempthree);
				if(iTemp <= 800)
				{
					continue; //������
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

				//����
				m_listStatistic.SetItemText(nRow, 2, pRentData->GetName());

				//ʵ�õ���
				fTemp1 = _wtof(pRentData->GetNowElec());
				fTemp2 = _wtof(pRentData->GetPreElec());
				fLineElecNumTotal = fTemp1 - fTemp2;
				fElecNumTotal += fLineElecNumTotal;
				strTemp.Format(_T("%.2f"),fLineElecNumTotal);
				m_listStatistic.SetItemText(nRow, 3, strTemp);

				//���
				fLineElecFundTotal = fLineElecNumTotal * _wtof(pRentData->GetPerMonthElec());
				fElecFundTotal += fLineElecFundTotal;
				strTemp.Format(_T("%.2f"),fLineElecFundTotal);
				m_listStatistic.SetItemText(nRow, 4, strTemp);

				//ʵ��ˮ��
				fTemp1 = _wtof(pRentData->GetNowWater());
				fTemp2 = _wtof(pRentData->GetPreWater());
				fLineWaterNumTotal = fTemp1 - fTemp2;
				fWaterNumTotal += fLineWaterNumTotal;
				strTemp.Format(_T("%.2f"),fLineWaterNumTotal);
				m_listStatistic.SetItemText(nRow, 5, strTemp);

				//ˮ��
				fLineWaterFundTotal = fLineWaterNumTotal * _wtof(pRentData->GetPerMonthWater());
				fWaterFundTotal += fLineWaterFundTotal;
				strTemp.Format(_T("%.2f"),fLineWaterFundTotal);
				m_listStatistic.SetItemText(nRow, 6, strTemp);


				//ʵ����Ȼ
				fTemp1 = _wtof(pRentData->GetNowGas());
				fTemp2 = _wtof(pRentData->GetPreGas());
				fLineGasNumTotal = fTemp1 - fTemp2;
				fGasNumTotal += fLineGasNumTotal;
				strTemp.Format(_T("%.2f"), fLineGasNumTotal);
				m_listStatistic.SetItemText(nRow, 7, strTemp);

				//��Ȼ����
				fLineGasFundTotal = fLineGasNumTotal * _wtof(pRentData->GetPerMonthGas());
				fGasFundTotal += fLineGasFundTotal;
				strTemp.Format(_T("%.2f"), fLineGasFundTotal);
				m_listStatistic.SetItemText(nRow, 8, strTemp);

				//�����
				fLineRent = _wtof(pRentData->GetRent());
				fRentTotal += fLineRent;
				m_listStatistic.SetItemText(nRow, 9, pRentData->GetRent());

				//�ӷ�
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

				//�ܽ��
				fLineTotal = _wtof(pRentData->GetTotal());
				fTotal += fLineTotal;
				m_listStatistic.SetItemText(nRow, 11, pRentData->GetTotal());

				//��ע
				m_listStatistic.SetItemText(nRow, 12, pRentData->GetRemark());
			}
			nRow++;
			nTotalNum++;
		}		
	}
	g_nTotalNum = nTotalNum; //����ͳ����Ҫ��ӡ�������� yjzhang 2012-07-01
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
    m_listStatistic.SetItemText(nRow, 1, _T("ͳ����Ϣ"));
	m_listStatistic.SetItemText(nRow, 3, _T("�ܵ����"));
	m_listStatistic.SetItemText(nRow, 4, _T("�ܵ��(Ԫ)"));
	m_listStatistic.SetItemText(nRow, 5, _T("��ˮ����"));
	m_listStatistic.SetItemText(nRow, 6, _T("��ˮ��(Ԫ)"));

	m_listStatistic.SetItemText(nRow, 7, _T("����Ȼ������"));
	m_listStatistic.SetItemText(nRow, 8, _T("����Ȼ����(Ԫ)"));


	m_listStatistic.SetItemText(nRow, 9, _T("�ܷ����(Ԫ)"));
	m_listStatistic.SetItemText(nRow, 10, _T("���ӷ�(Ԫ)"));
	m_listStatistic.SetItemText(nRow++, 11, _T("�ϼ�(Ԫ)"));

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

	//��������
	CBitmap bmpCanvas;
	CBitmap Bitmap;
	CBitmap* pOldBitmap;		

	CDC ParentMemDC;	
	ParentMemDC.CreateCompatibleDC(pDC);
	bmpCanvas.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	pOldBitmap = ParentMemDC.SelectObject(&bmpCanvas); 

	//����������䱳��ɫ
	CBrush  brushFrame(MANAGER_CREAM);
	//���߿�ͱ���
	CBrush* pOldBrush = ParentMemDC.SelectObject(&brushFrame);
	ParentMemDC.FillRect(rect,&brushFrame);
	ParentMemDC.SelectObject(pOldBrush);

	//����ͼƬ����Ļ
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

	if (nCtlColor == CTLCOLOR_STATIC) //��̬�ı�
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
		if (m_strBuildingCheck != _T("ȫ��"))
		{
			if (m_strBuildingCheck.Compare(_T("3����")) == 0 || m_strBuildingCheck.Compare(_T("3����")) == 0)
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
			if (m_strBuildingCheck.Compare(_T("3����")) == 0)
			{
				iTemp = StrToInt(strTempNo);
				if(iTemp > 800)
				{
					break; //����һ��û��������
				}
			}
			else if (m_strBuildingCheck.Compare(_T("3����")) == 0)
			{
				iTemp = StrToInt(strTempNo);
				if(iTemp <= 800)
				{
					continue; //������
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
			nRow++; //��Ҫ
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

	//����һ����ӡ��ҵ	
	static DOCINFO di={sizeof(DOCINFO),_T("printer"),NULL};	

	//�õ��豸�ַ�����������szprinter��	
	//GetProfileString(_T("windows"),_T("device"),_T(",,,"),szprinter,80);
	g_cfg.getStaticPrinterAddr(szprinter);
	//	GetProfileString("MCI Extensions.BAK","aif",",,,",szprinter,80);

	//���豸�ַ����ֽ�	
	WCHAR *pszResult = NULL; 
	//szDevice=wcstok_s(szprinter,_T(","), &pszResult);
	if(NULL != (szDevice=wcstok_s(szprinter,_T(","), &pszResult)) &&		
		NULL != (szDriver=wcstok_s(pszResult,_T(","), &pszResult)) &&		
		NULL != (szOutput=wcstok_s(pszResult,_T(","), &pszResult)))
	{
		CDC ParentMemDC;
		//����һ����ӡ���豸���		
		if((ParentMemDC.CreateDC(szDriver,szDevice,szOutput,NULL))!=0)			
		{	
			ParentMemDC.SetMapMode(MM_ISOTROPIC);
			ParentMemDC.SetViewportOrg(0, 0);
			ParentMemDC.SetViewportExt(215, 215);
			ParentMemDC.SetWindowOrg(0,0);
			ParentMemDC.SetWindowExt(100, 100);
			if(ParentMemDC.StartDoc(&di)>0) //��ʼִ��һ����ӡ��ҵ			
			{	
				for (int k = 1; k <= nPage; k++)
				{
					ParentMemDC.StartPage(); //��ӡ����ֽ,��ʼ��ӡ				
					ParentMemDC.SaveDC(); //�����ӡ���豸���	
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
						_T("����")); // lpszFac 
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
						_T("����")); // lpszFac 
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
					ParentMemDC.TextOut(x, y, _T("�� ��"));
					x += nWidth[0];
					ParentMemDC.TextOut(x, y, _T("ʵ�ö���"));
					x += nWidth[1];
					ParentMemDC.TextOut(x, y, _T("�µ��"));
					x += nWidth[2];
					ParentMemDC.TextOut(x, y, _T("ˮ ��"));
					x += nWidth[3];
					ParentMemDC.TextOut(x, y, _T("ʵ�÷���"));
					x += nWidth[4];
					ParentMemDC.TextOut(x, y, _T("��ˮ��"));
					x += nWidth[5];

					ParentMemDC.TextOut(x, y, _T("��Ȼ����"));
					x += nWidth[6];
					ParentMemDC.TextOut(x, y, _T("ʵ�÷���"));
					x += nWidth[7];
					ParentMemDC.TextOut(x, y, _T("��Ȼ����"));
					x += nWidth[8];

					ParentMemDC.TextOut(x, y, _T("��̩��"));
					x += nWidth[9];
					ParentMemDC.TextOut(x, y, _T("�����"));
					x += nWidth[10];
					ParentMemDC.TextOut(x, y, _T("���ӷ�"));
					//x += nWidth[8];
					//ParentMemDC.TextOut(x, y, _T("ͣ����"));
					//x += nWidth[9];
					//ParentMemDC.TextOut(x, y, _T("ˮ�ü�ѹ"));
					x += nWidth[11];
					ParentMemDC.TextOut(x, y, _T("ά�޷�"));
					x += nWidth[12];
					ParentMemDC.TextOut(x, y, _T(" ����"));
					x += nWidth[13];
					ParentMemDC.TextOut(x, y, _T(" ��  ��"));
					x += nWidth[14]; 
					ParentMemDC.TextOut(x, y, _T("  ��  ��"));
					x += nWidth[15];
					ParentMemDC.TextOut(x, y, _T("  ��   ��"));
					x += nWidth[16];
					//ParentMemDC.TextOut(x, y, _T("  ��   ע"));

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
						ParentMemDC.TextOut(x, y, _T("ͳ����Ϣ"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("�ܵ����"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("�ܵ��(Ԫ)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("��ˮ����"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("��ˮ��(Ԫ)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("����Ȼ������"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("����Ȼ����(Ԫ)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("�ܷ���(Ԫ)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("���ӷ�(Ԫ)"));
						x += nOffset;
						ParentMemDC.TextOut(x, y, _T("������(Ԫ)"));
						y += nHight;
						pointS = Origin;
						pointS.y = y;
						pointE = CPoint(Origin.x + nWidthTotal, pointS.y);
						ParentMemDC.MoveTo(pointS);
						ParentMemDC.LineTo(pointE);
						x = Origin.x+3;
						y += nHight;
						ParentMemDC.TextOut(x, y, m_strBuilding); //��ʾ���Ķ� yjzhang 2012-07-01
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
						_T("����")); // lpszFac 
					//CFont *OldFont = 
					ParentMemDC.SelectObject(&editFontTital);
					x = Origin.x+3 + 260;
					y = Origin.y  - 30;
					CString strFrontTitle;
					int nMonth = _wtoi(m_strSearchTime.Right(2));
					int nYear= _wtoi(m_strSearchTime.Mid(1,4)); //������ yjzhang 2012-07-01
					strFrontTitle.Format(_T("���ڱ���������ҵ����%d��%02d������ͳ�Ʊ�(%s)"), nYear, nMonth, m_strBuilding);
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
						_T("����")); // lpszFac 
					ParentMemDC.SelectObject(&editFontTital);

					x = Origin.x + 908;
					y = Origin.y + nHightTotal+ 3;
					CString strPage;
					strPage.Format(_T("�� %d ҳ"), k);
					ParentMemDC.TextOut(x, y, strPage);

					editFontTital.DeleteObject();

					ParentMemDC.SelectObject(oldPan);
					ParentMemDC.SelectObject(OldFont);

					//double angel = (90/180.0)*3.1415926;
					//RotateAnyAngle(ParentMemDC,792, 401, angel);

					//����ͼƬ����Ļ
					//pDC->BitBlt(rect.left, rect.top, rect.Height(),rect.Width(), &ParentMemDC, 0, 0, SRCCOPY);
					//pDC->BitBlt(rect.left, rect.top, rect.Width(),rect.Height(), &ParentMemDC, 0, 0, SRCCOPY);
				
					ParentMemDC.SelectObject(oldPan);
					ParentMemDC.SelectObject(OldFont);

					ParentMemDC.RestoreDC(-1); //�ָ���ӡ���豸���				
					ParentMemDC.EndPage(); //��ӡ��ֽͣ,ֹͣ��ӡ
				}				
			    ParentMemDC.EndDoc(); //����һ����ӡ��ҵ				
				//MessageBox(_T("��ӡ�ɹ�!"),_T("��ʾ"),MB_ICONINFORMATION);
		    }			
			//��API����DeleteDC����һ����ӡ���豸���			
			ParentMemDC.DeleteDC();	
		}
		else
		{
			MessageBox(_T("�򿪴�ӡ��ʧ��!"));
		}
    }
	else			
	{	
		MessageBox(_T("û��Ĭ�ϴ�ӡ��,����û�а�װ��ӡ��!"));
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
