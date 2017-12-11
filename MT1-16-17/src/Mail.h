/*
 * Mail.h
 */

#ifndef SRC_MAIL_H_
#define SRC_MAIL_H_
#include <vector>
#include <string>
using namespace std;


class Mail {
	string sender;
	string receiver;
	string zipCode;
public:
	Mail(string send, string rec, string zcode);
	virtual ~Mail();
    virtual unsigned int getPrice() const = 0;
	string getZipCode() const;
};


class RegularMail: public Mail {
	unsigned int weight;
public:
	RegularMail(string send, string rec, string code, unsigned int w);
    unsigned int getPrice () const;
};


class GreenMail: public Mail {
	string type;  // "envelope", "bag", "box"
public:
	GreenMail(string send, string rec, string code, string t);
    unsigned int getPrice () const;
};

template<class T>
unsigned int numberDifferent (const vector<T> & v1){

vector <T> temp;

	for (int i = 0; i < v1.size(); i++) {
		bool found = false;
		if (temp.size() > 0){

			for (int j = 0; j < temp.size(); j++){
				if (v1.at(i) == temp.at(j)) {
					found = true;
					break;
				}
			}

		}
		if (!found) {
			temp.push_back(v1.at(i));
		}
	}

	return (unsigned int)temp.size();

}



#endif /* SRC_MAIL_H_ */
