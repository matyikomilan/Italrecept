#ifndef MENU_HPP
#define MENU_HPP

#include<iostream>
#include <cstddef>
#include"Adatbazis.hpp"
#include"Sztring.hpp"
#include"Recept.hpp"
#include "memtrace.h"
#include"kivetelek.hpp"

/**
* @brief Menu osztaly a felhasznaloi interakcio kezelesere
*/
class Menu{
    Adatbazis* adatb;       ///< az adatbazisra mutato pointer
    public:

    /**
    * @brief konstruktor  (inicializalja az adatbazist)
    * @param ab = az adatbazisre mutat pointer
    * @throws LogicError ,ha az adatbazis nullptr
    */
    Menu(Adatbazis* ab);

    /**
    * @brief kiirja a fomenut
    * @param os Kimeneti stream
    */
    void fomenu(std::ostream& os) const;

    /**
    * @brief bekeri a fomenu pontjat
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    * @return  a valasztott menupont
    */
    int fo_menu_pont(std:: ostream& os, std::istream& is) const;

    /**
    * @brief visszalepes a fomenube
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    */
    void vissza(std::ostream& os, std::istream& is) const;

    /**
    * @brief letrehoz egy uj hozzavalot
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    * @return az uj hozzavalora mutat pointer
    * @throws InvalidInputError ha ervenytelen a bemenet
    */
    Hozzavalo* ujhozz(std::ostream& os, std::istream& is);

    /**
    * @brief bekeri a torlendo hozzavalo indexet
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    * @return a törlendő index, de ha nincs mit torolni, vagy visszalepest valasztja a user, akkor -1
    */
    int hozz_torl(std::ostream& os, std::istream& is);

    /**
    * @brief beker egy uj indexet
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    * @param felsohatar = a maximalis index
    * @return a valasztott index, visszalepesel -1 
    */
    int ujidx(std::ostream& os, std::istream& is, int felsohatar) const;

    /**
    * @brief beker egy uj mennyiseget
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    * @return mennyiseg
    */
    double ujmenny(std::ostream& os, std::istream& is) const;

    /**
    * @brief letrehoz egy uj hozzavalomennyisegeket tartalmazo dinamikus tombot
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    * @return  hozzavalomennyisegeket tartalmazo tomb
    * @throws InvalidInputError ha a bemenet ervenytelen
    */
    DinTomb<HozzavaloMennyiseg> ujhozzmk(std::ostream& os, std::istream& is);

    /**
    * @brief letrehoz egy uj receptet
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    * @return uj recept
    * @throws InvalidInputError ha ervenytelen a bemenet
    */
    Recept ujrecept(std::ostream& os, std::istream& is);

    /**
    * @brief bekeri a torlendo recept indexet
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    * @return torlendo index vagy -1, ha nincs mit torolni vagy a user visszalepni akar
    */
    size_t rec_torl(std::ostream& os, std::istream& is);

    /**
    * @brief kiirja a hozzavalokat
    * @param os = kimeneti stream
    */
    void hozzk_kiir(std::ostream& os) const;

    /**
    * @brief kiirja a recepteket
    * @param os = kimeneti stream
    */
    void reck_kiir(std::ostream& os) const;

    /**
    * @brief kiir egy adott receptet
    * @param os = kimeneti stream
    * @param is = bemeneti stream
    */
    void rec_kiir(std::ostream& os, std::istream& is) const;

    /**
    * @brief kiirja a statikus recepteket
    * @param os = kimeneti stream
    */
    void stat_reck_kiir(std::ostream& os) const;
    
};

#endif