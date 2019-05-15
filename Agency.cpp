#include "Agency.h"

string Agency::dateToStr(Date date) const {
	return date.getYear() + "/" + date.getMonth() + "/" + date.getDay();
}

void Agency::showTravelPacksFromAllClients() {
	vector<Packet> tps_arr;
	vector<string> id_packs_arr;
	vector<string> id_packs_arr_temp;		//NOVO!!!

	// fetchin all the ID's I have for each client
	for (int i = 0; i < clients.size(); i++)
		for (int j = 0; j < clients[i].getPacketList().size(); j++)
			id_packs_arr.push_back(clients[i].getPacketList().at(j));

	// erasing all the same ID's I have in the vector
	/*for(int i=id_packs_arr.size()-1; i>0; i--)
		for(int j=i-1; j>=0; j--)
			if(id_packs_arr[i] == id_packs_arr[j]) id_packs_arr.erase(id_packs_arr.begin() + j);*/

	for (int i = 0; i < id_packs_arr.size(); i++)
		if (findInVecStr(id_packs_arr_temp, id_packs_arr[i]) == -1)
			id_packs_arr_temp.push_back(id_packs_arr[i]);
	id_packs_arr = id_packs_arr_temp;

	// adding them to a tps_arr so I can display them with showTPS(), using abs() because of the negative ID's
	for (int i = 0; i < packets.size(); i++)
		for (int j = 0; j < id_packs_arr.size(); j++)
			if (abs(stoi(packets[i].getId())) == abs(stoi(id_packs_arr[j]))) tps_arr.push_back(packets[i]);

	showTps(tps_arr);

	cout << "\tPresse ENTER para recuar...";
	string line;
	getline(cin, line);
}

void Agency::showTravelPacksFromClient(string nif) {
	vector<Packet> tps_arr;
	vector<string> id_packs_arr;
	int index;
	bool found = false;
	do {
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i].getVATnumber() == nif) {
				found = true;
				index = i;
				break;
			}
		}
		if (!found) {
			cout << "\tNao existe ninguem com este NIF, escolha outro: ";
			getline(cin, nif);
		}
	} while (!found);

	id_packs_arr = clients[index].getPacketList();

	for (int i = 0; i < packets.size(); i++)
		for (int j = 0; j < id_packs_arr.size(); j++)
			if (abs(stoi(packets[i].getId())) == abs(stoi(id_packs_arr[j]))) tps_arr.push_back(packets[i]);

	showTps(tps_arr);

	cout << "\tPresse ENTER para recuar...";
	string line;
	getline(cin, line);
}

void Agency::showTps(vector<Packet> tps_arr) {
	cout << endl << std::left << std::setfill(' ') << std::setw(8) << "\tID" << std::setw(56) << "destino(s)" << std::setw(24) << "data inicial" << std::setw(16) << "data final" << std::setw(9) << "preco" << std::setw(11) << "bilhetes" << "comprados" << endl;
	cout << "\t--------------------------------------------------------------------------------------------------------------------------------------";
	for (int i = 0; i < tps_arr.size(); i++) {
		cout << endl << "\t";
		cout << std::setw(7) << tps_arr[i].getId();
		string places = "";
		for (int j = 0; j < tps_arr[i].getSites().size() - 1; j++) {
			if (j == 0) places += tps_arr[i].getSites().at(j) + " - ";
			else places += tps_arr[i].getSites().at(j) + ", ";
		}
		places += tps_arr[i].getSites().at(tps_arr[i].getSites().size() - 1);
		cout << std::setw(56) << places;
		string date = tps_arr[i].getBeginDate().getYear() + "/" + tps_arr[i].getBeginDate().getMonth() + "/" + tps_arr[i].getBeginDate().getDay();
		cout << std::setw(24) << date;
		date = tps_arr[i].getEndDate().getYear() + "/" + tps_arr[i].getEndDate().getMonth() + "/" + tps_arr[i].getEndDate().getDay();
		cout << std::setw(16) << date;
		cout << std::setw(9) << tps_arr[i].getPricePerPerson();
		cout << std::setw(11) << tps_arr[i].getMaxPersons();
		cout << tps_arr[i].getBoughtTickets();
	}
	cout << endl << "\t--------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
}

int Agency::findTpByID(string id) const {
	for (int i = 0; i < packets.size(); i++)
		if (packets[i].getId() == id) return i;
	return -1;
}

