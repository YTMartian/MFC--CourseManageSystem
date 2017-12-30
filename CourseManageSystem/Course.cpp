#include "stdafx.h"
#include "Course.h"

Course::Course() {
	courseNumber = totalClassHour = "NULL";
	courseProperty = courseName = L"NULL";
}

Course::Course(const Course& c) {
	courseNumber = c.courseNumber;
	courseName = c.courseName;
	courseProperty = c.courseProperty;
	totalClassHour = c.totalClassHour;
}

Course::Course(string nnumber, wstring nname, wstring np, string nt)
	: courseNumber(nnumber), courseName(nname), courseProperty(np), totalClassHour(nt) {
}

Course::~Course() {
}

string Course::getCourseNumber() {
	return courseNumber;
}

wstring Course::getCourseName() {
	return courseName;
}

wstring Course::getCourseProperty() {
	return courseProperty;
}

string Course::getTotalCourseHour() {
	return totalClassHour;
}

void Course::setCourseNumber(string t) {
	courseNumber = t;
}

void Course::setCourseName(wstring t) {
	courseName = t;
}

void Course::setCourseProperty(wstring t) {
	courseProperty = t;
}

void Course::setCourseClassHour(string t) {
	totalClassHour = t;
}
