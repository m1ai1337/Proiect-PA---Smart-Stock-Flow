#include "includes.h"
#include "json.hpp"
using json = nlohmann::json;

namespace produs {
    class adauga_produs
    {
    protected:
        float price;
        std::string nume;
        int stock;
        int medie_vanz; // vanzari med pe sapt
        int timp; // timp de livrare

    public:
        adauga_produs(float price, std::string nume, int stock, int medie_vanz, int timp);
        adauga_produs();
        ~adauga_produs();

        //get
        float get_price();
        int get_stock();
        int get_prag_min();
        int get_medie();
        std::string get_nume();

        //set
        void set_price(float price);
        void set_stock(int stock);
        void set_medie(int medie_vanz);
        void set_prag_min(int timp);
        void set_string(std::string nume);
        //other func
        bool alert();
        friend void to_json(json& j, const adauga_produs& p);
        friend void from_json(const json& j, adauga_produs& p);
    };


}
