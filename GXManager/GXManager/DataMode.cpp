#include "StdAfx.h"
#include "DataMode.h"
/////////////////////////////////////////////////////////////////////////////
// CDataRentInfoModel
//个人房租信息
CDataRentInfoModel::CDataRentInfoModel()
{
}

//CDataRentInfoModel:: ~CDataRentInfoModel()
//{
//}

void CDataRentInfoModel::SetTitle(CString strT)
{
	m_strTitle = strT;
}

CString CDataRentInfoModel::GetTitle()
{
	return m_strTitle;
}

void CDataRentInfoModel::SetTime(CString strT) 
{
	m_strTime = strT;
}

CString CDataRentInfoModel::GetTime() 
{
	return m_strTime;
}

void CDataRentInfoModel::SetName(CString strT) 
{
	m_strName = strT;
}

CString CDataRentInfoModel::GetName() 
{
	return m_strName;
}

void CDataRentInfoModel::SetSanitation(CString strT)
{
	m_strSanitation = strT;
}

CString CDataRentInfoModel::GetSanitation()
{
	return m_strSanitation;
}
 
void CDataRentInfoModel::SetWuGuanFei(CString strT)
{
	m_strWuGuanFei = strT;
}

CString CDataRentInfoModel::GetWuGuanFei()
{
	return m_strWuGuanFei;
}

void CDataRentInfoModel::SetTV(CString strT) 
{
	m_strTV = strT;
}

CString CDataRentInfoModel::GetTV() 
{
	return m_strTV;
}

void CDataRentInfoModel::SetRent(CString strT) 
{
	m_strRent = strT;
}

CString CDataRentInfoModel::GetRent() 
{
	return m_strRent;
}

void CDataRentInfoModel::SetParking(CString strT) 
{
	m_strParking = strT;
}

CString CDataRentInfoModel::GetParking() 
{
	return m_strParking;
}

void CDataRentInfoModel::SetBodyFund(CString strT) 
{
	m_strBodyFund = strT;
}

CString CDataRentInfoModel::GetBodyFund() 
{
	return m_strBodyFund;
}

void CDataRentInfoModel::SetRemark(CString strT) 
{
	m_strRemark = strT;
}

CString CDataRentInfoModel::GetRemark() 
{
	return m_strRemark;
}

void CDataRentInfoModel::SetPreElec(CString strT) 
{
	m_strPreElec = strT;
}

CString CDataRentInfoModel::GetPreElec() 
{
	return m_strPreElec;
}

void CDataRentInfoModel::SetNowElec(CString strT) 
{
	m_strNowElec = strT;
}

CString CDataRentInfoModel::GetNowElec() 
{
	return m_strNowElec;
}

void CDataRentInfoModel::SetPerMonthElec(CString strT) 
{
	m_strPerMonthElec = strT;
}

CString CDataRentInfoModel::GetPerMonthElec() 
{
	return m_strPerMonthElec;
}

void CDataRentInfoModel::SetPreWater(CString strT) 
{
	m_strPreWater = strT;
}

CString CDataRentInfoModel::GetPreWater() 
{
	return m_strPreWater;
}

void CDataRentInfoModel::SetNowWater(CString strT) 
{
	m_strNowWater = strT;
}

CString CDataRentInfoModel::GetNowWater() 
{
	return m_strNowWater;
}

void CDataRentInfoModel::SetPerMonthWater(CString strT) 
{
	m_strPerMonthWater = strT;
}

CString CDataRentInfoModel::GetPerMonthWater() 
{
	return m_strPerMonthWater;
}

void CDataRentInfoModel::SetPreGas(CString strT)
{
	m_strPreGas = strT;
}

CString CDataRentInfoModel::GetPreGas()
{
	return m_strPreGas;
}

void CDataRentInfoModel::SetNowGas(CString strT) {
	m_strNowGas = strT;
}

CString CDataRentInfoModel::GetNowGas() {
	return m_strNowGas;
}

void CDataRentInfoModel::SetPerMonthGas(CString strT) {
	m_strPerMonthGas = strT;
}

CString CDataRentInfoModel::GetPerMonthGas() {
	return m_strPerMonthGas;
}


void CDataRentInfoModel::SetOther(CString strT) 
{
	m_strOther = strT;
}

