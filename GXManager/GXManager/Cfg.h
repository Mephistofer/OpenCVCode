#pragma once
class Cfg
{
public:
	Cfg();
	~Cfg();
	BOOL getPrinterAddr(TCHAR sz[]);
	BOOL getStaticPrinterAddr(TCHAR sz[]);
private:
	CString m_strPrinterAddr;
};

