#include "Produs.hpp"


namespace produs {

    adauga_produs::~adauga_produs()
    {
       
    }

    adauga_produs::adauga_produs(float price_, std::string nume_, int stock_, int prag_min_, int medie_vanz_)
    {
        price = price_;
        nume = nume_;
        stock = stock_;
        prag_min = prag_min_;
        medie_vanz = medie_vanz_;
    }
    
    //get
    float adauga_produs::get_price()
    {
        return price;
    }
    int adauga_produs::get_stock()
    {
        return stock;
    }
    int adauga_produs::get_prag_min()
    {
        return prag_min;
    }
    std::string adauga_produs::get_nume()
    {
        return nume;
    }
    int adauga_produs::get_medie()
    {
        return medie_vanz;
    }

    //set
    void adauga_produs::set_price(float price_)
    {
        price = price_;
    }
    void adauga_produs::set_stock(int stock_)
    {
        stock = stock_;
    }
    void adauga_produs::set_prag_min(int prag_)
    {
        prag_min = prag_;
    }

    void adauga_produs::set_string(std::string nume_)
    {
        nume = nume_;
    }

    void adauga_produs::set_medie(int medie_vanz_)
    {
        medie_vanz = medie_vanz_;
    }

   

}
