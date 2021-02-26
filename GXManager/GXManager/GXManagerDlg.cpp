
// GXManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GXManager.h"
#include "GXManagerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGXManagerDlg 对话框




CGXManagerDlg::CGXManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGXManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGXManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAIN, m_ctrListMain);
	DDX_Control(pDX, IDC_EDIT, m_buttEdit);
	DDX_Control(pDX, IDC_PRINT, m_buttPrint);
	DDX_Control(pDX, IDC_STATISTIC, m_buttStatistic);
	DDX_Control(pDX, IDC_INSERT, m_buttInsert);
	DDX_Control(pDX, IDC_DELETE, m_buttDelete);
}

BEGIN_MESSAGE_MAP(CGXManagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
//	ON_NOTIFY(HDN_BEGINDRAG, 0, &CGXManagerDlg::OnHdnBegindragListMain)
//ON_NOTIFY(HDN_ENDTRACK, 0, &CGXManagerDlg::OnHdnEndtrackListMain)
//ON_NOTIFY(HDN_TRACK, 0, &CGXManagerDlg::OnHdnTrackListMain)
ON_BN_CLICKED(IDC_EDIT, &CGXManagerDlg::OnBnClickedEdit)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MAIN, &CGXManagerDlg::OnLvnItemchangedListMain)
ON_BN_CLICKED(IDC_PRINT, &CGXManagerDlg::OnBnClickedPrint)
ON_BN_CLICKED(IDC_STATISTIC, &CGXManagerDlg::OnBnClickedStatistic)
ON_BN_CLICKED(IDC_INSERT, &CGXManagerDlg::OnBnClickedInsert)
ON_BN_CLICKED(IDC_DELETE, &CGXManagerDlg::OnBnClickedDelete)
END_MESSAGE_MAP()


// CGXManagerDlg 消息处理程序

