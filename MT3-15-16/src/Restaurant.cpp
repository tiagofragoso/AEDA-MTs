/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include <iostream>
#include "Restaurant.h"
#include <algorithm>

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {

	for (int i = 0; i < n; i++){
		Dish * d = new Dish(collection, type);
		this->getCleanDishStack(collection, type).push(d);
	}

}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d;

	if (!this->getDirty().empty()){
		d = this->getDirty().front();
		this->dirty.pop();
		this->drying.push_back(d);
	}

	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {

	if (idx < tables.size()) {

		vector<Dish *> dty = tables.at(idx).clear();

		for (auto &d: dty){
			dirty.push(d);
		}
	}
}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {

	for (auto it = drying.begin(); it != drying.end(); it++){
		if ((*it)->getCollection() == collection && (*it)->getType() == type){
			this->getCleanDishStack(collection, type).push(*it);
			drying.erase(it);
			it--;
		}
	}

}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {
	vector<Dish *> d;
	if (idx < tables.size()) {
		Table * t = &tables.at(idx);
		if (!t->empty()) throw TableNotReadyException();
		else{
			if (getCleanDishStack(collection, Plate).size() < t->size()) throw NotEnoughDishesException();
			else{
				for (unsigned int i = 0; i < t->size(); i++){
					d.push_back(getCleanDishStack(collection, Plate).top());
					getCleanDishStack(collection, Plate).pop();
				}
				t->putOn(d);
			}
		}
	}

}

bool sortDishes(const Dish * d1, const Dish * d2){
	if (d1->getCollection() == d2->getCollection())
		return d1->getType() < d2->getType();
	else return d1->getCollection() < d2->getCollection();
}

/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped;
	vector<Dish*> temp;
	for (auto it = drying.begin(); it != drying.end(); it++){
		temp.push_back(*it);
		drying.erase(it);
		if (it != drying.begin()) it--;
	}

	sort(temp.begin(), temp.end(), sortDishes);

	for (auto const &d: temp){
		dry_grouped.push_back(d);
	}

	return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {

	int cntr = 0;
	string col;
	TypeOfDish tod;

	if (grouped_dishes.size() > 0){
		auto it = grouped_dishes.begin();
		col = (*it)->getCollection();
		tod = (*it)->getType();
		cntr++;
		getCleanDishStack(col, tod).push(*it);
		it++;
		for (; it != grouped_dishes.end(); it++){
			if (col != (*it)->getCollection() || tod != (*it)->getType()) {
				col = (*it)->getCollection();
				tod = (*it)->getType();
				cntr++;
			}
				getCleanDishStack(col, tod).push(*it);
		}
	}

	return cntr;
}

