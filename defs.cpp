#include "defs.h"

bool isEmpty(std::ifstream &file){
	return file.peek() == std::ifstream::traits_type::eof();
}

// this function cleans the extra spaces before and after the text
void cleanSpaces(string &name){
	while(name.at(0) == ' ') name.erase(0, 1); // changed if to while
	while(name.at(name.length()-1) == ' ') name.erase(name.length()-1); // changed if to while
}

// this function parses a text, dividing it by a character I choose and storing each parsed text into a vector
void parseText(string &var, size_t found_1, vector<string> &arr, char c){ // - found_1 is like split(%) in python where % is what I want him to split between, for example "/"
	if(found_1==0 || found_1 == var.length()-1) return;
	while(found_1!=string::npos){
		string parse;
		parse = var.substr(0, found_1);
		var.erase(0, found_1+1); // - erase my original until the next '/' string so my while loop can continue error free
		cleanSpaces(parse);
		arr.push_back(parse);
		found_1 = var.find_first_of(c);
	}
	// -had to push_back last value of address because my while loop wasn't perfect
	// 		so a last value is still un_pushed to the vector address_arr
	// -had to clean spaces in between because text file has a space between each '/'
	cleanSpaces(var);
	arr.push_back(var);
}

string packToStr(vector<string> packs_arr){
	string text = "";
	if(packs_arr.size() == 1){
		text = packs_arr[0];
	}else{
		for(int i=0; i<packs_arr.size()-1; i++){
			text += packs_arr[i] + " ; ";
		}
		text += packs_arr[packs_arr.size()-1];
	}
	return text;
}

string placesToStr(vector<string> places){
	if(places.size() == 1) return places[0];
	string places_str = places[0] + " - ";
	for(int i=1; i<places.size()-1; i++)
		places_str += places[i] + ", ";
	places_str += places[places.size()-1];
	return places_str;
}
