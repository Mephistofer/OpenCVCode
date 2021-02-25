#include "stdafx.h"
#include "Cfg.h"


Cfg::Cfg()
{
}


Cfg::~Cfg()
{
}

BOOL Cfg::getPrinterAddr(TCHAR sz[]) {

	TCHAR szCurDir[_MAX_PATH];
	memset(szCurDir, 0x00, sizeof(szCurDir));
	::GetModuleFileName(NULL, szCurDir, sizeof(szCurDir));
	CString strPath = szCurDir;
	int nPos = strPath.ReverseFind('\\');
	if (nPos != -1)
	{
		strPath = strPath.Left(nPos + 1);
	}
	strPath += "Data\\CfgFile.ini";

	TCHAR szTmp[_MAX_PATH];
	memset(szTmp, 0x00, sizeof(szTmp));
	memset(szTmp, 0x00, sizeof(szTmp));
	GetPrivateProfileString(_T("windows"), _T("device"), _T("EPSON LQ-730K ESC/P2,winspool,Ne02:"), szTmp, _MAX_PATH, strPath);
	wcscpy(sz, szTmp);
	return TRUE;
}

BOOL Cfg::getStaticPrinterAddr(TCHAR sz[]) {

	TCHAR szCurDir[_MAX_PATH];
	memset(szCurDir, 0x00, sizeof(szCurDir));
	::GetModuleFileName(NULL, szCurDir, sizeof(szCurDir));
	CString strPath = szCurDir;
	int nPos = strPath.ReverseFind('\\');
	if (nPos != -1)
	{
		strPath = strPath.Left(nPos + 1);
	}
	strPath += "Data\\CfgFile.ini";

	TCHAR szTmp[_MAX_PATH];
	memset(szTmp, 0x00, sizeof(szTmp));
	memset(szTmp, 0x00, sizeof(szTmp));
	GetPrivateProfileString(_T("windows"), _T("device_static"), _T("HP DeskJet 2600 series,winspool,Ne03:"), szTmp, _MAX_PATH, strPath);
	wcscpy(sz, szTmp);
	return TRUE;
}
