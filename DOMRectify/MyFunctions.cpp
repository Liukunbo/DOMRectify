#include "StdAfx.h"
#include "MyFunctions.h"
#include "DOMRectify.h"
#include "ColorTable.h"
CMainFrame* GetMainFramHand()
{
	return (CMainFrame *)(CFrameWndEx *)AfxGetMainWnd();
}
CChildFrame * GetChildFramHand()
{
	if (!GetMainFramHand()) return NULL;
	return (CChildFrame*)(GetMainFramHand()->GetActiveFrame());
}
CDOMRectifyDoc*GetDocHand()
{
	CMainFrame*pMain = GetMainFramHand();
	if (pMain == NULL) return NULL;
	else return (CDOMRectifyDoc*)pMain->GetActiveDocument();
}
CDOMRectifyView* GetViewHand()
{
	CDocument *pDoc = GetDocHand();
	if (pDoc == NULL) return NULL;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos!=NULL)
	{
		CView * pView = (CView*)pDoc->GetNextView(pos);
		return (CDOMRectifyView*)pView;
	}
	return NULL;
}

CString FunGetThisExePath()
{
	char strExePath[MAX_SIZE_PATH]; memset(strExePath, 0, MAX_SIZE_PATH);
	GetModuleFileName(NULL, strExePath, sizeof(strExePath));
	return strExePath;
}
//��ȡϵͳʱ��short sTime[8]
void	FunGetSysTimeDat(short* dTime)
{
	//	short dTime[8];
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	dTime[0] = (short)systime.wYear;
	dTime[1] = (short)systime.wMonth;
	dTime[2] = (short)systime.wDay;
	dTime[3] = (short)systime.wHour;
	dTime[4] = (short)systime.wMinute;
	dTime[5] = (short)systime.wSecond;
	dTime[6] = (short)systime.wMilliseconds;
	//	return dTime;
}

CString	FunGetSysTimeStr()
{
	short dTime[8]; FunGetSysTimeDat(dTime);
	char strTime[100], strTemp[10];
	if (dTime[0] < 1000) /*strTemp.Format("0%d-", dTime[0]);*/sprintf(strTemp, "0%d-", dTime[0]);
	else /*strTemp.Format("%d-", dTime[0]);*/sprintf(strTemp, "%d-", dTime[0]);
	/*strTime = strTemp;*/sprintf(strTime, "%s", strTemp);//Y-
	if (dTime[1] < 10) /*strTemp.Format("0%d-", dTime[1]);*/sprintf(strTemp, "0%d-", dTime[1]);
	else /*strTemp.Format("%d-", dTime[1]);*/sprintf(strTemp, "%d-", dTime[1]);
	/*strTime += strTemp;*/sprintf(strTime, "%s%s", strTime, strTemp);//Y-M-
	if (dTime[2] < 10) /*strTemp.Format("0%d ", dTime[2]);*/sprintf(strTemp, "0%d ", dTime[2]);
	else /*strTemp.Format("%d ", dTime[2]);*/sprintf(strTemp, "%d ", dTime[2]);
	/*strTime += strTemp;*/sprintf(strTime, "%s%s", strTime, strTemp);//Y-M-D
	if (dTime[3] < 10) /*strTemp.Format("0%d:", dTime[3]);*/sprintf(strTemp, "0%d:", dTime[3]);
	else /*strTemp.Format("%d:", dTime[3]);*/sprintf(strTemp, "%d:", dTime[3]);
	/*strTime += strTemp;*/sprintf(strTime, "%s%s", strTime, strTemp);//Y-M-D H:
	if (dTime[4] < 10) /*strTemp.Format("0%d:", dTime[4]);*/sprintf(strTemp, "0%d:", dTime[4]);
	else /*strTemp.Format("%d:", dTime[4]);*/sprintf(strTemp, "%d:", dTime[4]);
	/*strTime += strTemp;*/sprintf(strTime, "%s%s", strTime, strTemp);//Y-M-D h:m:
	if (dTime[5] < 10) /*strTemp.Format("0%d", dTime[5]);*/sprintf(strTemp, "0%d", dTime[5]);
	else /*strTemp.Format("%d", dTime[5]);*/sprintf(strTemp, "%d", dTime[5]);
	/*strTime += strTemp;*/sprintf(strTime, "%s%s", strTime, strTemp);//Y-M-D h:m:s
	return strTime;
}
//��ȡ�ļ���С
long  	FunGetFileSize(CString strFilePath)
{
	FILE *pfCheckSize = fopen(strFilePath, "rb");
	long nFileSize = 0;
	if (pfCheckSize != NULL)
	{
		fseek(pfCheckSize, 0, SEEK_END);
		nFileSize = ftell(pfCheckSize);
	}
	if (pfCheckSize != NULL)
	{
		fclose(pfCheckSize); pfCheckSize = NULL;
	}
	return nFileSize;
}
//��ȡ�ļ�Ŀ¼
CString FunGetFileFolder(CString strFullPath)
{
	CString strFolder = strFullPath.Left(strFullPath.ReverseFind('\\'));
	return strFolder;
}
//��ȡ�ļ���
CString FunGetFileName(CString strFullPath, bool bExt)
{
	CString strName; int nPos1 = 0;
	nPos1 = strFullPath.ReverseFind('\\');
	if (bExt)
	{
		strName = strFullPath.Right(strFullPath.GetLength() - nPos1 - 1);
	}
	else
	{
		int nPos2 = strFullPath.ReverseFind('.');
		if (nPos2 == -1) nPos2 = strFullPath.GetLength();
		strName = strFullPath.Mid(nPos1 + 1, nPos2 - nPos1 - 1);
	}
	return strName;
}
//��ȡ�ļ���׺
CString FunGetFileExt(CString strFullPath)
{
	CString strExt = strFullPath.Right(strFullPath.GetLength() - strFullPath.ReverseFind('.') - 1);
	return strExt;
}
//�ָ��ַ���
vector<CString> FunStrTok(CString str, CString strDot)
{
	vector<CString> vPart;
	char strInfo[MAX_SIZE_PATH]; strcpy(strInfo, str);
	char* p = strtok(strInfo, strDot);
	while (p != NULL)
	{
		vPart.push_back(p);
		p = strtok(NULL, strDot);
	}
	return vPart;
}
//����Ŀ¼
void FunCreateDir4Path(CString strPath,bool bThisPathisFolder)
{
	
	if (PathFileExists(strPath))	return;
	if (!bThisPathisFolder) strPath = FunGetFileFolder(strPath);

	char tmpPath[MAX_PATH];
	const char* pCur = strPath;

	memset(tmpPath, 0, sizeof(tmpPath));

	int pos = 0;
	while (*pCur++ != '\0')
	{
		tmpPath[pos++] = *(pCur - 1);

		if (*pCur == '/' || *pCur == '\\' || *pCur == '\0')
		{
			if (!PathFileExists(tmpPath) && strlen(tmpPath) > 0)
			{
				CreateDirectory(tmpPath, NULL);
			}
		}
	}
}