void Agency::fillClients(string fileName) {
	ifstream clientsFile;
	clientsFile.open(fileName);
	// - if file cannot be opened for some reason, return me an error.
	if (!clientsFile) {
		cerr << "Unable to open file clients.txt" << endl;
		exit(1);
	}

	if (isEmpty(clientsFile)) {
		clientsFile.close();
		return;
	}

	string line;

	while (!clientsFile.eof()) {
		Client client;
		Address address;
		vector<string> address_arr;
		vector<string> packs_arr;

		getline(clientsFile, line);
		client.setName(line);

		getline(clientsFile, line);
		client.setVATnumber(line);

		getline(clientsFile, line);
		client.setFamilySize(line);

		getline(clientsFile, line);
		size_t found_1 = line.find_first_of('/');
		parseText(line, found_1, address_arr, '/');
		address = Address(address_arr[0], address_arr[1], address_arr[2], address_arr[3], address_arr[4]);
		client.setAddress(address);

		getline(clientsFile, line);
		found_1 = line.find_first_of(';');
		parseText(line, found_1, packs_arr, ';');
		client.setPacketList(packs_arr);

		clients.push_back(client);

		getline(clientsFile, line);
	}
	clientsFile.close();
}

void Agency::fillPacks(string fileName, string & last_id) {
	ifstream packsFile;
	packsFile.open(fileName);

	// -if file cannot be opened for some reason, return me an error.
	if (!packsFile) {
		cerr << "Unable to open file packs.txt" << endl;
		exit(1);
	}

	if (isEmpty(packsFile)) {
		ofstream output;
		output.open(fileName);
		output << "0" << endl;
		output.close();
		packsFile.close();
		return;
	}

	string line;
	getline(packsFile, line);
	last_id = stoi(line);

	while (!packsFile.eof() && !isEmpty(packsFile)) {
		Packet packet;
		getline(packsFile, line);
		packet.setId(line); // adding the ID --------------------------------------------
		getline(packsFile, line);
		size_t found_1 = line.find_first_of('-');
		vector<string> sites;
		if (found_1 == string::npos) { // adding the PLACES
			cleanSpaces(line);
			sites.push_back(line);
		}
		else {
			string first_position = line.substr(0, found_1 - 1); // the string for places is divided by 2 different characters, '-' and ',', I want to separate the '-' so I can parse with my function only the ','
			line.erase(0, found_1 + 1);
			sites.push_back(first_position);
			cleanSpaces(line);
			found_1 = line.find_first_of(',');
			parseText(line, found_1, sites, ','); // string &var, size_t found_1, vector<string> &arr, char c
		}
		packet.setSites(sites);

		vector<string> date; // adding the BEGIN_DATE --------------------------------------------
		getline(packsFile, line);
		found_1 = line.find_first_of('/');
		parseText(line, found_1, date, '/');
		Date begin = Date(date[2], date[1], date[0]);
		packet.setBeginDate(begin);

		getline(packsFile, line); // adding the END_DATE --------------------------------------------
		found_1 = line.find_first_of('/');
		parseText(line, found_1, date, '/');
		Date end = Date(date[5], date[4], date[3]);
		packet.setEndDate(end);

		getline(packsFile, line); // adding the rest --------------------------------------------
		packet.setPricePerPerson(line);
		getline(packsFile, line);
		packet.setMaxPersons(line);
		getline(packsFile, line);
		packet.setBoughtTickets(line);

		packets.push_back(packet);
		getline(packsFile, line);
	}
	packsFile.close();
}

Agency::Agency() {}

Agency::Agency(vector<Client> & clients, vector<Packet> & packets, string & last_id) {
	ifstream agencyFile;
	string fileName = "agency.txt";
	agencyFile.open(fileName);

	if (!agencyFile) {
		cerr << "\tUnable to open file " << fileName << endl;
		exit(1);
	}

	string line;
	vector<string> text;
	while (!agencyFile.eof()) {
		getline(agencyFile, line);
		text.push_back(line);
	}

	// -parsing my address removing and separating each value by the '/' symbol so I can
	// -fill it in a vector and THEN initialize Address struct
	string address_str = text[3];
	size_t found_1 = address_str.find_first_of('/');
	vector<string> address_arr;
	parseText(address_str, found_1, address_arr, '/');

	Address agency_address = Address(address_arr[0], address_arr[1], address_arr[2], address_arr[3], address_arr[4]);

	name = text[0];
	VATnumber = text[1];
	URL = text[2];
	this->address = agency_address;
	clients_file = text[4];
	packs_file = text[5];
	fillClients(clients_file);
	fillPacks(packs_file, last_id);
	agencyFile.close();
}

// metodos GET
vector<Packet> Agency::cleanOrganizedPackets() const{
	Packet temp;
	vector<Packet> new_packets = packets;
	// adding replicates BoughtTickets + removing replicates
	for(int i = new_packets.size()-1; i > 0; i--)
		for(int j = i-1; j>=0; j--)
			if(new_packets[j].getSites().at(0) == new_packets[i].getSites().at(0)){
				new_packets[j].setBoughtTickets(to_string(stoi(new_packets[i].getBoughtTickets()) + stoi(new_packets[j].getBoughtTickets())));
				new_packets.erase(new_packets.begin() + i);
				break;
			}

	// sorting algorithm
	for(int i = 0; i<new_packets.size(); i++)
		for(int j = i+1; j<new_packets.size(); j++)
			if(stoi(new_packets[j].getBoughtTickets()) > stoi(new_packets[i].getBoughtTickets()))
				std::swap(new_packets[i], new_packets[j]);

	return new_packets;
}

