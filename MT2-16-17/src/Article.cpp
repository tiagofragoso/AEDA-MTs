/*
 * Article.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */


#include "Article.h"

using namespace std;

Article::Article(long cli, long bc) : client(cli), barCode(bc) {
	this->present = false;
	this->deliverHome = false;
	this->presentNumber = 0;
	this->arrivalNumber = 0;
};

long Article::getClient() const {
	return client;
}

long Article::getBarCode() const {
	return barCode;
}

bool Article::getPresent() const {
	return present;
}

void Article::setPresent(bool present) {
	this->present = present;
}

bool Article::getDeliverHome() const {
	return deliverHome;
}

void Article::setDeliverHome(bool deliverHome) {
	this->deliverHome = deliverHome;
}

int Article::getPresentNumber() const {
	return presentNumber;
}

void Article::setPresentNumber(int presentNumber) {
	this->presentNumber = presentNumber;
}

int Article::getArrivalNumber() const {
	return arrivalNumber;
}

void Article::setArrivalNumber(int arrivalNumber) {
	this->arrivalNumber = arrivalNumber;
}


bool sortFunctArt(Article *a1, Article *a2) {
	if (a1->getDeliverHome() && !a2->getDeliverHome()) return false;
	else if (!a1->getDeliverHome() && a2->getDeliverHome()) return true;
	else if (!a1->getDeliverHome() && !a2->getDeliverHome()){
		if (fabs(a1->getPresentNumber() - a2->getPresentNumber()) > 2){
			if (a1->getPresentNumber() < a2->getPresentNumber()) return true;
			else return false;
		} else return a1->getArrivalNumber() < a2->getArrivalNumber();
	} else return a1->getArrivalNumber() < a2->getArrivalNumber();
}
