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

// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "DOMRectify.h"

#include "ChildFrm.h"
#include "MyFunctions.h"
#include "DlgPrjNew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_NEW, &CChildFrame::OnFileNew)
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_OPEN, &CChildFrame::OnFileOpen)
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_bSpliter = false;
}


CChildFrame::~CChildFrame()
{
	DWORD lastError = 0;
	if (!wglDeleteContext(m_hRC))
	{
		lastError = GetLastError();
	}
	if (!wglDeleteContext(m_RRC))
	{
		lastError = GetLastError();
	}
	if (!wglDeleteContext(m_LRC))
	{
		lastError = GetLastError();
	}
	
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������


void CChildFrame::OnFileNew()
{
	// TODO: Add your command handler code here
	GetMainFramHand()->OnFileNew();
}

void CChildFrame::OnFileOpen()
{
	// TODO: Add your command handler code here
	GetMainFramHand()->OnFileOpen();
}


void CChildFrame::OnDestroy()
{
	CMDIChildWndEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CChildFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if (GetActiveDocument()->GetTitle() == "����ȫ��")
	{
		GetMainFramHand()->ClearData();
		theApp.CloseAllDocuments(TRUE);	
	}
	else
	{
		GetMainFramHand()->CloseStereDoc();
	}
	m_bSpliter = false;
}


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	if (theApp.m_pDocManager->GetOpenDocumentCount() == 2)
	{
		CRect rt;  GetClientRect(&rt);
		CRect rt_Left;  rt_Left.SetRectEmpty();
		if(GetMainFramHand()->m_wndImgData.GetSafeHwnd())
			GetMainFramHand()->m_wndImgData.GetClientRect(rt_Left);
		if (!m_wndSpliter.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE))
		{
			AfxMessageBox(_T("�ָ�ڴ���."));
			return false;
		}
		m_wndSpliter.CreateView(0, 0, RUNTIME_CLASS(CDOMRectifyView), CSize((rt.Width() + rt_Left.Width()) / 2, rt.Height()), pContext);
		m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CDOMRectifyView), CSize((rt.Width() + rt_Left.Width()) / 2, rt.Height()), pContext);
		m_bSpliter = true;
		GetMainFramHand()->m_pLView = (CDOMRectifyView*)m_wndSpliter.GetPane(0, 0);
		GetMainFramHand()->m_pRView = (CDOMRectifyView*)m_wndSpliter.GetPane(0, 1);

		m_hDC = NULL; m_hRC = NULL;
		m_hDC = GetDC()->GetSafeHdc();
		if (m_hDC == NULL) return FALSE;
		if (SetWindowPixelFormat(m_hDC) == FALSE)
		{
			ASSERT(0);
			return FALSE;
		}
		m_hRC = wglCreateContext(m_hDC);
		m_LRC = wglCreateContext(m_hDC);
		m_RRC = wglCreateContext(m_hDC);
		DWORD lastErr = 0;
		if (!wglShareLists(m_hRC, m_LRC))
		{
			lastErr = GetLastError();
		}
		if (!wglShareLists(m_hRC, m_RRC))
		{
			lastErr = GetLastError();
		}
		GetMainFramHand()->m_pLView->SetRC(m_LRC);
		GetMainFramHand()->m_pRView->SetRC(m_RRC);
		wglMakeCurrent(m_hDC, m_hRC);
		GLenum err = glewInit();
		wglMakeCurrent(NULL, NULL);
		return true;
	}
	else
	{
		m_hDC = NULL; m_hRC = NULL;
		m_hDC = GetDC()->GetSafeHdc();
		if (m_hDC == NULL) return FALSE;
		if (SetWindowPixelFormat(m_hDC) == FALSE)
		{
			ASSERT(0);
			return FALSE;
		}
		m_hRC = wglCreateContext(m_hDC);
		wglMakeCurrent(m_hDC, m_hRC);
		GLenum err = glewInit();
		wglMakeCurrent(NULL, NULL);
	}
	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}

void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: Add your specialized code here and/or call the base class
	nCmdShow = SW_SHOWMAXIMIZED;
	CMDIChildWndEx::ActivateFrame(nCmdShow);
}

