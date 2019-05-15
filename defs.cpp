#include "defs.h"
#include "Date.h"

bool isEmpty(std::ifstream& file) {
	return file.peek() == std::ifstream::traits_type::eof();
}

// this function cleans the extra spaces before and after the text
void cleanSpaces(string& name) {
	while (name.at(0) == ' ') name.erase(0, 1); // changed if to while
	while (name.at(name.length() - 1) == ' ') name.erase(name.length() - 1); // changed if to while
}

// this function parses a text, dividing it by a character I choose and storing each parsed text into a vector
void parseText(string var, size_t found_1, vector<string> & arr, char c) { // - found_1 is like split(%) in python where % is what I want him to split between, for example "/"
	if (var.size() == 0) {
		return;
	}
	if (var.find(c) == string::npos) {
		arr.push_back(var);
		cleanSpaces(arr[0]);
		return;
	}
	do {
		int ix = var.find(c);
		arr.push_back(var.substr(0, ix));
		var = var.substr(ix + 1);
		if (var.find(c) == string::npos) {
			arr.push_back(var);
		}
	} while (var.find(c) != string::npos);
	for (int i = 0; i < arr.size(); i++) {
		cleanSpaces(arr[i]);
	}
}

string packToStr(vector<string> packs_arr) {
	string text = "";
	if (packs_arr.size() == 1) {
		text = packs_arr[0];
	}
	else {
		for (int i = 0; i < packs_arr.size() - 1; i++) {
			text += packs_arr[i] + " ; ";
		}
		text += packs_arr[packs_arr.size() - 1];
	}
	return text;
}

string placesToStr(vector<string> places) {
	if (places.size() == 1) return places[0];
	string places_str = places[0] + " - ";
	for (int i = 1; i < places.size() - 1; i++)
		places_str += places[i] + ", ";
	places_str += places[places.size() - 1];
	return places_str;
}

int findInVecStr(vector<string> vec, string elem) {
	/*
	Return the index of elem in a vector with elements of type string.
	*/
	int index = -1;
	for (unsigned i = 0; i < vec.size(); i++) {
		if (vec[i] == elem) {
			index = i;
			break;
		}
	}
	return index;
}	//NOVO!!

bool strIsInt(string n)
{
	for (int i = 0; i < n.size(); i++) {
		if (n[i] < 48 || n[i] > 57) {
			return false;
		}
	}
	return true;
}

bool strIsDate(string date)
{
	vector<string> date_arr;
	parseText(date, 1, date_arr, '/');
	Date date1;
	if (date_arr.size() == 3) {
		date1.setDate(date);
		if (date1.isValid()) return true;
	}
	return false;
}

