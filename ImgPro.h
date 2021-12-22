
// ImgPro.h : main header file for the ImgPro application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CImgProApp:
// See ImgPro.cpp for the implementation of this class
//

class CImgProApp : public CWinApp
{
public:
	CImgProApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImgProApp theApp;
