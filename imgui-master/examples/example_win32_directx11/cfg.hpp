#pragma once
#include <cstdint>
#include "includes.h"

namespace cfg
{
    //pt produs
    inline char nume[128];
    inline float pret;
    inline int stock;
    inline int prag_min;
    inline int vanz_med;
    inline int cantitate;
    inline int old_stock;

   struct prod
   {
        char nume[128];
        float pret;
        int stock;
        int prag_min;
        int vanz_med;
   };
   inline prod edit;

   //pt tranza
   struct tranz
   {
       char descriere[128];
       float val;
       bool type;
   };

   inline tranz v;
   inline tranz e;
}
