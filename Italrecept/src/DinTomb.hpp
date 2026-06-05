#ifndef DINTOMB_HPP
#define DINTOMB_HPP

#include <cstddef>
#include "memtrace.h"
#include "Sztring.hpp"
#include"Hozzavalo_m.hpp"

/**
 * @brief dinamikus tomb sablonosztaly
 * @tparam T = a tarolt elemek tipusa
 */
template<typename T>
class DinTomb{
    private:
    T* tomb;            ///< a dinamikus tomb elemeit tarolo pointer
    size_t size;        ///< a dinamikus tomb merete
    size_t kapacitas;   ///< a dinamikus tomb kapacitasa

    /**
     * @brief boviti a dinamikus tomb kapacitasat
     */
    void bovit() {
        size_t uj_kapacitas = kapacitas == 0 ? 1 : kapacitas * 2;
        T* uj_tomb = new T[uj_kapacitas];
        for (size_t i = 0; i < size; ++i) {
            uj_tomb[i] = tomb[i];
        }
        delete[] tomb;
        tomb = uj_tomb;
        kapacitas = uj_kapacitas;
    }

    public:
    /**
    * @brief konstruktor (inicializalja a dinamikus tombot)
    */
    DinTomb() : tomb(nullptr), size(0), kapacitas(0)  {}

    /**
    * @brief masolokonstruktor
    * @param masik = a masolando dinamikus tomb
    */
    DinTomb(const DinTomb<T>& masik) : tomb(nullptr), size(masik.size), kapacitas(masik.kapacitas)  {
        if (kapacitas > 0) {
            tomb = new T[kapacitas];
            for (size_t i = 0; i < size; ++i) {
                tomb[i] = masik.tomb[i];
            }
        }
    }


    /**
    * @brief hzzaad egy elemet a dinamikus tomb vegehez
    * @param elem = a hozaadando elem
    */
    void push_back(const T& elem) {
        if (size >= kapacitas) {
            bovit();
        }
        tomb[size++] = elem;
    }

    /**
    * @brief beszur egy elemet a megadott indexre
    * @param idx = a beszuras erre a helye tortenik
    * @param elem = a beszurando elem
    * @throws LogicError, ha ervenytelen az index
    */
    void insert(size_t idx, const T& elem) {
        if (idx > size) {
            throw LogicError(Sztring("Az insert (DinTomb fv.) kapott indexparametere out of bounds (hibas index) :(\n"));
        }
        if (size >= kapacitas) {
            bovit();
        }
        for (size_t i = size; i > idx; --i) {
            tomb[i] = tomb[i - 1];
        }
        tomb[idx] = elem;
        ++size;
    }

    /**
    * @brief torol egy elemet a megadott indexrol
    * @param idx = a torleno elem indexe
    * @throws LogicError, ha ervenytelen az index
    */
    void torol(size_t idx) {
        if (idx >= size) {
            throw LogicError(Sztring("A torol (DinTomb fv.) kapott indexparametere out of bounds (hibas index) :(\n"));
        }
        for (size_t i = idx; i < size - 1; ++i) {
            tomb[i] = tomb[i + 1];
        }
        --size;
    }

    /**
    * @brief visszater a dinamikus tomb meretevel
    * @return a dinamikus tomb meretevel ter vissza
    */
    size_t getSize() const{return size;}

    /**
    * @brief visszater a tartalmazott tombre muztato pointerrel
    * @return a tombre mutat pointerrel ter vissza
    */
    const T* getTomb() const{return tomb;}

    /**
    * @brief indexelo operator
    * @param idx = az elem indexe
    * @return referencia az elemre
    * @throws LogicError, ha ervenynytelen az index
    */
    T& operator[](size_t idx) {
        // Index-ellenőrzés: idx-nek 0 és size-1 között kell lennie
        if(idx >= size) {
            throw LogicError(Sztring("Az operator[] (DinTomb fv.) kapott indexparametere out of bounds :(\n"));
        }

        return tomb[idx];
    }
    
    /**
    * @brief konstans indexelo operator
    * @param idx = az elem indexe
    * @return konstans referencia az elemre
    * @throws LogicError, a ervenytelen az index
    */
    const T& operator[](size_t idx) const{
        //index csekk
        if(idx >= size) {
            throw LogicError(Sztring("Az operator[] (DinTomb fv.) kapott indexparametere out of bounds :(\n"));
        }
        return tomb[idx];
    }

    /**
    * @brief ertekado operator
    * @param masik = a másolando dinamikus tomb
    * @return referencia az aktualis objektumra
    */
    DinTomb<T>& operator=(const DinTomb<T>& masik) {
        if (this != &masik) {
            delete[] tomb;
            tomb = nullptr;
            kapacitas = masik.kapacitas;
            size = masik.size;
            if (kapacitas > 0) {
                tomb = new T[kapacitas];
                for (size_t i = 0; i < size; ++i) {
                    tomb[i] = masik.tomb[i];
                }
            }
        }
        return *this;
    }

    /**
    * @brief destruktor (felszabadítja a tomb altal lefoglalt memoriat)
    */
   ~DinTomb() {
        delete[] tomb;
        tomb = nullptr;
        size = 0;
        kapacitas = 0;
    }
};

//// spec: Hozzavalo:
//template <>
//inline DinTomb<Hozzavalo*>::~DinTomb() {
//    for (size_t i = 0; i < size; ++i) {
//        delete tomb[i];
//    }
//    delete[] tomb;
//    tomb = nullptr;
//    size = 0;
//    kapacitas = 0;
//}

#endif