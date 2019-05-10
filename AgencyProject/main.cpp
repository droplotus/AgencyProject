#include <iostream>
#include <string>
#include <vector>

#include "Agency.h"
#include "Menus.h"
// #include "utils.h"

vector<Client> clients;
vector<Packet> packets;
string last_id;

int main(){
	string AGENCY_FILE_NAME;
	getline(cin, AGENCY_FILE_NAME);
	Agency agency = Agency(AGENCY_FILE_NAME, clients, packets, last_id);   // create the agency
	mainMenu(agency); // initial menu inicial with the major options of the application

	return 0;
}
