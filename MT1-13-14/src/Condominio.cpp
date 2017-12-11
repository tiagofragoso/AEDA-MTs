/*
 * Condominio.cpp
 */

#include "Condominio.h"


Imovel::Imovel(int areaH, string prop, int id): areaHabitacao(areaH), proprietario(prop), ID(id)
{}

int Imovel::getID() const
{ return ID; }

void Imovel::setID(int id)
{ ID=id; }

int Imovel::getAreaHabitacao() const
{ return areaHabitacao; }

string Imovel::getProprietario() const
{ return proprietario; }

float Imovel::getPrecoCond() const {
    return (float) 50+0.2*this->areaHabitacao;
}


Apartamento::Apartamento(int areaH, int anda, string prop, int id): Imovel(areaH,prop,id), andar(anda)
{}

float Apartamento::mensalidade() const {
    return this->getPrecoCond() + (float)andar;
}

Vivenda::Vivenda(int areaH, int areaExt, bool pisc, string prop, int id):Imovel(areaH,prop,id), areaExterior(areaExt), piscina(pisc)
{}

float Vivenda::mensalidade() const {
    return this->getPrecoCond() + 0.1 * this->areaExterior + 10*piscina;
}

Urbanizacao::Urbanizacao(string nm, int id): nome(nm), ID(id)
{}

int Urbanizacao::seqId = 1;

void Urbanizacao::adicionaImovel(Imovel *im1) {
    im1->setID(this->imID);
    imoveis.push_back(im1);
    imID++;
}


vector<Imovel *> Urbanizacao::getImoveis() const
{ return imoveis; }

string Urbanizacao::getNome() const
{ return nome; }

int Urbanizacao::getID() const
{ return ID; }

vector<Imovel *> Urbanizacao::areaSuperiorA(int area1) const {
    vector<Imovel *> imvs;

    for (auto const & im: imoveis){
        if (im->getAreaTotal() > area1) imvs.push_back(im);
    }

    return imvs;
}

bool Urbanizacao::operator>(const Urbanizacao &urb) {

    if (this->imoveis.size() == 0 || urb.imoveis.size() == 0){ return true; }
    else return (this->getImoveis().size()/this->getUniqueProps()) < (urb.getImoveis().size()/urb.getUniqueProps());
}

int Urbanizacao::getUniqueProps() const {

    set<string> uniqueProps;

    for (auto const & im: imoveis) {

        if (uniqueProps.size() > 0){

            if (uniqueProps.find(im->getProprietario()) == uniqueProps.end()) uniqueProps.insert(im->getProprietario());

        } else uniqueProps.insert(im->getProprietario());
    }

    return uniqueProps.size();
}

Urbanizacao::Urbanizacao(string nm): nome(nm), ID(seqId) { seqId++; }

void Urbanizacao::resetID() { seqId = 1; }


void ECondominio::adicionaUrbanizacao(Urbanizacao urb1)
{ urbanizacoes.push_back(urb1); }

vector<Urbanizacao> ECondominio::getUrbanizacoes() const
{ return urbanizacoes; }

float ECondominio::mensalidadeDe(string nomeProp) const {
    float total = 0;
    for (auto const &urb: urbanizacoes){
        for (auto const &im: urb.getImoveis()){
            if (im->getProprietario() == nomeProp) total += im->mensalidade();
        }
    }
    return total;
}

vector<Urbanizacao> ECondominio::removeUrbanizacaoDe(string nomeProp) {
    vector<Urbanizacao> urbs;

    for (unsigned int i = 0; i < urbanizacoes.size(); i++){
        bool found = false;
        for (auto const &im: urbanizacoes.at(i).getImoveis()){
            if (im->getProprietario() == nomeProp){
                found = true;
                break;
            }
        }
        if (found) {
            urbs.push_back(urbanizacoes.at(i));
            urbanizacoes.erase(urbanizacoes.begin() + i);
            i--;
        }
    }

    return urbs;
}

vector<Imovel *> ECondominio::operator()(string const &nome) const {
    vector<Imovel *> imvs;

    for (auto const & urb: urbanizacoes){
        if (urb.getNome() == nome) {

            for (auto const &im: urb.getImoveis()){
                imvs.push_back(im);
            }

        }

    }

    return imvs;
}