BOOL CGXManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_nListRow = 0;
	m_nListCol = 0;
	SortXMLFile(BUILD_DATA_PATH);
	CoUninitialize();

    InitCtrlListMain(); // (yjzhang 2011-03-09)

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGXManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGXManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
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
		CBrush  brushFrame(MANAGER_BODY_BLUE);
		//画边框和背景
		CBrush* pOldBrush = ParentMemDC.SelectObject(&brushFrame);
		ParentMemDC.FillRect(rect,&brushFrame);


		CPen cPen1, *oldPan;
		cPen1.CreatePen(PS_SOLID,0,MANAGER_BLACK);
		oldPan = ParentMemDC.SelectObject(&cPen1);


		ParentMemDC.SelectObject(oldPan);
		ParentMemDC.SelectObject(pOldBrush);

		//复制图片到屏幕
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &ParentMemDC, 0, 0, SRCCOPY);
		ParentMemDC.SelectObject(pOldBitmap);
		ReleaseDC(&ParentMemDC);
		//CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGXManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGXManagerDlg::InitCtrlListMain(void)
{
	try
	{
		m_editFont.CreateFont(18, // nHeight 
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

		DWORD dwStyle = m_ctrListMain.GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮
		dwStyle |= LVS_EX_GRIDLINES;//网格线
		dwStyle |= LVS_EX_SUBITEMIMAGES;

		m_ctrListMain.SetExtendedStyle(dwStyle);

		// 	m_ImageList.Create(17,17,ILC_COLOR32|ILC_MASK,5,1);
		// 	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		// 	m_ImageList.Add(hIcon);
		// 	hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		// 	m_ImageList.Add(hIcon);
		// 	
		// 	m_ctrlListFirmware.SetImageList(&m_ImageList, LVSIL_SMALL);	
		CString cstrXMLFile = BUILD_DATA_PATH;
		while  (!m_DataModelList.IsEmpty())
		{
			delete m_DataModelList.GetTail();
			m_DataModelList.RemoveTail();
		}
		InitListXML(cstrXMLFile,&m_DataModelList);
		CoUninitialize();
		m_ctrListMain.InsertColumn(0, _T("房租"), LVCFMT_CENTER, 0);
		m_ctrListMain.InsertColumn(0, _T("备注"), LVCFMT_CENTER, 290);
		m_ctrListMain.InsertColumn(0, _T("工作单位"), LVCFMT_CENTER, 125);
		m_ctrListMain.InsertColumn(0, _T( "电话"), LVCFMT_CENTER, 150);
		m_ctrListMain.InsertColumn(0, _T( "姓名"), LVCFMT_CENTER, 110);	
		m_ctrListMain.InsertColumn(0, _T( "房号"), LVCFMT_CENTER, 150);	
		m_ctrListMain.InsertColumn(0, _T( "序号"), LVCFMT_CENTER,75);	
		m_ctrListMain.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
		m_ctrListMain.SetItemHeight(25);
		m_ctrListMain.SetListHeaderHeight(1.2);		
		m_ctrListMain.SetListHeaderTextHeight(16);
        UpdateListFirst();
		//::SendMessage(m_ctrListMain.GetSafeHwnd(),WM_KEYDOWN,VK_DOWN,0);
		ShowWindow(SW_MAXIMIZE);
	}
	catch (...)
	{

	}
}

void CGXManagerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	try
	{
		if (m_ctrListMain.m_hWnd==NULL)
		{
			return;
		}
		CRect cr;
		GetClientRect(&cr);
		int left = cr.left + 25;
		int top = cr.top + 30;
		int right = cr.right - 125 ;
		int bottom = cr.bottom - 30;

		int nLength = right - left;
		int nHeight = bottom - top;

		m_ctrListMain.MoveWindow(CRect(left, top, right, bottom));	
		m_buttDelete.MoveWindow(CRect(cr.right - 100, cr.bottom - 550, cr.right - 20, cr.bottom - 500));
		m_buttDelete.ShowWindow(SW_HIDE);
		m_buttInsert.MoveWindow(CRect(cr.right - 100, cr.bottom - 450, cr.right - 20, cr.bottom - 400));
		m_buttStatistic.MoveWindow(CRect(cr.right - 100, cr.bottom - 350, cr.right - 20, cr.bottom- 300));
		m_buttEdit.MoveWindow(CRect(cr.right - 100, cr.bottom - 250, cr.right - 20, cr.bottom- 200));
		m_buttPrint.MoveWindow(CRect(cr.right - 100, cr.bottom - 150, cr.right - 20, cr.bottom - 100));

		//m_ctrListMain.SetColumnWidth(1, nLength * 0.25);
		//m_ctrListMain.SetColumnWidth(2, nLength * 0.25);
		//m_ctrListMain.SetColumnWidth(3, nLength * 0.25);
		if (nLength-610 < 290)
		{
			m_ctrListMain.SetColumnWidth(5, 300);
		}
		else
		{
			m_ctrListMain.SetColumnWidth(5, nLength-610);
		}
		//m_ctrListMain.SetFont(&m_editFont);

		//m_ctrListMain.SetListHeaderTextWidth(0);
		m_ctrListMain.Invalidate(FALSE);
	}
	catch (...)
	{
	}
}

