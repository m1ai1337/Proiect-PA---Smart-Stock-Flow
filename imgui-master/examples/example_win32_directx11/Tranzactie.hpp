#include "includes.h"
#include "json.hpp"
using json = nlohmann::json;

namespace TR {
    class Tranzactie
    {
    private:
        std::string descriere;
        float val;
        bool type; //true pt venit si false pt cheltuieli
    public:
        Tranzactie();
        Tranzactie(std::string descriere, float val, bool type);
        ~Tranzactie();

        //get
        float get_val();
        bool get_type();
        std::string get_descriere();

        //set
        void set_val(float val);
        void set_type(bool type);
        void set_descriere(std::string descriere);
        friend void to_json(json& j, const Tranzactie& p);
        friend void from_json(const json& j, Tranzactie& p);
    };
}