//�����ļ�
bool FunSearchFile(CString strFolderPath, CString strExt, vector<CString>& vecFilePath)
{
	if (!PathFileExists(strFolderPath))
	{
		return false;
	}

	CString path = strFolderPath;
	CString  strFileName, strFileExt;
	if (path.Right(path.GetLength() - 1) != "\\");//·��Ҫ��/��β 
	path += _T("\\");
	path += _T("*.*");//CFileFind �����·��/*.gzʱ��ָ����·���������ļ� 
					  //path += _T("*.tif");//CFileFind �����·��/*.tiffʱ��ָ����·���������ļ� 
	CFileFind ff;
	BOOL res = ff.FindFile(path);
	while (res)
	{
		res = ff.FindNextFile();
		//�������. ..��.��ʾ��ǰĿ¼��..��ʾ��һ��Ŀ¼��Ҳ�����ļ���ʽ���ڵ�)
		//Ҳ����·��/�ļ��У���������ļ�����ɾ������Ĳ������ǻ�ȡ�ļ���Ȼ���Ҫ���ҵ��ļ����бȽ�
		if (!ff.IsDots() && !ff.IsDirectory())
		{
			if (ff.IsReadOnly())
			{
				::SetFileAttributes(ff.GetFilePath(), FILE_ATTRIBUTE_NORMAL);
			}
			//strFilePath�ǵ�ǰ���������ļ�������·�������ļ����ͺ�׺
			CString strFilePath;
			strFilePath = ff.GetFilePath();

			//ȡ�õ�ǰ�ļ�·�����ļ���
			for (int j = strFilePath.GetLength(); j>0; j--)
			{

				if (strFilePath.GetAt(j) == '\\')
				{
			//		strFileName = strFilePath.Right(strFilePath.GetLength() - j - 1);
			//		strFileExt = strFilePath.Right(strFilePath.GetLength() - strFilePath.ReverseFind('.') - 1);
					strFileExt = strFilePath.Right(strExt.GetLength());
					if (strFileExt.MakeLower() == strExt.MakeLower())
					{
						vecFilePath.push_back(strFilePath);//�ļ������δ��뵽�ļ���������
					}
					break;
				}
			}
		}
		else   if (ff.IsDots())   //�����. ..���ͼ�����    
			continue;
		else    if (ff.IsDirectory())///*������ļ��У��͵ݹ����˷�������ɾ������Ĳ������ǵݹ����˷��������Ա��ļ�����������������    */
		{
			//���õݹ����
			// 			path = ff.GetFilePath();
			// 			FunSearchFile(path, strExt, vecFilePath);
		}
	}
	return true;
}