BOOL CGXManagerDlg::AddNodeToXML()
{
	using MSXML2::IXMLDOMDocumentPtr;
	using MSXML2::DOMDocument60;
	using MSXML2::IXMLDOMNodePtr;
	using MSXML2::IXMLDOMNodeListPtr;
	using MSXML2::IXMLDOMNamedNodeMapPtr;
	using MSXML2::IXMLDOMElementPtr;

	// XML文件中增加新节点.	
	IXMLDOMDocumentPtr	pXMLDom;
	IXMLDOMNodePtr		pNode;
	CString cstrXMLFile = BUILD_DATA_PATH; 

	CoInitialize(NULL); // for single thread to create COM Object(msxml4.dll).

	HRESULT hr = pXMLDom.CreateInstance(__uuidof(DOMDocument60));
	if (FAILED(hr))
	{
		return FALSE;
	}
	try
	{
		pXMLDom->async = VARIANT_FALSE; // default is true, must synchronization.

		// load XML file.
		if ( pXMLDom->load(cstrXMLFile.GetBuffer(0)) != VARIANT_TRUE)
			// if fail to load XML file...
		{

			RELEASE(pXMLDom); // release DOMDocument.
			//CoUninitialize();  // must do it, for exactly matching.
			CString msg;
			msg.Format(_T("加载[%s]失败,请检查是否正确配置了文件！"),cstrXMLFile);
			AfxMessageBox(msg);
			return FALSE;
		}
		cstrXMLFile.ReleaseBuffer();

		// transaction		
		CString searchPath = _T("branchbank/trs/交易报文定义/");
		CString cstrDefaultChoice = _T(""); // "_T" for program generality.

		pNode = pXMLDom->selectSingleNode(_T("branchbank/trs/交易报文定义"));
		if (pNode != NULL)
		{
			IXMLDOMNamedNodeMapPtr	pNodeMap;
			IXMLDOMNodePtr			pSubNode;
			IXMLDOMElementPtr       pElement;

			CString editMsgName;
			//m_ctrlEditMsgName.GetWindowText(editMsgName);
			CString editTradeCode;
			//m_ctrlEditTradeCode.GetWindowText(editTradeCode);
			CString cstrMac = _T("false");
			UpdateData(TRUE); // 刷新控件的值到对应的变量.
			//if (m_nRadio == 0)
			cstrMac = _T("true");

			pNodeMap = pNode->attributes; // get the node attribute.		
			if ( pNodeMap != NULL)
			{
				// get the attribute name.
				// <trs remark="交易周期(transaction)" father="cst" access="private">
				pSubNode = pNodeMap->getNamedItem("remark");
				if ( pSubNode != NULL)
				{
					cstrDefaultChoice = (LPCTSTR)pSubNode->text;
					pSubNode.Release();
				}
				pNodeMap.Release();				
			}
			////////////////////////////////////////// 2010-06-10 Saya ----- start///////
			// 报文名称和交易代码重复判断
			IXMLDOMNodeListPtr	    pNodeList;
			pNodeList = pNode->childNodes;
			int k = pNodeList->length;
			for (int i = 0; i < k; i++)
			{
				IXMLDOMNamedNodeMapPtr	pChildNodeMap;
				IXMLDOMNodePtr			pChildNode;
				pChildNode = pNodeList->item[i];
				pChildNodeMap = pChildNode->attributes;
				if (pChildNode->nodeName == static_cast<_bstr_t>(editMsgName))
				{
					//CoUninitialize();
					AfxMessageBox(_T("报文名称重复！"), MB_ICONINFORMATION);
					return FALSE;
				}
				if (pChildNodeMap->Getitem(0)->text == static_cast<_bstr_t>(editTradeCode))
				{
					//CoUninitialize();
					AfxMessageBox(_T("交易代码重复！"), MB_ICONINFORMATION);
					return FALSE;
				}
			}
			RELEASE(pNodeList);
			editMsgName = _T("陈幼敏");
			editTradeCode = _T("13424252857");
			//////////////////////////////////////////// 2010-06-10 Saya ----- end///////
			IXMLDOMNodePtr	pChildNode=pXMLDom->createElement(editMsgName.GetBuffer(0));
			editMsgName.ReleaseBuffer();
			if(pChildNode==NULL)
			{
				//CoUninitialize();
				return FALSE;
			}
			pNode->appendChild(pChildNode);
			pNode->lastChild->appendChild(pXMLDom->createTextNode("\n\t\t\t\t"));
			pElement = pNode->lastChild;
			pElement->setAttribute("jydm", editTradeCode.GetBuffer(0));
			editTradeCode.ReleaseBuffer();
			pElement->setAttribute("mac", cstrMac.GetBuffer(0));
			cstrMac.ReleaseBuffer();

			pSubNode = pNode->lastChild;
			pSubNode->appendChild(pXMLDom->createElement("sendfield"));
			pSubNode->lastChild->appendChild(pXMLDom->createTextNode("\n\t\t\t\t"));
			pSubNode->appendChild(pXMLDom->createTextNode("\n\t\t\t\t"));


			pSubNode->appendChild(pXMLDom->createElement("recvfield"));

			pSubNode->lastChild->appendChild(pXMLDom->createTextNode("\n\t\t\t\t"));
			pSubNode->appendChild(pXMLDom->createTextNode("\n\t\t\t"));
			pNode->appendChild(pXMLDom->createTextNode("\n\t\t"));
		}
	}
	catch(...)
	{
	}
	pXMLDom->save(cstrXMLFile.GetBuffer(0));
	cstrXMLFile.ReleaseBuffer();
	pXMLDom.Release();
	//CoUninitialize();
	//m_nTag = 0; // 成功添加后m_nTag归零 2010-06-10 Saya
	return TRUE;		
}

