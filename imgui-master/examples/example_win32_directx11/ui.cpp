#include "ui.hpp"


void custom_ui::render()
{
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse;

    ImGuiStyle* style = &ImGui::GetStyle();
    ImGui::StyleColorsClassic();
    ImGuiIO& io = ImGui::GetIO();
   
    io.FontGlobalScale = scale;
    style->FrameRounding = 5.0f;
    style->TabRounding = 5.0f;
    style->ScrollbarSize = 6.f;
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(50 / 255.f, 50 / 255.f, 50 / 255.f, 1.f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(70 / 255.f, 70 / 255.f, 70 / 255.f, 1.f);
    ImGui::Begin("smart stock flow", 0, flags);
    ImVec2 size = ImGui::GetWindowSize();
    ImGui::BeginTabBar("#tabs");
    if (ImGui::BeginTabItem("Dashboard")) {
        if (ImGui::BeginChild("Overview")) {
            ImGui::SeparatorText("Overview");
            if (ImGui::BeginTable("##Gestionare Stocuri", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
            {
                ImGui::TableSetupColumn("Fonduri");
                ImGui::TableSetupColumn("Venituri");
                ImGui::TableSetupColumn("Cheltuieli");
                ImGui::TableHeadersRow();
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0); ImGui::Text("%.0f RON", custom_ui::curren_balance);
                ImGui::TableSetColumnIndex(1); ImGui::Text("%.0f RON", custom_ui::venituri);
                ImGui::TableSetColumnIndex(2); ImGui::Text("%.0f RON", custom_ui::cheltuieli);
                ImGui::EndTable();
            }
            ImGui::SeparatorText("Alerte Stock");
            if (ImGui::BeginTable("##Alerte Stock", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingStretchProp))
            {
                ImGui::TableSetupColumn("Nr.");
                ImGui::TableSetupColumn("Nume");
                ImGui::TableSetupColumn("Pret");
                ImGui::TableSetupColumn("Stock");
                ImGui::TableSetupColumn("Vanzari medii");
                ImGui::TableSetupColumn("Timp de livrare");
                ImGui::TableSetupColumn("Informatii");
                ImGui::TableSetupColumn("Buy");
                ImGui::TableHeadersRow();

                int cnt = 0;
                for (produs::adauga_produs& p : lista_produse)
                {
                    if (p.alert())
                    {
                        cnt++;
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0); ImGui::Text("%d", cnt);
                        ImGui::TableSetColumnIndex(1); ImGui::Text("%s", p.get_nume().c_str());
                        ImGui::TableSetColumnIndex(2); ImGui::Text("%.0f RON", p.get_price());
                        ImGui::TableSetColumnIndex(3); ImGui::Text("%d", p.get_stock());
                        ImGui::TableSetColumnIndex(4); ImGui::Text("%d/sapt.", p.get_medie());
                        ImGui::TableSetColumnIndex(5); ImGui::Text("%d sapt.", p.get_prag_min());
                        ImGui::TableSetColumnIndex(6); ImGui::Text("Urmeaza sa rama fara stock in %.0f de sapt.!", (float)p.get_stock() / p.get_medie());
                        ImGui::TableSetColumnIndex(7);

                        ImGui::PushID(cnt);
                        if (ImGui::Button("Buy ##stock"))
                        {
                            ImGui::OpenPopup("buy stock");
                            cfg::cantitate = abs(p.get_medie() - p.get_stock()) * (int)p.get_stock() / p.get_medie();
                            cfg::old_stock = p.get_stock();
                        }
                        if (ImGui::BeginPopup("buy stock"))
                        {

                            ImGui::TextUnformatted("Nr de bucati");
                            ImGui::InputInt("##Stock", &cfg::cantitate);
                            ImGui::Spacing();
                            if (ImGui::Button("Cumpara"))
                            {
                                if (custom_ui::curren_balance - p.get_price()*cfg::cantitate >= 0)
                                {
                                    p.set_stock(cfg::old_stock + cfg::cantitate);
                                    custom_ui::curren_balance -= p.get_price() * cfg::cantitate;
                                    ImGui::CloseCurrentPopup();
                                }
                                else
                                {
                                    ImGui::OpenPopup("Fonduri insuficiente");
                                }
                                
                            }
                            if (ImGui::BeginPopup("Fonduri insuficiente"))
                            {
                                ImGui::Text("Mai ai nevoie de %.0f RON", abs(custom_ui::curren_balance - p.get_price() * cfg::cantitate));
                                ImGui::EndPopup();
                            }

                            ImGui::EndPopup();
                        }
                        ImGui::PopID();
                    }
                }

                ImGui::EndTable();
            }

        } ImGui::EndChild();

        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Stocks")) {

        if (ImGui::BeginChild("Adauga Produs", ImVec2(size.x * 0.4f - 15, size.y))) {
            ImGui::SeparatorText("Adauga Produs");
            ImGui::TextUnformatted("Nume");
            ImGui::InputText("##Nume", cfg::nume, IM_COUNTOF(cfg::nume));
            ImGui::TextUnformatted("Pret");
            ImGui::InputFloat("##Pret", &cfg::pret, 1.0f);
            ImGui::TextUnformatted("Stock");
            ImGui::InputInt("##Stock", &cfg::stock);
            ImGui::TextUnformatted("Vanzari medii pe saptamana");
            ImGui::InputInt("##Vanzari medii pe saptamana", &cfg::vanz_med);
            ImGui::TextUnformatted("Timp de livare");
            ImGui::InputInt("##Timp de livare", &cfg::prag_min);

            ImGui::Spacing();
            if (ImGui::Button("Adauga Produs"))
            {
                if (cfg::nume[0] != '\0')
                {
                    lista_produse.push_back(produs::adauga_produs(cfg::pret, std::string(cfg::nume), cfg::stock, cfg::vanz_med, cfg::prag_min));
                    std::strncpy(cfg::nume, "", sizeof(cfg::nume) - 1);
                    cfg::nume[sizeof(cfg::nume) - 1] = '\0';
                    cfg::stock = 0;
                    cfg::pret = 0.0f; 
                    cfg::prag_min = 0;
                    cfg::vanz_med = 0;
                }
                else
                {
                    ImGui::OpenPopup("Invalid");
                }
            }
            if (ImGui::BeginPopup("Invalid"))
            {
                ImGui::TextUnformatted("Introduce un nume valid!");
                ImGui::EndPopup();
            }
            
        } ImGui::EndChild();


        ImGui::SameLine(0.0f, 15);

        if (ImGui::BeginChild("Gestionare Stocuri", ImVec2(size.x * 0.6f - 15, size.y)))
        {
            ImGui::SeparatorText("Gestionare Stocuri");
            if (ImGui::BeginTable("##Gestionare Stocuri", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingStretchProp)) {
                ImGui::TableSetupColumn("Nr.");
                ImGui::TableSetupColumn("Nume");
                ImGui::TableSetupColumn("Pret");
                ImGui::TableSetupColumn("Stock");
                ImGui::TableSetupColumn("Vanzari medii");
                ImGui::TableSetupColumn("Timp de livare");
                ImGui::TableSetupColumn("Edit");
                ImGui::TableHeadersRow();
                int cnt = 0;
                int index_del = -1;
                for (produs::adauga_produs &prod : lista_produse)
                {
                    cnt++;
                   
                    char nume[128];
                    std::strncpy(nume, prod.get_nume().c_str(), sizeof(nume) - 1);
                    nume[sizeof(nume) - 1] = '\0';

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("%d", cnt);
                    ImGui::TableSetColumnIndex(1); ImGui::Text("%s", nume);
                    ImGui::TableSetColumnIndex(2); ImGui::Text("%.2f RON", prod.get_price());
                    ImGui::TableSetColumnIndex(3); ImGui::Text("%d", prod.get_stock());
                    ImGui::TableSetColumnIndex(4); ImGui::Text("%d/sapt.", prod.get_medie());
                    ImGui::TableSetColumnIndex(5); ImGui::Text("%d sapt.", prod.get_prag_min());
                    ImGui::TableSetColumnIndex(6);
                    ImGui::PushID(cnt);
                    if (ImGui::Button("Edit ##stock"))
                    {
                        ImGui::OpenPopup("Edit Window");
                        std::strncpy(cfg::edit.nume, prod.get_nume().c_str(), sizeof(cfg::edit.nume) - 1);
                        cfg::edit.nume[sizeof(cfg::edit.nume) - 1] = '\0';
                        cfg::edit.pret = prod.get_price();
                        cfg::edit.stock = prod.get_stock();
                        cfg::edit.prag_min = prod.get_prag_min();
                        cfg::edit.vanz_med = prod.get_medie();

                    }
                    if (ImGui::BeginPopup("Edit Window"))
                    {
                        
                        ImGui::TextUnformatted("Nume");
                        ImGui::InputText("##Nume", cfg::edit.nume, IM_COUNTOF(cfg::edit.nume));
                        ImGui::TextUnformatted("Pret");
                        ImGui::InputFloat("##Pret", &cfg::edit.pret, 1.0f);
                        ImGui::TextUnformatted("Stock");
                        ImGui::InputInt("##Stock", &cfg::edit.stock);
                        ImGui::TextUnformatted("Vanzari medii pe saptamana");
                        ImGui::InputInt("##Vanzari medii pe saptamana", &cfg::edit.vanz_med);
                        ImGui::TextUnformatted("Timp de livare");
                        ImGui::InputInt("##Timp de livare", &cfg::edit.prag_min);
                        ImGui::Spacing();
                        if (ImGui::Button("Save"))
                        {
                            prod.set_prag_min(cfg::edit.prag_min);
                            prod.set_stock(cfg::edit.stock);
                            prod.set_price(cfg::edit.pret);
                            prod.set_medie(cfg::edit.vanz_med);
                            prod.set_string(std::string(cfg::edit.nume));
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Delete"))
                        {
                            index_del = cnt - 1;
                            ImGui::CloseCurrentPopup();
                        }
                       
                        ImGui::EndPopup();
                    }
                    
                    ImGui::PopID();
                   
                    
                }
                if (index_del != -1)
                {
                    auto it = lista_produse.begin();
                    std::advance(it, index_del);
                    lista_produse.erase(it);
                    index_del = -1;
                }
                ImGui::EndTable();
                
            }
            
        } ImGui::EndChild();

        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Cashflow")) {
        if (ImGui::BeginChild("Adauga Tranzactie", ImVec2(size.x * 0.4f - 15, size.y))) {
            ImGui::SeparatorText("Adauga Tranzactie");
            ImGui::TextUnformatted("Descriere");
            ImGui::InputText("##Descriere", cfg::v.descriere, IM_COUNTOF(cfg::v.descriere));
            ImGui::TextUnformatted("Valoare");
            ImGui::InputFloat("##Valoare", &cfg::v.val, 1.0f);
            const char* items[] = { "Venit", "Cheltuiala"};
            static int item_current = 0;
            cfg::v.type = item_current == 0 ? true : false;
            ImGui::TextUnformatted("Tip");
            ImGui::Combo("##Tip", &item_current, items, IM_COUNTOF(items));
            ImGui::Spacing();
            if (ImGui::Button("Adauga Tranzactie"))
            {
                if (cfg::v.descriere[0]!= '\0')
                {
                    tranz.push_back(TR::Tranzactie(std::string(cfg::v.descriere), cfg::v.val, cfg::v.type));
                    item_current = 0;
                    cfg::v.val = 0;
                    std::strncpy(cfg::v.descriere, "", sizeof(cfg::v.descriere) - 1);
                    cfg::v.descriere[sizeof(cfg::v.descriere) - 1] = '\0';
                }
                else
                {
                    ImGui::OpenPopup("Invalid Cashflow");
                }
                
            }
            if (ImGui::BeginPopup("Invalid Cashflow"))
            {
                ImGui::TextUnformatted("Adauga o descriere valida!");

                ImGui::EndPopup();
            }

            ImGui::SeparatorText("Fonduri");
            ImGui::Text("Fonduri curente: %.2f RON", custom_ui::curren_balance);
            ImGui::TextUnformatted("Adauga Fonduri");
            ImGui::InputFloat("##Adauga Fonduri", &custom_ui::curren_balance, 1.0f);
            
        } ImGui::EndChild();

        ImGui::SameLine(0.0f, 15);

        if (ImGui::BeginChild("##Gestionare Tranzactii", ImVec2(size.x * 0.6f - 15, size.y)))
        {
            ImGui::SeparatorText("Gestionare Tranzactii");
            if (ImGui::BeginTable("##Gestionare Tranzactii", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
            {
                ImGui::TableSetupColumn("Nr.");
                ImGui::TableSetupColumn("Descriere");
                ImGui::TableSetupColumn("Valoare");
                ImGui::TableSetupColumn("Tip");
                ImGui::TableSetupColumn("Edit");
                ImGui::TableSetupColumn("Factura");
                ImGui::TableHeadersRow();

                int cnt = 0;
                int index_del = -1;
                for (TR::Tranzactie& t : tranz)
                {
                    cnt++;

                    char descriere[128];
                    std::strncpy(descriere, t.get_descriere().c_str(), sizeof(descriere) - 1);
                    descriere[sizeof(descriere) - 1] = '\0';

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("%d", cnt);
                    ImGui::TableSetColumnIndex(1); ImGui::Text("%s", descriere);
                    ImGui::TableSetColumnIndex(2); ImGui::Text("%.2f RON", t.get_val());
                    ImGui::TableSetColumnIndex(3); ImGui::Text("%s", (t.get_type() == false ? "Cheltuiala" : "Venit"));
                    ImGui::TableSetColumnIndex(4);  
                    ImGui::PushID(cnt);
                    if (ImGui::Button("Edit ##edit tranz"))
                    {
                        ImGui::OpenPopup("Edit Window");
                        std::strncpy(cfg::e.descriere, t.get_descriere().c_str(), sizeof(cfg::e.descriere) - 1);
                        cfg::e.descriere[sizeof(cfg::e.descriere) - 1] = '\0';
                        cfg::e.val = t.get_val();
                        cfg::e.type = t.get_type();
                    }

                    if (ImGui::BeginPopup("Edit Window"))
                    {

                        ImGui::TextUnformatted("Descriere");
                        ImGui::InputText("##Descriere", cfg::e.descriere, IM_COUNTOF(cfg::e.descriere));
                        ImGui::TextUnformatted("Valoare");
                        ImGui::InputFloat("##Valoare", &cfg::e.val, 1.0f);
                        const char* e_items[] = { "Venit", "Cheltuiala" };
                        int e_item_current = cfg::e.type == false ? 1 : 0;
                        ImGui::TextUnformatted("Tip");
                        ImGui::Combo("##Tip", &e_item_current, e_items, IM_COUNTOF(e_items));
                        ImGui::Spacing();
                        if (ImGui::Button("Save"))
                        {
                            t.set_descriere(std::string(cfg::e.descriere));
                            t.set_val(cfg::e.val);
                            t.set_type(e_item_current);
                            ImGui::CloseCurrentPopup();
                            
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Delete"))
                        {
                            index_del = cnt - 1;
                            ImGui::CloseCurrentPopup();
                        }

                        ImGui::EndPopup();
                    }

                    ImGui::TableSetColumnIndex(5);
                    if (ImGui::Button("Download"))
                    {
                        mypdf::create_pdf(cnt, t.get_descriere(), t.get_val(), t.get_type());
                    }

                    ImGui::PopID();

                    
                }
                if (index_del != -1)
                {
                    auto it = tranz.begin();
                    std::advance(it, index_del);
                    tranz.erase(it);
                    index_del = -1;
                }



                ImGui::EndTable();
            }
            
        } ImGui::EndChild();
       
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Misc")) {

        if (ImGui::BeginChild("Istoric", ImVec2(size.x * 0.5f - 15, size.y))) {
            ImGui::SeparatorText("Istoric");
           
           
        }  ImGui::EndChild();
       

        ImGui::SameLine(0.0f, 15);

        if (ImGui::BeginChild("Misc", ImVec2(size.x * 0.5f - 15, size.y))) {
            ImGui::SeparatorText("Misc");
            ImGui::TextUnformatted("Scale");
            ImGui::SliderFloat("##Scale", &custom_ui::scale, 0.5f, 3.5f, "ratio = %.2f");
            ImGui::Spacing();
            if (ImGui::Button("         Load        "))
            {
                data::load();
            }
            ImGui::Spacing();
            if (ImGui::Button("         Save        "))
            {
                ImGui::OpenPopup("Confirm Save");
                
            }
            if (ImGui::BeginPopup("Confirm Save"))
            {
                if (ImGui::Button("         Yes        "))
                {
                    data::save();
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine(0, 15.0f);
                if (ImGui::Button("         No         "))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
           
            
        } ImGui::EndChild();


        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
    ImGui::End();



}



