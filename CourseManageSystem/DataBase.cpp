#include "stdafx.h"
#include "DataBase.h"
#include <cstring>
#include <cstdio>
#include <istream>

//-----Initialize the static variables.----//
//-----https://www.cnblogs.com/chulia20002001/archive/2013/05/03/3055985.html---------//
vector<string> SqliteDataBase::s;
vector<wstring> SqliteDataBase::ws;
bool SqliteDataBase::init_ = init();
bool SqliteDataBase::isSelectCourse = false;
int SqliteDataBase::index = 0;

SqliteDataBase::SqliteDataBase() {
	//All the operations return value is an Integer.When the operation is successful it
	//returns TRUE,or it returns FALSE.
	int rc = sqlite3_open("./db.sqlite3", &db);
	char* studentSQL = new char[1024];
	studentSQL = "CREATE TABLE STUDENTS("
		"STUDENTID      TEXT    NOT NULL,"
		"NAME           TEXT    NOT NULL,"
		"GENDER         TEXT    NOT NULL,"
		"ACADEMY        TEXT    NOT NULL,"
		"MAJOR          TEXT    NOT NULL,"
		"PASSWORD       TEXT    NOT NULL);";
	sqlite3_exec(db, studentSQL, nullptr, nullptr, nullptr);
	char* courseSQL = new char[1024];
	courseSQL = "CREATE TABLE COURSES("
		"NUMBER         TEXT    NOT NULL,"
		"NAME           TEXT    NOT NULL,"
		"PROPERTY       TEXT    NOT NULL,"
		"HOUR           TEXT    NOT NULL );";
	sqlite3_exec(db, courseSQL, nullptr, nullptr, nullptr);
	char* selectCourseSQL = new char[1024];
	selectCourseSQL = "CREATE TABLE SELECTCOURSE("
		"COURSENUMBER   TEXT    NOT NULL,"
		"STUDENTID      TEXT    NOT NULL,"
		"SCORE          TEXT    NOT NULL );";
	sqlite3_exec(db, selectCourseSQL, nullptr, nullptr, nullptr);
}

SqliteDataBase::~SqliteDataBase() {
	sqlite3_close(db);
}

void SqliteDataBase::addStudent(const Student& s) {
	auto exist = find(deletedStudent.begin(), deletedStudent.end(), s.studentId);
	if (exist != deletedStudent.end()) {
		deletedStudent.erase(exist);
	}
	bool judge = judgeStudentIdExist(s.studentId);
	if (judge)return;
	char* sql = new char[500];
	//--------Solve the unsafe problem of the sprintf.-----//
	//--------https://jingyan.baidu.com/article/49711c616b8a1ffa441b7cdc.html--------//
	sprintf(sql, "INSERT INTO STUDENTS (STUDENTID,NAME,GENDER,ACADEMY,MAJOR,PASSWORD) "
	        "VALUES ('%s','%lls', '%lls', '%lls', '%lls','%s' ); ", s.studentId.c_str(), s.name.c_str(), s.gender.c_str(),
	        s.academy.c_str(), s.major.c_str(),
	        s.password.c_str());
	int rc = sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
	delete[] sql;
}

void SqliteDataBase::addCourse(const Course& c) {
	auto exist = find(deletedCourse.begin(), deletedCourse.end(), c.courseNumber);
	if (exist != deletedCourse.end()) {
		deletedCourse.erase(exist);
	}
	bool judge = judgeCourseIdExist(c.courseNumber);
	if (judge)return;
	char* sql = new char[512];
	//------ATTENTION:some string have " ' ",so sql syntax wrong!--------////
	sprintf(sql, "INSERT INTO COURSES(NUMBER,NAME,PROPERTY,HOUR) "
	        "VALUES('%s','%lls', '%lls', '%s'); ", c.courseNumber.c_str(), c.courseName.c_str(),
	        c.courseProperty.c_str(), c.totalClassHour.c_str());
	int rc = sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
	delete[] sql;
}

