#pragma once
#include <map>
#include <vector>
#include <cstdint>

class Sandpile {
    std::map<std::pair<int, int>, uint64_t> cells_;
    int min_x_, max_x_, min_y_, max_y_;

    void updateBounds(int x, int y);
    
public:
    Sandpile();
    void addGrain(int x, int y, uint64_t count);
    uint64_t getGrains(int x, int y) const;
    void topple();
    bool isStable() const;
    
    int getWidth() const;
    int getHeight() const;
    int getMinX() const;
    int getMaxX() const;
    int getMinY() const;
    int getMaxY() const;
};