vector<Packet> Agency::showTravelPacksByDatesAndPlace(string place, string date1, string date2) const {
	vector<Packet> tps_by_place_and_date = showTravelPacksByDates(date1, date2);
	return showTravelPacksByPlace(tps_by_place_and_date, place);
}

vector<Packet> Agency::showTravelPacksByDates(string date1, string date2) const {
	vector<Packet> tps_by_date;
	vector<string> date_1_arr;
	vector<string> date_2_arr;

	string date_1_temp = date1;
	string date_2_temp = date2;

	size_t found_1 = date1.find_first_of('/');
	parseText(date1, found_1, date_1_arr, '/');
	found_1 = date2.find_first_of('/');
	parseText(date2, found_1, date_2_arr, '/');

	date1 = date_1_temp;
	date2 = date_2_temp;

	for (int i = 0; i < packets.size(); i++) {
		if (stoi(packets[i].getId()) < 0) continue;
		if (date1 <= dateToStr(packets[i].getBeginDate()) && date2 >= dateToStr(packets[i].getEndDate()))
			tps_by_date.push_back(packets[i]);
	}

	return tps_by_date;
}

vector<Packet> Agency::showTravelPacksByPlace(vector<Packet> tp, string place) const {
	vector<Packet> tps_by_place;

	for (int i = 0; i < tp.size(); i++)
		if (tp[i].getSites().at(0) == place) tps_by_place.push_back(tp[i]);

	return tps_by_place;
}

string Agency::getName() const {
	return name;
}

string Agency::getVATnumber() const {
	return VATnumber;
}

Address Agency::getAddress() const {
	return address;
}

string Agency::getURL() const {
	return URL;
}

vector<Client> Agency::getClients() const {
	return clients;
}

vector<Packet> Agency::getPackets() const {
	return packets;
}

string Agency::totalTravelPacksBought() const{
	int total = 0;
	for(int i=0; i<packets.size(); i++)
		if(stoi(packets[i].getBoughtTickets()) > 0) total++;
	return to_string(total);
}

string Agency::totalIncome() const{
	int sum = 0;
	for(int i=0; i<packets.size(); i++)
		sum += stoi(packets[i].getBoughtTickets()) * stoi(packets[i].getPricePerPerson());
	return to_string(sum);
}

// SET Methods
void Agency::showRecommendations(){
	vector<Packet> new_packets = cleanOrganizedPackets();
	vector<string> output;
	cout << endl;
	for(int i=0; i<clients.size(); i++){
		for(int j=0; j<new_packets.size(); j++){
			bool found = false;
			int id;
			for(int z=0; z<clients[i].getPacketList().size(); z++){
				if(new_packets[j].getId() == clients[i].getPacketList().at(z))
					found = true;
				if(found) break;
			}
			if(!found){
				string name = clients[i].getName();
				transform(name.begin(), name.end(), name.begin(), ::toupper);
				output.push_back("\tPara: " + name + "\t\trecomendamos: " + new_packets[j].getSites().at(0));
				break;
			}
		}
	}
	for(int i=0; i<output.size(); i++) cout << output[i] << endl;
}

void Agency::showTopRatedLocations(){
	vector<Packet> new_packets = cleanOrganizedPackets();
	cout << endl;
	cout << "\t,-----------------------," << endl;
	cout << "\t| Locais mais visitados |" << endl;
	cout << "\t'-----------------------'" << endl << endl;

	cout << std::left << setw(31) << "\tLocal" << "Visitas" << endl;
	cout << "\t-------------------------------------" << endl;
	for(int i=0; i<new_packets.size(); i++)
		cout << "\t" << setw(30) << new_packets[i].getSites().at(0)  << new_packets[i].getBoughtTickets() << endl;
	
	cout << endl << "\tPresse ENTER para recuar..." << endl;
	string line;
	getline(cin, line);
}

