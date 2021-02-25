#include "stdafx.h"
#include "math.h"

/***************************************************************************
创建作者：yjzhang
创建日期：2011-03-22
函数功能：获得Title最后数字，即栋
输入参数：----
输出参数：----
返    回：CString
***************************************************************************/
CString GetTitleLastNum(CString &str)
{
	return str.Right(str.GetLength() - 5);
}

/***************************************************************************
创建作者：yjzhang
创建日期：2011-03-22
函数功能：获得x-xxx的栋数
输入参数：----
输出参数：----
返    回：----
***************************************************************************/
CString GetHouseFirstNum(CString& str)
{
	int n = str.Find('-');
	return str.Left(n);
}

/***************************************************************************
创建作者：yjzhang
创建日期：2011-03-22
函数功能：获得x-xxx的房数
输入参数：----
输出参数：----
返    回：----
***************************************************************************/
CString GetHouseLastNum(CString& str)
{
	int n = str.Find('-');
	return str.Right(str.GetLength() - n - 1);
}

/***************************************************************************
创建作者：yjzhang
创建日期：2011-03-26
函数功能：获得时间函数
输入参数：----
输出参数：----
返    回：----
***************************************************************************/
void SetTimeTitle(CString & str, CDateTimeCtrl &dt, CComboBox & month)
{
	CTime timeTime;

	DWORD dwResult =dt.GetTime(timeTime);
	INT iYear = 2012;
	INT iDay = 1;

	if (dwResult == GDT_VALID)
	{	
		CString strTmp;
		if (month.GetCurSel() != CB_ERR)
		{
			month.GetLBText(month.GetCurSel(), strTmp);
		}
		int i = _wtoi(strTmp.GetBuffer(0));
		strTmp.ReleaseBuffer();
		strTmp.Format(_T("%02d"), i);

		iYear = timeTime.GetYear();
		iDay = timeTime.GetDay();
		if (i == 1 && iDay > 23)
		{
			iYear+=1;
		}
		else
		{
		}
		str.Format(TEXT("D%d"), iYear);
		str+=strTmp;
	}
}

/***************************************************************************
创建作者：yjzhang
创建日期：2011-05-01
函数功能：旋转位图
输入参数：
输出参数：
返    回：
***************************************************************************/
void RotateAnyAngle(CDC &dcSrc,int SrcWidth,int SrcHeight,double angle)
{
	double x1,x2,x3;
	double y1,y2,y3;
	double maxWidth,maxHeight,minWidth,minHeight;
	double srcX,srcY;
	double sinA,cosA;
	double DstWidth;
	double DstHeight;
	CDC dcDst;//旋转后的内存设备环境
	HBITMAP newBitmap;
	sinA = sin(angle);
	cosA = cos(angle);
	x1 = -SrcHeight * sinA;
	y1 = SrcHeight * cosA;
	x2 = SrcWidth * cosA - SrcHeight * sinA;
	y2 = SrcHeight * cosA + SrcWidth * sinA;
	x3 = SrcWidth * cosA;
	y3 = SrcWidth * sinA;
	minWidth = x3>(x1>x2?x2:x1)?(x1>x2?x2:x1):x3;
	minWidth = minWidth>0?0:minWidth;
	minHeight = y3>(y1>y2?y2:y1)?(y1>y2?y2:y1):y3;
	minHeight = minHeight>0?0:minHeight;
	maxWidth = x3>(x1>x2?x1:x2)?x3:(x1>x2?x1:x2);
	maxWidth = maxWidth>0?maxWidth:0;
	maxHeight = y3>(y1>y2?y1:y2)?y3:(y1>y2?y1:y2);
	maxHeight = maxHeight>0?maxHeight:0;
	DstWidth = maxWidth - minWidth;
	DstHeight = maxHeight - minHeight;
	dcDst.CreateCompatibleDC(&dcSrc);
	newBitmap = CreateCompatibleBitmap(dcSrc,(int)DstWidth,(int)DstHeight);
	SelectObject(dcDst,newBitmap);
	for( int I = 0; I<DstHeight; I++)
	{
		for(int J = 0; J< DstWidth; J++)
		{
			srcX = (J + minWidth) * cosA + (I + minHeight) * sinA;
			srcY = (I + minHeight) * cosA - (J + minWidth) * sinA;
			if( (srcX >= 0) && (srcX <= SrcWidth) &&(srcY >= 0) && (srcY <= SrcHeight))
			{
				dcDst.BitBlt( J, I, 1, 1, &dcSrc,(int)srcX, (int)srcY, SRCCOPY);
			}
		}
	}
	DeleteObject(newBitmap);
	dcSrc.BitBlt( 0, 0, SrcHeight, SrcWidth, &dcDst,0, 0, SRCCOPY);
	dcDst.DeleteDC();
}