#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Date.h"

using namespace std;

class Packet {
private:
	string id; // packet unique identifier
	vector<string> sites; // touristic sites to visit
	Date begin;  // begin date
	Date end;  // end date
	string pricePerPerson; // price per person
	string maxPersons; // number of persons still available in the packet (updated whenever the packet is sold to a new client)
	string boughtTickets;

public:
	Packet();
	Packet(string id, vector<string> sites, Date begin, Date end, string pricePerPerson, string maxPersons, string boughtTickets);
	Packet(vector<string> sites, Date begin, Date end, string pricePerPerson, string maxPersons);

	// GET methods
	string getId() const;
	vector<string> getSites() const;
	Date getBeginDate() const;
	Date getEndDate() const;
	string getPricePerPerson() const;
	string getMaxPersons() const;
	string getBoughtTickets() const;

	// SET methods
	void setId(string id);  // to set negatve if "deprecated"
	void setSites(vector<string> sites);
	void setBeginDate(Date begin);
	void setEndDate(Date end);
	void setPricePerPerson(string pricePerPerson);
	void setMaxPersons(string maxPersons);
	void setBoughtTickets(string boughtTickets);
};
