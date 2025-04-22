#include "bmp_writer.h"
#include <fstream>
#include <vector>
#include <filesystem>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t type = 0x4D42;
    uint32_t size = 0;
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t offset = 54;
};

struct BMPInfoHeader {
    uint32_t size = 40;
    int32_t width = 0;
    int32_t height = 0;
    uint16_t planes = 1;
    uint16_t bpp = 24;
    uint32_t compression = 0;
    uint32_t img_size = 0;
    int32_t x_ppm = 0;
    int32_t y_ppm = 0;
    uint32_t colors = 0;
    uint32_t important = 0;
};
#pragma pack(pop)

void BMPWriter::save(const Sandpile& sandpile, const std::string& path) {
    BMPFileHeader fh;
    BMPInfoHeader ih;

    const int width = sandpile.getWidth();
    const int height = sandpile.getHeight();
    const int row_size = (width * 3 + 3) & ~3;
    
    fh.size = sizeof(fh) + sizeof(ih) + row_size * height;
    ih.width = width;
    ih.height = height;
    ih.img_size = row_size * height;

    std::ofstream file(path, std::ios::binary);
    file.write(reinterpret_cast<const char*>(&fh), sizeof(fh));
    file.write(reinterpret_cast<const char*>(&ih), sizeof(ih));

    for (int y = 0; y < height; ++y) {
        std::vector<uint8_t> row(row_size, 0);
        const int model_y = sandpile.getMaxY() - y;
        
        for (int x = 0; x < width; ++x) {
            const int model_x = sandpile.getMinX() + x;
            const uint64_t grains = sandpile.getGrains(model_x, model_y);
            
            uint8_t r = 0, g = 0, b = 0;
            if (grains == 0) { r = g = b = 255; }
            else if (grains == 1) { g = 255; }
            else if (grains == 2) { r = 128; b = 128; }
            else if (grains == 3) { r = g = 255; }
            else { r = g = b = 0; }
            
            row[x*3] = b;
            row[x*3 + 1] = g;
            row[x*3 + 2] = r;
        }
        file.write(reinterpret_cast<const char*>(row.data()), row_size);
    }
}
