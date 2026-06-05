#include<iostream>
#include"Sztring.hpp"
#include"Hozzavalo_m.hpp"


//Hozzavalo
//konstruktorok:
Hozzavalo::Hozzavalo(){}

Hozzavalo::Hozzavalo(const Sztring& neve):nev(neve){
    if(neve.getSize() == 0){
        throw InvalidInputError(Sztring("a hozzavalo neve nem lehet ures"));
    }
}

Hozzavalo::Hozzavalo(const Hozzavalo& masik) :nev(masik.nev){}

//a virtualis destruktor:
Hozzavalo::~Hozzavalo(){}
//setter/getter:
const Sztring& Hozzavalo::getNev() const {return nev;}



void Hozzavalo::setNev(const Sztring& n){
    if (n.getSize() == 0) {
        throw InvalidInputError(Sztring("a hozzavalo neve nem lehet ures"));
    }
    nev = n;
}



//Hozzavalo -> Folyadek
//konstruktorok:
Folyadek::Folyadek(){}
Folyadek::Folyadek(const Sztring& neve):Hozzavalo(neve){}
//mertekegyseghez getter:
const char* Folyadek::getMertekegyseg() const {return "ml";}


//Hozzavalo -> Szilard:
//konstruktorok:
Szilard::Szilard(){}
Szilard::Szilard(const Sztring& neve):Hozzavalo(neve){}
//mertekegyseghez getter:
const char* Szilard::getMertekegyseg() const {return "g";}


//HozzavaloMennyiseg

HozzavaloMennyiseg::HozzavaloMennyiseg() :hozz(nullptr), mennyiseg(0){}

HozzavaloMennyiseg::HozzavaloMennyiseg(Hozzavalo* const hozza, double m):hozz(nullptr), mennyiseg(m){
    if (m < 0) {
        throw InvalidInputError(Sztring("a mennyiseg nem lehet negativ"));
    }
    if (hozza) {
        hozz = hozza->clone();
    }
};

HozzavaloMennyiseg::HozzavaloMennyiseg(const HozzavaloMennyiseg& masik) :hozz(nullptr), mennyiseg(masik.mennyiseg){
    if(masik.hozz){
        hozz = masik.hozz->clone();
    }
}

HozzavaloMennyiseg& HozzavaloMennyiseg::operator=(const HozzavaloMennyiseg& masik){
    if (this != &masik) {
        delete hozz;
        hozz = nullptr;
        if (masik.hozz) {
            hozz = masik.hozz->clone();
        }
        mennyiseg = masik.mennyiseg;
    }
    return *this;
}

const Hozzavalo& HozzavaloMennyiseg::getHozz()const{
    if (hozz == nullptr) {
        throw LogicError(Sztring("A default parameterrel letrehozott HozzavaloMennyiseg nem ervenyes."));
    }
    return *hozz;
}

double HozzavaloMennyiseg::getMenny()const{return mennyiseg;}

HozzavaloMennyiseg::~HozzavaloMennyiseg(){
    delete hozz;
    hozz = nullptr;
}