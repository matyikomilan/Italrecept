#include <iostream>
#include <cstring>
#include "Sztring.hpp"

Sztring::Sztring():size(0), str(new char[1]) {str[0] = '\0';}

Sztring::Sztring(char const* s){
    size = std::strlen(s);
    str = new char[size+1];
    std::strcpy(str, s);
}

Sztring::Sztring(const Sztring& masik) {
    size = masik.size;
    str = new char[size + 1];
    for (size_t i = 0; i <= size; ++i) {
        str[i] = masik.str[i];
    }
}

Sztring& Sztring::operator=(const Sztring& masik) {
    if (this != &masik) {
        delete[] str;
        size = masik.size;
        str = new char[size + 1];
        for (size_t i = 0; i <= size; ++i) {
            str[i] = masik.str[i];
        }
    }
    return *this;
}


bool Sztring::operator==(const Sztring& masik)const{
    return std::strcmp(str, masik.str) == 0;
}


char& Sztring::operator[](size_t idx){
    if (idx >= size) throw LogicError(Sztring("Tulindexeles"));
    return str[idx];
}

const char& Sztring::operator[](size_t idx) const{
    if (idx >= size) throw LogicError(Sztring("Tulindexeles"));
    return str[idx];
}

Sztring& Sztring::operator+=(char c){
    char* ujstr = new char[size+2]; //+1 <- c; +1 <- '\0'

    //masolas:
    strcpy(ujstr, str);

    //+c, +'\0'
    ujstr[size] = c;
    ujstr[size+1] = '\0';

    delete[] str;
    str = ujstr;
    ++size;

    return *this;
}

size_t Sztring::getSize() const {
    return size;
}

const char* Sztring::getStr() const{
    return str;
}

void Sztring::kiir(std::ostream& os) const{
    os << str;
}

// Sztring beolvasasa inputbufferes megoldassal
bool Sztring::beolv(std::istream& is) {
    size_t kapacitas = 100;
    char* temp = new char[kapacitas];
    size_t idx = 0;

    // Kihagyjuk a whitespace-eket és sortöréseket az elején
    while (is.peek() != EOF && (is.peek() == '\n' || is.peek() == ' ' || is.peek() == '\r' || is.peek() == '\t')) {
        is.get();
    }

    if (!is.good() || is.peek() == EOF) {
        delete[] temp;
        return false;
    }

    char c;
    while (is.get(c)) {
        if (c == '\n' || c == '\r') {
            break;
        }
        if (idx >= kapacitas - 1) {
            kapacitas += 50;
            char* ujtemp = new char[kapacitas];
            for (size_t i = 0; i < idx; ++i) {
                ujtemp[i] = temp[i];
            }
            delete[] temp;
            temp = ujtemp;
        }
        temp[idx++] = c;
    }
    temp[idx] = '\0';

    if (idx == 0) {
        delete[] temp;
        return false;
    }

    delete[] str;
    str = temp;
    size = idx;
    return true;
}

size_t Sztring::find(char c, size_t start) const {
    for (size_t i = start; i < size; ++i) {
        if (str[i] == c) {
            return i;
        }
    }
    return 99;
}

Sztring Sztring::substr(size_t start, size_t len) const{
    if (start >= size || start + len > size) {
        throw LogicError(Sztring("ervenytelen substr parameter\n"));
    }
    char* temp = new char[len+1];
    for (size_t i = 0; i < len; ++i) {
        temp[i] = str[start + i];
    }
    temp[len] = '\0';
    Sztring result(temp);
    delete[] temp;
    return result;
}

Sztring::~Sztring(){
    delete[] str;
    str = nullptr;
}

//globalis fv (operator<<)
std::ostream& operator<<(std::ostream& os, const Sztring& s){
    s.kiir(os);
    return os;
}