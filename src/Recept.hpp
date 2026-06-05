#ifndef RECEPT_HPP
#define RECEPT_HPP

#include <iostream>
#include <cstddef>
#include "Sztring.hpp"
#include "Hozzavalo_m.hpp"
#include "DinTomb.hpp"
#include "memtrace.h"

/**
* @brief Recept osztaly a receptek tarolasara
*/
class Recept{
    Sztring nev;                                    ///< a recept neve
    Sztring tipus;                                  ///< a recept tipusa
    DinTomb<HozzavaloMennyiseg> hozzavalok;         ///< a hozzavalomennyisegeket tartalmazo dintomb tombje
    public:
    //konstruktorok:
    /**
    * @brief alapertelmezett konstruktor
    */
    Recept();

    /**
    * @brief konstruktor (amely beallítja a recept adatait)
    * @param neve = a recept neve
    * @param tipusa = a recept tipusa
    * @param hozzavaloi = a hozavalomennyisegeket tartalmazo dinamikus tomb
    */
    Recept(const Sztring& neve, const Sztring& tipusa, const DinTomb<HozzavaloMennyiseg>& hozzavaloi);

    /**
    * @brief masolo konstruktor
    * @param masik = a masolando recept
    */
    Recept(const Recept&);

    //ertekado operator
    /**
    * @brief Ertekado operator
    * @param masik = a masolando recept
    * @return eeferencia az aktualis objektumra
    */
    Recept& operator=(const Recept& masik);

    /**
    * @brief visszaadja a recept nevet
    * @return konstans referencia a nevre
    */
    const Sztring& getNev() const;

    /**
    * @brief beallitja a recept nevet
    * @param n Az uj nev
    * @throws InvalidInputError akkor, ha a nev ures
    */
    void setNev(const Sztring& n);

    /**
    * @brief visszaadja a recept tipusat
    * @return tipus
    */
    const Sztring& getTipus()const;

    /**
    * @brief beallitja a recept tipusat.
    * @param t = az uj tipus
    * @throws InvalidInputError ha a tipus ures
    */
    void setTipus(const Sztring& t);

    /**
    * @brief visszaadja a hozzavalok tombjet
    * @return konstans referencia a hozzavalok tombjere
    */
    const DinTomb<HozzavaloMennyiseg>& getHozz() const;

    /**
    * @brief destruktor
    */
    ~Recept();
};

#endif