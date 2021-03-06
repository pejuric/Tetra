
// Tetra.h : main header file for the Tetra application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTetraApp:
// See Tetra.cpp for the implementation of this class
//

class CTetraApp : public CWinApp
{
public:
	CTetraApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTetraApp theApp;
