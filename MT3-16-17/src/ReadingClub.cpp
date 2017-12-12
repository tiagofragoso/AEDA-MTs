/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {

	vector<BookCatalogItem> bci;

	for (auto &b : books){
		auto cbook = BookCatalogItem(b->getTitle(), b->getAuthor(), b->getYear());
		cbook.addItems(b);
		if (bci.empty()) bci.push_back(cbook);
		else {
			bool found = false;
			for (auto &bcit: bci){
				if (cbook == bcit) {
					bcit.addItems(b);
					found = true;
					break;
				}
			}
			if (!found) bci.push_back(cbook);

		}
	}

	for (auto const & b: bci) catalogItems.insert(b);

}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	BSTItrIn<BookCatalogItem> it(catalogItems);

	while(!it.isAtEnd()){
		if (it.retrieve() == BookCatalogItem(book->getTitle(), book->getAuthor(), 0)) {
			auto items = it.retrieve().getItems();
			for_each(items.begin(), items.end(), [&temp, &book](Book* b){ if (b->getReader() == nullptr) temp.push_back(book); });
		}
		it.advance();
	}

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {

	auto avBooks = this->getAvailableItems(book);

	if (!avBooks.empty()){
		reader->addReading(book->getTitle(), book->getAuthor());
		avBooks[0]->setReader(reader);
		return true;
	}

	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {

	if (userRecords.empty() || userRecords.find(user) == userRecords.end()) userRecords.insert(UserRecord(user));

}

void ReadingClub::changeUserEMail(User* user, string newEMail) {

	user->setEMail(newEMail);

}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {

	for_each(candidates.begin(), candidates.end(), [this, &min](const User &c){ if (c.numReadings() >= min) this->readerCandidates.push(c); });

}

int ReadingClub::awardReaderChampion(User& champion) {
	auto rdCnd = readerCandidates;
	if (!rdCnd.empty()){
		if (rdCnd.size() == 1){
			champion = rdCnd.top();
			return readerCandidates.size();
		} else {
			auto c1 = rdCnd.top();
			rdCnd.pop();
			if (c1.numReadings() != rdCnd.top().numReadings()){
				champion = c1;
				return readerCandidates.size();
			}
		}
	}

	return 0;
}
























