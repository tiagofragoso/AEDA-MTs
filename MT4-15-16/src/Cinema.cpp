/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
		numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// TODO

bool Cinema::operator<(const Cinema & cr) const
{
	if (this->distance != cr.distance) return this->distance > cr.distance;
    return this->services.size() > cr.services.size();
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {

	BSTItrIn<FilmTime> it(timetable);
    FilmTime prev(0, nullptr, 0);
	while (!it.isAtEnd() && it.retrieve().getHour() <= h1){
		if (it.retrieve().getHour() == h1) return it.retrieve().getFilm();
        prev = it.retrieve();
		it.advance();
	}

    if (prev == FilmTime(0, nullptr, 0)) return nullptr;

    h1 = prev.getHour();
    return prev.getFilm();
	
}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
    bool canChangeToHour2 = true;
    BSTItrIn<FilmTime> it(timetable);
    FilmTime f(h1, nullptr, room1);
    while(!it.isAtEnd()){
        if (it.retrieve().getRoomID() == room1 && it.retrieve().getHour() == h1) f.setFilm(it.retrieve().getFilm());
        if (it.retrieve().getRoomID() == room1 && it.retrieve().getHour() == h2) canChangeToHour2 = false;
        it.advance();
    }

    if (f.getFilm() != nullptr && canChangeToHour2){
        timetable.remove(f);
        timetable.insert(FilmTime(h2, f.getFilm(), room1));
        return true;
    }

	return false;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
    unsigned roomToUse = 0;

    BSTItrIn<FilmTime> it(timetable);

    while (!it.isAtEnd()) {
        if (it.retrieve().getHour() == h1 && it.retrieve().getRoomID() > roomToUse)
            roomToUse = it.retrieve().getRoomID();
        it.advance();
    }

    if (roomToUse < this->numberOfRooms) {
        roomToUse++;
        timetable.insert(FilmTime(h1, f1, roomToUse));
        return roomToUse;
    }
    else return 0;

}






