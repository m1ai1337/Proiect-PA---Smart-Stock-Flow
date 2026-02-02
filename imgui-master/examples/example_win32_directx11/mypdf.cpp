/*
 * << Haru Free PDF Library 2.0.0 >> -- font_demo.c
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */

 //https://github.com/libharu/libharu/wiki/Examples#user-content-text_democ

#include "mypdf.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <setjmp.h>
#include "hpdf.h"
#include <iostream>

jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler(HPDF_STATUS   error_no,
    HPDF_STATUS   detail_no,
    void* user_data)
{
    printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
        (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

void mypdf::create_pdf(int id, std::string descriere, float val, bool tip)
{
    const char* page_title = "Factura";
    HPDF_Doc  pdf;
    char fname[256];
    HPDF_Page page;
    HPDF_Font def_font;
    HPDF_REAL tw;
    HPDF_REAL height;
    HPDF_REAL width;
    HPDF_UINT i;

    std::string name = "factura_" + std::to_string(id) + ".pdf";
    std::string descriere_text = "Descriere: " + descriere;
    std::string val_text = "Valoare: " + std::to_string(val) + " RON";
    std::string tip_text = std::string("Tip: ") + (tip ? "Venit" : "Cheltuiala");

    pdf = HPDF_New(error_handler, NULL);
    if (!pdf) {
        printf("error: cannot create PdfDoc object\n");
        return;
    }

    if (setjmp(env)) {
        HPDF_Free(pdf);
        return;
    }

    /* Add a new page object. */
    page = HPDF_AddPage(pdf);

    height = HPDF_Page_GetHeight(page);
    width = HPDF_Page_GetWidth(page);

    /* Print the title of the page (with positioning center). */
    def_font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(page, def_font, 24);

    tw = HPDF_Page_TextWidth(page, page_title);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, (width - tw) / 2, height - 50, page_title);
    HPDF_Page_EndText(page);

    /* output subtitle. */ // acum info de la factura
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, def_font, 16);
    HPDF_Page_TextOut(page, 60, height - 80, descriere_text.c_str());
    HPDF_Page_TextOut(page, 60, height - 100, val_text.c_str());
    HPDF_Page_TextOut(page, 60, height - 120, tip_text.c_str());
    HPDF_Page_EndText(page);

    char* userProfile = nullptr;
    size_t len = 0;

    if (_dupenv_s(&userProfile, &len, "USERPROFILE") == 0 && userProfile) {
        std::string path = std::string(userProfile) + "\\Downloads\\"+name;
        HPDF_SaveToFile(pdf, path.c_str());
        free(userProfile);
    }


    /* clean up */
    HPDF_Free(pdf);
}
