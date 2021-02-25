// InsertInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GXManager.h"
#include "InsertInfoDlg.h"
#include "afxdialogex.h"
#include "GXManagerDlg.h"

// CInsertInfoDlg 对话框

IMPLEMENT_DYNAMIC(CInsertInfoDlg, CDialogEx)

CInsertInfoDlg::CInsertInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInsertInfoDlg::IDD, pParent)
{

}

CInsertInfoDlg::~CInsertInfoDlg()
{
}

void CInsertInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INSERT_PERSON_INFO_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_INSERT_PERSON_INFO_TEL, m_editTel);
	DDX_Control(pDX, IDC_EDIT_INSERT_PERSON_INFO_WORK, m_editWork);
	DDX_Control(pDX, IDC_EDIT_INSERT_PERSON_INFO_REMARK, m_editRemark);
	//DDX_Control(pDX, IDC_STATIC_PERSON_INFO_BUILD_1, m_staticNo1);
	//DDX_Control(pDX, IDC_STATIC_PERSON_INFO_BUILD_2, m_staticNo2);
	DDX_Control(pDX, IDC_COMBO_INSERT_BUILD1, m_comboBuild1);

	DDX_Control(pDX, IDC_EDIT_INSERT_RENT, m_editRent);
	DDX_Control(pDX, IDC_EDIT_INSERT_HOUSE_NUM, m_editHouseNum);
}


BEGIN_MESSAGE_MAP(CInsertInfoDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_EDIT_INSERT_OK, &CInsertInfoDlg::OnBnClickedInsertOk)
	//	ON_EN_SETFOCUS(IDC_EDIT_PERSON_INFO_NAME, &CPersonInfoDlg::OnEnSetfocusEditPersonInfoName)
	ON_CBN_CLOSEUP(IDC_COMBO_INSERT_BUILD1, &CInsertInfoDlg::OnCbnCloseupComboBuild1)

	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_EDIT_INSERT_CACEL, &CInsertInfoDlg::OnBnClickedEditInsertCacel)
END_MESSAGE_MAP()


// CInsertInfoDlg 消息处理程序
int CInsertInfoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	return 0;
}

BOOL CInsertInfoDlg::OnInitDialog()
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
				
			}
		}
	}

	return TRUE;
}

HBRUSH CInsertInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

BOOL CInsertInfoDlg::InsertXML(CString cstrXMLFile, CString strNO)
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
		if (pXMLDom->load(cstrXMLFile.GetBuffer(0)) != VARIANT_TRUE)
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
		for (POSITION pos = m_pDataModelList->GetHeadPosition(); pos != NULL;)
		{
			CDataModel * pData = m_pDataModelList->GetNext(pos);

			int i = searchPath.GetLength() - searchPath.Find('/');
			CString u = searchPath.Right(i - 1);
			if (pData->GetTitle() == searchPath.Right(searchPath.GetLength() - searchPath.Find('/') - 1))
			{
				pBuildData = new CDataBuildInfoModel;
				pData->m_ptrBuildInfoList.AddTail(pBuildData);
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


		//searchPath += _T("/");
		//searchPath += pBuildData->GetTitle();

		IXMLDOMNamedNodeMapPtr	pNodeMap;
		IXMLDOMElementPtr pElement;

		pNode = pXMLDom->selectSingleNode(static_cast<_bstr_t>(searchPath));

		IXMLDOMNodePtr			pSubNode;
		IXMLDOMNodeListPtr	    pSubNodeList;

		pSubNodeList = pNode->GetchildNodes();
		int nRentChild = pSubNodeList->Getlength();
		CString strTitleInsert;
		strTitleInsert.Format(_T("NO%03d"), nRentChild+1);

		IXMLDOMNodePtr	pChildNode = pXMLDom->createElement((LPCTSTR)strTitleInsert);
		pBuildData->SetTitle(strTitleInsert);
		if (pChildNode == NULL)
		{
			RELEASE(pXMLDom); // release DOMDocument.
			//CoUninitialize();  // must do it, for exactly matching.
			return PRINT_ERROR;
		}

		pNode->appendChild(pChildNode);
		pNode->lastChild->appendChild(pXMLDom->createTextNode("\n\t\t"));
		pElement = pNode->lastChild;
		pElement->setAttribute("no", (LPCTSTR)(pBuildData->GetNO()));
		pElement->setAttribute("name", (LPCTSTR)(pBuildData->GetName()));
		pElement->setAttribute("tel", (LPCTSTR)(pBuildData->GetTel()));
		pElement->setAttribute("work", (LPCTSTR)(pBuildData->GetWork()));
		pElement->setAttribute("remark", (LPCTSTR)(pBuildData->GetRemark()));
		pElement->setAttribute("rent", (LPCTSTR)(pBuildData->GetRent()));
		pNode->appendChild(pXMLDom->createTextNode("\n\t"));

		RELEASE(pElement);
		RELEASE(pNode);
		RELEASE(pNode);

		hr = pXMLDom->save(cstrXMLFile.GetBuffer(0));

		if (FAILED(hr))
		{
			TRACE("CreateProjAssemCtrlFile:DOM Fail");
		}
		else
		{
			TRACE("CreateProjAssemCtrlFile:DOM saved to [%s]\n", cstrXMLFile.GetBuffer(0));
		}
		cstrXMLFile.ReleaseBuffer();
		RELEASE(pXMLDom);
	}
	catch (...)
	{

	}
	//CoUninitialize();
	return TRUE;
}

