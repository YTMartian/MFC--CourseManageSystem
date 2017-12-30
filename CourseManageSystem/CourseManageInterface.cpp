#include "stdafx.h"
#include "CourseManageInterface.h"
#include "resource.h"

#define ADDSTUDENT 0
#define ADDCOURSE 1
#define DELSTUDENT 2
#define DELCOURSE 3
#define COURSEINFO 4
#define SELECTINFO 5

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
		ON_WM_SYSCOMMAND()
		ON_WM_PAINT()
		ON_WM_QUERYDRAGICON()
		ON_WM_GETMINMAXINFO()
		ON_WM_SIZE()
		ON_WM_CTLCOLOR()
		ON_BN_CLICKED(IDC_BUTTON5, &CAboutDlg::OnBnClickedButton5)
		ON_BN_CLICKED(IDC_BUTTON6, &CAboutDlg::OnBnClickedButton6)
		ON_BN_CLICKED(IDC_BUTTON7, &CAboutDlg::OnBnClickedButton7)
		ON_BN_CLICKED(IDC_BUTTON8, &CAboutDlg::OnBnClickedButton8)
		ON_BN_CLICKED(IDC_BUTTON9, &CAboutDlg::OnBnClickedButton9)
		ON_BN_CLICKED(IDC_BUTTON10, &CAboutDlg::OnBnClickedButton10)
		ON_BN_CLICKED(IDC_BUTTON11, &CAboutDlg::OnBnClickedButton11)
		ON_BN_CLICKED(IDC_BUTTON12, &CAboutDlg::OnBnClickedButton12)
		ON_BN_CLICKED(IDC_BUTTON13, &CAboutDlg::OnBnClickedButton13)
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {
}

void CAboutDlg::setStudentId(string nd) {
	stu = db.get_student(nd);//Initialize the student who have login.
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

void CAboutDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI) {
	lpMMI->ptMaxTrackSize.x = 1920; //set max width
	lpMMI->ptMaxTrackSize.y = 1080; //set max height
	lpMMI->ptMinTrackSize.x = 1280; //set min width
	lpMMI->ptMinTrackSize.y = 720; //set min width
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

BOOL CAboutDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	db.buildMap();
	db.get_course_students("T1301011");
	db.get_student_courses(stu.getStudentID());

	isStudentAddDelete = false;

	///////THESE TWO FUNCTIONS REMOVED THE TITLE BAR.//////////////////////
	//SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPED);
	////////THIS FUNCTION ELIMINATED THE IMAGE RESIDUE.////////////////////
	//SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	//----------------------------Set Buttons' picture----------------------//
	GetDlgItem(IDC_BUTTON10)->ShowWindow(FALSE);
	HBITMAP hBitmap;
	if (stu.getStudentID() == "2016902093") {
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7));
		((CButton *)GetDlgItem(IDC_BUTTON5))->SetBitmap(hBitmap);
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8));
		((CButton *)GetDlgItem(IDC_BUTTON6))->SetBitmap(hBitmap);
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP9));
		((CButton *)GetDlgItem(IDC_BUTTON8))->SetBitmap(hBitmap);
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP10));
		((CButton *)GetDlgItem(IDC_BUTTON9))->SetBitmap(hBitmap);
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP11));
		((CButton *)GetDlgItem(IDC_BUTTON10))->SetBitmap(hBitmap);
	}
	else {
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4));
		((CButton *)GetDlgItem(IDC_BUTTON5))->SetBitmap(hBitmap);
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5));
		((CButton *)GetDlgItem(IDC_BUTTON6))->SetBitmap(hBitmap);
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP14));
		((CButton *)GetDlgItem(IDC_BUTTON11))->SetBitmap(hBitmap);
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP13));
		((CButton *)GetDlgItem(IDC_BUTTON12))->SetBitmap(hBitmap);
		hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP15));
		((CButton *)GetDlgItem(IDC_BUTTON13))->SetBitmap(hBitmap);
	}


	hBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6));
	((CButton *)GetDlgItem(IDC_BUTTON7))->SetBitmap(hBitmap);

	//------------------------------Set edit Font-------------------------//
	font.CreatePointFont(fontSize, _T("Microsoft YaHei"));
	for (auto i : editBox) {
		GetDlgItem(i)->SetFont(&font);
		GetDlgItem(i)->ShowWindow(FALSE);
	}

	//------------------------------Set user name.-----------------------//
	wchar_t* temp = new wchar_t[250];//TCHAR : font code is what you set.
	wstring name = stu.getStudentName();
	GetDlgItem(IDC_STATIC3)->SetWindowText(name.c_str());//Show user name.

	//--------If the login user is not administer.---------//
	for (auto i : addDeleteButtons)
		GetDlgItem(i)->ShowWindow(FALSE);
	if (stu.getStudentID() != "2016902093") {//the default administer is me.
		showPersonalInfo();
	}
	else {
		for (auto i : PersonalInfoText)
			GetDlgItem(i)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON7)->ShowWindow(FALSE);
	}
	//get the size of window
	GetClientRect(&m_rect);
	old.x = m_rect.right - m_rect.left;
	old.y = m_rect.bottom - m_rect.top;

	char buf[256] = "";
	GetCurrentDirectoryA(256, buf);
	sprintf_s(buf, "%s\\res\\manageBackground.jpg", buf);
	CStringW s; //transform to wide string
	s = buf;
	m_img = Gdiplus::Image::FromFile(s); //load picture

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

	// Set the icon for this dialog.
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE);// Set small icon.
	// TODO: Add extra initialization here

	return TRUE; // return TRUE  unless you set the focus to a control
}

void CAboutDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CAboutDlg::OnPaint() {
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

HCURSOR CAboutDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

void CAboutDlg::OnSize(UINT nType, int cx, int cy) {
	CDialogEx::OnSize(nType, cx, cy);

	//Let previous window invalid.
	Invalidate(FALSE);
	//judge whether the window is minimize,or it will Divide zero(Segmentation fault).
	if (nType != SIZE_MINIMIZED) {
		CWnd* pWnd;//CWnd is the Based Window Class.
		for (auto i : topText) {
			pWnd = GetDlgItem(i);
			ChangeSize(pWnd, cx, cy);
		}
		for (auto i : PersonalInfoText) {
			pWnd = GetDlgItem(i);
			ChangeSize(pWnd, cx, cy);
		}
		for (auto i : addDeleteButtons) {
			pWnd = GetDlgItem(i);
			ChangeSize(pWnd, cx, cy);
		}
		for (auto i : editBox) {
			pWnd = GetDlgItem(i);
			ChangeSize(pWnd, cx, cy);
		}
		pWnd = GetDlgItem(IDC_BUTTON10);
		ChangeSize(pWnd, cx, cy);
		GetClientRect(&m_rect);// record the size after transfor to m_rect.    
	}

	// TODO: Add your message handler code here
}

void CAboutDlg::ChangeSize(CWnd* pWnd, int cx, int cy) {
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

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	for (auto i : topText)
		if (pWnd->GetDlgCtrlID() == i) {
			//judge whether the message is Static Text
			pDC->SelectObject(&font);//choose the font
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(OPAQUE);//set background transparent
			pDC->SetBkColor(RGB(33, 173, 102));//Match the background.
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); // set background color
		}
	for (auto i : PersonalInfoText)
		if (pWnd->GetDlgCtrlID() == i) {
			pDC->SelectObject(&font);
			pDC->SetTextColor(RGB(0, 0,0));
			pDC->SetBkMode(OPAQUE);
			pDC->SetBkColor(RGB(255, 255, 255));
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

//=================PERSONAL-INFO============================//
void CAboutDlg::OnBnClickedButton5() {
	for (auto i : addDeleteButtons)
		GetDlgItem(i)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON10)->ShowWindow(FALSE);
	if (stu.getStudentID() != "2016902093") {
		for (auto i : PersonalInfoText)
			GetDlgItem(i)->ShowWindow(FALSE);
		CString cs0(stu.getStudentID().c_str());
		CStringW cs1(stu.getStudentName().c_str());
		CStringW cs2(stu.getStudentGender().c_str());
		CStringW cs3(stu.getStudentAcademy().c_str());
		CStringW cs4(stu.getStudentMajor().c_str());
		GetDlgItem(PersonalInfoText[0])->SetWindowText(L"姓名");
		GetDlgItem(PersonalInfoText[1])->SetWindowText(L"学号");
		GetDlgItem(PersonalInfoText[2])->SetWindowText(L"性别");
		GetDlgItem(PersonalInfoText[3])->SetWindowText(L"学院");
		GetDlgItem(PersonalInfoText[4])->SetWindowText(L"专业");
		GetDlgItem(PersonalInfoText[5])->SetWindowText(cs1);
		GetDlgItem(PersonalInfoText[6])->SetWindowText(cs0);
		GetDlgItem(PersonalInfoText[7])->SetWindowText(cs2);
		GetDlgItem(PersonalInfoText[8])->SetWindowText(cs3);
		GetDlgItem(PersonalInfoText[9])->SetWindowText(cs4);
		for (auto i : PersonalInfoText)
			GetDlgItem(i)->ShowWindow(TRUE);
	}
	else {
		for (auto i : editBox) {
			GetDlgItem(i)->ShowWindow(FALSE);
		}
		for (auto i = 0; i < 5; i++) {
			GetDlgItem(PersonalInfoText[i])->ShowWindow(FALSE);
		}
		for (int i = 0; i < 2; i++) {
			GetDlgItem(addDeleteButtons[i])->ShowWindow(TRUE);
		}
		isStudentAddDelete = true;//have clicked this button in administer.
	}
}

//=================COURSE-INFO============================//
void CAboutDlg::OnBnClickedButton6() {
	GetDlgItem(IDC_BUTTON10)->ShowWindow(FALSE);
	if (stu.getStudentID() != "2016902093") {
		courseOrSelectInfo = COURSEINFO;
		courseNumber = 0;
		showCourseInfo();
		GetDlgItem(IDC_BUTTON13)->ShowWindow(TRUE);
	}
	else {
		for (auto i : editBox) {
			GetDlgItem(i)->ShowWindow(FALSE);
		}
		for (auto i = 0; i < 5; i++) {
			GetDlgItem(PersonalInfoText[i])->ShowWindow(FALSE);
		}
		for (int i = 0; i < 2; i++) {
			GetDlgItem(addDeleteButtons[i])->ShowWindow(TRUE);
		}
		isStudentAddDelete = false;
	}
}

//=================SELECT-INFO============================//
void CAboutDlg::OnBnClickedButton7() {
	for (auto i : addDeleteButtons)
		GetDlgItem(i)->ShowWindow(FALSE);
	for (auto i : PersonalInfoText)
		GetDlgItem(i)->ShowWindow(FALSE);
	courseOrSelectInfo = SELECTINFO;
	selectNumber = 0;
	if (db.student_courses.size() == 0) {
		CStringW ss(L"未曾选课");
		MessageBox(ss);
	}
	else {
		showSelectInfo();
	}

}

void CAboutDlg::showPersonalInfo() {
	wstring s1 = stu.getStudentName();
	GetDlgItem(IDC_STATIC7)->SetWindowText(s1.c_str());
	string s2 = stu.getStudentID();
	CString s3(s2.c_str());
	GetDlgItem(IDC_STATIC11)->SetWindowText(s3);
	s1 = stu.getStudentGender();
	GetDlgItem(IDC_STATIC12)->SetWindowText(s1.c_str());
	s1 = stu.getStudentAcademy();
	GetDlgItem(IDC_STATIC13)->SetWindowText(s1.c_str());
	s1 = stu.getStudentMajor();
	GetDlgItem(IDC_STATIC14)->SetWindowText(s1.c_str());
}

void CAboutDlg::showCourseInfo() {
	Course c = db.get_course(db.allCourseNumber[courseNumber]);
	for (auto i : PersonalInfoText)
		GetDlgItem(i)->ShowWindow(FALSE);
	if (courseNumber != 0)
		GetDlgItem(addDeleteButtons[2])->ShowWindow(TRUE);
	else
		GetDlgItem(addDeleteButtons[2])->ShowWindow(FALSE);
	if (courseNumber != db.allCourseNumber.size() - 1)
		GetDlgItem(addDeleteButtons[3])->ShowWindow(TRUE);
	else
		GetDlgItem(addDeleteButtons[3])->ShowWindow(FALSE);
	CString cs0(c.getCourseNumber().c_str());
	CStringW cs1(c.getCourseName().c_str());
	CStringW cs2(c.getCourseProperty().c_str());
	CString cs3(c.getTotalCourseHour().c_str());
	GetDlgItem(PersonalInfoText[0])->SetWindowText(L"课程号");
	GetDlgItem(PersonalInfoText[1])->SetWindowText(L"课程名");
	GetDlgItem(PersonalInfoText[2])->SetWindowText(L"属性");
	GetDlgItem(PersonalInfoText[3])->SetWindowText(L"学时");
	GetDlgItem(PersonalInfoText[5])->SetWindowText(cs0);
	GetDlgItem(PersonalInfoText[6])->SetWindowText(cs1);
	GetDlgItem(PersonalInfoText[7])->SetWindowText(cs2);
	GetDlgItem(PersonalInfoText[8])->SetWindowText(cs3);
	for (auto i : PersonalInfoText)
		GetDlgItem(i)->ShowWindow(TRUE);
	GetDlgItem(PersonalInfoText[4])->ShowWindow(FALSE);
	GetDlgItem(PersonalInfoText[9])->ShowWindow(FALSE);
}

void CAboutDlg::showSelectInfo() {
	SelectCourse sc = db.get_select_course(db.student_courses[selectNumber]);
	string sss = db.student_courses[selectNumber];
	Course c = db.get_course(db.student_courses[selectNumber]);
	for (auto i : PersonalInfoText)
		GetDlgItem(i)->ShowWindow(FALSE);
	if (selectNumber != 0)
		GetDlgItem(addDeleteButtons[2])->ShowWindow(TRUE);
	else
		GetDlgItem(addDeleteButtons[2])->ShowWindow(FALSE);
	if (selectNumber != db.student_courses.size() - 1)
		GetDlgItem(addDeleteButtons[3])->ShowWindow(TRUE);
	else
		GetDlgItem(addDeleteButtons[3])->ShowWindow(FALSE);
	CString cs0(c.getCourseNumber().c_str());
	CStringW cs1(c.getCourseName().c_str());
	CString cs2(db.mp[c.getCourseNumber()].c_str());
	GetDlgItem(PersonalInfoText[0])->SetWindowText(L"课程号");
	GetDlgItem(PersonalInfoText[1])->SetWindowText(L"课程名");
	GetDlgItem(PersonalInfoText[2])->SetWindowText(L"成绩");
	GetDlgItem(PersonalInfoText[5])->SetWindowText(cs0);
	GetDlgItem(PersonalInfoText[6])->SetWindowText(cs1);
	GetDlgItem(PersonalInfoText[7])->SetWindowText(cs2);
	for (auto i : PersonalInfoText)
		GetDlgItem(i)->ShowWindow(TRUE);
	GetDlgItem(PersonalInfoText[3])->ShowWindow(FALSE);
	GetDlgItem(PersonalInfoText[4])->ShowWindow(FALSE);
	GetDlgItem(PersonalInfoText[8])->ShowWindow(FALSE);
	GetDlgItem(PersonalInfoText[9])->ShowWindow(FALSE);
}


void CAboutDlg::OnBnClickedButton8() {
	for (auto i : addDeleteButtons) {
		GetDlgItem(i)->ShowWindow(FALSE);
	}
	//=====================ADD STUDENT======================//
	if (isStudentAddDelete) {
		What = ADDSTUDENT;
		GetDlgItem(PersonalInfoText[0])->SetWindowText(L"学号");
		GetDlgItem(PersonalInfoText[1])->SetWindowText(L"姓名");
		GetDlgItem(PersonalInfoText[2])->SetWindowText(L"性别");
		GetDlgItem(PersonalInfoText[3])->SetWindowText(L"学院");
		GetDlgItem(PersonalInfoText[4])->SetWindowText(L"专业");
		for (auto i = 0; i < 5; i++) {
			GetDlgItem(PersonalInfoText[i])->ShowWindow(TRUE);
			GetDlgItem(editBox[i])->ShowWindow(TRUE);
		}
		GetDlgItem(IDC_BUTTON10)->ShowWindow(TRUE);
	}
		//=====================ADD COURSE======================//
	else {
		What = ADDCOURSE;
		GetDlgItem(PersonalInfoText[0])->SetWindowText(L"课程号");
		GetDlgItem(PersonalInfoText[1])->SetWindowText(L"课程名");
		GetDlgItem(PersonalInfoText[2])->SetWindowText(L"属性");
		GetDlgItem(PersonalInfoText[3])->SetWindowText(L"学时");
		for (auto i = 0; i < 4; i++) {
			GetDlgItem(PersonalInfoText[i])->ShowWindow(TRUE);
			GetDlgItem(editBox[i])->ShowWindow(TRUE);
		}
		GetDlgItem(IDC_BUTTON10)->ShowWindow(TRUE);
	}
}


void CAboutDlg::OnBnClickedButton9() {
	for (auto i : addDeleteButtons) {
		GetDlgItem(i)->ShowWindow(FALSE);
	}
	//=====================DELETE STUDENT======================//
	if (isStudentAddDelete) {
		What = DELSTUDENT;
		GetDlgItem(editBox[0])->ShowWindow(TRUE);
		GetDlgItem(PersonalInfoText[0])->SetWindowText(_T("学号"));
		GetDlgItem(PersonalInfoText[0])->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON10)->ShowWindow(TRUE);
	}
		//=====================DELETE COURSE======================//
	else {
		What = DELCOURSE;
		GetDlgItem(editBox[0])->ShowWindow(TRUE);
		GetDlgItem(PersonalInfoText[0])->SetWindowText(_T("课程号"));
		GetDlgItem(PersonalInfoText[0])->ShowWindow(TRUE);
		GetDlgItem(IDC_BUTTON10)->ShowWindow(TRUE);
	}
}

