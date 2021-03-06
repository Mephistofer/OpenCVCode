// PrintInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GXManager.h"
#include "PrintInfoDlg.h"

// PrintInfoDlg 对话框

IMPLEMENT_DYNAMIC(PrintInfoDlg, CDialog)

PrintInfoDlg::PrintInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PrintInfoDlg::IDD, pParent)
{

}

PrintInfoDlg::~PrintInfoDlg()
{
}

void PrintInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PRINT_BUILD1, m_comboBuild1);
	DDX_Control(pDX, IDC_COMBO_PRINT_BUILD2, m_comboBuild2);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtTime);
	DDX_Control(pDX, IDC_EDIT_PRINT_NAME, m_editName);
	//DDX_Control(pDX, IDC_EDIT_PRINT_SANITATION, m_editSanitation);
	DDX_Control(pDX, IDC_EDIT_PRINT_TV, m_editTV);
	DDX_Control(pDX, IDC_EDIT_PRINT_RENT, m_editRent);
	//DDX_Control(pDX, IDC_EDIT_PRINT_PARKING, m_editParking);
	DDX_Control(pDX, IDC_EDIT_BODY_FUND, m_editBodyFund);
	DDX_Control(pDX, IDC_EDIT_PRINT_REMARK, m_editRemark);
	DDX_Control(pDX, IDC_EDIT_PRE_ELEC, m_editPreElec);
	DDX_Control(pDX, IDC_EDIT1_NOW_ELEC, m_editNowElec);
	DDX_Control(pDX, IDC_EDIT_ELEC_PERMONTH, m_editPerMonthElec);
	DDX_Control(pDX, IDC_EDIT_PRE_WATER, m_editPreWater);
	DDX_Control(pDX, IDC_EDIT_NOW_WATER, m_editNowWater);
	DDX_Control(pDX, IDC_EDIT_WATER_PERMONTH, m_editPerMonthWater);
	DDX_Control(pDX, IDC_EDIT_LIST_MAKER, m_editMaker);
	DDX_Control(pDX, IDC_COMBO_MONTH, m_comboRentMonth);
	DDX_Control(pDX, IDC_EDIT_PRINT_OTHER, m_editOther);
	//DDX_Control(pDX, IDC_EDIT_PRINT_PUMP, m_editPump);
	DDX_Control(pDX, IDC_EDIT_PRINT_MANAGER, m_editManager);
	DDX_Control(pDX, IDC_EDIT_PRINT_WUGUANFEI, m_editWuGuanFei);
	DDX_Control(pDX, IDC_EDIT_PRE_GAS, m_editPreGas);
	DDX_Control(pDX, IDC_EDIT_NOW_GAS, m_editNowGas);
	DDX_Control(pDX, IDC_EDIT_GAS_PERMONTH, m_editPerMonthGas);
}


BEGIN_MESSAGE_MAP(PrintInfoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_CBN_CLOSEUP(IDC_COMBO_PRINT_BUILD1, &PrintInfoDlg::OnCbnCloseupComboPrintBuild1)
	ON_CBN_CLOSEUP(IDC_COMBO_PRINT_BUILD2, &PrintInfoDlg::OnCbnCloseupComboPrintBuild2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &PrintInfoDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &PrintInfoDlg::OnBnClickedButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_PRE, &PrintInfoDlg::OnBnClickedButtonPre)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &PrintInfoDlg::OnBnClickedButtonNext)
	ON_CBN_CLOSEUP(IDC_COMBO_MONTH, &PrintInfoDlg::OnCbnCloseupComboMonth)
END_MESSAGE_MAP()

BOOL PrintInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editFont.CreateFont(14, // nHeight 
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

	m_editName.SetFont(&m_editFont);
	m_editRemark.SetFont(&m_editFont);	
	m_comboBuild1.SetFont(&m_StaticFont);
	m_comboBuild2.SetFont(&m_StaticFont);
	m_comboRentMonth.SetFont(&m_StaticFont);
	m_editMaker.SetFont(&m_editFont);

	//m_dtTime.SetFont(&m_editFont);
	//m_editTV.SetFont(&m_editFont);
	//m_editSanitation.SetFont(&m_editFont);
	//m_editRent.SetFont(&m_editFont);
	//m_editNowElec.SetFont(&m_editFont);
	//m_editPreElec.SetFont(&m_editFont);
	//m_editNowWater.SetFont(&m_editFont);
	//m_editPreWater.SetFont(&m_editFont);
	//m_editParking.SetFont(&m_editFont);
	//m_editBodyFund.SetFont(&m_editFont);
	//m_editPerMonthElec.SetFont(&m_editFont);
	//m_editPerMonthWater.SetFont(&m_editFont);
	//m_staticNo1.SetFont(&m_StaticFont);
	//m_staticNo2.SetFont(&m_StaticFont);
	InitPrintDlg();	
	return TRUE;
}
// PrintInfoDlg 消息处理程序
void PrintInfoDlg::SetParentWnd(CWnd* p)
{
	m_pParent = p;
}
void PrintInfoDlg::OnPaint()
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

	CPen cPen, *oldPan;
	cPen.CreatePen(PS_SOLID,0,MANAGER_GRAY);
	oldPan = ParentMemDC.SelectObject(&cPen);
	/*CPoint pointS,pointE;
	pointS = CPoint(20,400);
	pointE = CPoint(565, 400);
	ParentMemDC.MoveTo(pointS);
	ParentMemDC.LineTo(pointE);

	pointS = CPoint(20,444);
	pointE = CPoint(565, 444);
	ParentMemDC.MoveTo(pointS);
	ParentMemDC.LineTo(pointE);

	pointS = CPoint(110, 363);
	pointE = CPoint(110, 483);
	ParentMemDC.MoveTo(pointS);
	ParentMemDC.LineTo(pointE);

	pointS = CPoint(260, 363);
	pointE = CPoint(260, 483);
	ParentMemDC.MoveTo(pointS);
	ParentMemDC.LineTo(pointE);

	pointS = CPoint(415, 363);
	pointE = CPoint(415, 483);
	ParentMemDC.MoveTo(pointS);
	ParentMemDC.LineTo(pointE);*/

	ParentMemDC.SelectObject(oldPan);
	ParentMemDC.SelectObject(pOldBrush);

	//复制图片到屏幕
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &ParentMemDC, 0, 0, SRCCOPY);
	ParentMemDC.SelectObject(pOldBitmap);
	ReleaseDC(&ParentMemDC);
}

HBRUSH PrintInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void PrintInfoDlg::OnCbnCloseupComboPrintBuild1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp1;
	if (m_comboBuild1.GetCurSel() != CB_ERR)
	{
        m_comboBuild1.GetLBText(m_comboBuild1.GetCurSel(), strTemp1);
	}	

	if (strTemp1 == m_strComboEdit1)
	{
		return;
	}
	else
	{
		m_strComboEdit1 = strTemp1;
	}

	CDataBuildInfoModel * pBuildData;
	CString strTemp2;
	int nHouseFirst = 0;
	for (POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL; nHouseFirst++)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);

		strTemp2 = GetTitleLastNum(pData->GetTitle());
		//m_comboBuild1.AddString(strTemp2);
		if (strTemp2 == m_strComboEdit1)
		{
			//m_comboBuild1.SetCurSel(nHouseFirst);
			m_comboBuild2.ResetContent();
			int i = 0;
			for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL; i++)
			{
				pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);

				strTemp2 = GetHouseLastNum(pBuildData->GetNO());
				m_comboBuild2.AddString(strTemp2);
				if (0==i)
				{
					i++; //不在重新设置，让房号尽快显示
					m_comboBuild2.SetCurSel(0);
					m_comboBuild2.GetLBText(m_comboBuild2.GetCurSel(), strTemp2);
					m_strComboEdit2 = strTemp2;	
					DialogShow(pBuildData);
				}
			}
			break;
		}
	}	
	m_strNo = m_strComboEdit1+_T("-") + m_strComboEdit2;
}

