
// TestOpenCVDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "TestOpenCV.h"
#include "TestOpenCVDlg.h"
#include "afxdialogex.h"

#include <iostream>
using namespace std;

#include <opencv2\core\core.hpp>
//OpenCV图形处理头文件
#include <opencv2\highgui\highgui.hpp>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestOpenCVDlg 对话框



CTestOpenCVDlg::CTestOpenCVDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TESTOPENCV_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestOpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PIC_PATH, m_editPicPath);
    DDX_Control(pDX, IDC_EDIT_VEDIO_PATH, m_editVedioPath);
}

BEGIN_MESSAGE_MAP(CTestOpenCVDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_PIC, &CTestOpenCVDlg::OnBnClickedButtonPic)
    ON_BN_CLICKED(IDC_BUTTON_PIC_PATH_CHOOSE, &CTestOpenCVDlg::OnBnClickedButtonPicPathChoose)
    ON_BN_CLICKED(IDC_BUTTON_VEDIO_PATH_CHOOSE, &CTestOpenCVDlg::OnBnClickedButtonVedioPathChoose)
END_MESSAGE_MAP()


// CTestOpenCVDlg 消息处理程序

BOOL CTestOpenCVDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
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

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码
    m_editPicPath.SetWindowText("F:\\Image1.jpg");
    m_editVedioPath.SetWindowText("F:\\Vedio1.avi");

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestOpenCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestOpenCVDlg::OnPaint()
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
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestOpenCVDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CTestOpenCVDlg::OnBnClickedButtonPic()
{
    //窗口名称
    std::string windowName = "HelloWorld";
    //图像名称
    CString strImgFile;
    m_editPicPath.GetWindowText(strImgFile);
    //读入图像
    cv::Mat image = cv::imread(strImgFile.GetBuffer(0), cv::IMREAD_COLOR);
    strImgFile.ReleaseBuffer();
    //如果无法读取图形
    if (!image.data)
    {
        std::cout << "无法打开图像文件" << std::endl;
        system("PAUSE");//暂停窗口
        return;
    }

    //创建一个新窗口
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    //将图像显示都新创建的窗口中
    cv::imshow(windowName, image);
    //等待，直到用户按任意键时退出
    cv::waitKey(0);
}


void CTestOpenCVDlg::OnBnClickedButtonPicPathChoose()
{
	TCHAR path[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, path); // 文件目录保存在path这个字符数组
	CString filePath = path;

	if (!m_strFilePathName.IsEmpty())
		filePath = m_strFilePathName;
	// TODO: Add your control notification handler code here
	CFileDialog  dlg(TRUE, NULL, " ", OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT,
		"All   Files(*.*)|*.*|图像文件(*.jpg)|*.jpg|位图文件(*.bmp)|*.bmp|| ", NULL);
	dlg.m_ofn.lpstrInitialDir = (LPCTSTR)filePath;  //设置默认的打开文件路径
	dlg.m_ofn.lpstrFile = new TCHAR[1024];
	memset(dlg.m_ofn.lpstrFile, 0, 1024);  // 初始化定义的缓冲 
	dlg.m_ofn.nMaxFile = 1024;           // 重定义 nMaxFile 

	CString fileExt("");
	CString fileName("");

	if (dlg.DoModal() == IDOK)
	{
		m_strFilePathName = dlg.GetPathName();
		m_editPicPath.SetWindowText(m_strFilePathName);
	}
	else
	{

	}
}


void CTestOpenCVDlg::OnBnClickedButtonVedioPathChoose()
{
	TCHAR path[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, path); // 文件目录保存在path这个字符数组
	CString filePath = path;

	if (!m_strFilePathName.IsEmpty())
		filePath = m_strFilePathName;


	// TODO: Add your control notification handler code here
	CFileDialog  dlg(TRUE, NULL, " ", OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT,
		"All   Files(*.*)|*.*|视频文件(*.avi)|| ", NULL);
	dlg.m_ofn.lpstrInitialDir = (LPCTSTR)filePath;  //设置默认的打开文件路径
	dlg.m_ofn.lpstrFile = new TCHAR[1024];
	memset(dlg.m_ofn.lpstrFile, 0, 1024);  // 初始化定义的缓冲 
	dlg.m_ofn.nMaxFile = 1024;           // 重定义 nMaxFile 

	CString fileExt("");
	CString fileName("");

	if (dlg.DoModal() == IDOK)
	{
		m_strFilePathName = dlg.GetPathName();
		m_editVedioPath.SetWindowText(m_strFilePathName);
	}
	else
	{

	}
}