void Agency::showTravelPack(string id) {
	int index;
	bool found = false;
	do {
		for (int i = 0; i < packets.size(); i++) {
			if (packets[i].getId() == id) {
				found = true;
				index = i;
				break;
			}
		}
		if (!found) {
			cout << "\tNao existe nenhum pack com este ID, escolha outro: ";
			getline(cin, id);
		}
	} while (!found);

	if (found) {
		cout << endl << "\t----------------------------------------------------------------------" << endl;
		cout << "\tID: " << packets[index].getId() << endl;
		cout << "\tSitios: " << placesToStr(packets[index].getSites()) << endl;
		cout << "\tData inicial: " << packets[index].getBeginDate().getYear() << "/" << packets[index].getBeginDate().getMonth() << "/" << packets[index].getBeginDate().getDay() << endl;
		cout << "\tData final: " << packets[index].getEndDate().getYear() << "/" << packets[index].getEndDate().getMonth() << "/" << packets[index].getEndDate().getDay() << endl;
		cout << "\tPreco por pessoa: " << packets[index].getPricePerPerson() << endl;
		cout << "\tBilhetes iniciais: " << packets[index].getMaxPersons() << endl;
		cout << "\tBilhetes comprados: " << packets[index].getBoughtTickets();
		cout << endl << "\t----------------------------------------------------------------------" << endl << endl;
	}
	cout << "\tPresse ENTER para recuar...";
	string line;
	getline(cin, line);
}

void Agency::showAllClients() {
	if (clients.size() == 0) return;
	cout << endl << std::left << std::setfill(' ') << std::setw(20) << "\tnome" << std::setw(15) << "NIF" << std::setw(12) << "a. fam." << std::setw(62) << "morada" << "pacotes" << endl;
	cout << "\t-------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < clients.size(); i++) {
		cout << "\t";
		cout << std::setw(19) << clients[i].getName();
		cout << std::setw(15) << clients[i].getVATnumber();
		cout << std::setw(12) << clients[i].getFamilySize();
		string address = clients[i].getAddress().getStreet() + " / " + clients[i].getAddress().getDoorNumber() + " / " + clients[i].getAddress().getFloor() + " / " + clients[i].getAddress().getPostalCode() + " / " + clients[i].getAddress().getLocation();
		cout << std::setw(62) << address;
		string id_packs = "";
		for (int j = 0; j < clients[i].getPacketList().size() - 1; j++) {
			id_packs += clients[i].getPacketList().at(j) + " ; ";
		}
		id_packs += clients[i].getPacketList().at(clients[i].getPacketList().size() - 1);
		cout << id_packs << endl;
	}
	cout << "\t-------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "\tPresse ENTER para recuar...";
	string line;
	getline(cin, line);
}

void Agency::showClient(string nif) {
	int index;
	bool found = false;
	do {
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i].getVATnumber() == nif) {
				found = true;
				index = i;
				break;
			}
		}
		if (!found) {
			cout << "\tNao existe ninguem com este NIF, escolha outro: ";
			getline(cin, nif);
		}
	} while (!found);

	if (found) {
		cout << endl << "\t----------------------------------------------------------------------" << endl;
		cout << "\tNome: " << clients[index].getName() << endl;
		cout << "\tNIF: " << clients[index].getVATnumber() << endl;
		cout << "\tAgregado familiar: " << clients[index].getFamilySize() << endl;
		cout << "\tMorada: " << clients[index].getAddress().getStreet() << " / " << clients[index].getAddress().getDoorNumber() << " / " << clients[index].getAddress().getFloor() << " / " << clients[index].getAddress().getPostalCode() << " / " << clients[index].getAddress().getLocation() << endl;
		cout << "\tPacote(s): " << clients[index].getPacketList().at(0);
		for (int i = 1; i < clients[index].getPacketList().size(); i++) {
			cout << " ; " << clients[index].getPacketList().at(i);
		}
		cout << endl << "\t----------------------------------------------------------------------" << endl << endl;
	}
	cout << "\tPresse ENTER para recuar...";
	string line;
	getline(cin, line);
}

void Agency::removeTravelPack(string id) {
	int index;
	bool found = false;
	if(id == ":q") return;
	do {
		for (int i = 0; i < packets.size(); i++)
			if (packets[i].getId() == id) {
				index = i;
				found = true;
				break;
			}
		if (found) {
			packets.erase(packets.begin() + index);
			/*if(packets.size() == 0){
			  last_id = "0";
			}else{
			  last_id = packets[packets.size()-1].getId();
			}*/
			cout << "\tPack removido com sucesso." << endl;
		}
		else {
			cout << "\tNao existe nenhum pack com esse ID, escolha outro: ";
			getline(cin, id);
		}
	} while (!found);
	updatePacksFile();
}

