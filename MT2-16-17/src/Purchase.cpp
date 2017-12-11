/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {
	Article * newA = new Article(this->client, barCode);
	newA->setPresent(present);
	newA->setDeliverHome(deliverHome);
	return newA;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
	if (this->bags.back().size() < Purchase::BAG_SIZE) this->bags.back().push(article);
	else {
		stack<Article*> stack1;
		stack1.push(article);
		this->bags.push_back(stack1);
	}

}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;

	for (auto &b: this->bags){
		stack<Article*> temp;
		while (!b.empty()){
		if (b.top()->getPresent()) presents.push_back(b.top());
		else temp.push(b.top());
		b.pop();
		}
		while (!temp.empty()){
			b.push(temp.top());
			temp.pop();
		}
	}

	return presents;

}

