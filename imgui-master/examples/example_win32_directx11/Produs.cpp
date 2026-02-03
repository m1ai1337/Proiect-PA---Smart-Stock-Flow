#include "Produs.hpp"


namespace produs {

    adauga_produs::adauga_produs()
    {
        this->price = 0.0f;
        this->nume = "";
        this->stock = 0;
        this->medie_vanz = 0;
        this->timp = 0;
    }

    adauga_produs::~adauga_produs()
    {
       
    }

    adauga_produs::adauga_produs(float price, std::string nume, int stock, int medie_vanz, int timp)
    {
        this->price = price;
        this->nume = nume;
        this->stock = stock;
        this->medie_vanz = medie_vanz;
        this->timp = timp;
    }
    
    //get
    float adauga_produs::get_price()
    {
        return this->price;
    }
    int adauga_produs::get_stock()
    {
        return this->stock;
    }
    int adauga_produs::get_prag_min()
    {
        return this->timp;
    }
    std::string adauga_produs::get_nume()
    {
        return this->nume;
    }
    int adauga_produs::get_medie()
    {
        return this->medie_vanz;
    }

    //set
    void adauga_produs::set_price(float price)
    {
        this->price = price;
    }

    void adauga_produs::set_stock(int stock)
    {
        this->stock = stock;
    }

    void adauga_produs::set_prag_min(int timp) // initial prag minim acum timp de livrare (nu am modificat numele la fct pt imi era... ) ;)))
    {
        this->timp = timp;
    }

    void adauga_produs::set_string(std::string nume)
    {
        this->nume = nume;
    }

    void adauga_produs::set_medie(int medie_vanz)
    {
        this->medie_vanz = medie_vanz;
    }

    void to_json(json& j, const adauga_produs& p)
    {
        j = json{ {"nume", p.nume}, {"price", p.price}, {"stock", p.stock},  {"medie", p.medie_vanz},  {"timp", p.timp}};
    }

    void from_json(const json& j, adauga_produs& p)
    {
        j.at("nume").get_to(p.nume);
        j.at("price").get_to(p.price);
        j.at("stock").get_to(p.stock);
        j.at("medie").get_to(p.medie_vanz);
        j.at("timp").get_to(p.timp);
    }

}
