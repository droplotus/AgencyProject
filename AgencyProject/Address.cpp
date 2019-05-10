#include "Address.h"


Address::Address(){
}

Address::Address(string STREET, string DOORNUMBER, string FLOOR, string POSTALCODE, string LOCATION){
  street = STREET;
  doorNumber = DOORNUMBER;
  floor = FLOOR;
  postalCode = POSTALCODE;
  location = LOCATION;
}

// metodos GET


string Address::getStreet() const{
  return street;
}

string Address::getDoorNumber() const{
  return doorNumber;
}

string Address::getFloor() const{
  return floor;
}

string Address::getPostalCode() const{
  return postalCode;
}

string Address::getLocation() const{
  return location;
}

// metodos SET

void Address::setStreet(string street){
  this->street = street;
}

void Address::setDoorNumber(string doorNumber){
  this->doorNumber = doorNumber;
}

void Address::setFloor(string floor){
  this->floor = floor;
}

void Address::setPostalCode(string postalCode){
  this->postalCode = postalCode;
}

void Address::setLocation(string location){
  this->location = location;
}

