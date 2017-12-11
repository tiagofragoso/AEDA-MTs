/*
 * Postman.cpp
 */
#include <iostream>
#include "Postman.h"

static unsigned int postmanId = 1;

Postman::Postman(): id(0) {}

Postman::Postman(string name): name(name), id(postmanId) {
	postmanId++;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator<(const Postman &p1) {
	vector<string> zip1, zip2;
	for (auto const & mail: this->getMail()){
		zip1.push_back(mail->getZipCode());
	}

	for (auto const & mail: p1.getMail()){
		zip2.push_back(mail->getZipCode());
	}

	return numberDifferent(zip1) < numberDifferent(zip2);

}



