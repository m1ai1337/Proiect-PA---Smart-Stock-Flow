#include "data.hpp"
#include "ui.hpp"

namespace data {

    void save()
    {
        fs::path base = fs::path(std::getenv("USERPROFILE")) / "OneDrive" / "Documents" / "smart stock flow";
        if (!fs::exists(base)) {
            fs::create_directory(base);
            std::cout << "Directory created: " << base
                << std::endl;
        }
        fs::path file = base / "save.json";

        json j;

        j["balance"] = custom_ui::curren_balance;
        j["tranzactie"] = json::array();

        for (TR::Tranzactie &t : custom_ui::tranz)
        {
            json jt;
            to_json(jt, t);
            j["tranzactie"].push_back(jt);
        }

        j["produse"] = json::array();

        for (produs::adauga_produs& p : custom_ui::lista_produse)
        {
        
        }

        std::ofstream out(file);
        out << j.dump(4) << std::endl;
      
    }
    void load()
    {
        fs::path base = fs::path(std::getenv("USERPROFILE")) / "OneDrive" / "Documents" / "smart stock flow";
        if (!fs::exists(base)) {
            fs::create_directory(base);
            std::cout << "Directory created: " << base
                << std::endl;
        }
        fs::path file = base / "save.json";

        if (!fs::exists(file)) {
            return;
        }

        std::fstream in(file);
        if (!in.is_open())
        {
            return;
        }

        json j;
        in >> j;

        if (j.contains("balance"))
        {
            custom_ui::curren_balance = j.at("balance");
        }

        custom_ui::tranz.clear();
        if (j.contains("tranzactie") && j["tranzactie"].is_array())
        {
            for (const auto& jt : j["tranzactie"])
            {
                TR::Tranzactie t = TR::Tranzactie();
                from_json(jt, t);
                custom_ui::tranz.push_back(t);
            }
        }

       
    }
}