//=====================ENSURE=============================//
void CAboutDlg::OnBnClickedButton10() {
	if (What == ADDSTUDENT) {
		Student st;
		CString cs;
		GetDlgItemText(editBox[0], cs);
		string t = CT2A(cs.GetBuffer());
		bool judge = db.judgeStudentIdExist(t);
		//-----------//When didn't find it return -1.------------//
		if (judge || t.size() != 10 || t.find("201690") == -1) {
			CString tt(L"学号错误或已存在！");
			MessageBox(tt);
		}
		else {
			st.setStudentId(t);
			st.setStudentPassword(t);
			CString csw[4];
			for (int i = 0; i < 4; i++)
				GetDlgItemText(editBox[i + 1], csw[i]);
			wstring ws = csw[0];
			st.setStudentName(ws);
			ws = csw[1];
			st.setStudentGender(ws);
			ws = csw[2];
			st.setStudentAcademy(ws);
			ws = csw[3];
			st.setStudentMajor(ws);
			db.addStudent(st);
			db.getAllStudents();
			CString tt(L"添加成功！");
			MessageBox(tt);

		}

	}
	else if (What == ADDCOURSE) {
		Course c;
		CString cs;
		GetDlgItemText(editBox[0], cs);
		string t = CT2A(cs.GetBuffer());
		bool judge = db.judgeCourseIdExist(t);
		if (judge || t.size() != 8) {
			CString tt(L"课程号错误已存在！");
			MessageBox(tt);
		}
		else {
			c.setCourseNumber(t);
			GetDlgItemText(editBox[3], cs);
			t = CT2A(cs.GetBuffer());
			c.setCourseClassHour(t);
			CString csw[2];
			for (int i = 0; i < 2; i++)
				GetDlgItemText(editBox[i + 1], csw[i]);
			wstring ws = csw[0];
			c.setCourseName(ws);
			ws = csw[1];
			c.setCourseProperty(ws);
			CString tt(L"添加成功！");
			MessageBox(tt);
			db.addCourse(c);
			db.getAllCourses();
		}
	}
	else if (What == DELSTUDENT) {
		CString cs;
		GetDlgItemText(editBox[0], cs);
		string t = CT2A(cs.GetBuffer());
		bool judge = db.judgeStudentIdExist(t);
		if (judge == TRUE) {
			db.delete_student(t);
			db.getAllStudents();
			CString s(L"删除成功！");
			MessageBox(s);
		}
		else {
			CString s(L"无此学号！");
			MessageBox(s);
		}
	}
	else if (What == DELCOURSE) {
		CString cs;
		GetDlgItemText(editBox[0], cs);
		string t = CT2A(cs.GetBuffer());
		bool judge = db.judgeCourseIdExist(t);
		if (judge == TRUE) {
			db.delete_course(t);
			CString s(L"删除成功！");
			db.getAllCourses();
			MessageBox(s);
		}
		else {
			CString s(L"无此课程号！");
			MessageBox(s);
		}
	}
	for (auto i = 0; i < 5; i++) {
		GetDlgItem(PersonalInfoText[i])->ShowWindow(FALSE);
	}
	for (auto i : editBox) {
		GetDlgItem(i)->ShowWindow(FALSE);
		GetDlgItem(i)->SetWindowText(_T(""));
	}
	GetDlgItem(IDC_BUTTON10)->ShowWindow(FALSE);
}

