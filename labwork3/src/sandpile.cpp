#include "sandpile.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Sandpile::Sandpile() : min_x_(0), max_x_(0), min_y_(0), max_y_(0) {}

void Sandpile::updateBounds(int x, int y) {
    if (cells_.empty()) {
        min_x_ = max_x_ = x;
        min_y_ = max_y_ = y;
    } else {
        min_x_ = std::min(min_x_, x);
        max_x_ = std::max(max_x_, x);
        min_y_ = std::min(min_y_, y);
        max_y_ = std::max(max_y_, y);
    }
}

void Sandpile::addGrain(int x, int y, uint64_t count) {
    cells_[{x, y}] += count;
    updateBounds(x, y);
}

uint64_t Sandpile::getGrains(int x, int y) const {
    auto it = cells_.find({x, y});
    return (it != cells_.end()) ? it->second : 0;
}

void Sandpile::topple() {
    std::map<std::pair<int, int>, uint64_t> new_cells;
    const std::vector<std::pair<int, int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    for (const auto& [pos, grains] : cells_) {
        int x = pos.first, y = pos.second;
        if (grains < 4) {
            new_cells[pos] += grains;
        } else {
            new_cells[pos] += grains % 4;
            for (const auto& d : dirs) {
                int nx = x + d.first;
                int ny = y + d.second;
                new_cells[{nx, ny}] += grains / 4;
            }
        }
    }
    
    cells_.swap(new_cells);
    min_x_ = max_x_ = min_y_ = max_y_ = 0;
    for (const auto& [pos, _] : cells_) updateBounds(pos.first, pos.second);
}

bool Sandpile::isStable() const {
    for (const auto& [_, grains] : cells_) 
        if (grains >= 4) return false;
    return true;
}

// Getters implementation
int Sandpile::getWidth() const { return max_x_ - min_x_ + 1; }
int Sandpile::getHeight() const { return max_y_ - min_y_ + 1; }
int Sandpile::getMinX() const { return min_x_; }
int Sandpile::getMaxX() const { return max_x_; }
int Sandpile::getMinY() const { return min_y_; }
int Sandpile::getMaxY() const { return max_y_; }