void CInsertInfoDlg::SetParentWnd(CWnd* p)
{
	m_pParent = p;
}

void CInsertInfoDlg::OnCbnCloseupComboBuild1()
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

	m_editName.UpdateData(FALSE);
	m_editTel.UpdateData(FALSE);
	m_editWork.UpdateData(FALSE);
	m_editName.UpdateData(FALSE);
	m_editRemark.UpdateData(FALSE);
	m_editRent.UpdateData(FALSE);
	m_strNo = m_strComboEdit1 + _T("-") + m_strComboEdit2;
}

void CInsertInfoDlg::OnBnClickedInsertOk()
{
	UpdateData(TRUE);
	CString strPath = BUILD_DATA_PATH;
	CString strNo;
	if (m_comboBuild1.GetCurSel() != CB_ERR)
	{
		m_comboBuild1.GetLBText(m_comboBuild1.GetCurSel(), strNo);
	}

	CString strTemp;
	m_editHouseNum.GetWindowText(strTemp);
	if (strTemp.IsEmpty())
	{
		AfxMessageBox(_T("没有输入房号！"));
		return;
	}

	CString strBox;
	strBox.Format(_T("确认插入房号 %s ？"), strTemp);
	if (IDYES == AfxMessageBox(strBox, MB_YESNO | MB_ICONQUESTION))
	{
		InsertXML(strPath, strNo);
		CoUninitialize();
	}
	else
	{

	}

	((CGXManagerDlg*)m_pParent)->UpdateList();
	CDialog::OnOK();

}

void CInsertInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);

	CDC* pDC = &dc;

	//画布定义
	CBitmap bmpCanvas;
	CBitmap Bitmap;
	CBitmap* pOldBitmap;

	CDC ParentMemDC;
	ParentMemDC.CreateCompatibleDC(pDC);
	bmpCanvas.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = ParentMemDC.SelectObject(&bmpCanvas);

	//整个画板填充背景色
	CBrush  brushFrame(MANAGER_CREAM);
	//画边框和背景
	CBrush* pOldBrush = ParentMemDC.SelectObject(&brushFrame);
	ParentMemDC.FillRect(rect, &brushFrame);
	ParentMemDC.SelectObject(pOldBrush);

	//复制图片到屏幕
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &ParentMemDC, 0, 0, SRCCOPY);
	ParentMemDC.SelectObject(pOldBitmap);
	ReleaseDC(&ParentMemDC);
}


void CInsertInfoDlg::OnBnClickedEditInsertCacel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
