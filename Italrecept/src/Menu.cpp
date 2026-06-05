#include<iostream>
#include"Sztring.hpp"
#include"Menu.hpp"
#include"DinTomb.hpp"

Menu::Menu(Adatbazis *ab) :adatb(ab){
    if(!ab){
        throw LogicError(Sztring("Az adatb nullptr :("));
    }
}

void Menu::fomenu(std::ostream& os) const{
    os << "ITALRECEPTEK\n\n\n";
    os << "1\tReceptek\n";
    os << "2\tHozzavalok\n\n";
    os << "3\tUj recept felvetele\n";
    os << "4\tRecept torlese\n\n";
    os << "5\tUj hozzavalo felvetele\n";
    os << "6\tHozzavalo torlese\n\n\n\n";
    os << "0\tkilepes\n\n\n\n\n\n";
}

int Menu::fo_menu_pont(std:: ostream& os, std::istream& is) const{
    int valasztas;
    os << "(valassza ki a kivant menupont sorszamat, 0-6): ";

    while (true) {
        if (is >> valasztas) {
            if (valasztas >= 0 && valasztas <= 6) {
                is.clear();
                is.ignore(10000, '\n');
                return valasztas;
            }
        }
        is.clear();
        is.ignore(10000, '\n');
        os << "Hibas bemenet. Kerem, adjon meg egy szamot 0 és 6 kozott: ";
    }
}

void Menu::vissza(std::ostream& os, std::istream& is) const{
    int valasz;
    while(true){
        os << "\n(visszalepeshez usse be: 0) ";
        if (is >> valasz && valasz == 0) {
            is.clear();
            is.ignore(10000, '\n');
            break;
        }
        is.clear();
        is.ignore(10000, '\n');
        os << "ervenytelen bemenet, irjon 0-t a visszalepeshez: ";
    }
}

void Menu::hozzk_kiir(std::ostream& os) const{
    const DinTomb<Hozzavalo*>& hozzk = adatb->getHozzk();

    os << "HOZZAVALOK:\n\n";

    if(hozzk.getSize() == 0){
        os << "(Nincs megadva hozzavalo)\n\n";
    }

    else{
        for(size_t i=0; i<hozzk.getSize(); ++i){
            os << i+1 << ".\t" << hozzk[i]->getNev() << "\n";
        }
    }

    os << "\n";
}

//ujidx: FONTOS!! ez elott ki kell irni, hogy mit valaszt vele a user
int Menu::ujidx(std::ostream& os, std::istream& is, int felsohatar) const {
    int idx;
    os << "Adjon meg egy sorszamot (1-" << felsohatar << "): ";

    while (true) {
        if (is >> idx) {
            if (idx == 0) {
                return -1; // Visszalépés
            }
            if (idx >= 1 && idx <= felsohatar) {
                is.clear();
                is.ignore(10000, '\n');
                return idx - 1; //1-alapu -> 0-alapu
            }
        }
        // Hibás bemenet vagy érvénytelen index
        is.clear();
        is.ignore(10000, '\n');
        os << "Hibás bemenet! Kérem, adjon meg egy számot 1 és " << felsohatar << " között: ";
    }
}

void Menu::reck_kiir(std::ostream& os) const{
    const DinTomb<Recept> reck = adatb->getReck();

    os << "RECEPTEK:\n\n";

    if(reck.getSize() == 0){
        os << "(Nincsenek megadva receptek)\n\n";
        return;
    }
    
    Sztring elozo_tipus = reck[0].getTipus();

    os << elozo_tipus << "\n";

    for(size_t i=0; i<reck.getSize(); ++i){    
        //nincs != operator ez igy nagyon csunya?
        if(!(reck[i].getTipus() == elozo_tipus)){
            elozo_tipus = reck[i].getTipus();
            os << "\n" << elozo_tipus << "\n";
        }

        os << "\t" << i+1 << ". " << reck[i].getNev() << "\n";
    }

}

void Menu::rec_kiir(std::ostream& os, std::istream& is) const{
    //ha nincs recept, nincs mi kozul valasztani
    if (adatb->getReck().getSize() == 0) {
        os << "\nNincsenek receptek.\n";
        vissza(os, is);
        return;
    }

    os << "\n\n\n\nValassza ki az ital sorszamat: ";
    int idx = ujidx(os, is, adatb->getReck().getSize());
    if(idx == -1){
        return;
    }

    system("cls");
    os << "Nev:\t" << adatb->getReck()[idx].getNev() << "\n";
    os << "Tipus:\t" << adatb->getReck()[idx].getTipus() << "\n";

    //hozzavalok
    os << "Hozzavalok:\n";
    for(size_t i=0; i<adatb->getReck()[idx].getHozz().getSize(); ++i){
        os << "- " << adatb->getReck()[idx].getHozz()[i].getHozz().getNev() << ": " << adatb->getReck()[idx].getHozz()[i].getMenny() << adatb->getReck()[idx].getHozz()[i].getHozz().getMertekegyseg() << "\n";
    }
}

void Menu::stat_reck_kiir(std::ostream& os) const{
    os << adatb->getStat_reck();
}

