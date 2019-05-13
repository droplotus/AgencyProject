#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const std::string AGENCY_FILE_NAME = "agency.txt";

// this function returns TRUE if the file is empty, FALSE otherwise
bool isEmpty(std::ifstream& file);

// this function cleans the extra spaces before and after the text
void cleanSpaces(string& name);

// this function parses a text, dividing it by a character I choose and storing each parsed text into a vector
void parseText(string& var, size_t found_1, vector<string>& arr, char c);

string packToStr(vector<string> packs_arr);

string placesToStr(vector<string> places);

int findInVecStr(vector<string> vec, string elem);