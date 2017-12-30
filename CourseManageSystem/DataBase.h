#pragma once
#pragma comment(lib, "sqlite3.lib")
#include "sqlite3.h"
#include "Student.h"
#include "Course.h"
#include "SelectCourse.h"
#include <string>
#include <vector>
#include <map>


using namespace std;

//-----Declear the classes used.Or many errors-------//
class Student;
class Course;
class SelectCourse;

class SqliteDataBase {
public:
	SqliteDataBase();
	~SqliteDataBase();
	void addStudent(const Student& s);
	void addCourse(const Course& c);
	void addSelectCourse(const SelectCourse& sc);
	Student get_student(string studentID);
	Course get_course(string courseNumber);
	SelectCourse get_select_course(string courseNumber);
	void delete_student(string studentID);
	void delete_course(string courseNumber);
	void delete_select_course(string courseNumber);
	static vector<string> s;
	static vector<wstring> ws;
	map<string, string> mp;//Related courses and scores.
	vector<string> course_students;//Students who choose this course.
	vector<string> student_courses;//Courses which are chosen by this student.
	void get_course_students(string courseNumber);
	void get_student_courses(string studentId);
	void closeDataBase();
private:
	sqlite3* db;
	static bool init_;

	static bool init() {
		ws.push_back(L"string1");
		ws.push_back(L"string2");
		ws.push_back(L"string3");
		s.push_back("string1");
		s.push_back("string2");
		s.push_back("string3");

		return true;
	}

	static int index;

	vector<string> deletedStudent;//Restore the student deleted when cancellation.
	vector<string> deletedCourse;
	static bool isSelectCourse;
public:
	//---------nCount is the columns' number of the line.----//
	//-------Chinese characters use wstring---------------//
	static int callback(void* para, int nCount, char** pValue, char** pName);
	bool judgeStudentExist(string studentID, string password);
	bool judgeStudentIdExist(string studentID);
	bool judgeCourseIdExist(string courseNumber);
	bool judgeSelectCourseExist(string courseNumber);
	void buildMap();
	void getAllCourses();
	void getAllStudents();
	vector<string> allCourseNumber;
	vector<string> allStudents;//All students and passwords
	vector<string>passwords;
	void updataSelect(string courseNumber, string studentId);
};
