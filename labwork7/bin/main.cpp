#include <fstream>
#include <iostream>
#include "ID3Parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file.mp3>\n";
        return 1;
    }
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open " << argv[1] << "\n";
        return 2;
    }
    parseID3v2_4(file);
    return 0;
}

