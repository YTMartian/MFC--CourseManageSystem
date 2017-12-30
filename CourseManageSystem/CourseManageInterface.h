// CourseManageInterface.h : header file
//CAboutDlg dialog used for Course Manage Interface.
//
//
#include <gdiplus.h>
#include "DataBase.h"

using namespace std;

#pragma once
#pragma comment(lib,"gdiplus.lib")

class CAboutDlg : public CDialogEx {
public:
	CAboutDlg();
	void setStudentId(string nd);
private:
	Gdiplus::GdiplusStartupInput m_GdiplusStarupInput;
	ULONG_PTR m_uGdiplusToken;
	Gdiplus::Image* m_img;
	POINT old;//record the width and height of window.
	CFont font;//font
	int fontSize = 125;
	// Dialog Data
	SqliteDataBase db;
	Student stu;
	vector<int> topText{1026, 1027};//Static text at the top.
	vector<int> PersonalInfoText{1028, 1029, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037};//Static text in personalInfo.
	vector<int> addDeleteButtons{1025, 1039,1044,1046,1047};
	vector<int> editBox{1038, 1040, 1041, 1043, 1045};
	bool isStudentAddDelete;//judge whether is click student or course button.
	int courseOrSelectInfo = 0;
	int What;//Judge waht operation when click the ensure button.
	int courseNumber = 0;//Record the page.
	int selectNumber = 0;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	HICON m_hIcon;//Icon handle.
	CRect m_rect;//record the Rect size.

	void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	BOOL OnInitDialog() override;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	// Implementation
DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void ChangeSize(CWnd* pWnd, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	void showPersonalInfo();
	void showCourseInfo();
	void showSelectInfo();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
};
