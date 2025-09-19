#pragma once

#include <cstddef>

struct Cell{
    int x, y;

    bool operator== (const Cell& other) const {
        return x == other.x && y == other.y;
    }
};

struct CellHash {
    std::size_t operator()(const Cell& cell) const {
        constexpr size_t prime1 = 73856093;
        constexpr size_t prime2 = 19349663;
        return (static_cast<std::size_t>(cell.x) * prime1) ^ 
               (static_cast<std::size_t>(cell.y) * prime2);
    }
};