// CourseManageSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CourseManageSystem.h"
#include "CourseManageSystemDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCourseManageSystemDlg dialog


CCourseManageSystemDlg::CCourseManageSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COURSEMANAGESYSTEM_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	GdiplusStartup(&m_uGdiplusToken, &m_GdiplusStarupInput, nullptr);
}

CCourseManageSystemDlg::~CCourseManageSystemDlg() {
}


void CCourseManageSystemDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCourseManageSystemDlg, CDialogEx)
		ON_WM_SYSCOMMAND()
		ON_WM_PAINT()
		ON_WM_QUERYDRAGICON()
		ON_WM_GETMINMAXINFO()
		ON_WM_SIZE()
		ON_WM_CTLCOLOR()
		ON_BN_CLICKED( IDC_BUTTON1, &CCourseManageSystemDlg::OnBnClickedButton1 )
		ON_BN_CLICKED( IDC_BUTTON2, &CCourseManageSystemDlg::OnBnClickedButton2 )
END_MESSAGE_MAP()


BOOL CCourseManageSystemDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	db.getAllStudents();
	////////////////////////DEBUG////////////////////////////////////////
	/////////////////WHEN DESIGNING THE SECOND WINDOW////////////////////
	/*AfxGetMainWnd()->SendMessage(WM_CLOSE);
	pDlg.setStudentId("2016902093");
	db.getAllStudents();
	bool judge = db.judgeStudentExist("2016902093", "dongjiayi");
	pDlg.DoModal();*/
	////////////COMMENT OUT THESE CODE AFTER FINISHING THIS PROJECT//////
	////////////////////////////////////////////////////////////////////

	///////These two functions removed the title bar.//////////////////////
	//SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPED);
	////////This function eliminated the image residue.////////////////////
	//SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);


	//Set Buttons' picture
	HBITMAP hBitmap;
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE( IDB_BITMAP1 ));
	((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap);
	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP3 ));
	((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap);

	//get the size of window
	GetClientRect(&m_rect);
	old.x = m_rect.right - m_rect.left;
	old.y = m_rect.bottom - m_rect.top;

	//------------------------------Set edit Font-------------------------//
	CEdit* m_Edit_1 = (CEdit *)GetDlgItem(IDC_EDIT1); //associate control 1
	CEdit* m_Edit_2 = (CEdit *)GetDlgItem(IDC_EDIT2); //associate control 2
	font.CreatePointFont(fontSize, _T("Microsoft YaHei")); //set the font style L transes ANSI to UNICODE
	m_Edit_1->SetFont(&font);
	m_Edit_2->SetFont(&font);

	//-----set the background image---------------------------------------//
	//-----http://blog.csdn.net/qq_18297675/article/details/58661363--------//
	//-----http://blog.csdn.net/qq_18297675/article/details/59118492--------//
	char buf[256] = "";
	GetCurrentDirectoryA(256, buf);
	sprintf_s(buf, "%s\\res\\loginBackground.jpg", buf);//use sprint_sto format the string
	CStringW s; //transform to wide string
	s = buf;
	m_img = Gdiplus::Image::FromFile(s); //load picture

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	// TODO: Add extra initialization here

	return TRUE; // return TRUE  unless you set the focus to a control
}

void CCourseManageSystemDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCourseManageSystemDlg::OnPaint() {

	if (IsIconic()) {
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CPaintDC dc(this);
		CRect rect = {nullptr};
		GetClientRect(&rect); //get the size of the window.
		Gdiplus::Graphics g(dc);
		g.DrawImage(m_img, 0, 0, rect.Width(), rect.Height());
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCourseManageSystemDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}


//--------limit the size of dialog-----------------------//
void CCourseManageSystemDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI) {
	lpMMI->ptMaxTrackSize.x = 1920; //set max width
	lpMMI->ptMaxTrackSize.y = 1080; //set max height
	lpMMI->ptMinTrackSize.x = 1280; //set min width
	lpMMI->ptMinTrackSize.y = 720; //set min width
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CCourseManageSystemDlg::OnSize(UINT nType, int cx, int cy) {
	CDialogEx::OnSize(nType, cx, cy);

	//Let previous window invalid.
	Invalidate(FALSE);
	//judge whether the window is minimize,or it will Divide zero(Segmentation fault).
	if (nType != SIZE_MINIMIZED) {
		CWnd* pWnd;//CWnd is the Based Window Class.
		pWnd = GetDlgItem(IDC_STATIC1);
		ChangeSize(pWnd, cx, cy);
		pWnd = GetDlgItem(IDC_STATIC2);
		ChangeSize(pWnd, cx, cy);
		pWnd = GetDlgItem(IDC_EDIT1);
		ChangeSize(pWnd, cx, cy);
		pWnd = GetDlgItem(IDC_EDIT2);
		ChangeSize(pWnd, cx, cy);
		pWnd = GetDlgItem(IDC_BUTTON1);
		ChangeSize(pWnd, cx, cy);
		pWnd = GetDlgItem(IDC_BUTTON2);
		ChangeSize(pWnd, cx, cy);
		GetClientRect(&m_rect);// record the size after transfor to m_rect.    
	}

	// TODO: Add your message handler code here
}

//-----------https://www.cnblogs.com/Tris-wu/p/4956027.html-------//
void CCourseManageSystemDlg::ChangeSize(CWnd* pWnd, int cx, int cy) {
	//Determine whether it is empty, because the function is called when the dialog box is created, and the control is not created at that time.
	if (pWnd) {
		CRect rect; //Get the size of the control before the change.
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);//Convert the control size to the regional coordinates in a dialog box
		//cx/m_rect.Width() is the horizontal change ratio for the dialog box
		rect.left = rect.left * cx / m_rect.Width();//Adjust the size of the control
		rect.right = rect.right * cx / m_rect.Width();
		rect.top = rect.top * cy / m_rect.Height();
		rect.bottom = rect.bottom * cy / m_rect.Height();
		pWnd->MoveWindow(rect);//Set the size of control.
	}
}

HBRUSH CCourseManageSystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC1) {
		//Change IDC_STATIC1
		//judge whether the message is Static Text
		pDC->SelectObject(&font);//choose the font
		pDC->SetTextColor(RGB( 0, 0, 0 ));
		pDC->SetBkMode(OPAQUE);//set background transparent
		pDC->SetBkColor(RGB( 255, 255, 255 ));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH); // set background color
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC2) {
		//Change IDC_STATIC2
		//judge whether the message is Static Text
		pDC->SelectObject(&font);//choose the font
		pDC->SetTextColor(RGB( 0, 0, 0 ));
		pDC->SetBkMode(OPAQUE);//set background transparent
		pDC->SetBkColor(RGB( 255, 255, 255 ));//Match the background.
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH); // set background color
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

//==========================LOGIN=========================//
void CCourseManageSystemDlg::OnBnClickedButton1() {
	// TODO: Add your control notification handler code here
	CString studentID, password;
	GetDlgItemText(IDC_EDIT1, studentID);//get the string input in the Edit control
	GetDlgItemText(IDC_EDIT2, password);
	string s1 = CT2A(studentID.GetBuffer());
	string s2 = CT2A(password.GetBuffer());
	bool judge = db.judgeStudentExist(s1, s2);
	if (!judge) {
		CStringW sss(L"学号或密码错误！");
		MessageBox(sss);
		//Clear the text box
		CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT1);
		edit->SetWindowText(_T( "" ));
		edit = (CEdit*)GetDlgItem(IDC_EDIT2);
		edit->SetWindowText(_T( "" ));
	}
	else {
		//Close current window rather than hiding it and show other window at the same time.
		//ShowWindow(SW_HIDE);
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
		pDlg.setStudentId(s1);
		db.closeDataBase();
		pDlg.DoModal();
	}
}

//=================CANCELLATION=======================//
void CCourseManageSystemDlg::OnBnClickedButton2() {
	CString studentID, password;
	GetDlgItemText(IDC_EDIT1, studentID);
	GetDlgItemText(IDC_EDIT2, password);
	string s1 = CT2A(studentID.GetBuffer());
	string s2 = CT2A(password.GetBuffer());
	bool judge = db.judgeStudentExist(s1, s2);
	if (!judge) {
		CStringW sss(L"学号或密码错误！");
		MessageBox(sss);
		//Clear the text box
		CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT1);
		edit->SetWindowText(_T( "" ));
		edit = (CEdit*)GetDlgItem(IDC_EDIT2);
		edit->SetWindowText(_T( "" ));
	}
	else {
		db.delete_student(s1);
		CStringW sss(L"注销成功！");
		db.getAllStudents();
		MessageBox(sss);
		//Clear the text box
		CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT1);
		edit->SetWindowText(_T(""));
		edit = (CEdit*)GetDlgItem(IDC_EDIT2);
		edit->SetWindowText(_T( "" ));
	}
}
