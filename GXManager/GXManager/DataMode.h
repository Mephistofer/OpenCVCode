#pragma once
#include "afx.h"

//个人房租信息
class CDataRentInfoModel :public CObject
{
public:
	CDataRentInfoModel();
	//virtual ~CDataRentInfoModel();

	virtual void SetTitle(CString strT);
	virtual CString GetTitle();
	virtual void SetTime(CString strT);
	virtual CString GetTime();
	virtual void SetName(CString strT);
	virtual CString GetName();
	virtual void SetSanitation(CString strT);
	virtual CString GetSanitation();
	virtual void SetWuGuanFei(CString strT);
	virtual CString GetWuGuanFei();
	virtual void SetTV(CString strT);
	virtual CString GetTV();
	virtual void SetRent(CString strT);
	virtual CString GetRent();
	virtual void SetParking(CString strT);
	virtual CString GetParking();
	virtual void SetBodyFund(CString strT);
	virtual CString GetBodyFund();
	virtual void SetRemark(CString strT);
	virtual CString GetRemark();
	virtual void SetPreElec(CString strT);
	virtual CString GetPreElec();
	virtual void SetNowElec(CString strT);
	virtual CString GetNowElec();
	virtual void SetPerMonthElec(CString strT);
	virtual CString GetPerMonthElec();
	virtual void SetPreWater(CString strT);
	virtual CString GetPreWater();
	virtual void SetNowWater(CString strT);
	virtual CString GetNowWater();
	virtual void SetPerMonthWater(CString strT);
	virtual CString GetPerMonthWater();

	virtual void SetPreGas(CString strT);
	virtual CString GetPreGas();
	virtual void SetNowGas(CString strT);
	virtual CString GetNowGas();
	virtual void SetPerMonthGas(CString strT);
	virtual CString GetPerMonthGas();


	virtual void SetOther(CString strT);
	virtual CString GetOther();
	virtual void SetPump(CString strT);
	virtual CString GetPump();
	virtual void SetManager(CString strT);
	virtual CString GetManager();
	virtual void SetRealElec(CString strT);
	virtual CString GetRealElec();
	virtual void SetRealWater(CString strT);
	virtual CString GetRealWater();

	virtual void SetRealGas(CString strT);
	virtual CString GetRealGas();

	virtual void SetTotalElec(CString strT);
	virtual CString GetTotalElec();
	virtual void SetTotalWater(CString strT);
	virtual CString GetTotalWater();

	virtual void SetTotalGas(CString strT);
	virtual CString GetTotalGas();

	virtual void SetTotal(CString strT);
	virtual CString GetTotal();
	CString m_strNo;

	// Attribute 
	private:
	CString m_strTitle;
	CString m_strTime;
	CString m_strName;
	CString m_strSanitation;
	CString m_strWuGuanFei;
	CString m_strTV; //有线电视费
	CString m_strRent; //房费
	CString m_strParking; //停车费
	CString m_strBodyFund; //本体基金
	CString m_strRemark; //备注
	CString m_strPreElec; //上月电度
	CString m_strNowElec; //本月电度
	CString m_strPerMonthElec; //每度电费
	CString m_strPreWater; //上月水方
	CString m_strNowWater; //本月水方
	CString m_strPerMonthWater; //每方水费

	CString m_strPreGas; //上月天然气
	CString m_strNowGas; //本月天然气
	CString m_strPerMonthGas; //每方天然气费

	CString m_strOther; //其他
	CString m_strPump; //水泵加压
	CString m_strManager; //管理成本费
	CString m_strTotal;
	CString m_strRealElec;
	CString m_strRealWater;
	CString m_strTotalElec;
	CString m_strRealGas;
	CString m_strTotalGas;
	CString m_strTotalWater;
};
typedef CTypedPtrList<CObList,CDataRentInfoModel*> CDataRentInfoModelList;

//房子信息
class CDataBuildInfoModel :public CObject
{
	//DECLARE_SERIAL(CDataModel)
public:
	CDataBuildInfoModel();
	virtual ~CDataBuildInfoModel();

	virtual void SetTitle(CString strT);
	virtual CString GetTitle();
	virtual void SetNO(CString strT);
	virtual CString GetNO();
	virtual void SetName(CString strT);
	virtual CString GetName();
	virtual void SetTel(CString strT);
	virtual CString GetTel();
	virtual void SetWork(CString strT);
	virtual CString GetWork();
	virtual void SetRemark(CString strT);
	virtual CString GetRemark();
	virtual void SetRent(CString strT);
	virtual CString GetRent();

	// Attribute 
public:
	CString m_strTitle;
	CString m_strNO;
	CString m_strName;
	CString m_strTel;
	CString m_strWork;
	CString m_strRemark;
	CString m_strRent;
	CDataRentInfoModelList m_ptrRentInfoList;
};
typedef CTypedPtrList<CObList,CDataBuildInfoModel*> CDataBuildInfoModelList;

//国雄信息
class CDataModel :public CObject
{
	//DECLARE_SERIAL(CDataModel)
public:
	CDataModel();
	virtual ~CDataModel();

	virtual void SetTitle(CString strT);
	virtual CString GetTitle();
	virtual void SetRemark(CString strT);
	virtual CString GetRemark();

	// Attribute 
public:
	CString m_strTitle;
	CString m_strRemark;

	CDataBuildInfoModelList m_ptrBuildInfoList;
};
typedef CTypedPtrList<CObList,CDataModel*> CDataModelList;
