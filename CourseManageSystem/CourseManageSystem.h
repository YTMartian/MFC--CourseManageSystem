// CourseManageSystem.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCourseManageSystemApp:
// See CourseManageSystem.cpp for the implementation of this class
//

class CCourseManageSystemApp : public CWinApp {
public:
	CCourseManageSystemApp();

	// Overrides
public:
	BOOL InitInstance() override;

	// Implementation

DECLARE_MESSAGE_MAP()
};

extern CCourseManageSystemApp theApp;
