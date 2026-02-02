#include "includes.h"

namespace TR {
    class Tranzactie
    {
    private:
        std::string descriere;
        float val;
        bool type; //true pt venit si false pt cheltuieli
    public:
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
    };
}