void PrintInfoDlg::OnCbnCloseupComboPrintBuild2()
{
	CString strTemp1;
	if (m_comboBuild2.GetCurSel() != CB_ERR)
	{
        m_comboBuild2.GetLBText(m_comboBuild2.GetCurSel(), strTemp1);
	}
	if (strTemp1 == m_strComboEdit2)
	{
		return;
	}
	else
	{
		m_strComboEdit2 = strTemp1;
	}

	CDataBuildInfoModel * pBuildData;
	CString strTemp2;
	int nHouseFirst = 0;
	for (POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL; nHouseFirst++)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);

		strTemp2 = GetTitleLastNum(pData->GetTitle());
		if (strTemp2 == m_strComboEdit1)
		{
			int i = 0;
			for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL; i++)
			{
				pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);

				strTemp2 = GetHouseLastNum(pBuildData->GetNO());
				if (m_strComboEdit2 == strTemp2)
				{
					DialogShow(pBuildData);
					break;
				}
			}
			break;
		}
	}
	m_strNo = m_strComboEdit1+_T("-") + m_strComboEdit2;
}

void PrintInfoDlg::InitPrintDlg(void)
{
	m_editMaker.SetWindowText(g_strMaker);
	CString strTemp;
	for (int i = 1; i <= 12; i++)
	{
		strTemp.Format(_T("%d"), i);
		m_comboRentMonth.AddString(strTemp);
	}
	CTime ctTime;
	DWORD dwResult = m_dtTime.GetTime(ctTime);
	if (dwResult == GDT_VALID)
	{
		int nMonth = ctTime.GetMonth();
		int nDay = ctTime.GetDay();
		if (nDay <= 20)
		{
			nMonth--;
		}
		else
		{
			if (nMonth == 12)
			{
				nMonth = 0;
			}
		}

		m_comboRentMonth.SetCurSel(nMonth);
	}

	CDataBuildInfoModel * pBuildData;
	
	int nHouseFirst = 0;
	for (POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL; nHouseFirst++)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);
	
		strTemp = GetTitleLastNum(pData->GetTitle());
		m_comboBuild1.AddString(strTemp);
		if (strTemp == GetHouseFirstNum(m_strNo))
		{
			m_comboBuild1.SetCurSel(nHouseFirst);
			m_comboBuild1.GetLBText(nHouseFirst, m_strComboEdit1);
			int nHouseLast = 0;
			for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL; nHouseLast++)
			{
				pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);
				strTemp = GetHouseLastNum(pBuildData->GetNO());
				m_comboBuild2.AddString(strTemp);
				if (strTemp == GetHouseLastNum(m_strNo))
				{
					m_comboBuild2.SetCurSel(nHouseLast);
					m_comboBuild2.GetLBText(nHouseLast, m_strComboEdit2);
					DialogShow(pBuildData);
				}
			}
		}
	}
}

HRESULT PrintInfoDlg::SaveData()
{
	m_editMaker.GetWindowText(g_strMaker);
	CString strTemp;
	CString strNULL = _T("    /");

	CString strRent = strNULL;
	double fRent = 0.0;

	CString strPump = strNULL;
	double fPump = 0.0;

	CString strManager = strNULL;
	double fManager = 0.0;

	CString strPreElec = strNULL;
	double fPreElec = 0.0;
	CString strNowElec = strNULL;
	double fNowElec = 0.0;
	CString strRealElec = strNULL;
	double fRealElec = 0.0;
	CString strPerMonthElec = strNULL;
	double fPerMonthElec = 0.0;
	CString strTotalElec = strNULL;
	double fTotalElec = 0.0;

	CString strPreWater = strNULL;
	double fPreWater = 0.0;
	CString strNowWater = strNULL;
	double fNowWater = 0.0;
	CString strRealWater = strNULL;
	double fRealWater = 0.0;
	CString strPerMonthWater = strNULL;
	double fPerMonthWater = 0.0;
	CString strTotalWater = strNULL;
	double fTotalWater = 0.0;

	CString strPreGas = strNULL;
	double fPreGas = 0.0;
	CString strNowGas = strNULL;
	double fNowGas = 0.0;
	CString strRealGas = strNULL;
	double fRealGas = 0.0;
	CString strPerMonthGas = strNULL;
	double fPerMonthGas= 0.0;
	CString strTotalGas = strNULL;
	double fTotalGas = 0.0;

	//CString strSanitation = strNULL;
	//double fSanitation = 0.0;
	CString strWuGuanFei = strNULL;
	double fWuGuanFei = 0.0;

	CString strTV = strNULL;
	double fTV = 0.0;

	CString strParking = strNULL;
	double fParking = 0.0;

	CString strBodyFund = strNULL;
	double fBodyFund = 0.0;

	CString strOther = strNULL;
	double fOther = 0.0;

	CString strTotal = strNULL;
	double fTotal = 0.0;


	//Rent
	m_editRent.GetWindowText(strTemp);
	SetString(strTemp, strRent);
	fRent = _wtof(strRent);

	//m_editPump.GetWindowText(strTemp);
	//SetString(strTemp, strPump);
	//fPump = _wtof(strPump);

	m_editManager.GetWindowText(strTemp);
	SetString(strTemp, strManager);
	fManager = _wtof(strManager);

	//Elec
	m_editPreElec.GetWindowText(strTemp);
	SetString(strTemp, strPreElec);
	fPreElec = _wtof(strPreElec);

	m_editNowElec.GetWindowText(strTemp);
	SetString(strTemp, strNowElec);
	fNowElec = _wtof(strNowElec);

	fRealElec = fNowElec - fPreElec;
	m_strRealElec.Format(_T("%.2f"), fRealElec);

	m_editPerMonthElec.GetWindowText(strTemp);
	SetString(strTemp, strPerMonthElec);
	fPerMonthElec = _wtof(strPerMonthElec);

	fTotalElec = fPerMonthElec * fRealElec;
	m_strTotalElec.Format(_T("%.2f"), fTotalElec);

	//Water
	m_editPreWater.GetWindowText(strTemp);
	SetString(strTemp, strPreWater);
	fPreWater = _wtof(strPreWater);

	m_editNowWater.GetWindowText(strTemp);
	SetString(strTemp, strNowWater);
	fNowWater = _wtof(strNowWater);

	fRealWater = fNowWater - fPreWater;
	m_strRealWater.Format(_T("%.2f"), fRealWater);

	m_editPerMonthWater.GetWindowText(strTemp);
	SetString(strTemp, strPerMonthWater);
	fPerMonthWater = _wtof(strPerMonthWater);

	fTotalWater = fPerMonthWater * fRealWater;
	m_strTotalWater.Format(_T("%.2f"), fTotalWater);

	//Gas
	m_editPreGas.GetWindowText(strTemp);
	SetString(strTemp, strPreGas);
	fPreGas= _wtof(strPreGas);

	m_editNowGas.GetWindowText(strTemp);
	SetString(strTemp, strNowGas);
	fNowGas= _wtof(strNowGas);

	fRealGas= fNowGas - fPreGas;
	m_strRealGas.Format(_T("%.2f"), fRealGas);

	m_editPerMonthGas.GetWindowText(strTemp);
	SetString(strTemp, strPerMonthGas);
	fPerMonthGas = _wtof(strPerMonthGas);

	fTotalGas = fPerMonthGas * fRealGas;
	m_strTotalGas.Format(_T("%.2f"), fTotalGas);

	//other
	//m_editSanitation.GetWindowText(strTemp);
	//SetString(strTemp, strSanitation);
	//fSanitation = _wtof(strSanitation);

	m_editWuGuanFei.GetWindowText(strTemp);
	SetString(strTemp, strWuGuanFei);
	fWuGuanFei = _wtof(strWuGuanFei);

	m_editTV.GetWindowText(strTemp);
	SetString(strTemp, strTV);
	fTV = _wtof(strTV);

	//m_editParking.GetWindowText(strTemp);
	//SetString(strTemp, strParking);
	//fParking = _wtof(strParking);

	m_editBodyFund.GetWindowText(strTemp);
	SetString(strTemp, strBodyFund);
	fBodyFund = _wtof(strBodyFund);

	m_editOther.GetWindowText(strTemp);
	SetString(strTemp, strOther);
	fOther = _wtof(strOther);
	strOther.Format(_T("%10.2f"), fOther);

	fTotal = fRent + fTotalElec + fTotalWater + fTotalGas+ /*fSanitation*/ fWuGuanFei+ fParking + fTV + fBodyFund + fOther + fPump + fManager;
	m_strTotal.Format(_T("%.2f"), fTotal);

	CString strNo;
	if (m_comboBuild1.GetCurSel() != CB_ERR)
	{
		m_comboBuild1.GetLBText(m_comboBuild1.GetCurSel(), strNo);
	}
	HRESULT hResult = SaveXML(BUILD_DATA_PATH, strNo);
	CoUninitialize();
	return hResult;
}
void PrintInfoDlg::OnBnClickedButtonSave()
{
	HRESULT hResult = SaveData();
	if (hResult == PRINT_ERROR)
	{
		AfxMessageBox(_T("保存失败！"));
	}
	else if (hResult == PRINT_NEGATIVE_ELEC)
	{
		AfxMessageBox(_T("你的电度数输入有误！"));
	}
	else if (hResult == PRINT_NEGATIVE_WATER)
	{
		AfxMessageBox(_T("你的水方数输入有误！"));
	}
	else if (hResult == PRINT_NEGATIVE_GAS)
	{
		AfxMessageBox(_T("你的天然气方数输入有误！"));
	}
	else
	{
        AfxMessageBox(_T("保存成功！"));
	}
	//CoUninitialize();	
	//CDialog::OnOK();
}

