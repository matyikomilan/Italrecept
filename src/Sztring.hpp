#include <iostream>
#include <cstring>
#include <cstddef>
#include "memtrace.h"
#include"kivetelek.hpp"

#ifndef SZTRING_HPP
#define SZTRING_HPP

/**
* @brief sajat sztring osztaly
*/
class Sztring{
    size_t size;    ///< a sztring merete
    char* str;      ///< a sztring karaktereinek tombje
    public:
    /**
    * @brief alapertelmezett konstruktor
    */
    Sztring();

    /**
    * @brief konstruktor C-stilusu szoveggel
    * @param s = a sztring tartalma
    */
    Sztring(const char* s);

    /**
    * @brief masolo konstruktor
    * @param masik = a masolando sztring
    */
    Sztring(const Sztring& masik);

    /**
    * @brief ertekado operator
    * @param masik = a masolando sztring
    * @return referencia az aktualis objektumra
    */
    Sztring& operator=(const Sztring& masik);

    /**
    * @brief egyenloseg operator
    * @param masik = a masik sztring
    * @return true  ha a sztringek egyenlok
    */
    bool operator==(const Sztring& masik)const;

    /**
    * @brief indexelo operator
    * @param idx = az index
    * @return referencia a karakterre
    * @throws LogicError ha ervenytelen az index
    */
    char& operator[](size_t idx);

    /**
    * @brief konstans indexelo operator
    * @param idx = az index
    * @return konstans referencia a karakterre
    * @throws LogicError ha ervenytelen az index
    */
    const char& operator[](size_t idx) const;

    /**
    * @brief hozzafuz egy karaktert
    * @param c = a hozzafuzedo karakter
    * @return referencia az aktualis objektumra
    */
    Sztring& operator+=(char c);

    /**
    * @brief visszaadja a sztring meretet
    * @return meret
    */
    size_t getSize()const;

    /**
    * @brief visszaadja a sztring C-stilusu szoveget
    * @return pointer a szovegre
    */
    const char* getStr()const;

    /**
    * @brief kiirja a sztringet
    * @param os = kimeneti stream
    */
    void kiir(std::ostream& os)const;

    /**
    * @brief beolvassa a sztringet
    * @param is bemeneti stream
    * @throws InvalidInputError akkor, ha a beolvasas sikertelen
    * @return true ha sikeres a beolvasas, false ha nem az
    */
    bool beolv(std::istream& is);

    /// @brief reszsorozat kinyerese
    /// @param start = kezdo poz
    /// @param len = a reszsorozat hossza
    /// @return uj Sztring objektum a reszsorozattal
    Sztring substr(size_t start, size_t len) const;

    /// @brief keres egy karaktert a stringben
    /// @param c = a keresendo karakter
    /// @param start = ahonnan kezdve keressuk
    /// @return a keresett karakter helye
    size_t find(char c, size_t start = 0) const;

    /**
    * @brief Destruktor.
    */
    ~Sztring();
};

/**
* @brief kiirja a sztringet egy streamre
* @param os = kimeneti stream
* @param s = a sztring
* @return kimeneti stream
*/
std::ostream& operator<<(std::ostream& os, const Sztring& s);

#endif