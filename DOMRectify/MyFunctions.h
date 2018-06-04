#ifndef MY_FUNCTIONS
#define MY_FUNCTIONS
#pragma once

#include "MainFrm.h"
#include "ChildFrm.h"
#include "DOMRectifyDoc.h"
#include "DOMRectifyView.h"
class CMainFrame;
class CDOMRectifyDoc;
class CDOMRectifyView;
CMainFrame*      GetMainFramHand();
CChildFrame*     GetChildFramHand();
CDOMRectifyDoc*  GetDocHand();
CDOMRectifyView* GetViewHand();

/*g5 global functions*/
//��ȡexe·��
CString FunGetThisExePath();

//��ȡϵͳʱ��short sTime[8]
void	FunGetSysTimeDat(short* dTime);

CString	FunGetSysTimeStr();
//��ȡ�ļ���С
long  	FunGetFileSize(CString strFilePath);
//��ȡ�ļ�Ŀ¼
CString FunGetFileFolder(CString strFullPath);
//��ȡ�ļ���
CString FunGetFileName(CString strFullPath, bool bExt);
//��ȡ�ļ���׺
CString FunGetFileExt(CString strFullPath);
//�ָ��ַ���
vector<CString> FunStrTok(CString str, CString strDot);
//����Ŀ¼
void FunCreateDir4Path(CString strPath, bool bThisPathisFolder);
//�����ļ�
bool FunSearchFile(CString strFolderPath, CString strExt, vector<CString>& vecFilePath);

//��ȡ��־�ļ�·��
inline CString	FunGetSyslogPath()
{
	CString strLogPath = FunGetThisExePath();
	int np1 = strLogPath.ReverseFind('.');
	strLogPath = strLogPath.Left(np1);
	strLogPath += ".log";
	return strLogPath;
}
//�����־��Ϣ
inline void FunOutPutLogInfo(CString strLogInfo)
{
	CString strLogFilePath = FunGetSyslogPath();
	CString strTime = FunGetSysTimeStr();
	long nFileSize = FunGetFileSize(strLogFilePath);
	if (nFileSize >= MAX_SIZE_LOGF) DeleteFile(strLogFilePath);
	FILE *pfW = fopen(strLogFilePath, "at+");
	if (pfW != NULL)
	{
		if (nFileSize > 0 && strLogInfo == "\n") fprintf(pfW, "\n");
		else if (strLogInfo != "\n") fprintf(pfW, "%s ===> %s\n", strTime, strLogInfo);
		fclose(pfW); pfW = NULL;
	}
}
/************************************************************************/
/* Ӱ�������������ص�                                                   */
/************************************************************************/
enum MenmResampleMode
{
	RESMODE_NEARST = 0,
	RESMODE_GUASS = 1,
	RESMODE_CUBIC = 2,
	RESMODE_AVAERAGE = 3
};
typedef int(*pCallBackProFun)(double dStp, const char *pStrInfo, void *pProgressCtrl);
int CallBakPrjPro(double dPos, const char* strInfo, void *pHand);
bool BuildPryamid(CString strImgPath, bool bReBuild = false, MenmResampleMode eMode= RESMODE_NEARST, 
	int nBottomSize = 64, pCallBackProFun pFun = NULL, void *pProgressCtrl = NULL);


/************************************************************************/
/* ���̺߳���                                                                     */
/************************************************************************/
void WINAPI MultiThreadBuildPyramid(LPVOID p);
void WINAPI MultiThreadCreateDockPanes(LPVOID p);
void WINAPI MultiThreadUpdateViewer(LPVOID p);
#endif
