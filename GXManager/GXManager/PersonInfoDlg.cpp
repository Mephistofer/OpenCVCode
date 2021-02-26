// PersonInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GXManager.h"
#include "PersonInfoDlg.h"
#include "GXManagerDlg.h"

// CPersonInfoDlg 对话框

IMPLEMENT_DYNAMIC(CPersonInfoDlg, CDialog)

CPersonInfoDlg::CPersonInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPersonInfoDlg::IDD, pParent)
{	
}

CPersonInfoDlg::~CPersonInfoDlg()
{
}

void CPersonInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PERSON_INFO_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_PERSON_INFO_TEL, m_editTel);
	DDX_Control(pDX, IDC_EDIT_PERSON_INFO_WORK, m_editWork);
	DDX_Control(pDX, IDC_EDIT_PERSON_INFO_REMARK, m_editRemark);
	//DDX_Control(pDX, IDC_STATIC_PERSON_INFO_BUILD_1, m_staticNo1);
	//DDX_Control(pDX, IDC_STATIC_PERSON_INFO_BUILD_2, m_staticNo2);
	DDX_Control(pDX, IDC_COMBO_BUILD1, m_comboBuild1);
	DDX_Control(pDX, IDC_COMBO_BUILD2, m_comboBuild2);
	DDX_Control(pDX, IDC_EDIT_RENT, m_editRent);
	DDX_Control(pDX, IDC_EDIT_HOUSE_NUM, m_editHouseNum);
}


BEGIN_MESSAGE_MAP(CPersonInfoDlg, CDialog)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_EDIT_OK, &CPersonInfoDlg::OnBnClickedEditOk)
//	ON_EN_SETFOCUS(IDC_EDIT_PERSON_INFO_NAME, &CPersonInfoDlg::OnEnSetfocusEditPersonInfoName)
	ON_CBN_CLOSEUP(IDC_COMBO_BUILD1, &CPersonInfoDlg::OnCbnCloseupComboBuild1)
	ON_CBN_CLOSEUP(IDC_COMBO_BUILD2, &CPersonInfoDlg::OnCbnCloseupComboBuild2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPersonInfoDlg 消息处理程序

int CPersonInfoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	return 0;
}

BOOL CPersonInfoDlg::OnInitDialog()
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
	//m_editTel.SetFont(&m_editFont);
	m_editWork.SetFont(&m_editFont);
	m_editRemark.SetFont(&m_editFont);	
	m_comboBuild1.SetFont(&m_StaticFont);
	m_comboBuild2.SetFont(&m_StaticFont);
	//m_editRent.SetFont(&m_editFont);
	//m_staticNo1.SetFont(&m_StaticFont);
	//m_staticNo2.SetFont(&m_StaticFont);
	CDataBuildInfoModel * pBuildData;
	CString strTemp;
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
				}
			}
		}
	}
   
	m_editName.SetWindowText(m_strName);
	m_editTel.SetWindowText(m_strTel);
	m_editWork.SetWindowText(m_strWork);
	m_editRemark.SetWindowText(m_strRemark);
	m_editRent.SetWindowText(m_strRent);
	m_editHouseNum.SetWindowText(GetHouseLastNum(m_strNo));

	return TRUE;
}