Hozzavalo* Menu::ujhozz(std::ostream& os, std::istream& is){
    os << "Adja meg az uj hozzavalo nevet: ";
    Sztring neve;   
    //is.clear();
    //is.ignore(1000, '\n');
    while (true) {
        if (neve.beolv(is) && neve.getSize() > 0) {
            break;
        }
        is.clear();
        is.ignore(10000, '\n');
        os << "Hibas vagy ures nev. Adjon meg egy nem ures nevet: ";
    }

    os << "Folyadek(f), vagy szilard(s)? ";
    char tipus;
    while (true) {
        if (is >> tipus && (tipus == 'f' || tipus == 's')) {
            is.clear();
            is.ignore(10000, '\n');
            break;
        }
        is.clear();
        is.ignore(10000, '\n');
        os << "Hibas bemenet! Kerem, irjon 'f' vagy 's' betut: ";
    }

    if(tipus == 'f'){
        return new Folyadek(neve);
    }
    else{
        return new Szilard(neve);
    }
}

//-1-et ad vissza, ha nincs mit tortolni (ki is irja, hogy nincs mit torolni btw)
int Menu::hozz_torl(std::ostream& os, std::istream& is){
    if (adatb->getHozzk().getSize() == 0) {
        os << "\nNincsenek hozzavalok.\n";
        return -1;
    }

    if(adatb->getHozzk().getSize() == 0){
        std::cout << "Nincs hozzavalo, amit torolhetni lehetne:(" << std::endl;
        vissza(os, is);
    }

    hozzk_kiir(os);
    os << "Valassza ki, hogy melyik hozzavalot szeretne torolni: ";
    int idx = ujidx(os, is, adatb->getHozzk().getSize());
    if (idx == -1) {
        os << "Visszalepes a fomenube.\n";
        return -1;
    }
    return idx;
}

double Menu::ujmenny(std::ostream& os, std::istream& is) const{
    os << "Adja meg a mennyiseget:";
    double mennyi;

    while (true) {
        if (is >> mennyi) {
            if (mennyi >= 0) {
                is.clear();
                is.ignore(10000, '\n');
                return mennyi;
            }
        }
        is.clear();
        is.ignore(10000, '\n');
        os << "Hibas mennyiseg adj meg egy nem negativ szamot: ";
    }
}

DinTomb<HozzavaloMennyiseg> Menu::ujhozzmk(std::ostream& os, std::istream& is){
    DinTomb<HozzavaloMennyiseg> hozzmk;

    if (adatb->getHozzk().getSize() == 0) {
        os << "Nincs hozzavalo, amihez mennyiseg rendelheto lenne :(\n";
        return hozzmk;
    }

    while(true){
        //Hozzavalok kiirasa a valasztashoz
        os << "Melyik hozzavalobol?\n(Ha kesz, 0-t irjon)\n\n";
        for(size_t i=0; i<adatb->getHozzk().getSize(); ++i){
            os << "\t" << i+1 << ".\t";
            adatb->getHozzk()[i]->getNev().kiir(os);
            os << "\n\n";
        }
        //index bekerese:
        os << "Valasszon egy hozzavalot (sorszammal):\n(ha kesz, irjon 0-t)\n\n";
        int melyik = ujidx(os, is, adatb->getHozzk().getSize());
        if (melyik == -1) break;

        Hozzavalo* ezahozz = adatb->getHozzk()[melyik];

        //mennyiseg bekerese:
        os << "Add meg a " << ezahozz->getNev() << "mennyiseget (" << ezahozz->getMertekegyseg() << "): ";
        double mennyi = ujmenny(os, is);

        if (mennyi == 0) {
            continue; // Ha 0-t adott meg, nem adjuk hozzá
        }
        else{
            //objektum letrehozasa a beszerzett adatokbol
            HozzavaloMennyiseg ujhozzm(ezahozz, mennyi);
            hozzmk.push_back(ujhozzm);
        }

    }

    return hozzmk;
}

Recept Menu::ujrecept(std::ostream& os, std::istream& is){
    //neve:
    os << "Uj recept letrehozasa\nAdja meg az ital nevet: ";
    Sztring neve;
    while (true) {
        if (neve.beolv(is) && neve.getSize() > 0) {
            break;
        }
        is.clear();
        is.ignore(10000, '\n');
        os << "Hibas vagy ures nev. Adjon meg egy nem ures nevet: ";
    }

    //tipusa:
    os << "Adja meg az ital tipusat: ";
    Sztring tipusa;
    while (true) {
        if (tipusa.beolv(is) && tipusa.getSize() > 0) {
            break;
        }
        is.clear();
        is.ignore(10000, '\n');
        os << "Hibas vagy ures tipus. Adj meg egy nem ures tipust: ";
    }

    //hozzavaloi:
    os << "Adja meg az ital hozzavaloit: ";
    DinTomb<HozzavaloMennyiseg> hozzmei = ujhozzmk(os, is);

    Recept ujrec(neve, tipusa, hozzmei);
    return ujrec;
}

size_t Menu::rec_torl(std::ostream& os, std::istream& is){
    if (adatb->getReck().getSize() == 0) {
        os << "Nincs recept, amit torolhetni lehetne:(\n";
        vissza(os, is);
    }

    reck_kiir(os);
    os << "valassza ki, hogy melyik receptet szeretne torolni:";
    int idx = ujidx(os, is, adatb->getReck().getSize());
    if (idx == -1) {
        os << "Visszalepes a fomenube.\n";
        vissza(os, is);
    }
    return idx;
}