void SqliteDataBase::addSelectCourse(const SelectCourse& sc) {
	char* sql = new char[512];
	sprintf(sql, "INSERT INTO SELECTCOURSE (COURSENUMBER,STUDENTID,SCORE) "
	        "VALUES ('%s','%s', '%s'); ", sc.courseNumber.c_str(), sc.StudentID.c_str(),
	        sc.score.c_str());
	int rc = sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
	delete[] sql;
}


Student SqliteDataBase::get_student(string studentID) {
	char* sql = new char[500];
	sprintf(sql, "SELECT * FROM STUDENTS WHERE STUDENTID = '%s'", studentID.c_str());
	//Use the CALLBACK function.
	int rc = sqlite3_exec(db, sql, callback, this, nullptr);
	Student temp(s[0], ws[0], ws[1], ws[2], ws[3], s[1]);
	delete[] sql;
	return temp;
}

Course SqliteDataBase::get_course(string courseNumber) {
	char* sql = new char[500];
	sprintf(sql, "SELECT * FROM COURSES WHERE NUMBER = '%s'", courseNumber.c_str());
	//Use the CALLBACK function.
	int rc = sqlite3_exec(db, sql, callback, nullptr, nullptr);
	size_t a = s.size();
	size_t b = ws.size();
	Course temp(s[0], ws[0], ws[1], s[1]);
	delete[] sql;
	return temp;
}

SelectCourse SqliteDataBase::get_select_course(string courseNumber) {
	isSelectCourse = true;
	char* sql = new char[500];
	sprintf(sql, "SELECT * FROM SELECTCOURSE WHERE COURSENUMBER = '%s'", courseNumber.c_str());
	//Use the CALLBACK function.
	sqlite3_exec(db, sql, callback, nullptr, nullptr);
	SelectCourse temp(s[0], s[1], s[2]);
	delete[] sql;
	return temp;
}

void SqliteDataBase::delete_student(string studentID) {
	auto exist = find(deletedStudent.begin(), deletedStudent.end(), studentID);
	if (exist != deletedStudent.end()) {
		return;
	}
	char* sql = new char[500];
	//Don't add '*' behind DELETE.
	sprintf(sql, "DELETE FROM STUDENTS WHERE STUDENTID = '%s'", studentID.c_str());
	sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
	delete[] sql;
	deletedStudent.push_back(studentID);
}

void SqliteDataBase::delete_course(string courseNumber) {
	auto exist = find(deletedCourse.begin(), deletedCourse.end(), courseNumber);
	if (exist != deletedCourse.end()) {
		return;
	}
	char* sql = new char[500];
	sprintf(sql, "DELETE FROM COURSES WHERE NUMBER = '%s'", courseNumber.c_str());
	sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
	delete[] sql;
}

void SqliteDataBase::delete_select_course(string courseNumber) {
	char* sql = new char[500];
	sprintf(sql, "DELETE FROM SELECTCOURSE WHERE COURSENUMBER = '%s'", courseNumber.c_str());
	sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
	delete[] sql;
}

void SqliteDataBase::get_course_students(string courseNumber) {
	course_students.clear();
	get_select_course(courseNumber);
	string st;
	for (unsigned int i = 0; i < s[1].size(); i++) {
		if (s[1][i] == ',') {
			course_students.push_back(st);
			st.clear();
		}
		else {
			st += s[1][i];
		}
	}

}

