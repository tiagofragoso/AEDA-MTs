/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>
#include <iostream>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name) {
	vector <Mail *> mail;

for (int i = 0; i < postmen.size(); i++){
	if (postmen.at(i).getName() == name){
		mail = postmen.at(i).getMail();
		postmen.erase(postmen.begin() + i);
	}

}
	return mail;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
    vector<Mail *> sendToOtherPO;
    balance = 0;
    for(auto& mail: mailToSend){
        balance += mail->getPrice();
        if (mail->getZipCode() >= firstZipCode && mail->getZipCode() <= lastZipCode) addMailToDeliver(mail);
        else sendToOtherPO.push_back(mail);
    }
    mailToSend.clear();

    return sendToOtherPO;
}

Postman PostOffice::addMailToPostman(Mail *m, string name){

    for (auto &postman: postmen){
        if (name == postman.getName()){
            postman.addMail(m);
            return postman;
        }
    }
    throw NoPostmanException(name);

}