void Agency::editTravelPack(string id) {
	int index;
	bool found = false;
	if(id == ":q") return;
	do {
		for (int i = 0; i < packets.size(); i++)
			if (packets[i].getId() == id) {
				index = i;
				found = true;
				break;
			}
		if (found) {
			cout << "\tPacote de viagem escolhido." << endl << endl;
			cout << "\t,-, -------------------------------- ,-," << endl;
			cout << "\t|/    (escreva ':q' para cancelar)   |/" << endl;
			cout << "\to   -------------------------------- o" << endl << endl;
			cout << "\tQue deseja modificar? ";
		}
		else {
			cout << "\tNao existe nenhum pacote de viagem com esse ID, escolha outro: ";
			getline(cin, id);
		}
	} while (!found);

	string edit;
	string value;
	getline(cin, edit);

	

	if(edit == ":q") return;

	do {
		vector<string> places_arr;
		vector<string> date_arr;
		string text = "";
		if (edit == "id") {
			found = true;
			cout << "\tID antigo: " << packets[index].getId() << endl;
			cout << "\tEscolha um ID novo: ";
			getline(cin, value);
			packets[index].setId(value);
		}
		else if (edit == "local") {
			found = true;
			if (packets[index].getSites().size() == 1) {
				text += packets[index].getSites().at(0);
			}
			else {
				for (int j = 0; j < packets[index].getSites().size() - 1; j++) {
					if (j == 0)
						text += packets[index].getSites().at(0) + " - ";
					else
						text += packets[index].getSites().at(j) + ", ";
				}
				text += packets[index].getSites().at(packets[index].getSites().size() - 1);
			}
			cout << "\tLocal antigo: " << text << endl;
			cout << "\tEscolha um local novo: ";
			getline(cin, value);
			size_t found_1 = value.find_first_of('-');
			if (found_1 == string::npos) { // adding the PLACES
				cleanSpaces(value);
				places_arr.push_back(value);
			}
			else {
				string first_position = value.substr(0, found_1); // the string for places is divided by 2 different characters, '-' and ',', I want to separate the '-' so I can parse with my function only the ','
				value.erase(0, found_1 + 1);
				cleanSpaces(first_position);
				value += " ";
				places_arr.push_back(first_position);
				cleanSpaces(value);
				found_1 = value.find_first_of(',');
				parseText(value, found_1, places_arr, ','); // string &var, size_t found_1, vector<string> &arr, char c
			}
			packets[index].setSites(places_arr);
		}
		else if (edit == "data inicial") {
			found = true;
			cout << "\tData inicial antiga: " << packets[index].getBeginDate().getDay() << "/" << packets[index].getBeginDate().getMonth() << "/" << packets[index].getBeginDate().getYear() << endl;
			cout << "\tEscolha uma data inicial nova: ";
			getline(cin, value);
			size_t found_1 = value.find_first_of('/');
			parseText(value, found_1, date_arr, '/');
			Date begin_date = Date(date_arr[0], date_arr[1], date_arr[2]);
			packets[index].setBeginDate(begin_date);
		}
		else if (edit == "data final") {
			found = true;
			cout << "\tData final antiga: " << packets[index].getEndDate().getDay() << "/" << packets[index].getEndDate().getMonth() << "/" << packets[index].getEndDate().getYear() << endl;
			cout << "\tEscolha uma data final nova: ";
			getline(cin, value);
			size_t found_1 = value.find_first_of('/');
			parseText(value, found_1, date_arr, '/');
			Date end_date = Date(date_arr[0], date_arr[1], date_arr[2]);
			packets[index].setEndDate(end_date);
		}
		else if (edit == "valor") {
			found = true;
			cout << "\tValor antigo: " << packets[index].getPricePerPerson() << endl;
			cout << "\tEscolha um valor novo: ";
			getline(cin, value);
			packets[index].setPricePerPerson(value);
		}
		else if (edit == "tickets") {
			found = true;
			cout << "\tTicket(s) antigo(s): " << packets[index].getMaxPersons() << endl;
			cout << "\tEscolha um valor novo para tickets: ";
			getline(cin, value);
			packets[index].setMaxPersons(value);
		}
		else if (edit == "comprados") {
			found = true;
			cout << "\tTicket(s) comprado(s) antigo(s): " << packets[index].getBoughtTickets() << endl;
			cout << "\tEscolha um valor novo para tickets comprados: ";
			getline(cin, value);
			packets[index].setBoughtTickets(value);
		}
		else {
			found = false;
			cout << "\tCertifique-se que escreva: 'id', 'local', 'data inicial', 'data final', 'valor', 'valor', 'tickets', 'comprados' : ";
			getline(cin, edit);
		}
	} while (!found);
	updatePacksFile();
}