/************************************************************************/
/* Ӱ�������������ص�                                                   */
/************************************************************************/
int CallBakPrjPro(double dPos, const char * strInfo, void * pHand)
{
	CMainFrame* pMainFrame = (CMainFrame*)pHand;
	if (pMainFrame == NULL) return 0;
	SendMessage(pMainFrame->m_hWnd,WM_WND_PROGRESS_POS, WPARAM(&pMainFrame->m_wndProgressPyramid), dPos*100);
	return 1;
}

bool BuildPryamid(CString strImgPath, bool bReBuild /* = false */, MenmResampleMode eMode/* = RESMODE_NEARST */,
	int nBottomSize /* = 64 */, pCallBackProFun pFun /* = NULL */, void *pProgressCtrl /* = NULL */)
{
	GDALDataset* pDataset = (GDALDataset*)GDALOpen(strImgPath, GA_ReadOnly);
	if (pDataset == NULL) return false;
	char strOvr[MAX_SIZE_PATH]; sprintf(strOvr, "%s.ovr", strImgPath);
	if (PathFileExists(strOvr))
	{
		if (bReBuild)
			DeleteFile(strOvr);
		else
		{
			pFun(1, 0, pProgressCtrl);
			return true;
		}
	}
	GDALDriverH hDriver = GDALGetDatasetDriver(pDataset);
	char strDriver[MAX_SIZE_LINE];
	strcpy(strDriver, GDALGetDriverShortName(hDriver));
	if (EQUAL(strDriver, "HFA") || EQUAL(strDriver, "PCIDSK"))
	{
		GDALClose(pDataset);//img/pix�����ڽ�������������ʽ�����������
		GDALDataset* pDataset = (GDALDataset*)GDALOpen(strImgPath, GA_Update);
	}
	//��ȡӰ�������Ϣ�����ɽ�����
	if (nBottomSize < 0) nBottomSize = 32;
	int nWidth = pDataset->GetRasterXSize();
	int nHeight = pDataset->GetRasterYSize();
	int nPixelAll = nWidth*nHeight; //Ӱ����������
	int nPixelTop = nBottomSize*nBottomSize;  //��������������� 64*64
	int NumCur = nPixelAll;
	int nGap = 4;
	int nTemp = 0;
	do
	{
		nTemp++;
		NumCur /= nGap;
	} while (NumCur > nPixelTop);
	int *anLevels = new int[nTemp]; memset(anLevels, 0, nTemp * sizeof(int));
	int nLevelCount = 0; //����������
	NumCur = nPixelAll / nGap;
	do //���������������2->top
	{
		anLevels[nLevelCount] = static_cast<int>(pow(2.0, nLevelCount + 2));
		nLevelCount++;
		NumCur /= nGap;
	} while (NumCur > nPixelTop);
	//CString strResample = "nearest";//���ڽ�������ʽ
	char strResampleMode[MAX_SIZE_LINE]; memset(strResampleMode, 0, MAX_SIZE_LINE);
	switch (eMode)
	{
	case RESMODE_NEARST:
		strcpy(strResampleMode, "NEARST");
		break;
	case RESMODE_GUASS:
		strcpy(strResampleMode, "GUASS");
		break;
	case RESMODE_CUBIC:
		strcpy(strResampleMode, "CUBIC");
		break;
	case RESMODE_AVAERAGE:
		strcpy(strResampleMode, "AVERAGE");
		break;
	default:
		break;
	}
	if (pDataset->BuildOverviews(strResampleMode, nLevelCount, anLevels, 0, NULL, (GDALProgressFunc)pFun, pProgressCtrl) != CE_None) /*(nLevelCount > 0 && GDALBuildOverviews(hDataSet, strResample, nLevelCount, anLevels, 0, NULL, NULL, NULL) != CE_None)*/
	{
		return false;
	}
	delete[]anLevels; anLevels = NULL;
	return true;
}



