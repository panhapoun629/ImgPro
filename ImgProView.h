
// ImgProView.h : interface of the CImgProView class
//

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
using namespace std;
using namespace cv;

class CImgProView : public CView
{
protected: // create from serialization only
	CImgProView() noexcept;
	DECLARE_DYNCREATE(CImgProView)

	// Attributes
public:
	CImgProDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CImgProView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOperationGrayscale();
	afx_msg void OnFileOpen();
	Mat img_src;
	afx_msg void OnFileSave();
	Mat img_save;
};

#ifndef _DEBUG  // debug version in ImgProView.cpp
inline CImgProDoc* CImgProView::GetDocument() const
{
	return reinterpret_cast<CImgProDoc*>(m_pDocument);
}
#endif

