#pragma once
#include <cstdint>
#include <string>

struct Args {
    uint16_t length;
    uint16_t width;
    std::string input_path;
    std::string output_dir;
    uint64_t max_iter;
    uint64_t freq;
};

Args parseArgs(int argc, char* argv[]);
