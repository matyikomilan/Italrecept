#include<iostream>
#include"Adatbazis.hpp"



void Adatbazis::betolt(const char* reck_fajlnev, const char* hozzk_fajlnev, const char* stat_reck_fajlnev) {
    for (size_t i = 0; i < hozzk.getSize(); ++i) {
        delete hozzk[i];
        hozzk[i] = nullptr;
    }
    hozzk = DinTomb<Hozzavalo*>();

    hozzk = fajlkezelo.hozzk_betolt(hozzk_fajlnev);
    reck = fajlkezelo.reck_betolt(reck_fajlnev, hozzk);
    stat_reck = fajlkezelo.stat_reck_beolv(stat_reck_fajlnev);
}

void Adatbazis::ment(const char* reck_fajlnev, const char* hozzk_fajlnev){
    fajlkezelo.hozzk_ment(hozzk_fajlnev, hozzk);
    fajlkezelo.reck_ment(reck_fajlnev, reck);
}

bool Adatbazis::hozz_add(Hozzavalo* const ujhozz){
    //ha mar letezik, akkor visszaterunk
    for(size_t i=0; i<hozzk.getSize(); ++i){
        if(hozzk[i]->getNev() == ujhozz->getNev()){
            return false;   //"sikertelen hozzaadas" = mar letezik a hozzavalo
        }
    }

    hozzk.push_back(ujhozz);

    return 1;   //sikeres hozzaadas
}

bool Adatbazis::rec_add(const Recept& ujrec){
    //beszurjuk az uj receptet az ugyanolyan tipusu receptek melle:
    for(size_t i=0; i<reck.getSize(); ++i){
        //ha talalunk ugyanolyan tipusu receptet, akkor az ele beszurjuk az ujat
        if(ujrec.getTipus() == reck[i].getTipus()){
            reck.insert(i, ujrec);
            return true;
        }
    }

    //Ha nem talalunk ilyet, akk mehet a pushback
    reck.push_back(ujrec);
    return true;
}

bool Adatbazis::hozz_torl(size_t torlendo_hozz_idx){
    if (torlendo_hozz_idx >= hozzk.getSize()) {
        throw LogicError(Sztring("ervenytelen hozzavaloindex torlesnel\n")); // ervenytelen index
    }
    Hozzavalo* torlendo = hozzk[torlendo_hozz_idx];

    //ha szerepel a hozzavalo valamelyik receptben, akkor nem torolhetjuk
    for(size_t i=0; i<reck.getSize(); ++i){
        const DinTomb<HozzavaloMennyiseg>& hozzmk = reck[i].getHozz();
        for(size_t j=0; j<hozzmk.getSize(); ++j){
            if(hozzmk[j].getHozz().getNev() == torlendo->getNev()){
                return false;   //szerepel egy receptben -> NEM torolheto
            }
        }
    }

    //NEM szerepel receptben -> TOROLHETO -> toroljuk
    delete hozzk[torlendo_hozz_idx];
    hozzk[torlendo_hozz_idx] = nullptr;
    hozzk.torol(torlendo_hozz_idx);
    return true;
}

bool Adatbazis::rec_torl(size_t torlendo_rec_idx){
    if (torlendo_rec_idx >= reck.getSize()) {
        throw LogicError(Sztring("ervenytelen receptindex torlesnel\n")); // ervenytele index
    }
    reck.torol(torlendo_rec_idx);
    return true;
}

//getterek
const DinTomb<Recept>& Adatbazis::getReck() const{
    return reck;
}

const DinTomb<Hozzavalo*>& Adatbazis::getHozzk() const{
    return hozzk;
}

const Sztring& Adatbazis::getStat_reck() const{
    return stat_reck;
}

Adatbazis::~Adatbazis() {
    for (size_t i = 0; i < hozzk.getSize(); ++i) {
        delete hozzk[i];
        //hozzk[i] = nullptr;
    }
}