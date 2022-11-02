#include "Headers.h"


//================================================//
// Grid class containing all cells and logic for game of life algorithm.

Grid::Grid()
{
    startTimer(Variables::refreshRate);
    
    initializeCells();
    initializeGrid();
}

Grid::~Grid() {}


//================================================//
// Init methods.


void Grid:: initializeCells()
{
    cells.ensureStorageAllocated(Variables::numRows * Variables::numColumns);
    
    for (int i = 0; i < Variables::numRows * Variables::numColumns; i++)
    {
        cells.add(new Cell());
    }
}

void Grid::initializeGrid()
{
    for (int row = 0; row < Variables::numRows; row++)
    {
        for (int column = 0; column < Variables::numColumns; column++)
        {
            // If cell is a border cell set to dead.
            if (row == 0 || row == Variables::numRows - 1 || column == 0 || column == Variables::numColumns - 1)
                setCellIsAlive (row, column, false);
            
            // Else randomly set to 0 or 1.
            else
            {
                // Generates a random number between [n, 1].
                int _random = random.nextInt (juce::Range<int> (Variables::lowRandomRange, 2));
                
                // This constrains the random number to [0,1].
                // It is used to increase the chances random is 0.
                if (_random < 0)
                    _random = 0;
            
                setCellIsAlive (row, column, _random);
            }
        }
    }
}

//================================================//
// Setter methods.

void Grid::setCellIsAlive (int _row, int _column, bool _isAlive)
{
    getCell(_row, _column)->setIsAlive(_isAlive);
}


//================================================//
// Getter methods.

Cell* Grid::getCell (int _row, int _column)
{
    return cells[_row * Variables::numColumns + _column];
}

bool Grid::getCellIsAlive (int _row, int _column)
{
    return getCell (_row, _column)->getIsAlive();
}


//================================================//
// Grid logic methods.

int Grid::getNumAlive(int _row, int _column)
{
    return (
            getCellIsAlive(_row, _column - 1) +
            getCellIsAlive(_row, _column + 1) +
            getCellIsAlive(_row - 1, _column) +
            getCellIsAlive(_row - 1, _column - 1) +
            getCellIsAlive(_row - 1, _column + 1) +
            getCellIsAlive(_row + 1, _column) +
            getCellIsAlive(_row + 1, _column - 1) +
            getCellIsAlive(_row + 1, _column + 1)
            );
}


//================================================//
// Grid state methods.

void Grid::setNextState(int _row, int _column, int _numAlive)
{
    // 1) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    // 2) Any live cell with two or three live neighbours lives on to the next generation.
    // 3) Any live cell with more than three live neighbours dies, as if by overpopulation.
    // 4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    
    if (getCellIsAlive(_row, _column))
    {
        // Rule 1
        if (_numAlive < 2)
            setCellIsAlive(_row, _column, false);
        
        // Rule 3
        else if (_numAlive > 3)
            setCellIsAlive(_row, _column, false);
    }
    
    // Rule 4
    else if (_numAlive == 3)
        setCellIsAlive(_row, _column, true);
}

void Grid::updateGrid()
{
    for (int row = 1; row < Variables::numRows - 1; row++)
    {
        for (int column = 1; column < Variables::numColumns - 1; column++)
        {
            // Get number of cells alive around current cell.
            int numAlive = getNumAlive(row, column);
            
            // Calculate state for next iteration.
            setNextState(row, column, numAlive);
        }
    }
}


//================================================//
// Timer class methods.

void Grid::timerCallback()
{
    updateGrid();
}
