#ifndef ADATBAZIS_HPP
#define ADATBAZIS_HPP

#include<iostream>
#include <cstddef>
#include"DinTomb.hpp"
#include"Recept.hpp"
#include"Hozzavalo_m.hpp"
#include"Fajlkezelo.hpp"
#include"Sztring.hpp"
#include "memtrace.h"

/**
* @brief Adatbázis osztály a receptek és hozzávalók tárolására és kezelésére.
*/
class Adatbazis{
    private:
    DinTomb<Recept> reck;           ///< recepteket tartalmazo dinamikus tomb
    DinTomb<Hozzavalo*> hozzk;      ///< hozzavalokat tartalmazo dinamikus tomb
    Sztring stat_reck;              ///< statikus recepteket tartalmazo szöveg
    Fajlkezelo fajlkezelo;          ///< Fajlkezelo objektum

    public:
   /**
    * @brief default konstruktor (inicializalja az attributumokat):
    */
    Adatbazis() : reck(), hozzk(), stat_reck(), fajlkezelo() {}

    //mentes es betoltes
    /**
    * @brief betolti az adatokat a megadott fajlokbol
    * @param reck_fajlnev a recepteket tartalmazo fajl neve
    * @param hozzk_fajlnev a hozzavalokat tartalmazo fajl neve
    * @param stat_reck_fajlnev a statikus recepteket tartalmazo fajl neve
    */
    void betolt(const char* reck_fajlnev, const char* hozzk_fajlnev, const char* stat_reck_fajlnev);

    /**
    * @brief menti az adatokat a megadott fajlokba
    * @param reck_fajlnev a recepteket tartalmazo fajl neve
    * @param hozzk_fajlnev a hozzavalokat tartalmazo fajl neve
    */
    void ment(const char* reck_fajlnev, const char* hozzk_fajlnev);

    //hozzadas es torles (hozz/rec)
    /**
    * @brief hozzad egy uj hozzavalot az adatbazishoz
    * @param ujhozz a hozzaadando hozzavalora mutato pointer
    * @return true ha a hozzáadás sikeres, false ha a hozzávaló már létezik
    */
    bool hozz_add(Hozzavalo* const ujhozz);

    /**
    * @brief hozzad egy uj receptet az adatbazishoz
    * @param ujrec a hozzaadando recept
    * @return true ha a hozzáadás sikeres, false ha nem
    */
    bool rec_add(const Recept& ujrec);

    /**
    * @brief torol egy hozzavalot az adatbazisbol
    * @param torlendo_hozz_idx A torlendo hozzavalo indexe
    * @return true, ha a torles sikeres, false ha nem torolheto
    * @throws LogicError ervenytelen index eseten
    */
    bool hozz_torl(size_t torlendo_hozz_idx);

    /**
    * @brief torol egy receptet az adatbazisbol
    * @param torlendo_rec_idx a torlendo recept indexe
    * @return true ha a troles sikeres, false, ha nem torolheto
    * @throws LogicError ervenytelen index eseten
    */
    bool rec_torl(size_t torlendo_rec_idx);

    //getterek
    /**
     * @brief visszater a recepteket tartalmazo dinamikus tombbel
     * @return a receptek tombjenek referenciajaval ter vissza
     */
    const DinTomb<Recept>& getReck() const;

    /**
     * @brief visszater a hozzavalokat tartalmazo dinamuikus tombbel
     * @return referencia a hozzavalokat tartalmazo tombre
     */
    const DinTomb<Hozzavalo*>& getHozzk() const;    //direkt nem const a fv

    /**
     * @brief visszater a statikus recepteket tartalmazo szoveggel
     * @return konstans referencia a statikus receptek szovegere
     */
    const Sztring& getStat_reck() const;

    //destruktor a pointertarolas miatt:
    /**
     * @brief destruktor: felszabaditja a hozzavalokat
     */
    ~Adatbazis();
};

#endif