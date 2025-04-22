#include "args_parser.h"
#include <stdexcept>
#include <iostream>

Args parseArgs(int argc, char* argv[]) {
    Args args = {};
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-l" || arg == "--length") {
            args.length = static_cast<uint16_t>(std::stoi(argv[++i]));
        } else if (arg == "-w" || arg == "--width") {
            args.width = static_cast<uint16_t>(std::stoi(argv[++i]));
        } else if (arg == "-i" || arg == "--input") {
            args.input_path = argv[++i];
        } else if (arg == "-o" || arg == "--output") {
            args.output_dir = argv[++i];
        } else if (arg == "-m" || arg == "--max-iter") {
            args.max_iter = std::stoull(argv[++i]);
        } else if (arg == "-f" || arg == "--freq") {
            args.freq = std::stoull(argv[++i]);
        }
    }
    if (args.length == 0 || args.width == 0 || 
        args.input_path.empty() || args.output_dir.empty()) {
        throw std::runtime_error("Missing required arguments");
    }
    return args;
}
