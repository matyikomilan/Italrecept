#ifndef HOZZAVALO_M_HPP
#define HOZZAVALO_M_HPP

#include<iostream>
#include <cstddef>
#include"Sztring.hpp"
#include "memtrace.h"
#include "kivetelek.hpp"

/**
* @brief absztrakt alaposztaly a hozzavalokhoz
*/
class Hozzavalo{
    Sztring nev;        ///< a hozzavalo neve
    public:
    //konstruktorok:
    /**
    * @brief alapertelmezett konstruktor
    */
    Hozzavalo();

    /**
    * @brief konstruktor (beallitja a nevet)
    * @param neve = a hozzavalo neve
    */
    Hozzavalo(const Sztring& neve);

    /**
    * @brief maolo konstruktor
    * @param masik = a masolando hozzavalo
    */
    Hozzavalo(const Hozzavalo& masik);

    //getter/setter:
    /**
    * @brief visszater a hozzavalo nevevel
    * @return konstans referencia a nevre
    */
    const Sztring& getNev() const;

    /**
    * @brief beallitja a hozzavalo nevet
    * @param n = az uj nev
    * @throws InvalidInputError, ha a nev ures
    */
    void setNev(const Sztring& n);

    //virtualis destruktor:
    /**
    * @brief Virtuális destruktor.
    */
    virtual ~Hozzavalo();

    //virtualis getter mertekegyseghez:
    /**
    * @brief absztrakt getter a mertekegyseghez
    * @return a mertekegyseg
    */
    virtual const char* getMertekegyseg() const = 0; //absztrakt

    /**
    * @brief klonozo metodus
    * @return uj masolat a hozzavalorol
    */
    virtual Hozzavalo* clone() const = 0;
};


/**
* @brief Folyadek tipusu hozzavalo osztaly
*/
class Folyadek :public Hozzavalo{
    public:
    /**
    * @brief alapertelmezett konstruktor
    */
    Folyadek();

    /**
    * @brief konstruktor (beallitja a nevet)
    * @param neve = a hozzavalo neve
    */
    Folyadek(const Sztring& neve);

    /**
    * @brief masolo konstruktor
    * @param masik = a masolando Folyadek objektum
    */
    Folyadek(const Folyadek& masik) : Hozzavalo(masik) {}

    /**
    * @brief visszater a mertekegyseggel
    * @return "ml"
    */
    const char* getMertekegyseg() const;

    /**
    * @brief klonozo metodus
    * @return u masolat a folyadekrol
    */
    Hozzavalo* clone() const { return new Folyadek(*this); }
};


/**
* @brief Szilard tipusu hozzavalo osztaly
*/
class Szilard :public Hozzavalo{
    public:
    /**
    * @brief alapertelmezett konstruktor
    */
    Szilard();

    /**
    * @brief masolo konstruktor
    * @param masik = a masolando Folyadek objektum
    */
    Szilard(const Szilard& masik) : Hozzavalo(masik) {}

    /**
    * @brief konstruktor (amely beallitja a nevet)
    * @param neve = a hozzavalo neve
    */
    Szilard(const Sztring& neve);

    /**
    * @brief visszater a mertekegyseggel
    * @return "g"
    */
    const char* getMertekegyseg() const;

    /**
    * @brief klonozo metodus
    * @return uj masolat a szilard hozzavalorol
    */
    Hozzavalo* clone() const { return new Szilard(*this); }
};

/**
* @brief egy Hozzavalot es mennyiseget tarolo osztaly
*/
class HozzavaloMennyiseg{
    private:
    Hozzavalo* hozz;    ///< A hozzavalo pointere
    double mennyiseg;   ///< A mennyiseg

    public:
    /**
    * @brief alapertelmezett konstruktor
    */
    HozzavaloMennyiseg();
    //nagyon fontos, hogy a default konstruktor miatt, a getternek ellenoriznie kell a hozz-t
    //mert semmi ertelme a default konstruktorral letrehozott HozzavaloMennyisegnek

    /**
    * @brief konstruktor (amely beallitja a hozzavalot as mennyiseget)
    * @param hozza = a hozzavalora mutato pointer
    * @param m = a mennyiség
    */
    HozzavaloMennyiseg(Hozzavalo* const hozza, double m);

    /**
    * @brief masolo konstruktor
    * @param masik = a masolando objektum
    */
    HozzavaloMennyiseg(const HozzavaloMennyiseg& masik);

    /**
    * @brief ertekado operator
    * @param masik = a masolando objektum
    * @return referencia az aktualis objektumra
    */
    HozzavaloMennyiseg& operator=(const HozzavaloMennyiseg& masik);

    /**
    * @brief visszater a hozzavaloval
    * @return konstans referencia a hozzavalora.
    * @throws LogicError, ha a hozzavalo nullptr
    */
    const Hozzavalo& getHozz()const;

    /**
    * @brief visszater a mennyiseggel
    * @return = a mennyiseg
    */
    double getMenny()const;

    /**
    * @brief destruktor
    */
    ~HozzavaloMennyiseg();
};

#endif