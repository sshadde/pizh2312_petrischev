#pragma once
#include "sandpile.h"
#include <string>

class BMPWriter {
public:
    static void save(const Sandpile& sandpile, const std::string& path);
};
