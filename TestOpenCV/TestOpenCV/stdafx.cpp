
// stdafx.cpp : 只包括标准包含文件的源文件
// TestOpenCV.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

void CDECL MyDebugPrintf(TCHAR * szFormat, ...)
{
	TCHAR   szBuffer[1024] = { "[skk] " };
	va_list pArgList;

	// The va_start macro (defined in STDARG.H) is usually equivalent to:
	// pArgList = (char *) &szFormat + sizeof (szFormat) ;

	va_start(pArgList, szFormat);

	// The last argument to wvsprintf points to the arguments

	_vsntprintf_s(&szBuffer[6], 1024 - 7, sizeof(szBuffer) / sizeof(TCHAR) - 7,
		szFormat, pArgList);

	// The va_end macro just zeroes out pArgList for no good reason
	va_end(pArgList);
	OutputDebugString(szBuffer);
}
