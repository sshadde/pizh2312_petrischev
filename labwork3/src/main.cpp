#include "args_parser.h"
#include "sandpile.h"
#include "bmp_writer.h"
#include <iostream>
#include <filesystem>
#include <fstream>

int main(int argc, char* argv[]) {
    try {
        Args args = parseArgs(argc, argv);
        Sandpile sandpile;
        
        std::ifstream file(args.input_path);
        std::string line;
        while (std::getline(file, line)) {
            int x, y;
            uint64_t grains;
            if (sscanf(line.c_str(), "%d %d %lu", &x, &y, &grains) != 3) {
                throw std::runtime_error("Invalid input format");
            }
            sandpile.addGrain(x, y, grains);
        }
        
        std::filesystem::create_directories(args.output_dir);
        bool stable = false;
        uint64_t iter = 0;
        
        while (iter < args.max_iter && !stable) {
            if (args.freq > 0 && (iter % args.freq) == 0) {
                const std::string path = args.output_dir + "/iter" + std::to_string(iter) + ".bmp";
                BMPWriter::save(sandpile, path);
            }
            
            sandpile.topple();
            stable = sandpile.isStable();
            iter++;
        }
        
        const std::string final_path = args.output_dir + "/final.bmp";
        BMPWriter::save(sandpile, final_path);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