BOOL CGXManagerDlg::InitListXML(CString cstrXMLFile, CDataModelList * pList)
{
	using MSXML2::IXMLDOMDocumentPtr;
	using MSXML2::DOMDocument60;
	using MSXML2::IXMLDOMNodePtr;
	using MSXML2::IXMLDOMNodeListPtr;
	using MSXML2::IXMLDOMNamedNodeMapPtr;
	using MSXML2::IXMLDOMElementPtr;

	if (cstrXMLFile.IsEmpty())
		return FALSE;

	IXMLDOMDocumentPtr	pXMLDom;    //MSXML2::IXMLDOMDocumentPtr ---> StdAfx.h
	IXMLDOMNodeListPtr	pNodeList;
	IXMLDOMNodePtr		pNode;

	HRESULT p = CoInitialize(NULL); // for single thread to create COM Object(msxml6.dll).

	// 创建DOMDocument并且检测返回值.
	// hr type is a 32-bit value that is used to describe an error or warning.
	HRESULT hr = pXMLDom.CreateInstance(__uuidof(DOMDocument60));
	if (FAILED(hr))
	{
		return FALSE;
	}
	try
	{
		pXMLDom->async = VARIANT_FALSE; //  默认是true, 需要同步.

		// 加载XML文件.
		if (pXMLDom->load(cstrXMLFile.GetBuffer(0)) != VARIANT_TRUE)	
		{
			// 如果加载失败
			RELEASE(pXMLDom); // 释放DOMDocument.
			RELEASE(pNodeList);
			RELEASE(pNode);
			//CoUninitialize();  // 与CoInitialize匹配.

			return FALSE;
		}
		cstrXMLFile.ReleaseBuffer();

		//building_information
		CString searchPath = _T("building_information") ;

		pNode = pXMLDom->selectSingleNode(static_cast<_bstr_t>(searchPath));
		pNodeList = pNode->childNodes;   // all child node.
		//pNode->get_childNodes(&pNodeList);

		RELEASE(pNode);	

		//long lCount = pNodeList->length; // get the number of child node.
		//pNodeList->get_length(&lCount);
		int nbuildInfoChild = pNodeList->length; //building_information拥有的子节点数
		for (int i = 0; i < nbuildInfoChild; i++)
		{
			IXMLDOMNamedNodeMapPtr	pNodeMap;
			IXMLDOMNodePtr			pSubNode;
			IXMLDOMNodeListPtr	    pSubNodeList;

			pNode = pNodeList->item[i];
			pNodeMap = pNode->attributes;
			pSubNode = pNodeMap->getNamedItem("remark");     // check..
			CDataModel *pData = new CDataModel;            // where to set free.
			if (pSubNode != NULL)
			{
				pData->SetTitle((CString)(LPCTSTR)pNode->nodeName);   // get the node name.
				pSubNode.Release();
			}

			pList->AddTail(pData);                    

			pSubNodeList = pNode->childNodes;
			int nbuildChild = pSubNodeList->length;
			for (int j = 0; j < nbuildChild; j++)
			{
				IXMLDOMNamedNodeMapPtr	pChildNodeMap;
				IXMLDOMNodePtr			pChildNode;
				IXMLDOMNodeListPtr	    pChildNodeList;
				CDataBuildInfoModel *pDataTrade = new CDataBuildInfoModel;

				RELEASE(pSubNode);				

				pSubNode      = pSubNodeList->item[j];
				pChildNodeMap = pSubNode->attributes;
				pDataTrade->SetTitle((CString)(LPCTSTR)(pSubNode->nodeName));
				CString sss = pSubNode->nodeName; 
				int nBuildAttributeLen = pChildNodeMap->length;
				for (int nCounter = 0; nCounter < nBuildAttributeLen; nCounter++)
				{
					pChildNode = pChildNodeMap->Getitem(nCounter);
					switch (nCounter)
					{
					case 0:
						pDataTrade->SetNO((CString)(LPCTSTR)pChildNode->text);
						break;
					case 1:
						pDataTrade->SetName((CString)(LPCTSTR)pChildNode->text);
						break;
					case 2:
						pDataTrade->SetTel((CString)(LPCTSTR)pChildNode->text);
						break;
					case 3:
						pDataTrade->SetWork((CString)(LPCTSTR)pChildNode->text);
						break;
					case 4:
						pDataTrade->SetRemark((CString)(LPCTSTR)pChildNode->text);
						break;
					case 5:
						pDataTrade->SetRent((CString)(LPCTSTR)pChildNode->text);
						break;
					default:
						break;
					}
					//pChildNode.Release();
				}
				pData->m_ptrBuildInfoList.AddTail(pDataTrade);

				pChildNodeList = pSubNode->childNodes;
				int nRentChild = pChildNodeList->length;
				for (int k = 0; k < nRentChild; k++)
				{
					IXMLDOMNamedNodeMapPtr	pRentNodeMap;
					IXMLDOMNodePtr			pRentNode;
					CDataRentInfoModel *pDataRent = new CDataRentInfoModel;

					RELEASE(pChildNode);				

					pChildNode      = pChildNodeList->item[k];
					pRentNodeMap = pChildNode->attributes;
					pDataRent->SetTitle((CString)(LPCTSTR)(pChildNode->nodeName));
					int nRentAttributeLen = pRentNodeMap->length;
					for (int nCounter = 0; nCounter < nRentAttributeLen; nCounter++)
					{
						pRentNode = pRentNodeMap->Getitem(nCounter);
						switch (nCounter)
						{
						case 0:
							pDataRent->SetName((CString)(LPCTSTR)pRentNode->text);
							break;
						case 1:
							pDataRent->SetRent((CString)(LPCTSTR)pRentNode->text);
							break;
						//case 2:
						//	pDataRent->SetSanitation((CString)(LPCTSTR)pRentNode->text);
						//	break;

						case 3:
							pDataRent->SetParking((CString)(LPCTSTR)pRentNode->text);
							break;
						case 4:
							pDataRent->SetTV((CString)(LPCTSTR)pRentNode->text);
							break;
						case 5:
							pDataRent->SetBodyFund((CString)(LPCTSTR)pRentNode->text);
							break;
						case 6:
							pDataRent->SetPreElec((CString)(LPCTSTR)pRentNode->text);
							break;
						case 7:
							pDataRent->SetNowElec((CString)(LPCTSTR)pRentNode->text);
							break;
						case 8:
							pDataRent->SetPreWater((CString)(LPCTSTR)pRentNode->text);
							break;
						case 9:
							pDataRent->SetNowWater((CString)(LPCTSTR)pRentNode->text);
							break;
						case 10:
							pDataRent->SetPerMonthElec((CString)(LPCTSTR)pRentNode->text);
							break;
						case 11:
							pDataRent->SetPerMonthWater((CString)(LPCTSTR)pRentNode->text);
							break;
						case 12:
							pDataRent->SetOther((CString)(LPCTSTR)pRentNode->text);
							break;
						//case 13:
						//	pDataRent->SetPump((CString)(LPCTSTR)pRentNode->text);
						//	break;
						case 14:
							pDataRent->SetManager((CString)(LPCTSTR)pRentNode->text);
							break;
						case 15:
							pDataRent->SetTotal((CString)(LPCTSTR)pRentNode->text);
							break;
						case 16:
							pDataRent->SetRemark((CString)(LPCTSTR)pRentNode->text);
							break;
						case 17:
							pDataRent->SetWuGuanFei((CString)(LPCTSTR)pRentNode->text);
							break;
						case 18:
							pDataRent->SetPreGas((CString)(LPCTSTR)pRentNode->text);
							break;
						case 19:
							pDataRent->SetNowGas((CString)(LPCTSTR)pRentNode->text);
							break;
						case 20:
							pDataRent->SetPerMonthGas((CString)(LPCTSTR)pRentNode->text);
							break;

						default:
							break;
						}
						//pChildNode.Release();
					}

					// 实际上可以不用判断，直接插入最后面，因为只要调用了SortXML后，已经是有序的了
					POSITION posAdd = NULL;
					POSITION posAddPre = NULL;
					BOOL bFind = FALSE;
					for (posAdd = pDataTrade->m_ptrRentInfoList.GetHeadPosition(); posAdd != NULL;)
					{
						posAddPre = posAdd;
						CDataRentInfoModel * pData = pDataTrade->m_ptrRentInfoList.GetNext(posAdd);
						if (pData->GetTitle() < pDataRent->GetTitle())
						{
							continue;
						}
						else
						{
							bFind = TRUE;
							pDataTrade->m_ptrRentInfoList.InsertBefore(posAddPre, pDataRent);
							break;
						}
					}
					//没有找到可以插入的数据，说明这个数据最大，直接插入到最后
					if (!bFind)
					{
						pDataTrade->m_ptrRentInfoList.AddTail(pDataRent);
					}

					RELEASE(pRentNode);	
					RELEASE(pRentNodeMap);	

				}
				RELEASE(pChildNode);	
				RELEASE(pChildNodeMap);	
				RELEASE(pChildNodeList);
			}		
			RELEASE(pSubNode);		
			RELEASE(pSubNodeList);
			RELEASE(pNodeMap);
		}		
		RELEASE(pNodeList);
		RELEASE(pXMLDom);
		RELEASE(pNode);
	}
	catch(...)
	{
		AfxMessageBox(_T("InitListXML() Catch Some Error!"));
	}	
	//CoUninitialize();
	return TRUE;	
}