void PrintInfoDlg::OnBnClickedButtonPrint()
{
	HRESULT hResult = SaveData();
	if (hResult == PRINT_ERROR)
	{
		AfxMessageBox(_T("保存失败，不能打印！"));
		return;
	}
	else if (hResult == PRINT_NEGATIVE_ELEC)
	{
		AfxMessageBox(_T("你的电度数输入有误，不能打印！"));
		return;
	}
	else if (hResult == PRINT_NEGATIVE_WATER)
	{
		AfxMessageBox(_T("你的水度数输入有误，不能打印！"));
		return;
	}
	else if (hResult == PRINT_NEGATIVE_GAS)
	{
		AfxMessageBox(_T("你的天然气方数输入有误，不能打印！"));
		return;
	}

	PrintList();

	//CoUninitialize();
	//CDialog::OnOK();
}

HRESULT PrintInfoDlg::SaveXML(CString cstrXMLFile, CString strNO)
{
	using MSXML2::IXMLDOMDocumentPtr;
	using MSXML2::DOMDocument60;
	using MSXML2::IXMLDOMNodePtr;
	using MSXML2::IXMLDOMNodeListPtr;
	using MSXML2::IXMLDOMNamedNodeMapPtr;
	using MSXML2::IXMLDOMElementPtr;
	try
	{
		IXMLDOMDocumentPtr	pXMLDom;    //MSXML2::IXMLDOMDocumentPtr ---> StdAfx.h
		//IXMLDOMNodeListPtr	pNodeList;
		IXMLDOMNodePtr		pNode;

		//IXMLDOMNodeListPtr  pNodeChildList;

		CoInitialize(NULL); // for single thread to create COM Object(msxml4.dll).

		// creat DOMDocument and check the return value.
		// hr type is a 32-bit value that is used to describe an error or warning.
		HRESULT hr = pXMLDom.CreateInstance(__uuidof(DOMDocument60));
		if (FAILED(hr))
		{
			return PRINT_ERROR;
		}

		pXMLDom->async = VARIANT_FALSE; // default is true, must synchronization.

		// load XML file.
		if ( pXMLDom->load(cstrXMLFile.GetBuffer(0)) != VARIANT_TRUE)
			// if fail to load XML file...
		{
			RELEASE(pXMLDom); // release DOMDocument.
			//CoUninitialize();  // must do it, for exactly matching.

			return PRINT_ERROR;
		}
		cstrXMLFile.ReleaseBuffer();

		// transaction
		CString searchPath = _T("building_information/build");
		searchPath += strNO; //important (yjzhang 2011-03-15)

		//修改列表数据
		CDataBuildInfoModel * pBuildData;
		for ( POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL;)
		{
			CDataModel * pData = m_pDataModelList->GetNext(pos);
			int i = searchPath.GetLength() - searchPath.Find('/');
			CString u = searchPath.Right(i-1);
			if ( pData->GetTitle() == searchPath.Right(searchPath.GetLength() - searchPath.Find('/') - 1))
			{
				for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL;)
				{
					pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);
					if (pBuildData->GetNO() == m_strNo)
					{
						break;
					}
				}
				break;
			}				
		}
		CString strTemp;
		CDataRentInfoModel *pRentInfo = new CDataRentInfoModel;
		m_editName.GetWindowText(strTemp);
		pRentInfo->SetName(strTemp);
		m_editBodyFund.GetWindowText(strTemp);
		pRentInfo->SetBodyFund(strTemp);
		//m_editSanitation.GetWindowText(strTemp);
		//pRentInfo->SetSanitation(strTemp);
		m_editWuGuanFei.GetWindowText(strTemp);
		pRentInfo->SetWuGuanFei(strTemp);

		m_editRemark.GetWindowText(strTemp);
		pRentInfo->SetRemark(strTemp);
		m_editRent.GetWindowText(strTemp);
		pRentInfo->SetRent(strTemp);
		m_editTV.GetWindowText(strTemp);
		pRentInfo->SetTV(strTemp);
		//m_editParking.GetWindowText(strTemp);
		//pRentInfo->SetParking(strTemp);

		//Elec
		m_editPreElec.GetWindowText(strTemp);
		pRentInfo->SetPreElec(strTemp);
		double ftempPreElec = _wtof(strTemp);
		m_editNowElec.GetWindowText(strTemp);
		pRentInfo->SetNowElec(strTemp);
		double ftempNowElec = _wtof(strTemp);
		if (ftempNowElec - ftempPreElec < 0.0)
		{
			delete pRentInfo;
			RELEASE(pXMLDom); // release DOMDocument.
			//CoUninitialize();  // must do it, for exactly matching.
			return PRINT_NEGATIVE_ELEC;			
		}
		m_editPerMonthElec.GetWindowText(strTemp);
		pRentInfo->SetPerMonthElec(strTemp);

		//Water
		m_editPreWater.GetWindowText(strTemp);
		pRentInfo->SetPreWater(strTemp);
		double ftempPreWater = _wtof(strTemp);
		m_editNowWater.GetWindowText(strTemp);
		pRentInfo->SetNowWater(strTemp);		
		double ftempNowWater = _wtof(strTemp);
		if (ftempNowWater - ftempPreWater < 0.0)
		{
			delete pRentInfo;
			RELEASE(pXMLDom); // release DOMDocument.
			//CoUninitialize();  // must do it, for exactly matching.
			return PRINT_NEGATIVE_WATER;			
		}
		m_editPerMonthWater.GetWindowText(strTemp);
		pRentInfo->SetPerMonthWater(strTemp);

		//GAS
		m_editPreGas.GetWindowText(strTemp);
		pRentInfo->SetPreGas(strTemp);
		double ftempPreGas = _wtof(strTemp);
		m_editNowGas.GetWindowText(strTemp);
		pRentInfo->SetNowGas(strTemp);
		double ftempNowGas = _wtof(strTemp);
		if (ftempNowGas- ftempPreGas < 0.0)
		{
			delete pRentInfo;
			RELEASE(pXMLDom); // release DOMDocument.
			//CoUninitialize();  // must do it, for exactly matching.
			return PRINT_NEGATIVE_GAS;
		}
		m_editPerMonthGas.GetWindowText(strTemp);
		pRentInfo->SetPerMonthGas(strTemp);

		m_editOther.GetWindowText(strTemp);	
		pRentInfo->SetOther(strTemp);
		//m_editPump.GetWindowText(strTemp);	
		//pRentInfo->SetPump(strTemp);
		m_editManager.GetWindowText(strTemp);	
		pRentInfo->SetManager(strTemp);

		pRentInfo->SetTotal(m_strTotal); //统计价钱 yjzhang 2011-04-04
		pRentInfo->SetRealElec(m_strRealElec);
		pRentInfo->SetRealWater(m_strRealWater);
		pRentInfo->SetRealGas(m_strRealGas);
		pRentInfo->SetTotalElec(m_strTotalElec);
		pRentInfo->SetTotalWater(m_strTotalWater);
		pRentInfo->SetTotalGas(m_strTotalGas);

		SetTimeTitle(strTemp, m_dtTime, m_comboRentMonth);
		pRentInfo->SetTitle(strTemp); 
		CDataRentInfoModel * pRentData = NULL;
		POSITION posRent = NULL;
		POSITION posRentNext = NULL;
		BOOL bAdd = FALSE;
		int nPos = -1;
		
		BOOL bFindElement = FALSE;
		//如果有元素，索引元素，找到合适的位置插入
		for (posRent = pBuildData->m_ptrRentInfoList.GetTailPosition(); posRent != NULL;)
		{
			nPos++;
			posRentNext = posRent;
			pRentData = pBuildData->m_ptrRentInfoList.GetPrev(posRent);
			//找到匹配元素，更新对应元素
			if (pRentData->GetTitle() == strTemp)
			{
				bFindElement = TRUE;
				pBuildData->m_ptrRentInfoList.SetAt(posRentNext, pRentInfo);
				break;
			}
			
			//由于链表排序从小到大，因此在指定位置增加数据
			if (pRentData->GetTitle() < strTemp)
			{
				bFindElement = TRUE;
				pBuildData->m_ptrRentInfoList.InsertAfter(posRentNext, pRentInfo);
				bAdd = TRUE; //增加数据
				break;
			}
		}

		//如果没有元素，或者元素最小，添加至开头
		if (!bFindElement)
		{
			pBuildData->m_ptrRentInfoList.AddHead(pRentInfo);
			bAdd = TRUE; //增加数据
		}

		//IXMLDOMNodePtr			pChildNode;
		// CDataTradeModel *pDataTrade = new CDataTradeModel;
		searchPath += _T("/");
		searchPath += pBuildData->GetTitle();

		IXMLDOMElementPtr pElement;
		pNode = pXMLDom->selectSingleNode(static_cast<_bstr_t>(searchPath));

		if (bAdd)
		{
			IXMLDOMNodePtr	pChildNode=pXMLDom->createElement((LPCTSTR)(pRentInfo->GetTitle()));
	
			CString strTmep = (LPCTSTR)pRentInfo->GetTitle();
			if(pChildNode==NULL)
			{
				RELEASE(pXMLDom); // release DOMDocument.
				//CoUninitialize();  // must do it, for exactly matching.
				return PRINT_ERROR;
			}

			IXMLDOMNodePtr			pSubNode;
			IXMLDOMNodeListPtr	    pSubNodeList;

			pSubNodeList = pNode->GetchildNodes();
			int nRentChild = pSubNodeList->Getlength();
			CString strTitleTemp;
			CString strTitle = (CString)(LPCTSTR)(pRentInfo->GetTitle());

			BOOL bInsert = FALSE;
			for (int i = 0; i < nRentChild; i++)
			{
				pSubNode = pSubNodeList->Getitem(i);
				strTitleTemp = (CString)(LPCTSTR)(pSubNode->GetnodeName());
				if (strTitleTemp > strTitle)
				{
					bInsert = TRUE;
					pChildNode->appendChild(pXMLDom->createTextNode("\n\t\t\t"));
					pElement = pChildNode;
					pElement->setAttribute("name", (LPCTSTR)(pRentInfo->GetName()));
					pElement->setAttribute("rent", (LPCTSTR)(pRentInfo->GetRent()));
					pElement->setAttribute("sanitation", (LPCTSTR)(pRentInfo->GetSanitation()));					
					pElement->setAttribute("parking", (LPCTSTR)(pRentInfo->GetParking()));
					pElement->setAttribute("tv", (LPCTSTR)(pRentInfo->GetTV()));
					pElement->setAttribute("body_fund", (LPCTSTR)(pRentInfo->GetBodyFund()));
					pElement->setAttribute("pre_elec", (LPCTSTR)(pRentInfo->GetPreElec()));
					pElement->setAttribute("now_elec", (LPCTSTR)(pRentInfo->GetNowElec()));
					pElement->setAttribute("pre_water", (LPCTSTR)(pRentInfo->GetPreWater()));
					pElement->setAttribute("now_water", (LPCTSTR)(pRentInfo->GetNowWater()));
					pElement->setAttribute("per_elec", (LPCTSTR)(pRentInfo->GetPerMonthElec()));
					pElement->setAttribute("per_water", (LPCTSTR)(pRentInfo->GetPerMonthWater()));
					pElement->setAttribute("other", (LPCTSTR)(pRentInfo->GetOther()));
					pElement->setAttribute("pump", (LPCTSTR)(pRentInfo->GetPump()));
					pElement->setAttribute("manager", (LPCTSTR)(pRentInfo->GetManager()));
					pElement->setAttribute("total", (LPCTSTR)(pRentInfo->GetTotal()));
					pElement->setAttribute("remark", (LPCTSTR)(pRentInfo->GetRemark()));
					pElement->setAttribute("wuguanfei", (LPCTSTR)(pRentInfo->GetWuGuanFei()));
					pElement->setAttribute("pre_gas", (LPCTSTR)(pRentInfo->GetPreGas()));
					pElement->setAttribute("now_gas", (LPCTSTR)(pRentInfo->GetNowGas()));
					pElement->setAttribute("per_gas", (LPCTSTR)(pRentInfo->GetPerMonthGas()));
					pNode->insertBefore(pChildNode, pSubNode.GetInterfacePtr());
					pNode->insertBefore(pXMLDom->createTextNode("\n\t\t\t"), pSubNode.GetInterfacePtr());
					break;
				}

			}

			if (!bInsert)
			{
				pNode->appendChild(pChildNode);

				pNode->lastChild->appendChild(pXMLDom->createTextNode("\n\t\t\t"));

				pElement = pNode->lastChild;
				pElement->setAttribute("name", (LPCTSTR)(pRentInfo->GetName()));
				pElement->setAttribute("rent", (LPCTSTR)(pRentInfo->GetRent()));
				pElement->setAttribute("sanitation", (LPCTSTR)(pRentInfo->GetSanitation()));				
				pElement->setAttribute("parking", (LPCTSTR)(pRentInfo->GetParking()));
				pElement->setAttribute("tv", (LPCTSTR)(pRentInfo->GetTV()));
				pElement->setAttribute("body_fund", (LPCTSTR)(pRentInfo->GetBodyFund()));
				pElement->setAttribute("pre_elec", (LPCTSTR)(pRentInfo->GetPreElec()));
				pElement->setAttribute("now_elec", (LPCTSTR)(pRentInfo->GetNowElec()));
				pElement->setAttribute("pre_water", (LPCTSTR)(pRentInfo->GetPreWater()));
				pElement->setAttribute("now_water", (LPCTSTR)(pRentInfo->GetNowWater()));
				pElement->setAttribute("per_elec", (LPCTSTR)(pRentInfo->GetPerMonthElec()));
				pElement->setAttribute("per_water", (LPCTSTR)(pRentInfo->GetPerMonthWater()));
				pElement->setAttribute("other", (LPCTSTR)(pRentInfo->GetOther()));
				pElement->setAttribute("pump", (LPCTSTR)(pRentInfo->GetPump()));
				pElement->setAttribute("manager", (LPCTSTR)(pRentInfo->GetManager()));
				pElement->setAttribute("total", (LPCTSTR)(pRentInfo->GetTotal()));
				pElement->setAttribute("remark", (LPCTSTR)(pRentInfo->GetRemark()));
				pElement->setAttribute("wuguanfei", (LPCTSTR)(pRentInfo->GetWuGuanFei()));
				pElement->setAttribute("pre_gas", (LPCTSTR)(pRentInfo->GetPreGas()));
				pElement->setAttribute("now_gas", (LPCTSTR)(pRentInfo->GetNowGas()));
				pElement->setAttribute("per_gas", (LPCTSTR)(pRentInfo->GetPerMonthGas()));
				
				pNode->appendChild(pXMLDom->createTextNode("\n\t\t"));
			}


			RELEASE(pElement);
			RELEASE(pNode);
		}
		else
		{
			IXMLDOMNamedNodeMapPtr	pNodeMap;
			IXMLDOMNodeListPtr	    pNodeList;
			pNodeList = pNode->GetchildNodes();
			int nlistLen = pNodeList->Getlength();
			IXMLDOMNodePtr pSubNode = pNodeList->Getitem(nlistLen-1-nPos);
			pNodeMap    = pSubNode->Getattributes();
			int i = 0;
			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetName().GetBuffer(0));
			pRentInfo->GetName().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetRent().GetBuffer(0));
			pRentInfo->GetRent().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetSanitation().GetBuffer(0));
			pRentInfo->GetSanitation().ReleaseBuffer();


			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetParking().GetBuffer(0));
			pRentInfo->GetParking().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetTV().GetBuffer(0));
			pRentInfo->GetTV().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetBodyFund().GetBuffer(0));
			pRentInfo->GetBodyFund().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetPreElec().GetBuffer(0));
			pRentInfo->GetPreElec().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetNowElec().GetBuffer(0));
			pRentInfo->GetNowElec().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetPreWater().GetBuffer(0));
			pRentInfo->GetPreWater().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetNowWater().GetBuffer(0));
			pRentInfo->GetNowWater().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetPerMonthElec().GetBuffer(0));
			pRentInfo->GetPerMonthElec().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetPerMonthWater().GetBuffer(0));
			pRentInfo->GetPerMonthWater().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetOther().GetBuffer(0));
			pRentInfo->GetOther().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetPump().GetBuffer(0));
			pRentInfo->GetPump().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetManager().GetBuffer(0));
			pRentInfo->GetManager().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetTotal().GetBuffer(0));
			pRentInfo->GetTotal().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetRemark().GetBuffer(0));
			pRentInfo->GetRemark().ReleaseBuffer();
			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetWuGuanFei().GetBuffer(0));
			pRentInfo->GetWuGuanFei().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetPreGas().GetBuffer(0));
			pRentInfo->GetPreGas().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetNowGas().GetBuffer(0));
			pRentInfo->GetNowGas().ReleaseBuffer();

			pNodeMap->Getitem(i++)->put_text(pRentInfo->GetPerMonthGas().GetBuffer(0));
			pRentInfo->GetPerMonthGas().ReleaseBuffer();

			RELEASE(pSubNode);
			RELEASE(pNodeMap);
			RELEASE(pNodeList);
			RELEASE(pNode);
		}	

		//hr = pXMLDom->save("D://b.xml");
		hr = pXMLDom->save(cstrXMLFile.GetBuffer(0));

		if (FAILED(hr)) 
		{
			TRACE("CreateProjAssemCtrlFile:DOM Fail");
		}
		else 
		{
			TRACE("CreateProjAssemCtrlFile:DOM saved to [%s]\n",cstrXMLFile.GetBuffer(0));
		}
		cstrXMLFile.ReleaseBuffer();
		RELEASE(pXMLDom); // release DOMDocument.
		
	}
	catch(...)
	{

	}
	//CoUninitialize();  // must do it, for exactly matching.
	return PRINT_SUCCESS;
}


