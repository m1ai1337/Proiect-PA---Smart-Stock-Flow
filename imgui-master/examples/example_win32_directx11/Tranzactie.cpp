#include "Tranzactie.hpp"

namespace TR {

    Tranzactie::Tranzactie(std::string descriere, float val, bool type)
    {
        this->descriere = descriere;
        this->val = val;
        this->type = type;
    }

    Tranzactie::~Tranzactie()
    {

    }

    //set
    void Tranzactie::set_val(float val)
    {
        this->val = val;
    }

    void Tranzactie::set_type(bool type)
    {
        this->type = type;
    }

    void Tranzactie::set_descriere(std::string descriere)
    {
        this->descriere = descriere;
    }

    //get

    float Tranzactie::get_val()
    {
        return this->val;
    }
    bool Tranzactie::get_type()
    {
        return this->type;
    }
    std::string Tranzactie::get_descriere()
    {
        return this->descriere;
    }
    



}