HRESULT CGXManagerDlg::SortXMLFile(CString cstrXMLFile)
{
	using MSXML2::IXMLDOMDocumentPtr;
	using MSXML2::DOMDocument60;
	using MSXML2::IXMLDOMNodePtr;
	using MSXML2::IXMLDOMNodeListPtr;
	using MSXML2::IXMLDOMNamedNodeMapPtr;
	using MSXML2::IXMLDOMElementPtr;

	if (cstrXMLFile.IsEmpty())
		return FALSE;

	IXMLDOMDocumentPtr	pXMLDom;    //MSXML2::IXMLDOMDocumentPtr ---> StdAfx.h
	IXMLDOMNodeListPtr	pNodeList;
	IXMLDOMNodePtr		pNode;

	HRESULT p = CoInitialize(NULL); // for single thread to create COM Object(msxml6.dll).

	// 创建DOMDocument并且检测返回值.
	// hr type is a 32-bit value that is used to describe an error or warning.
	HRESULT hr = pXMLDom.CreateInstance(__uuidof(DOMDocument60));
	if (FAILED(hr))
	{
		return FALSE;
	}
	try
	{
		pXMLDom->async = VARIANT_FALSE; //  默认是true, 需要同步.

		// 加载XML文件.
		if (pXMLDom->load(cstrXMLFile.GetBuffer(0)) != VARIANT_TRUE)
		{
			// 如果加载失败
			RELEASE(pXMLDom); // 释放DOMDocument.
			RELEASE(pNodeList);
			RELEASE(pNode);
			//CoUninitialize();  // 与CoInitialize匹配.

			return FALSE;
		}
		cstrXMLFile.ReleaseBuffer();

		//building_information
		CString searchPath = _T("building_information");

		pNode = pXMLDom->selectSingleNode(static_cast<_bstr_t>(searchPath));
		pNodeList = pNode->childNodes;   // all child node.
		//pNode->get_childNodes(&pNodeList);

		RELEASE(pNode);

		BOOL bChanged = FALSE;

		//long lCount = pNodeList->length; // get the number of child node.
		//pNodeList->get_length(&lCount);
		int nbuildInfoChild = pNodeList->length; //building_information拥有的子节点数
		//国雄楼目前有三栋房子
		for (int i = 0; i < nbuildInfoChild; i++)
		{
			IXMLDOMNodePtr			pSubNode;
			IXMLDOMNodeListPtr	    pSubNodeList;

			pNode = pNodeList->item[i];

			pSubNodeList = pNode->childNodes;
			int nbuildChild = pSubNodeList->length;
			for (int j = 0; j < nbuildChild; j++)
			{				
				IXMLDOMNodePtr			pChildNode;
				IXMLDOMNodeListPtr	    pChildNodeList;
		
				RELEASE(pSubNode);
				pSubNode = pSubNodeList->item[j];

				pChildNodeList = pSubNode->childNodes;
				int nRentChild = pChildNodeList->length;
				//这部分需要排序
				IXMLDOMNodePtr	PreChildNode;
				CString strTitlePre;
				CString strTitle;
				for (int j = 0; j < nRentChild; j++)
				{
					RELEASE(pChildNode);
					pChildNode = pChildNodeList->Getitem(j);

					strTitle = ((CString)(LPCTSTR)(pChildNode->nodeName));

					//如果当前节点最大，则Pre赋值，其他不需要处理
					if (strTitle > strTitlePre)
					{
						strTitlePre = strTitle;
						RELEASE(PreChildNode);
						PreChildNode = pChildNodeList->Getitem(j);
						continue;
					}
					//相等的时候，以后一个为准
					else if (strTitle == strTitlePre)
					{
						pSubNode->replaceChild(pChildNode, PreChildNode);
						RELEASE(PreChildNode);
						PreChildNode = pChildNodeList->Getitem(j-1);
						j--;
						nRentChild--;
						bChanged = TRUE;
					}
					//需要插入到前面的位置
					else //strTitle < strTitlePre
					{	
						bChanged = TRUE;
						CString strTemp;
						for (int k = 0; k < j; k++)
						{
							RELEASE(PreChildNode);
							PreChildNode = pChildNodeList->Getitem(k);
							strTemp = ((CString)(LPCTSTR)(PreChildNode->nodeName));
							if (strTitle < strTemp)
							{
								pSubNode->removeChild(pChildNode);
								pSubNode->insertBefore(pChildNode, PreChildNode.GetInterfacePtr());
								break;
							}
							else if (strTitle == strTemp)
							{
								pSubNode->replaceChild(pChildNode, PreChildNode);
								j--;
								nRentChild--;
								break;
							}
							else
							{
								//nothing
							}
						}
					}
				}

				RELEASE(pChildNode);
				RELEASE(pChildNodeList);
				RELEASE(PreChildNode);
			}
			RELEASE(pSubNode);
			RELEASE(pSubNodeList);
		}
		RELEASE(pNodeList);
		RELEASE(pNode);

		if (bChanged)
		{
			hr = pXMLDom->save(cstrXMLFile.GetBuffer(0));
			cstrXMLFile.ReleaseBuffer();

			if (FAILED(hr))
			{
				TRACE("CreateProjAssemCtrlFile:DOM Fail");
			}
			else
			{
				TRACE("CreateProjAssemCtrlFile:DOM saved to [%s]\n", cstrXMLFile.GetBuffer(0));
			}
		}
		
		RELEASE(pXMLDom); // release DOMDocument.

	}
	catch (...)
	{
		AfxMessageBox(_T("SortXMLFile() Catch Some Error!"));
	}

	return TRUE;
}
/***************************************************************************
创建作者：yjzhang
创建日期：2011-03-25
函数功能：点击列表响应
输入参数：----
输出参数：----
返    回：void
***************************************************************************/
void CGXManagerDlg::OnLvnItemchangedListMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nListRow = pNMLV->iItem;
	m_nListCol = pNMLV->iSubItem;

	*pResult = 0;
}

