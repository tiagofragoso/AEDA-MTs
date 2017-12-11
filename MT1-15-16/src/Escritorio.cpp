#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA) :
        numPaginas(nPag), pPreto(pP), pAmarelo(pA) {}

Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }

Documento Documento::operator+(const Documento &d1) {

    return Documento(this->getNumPaginas()+ d1.getNumPaginas(),
                     (this->getNumPaginas()*this->getPercentagemPreto() + d1.getNumPaginas()*d1.getPercentagemPreto())/(this->getNumPaginas()+d1.getNumPaginas()),
                     (this->getNumPaginas()*this->getPercentagemAmarelo() + d1.getNumPaginas()*d1.getPercentagemAmarelo())/(this->getNumPaginas()+d1.getNumPaginas()));

}


//Impressora
Impressora::Impressora(string cod, int a) : codigo(cod), ano(a) {}

Impressora::~Impressora() {}

string Impressora::getCodigo() const { return codigo; }

int Impressora::getAno() const { return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const { return docsImpressos; }


//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner) : Impressora(cod, a), numPagImprimir(toner) {}

int ImpressoraPB::getNumPaginasImprimir() const { return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1) {

    if (this->numPagImprimir >= doc1.getNumPaginas()){
        this->numPagImprimir -= doc1.getNumPaginas();
        this->docsImpressos.push_back(doc1);
        return true;
    }

    return false;
}


//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner) : Impressora(cod, a),
                                                                 numPagImprimirPreto(toner),
                                                                 numPagImprimirAmarelo(toner) {}

int ImpressoraCores::getNumPaginasImprimir() const {
    if (numPagImprimirPreto < numPagImprimirAmarelo) return (int) numPagImprimirPreto;
    return (int) numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1) {

    if (this->numPagImprimirAmarelo >= (doc1.getNumPaginas()*doc1.getPercentagemAmarelo()) &&
        this->numPagImprimirPreto >= (doc1.getNumPaginas()*doc1.getPercentagemPreto())){
        this->numPagImprimirPreto -= doc1.getNumPaginas()*doc1.getPercentagemPreto();
        this->numPagImprimirAmarelo -= doc1.getNumPaginas()*doc1.getPercentagemAmarelo();
        this->docsImpressos.push_back(doc1);
        return true;
    }

    return false;
}


//Funcionario
Funcionario::Funcionario(string cod) : codigo(cod) {}

Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1) { impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const { return impressoras; }

string Funcionario::getCodigo() const { return codigo; }


//Escritorio
Escritorio::Escritorio() {}

Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1) { impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1) { funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const { return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const {
    int impCFunc = 0;
    for (auto const &func: funcionarios) {
        impCFunc += func.getImpressoras().size();
    }

    return impressoras.size() - impCFunc;
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1) {
    vector<Impressora*> impressorasRetiradas;
    for (int i = 0; i < impressoras.size(); i++){
        if (impressoras.at(i)->getAno() < ano1) {
                impressorasRetiradas.push_back(impressoras.at(i));
            impressoras.erase(impressoras.begin() + i);
            i--;
        }
    }
    return impressorasRetiradas;
}

Impressora *Escritorio::imprimeDoc(Documento doc1) const {

    for (auto const & imp: impressoras){
        if (imp->imprime(doc1)) return imp;
    }

    return new ImpressoraPB("inexistente", 0, 0);
}

vector<Impressora *> Escritorio::tonerBaixo() const {

    vector<Impressora *> imps;

    for (auto const & imp: impressoras){
        if (imp->getTipo() == "pb" && imp->getNumPaginasImprimir() < 30) imps.push_back(imp);
        else if (imp->getTipo() == "cores" && imp->getNumPaginasImprimir() < 20) imps.push_back(imp);
    }

    return imps;
}

string Escritorio::operator()(const string & cod) const {

    for (auto const & func: funcionarios){
        for (auto const & imp: func.getImpressoras()){
            if (imp->getCodigo() == cod) return func.getCodigo();
        }
    }

    return "nulo";
}


