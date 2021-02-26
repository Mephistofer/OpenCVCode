
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

//////////////////////////////////////////////////////////////////////////
#include "TipListCtrl.h"
#include "DataMode.h"
#include "Common.h"
#include "Cfg.h"
#define MANAGER_RED               (RGB(0xFF, 0x00, 0x00))
#define MANAGER_DARKRED           (RGB(0xDF,0x40,0x40))
//#define MANAGER_GRAY              (RGB(236,233,216))
#define MANAGER_GRAY              (RGB(200,200,200))
#define MANAGER_CLICK             (RGB(0x1e,0x90,0xff))
#define MANAGER_WHITE             (RGB(0xFF, 0xFF, 0xFF))
#define MANAGER_BLACK             (RGB(0x00, 0x00, 0x00))
#define MANAGER_RED               (RGB(0xFF, 0x00, 0x00))
#define MANAGER_BLUE              (RGB(0x00, 0x00, 0xFF))
#define MANAGER_BODY_BLUE         (RGB(0xE0, 0xFF, 0xFF))
#define MANAGER_MINT_CREAM        (RGB(0xF5, 0xFF, 0xFA))
#define MANAGER_LIST_TEST         (RGB(0x6F, 0x6F, 0x6F))
#define MANAGER_CREAM             (RGB(0xFF, 0xFD, 0xD0))

#define ALL_COL  34
#define ALL_ROW  17

#define PRINT_SUCCESS			0
#define PRINT_ERROR				1
#define PRINT_NEGATIVE_ELEC		2
#define PRINT_NEGATIVE_WATER	3
#define PRINT_NEGATIVE_GAS		4

#define BUILD_DATA_PATH           (_T("D:\\GXManager\\Data\\GXInfoData.xml"))
//#define BUILD_DATA_PATH           (_T("D:\\GXManager\\Data\\test.xml"))
//
#define RELEASE(A)  {\
	if(A != NULL) {\
        A.Release(); \
	}\
}\

#define SetString(a, b)  {\
	if(!a.IsEmpty()) {\
	b = a; \
	}\
}\

extern CString g_strMaker;
extern UINT g_nTotalNum;
extern Cfg g_cfg;

#import <msxml6.dll>
//#include <comutil.h>  
//#pragma comment(lib, "comsuppwd.lib") 
//using namespace MSXML2;

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


