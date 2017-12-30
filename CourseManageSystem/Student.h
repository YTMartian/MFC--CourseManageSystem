#pragma once

#include <atltime.h>
#include <string>
#include "DataBase.h"

using namespace std;


class Student {
public:
	friend class SqliteDataBase;
	Student();
	Student(Student& s);
	Student(string ns);
	Student(string ns, wstring nn, wstring ng, wstring na, wstring nm, string np);
	~Student();
	string getStudentID();
	wstring getStudentName();
	wstring getStudentGender();
	wstring getStudentAcademy();
	wstring getStudentMajor();
	string getStudentPassword();
	void setStudentId(string nd);
	void setStudentName(wstring nn);
	void setStudentGender(wstring ng);
	void setStudentAcademy(wstring na);
	void setStudentMajor(wstring nm);
	void setStudentPassword(string np);
private:
	//-------Chinese characters use wstring.---------//
	string studentId;//Student's id
	wstring name;//Student's name
	wstring gender;//Student's gender
	wstring academy;//Student's academy
	wstring major;//Student's major
	string password;
};