void SqliteDataBase::get_student_courses(const string studentId) {
	for (auto i : allCourseNumber) {
		mp[i] = "0";
	}
	student_courses.clear();
	vector<string> tempCourses;
	string sql = "SELECT * FROM SELECTCOURSE";
	char** result;
	int row, column;
	int rc = sqlite3_get_table(db, sql.c_str(), &result, &row, &column, nullptr);
	int p = column;
	for (int i = 0; i < row; i++) {
		string ss;
		bool judge = true;
		for (int j = 0; j < column; j++) {
			ss = result[p++];
			if (judge)tempCourses.push_back(ss);
			judge = false;
		}
	}
	sqlite3_free_table(result);//Free memory.
	for (auto courseNumber : tempCourses) {
		int index_ = 0;
		get_select_course(courseNumber);
		string st;
		unsigned int i;
		for (i = 0; i < s[1].size(); i++) {
			if (s[1][i] == ',') {
				if (st == studentId) {
					student_courses.push_back(courseNumber);
					break;
				}
				index_++;
				st.clear();
			}
			else {
				st += s[1][i];
			}
		}
		if (i == s[1].size())continue;
		st.clear();
		for (i = 0; i < s[2].size(); i++) {
			if (s[2][i] == ',') {
				if (index_ == 0) {
					mp[courseNumber] = st;
					break;
				}
				index_--;
				st.clear();
			}
			else {
				st += s[2][i];
			}
		}
	}
}

void SqliteDataBase::closeDataBase() {
	sqlite3_close(db);
}

//------http://blog.csdn.net/jqsad/article/details/51782088-------//
int SqliteDataBase::callback(void* para, int nCount, char** pValue, char** pName) {
	//Clear s Before putting the data into it.
	ws.clear();
	s.clear();
	if (isSelectCourse) {
		isSelectCourse = false;
		for (int i = 0; i < nCount; i++)
			s.push_back(pValue[i]);
		return 0;
	}
	s.push_back(pValue[0]);
	for (int i = 1; i < nCount - 1; i++) {
		wchar_t* temp = new wchar_t[250];
		wsprintf(temp, L"%s", pValue[i]);
		ws.push_back(temp);
		delete[] temp;
	}
	s.push_back(pValue[nCount - 1]);
	return 0;
}

bool SqliteDataBase::judgeStudentExist(string studentID, string password) {
	auto exist = find(deletedStudent.begin(), deletedStudent.end(), studentID);
	if (exist != deletedStudent.end()) {
		return false;
	}
	unsigned int i = 0;
	for(i=0;i<allStudents.size();i++) {
		if(allStudents[i]==studentID) {
			break;
		}
	}
	if (i == allStudents.size())return false;
	if (passwords[i] != password)return false;
	return true;
//=========================================================================//
//==============================HUGE BUG!==================================//
//======================DO NOT JUDGE IT AS FOLLOWS!========================//
//=========================================================================//
	//char* sql = new char[500];
	////Must add '*' behind SELECT.
	//sprintf(sql, "SELECT * FROM STUDENTS WHERE STUDENTID = '%s'", studentID.c_str());
	////judge whether exists the data
	//struct sqlite3_stmt* selectstmt;
	//int rc = sqlite3_prepare_v2(db, sql, -1, &selectstmt, nullptr);
	//delete[] sql;
	//if (rc == SQLITE_OK) {
	//	if (sqlite3_step(selectstmt) != SQLITE_ROW) {

	//		return false;
	//	}
	//	get_student(studentID);
	//	if (s[1] != password) {

	//		return false;
	//	}

	//	return true;
	//}

	//return false;
}

bool SqliteDataBase::judgeStudentIdExist(string studentID) {
	auto exist = find(deletedStudent.begin(), deletedStudent.end(), studentID);
	if (exist != deletedStudent.end()) {
		return false;
	}
	auto exist2 = find(allStudents.begin(), allStudents.end(), studentID);
	if (exist2 == allStudents.end())return false;
	return true;
	/*char* sql = new char[500];
	sprintf(sql, "SELECT * FROM STUDENTS WHERE STUDENTID = '%s'", studentID.c_str());
	struct sqlite3_stmt* selectstmt;
	int rc = sqlite3_prepare_v2(db, sql, -1, &selectstmt, nullptr);
	delete[] sql;
	if (rc == SQLITE_OK) {
		if (sqlite3_step(selectstmt) != SQLITE_ROW) {
			return false;
		}

		return true;
	}

	return false;*/

}