void Agency::createTravelPack() {
	ofstream packsFile;
	string line;
	int offset = -1;
	vector<string> text;
	vector<string> places;
	vector<string> begin_date_arr;
	vector<string> end_date_arr;

	packsFile.open(packs_file, std::ios_base::app);
	if (packets.size() != 0) {
		text.push_back("::::::::::");
		offset = 0;
	}
	cout << "\t,-, --------------------------------------------------------------------- ,-," << endl;
	cout << "\t|/    Indique as informacoes seguintes:    (escreva ':q' para cancelar)   |/" << endl;
	cout << "\to   --------------------------------------------------------------------- o" << endl << endl;
	cout << "\tID do pack: ";
	getline(cin, line);
	if(line == ":q") return;
	text.push_back(line);
	cout << "\tLocal/locais turistico(s): ";
	getline(cin, line);
	if(line == ":q") return;
	text.push_back(line);
	cout << "\tData de inicio da viagem: ";
	getline(cin, line);
	if(line == ":q") return;
	text.push_back(line);
	cout << "\tData de fim da viagem: ";
	getline(cin, line);
	if(line == ":q") return;
	text.push_back(line);
	cout << "\tPreco por pessoa: ";
	getline(cin, line);
	if(line == ":q") return;
	text.push_back(line);
	cout << "\tBilhetes disponiveis: ";
	getline(cin, line);
	if(line == ":q") return;
	text.push_back(line);
	cout << "\tBilhetes comprados: ";
	getline(cin, line);
	if(line == ":q") return;
	text.push_back(line);

	string places_str = text[2 + offset];
	string begin_date_str = text[3 + offset];
	string end_date_str = text[4 + offset];

	size_t found_1 = text[2 + offset].find_first_of('-');
	if (found_1 == string::npos) { // adding the PLACES
		cleanSpaces(text[2 + offset]);
		places.push_back(text[2 + offset]);
	}
	else {
		string first_position = text[2 + offset].substr(0, found_1 - 1); // the string for places is divided by 2 different characters, '-' and ',', I want to separate the '-' so I can parse with my function only the ','
		cout << first_position << endl;
		text[2 + offset].erase(0, found_1 + 1);
		places.push_back(first_position);
		cleanSpaces(text[2 + offset]);
		found_1 = text[2 + offset].find_first_of(',');
		parseText(text[2 + offset], found_1, places, ','); // string &var, size_t found_1, vector<string> &arr, char c

	}
	found_1 = text[3 + offset].find_first_of('/');
	parseText(text[3 + offset], found_1, begin_date_arr, '/');
	found_1 = text[4 + offset].find_first_of('/');
	parseText(text[4 + offset], found_1, end_date_arr, '/');

	Date begin_date = Date(begin_date_arr[0], begin_date_arr[1], begin_date_arr[2]);
	Date end_date = Date(end_date_arr[0], end_date_arr[1], end_date_arr[2]);

	Packet tp = Packet(text[1 + offset], places, begin_date, end_date, text[5 + offset], text[6 + offset], text[7 + offset]);
	packets.push_back(tp);

	text[2 + offset] = places_str;
	text[3 + offset] = begin_date_str;
	text[4 + offset] = end_date_str;

	fstream packsfile_2(packs_file, std::ios::in | std::ios::out);
	packsfile_2 << packets[packets.size() - 1].getId();
	packsfile_2.close();

	for (int i = 0; i < text.size(); i++) {
		packsFile << text[i] << endl;
	}
	packsFile.close();
}

void Agency::removeClient(string nif) {
	int id;
	bool found = false;
	do {
		for (int i = 0; i < clients.size(); i++)
			if (clients[i].getVATnumber() == nif) {
				id = i;
				found = true;
				break;
			}
		if (found) {
			clients.erase(clients.begin() + id);
			cout << "\tCliente removido com sucesso." << endl;
		}
		else {
			cout << "\tNao existe nenhum cliente com esse NIF, escolha outro: ";
			getline(cin, nif);
		}
	} while (!found);
	updateClientsFile();
}

