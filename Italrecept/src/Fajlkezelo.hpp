#ifndef FAJLKEZELO_HPP
#define FAJLKEZELO_HPP

#include<iostream>
#include <cstddef>
#include"DinTomb.hpp"
#include"Sztring.hpp"
#include"Hozzavalo_m.hpp"
#include"Recept.hpp"
#include "memtrace.h"
#include "kivetelek.hpp"

/**
* @brief Fajlkezelo osztaly, ami a receptek es hozzavalok fajlba menteseert es betolteseert felelos
*/
class Fajlkezelo{
    public:
    /**
     * @brief menti a hozzavalokat a megadott fajlba
     * @param fajlnev = a celfajl neve
     * @param hozzk = a mentendo hozzavalokat tartalmazo dinamikus tomb
     * @throws FileError, ha a fajl megnyitasa sikertelen
     */
    void hozzk_ment(const Sztring& fajlnev, const DinTomb<Hozzavalo*>& hozzk);

    /**
     * @brief menti a recepteket a megadott fajlba
     * @param fajlnev = a celfajl neve
     * @param reck = a mentendo recepteket tartalmazo dinamikus tomb
     * @throws FileError, h a fajl megnyitasa sikertelen
     */
    void reck_ment(const Sztring& fajlnev, const DinTomb<Recept>& reck);

    /**
     * @brief betolt a hozzavalokat a megadott fajlbol
     * @param fajlnev = a forrasfajl neve
     * @return a betoltott hozzavalokat tartalmazo tomb
     * @throws FileError, ha a fajl megnyitasa vagy feldolgozasa sikertelen
     */
    DinTomb<Hozzavalo*> hozzk_betolt(const Sztring& fajlnev);

    /**
     * @brief betolti a recepteket a megadott nevu fajlbol
     * @param fajlnev = a forrasfajl neve
     * @param hozzk = a hozzavalokat tartalmazo dinamikus tomb referenciaja
     * @return a betoltott recepteket taralmazo dinamikus tomb
     * @throws FileError, ha a fajl megnyitasa vagy feldolgozasa sikertelen
     */
    DinTomb<Recept> reck_betolt(const Sztring& fajlnev, DinTomb<Hozzavalo*>& hozzk) const;

    /**
     * @brief beolvassa a statikus recepteket tartalmazo szoveget a megadott nevu fajlbol
     * @param fajlnev = a forrasfajl neve
     * @return a statikus receptek szovege
     * @throws FileError, ha a fajl megnyitasa sikertelen
     */
    Sztring stat_reck_beolv(const Sztring& fajlnev) const;
};

#endif