#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "defs.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"

using namespace std;

class Agency{
 private:
  string name; // name of the  agency
  string VATnumber; // VAT number of the agency
  Address address = Address(); // address of the agency
  string URL; // URL of the agency Web site
  string clients_file;
  string packs_file;
  vector<Client> clients; // vector to store the existing clients
  vector<Packet> packets; // vector to store the existing packets

 public:
  Agency();
  Agency(string fileName, vector<Client> &clients, vector<Packet> &packets, string &last_id);

  // methods GET
  int findTpByID(string id) const;
  string getName() const;
  string getVATnumber() const;
  Address getAddress() const;
  string getURL() const;
  vector<Client> getClients() const;
  vector<Packet> getPackets() const;
  vector<Packet> showTravelPacksByPlace(vector<Packet> tp, string place) const;
  vector<Packet> showTravelPacksByDates(string date1, string date2) const;
  vector<Packet> showTravelPacksByDatesAndPlace(string place, string date1, string date2) const;
  string dateToStr(Date date) const;

  // methods calculations
  void showTravelPacksFromAllClients();
  void showTravelPacksFromClient(string nif);
  void showTravelPack(string id);
  void showAllClients();
  void showClient(string nif);
  void removeTravelPack(string id);
  void editTravelPack(string id);
  void createTravelPack();
  void removeClient(string nif);
  void editClient(string nif);
  void createClient();
  void showTps(vector<Packet> tps_arr);
  void fillPacks(string fileName, string &last_id);
  void fillClients(string fileName);
  void updatePacksFile();
  void updateClientsFile();
  void buyTravelPack(string nif);

  // methods SET
  void setName(string name);
  void setVATnumber(string VATnumber);
  void setAddress(Address address);
  void setURL(string url);
  void setClients(vector<Client> & clients);
  void setPackets(vector<Packet> & packets);


};
