#pragma once

#include <unordered_set>
#include "cell.h"

class Field{
public:
    Field() = default;
    Field( int width, int height );
    void updateField(); // Used for generation
    void updateCell( Cell cell ); // Used for user's input
    void clear();
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getGeneration() const { return m_generation; }
    const std::unordered_set <Cell, CellHash>& getAlive() const { return currentGeneration; }

private:
    std::unordered_set <Cell, CellHash> currentGeneration;
    std::unordered_set <Cell, CellHash> nextGeneration;
    int m_width = 1000, m_height = 1000;
    int m_generation = 0;

    static const int MIN_FIELD_SIZE;
    static const int MAX_FIELD_SIZE;

    bool getCellState( Cell cell ) const;
    int countNeighbours( Cell cell ) const;
};