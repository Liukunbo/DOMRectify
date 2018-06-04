// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// DOMRectify.h : DOMRectify Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "GDAL/ogr_geometry.h"

// CDOMRectifyApp:
// �йش����ʵ�֣������ DOMRectify.cpp
//

class CDOMRectifyApp : public CWinAppEx
{
public:
	CDOMRectifyApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	bool m_bPointAdd;
	bool m_bPointDel;
	bool m_bWrapperView;
	bool m_bPtDom;
	bool m_bPtRef;
	OGRPoint m_ptDom;
	OGRPoint m_ptRef;
	int m_nRefIdx;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdateButtonPointDelete(CCmdUI *pCmdUI);
};

extern CDOMRectifyApp theApp;
