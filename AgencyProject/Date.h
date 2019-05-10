#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"

using namespace std;

class Date{
 private:
  string day;
  string month;
  string year;

 public:
  Date();
  Date(string date);
  Date(string day, string month, string year);

  // GET methods
  string getDay() const;
  string getMonth() const;
  string getYear() const;
  
  // SET methods
  
  void setDay(string day);
  void setMonth(string month);
  void setYear(string year);

};
