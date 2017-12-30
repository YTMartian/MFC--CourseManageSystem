#include "stdafx.h"
#include "SelectCourse.h"

SelectCourse::SelectCourse() {
	courseNumber = score = StudentID = "NULL";

}

SelectCourse::SelectCourse(const SelectCourse& s)
	: courseNumber(s.courseNumber), StudentID(s.StudentID), score(s.score) {
}

SelectCourse::SelectCourse(string nn, string ni, string ns)
	: courseNumber(nn), StudentID(ni), score(ns) {
}

string SelectCourse::getSelectCourseNumber() {
	return courseNumber;
}

string SelectCourse::getStudentID() {
	return StudentID;

}

string SelectCourse::getSelectCourseScore() {
	return score;
}

SelectCourse::~SelectCourse() {
}

void SelectCourse::setCourseNumber(string t) {
	courseNumber = t;
}

void SelectCourse::setStudentId(string t) {
	StudentID = t;
}

void SelectCourse::setScore(string t) {
	score = t;
}