void CGXManagerDlg::UpdateListFirst(void)
{
	int nRow = 0;
	CString strNum;
	for ( POSITION pos = m_DataModelList.GetHeadPosition(); pos != NULL;)
	{
		CDataModel * pData = m_DataModelList.GetNext(pos);	

		for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL;)
		{
			CDataBuildInfoModel * pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);

			m_ctrListMain.InsertItem(nRow, _T(""), -1);
			strNum.Format(_T("%d"), nRow+1);
			m_ctrListMain.SetItemText(nRow, 1, strNum);
			m_ctrListMain.SetItemText(nRow, 2, pBuildData->GetNO());
			m_ctrListMain.SetItemText(nRow, 3, pBuildData->GetName());
			m_ctrListMain.SetItemText(nRow, 4, pBuildData->GetTel());
			m_ctrListMain.SetItemText(nRow, 5, pBuildData->GetWork());
			m_ctrListMain.SetItemText(nRow, 6, pBuildData->GetRemark());
			m_ctrListMain.SetItemText(nRow++, 7, pBuildData->GetRent());
		}		
	}
	m_ctrListMain.InsertItem(nRow + 1, _T(""), -1); //多增加一行，用于增加行数据
	g_nTotalNum = nRow;
}

void CGXManagerDlg::UpdateList(void)
{
	int nRow = 0;
	for ( POSITION pos = m_DataModelList.GetHeadPosition(); pos != NULL;)
	{
		CDataModel * pData = m_DataModelList.GetNext(pos);

		for (POSITION pos = pData->m_ptrBuildInfoList.GetHeadPosition(); pos != NULL;)
		{
			CDataBuildInfoModel * pBuildData = pData->m_ptrBuildInfoList.GetNext(pos);

			//if (nRow == m_nListRow)
			{
				m_ctrListMain.SetItemText(nRow, 2, pBuildData->GetNO());
				m_ctrListMain.SetItemText(nRow, 3, pBuildData->GetName());
				m_ctrListMain.SetItemText(nRow, 4, pBuildData->GetTel());
				m_ctrListMain.SetItemText(nRow, 5, pBuildData->GetWork());
				m_ctrListMain.SetItemText(nRow, 6, pBuildData->GetRemark());
				m_ctrListMain.SetItemText(nRow, 7, pBuildData->GetRent());
			}
			nRow++;
		}
	}
}
void CGXManagerDlg::OnBnClickedEdit()
{
	CPersonInfoDlg DlgPerson;
	DlgPerson.m_pDataModelList = &m_DataModelList;
	DlgPerson.SetParentWnd(this);
	DlgPerson.m_strNo = m_ctrListMain.GetItemText(m_nListRow, 2);
	DlgPerson.m_strName = m_ctrListMain.GetItemText(m_nListRow, 3);
	DlgPerson.m_strTel = m_ctrListMain.GetItemText(m_nListRow, 4);
	DlgPerson.m_strWork = m_ctrListMain.GetItemText(m_nListRow, 5);
	DlgPerson.m_strRemark = m_ctrListMain.GetItemText(m_nListRow, 6);
	DlgPerson.m_strRent = m_ctrListMain.GetItemText(m_nListRow, 7);

	DlgPerson.DoModal();
}