//======================PREVIOUS PAGE=====================//
void CAboutDlg::OnBnClickedButton11() {
	if (courseOrSelectInfo == COURSEINFO) {
		courseNumber -= 1;
		showCourseInfo();
	}
	else if (courseOrSelectInfo == SELECTINFO) {
		selectNumber -= 1;
		showSelectInfo();
	}
}

//======================NEXT PAGE=========================//
void CAboutDlg::OnBnClickedButton12() {
	if (courseOrSelectInfo == COURSEINFO) {
		courseNumber += 1;
		showCourseInfo();
	}
	else if (courseOrSelectInfo == SELECTINFO) {
		selectNumber += 1;
		showSelectInfo();
	}
}

//=====================ADD COURSE ENSURE======================//
void CAboutDlg::OnBnClickedButton13() {
	auto exist = find(db.student_courses.begin(), db.student_courses.end(), db.allCourseNumber[courseNumber]);
	if (exist != db.student_courses.end()) {
		CStringW s(L"选课失败，已选！");
		MessageBox(s);
	}
	else {
		db.updataSelect(db.allCourseNumber[courseNumber], stu.getStudentID());
		//------------updata some data.---------//
		db.buildMap();
		db.get_course_students("T1301011");
		db.get_student_courses(stu.getStudentID());
		CStringW s(L"选课成功！");
		MessageBox(s);
	}

}
