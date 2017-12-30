#include "stdafx.h"
#include "Student.h"

Student::Student() {
	studentId = password = "NULL";
	gender = academy = major = L"NULL";
}

Student::Student(Student& s) {
	studentId = s.studentId;
	name = s.name;
	gender = s.gender;
	academy = s.academy;
	major = s.major;
	password = s.password;
}

Student::Student(string ns)
	: studentId(ns) {
	password = "NULL";
	gender = academy = major = L"NULL";
}

Student::Student(string ns, wstring nn, wstring ng, wstring na, wstring nm, string np) {
	studentId = ns;
	name = nn;
	gender = ng;
	academy = na;
	major = nm;
	password = np;
}

Student::~Student() {
}

string Student::getStudentID() {
	return studentId;
}

wstring Student::getStudentName() {
	return name;
}

wstring Student::getStudentGender() {
	return gender;
}

wstring Student::getStudentAcademy() {
	return academy;
}

wstring Student::getStudentMajor() {
	return major;
}

string Student::getStudentPassword() {
	return password;
}

void Student::setStudentId(string nd) {
	studentId = nd;
}

void Student::setStudentName(wstring nn) {
	name = nn;
}

void Student::setStudentGender(wstring ng) {
	gender = ng;
}

void Student::setStudentAcademy(wstring na) {
	academy = na;
}

void Student::setStudentMajor(wstring nm) {
	major = nm;
}

void Student::setStudentPassword(string np) {
	password = np;
}
