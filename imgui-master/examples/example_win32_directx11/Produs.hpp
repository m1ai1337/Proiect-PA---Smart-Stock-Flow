#include "includes.h"

namespace produs {
    class adauga_produs
    {
    protected:
        float price;
        std::string nume;
        int stock;
        int medie_vanz;
        int prag_min; // timp de livrare

    public:
        adauga_produs(float price_, std::string nume_, int stock_, int prag_min_, int medie_vanz_);
        ~adauga_produs();

        //get
        float get_price();
        int get_stock();
        int get_prag_min();
        int get_medie();
        std::string get_nume();

        //set
        void set_price(float price_);
        void set_stock(int stock_);
        void set_medie(int medie_vanz_);
        void set_prag_min(int prag_);
        void set_string(std::string nume_);
        //other func
        bool alert();
    
    };


}