void CGXManagerDlg::OnBnClickedPrint()
{
	PrintInfoDlg DlgPrint;
	DlgPrint.m_pDataModelList = &m_DataModelList;
	DlgPrint.SetParentWnd(this);

	DlgPrint.m_strNo = m_ctrListMain.GetItemText(m_nListRow, 2);
	DlgPrint.m_strName = m_ctrListMain.GetItemText(m_nListRow, 3);
	DlgPrint.m_strRent = m_ctrListMain.GetItemText(m_nListRow, 7);

	DlgPrint.DoModal();
}

void CGXManagerDlg::OnBnClickedStatistic()
{
	CStatisticDlg DlgStatistic;
	DlgStatistic.m_pDataModelList = &m_DataModelList;
	DlgStatistic.DoModal();
}


void CGXManagerDlg::OnBnClickedInsert()
{
	// TODO:  在此添加控件通知处理程序代码
	CInsertInfoDlg DlgInsert;
	DlgInsert.m_pDataModelList = &m_DataModelList;
	DlgInsert.SetParentWnd(this);
	DlgInsert.m_strNo = m_ctrListMain.GetItemText(m_nListRow, 2);

	DlgInsert.DoModal();
}


void CGXManagerDlg::OnBnClickedDelete()
{
	/*
	// TODO:  在此添加控件通知处理程序代码
	CString strNo = m_ctrListMain.GetItemText(m_nListRow, 2);
	CString strBox;
	strBox.Format(_T("删除后会将关于房号 %s 的所有记录删除，确认删除？"), strNo);
	if (IDYES == AfxMessageBox(strBox, MB_YESNO | MB_ICONQUESTION))
	{
		InsertXML(strPath, strNo);
		CoUninitialize();
	}
	else
	{

	}
	*/
}