CString CDataRentInfoModel::GetOther() 
{
	return m_strOther;
}

void CDataRentInfoModel::SetPump(CString strT)
{
	m_strPump = strT;
}

CString CDataRentInfoModel::GetPump()
{
	return m_strPump;
}

void CDataRentInfoModel::SetManager(CString strT)
{
	m_strManager = strT;
}

CString CDataRentInfoModel::GetManager()
{
	return m_strManager;
}

void CDataRentInfoModel::SetTotal(CString strT)
{
	m_strTotal = strT;
}

CString CDataRentInfoModel::GetTotal()
{
	return m_strTotal;
}

void CDataRentInfoModel::SetRealElec(CString strT)
{
	m_strRealElec = strT;
}

CString CDataRentInfoModel::GetRealElec()
{
	return m_strRealElec;
}

void CDataRentInfoModel::SetRealWater(CString strT)
{
	m_strRealWater = strT;
}

CString CDataRentInfoModel::GetRealGas()
{
	return m_strRealGas;
}

void CDataRentInfoModel::SetRealGas(CString strT)
{
	m_strRealGas = strT;
}

CString CDataRentInfoModel::GetRealWater()
{
	return m_strRealWater;
}

void CDataRentInfoModel::SetTotalElec(CString strT)
{
	m_strTotalElec = strT;
}

CString CDataRentInfoModel::GetTotalElec()
{
	return m_strTotalElec;
}

void CDataRentInfoModel::SetTotalGas(CString strT)
{
	m_strTotalGas = strT;
}

CString CDataRentInfoModel::GetTotalGas()
{
	return m_strTotalGas;
}

void CDataRentInfoModel::SetTotalWater(CString strT)
{
	m_strTotalWater = strT;
}

CString CDataRentInfoModel::GetTotalWater()
{
	return m_strTotalWater;
}
/////////////////////////////////////////////////////////////////////////////
// CDataBuildInfoModel
CDataBuildInfoModel::CDataBuildInfoModel()
{
}

CDataBuildInfoModel::~CDataBuildInfoModel()
{

	while (m_ptrRentInfoList.GetTailPosition())
	{
		CDataRentInfoModel * pData = m_ptrRentInfoList.GetTail();
		delete pData;
		m_ptrRentInfoList.RemoveTail();
	}
}

void CDataBuildInfoModel::SetTitle(CString strT)
{
	m_strTitle = strT;
}

CString CDataBuildInfoModel::GetTitle()
{
	return m_strTitle;
}

void CDataBuildInfoModel::SetNO(CString strT)
{
	m_strNO = strT;
}

CString CDataBuildInfoModel::GetNO()
{
	return m_strNO;
}

void CDataBuildInfoModel::SetRemark(CString strT)
{
	m_strRemark = strT;
}

CString CDataBuildInfoModel::GetRemark()
{
	return m_strRemark;
}

void CDataBuildInfoModel::SetName(CString strT)
{
	m_strName = strT;
}

CString CDataBuildInfoModel::GetName()
{
	return m_strName;
}

void CDataBuildInfoModel::SetTel(CString strT)
{
	m_strTel = strT;
}

CString CDataBuildInfoModel::GetTel()
{
	return m_strTel;
}

void CDataBuildInfoModel::SetWork(CString strT)
{
	m_strWork= strT;
}

CString CDataBuildInfoModel::GetWork()
{
	return m_strWork;
}

void CDataBuildInfoModel::SetRent(CString strT)
{
	m_strRent = strT;
}

CString CDataBuildInfoModel::GetRent()
{
	return m_strRent;
}
/////////////////////////////////////////////////////////////////////////////
// CDataModel

CDataModel::CDataModel()
{
}
CDataModel::~CDataModel()
{
	while (m_ptrBuildInfoList.GetTailPosition())
	{
		CDataBuildInfoModel * pData = m_ptrBuildInfoList.GetTail();
		delete pData;
		m_ptrBuildInfoList.RemoveTail();
	}
}

void CDataModel::SetRemark(CString strT)
{
	m_strRemark = strT;
}

CString CDataModel::GetRemark()
{
	return m_strRemark;
}

void CDataModel::SetTitle(CString strT)
{
	m_strTitle = strT;
}

CString CDataModel::GetTitle()
{
	return m_strTitle;
}


