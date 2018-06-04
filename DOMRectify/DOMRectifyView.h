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

// DOMRectifyView.h : CDOMRectifyView ��Ľӿ�
//

#pragma once
#include "GLImageView/GLImageView.h"
#include "GLImageReader/GLImageReader.h"

inline void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

class CDOMRectifyView : public ImageView
{
protected: // �������л�����
	CDOMRectifyView();
	DECLARE_DYNCREATE(CDOMRectifyView)

// ����
public:
	//CDOMRectifyDoc* GetDocument() const;
	enum CHECK_ORIENTATION
	{
		LEFT_RIGHT,
		BOTTOM_UP,
		NONE
	};
	bool m_bStartSelect;
	bool m_bStartWrapper;
	CHECK_ORIENTATION m_CheckOri;
	GLuint m_OrinVBO;
	GLuint m_WrapVBO;
// ����
public:

	OGREnvelope m_EnveSelectBox;
// ʵ��
public:
	virtual ~CDOMRectifyView();
	DECLARE_MESSAGE_MAP()
public:
	void SyncDisplay(const OGREnvelope& enve);
	int GetCurImage();
	void DrawInsideImageFrame();
	void DrawMatchImageFrame();
	void DrawOverlapBox();
	void DrawSelectBox();
	void DrawSelectPoint();
	void DrawImageNames();
	virtual void DrawTexture();
	virtual void DrawGeometry();
	virtual void DrawImageGrids();
	virtual void DrawImageFrame();
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnButtonPointAdd();
	afx_msg void OnUpdateButtonPointAdd(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonPointDelete();
	afx_msg void OnUpdateButtonPointDelete(CCmdUI *pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonWrapperCheck();
	afx_msg void OnUpdateButtonWrapperCheck(CCmdUI *pCmdUI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