HBRUSH CPersonInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	if (nCtlColor == CTLCOLOR_STATIC) //静态文本
	{
		pDC->SetBkMode(TRANSPARENT); 
		return  (HBRUSH)::GetStockObject(NULL_BRUSH);

		//pDC->SetBkColor(MANAGER_WHITE);//字体背景色

		//return CreateSolidBrush(MANAGER_WHITE); //控件背景色

	}
	if (nCtlColor == CTLCOLOR_EDIT)
	{

		pDC->SetTextColor(MANAGER_BLUE);
		//pDC->SetBkColor(MANAGER_WHITE);//字体背景色

	}	

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL CPersonInfoDlg::ModifyXML(CString cstrXMLFile, CString strNO)
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
			return FALSE;
		}
	
		pXMLDom->async = VARIANT_FALSE; // default is true, must synchronization.

		// load XML file.
		if ( pXMLDom->load(cstrXMLFile.GetBuffer(0)) != VARIANT_TRUE)
		// if fail to load XML file...
		{
			RELEASE(pXMLDom); // release DOMDocument.
			//CoUninitialize();  // must do it, for exactly matching.

			return FALSE;
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
		m_editName.GetWindowText(strTemp);
		pBuildData->SetName(strTemp);
		m_editTel.GetWindowText(strTemp);
		pBuildData->SetTel(strTemp);
		m_editWork.GetWindowText(strTemp);
		pBuildData->SetWork(strTemp);
		m_editRemark.GetWindowText(strTemp);
		pBuildData->SetRemark(strTemp);
		m_editRent.GetWindowText(strTemp);
		pBuildData->SetRent(strTemp);
		m_editHouseNum.GetWindowText(strTemp);

		CString strTemp2;
		strTemp2.Format(_T("%s-%s"), m_strComboEdit1, strTemp);

		pBuildData->SetNO(strTemp2);

		//IXMLDOMNodePtr			pChildNode;
		// CDataTradeModel *pDataTrade = new CDataTradeModel;
		searchPath += _T("/");
		searchPath += pBuildData->GetTitle();

		IXMLDOMNamedNodeMapPtr	pNodeMap;

		pNode = pXMLDom->selectSingleNode(static_cast<_bstr_t>(searchPath));
	

		pNodeMap    = pNode->attributes;
		pNodeMap->Getitem(0)->put_text(pBuildData->GetNO().GetBuffer(0));
		pBuildData->GetName().ReleaseBuffer();
		pNodeMap->Getitem(1)->put_text(pBuildData->GetName().GetBuffer(0));
		pBuildData->GetName().ReleaseBuffer();
		pNodeMap->Getitem(2)->put_text(pBuildData->GetTel().GetBuffer(0));
		pBuildData->GetTel().ReleaseBuffer();
		pNodeMap->Getitem(3)->put_text(pBuildData->GetWork().GetBuffer(0));
		pBuildData->GetWork().ReleaseBuffer();
		pNodeMap->Getitem(4)->put_text(pBuildData->GetRemark().GetBuffer(0));
		pBuildData->GetRemark().ReleaseBuffer();
		pNodeMap->Getitem(5)->put_text(pBuildData->GetRent().GetBuffer(0));
		pBuildData->GetRent().ReleaseBuffer();

		RELEASE(pNodeMap);
		RELEASE(pNode);
	
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
		RELEASE(pXMLDom);
	}
	catch(...)
	{

	}
	//CoUninitialize();
	return TRUE;
}

void CPersonInfoDlg::SetParentWnd(CWnd* p)
{
	m_pParent = p;
}

void CPersonInfoDlg::OnCbnCloseupComboBuild1()
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
				if (i == 0)
				{
					//为了让房号尽快显示
					m_comboBuild2.SetCurSel(0);

                    m_comboBuild2.GetLBText(m_comboBuild2.GetCurSel(), strTemp2);
						
					m_strComboEdit2 = strTemp2;	
					m_editName.SetWindowText(pBuildData->GetName());
					m_editTel.SetWindowText(pBuildData->GetTel());
					m_editWork.SetWindowText(pBuildData->GetWork());
					m_editRemark.SetWindowText(pBuildData->GetRemark());
					m_editRent.SetWindowText(pBuildData->GetRent());
					m_editHouseNum.SetWindowText(GetHouseLastNum(pBuildData->GetNO()));
				}
			}
			break;
		}
	}
	m_editName.UpdateData(FALSE);
	m_editTel.UpdateData(FALSE);
	m_editWork.UpdateData(FALSE);
	m_editName.UpdateData(FALSE);
	m_editRemark.UpdateData(FALSE);
	m_editRent.UpdateData(FALSE);
	m_strNo = m_strComboEdit1+_T("-") + m_strComboEdit2;
}

void CPersonInfoDlg::OnCbnCloseupComboBuild2()
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
					//为了让房号尽快显示				
					m_editName.SetWindowText(pBuildData->GetName());
					m_editTel.SetWindowText(pBuildData->GetTel());
					m_editWork.SetWindowText(pBuildData->GetWork());
					m_editRemark.SetWindowText(pBuildData->GetRemark());
					m_editRent.SetWindowText(pBuildData->GetRent());
					m_editHouseNum.SetWindowText(GetHouseLastNum(pBuildData->GetNO()));
					break;
				}
			}
			break;
		}
	}
	m_editName.UpdateData(FALSE);
	m_editTel.UpdateData(FALSE);
	m_editWork.UpdateData(FALSE);
	m_editName.UpdateData(FALSE);
	m_editRemark.UpdateData(FALSE);
	m_editRent.UpdateData(FALSE);
	m_strNo = m_strComboEdit1+_T("-") + m_strComboEdit2;
}

void CPersonInfoDlg::OnBnClickedEditOk()
{
	UpdateData(TRUE);
	CString strPath = BUILD_DATA_PATH;
	CString strNo;
	if (m_comboBuild1.GetCurSel() != CB_ERR)
	{
		m_comboBuild1.GetLBText(m_comboBuild1.GetCurSel(), strNo);
	}

	ModifyXML(strPath, strNo);
	CoUninitialize();
	((CGXManagerDlg*)m_pParent)->UpdateList();
	CDialog::OnOK();

}

void CPersonInfoDlg::OnPaint()
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