BOOL PrintInfoDlg::PrintList(void)
{
	try
	{
		//定义和初始化表格相关变量
		CString strTemp;
		CString strNULL = _T("    /");
		CString strName = _T("住户：");
		CString strNo1 = _T("房号：国雄楼 ");
		CString strNo2 = _T("栋 ");
		CString strRentMonth = _T("月份：");

		CString strRent = strNULL;
		double fRent = 0.0;

		CString strPump = strNULL;
		double fPump = 0.0;

		CString strManager= strNULL;
		double fManager = 0.0;

		CString strPreElec = strNULL;
		double fPreElec = 0.0;
		CString strNowElec = strNULL;
		double fNowElec = 0.0;
		CString strRealElec = strNULL;
		double fRealElec = 0.0;
		CString strPerMonthElec = strNULL;
		double fPerMonthElec = 0.0;
		CString strTotalElec = strNULL;
		double fTotalElec = 0.0;


		CString strPreWater = strNULL;
		double fPreWater = 0.0;
		CString strNowWater = strNULL;
		double fNowWater = 0.0;
		CString strRealWater = strNULL;
		double fRealWater = 0.0;
		CString strPerMonthWater = strNULL;
		double fPerMonthWater = 0.0;
		CString strTotalWater = strNULL;
		double fTotalWater = 0.0;

		CString strPreGas = strNULL;
		double fPreGas = 0.0;
		CString strNowGas= strNULL;
		double fNowGas = 0.0;
		CString strRealGas = strNULL;
		double fRealGas= 0.0;
		CString strPerMonthGas = strNULL;
		double fPerMonthGas = 0.0;
		CString strTotalGas= strNULL;
		double fTotalGas = 0.0;

		//CString strSanitation = strNULL;
		//double fSanitation = 0.0;

		CString strWuGuanFei = strNULL;
		double fWuGuanFei = 0.0;
		
		CString strTV = strNULL;
		double fTV = 0.0;

		CString strParking = strNULL;
		double fParking = 0.0;

		CString strBodyFund = strNULL;
		double fBodyFund = 0.0;

		CString strOther = strNULL;
		double fOther = 0.0;

		CString strTotal = strNULL;
		double fTotal= 0.0;

		CString strBigTotal = strNULL;

		CString strRemark = _T("备注：");

		CString strMaker = _T("制表人：");

		CString strTime = _T("打印时间：");

		//格式化表格相关变量
		m_editName.GetWindowText(strTemp);
		strName += strTemp;

		strNo1 += m_strComboEdit1;
		strNo2 += m_strComboEdit2;
		strNo1 += strNo2;

		if (m_comboRentMonth.GetCurSel() != CB_ERR)
		{
			m_comboRentMonth.GetLBText(m_comboRentMonth.GetCurSel(), strTemp);
		}
		else
		{
			strTemp = _T("");
		}
		
		strRentMonth += strTemp;

		//Rent
		m_editRent.GetWindowText(strTemp);
		SetString(strTemp, strRent);
		fRent = _wtof(strRent);
		strRent.Format(_T("%10.2f"), fRent);

		//m_editPump.GetWindowText(strTemp);
		//SetString(strTemp, strPump);
		//fPump = _wtof(strPump);
		//strPump.Format(_T("%10.2f"), fPump);

		m_editManager.GetWindowText(strTemp);
		SetString(strTemp, strManager);
		fManager = _wtof(strManager);
		strManager.Format(_T("%10.2f"), fManager);

		//Elec
		m_editPreElec.GetWindowText(strTemp);
		SetString(strTemp, strPreElec);
		fPreElec = _wtof(strPreElec);
		strPreElec.Format(_T("%9.2f"), fPreElec);

		m_editNowElec.GetWindowText(strTemp);
		SetString(strTemp, strNowElec);
		fNowElec = _wtof(strNowElec);
		strNowElec.Format(_T("%9.2f"), fNowElec);

		fRealElec = fNowElec - fPreElec;
		strRealElec.Format(_T("%8.2f"), fRealElec);
		m_strRealElec.Format(_T("%.2f"), fRealElec);		

		m_editPerMonthElec.GetWindowText(strTemp);
		SetString(strTemp, strPerMonthElec);
		fPerMonthElec = _wtof(strPerMonthElec);
		strPerMonthElec.Format(_T("%6.2f"), fPerMonthElec);

		fTotalElec = fPerMonthElec * fRealElec;
		strTotalElec.Format(_T("%10.2f"), fTotalElec);
		m_strTotalElec.Format(_T("%.2f"), fTotalElec);

		//Water
		m_editPreWater.GetWindowText(strTemp);
		SetString(strTemp, strPreWater);
		fPreWater = _wtof(strPreWater);
		strPreWater.Format(_T("%9.2f"), fPreWater);

		m_editNowWater.GetWindowText(strTemp);
		SetString(strTemp, strNowWater);
		fNowWater = _wtof(strNowWater);
		strNowWater.Format(_T("%9.2f"), fNowWater);

		fRealWater = fNowWater - fPreWater;
		strRealWater.Format(_T("%8.2f"), fRealWater);
		m_strRealWater.Format(_T("%.2f"), fRealWater);

		m_editPerMonthWater.GetWindowText(strTemp);
		SetString(strTemp, strPerMonthWater);
		fPerMonthWater = _wtof(strPerMonthWater);
		strPerMonthWater.Format(_T("%6.2f"), fPerMonthWater);

		fTotalWater = fPerMonthWater * fRealWater;
		strTotalWater.Format(_T("%10.2f"), fTotalWater);
		m_strTotalWater.Format(_T("%.2f"), fTotalWater);

		//Gas
		m_editPreGas.GetWindowText(strTemp);
		SetString(strTemp, strPreGas);
		fPreGas = _wtof(strPreGas);
		strPreGas.Format(_T("%9.2f"), fPreGas);

		m_editNowGas.GetWindowText(strTemp);
		SetString(strTemp, strNowGas);
		fNowGas = _wtof(strNowGas);
		strNowGas.Format(_T("%9.2f"), fNowGas);

		fRealGas = fNowGas - fPreGas;
		strRealGas.Format(_T("%8.2f"), fRealGas);
		m_strRealGas.Format(_T("%.2f"), fRealGas);

		m_editPerMonthGas.GetWindowText(strTemp);
		SetString(strTemp, strPerMonthGas);
		fPerMonthGas = _wtof(strPerMonthGas);
		strPerMonthGas.Format(_T("%6.2f"), fPerMonthGas);

		fTotalGas = fPerMonthGas * fRealGas;
		strTotalGas.Format(_T("%10.2f"), fTotalGas);
		m_strTotalGas.Format(_T("%.2f"), fTotalGas);

		//other
		//m_editSanitation.GetWindowText(strTemp);
		//SetString(strTemp, strSanitation);
		//fSanitation = _wtof(strSanitation);
		//strSanitation.Format(_T("%10.2f"), fSanitation);

		m_editWuGuanFei.GetWindowText(strTemp);
		SetString(strTemp, strWuGuanFei);
		fWuGuanFei = _wtof(strWuGuanFei);
		strWuGuanFei.Format(_T("%10.2f"), fWuGuanFei);

		m_editTV.GetWindowText(strTemp);
		SetString(strTemp, strTV);
		fTV = _wtof(strTV);
		strTV.Format(_T("%10.2f"), fTV);

		//m_editParking.GetWindowText(strTemp);
		//SetString(strTemp, strParking);
		//fParking = _wtof(strParking);
		//strParking.Format(_T("%10.2f"), fParking);

		m_editBodyFund.GetWindowText(strTemp);
		SetString(strTemp, strBodyFund);
		fBodyFund = _wtof(strBodyFund);
		strBodyFund.Format(_T("%10.2f"), fBodyFund);

		m_editOther.GetWindowText(strTemp);
		SetString(strTemp, strOther);
		fOther = _wtof(strOther);
		strOther.Format(_T("%10.2f"), fOther);

		fTotal = fRent + fTotalElec + fTotalWater + fTotalGas +/*fSanitation*/ fWuGuanFei + fParking + fTV + fBodyFund + fOther + fPump + fManager;
		strTotal.Format(_T("%10.2f"), fTotal);
		m_strTotal.Format(_T("%.2f"), fTotal);
		if (fTotal > 99999999.00)
		{
			strBigTotal = _T("金额太大了！");
		}
		else
		{
			NumToBig(strTotal, strBigTotal);
		}

		m_editRemark.GetWindowText(strTemp);
		strRemark += strTemp;

		m_editMaker.GetWindowText(strTemp);
		strMaker += strTemp;

		CTime timeTime;
		DWORD dwResult =m_dtTime.GetTime(timeTime);

	    int nY = timeTime.GetYear();
		int nM = timeTime.GetMonth();
		int nD = timeTime.GetDay();
		strTemp.Format(_T("%d年%02d月%02d日"), nY, nM, nD);
		strTime += strTemp;

		TCHAR szprinter[800];	
		TCHAR *szDevice,*szDriver,*szOutput;	

		//定义一个打印作业	
		static DOCINFO di={sizeof(DOCINFO),_T("printer"),NULL};	

		//得到设备字符串存入数组szprinter中	
		//GetProfileString(_T("windows"),_T("device"),_T(",,,"),szprinter,80);
		g_cfg.getPrinterAddr(szprinter);
		//	GetProfileString("MCI Extensions.BAK","aif",",,,",szprinter,80);
		//AfxMessageBox(szprinter);

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
					ParentMemDC.StartPage(); //打印机走纸,开始打印				
					ParentMemDC.SaveDC(); //保存打印机设备句柄	
					CPen cPen, *oldPan;
					cPen.CreatePen(PS_SOLID,0,MANAGER_BLACK);
					oldPan = ParentMemDC.SelectObject(&cPen);

					CFont  editFontTital;
					editFontTital.CreateFont(14, // nHeight 
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

					CFont numTotalFont;
					numTotalFont.CreateFont(14,
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

					CPoint Origin(74, 65);
					int nHight = 23;
					int nWidth[6] = {100, 90, 90, 90, 80, 100};

					int nFirstAdd = 0;
					int nHightTotal = 13*nHight;
					int nWidthTotal = 0;
					for (int i = 0; i < 6; i++)
					{
						nWidthTotal += nWidth[i];
					}

					CPoint pointS,pointE;
					pointS = Origin;
					pointE = CPoint(Origin.x + nWidthTotal, Origin.y);
					ParentMemDC.MoveTo(pointS);
					ParentMemDC.LineTo(pointE);

					pointS.y += nHight + nFirstAdd;
					pointE.y += nHight + nFirstAdd;
					ParentMemDC.MoveTo(pointS);
					ParentMemDC.LineTo(pointE);
					for (int i = 0; i < 12; i++)
					{
						pointS.y += nHight;
						pointE.y += nHight;
						ParentMemDC.MoveTo(pointS);
						ParentMemDC.LineTo(pointE);
					}

					pointS = Origin;
					pointE = CPoint(Origin.x, Origin.y + nHightTotal + nFirstAdd);
					ParentMemDC.MoveTo(pointS);
					ParentMemDC.LineTo(pointE);
					for (int i = 0; i < 6; i++)
					{
						if (i == 0 || i == 1)
						{
							pointE.y -= nHight;
						}
						if (i == 5)
						{
							pointE.y += 2*nHight;
						}
						pointS.x += nWidth[i];
						pointE.x += nWidth[i];
						ParentMemDC.MoveTo(pointS);
						ParentMemDC.LineTo(pointE);
					}
					int x = Origin.x + 10;
					int y = Origin.y + 4;
					ParentMemDC.TextOut(x, y, _T("  项    目"));
					x += nWidth[0];
					ParentMemDC.TextOut(x, y, _T(" 上月读数"));
					x += nWidth[1];
					ParentMemDC.TextOut(x, y, _T(" 本月读数"));
					x += nWidth[2];
					ParentMemDC.TextOut(x, y, _T(" 实用数量"));
					x += nWidth[3] + 5;
					ParentMemDC.TextOut(x, y, _T("单价(元)"));
					x += nWidth[4]+ 13;
					ParentMemDC.TextOut(x, y, _T("金额(元)"));

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T("  房    费"));
					for (int i = 0; i < 5; i++)
					{
						x += nWidth[i];
						if (i == 4)
						{
							ParentMemDC.TextOut(x, y, strRent);
						}
						else
						{
							ParentMemDC.TextOut(x, y, strNULL);
						}
					}

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T("  电    费"));
					x += nWidth[0];
					ParentMemDC.TextOut(x, y, strPreElec);
					x += nWidth[1];
					ParentMemDC.TextOut(x, y, strNowElec);
					x += nWidth[2];
					ParentMemDC.TextOut(x, y, strRealElec);
					x += nWidth[3];
					ParentMemDC.TextOut(x, y, strPerMonthElec);
					x += nWidth[4];
					ParentMemDC.TextOut(x, y, strTotalElec);

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T("  水    费"));
					x += nWidth[0];
					ParentMemDC.TextOut(x, y, strPreWater);
					x += nWidth[1];
					ParentMemDC.TextOut(x, y, strNowWater);
					x += nWidth[2];
					ParentMemDC.TextOut(x, y, strRealWater);
					x += nWidth[3];
					ParentMemDC.TextOut(x, y, strPerMonthWater);
					x += nWidth[4];
					ParentMemDC.TextOut(x, y, strTotalWater);

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T("  天然气费"));
					x += nWidth[0];
					ParentMemDC.TextOut(x, y, strPreGas);
					x += nWidth[1];
					ParentMemDC.TextOut(x, y, strNowGas);
					x += nWidth[2];
					ParentMemDC.TextOut(x, y, strRealGas);
					x += nWidth[3];
					ParentMemDC.TextOut(x, y, strPerMonthGas);
					x += nWidth[4];
					ParentMemDC.TextOut(x, y, strTotalGas);

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T(" 安泰物业费"));
					for (int i = 0; i < 5; i++)
					{
						x += nWidth[i];
						if (i == 4)
						{
							ParentMemDC.TextOut(x, y, strWuGuanFei);
						}
						else
						{
							ParentMemDC.TextOut(x, y, strNULL);
						}
					}


					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T(" 管理成本费"));
					for (int i = 0; i < 5; i++)
					{
						x += nWidth[i];
						if (i == 4)
						{
							ParentMemDC.TextOut(x, y, strManager);
						}
						else
						{
							ParentMemDC.TextOut(x, y, strNULL);
						}
					}


					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T(" 有线电视费"));
					for (int i = 0; i < 5; i++)
					{
						x += nWidth[i];
						if (i == 4)
						{
							ParentMemDC.TextOut(x, y, strTV);
						}
						else
						{
							ParentMemDC.TextOut(x, y, strNULL);
						}
					}

					/*x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T(" 停  车  费"));
					for (int i = 0; i < 5; i++)
					{
						x += nWidth[i];
						if (i == 4)
						{
							ParentMemDC.TextOut(x, y, strParking);
						}
						else
						{
							ParentMemDC.TextOut(x, y, strNULL);
						}
					}

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T(" 水泵加压费"));
					for (int i = 0; i < 5; i++)
					{
						x += nWidth[i];
						if (i == 4)
						{
							ParentMemDC.TextOut(x, y, strPump);
						}
						else
						{
							ParentMemDC.TextOut(x, y, strNULL);
						}
					}*/

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T("  维  修  费"));
					for (int i = 0; i < 5; i++)
					{
						x += nWidth[i];
						if (i == 4)
						{
							ParentMemDC.TextOut(x, y, strBodyFund);
						}
						else
						{
							ParentMemDC.TextOut(x, y, strNULL);
						}
					}

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T("  其    他"));
					for (int i = 0; i < 5; i++)
					{
						x += nWidth[i];
						if (i == 4)
						{
							ParentMemDC.TextOut(x, y, strOther);
						}
						else
						{
							ParentMemDC.TextOut(x, y, strNULL);
						}
					}

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T("  合    计"));
					for (int i = 0; i < 5; i++)
					{
						x += nWidth[i];
						if (i == 4)
						{
							ParentMemDC.SelectObject(&numTotalFont);
							ParentMemDC.TextOut(x, y, strTotal);
						}
						else
						{
							ParentMemDC.TextOut(x, y, strNULL);
						}
					}

					ParentMemDC.SelectObject(&editFontTital);

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, _T(" 金额(大写)"));
					x += nWidth[0];
					CString strSpace = _T("                ");
					strBigTotal = strSpace + strBigTotal;
					ParentMemDC.TextOut(x, y, strBigTotal);

					x = Origin.x + 10;
					y += nHight;
					ParentMemDC.TextOut(x, y, strRemark);

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
					ParentMemDC.TextOut(x, y, _T(" 深圳市宝安区国雄物业管理处"));

					editFontTital.DeleteObject();
					editFontTital.CreateFont(16, // nHeight 
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
						_T("楷体_GB2312")); // lpszFac 
					ParentMemDC.SelectObject(&editFontTital);
					x = Origin.x + 10;
					y = Origin.y- 23;
					ParentMemDC.TextOut(x, y, strNo1);

					x += 255;
					ParentMemDC.TextOut(x, y, strName);

					x += 175;
					ParentMemDC.TextOut(x, y, strRentMonth);

					editFontTital.DeleteObject();
					editFontTital.CreateFont(14, // nHeight 
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
						_T("楷体_GB2312")); // lpszFac 
					ParentMemDC.SelectObject(&editFontTital);
					x = Origin.x;
					y = Origin.y + nHightTotal + 15;
					ParentMemDC.TextOut(x, y, strTime);

					x += 190;
					ParentMemDC.TextOut(x, y, _T("收款人："));

					x += 180;
					ParentMemDC.TextOut(x, y, _T("收款日期："));

					ParentMemDC.SelectObject(oldPan);
					ParentMemDC.SelectObject(OldFont);

					ParentMemDC.RestoreDC(-1); //恢复打印机设备句柄				
					ParentMemDC.EndPage(); //打印机停纸,停止打印				
					ParentMemDC.EndDoc(); //结束一个打印作业				
					//MessageBox(_T("打印成功!"),_T("提示1"),MB_ICONINFORMATION);
				}			
				//用API函数DeleteDC销毁一个打印机设备句柄			
				ParentMemDC.DeleteDC();	
				//MessageBox(_T("打印成功!"),_T("提示2"),MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(_T("打开打印机失败!"));
			}
		}
		else			
		{	
			MessageBox(_T("没有默认打印机,或者没有安装打印机!"));
			return FALSE;			
		} 
		return TRUE;
		
	}
	catch(...)
	{
		AfxMessageBox(_T("Print Error Occur!"));
		return FALSE;
	}	
}

