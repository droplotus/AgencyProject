#include <iostream>
#include <string>
#include <vector>

#include "Agency.h"
#include "Menus.h"
// #include "utils.h"

vector<Client> clients;
vector<Packet> packets;
string last_id;

int main() {
	Agency agency = Agency(clients, packets, last_id);   // create the agency
	mainMenu(agency); // initial menu inicial with the major options of the application

	return 0;
}
