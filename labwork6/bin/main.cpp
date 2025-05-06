#include "lib/parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::vector<std::string> candidates;
    if (argc > 1) {
        candidates.push_back(argv[1]);
    }

    candidates.push_back("../../example/config.omfl");
    candidates.push_back("../example/config.omfl");
    candidates.push_back("example/config.omfl");

    std::string path;
    std::ifstream fin;
    for (auto& p : candidates) {
        fin.open(p);
        if (fin) {
            path = p;
            break;
        }
    }

    if (!fin) {
        std::cerr << "Ошибка: не удалось найти config.omfl.\n";
        std::cerr << "Пытались:\n";
        for (auto& p : candidates) {
            std::cerr << "  " << p << "\n";
        }
        std::cerr << "Запустите так:\n"
        "  ./lab6 path/to/config.omfl\n";
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(fin)),
                        std::istreambuf_iterator<char>());
    fin.close();

    omfl::Node root = omfl::parse(content);
    if (!root.valid()) {
        std::cerr << "Ошибка: конфиг невалиден.\n";
        std::istringstream iss(content);
        std::string line;
        int ln = 1;
        while (std::getline(iss, line)) {
            std::cerr << (ln < 10 ? " " : "") << ln << " | " << line << "\n";
            ++ln;
        }

        return 1;
    }

    std::cout << "Конфиг успешно распарсен из «" << path << "»\n\n";

    std::cout << "[common]\n";
    std::cout << "name        = "
    << root.Get("common.name").AsStringOrDefault("<no>") << "\n";
    std::cout << "description = "
    << root.Get("common.description").AsStringOrDefault("<no>") << "\n";
    std::cout << "version     = "
    << root.Get("common.version").AsIntOrDefault(0) << "\n\n";

    for (auto srv : { "first", "second" }) {
        std::string base = std::string("servers.") + srv;
        std::cout << "[servers." << srv << "]\n";
        bool en = root.Get(base + ".enabled").AsBoolOrDefault(false);
        std::cout << " enabled = " << (en ? "true" : "false") << "\n";
        std::cout << " ip      = "
        << root.Get(base + ".ip").AsStringOrDefault("<no>") << "\n";

        auto ports = root.Get(base + ".ports");
        std::cout << " ports   = ";
        if (ports.IsArray()) {
            std::cout << "[ ";
            for (size_t i = 0; ; ++i) {
                int p = ports[i].AsIntOrDefault(-1);
                if (p < 0) break;
                std::cout << p;
                if (ports[i+1].AsIntOrDefault(-1) >= 0) std::cout << ", ";
                else std::cout << " ";
            }
            std::cout << "]";
        } else {
            std::cout << "<no ports>";
        }
        std::cout << "\n\n";
    }

    return 0;
}
