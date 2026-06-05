#ifndef KIVETELEK_HPP
#define KIVETELEK_HPP

#include "Sztring.hpp"

/**
* @brief alap kivetel osztaly
*/
class BaseError {
protected:
    Sztring msg;    ///< A hibaüzenet
public:
    /**
    * @brief konstruktor (C-stilusu szoveggel)
    * @param message = a hibauzenet
    */
    BaseError(const char* message) : msg(message) {}

    /**
    * @brief konstruktor (Sztring objektummal)
    * @param message = A hibauzenet
    */
    BaseError(const Sztring& message) : msg(message) {}

    /**
    * @brief visszaadja a hibauzenetet
    * @return konstans referencia a hibauzenetre
    */
    virtual const Sztring& what() const { return msg; }

    /**
    * @brief virtualis destruktor
    */
    virtual ~BaseError() {}
};


/**
* @brief ervenytelen bemenet kivetel
*/
class InvalidInputError : public BaseError {
public:
    InvalidInputError(const char* message) : BaseError(message) {}
    InvalidInputError(const Sztring& message) : BaseError(message) {}
};


/**
* @brief fajlkezelesi hiba kivetel
*/
class FileError : public BaseError {
public:
    FileError(const char* message) : BaseError(message) {}
    FileError(const Sztring& message) : BaseError(message) {}
};

/**
* @brief logikai hiba kivetel
*/
class LogicError : public BaseError {
public:
    LogicError(const char* message) : BaseError(message) {}
    LogicError(const Sztring& message) : BaseError(message) {}
};

#endif