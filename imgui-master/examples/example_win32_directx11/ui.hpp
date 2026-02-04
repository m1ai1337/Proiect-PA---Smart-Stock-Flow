#include "includes.h"
#include "cfg.hpp"
#include "Produs.hpp"
#include "Tranzactie.hpp"
#include "mypdf.hpp"
#include "data.hpp"

namespace custom_ui {
    inline float scale = 0.90f;
    //de salvat variabilele astea intr un format json probabil
    inline std::list<produs::adauga_produs> lista_produse;
    inline std::list<TR::Tranzactie> tranz;
    inline std::list<std::string> istoric;
    inline float curren_balance = 0.0f;
    static inline float cheltuieli = 0.0f;
    static inline float venituri = 0.0f;

    void render();
}
