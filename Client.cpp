#include "Client.h"

Client::Client(){}

Client::Client(string name, string VATnumber, string familySize, Address address, vector<string> id_packs){
  
  // REQUIRES IMPLEMENTATION 
}

  // GET methods

string Client::getName() const{
  return name;
}
  
string Client::getVATnumber() const{
  return VATnumber;
}

string Client::getFamilySize() const{
  return familySize;
}

Address Client::getAddress() const{
  return address;
}

vector<string> Client::getPacketList() const{
  return id_packs;
}
  
  // metodos SET
	  
void Client::setName(string name){
  this->name = name;
}

void Client::setVATnumber(string VATnumber){
  this->VATnumber = VATnumber;
}

void Client::setFamilySize(string familySize){
  this->familySize = familySize;
}

void Client::setAddress(Address address){
  this->address = address;
}

void Client::setPacketList(vector<string> id_packs){
  this-> id_packs = id_packs;
}