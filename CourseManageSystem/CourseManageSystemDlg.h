// CourseManageSystemDlg.h : header file
//
#include <gdiplus.h>
#include "DataBase.h"
#include "CourseManageInterface.h"

using namespace std;

#pragma once
#pragma comment(lib,"gdiplus.lib")

// CCourseManageSystemDlg dialog
class CCourseManageSystemDlg : public CDialogEx {
private:
	//use GDI to change the background picture
	Gdiplus::GdiplusStartupInput m_GdiplusStarupInput;
	ULONG_PTR m_uGdiplusToken;
	Gdiplus::Image* m_img;
	POINT old;//record the width and height of window.
	//font
	CFont font;
	int fontSize = 125;
	SqliteDataBase db;;
	CAboutDlg pDlg;

public:
	CCourseManageSystemDlg(CWnd* pParent = nullptr); // standard constructor
	~CCourseManageSystemDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COURSEMANAGESYSTEM_DIALOG };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support

	//limit the size of the window
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	//afx_msg is an empty macro #define'd in afxwin.h
	//The code will compile and work the same with or without afx_msg,
	//but it is used by convention as an indicator that the function is 
	//a message handler, and is required if using the class wizard

	// Implementation
protected:
	HICON m_hIcon;//Icon handle.
	CRect m_rect;//record the Rect size.

	// Generated message map functions
	BOOL OnInitDialog() override;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

DECLARE_MESSAGE_MAP()
public:
	//	afx_msg HBRUSH OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor );
	//make the previous background invalid,and inform the OnPaint() Redraw the background.
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void ChangeSize(CWnd* pWnd, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