void Agency::editClient(string nif) {
	int id;
	bool found = false;
	do {
		for (int i = 0; i < clients.size(); i++)
			if (clients[i].getVATnumber() == nif) {
				id = i;
				found = true;
				break;
			}
		if (found) {
			cout << "\tCliente escolhido." << endl << endl;
			cout << "\t,-, --------------------------------- ,-," << endl;
			cout << "\t|/     (escreva ':q' para cancelar)   |/" << endl;
			cout << "\to   --------------------------------- o" << endl << endl;
			cout << "\tCertifique-se que escreva 'rua / porta / andar / codigo-postal / localidade'" << endl;
			cout << "\tQue deseja modificar? ";
		}
		else {
			cout << "\tNao existe nenhum cliente com esse NIF, escolha outro: ";
			getline(cin, nif);
		}
	} while (!found);

	string edit;
	string value;
	getline(cin, edit);
	if(edit == ":q") return;

	do {
		if (edit == "nome") {
			found = true;
			cout << "\tNome antigo: " << clients[id].getName() << endl;
			cout << "\tEscolha um nome novo: ";
			getline(cin, value);
			clients[id].setName(value);
		}
		else if (edit == "nif") {
			found = true;
			cout << "\tNif antigo: " << clients[id].getVATnumber() << endl;
			cout << "\tEscolha um nif novo: ";
			getline(cin, value);
			clients[id].setVATnumber(value);
		}
		else if (edit == "agregado") {
			found = true;
			cout << "\tAgregado familiar antigo: " << clients[id].getFamilySize() << endl;
			cout << "\tEscolha um agregado familiar novo: ";
			getline(cin, value);
			clients[id].setFamilySize(value);
		}
		else if (edit == "morada") {
			found = true;
			cout << "\tMorada antiga: " << clients[id].getAddress().getStreet() << " / " << clients[id].getAddress().getDoorNumber() << " / " << clients[id].getAddress().getFloor() << " / " << clients[id].getAddress().getPostalCode() << " / " << clients[id].getAddress().getLocation() << endl;
			cout << "\tEscolha uma morada nova: ";
			vector<string> address_arr;
			bool accepted = false;
			do {
				getline(cin, value);
				size_t found_1 = value.find_first_of('/');
				parseText(value, found_1, address_arr, '/');
				if (address_arr.size() == 5) {
					accepted = true;
				}
				else {
					cout << "\tCertifique-se que escreva 'rua / porta / andar / codigo-postal / localidade ': ";
				}
			} while (!accepted);
			Address address = Address(address_arr[0], address_arr[1], address_arr[2], address_arr[3], address_arr[4]);
			clients[id].setAddress(address);
		}
		else if (edit == "pacotes") {
			found = true;
			cout << "\tPacote(s) antigo(s): " << packToStr(clients[id].getPacketList()) << endl;
			cout << "\tEscolha um pacote novo / uns pacotes novos: ";
			vector<string> packs_arr;
			bool accepted = false;
			do {
				getline(cin, value);
				size_t found_1 = value.find_first_of(';');
				parseText(value, found_1, packs_arr, ';');
				if (packs_arr.size() >= 1) {
					accepted = true;
				}
				else {
					cout << "\tCertifique-se que escreva o ID do pacote e se tiver mais que um, separe-os por ';' : ";
				}
			} while (!accepted);
			clients[id].setPacketList(packs_arr);
		}
		else {
			found = false;
			cout << "\tCertifique-se que escreva: 'nome', 'nif', 'agregado', 'morada', 'pacotes': ";
			getline(cin, edit);
		}
	} while (!found);
	updateClientsFile();
}

void Agency::createClient() {
	ofstream clientsFile;
	string name, nif, family, address_str, packs_str;
	int offset = -1;
	vector<string> text;
	vector<string> client_address_arr;
	vector<string> packs_arr;
	Address client_address;

	if (clients.size() != 0) {
		text.push_back("\n::::::::::");
		offset = 0;
	}
	cout << "\t,-, --------------------------------------------------------------------- ,-," << endl;
	cout << "\t|/    Indique as informacoes seguintes:    (escreva ':q' para cancelar)   |/" << endl;
	cout << "\to   --------------------------------------------------------------------- o" << endl << endl;
	cout << "\tNome do cliente: ";
	getline(cin, name);
	if(name == ":q") return;
	text.push_back(name);
	cout << "\tNIF do cliente: ";
	getline(cin, nif);
	if(nif == ":q") return;
	text.push_back(nif);
	cout << "\tAgregado familiar: ";
	getline(cin, family);
	if(family == ":q") return;
	text.push_back(family);
	cout << "\tMorada: ";
	getline(cin, address_str);
	if(address_str == ":q") return;
	text.push_back(address_str);
	cout << "\tPacote(s) turistico(s): ";
	getline(cin, packs_str);
	if(packs_str == ":q") return;
	text.push_back(packs_str);

	string places_str = text[5 + offset];

	size_t found_1 = text[5 + offset].find_first_of(';');
	parseText(text[5 + offset], found_1, packs_arr, ';');
	while (true) {
		found_1 = text[4 + offset].find_first_of('/');
		parseText(text[4 + offset], found_1, client_address_arr, '/');

		if (client_address_arr.size() == 5) {
			client_address = Address(client_address_arr[0], client_address_arr[1], client_address_arr[2], client_address_arr[3], client_address_arr[4]);
			break;
		}
		else {
			cout << "\tMorada invalida! Escreva a morada no seguinte formato [rua] / [porta] / [andar] / [codigo postal] / [cidade]: ";
			getline(cin, address_str);
			if(address_str == ":q") return;
			text[4 + offset] = address_str;
			client_address_arr.clear();
		}
	} 
	Client client = Client(text[1 + offset], text[2 + offset], text[3 + offset], client_address, packs_arr);
	clients.push_back(client);
	
	clientsFile.open(clients_file, std::ios_base::app);
	for (int i = 0; i < text.size(); i++)
		clientsFile << text[i] << endl;

	clientsFile.close();
	cout << "\tCliente adicionado com sucesso!\n";
	
}

void Agency::setName(string name) {
	this->name = name;
}

void Agency::setVATnumber(string VATnumber) {
	this->VATnumber = VATnumber;
}

void Agency::setAddress(Address address) {
	this->address = address;
}

void Agency::setURL(string URL) {
	this->URL = URL;
}

void Agency::setClients(vector<Client> & clients) {
	this->clients = clients;
}

