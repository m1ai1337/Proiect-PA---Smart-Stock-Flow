#include "Tranzactie.hpp"

namespace TR {

    Tranzactie::Tranzactie(std::string descriere, float val, bool type)
    {
        this->descriere = descriere;
        this->val = val;
        this->type = type;
    }

    Tranzactie::Tranzactie()
    {
        this->descriere = "";
        this->val = 0.0f;
        this->type = false;
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

    void to_json(json& j, const Tranzactie& p)
    {
        j = json{ {"descriere", p.descriere}, {"type", p.val}, {"val", p.type} };
    }

    void from_json(const json& j, Tranzactie& p)
    {
        j.at("descriere").get_to(p.descriere);
        j.at("type").get_to(p.val);
        j.at("val").get_to(p.type);
    }
}
