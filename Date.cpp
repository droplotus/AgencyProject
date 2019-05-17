#include "Date.h"

Date::Date() {
}

Date::Date(string date) {
	vector<string> date_str;
	parseText(date, 1, date_str, '/');
	date_str.resize(3);
	for (int i = 0; i < date_str.size(); i++) {
		if (date_str[i] == "" || !strIsInt(date_str[i])) {
			year = "0";
			month = "0";
			day = "0";
			return;
		}
	}
	year = date_str[0];
	month = date_str[1];
	day = date_str[2];
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

void Date::setDate(string date)
{
	vector<string> date_str;
	parseText(date, 1, date_str, '/');
	year = date_str[0];
	month = date_str[1];
	day = date_str[2];
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
	else if (ly < ry)
		return false;
	if (lm > rm)
		return true;
	else if (lm < rm)
		return false;
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
	else if (ly > ry)
		return false;
	if (lm < rm)
		return true;
	else if (lm > rm)
		return false;
	if (ld <= rd)
		return true;
	return false;
}

bool Date::isValid() {
	if (!strIsInt(year) || !strIsInt(month) || !strIsInt(day) || (stoi(month) > 12 || stoi(month) < 1) || (stoi(day) > 31 || stoi(day) < 1)) 
		return false;
	return true;
}