void Agency::setPackets(vector<Packet> & packets) {
	this->packets = packets;
}

void Agency::buyTravelPack(string nif) {
	vector<Packet> tps_arr;
	vector<string> id_packs_arr;
	int index;
	bool found = false;
	do {
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i].getVATnumber() == nif) {
				found = true;
				index = i;
				break;
			}
		}
		if (!found) {
			cout << "Nao existe ninguem com este NIF, escolha outro: ";
			getline(cin, nif);
		}
	} while (!found);

	for (int i = 0; i < clients[index].getPacketList().size(); i++)
		id_packs_arr.push_back(clients[index].getPacketList().at(i));


	bool diff = true;
	for (int i = 0; i < packets.size(); i++) {
		diff = true;
		if (stoi(packets[i].getId()) < 0) continue;
		for (int j = 0; j < id_packs_arr.size(); j++)
			if (abs(stoi(packets[i].getId())) == stoi(id_packs_arr[j])) {
				diff = false;
			}
		if (diff) tps_arr.push_back(packets[i]);
	}

	showTps(tps_arr);
	if (!tps_arr.size()) {
		cout << "Sem packs para comprar, presse ENTER para recuar..." << endl;
		string l;
		getline(cin, l);
		return;
	}

	cout << endl << "Escolha pack a comprar: ";
	string option;
	bool accepted = false;
	while (!accepted) {
		getline(cin, option);
		if (option == "0") break;
		for (int i = 0; i < tps_arr.size(); i++)
			if (option == tps_arr[i].getId()) {
				string agregated = clients[index].getFamilySize();
				if (stoi(tps_arr[i].getBoughtTickets()) + stoi(agregated) <= stoi(tps_arr[i].getMaxPersons())) {
					int index_1 = findTpByID(tps_arr[i].getId());
					packets[index_1].setBoughtTickets(to_string(stoi(tps_arr[i].getBoughtTickets()) + stoi(agregated)));
					if (packets[index_1].getBoughtTickets() == packets[index_1].getMaxPersons()) packets[index_1].setId("-" + packets[index_1].getId());
					vector<string> id_packs_temp = clients[index].getPacketList();
					id_packs_temp.push_back(packets[index_1].getId());
					clients[index].setPacketList(id_packs_temp);
					accepted = true;
					updatePacksFile();
					updateClientsFile();
				}
			}
		if (accepted) break;
		cout << accepted << endl;
		cout << "Escolha outra opcao: ";
	}
}

void Agency::updateClientsFile() {
	ofstream clientsFile;
	clientsFile.open(clients_file);

	for (int i = 0; i < clients.size(); i++) {
		clientsFile << clients[i].getName() << endl;
		clientsFile << clients[i].getVATnumber() << endl;
		clientsFile << clients[i].getFamilySize() << endl;
		clientsFile << clients[i].getAddress().getStreet() << " / " << clients[i].getAddress().getDoorNumber() << " / " << clients[i].getAddress().getFloor() << " / " << clients[i].getAddress().getPostalCode() << " / " << clients[i].getAddress().getLocation() << endl;
		for (int j = 0; j < clients[i].getPacketList().size(); j++) {
			if (j == clients[i].getPacketList().size() - 1) {
				clientsFile << clients[i].getPacketList().at(j) << endl;
			}
			else {
				clientsFile << clients[i].getPacketList().at(j) << " ; ";
			}
		}
		if (i != clients.size() - 1) clientsFile << "::::::::::" << endl;
	}
	clientsFile.close();
}

void Agency::updatePacksFile() {
	ofstream packsFile;
	packsFile.open(packs_file);

	packsFile << packets[packets.size() - 1].getId() << endl;
	string text = "";
	for (int i = 0; i < packets.size(); i++) {
		text = "";
		packsFile << packets[i].getId() << endl;
		if (packets[i].getSites().size() == 1) {
			text += packets[i].getSites().at(0);
		}
		else {
			for (int j = 0; j < packets[i].getSites().size() - 1; j++) {
				if (j == 0)
					text += packets[i].getSites().at(0) + " - ";
				else
					text += packets[i].getSites().at(j) + ", ";
			}
			text += packets[i].getSites().at(packets[i].getSites().size() - 1);
		}
		packsFile << text << endl;
		packsFile << packets[i].getBeginDate().getYear() << "/" << packets[i].getBeginDate().getMonth() << "/" << packets[i].getBeginDate().getDay() << endl;
		packsFile << packets[i].getEndDate().getYear() << "/" << packets[i].getEndDate().getMonth() << "/" << packets[i].getEndDate().getDay() << endl;
		packsFile << packets[i].getPricePerPerson() << endl;
		packsFile << packets[i].getMaxPersons() << endl;
		packsFile << packets[i].getBoughtTickets() << endl;
		if (i != packets.size() - 1) packsFile << "::::::::::" << endl;
	}
	packsFile.close();
}