void PrintInfoDlg::NumToBig(CString strTotal, CString& strBigTotal)
{ 
	CString strOld[4]     = {_T("拾"), _T("佰"), _T("仟"), _T("万")};
	CString strMoney[3]   = {_T("分"), _T("角"), _T("元")};
	CString strOldNum[10] = {_T("零"), _T("壹"), _T("贰"), _T("叁"), _T("肆"), 
		                     _T("伍"), _T("陆"), _T("柒"), _T("捌"), _T("玖")};

	if (strTotal.IsEmpty())
	{
		return;
	}
	else
	{
	}

	double fTemp = _wtof(strTotal);
	if (fTemp < 0.001)
	{
		strBigTotal = _T("零元整");
		return;
	}

	strTotal.Remove(_T(' '));
	int nLength = strTotal.GetLength();
	CString strTemp;
	TCHAR * pStrTotal = strTotal.GetBuffer(0);

	for (int i = 0; i < nLength; i++)
	{
		if (nLength - i < 4)
		{
			if (nLength - i == 3)
			{
				if(fTemp < 1.00)
				{
				}
				else
				{
					strTemp += strMoney[nLength-i-1];
				}
				continue;
			}
			if ((pStrTotal[i]&0x0F))
			{
				strTemp += strOldNum[pStrTotal[i]&0x0F];
				strTemp += strMoney[nLength-i-1];
			}
		}
		else
		{ 
			if (i == 0)
			{
				if (pStrTotal[i]&0x0F)
				{
					strTemp += strOldNum[pStrTotal[i]&0x0F];
					if ((nLength-i-5) >= 0)
					{
						strTemp += strOld[(nLength-i-5)%4];
					}
				}
			}
			else
			{
				if ((((pStrTotal[i+1]&0x0F) == 0) || (nLength - i == 4)) && ((pStrTotal[i]&0x0F) == 0))
				{
					if (nLength > 7 && nLength - i == 8)
					{
						strTemp += strOld[(nLength-i-5)%4];
					}
					continue;
				}
				else
				{
					strTemp += strOldNum[pStrTotal[i]&0x0F];
				}

				if ((pStrTotal[i]&0x0F) && ((nLength-i-5) >= 0))
				{
					strTemp += strOld[(nLength-i-5)%4];
				}
				else
				{
				}
			}
		}
	}
	strBigTotal = strTemp;
	if (_wtoi(strTotal.Right(2)) == 0)
	{
		 strBigTotal+= _T("整");
	}
}

