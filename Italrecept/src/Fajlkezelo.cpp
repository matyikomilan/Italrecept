#include<iostream>
#include"Fajlkezelo.hpp"
#include"Sztring.hpp"
#include"Hozzavalo_m.hpp"
#include<fstream>
#include "DinTomb.hpp"
#include"Recept.hpp"

/**
 * @brief sztringet intte konvertal, std::stoi helyett hasznalando
 * @param sz a konvertalando sztring
 * @return az egesz szam
 * @throws FileError, ha a sztring ervenytelen szam
 */
int sztringtoint(const Sztring& sz) {
    if (sz.getSize() == 0) {
        throw FileError(Sztring("ures sztring (strtoi)\n"));
    }

    int res = 0;
    for (size_t i = 0; i < sz.getSize(); ++i) {
        if (sz[i] < '0' || sz[i] > '9') {
            throw FileError(Sztring("hibas formatumu mennyiseg:(\n"));
        }
        res = res * 10 + (sz[i] - '0');
    }
    return res;
}

void Fajlkezelo::hozzk_ment(const Sztring& fajlnev, const DinTomb<Hozzavalo*>& hozzk){
    std::ofstream fajl(fajlnev.getStr());
    if(!fajl.is_open()){
        throw FileError(Sztring("Nem sikerult megnyitni a hozzk.txt-t a menteshez:(\n"));
    }

    for(size_t i=0; i<hozzk.getSize(); ++i){
        //eloszor beirjuk a fajlba a hozzavalo nevet, majd a hakmazallapotat:
        fajl << hozzk[i]->getNev() << "_";
        if(strcmp(hozzk[i]->getMertekegyseg(), "ml") == 0){
            fajl << "f" << std::endl;
        }
        else{
            fajl << "s" << std::endl;
        }
    }
    fajl.close();
}

void Fajlkezelo::reck_ment(const Sztring& fajlnev, const DinTomb<Recept>& reck){
    std::ofstream fajl(fajlnev.getStr());
    if(!fajl.is_open()){
        throw FileError(Sztring("Nem sikerult megnyitni a receptek szovegfajljat:(\n"));
    }

    for(size_t i=0; i<reck.getSize(); ++i){
        fajl << reck[i].getTipus() << ":" << reck[i].getNev() << ":";

        //hozzavalomennyisegek fajlbairasa:
        for(size_t j=0; j<reck[i].getHozz().getSize(); ++j){
            fajl << reck[i].getHozz()[j].getHozz().getNev().getStr() << "_" <<  reck[i].getHozz()[j].getMenny();
            if(j!=reck[i].getHozz().getSize()-1) fajl << ",";
        }
        fajl << ";\n";
    }
    fajl.close();
}


DinTomb<Hozzavalo*> Fajlkezelo::hozzk_betolt(const Sztring& fajlnev) {
    std::ifstream fajl(fajlnev.getStr());
    if (!fajl.is_open()) {
        return DinTomb<Hozzavalo*>();
    }
    
    DinTomb<Hozzavalo*> hozzk;
    Sztring sor;
    size_t sorszam = 0;
    while (fajl.good()) {
        if (!sor.beolv(fajl)) {
            continue;
        }
        sorszam++;
        if (sor.getSize() == 0) {
            continue;
        }
        if (sor.getSize() < 2) {
            continue;
        }
        size_t alav_index = sor.getSize() - 2;
        Sztring nev = sor.substr(0, alav_index);
        Sztring tipus = sor.substr(alav_index, 2);
        if (tipus == "_f") {
            hozzk.push_back(new Folyadek(nev));
        } else if (tipus == "_s") {
            hozzk.push_back(new Szilard(nev));
        } else {
            throw FileError(Sztring("Helytelen hozzavalo tipus a fajlban"));
        }
        
    }
    
    fajl.close();
    return hozzk;
}

DinTomb<Recept> Fajlkezelo::reck_betolt(const Sztring& fajlnev, DinTomb<Hozzavalo*>& hozzk) const {
    std::ifstream fajl(fajlnev.getStr());
    if (!fajl.is_open()) {
        return DinTomb<Recept>();
    }

    DinTomb<Recept> reck;
    Sztring sor;
    size_t sor_szam = 0;

    while (fajl.good()) {
        sor_szam++;
        if (!sor.beolv(fajl)) {
            if (fajl.eof()) {
                break;
            }
            continue;
        }
        if (sor.getSize() == 0) {
            continue;
        }

        size_t elso_kettospont = sor.find(':');
        if (elso_kettospont == 99) {
            continue;
        }

        Sztring tipus = sor.substr(0, elso_kettospont);
        if (tipus.getSize() == 0) {
            continue;
        }

        size_t masodik_kettospont = sor.find(':', elso_kettospont + 1);
        if (masodik_kettospont == 99) {
            continue;
        }

        Sztring nev = sor.substr(elso_kettospont + 1, masodik_kettospont - elso_kettospont - 1);
        if (nev.getSize() == 0) {
            continue;
        }

        size_t pontosvesszo = sor.find(';');
        if (pontosvesszo == 99) {
            continue;
        }

        Sztring hozzavalok_str = sor.substr(masodik_kettospont + 1, pontosvesszo - masodik_kettospont - 1);
        DinTomb<HozzavaloMennyiseg> hozzavalok_lista;

        size_t start = 0;
        bool hiba = false;
        while (start < hozzavalok_str.getSize()) {
            size_t vesszo = hozzavalok_str.find(',', start);
            if (vesszo == 99) {
                vesszo = hozzavalok_str.getSize();
            }

            Sztring hozzavalo = hozzavalok_str.substr(start, vesszo - start);
            size_t alav_index = hozzavalo.find('_');
            if (alav_index == 99) {
                hiba = true;
                break;
            }

            Sztring hozz_nev = hozzavalo.substr(0, alav_index);
            Sztring mennyiseg_str = hozzavalo.substr(alav_index + 1, hozzavalo.getSize() - alav_index - 1);

            double mennyiseg = 0;
            try {
                mennyiseg = sztringtoint(mennyiseg_str);
            } catch (...) {
                hiba = true;
                break;
            }

            bool talalt = false;
            for (size_t i = 0; i < hozzk.getSize(); ++i) {
                if (hozzk[i] && hozzk[i]->getNev() == hozz_nev) {
                    hozzavalok_lista.push_back(HozzavaloMennyiseg(hozzk[i], mennyiseg));
                    talalt = true;
                    break;
                }
            }
            if (!talalt) {
                hiba = true;
                break;
            }
            start = vesszo + 1;
        }

        if (!hiba) {
            reck.push_back(Recept(nev, tipus, hozzavalok_lista));
        }
    }

    fajl.close();
    return reck;
}

//ez csak soronkent beolvassa a komplett txt fajlt egy hosszu Sztringbe
Sztring Fajlkezelo::stat_reck_beolv(const Sztring& fajlnev) const{
    std::ifstream fajl(fajlnev.getStr());
    if(!fajl.is_open()){
        throw FileError(Sztring("Nem sikerult megnyitni a statikus_receptek.txt fajlt:(\n"));
    }

    Sztring stat_reck;

    //soronkent beolvassuk a fajlt, a sorokat betunkent hozzafuzzuk a stat_reck-hez
    while(fajl.peek() != EOF){
        Sztring sor;
        sor.beolv(fajl);
        for(size_t i=0; i<sor.getSize(); ++i){
            stat_reck += sor[i];
        }
        stat_reck += '\n';
    }

    return stat_reck;
}