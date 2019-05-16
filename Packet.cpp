#include "Packet.h"

Packet::Packet() {}

Packet::Packet(string id, vector<string> sites, Date begin, Date end, string pricePerPerson, string maxPersons, string boughtTickets) {
	this->id = id;
	this->sites = sites;
	this->begin = begin;
	this->end = end;
	this->pricePerPerson = pricePerPerson;
	this->maxPersons = maxPersons;
	this->boughtTickets = boughtTickets;
}

Packet::Packet(vector<string> sites, Date begin, Date end, string pricePerPerson, string maxPersons) {
	this->sites = sites;
	this->begin = begin;
	this->end = end;
	this->pricePerPerson = pricePerPerson;
	this->maxPersons = maxPersons;
}
// metodos GET

string Packet::getId() const {
	return id;
}

vector<string> Packet::getSites() const {
	return sites;
}

Date Packet::getBeginDate() const {
	return begin;
}

Date Packet::getEndDate() const {
	return end;
}

string Packet::getPricePerPerson() const {
	return pricePerPerson;
}

string Packet::getMaxPersons() const {
	return maxPersons;
}

string Packet::getBoughtTickets() const {
	return boughtTickets;
}

// metodos SET

void Packet::setId(string id) {
	this->id = id;
}

void Packet::setSites(vector<string> sites) {
	this->sites = sites;
}

void Packet::setBeginDate(Date begin) {
	this->begin = begin;
}

void Packet::setEndDate(Date end) {
	this->end = end;
}

void Packet::setPricePerPerson(string pricePerPerson) {
	this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPersons(string maxPersons) {
	this->maxPersons = maxPersons;
}

void Packet::setBoughtTickets(string boughtTickets) {
	this->boughtTickets = boughtTickets;
}