void PrintInfoDlg::OnBnClickedButtonPre()
{
	ClickArrow(FALSE);
	m_editNowElec.SetFocus();
}

void PrintInfoDlg::OnBnClickedButtonNext()
{
	ClickArrow(TRUE);
	m_editNowElec.SetFocus();
}

void PrintInfoDlg::DialogShow(CDataBuildInfoModel * pBuildData)
{
	CDataRentInfoModel * pRentData;
	POSITION posRent = NULL;
	POSITION posRentPre = NULL;
	CString strTemp;
	SetTimeTitle(strTemp, m_dtTime, m_comboRentMonth);

	for (posRent = pBuildData->m_ptrRentInfoList.GetTailPosition(); posRent != NULL;)
	{
		posRentPre = posRent;
		pRentData = pBuildData->m_ptrRentInfoList.GetPrev(posRent);

		//显示对应的数据
		if (pRentData->GetTitle() == strTemp)
		{
			m_editName.SetWindowText(pRentData->GetName());
			m_editRent.SetWindowText(pRentData->GetRent());
			m_editTV.SetWindowText(pRentData->GetTV());
			//m_editParking.SetWindowText(pRentData->GetParking());
			//m_editSanitation.SetWindowText(pRentData->GetSanitation());
			m_editBodyFund.SetWindowText(pRentData->GetBodyFund());
			m_editPreElec.SetWindowText(pRentData->GetPreElec());
			m_editNowElec.SetWindowText(pRentData->GetNowElec());
			m_editPreWater.SetWindowText(pRentData->GetPreWater());
			m_editNowWater.SetWindowText(pRentData->GetNowWater());
			m_editPerMonthElec.SetWindowText(pRentData->GetPerMonthElec());
			m_editPerMonthWater.SetWindowText(pRentData->GetPerMonthWater());
			m_editOther.SetWindowText(pRentData->GetOther());
			//m_editPump.SetWindowText(pRentData->GetPump());
			m_editManager.SetWindowText(pRentData->GetManager());
			m_editRemark.SetWindowText(pRentData->GetRemark());
			m_editWuGuanFei.SetWindowText(pRentData->GetWuGuanFei());

			m_editPreGas.SetWindowText(pRentData->GetPreGas());
			m_editNowGas.SetWindowText(pRentData->GetNowGas());
			m_editPerMonthGas.SetWindowText(pRentData->GetPerMonthGas());

			break;
		}

		//排序从小到大，如果最后一个都小于目前的时间，则显示最后的一组数据
		if (pRentData->GetTitle() < strTemp)
		{
			m_editName.SetWindowText(pRentData->GetName());
			m_editRent.SetWindowText(pRentData->GetRent());
			m_editTV.SetWindowText(pRentData->GetTV());
			//m_editParking.SetWindowText(pRentData->GetParking());
			//m_editSanitation.SetWindowText(pRentData->GetSanitation());
			m_editBodyFund.SetWindowText(pRentData->GetBodyFund());
			m_editPreElec.SetWindowText(pRentData->GetNowElec());
			m_editNowElec.SetWindowText(_T(""));
			m_editPreWater.SetWindowText(pRentData->GetNowWater());
			m_editNowWater.SetWindowText(_T(""));
			m_editPerMonthElec.SetWindowText(pRentData->GetPerMonthElec());
			m_editPerMonthWater.SetWindowText(pRentData->GetPerMonthWater());
			m_editOther.SetWindowText(pRentData->GetOther());
			//m_editPump.SetWindowText(pRentData->GetPump());
			m_editManager.SetWindowText(pRentData->GetManager());
			m_editRemark.SetWindowText(pRentData->GetRemark());
			m_editWuGuanFei.SetWindowText(pRentData->GetWuGuanFei());

			m_editPreGas.SetWindowText(pRentData->GetNowGas());
			m_editNowGas.SetWindowText(_T(""));
			m_editPerMonthGas.SetWindowText(pRentData->GetPerMonthGas());
			break;
		}
	}


	if (posRentPre != NULL)
	{

	}
	else
	{
		m_editName.SetWindowText(_T(""));
		m_editRent.SetWindowText(_T(""));
		m_editTV.SetWindowText(_T(""));
		//m_editParking.SetWindowText(_T(""));
		//m_editSanitation.SetWindowText(_T(""));
		m_editBodyFund.SetWindowText(_T(""));
		m_editPreElec.SetWindowText(_T(""));
		m_editNowElec.SetWindowText(_T(""));
		m_editPreWater.SetWindowText(_T(""));
		m_editNowWater.SetWindowText(_T(""));
		//m_editPerMonthElec.SetWindowText(_T(""));
		//m_editPerMonthWater.SetWindowText(_T(""));
		m_editOther.SetWindowText(_T(""));
		//m_editPump.SetWindowText(_T(""));
		m_editManager.SetWindowText(_T(""));
		m_editRemark.SetWindowText(_T(""));
		m_editWuGuanFei.SetWindowText(_T(""));
		m_editPreGas.SetWindowText(_T(""));
		m_editNowGas.SetWindowText(_T(""));
	}
}

