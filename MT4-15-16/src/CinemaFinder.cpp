/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;

    for_each(films.begin(), films.end(), [&actorName, &res](const FilmPtr &f){
        auto actors = f.film->getActors();
        if (!actors.empty())
        if (find(actors.begin(), actors.end(), actorName) != actors.end()) res.push_back(f.film->getTitle());
    });

	return res;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {

	for (auto it = begin(films); it != end(films); it++){
        if (it->film->getTitle() == filmTitle) {
            auto f = it->film;
            films.erase(it);
            f->addActor(actorName);
            addFilm(f);
            return;
        }
    }
    Film * f = new Film(filmTitle);
    f->addActor(actorName);
    addFilm(f);
}


//c1
string CinemaFinder::nearestCinema(string service1) const {
	string cName="";

	auto lst = cinemas;

    while (!lst.empty()){
        auto sv = lst.top().getServices();
        if (find(sv.begin(), sv.end(), service1) != sv.end()) return lst.top().getName();
        lst.pop();
    }

	return cName;
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {

	if (cinemas.empty()) throw CinemaNotFound();
    if (cinemas.top().getDistance() >= maxDistance) throw CinemaNotFound();

    auto cinema = cinemas.top();
    cinema.addService(service1);
    cinemas.pop();
    cinemas.push(cinema);

}
