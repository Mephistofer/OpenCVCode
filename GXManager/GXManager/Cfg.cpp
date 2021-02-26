#include "stdafx.h"
#include "Cfg.h"


Cfg::Cfg()
{
}


Cfg::~Cfg()
{
}

BOOL Cfg::getPrinterAddr(TCHAR sz[]) {


	CString strPath = _T("D:\\GXManager\\Data\\CfgFile.ini");

	TCHAR szTmp[_MAX_PATH];
	memset(szTmp, 0x00, sizeof(szTmp));
	memset(szTmp, 0x00, sizeof(szTmp));
	GetPrivateProfileString(_T("windows"), _T("device"), _T("EPSON LQ-730K ESC/P2,winspool,Ne02:"), szTmp, _MAX_PATH, strPath);

	wcscpy(sz, szTmp);
	return TRUE;
}

BOOL Cfg::getStaticPrinterAddr(TCHAR sz[]) {


	CString strPath = _T("D:\\GXManager\\Data\\CfgFile.ini");

	TCHAR szTmp[_MAX_PATH];
	memset(szTmp, 0x00, sizeof(szTmp));
	memset(szTmp, 0x00, sizeof(szTmp));
	GetPrivateProfileString(_T("windows"), _T("device_static"), _T("EPSON LQ-730K ESC/P2,winspool,Ne02:"), szTmp, _MAX_PATH, strPath);

	wcscpy(sz, szTmp);
	return TRUE;
}