bool SqliteDataBase::judgeCourseIdExist(string courseNumber) {
	auto exist = find(deletedCourse.begin(), deletedCourse.end(), courseNumber);
	if (exist != deletedCourse.end()) {
		return false;
	}
	auto exist2 = find(allCourseNumber.begin(), allCourseNumber.end(), courseNumber);
	if (exist2 == allCourseNumber.end())return false;
	return true;
	//char* sql = new char[500];
	////----------ATTENTION:Add '' to %s.---------------//
	//sprintf(sql, "SELECT * FROM COURSES WHERE NUMBER = '%s'", courseNumber.c_str());
	//struct sqlite3_stmt* selectstmt;
	//int rc = sqlite3_prepare_v2(db, sql, -1, &selectstmt, nullptr);
	//delete[] sql;
	//if (rc == SQLITE_OK) {
	//	if (sqlite3_step(selectstmt) != SQLITE_ROW) {

	//		return false;
	//	}

	//	return true;
	//}

	//return false;
}

bool SqliteDataBase::judgeSelectCourseExist(string courseNumber) {
	char* sql = new char[500];
	sprintf(sql, "SELECT * FROM SELECTCOURSE WHERE COURSENUMBER = '%s'", courseNumber.c_str());
	struct sqlite3_stmt* selectstmt;
	int rc = sqlite3_prepare_v2(db, sql, -1, &selectstmt, nullptr);
	delete[] sql;
	if (rc == SQLITE_OK) {
		if (sqlite3_step(selectstmt) != SQLITE_ROW) {

			return false;
		}

		return true;
	}

	return false;
}

void SqliteDataBase::buildMap() {
	getAllCourses();
}

void SqliteDataBase::getAllCourses() {
	allCourseNumber.clear();
	string sql = "SELECT * FROM COURSES";
	char** result;
	int row, column;
	int rc = sqlite3_get_table(db, sql.c_str(), &result, &row, &column, nullptr);
	int p = column;
	for (int i = 0; i < row; i++) {
		string ss;
		bool judge = true;
		for (int j = 0; j < column; j++) {
			ss = result[p++];
			if (judge)allCourseNumber.push_back(ss);
			judge = false;
		}
	}
	sqlite3_free_table(result);//Free memory.
}

void SqliteDataBase::getAllStudents() {
	allStudents.clear();
	passwords.clear();
	string sql = "SELECT * FROM STUDENTS";
	char** result;
	int row, column;
	int rc = sqlite3_get_table(db, sql.c_str(), &result, &row, &column, nullptr);
	int p = column;
	for (int i = 0; i < row; i++) {
		string ss;
		for (int j = 0; j < column; j++) {
			ss = result[p++];
			if (j==0)allStudents.push_back(ss);
			else if (j == column - 1)passwords.push_back(ss);
		}
	}
	for (auto i : allStudents)
		i;
	for (auto i : passwords)
		i;
	sqlite3_free_table(result);//Free memory.
}

void SqliteDataBase::updataSelect(string courseNUmber, string studentId) {
	bool judge = judgeSelectCourseExist(courseNUmber);
	if (judge == false) {
		SelectCourse sc;
		string newIDS = studentId + ',';//New STUDENTID
		string newScores = "0,";//New SCORE
		sc.setStudentId(newIDS);
		sc.setCourseNumber(courseNUmber);
		sc.setScore(newScores);
		addSelectCourse(sc);
		return;
	}
	SelectCourse sc = get_select_course(courseNUmber);
	string newIDS = s[1] + studentId + ',';//New STUDENTID
	string newScores = s[2] + "0,";//New SCORE
	char* sql = new char[10240];
	sprintf(
		sql,
		"UPDATE SELECTCOURSE SET STUDENTID = '%s' WHERE COURSENUMBER = '%s';UPDATE SELECTCOURSE SET SCORE = '%s' WHERE COURSENUMBER = '%s';",
		newIDS.c_str(),
		courseNUmber.c_str(), newScores.c_str(), courseNUmber.c_str());
	int rc = sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
	delete[] sql;

}