void PrintInfoDlg::ClickArrow(BOOL b)
{
	CString strTemp1;	

	int nLen = m_comboBuild2.GetCount();
	int nThis = m_comboBuild2.GetCurSel();

	if (b)
	{
		if (nThis >= nLen-1)
		{
			return;
		}
		else
		{
			nThis++;
		}
	}
	else
	{
		if (nThis <= 0)
		{
			return;
		}
		else
		{
			nThis--;
		}

	}
	
	m_comboBuild2.SetCurSel(nThis);

	m_comboBuild2.GetLBText(nThis, strTemp1);

	if (strTemp1 == m_strComboEdit2)
	{
		return;
	}
	else
	{
		m_strComboEdit2 = strTemp1;
	}

	CDataBuildInfoModel * pBuildData;
	CString strTemp2;
	int nHouseFirst = 0;
	for (POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL; nHouseFirst++)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);
		strTemp2 = GetTitleLastNum(pData->GetTitle());
		if (strTemp2 == m_strComboEdit1)
		{
			int i = 0;
			for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL; i++)
			{
				pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);
				strTemp2 = GetHouseLastNum(pBuildData->GetNO());
				if (m_strComboEdit2 == strTemp2)
				{
					DialogShow(pBuildData);
					break;
				}
			}
			break;
		}
	}
	m_strNo = m_strComboEdit1+_T("-") + m_strComboEdit2;

}

void PrintInfoDlg::OnCbnCloseupComboMonth()
{
	CString strTemp1;
	int nLen = m_comboRentMonth.GetCount();
	int nThis = m_comboRentMonth.GetCurSel();
	m_comboRentMonth.GetLBText(nThis, strTemp1);

	if (strTemp1 == m_strComboRentMonth)
	{
		return;
	}
	else
	{
		m_strComboRentMonth = strTemp1;
	}

	CDataBuildInfoModel * pBuildData;
	CString strTemp2;
	int nHouseFirst = 0;
	for (POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL; nHouseFirst++)
	{
		CDataModel * pData = m_pDataModelList->GetNext(pos);
		strTemp2 = GetTitleLastNum(pData->GetTitle());
		if (strTemp2 == m_strComboEdit1)
		{
			int i = 0;
			for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL; i++)
			{
				pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);
				strTemp2 = GetHouseLastNum(pBuildData->GetNO());
				if (m_strComboEdit2 == strTemp2)
				{
					DialogShow(pBuildData);
					break;
				}
			}
			break;
		}
	}
	m_strNo = m_strComboEdit1 + _T("-") + m_strComboEdit2;
}


