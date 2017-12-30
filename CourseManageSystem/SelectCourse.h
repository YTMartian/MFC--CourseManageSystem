#pragma once
#include <string>
#include "DataBase.h"

using namespace std;

class SelectCourse {
public:
	friend class SqliteDataBase;
	SelectCourse();
	SelectCourse(const SelectCourse& s);
	SelectCourse(string nn, string ni, string ns);
	string getSelectCourseNumber();
	string getStudentID();
	string getSelectCourseScore();
	~SelectCourse();
	void setCourseNumber(string t);
	void setStudentId(string t);
	void setScore(string t);
private:
	string courseNumber;
	string StudentID;
	string score;
};
