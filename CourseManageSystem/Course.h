#pragma once
#include <string>
#include "DataBase.h"

using namespace std;

class Course {
public:
	friend class SqliteDataBase;
	Course();
	Course(const Course& c);
	Course(string nnumber, wstring nname, wstring np, string nt);
	~Course();
	string getCourseNumber();
	wstring getCourseName();
	wstring getCourseProperty();
	string getTotalCourseHour();
	void setCourseNumber(string t);
	void setCourseName(wstring t);
	void setCourseProperty(wstring t);
	void setCourseClassHour(string t);
private:
	string courseNumber;
	wstring courseName;
	wstring courseProperty;
	string totalClassHour;
};
