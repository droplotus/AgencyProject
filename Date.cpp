#include "Date.h"

Date::Date() {
}

Date::Date(string date) {
	
}


Date::Date(string day, string month, string year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

/*********************************
 * GET Methods
 ********************************/

string Date::getDay() const {
	return day;
}


string Date::getMonth() const {
	return month;
}

string Date::getYear() const {
	return year;
}

/*********************************
 * SET Methods
 ********************************/

void Date::setDay(string day) {
	this->day = day;
}
void Date::setMonth(string month) {
	this->month = month;
}

void Date::setYear(string year) {
	this->year = year;
}

bool Date::operator>=(Date right)
{
	int ly, lm, ld, ry, rm, rd;
	ly = stoi(year);
	lm = stoi(month);
	ld = stoi(day);
	ry = stoi(right.year);
	rm = stoi(right.month);
	rd = stoi(right.day);

	if (ly > ry)
		return true;
	if (lm > rm)
		return true;
	if (ld >= rd)
		return true;
	return false;
}

bool Date::operator<=(Date right)
{
	int ly, lm, ld, ry, rm, rd;
	ly = stoi(year);
	lm = stoi(month);
	ld = stoi(day);
	ry = stoi(right.year);
	rm = stoi(right.month);
	rd = stoi(right.day);

	if (ly < ry)
		return true;
	if (lm < rm)
		return true;
	if (ld <= rd)
		return true;
	return false;
}