/************************************************************************/
/* ���̺߳���                                                                     */
/************************************************************************/
void MultiThreadBuildPyramid(LPVOID p)
{
	CMainFrame*pMainFrame = (CMainFrame*)p;
	SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_SHOW, WPARAM(&pMainFrame->m_wndProgressPyramid), 1);
	SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_POS, WPARAM(&pMainFrame->m_wndProgressPyramid), 1.0);
	SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_SHOW, WPARAM(&pMainFrame->m_wndProgress), 1);
	SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_POS, WPARAM(&pMainFrame->m_wndProgress), 1.0);
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
	int nAllImgNum = pMainFrame->m_Project.GetRefNum() + pMainFrame->m_Project.GetDomNum();
	CString strImgPath, strImgName;
	//ref
	for (int i = 0; i<pMainFrame->m_Project.GetRefNum(); i++)
	{
		strImgPath = pMainFrame->m_Project.GetRefPath(i);
		strImgName = FunGetFileName(strImgPath, true);
		SendMessage(pMainFrame->m_hWnd, WM_UPDATE_STATUSINFO, (WPARAM)pMainFrame->m_pStatusPaneProcessing, (LPARAM)&strImgName);
		BuildPryamid(strImgPath, false, RESMODE_NEARST, 64, CallBakPrjPro, pMainFrame);
		BuildColorTable(strImgPath.GetBuffer());
		SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_POS, WPARAM(&pMainFrame->m_wndProgress), (i + 1)*100.0 / nAllImgNum);
	}
	for (int i = 0; i < pMainFrame->m_Project.GetGroupNum(); i++)
	{
		strImgPath = pMainFrame->m_Project.GetPanPath(i);
		strImgName = FunGetFileName(strImgPath, true);
		SendMessage(pMainFrame->m_hWnd, WM_UPDATE_STATUSINFO, (WPARAM)pMainFrame->m_pStatusPaneProcessing, (LPARAM)&strImgName);
		BuildPryamid(strImgPath, false, RESMODE_NEARST, 64, CallBakPrjPro, pMainFrame);
		BuildColorTable(strImgPath.GetBuffer());
		SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_POS, WPARAM(&pMainFrame->m_wndProgress), (i + 1 + pMainFrame->m_Project.GetRefNum())*100.0 / nAllImgNum);

		strImgPath = pMainFrame->m_Project.GetMuxPath(i);
		strImgName = FunGetFileName(strImgPath, true);
		SendMessage(pMainFrame->m_hWnd, WM_UPDATE_STATUSINFO, (WPARAM)pMainFrame->m_pStatusPaneProcessing, (LPARAM)&strImgName);
		BuildPryamid(strImgPath, false, RESMODE_NEARST, 64, CallBakPrjPro, pMainFrame);
		BuildColorTable(strImgPath.GetBuffer());
		SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_POS, WPARAM(&pMainFrame->m_wndProgress), (i + 2 + pMainFrame->m_Project.GetRefNum())*100.0 / nAllImgNum);

		strImgPath = pMainFrame->m_Project.GetFusPath(i);
		strImgName = FunGetFileName(strImgPath, true);
		SendMessage(pMainFrame->m_hWnd, WM_UPDATE_STATUSINFO, (WPARAM)pMainFrame->m_pStatusPaneProcessing, (LPARAM)&strImgName);
		BuildPryamid(strImgPath, false, RESMODE_NEARST, 64, CallBakPrjPro, pMainFrame);
		BuildColorTable(strImgPath.GetBuffer());
		SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_POS, WPARAM(&pMainFrame->m_wndProgress), (i + 3 + pMainFrame->m_Project.GetRefNum())*100.0 / nAllImgNum);
	}
	SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_SHOW, WPARAM(&pMainFrame->m_wndProgressPyramid), 0);
	SendMessage(pMainFrame->m_hWnd, WM_WND_PROGRESS_SHOW, WPARAM(&pMainFrame->m_wndProgress), 0);
	SendMessage(pMainFrame->m_hWnd, WM_UPDATE_STATUSINFO, (WPARAM)pMainFrame->m_pStatusPaneProcessing, 0);

	SendMessage(pMainFrame->m_hWnd, WM_NEW_PROJECT, 0, 0);

}

void MultiThreadCreateDockPanes(LPVOID p)
{
	CMainFrame *pMainFrame = (CMainFrame*)p;
	if (pMainFrame)
		SendMessage(pMainFrame->m_hWnd,WM_CREATE_DOCKPANE,0,0);
}

void MultiThreadUpdateViewer(LPVOID p)
{
	Sleep(500);
	CMainFrame *pMainFrame = (CMainFrame*)p;
	if(pMainFrame)
		SendMessage(pMainFrame->m_hWnd, WM_UPDATE_VIEWER, 0, 0);
}


