#include "field.h"

const int Field::MIN_FIELD_SIZE { 10 };
const int Field::MAX_FIELD_SIZE { 4000 };

Field::Field( int width, int height ) : m_width( width ), m_height( height )
{
    m_width = std::min( MAX_FIELD_SIZE, m_width );
    m_width = std::max( MIN_FIELD_SIZE, m_width );
    m_height = std::min( MAX_FIELD_SIZE, m_height );
    m_height = std::min( MAX_FIELD_SIZE, m_height );
}

bool Field::getCellState( Cell cell ) const
{
    return currentGeneration.contains( cell );
}

int Field::countNeighbours( Cell cell ) const
{
    int res { 0 };
    for ( int dx = -1; dx <= 1 ; ++dx)
    {
        for ( int dy = -1; dy <= 1; ++dy )
        {
            if ( dx == 0 && dy == 0 ) continue;
            Cell neighbour { cell.x + dx, cell.y + dy };
            if ( neighbour.x >= 0 && neighbour.x < m_width && neighbour.y >= 0 && neighbour.x < m_height )
            {
                res += getCellState( neighbour );
            }
        }
    }
    return res;
}

void Field::updateField()
{
    nextGeneration.clear();
    std::unordered_set <Cell, CellHash> toCheck;
    nextGeneration.reserve( currentGeneration.size() * 2 );
    toCheck.reserve( currentGeneration.size() * 9 );

    for ( Cell cell : currentGeneration )
    {
        for ( int dx = -1; dx <= 1 ; ++dx)
        {
            for ( int dy = -1; dy <= 1; ++dy )
            {
                Cell neighbour { cell.x + dx, cell.y + dy };
                if ( neighbour.x >= 0 && neighbour.x < m_width && neighbour.y >= 0 && neighbour.x < m_height )
                {
                    toCheck.insert( neighbour );
                }
            }
        }
    }

    for ( Cell cell : toCheck )
    {
        bool alive = getCellState( cell );
        int cnt = countNeighbours( cell );
        if ( alive && (cnt == 2 || cnt == 3) ){
            nextGeneration.insert( cell );
        }
        else if ( !alive && cnt == 3 ){
            nextGeneration.insert( cell );
        }
    }

    std::swap( currentGeneration, nextGeneration );

    ++m_generation;
}

void Field::updateCell( Cell cell )
{
    if ( cell.x >= 0 && cell.x < m_width && cell.y >= 0 && cell.y < m_height )
    {
        if ( currentGeneration.contains( cell ) ){
            currentGeneration.erase( cell );
        }
        else{
            currentGeneration.insert( cell );
        }
    }
}

void Field::clear()
{
    nextGeneration.clear();
    std::swap( currentGeneration, nextGeneration );
    m_generation = 0;
}