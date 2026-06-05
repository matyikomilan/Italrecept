#include<iostream>
#include"Sztring.hpp"
#include"Hozzavalo_m.hpp"
#include"Recept.hpp"

Recept::Recept():nev("alapertelmezett"), tipus("alapertelmezett"), hozzavalok(){}

Recept::Recept(const Sztring& neve, const Sztring& tipusa, const DinTomb<HozzavaloMennyiseg>& hozzavaloi) :nev(neve), tipus(tipusa), hozzavalok(hozzavaloi){
    if (neve.getSize() == 0) {
        throw InvalidInputError(Sztring("a recept neve nem lehet ures"));
    }
    if (tipusa.getSize() == 0) {
        throw InvalidInputError(Sztring("a recept tipusa nem lehet ures"));
    }
}

//masolokonstruktor
Recept::Recept(const Recept& masik): nev(masik.nev), tipus(masik.tipus), hozzavalok(masik.hozzavalok){}

//ertekado operator
Recept& Recept::operator=(const Recept& masik){
    if(this == &masik) return *this;
    nev = masik.nev;
    tipus = masik.tipus;
    hozzavalok = masik.hozzavalok;
    return *this;
}

const Sztring& Recept::getNev() const {return nev;}

void Recept::setNev(const Sztring& n){
    if (n.getSize() == 0) {
        throw InvalidInputError(Sztring("a recept neve nem lehet ures"));
    }
    nev = n;
}

const Sztring& Recept::getTipus() const {return tipus;}

void Recept::setTipus(const Sztring& t){
    if (t.getSize() == 0) {
        throw InvalidInputError(Sztring("A recept tipusa nem lehet ures."));
    }
    tipus = t;
}

const DinTomb<HozzavaloMennyiseg>& Recept::getHozz() const {return hozzavalok;}

Recept::~Recept(){}