#ifndef MY_DEFINE
#define MY_DEFINE
#pragma once

#include <afx.h>  
#include <Shlwapi.h>
#include <algorithm>
#include <vector>
using namespace std;

#define WM_OPEN_MATCH_VIEW       WM_USER+10001  //����ƥ���鿴����
#define WM_WND_PROGRESS_SHOW     WM_USER+10002  //���ڽ�������ʾ-����
#define WM_WND_PROGRESS_POS      WM_USER+10003  //���ڽ��������ȸ���
#define WM_SYSTEM_TIME           WM_USER+10004  //ϵͳʱ��
#define WM_CREATE_DOCKPANE       WM_USER+10005  
#define WM_UPDATE_VIEWER         WM_USER+10006
#define WM_UPDATE_STATUSINFO     WM_USER+10007
#define WM_NEW_PROJECT           WM_USER+10008
#define WM_UPDATE_MATCHVIEW      WM_USER+10009 //����ƥ�䴰����ʾ����:����ƥ��˫����
#define WM_ADD_MATCHPOINT        WM_USER+10010 //����ƥ�䴰����ʾ����:���ƥ���
#define WM_DELETE_MATCHPOINT     WM_USER+10011 //����ƥ�䴰����ʾ����:ɾ��ƥ���
#define WM_UPDATE_ORTHORIMAGE    WM_USER+10012 //����ƥ�䴰����ʾ����:������ͼ��

#define ImageGridHeight 300   //ͼ��߶�
#define ImageGridGap    5     //ͼ����
#define ImageGridCols   8     //��ͼ����
#define MAX_SIZE_LINE   1024
#define MAX_SIZE_PATH   1024
#define MAX_SIZE_LOGF  (1024*1024)
struct stuImgGroup
{
	int nIdx;
	CString strPanPath;
	CString strMuxPath;
	CString strFusPath;
	CString strPanShp;
	CString strMuxShp;
	CString strFusShp;
	CString strMatchFilePan;
	CString strMatchFileMux;
	CString strMatchFileFus;
	stuImgGroup()
	{
		nIdx = -1;
		strPanPath.Empty();
		strMuxPath.Empty();
		strFusPath.Empty();
		strPanShp.Empty();
		strMuxShp.Empty();
		strFusShp.Empty();
		strMatchFilePan.Empty();
		strMatchFileMux.Empty();
		strMatchFileFus.Empty();
	}
};



enum eDOMTYPE
{
	PAN = 1,
	MUX = 2,
	FUS = 3
};

#endif