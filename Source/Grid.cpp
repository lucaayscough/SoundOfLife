#include "Headers.h"


//================================================//
// Grid class containing all cells and logic for game of life algorithm.

Grid::Grid()
{
    // Starts the timer used to refresh update grid state.
    startTimer (Variables::gridRefreshRate);
    
    // Init cells.
    m_Cells.ensureStorageAllocated(Variables::numRows * Variables::numColumns);
    
    for (int i = 0; i < Variables::numRows * Variables::numColumns; ++i)
        m_Cells.add(new Cell());
    
    for (int row = 0; row < Variables::numRows; ++row)
    {
        for (int column = 0; column < Variables::numColumns; ++column)
        {
            // Generates a random number between [n,1].
            int random = m_Random.nextInt (juce::Range<int> (Variables::lowRandomRange, 2));
            
            // This constrains the random number to [0,1].
            // It is used to increase the chances random is 0.
            if (random < 0)
                random = 0;
        
            setCellIsAlive (row, column, random);
        }
    }
}

Grid::~Grid() {}


//================================================//
// Setter methods.

/**
    Sets the state of a cell to alive or dead.
    @param row Row index of the cell.
    @param column Column index of the cell.
    @param isAlive State of the cell.
 */

void Grid::setCellIsAlive (int row, int column, bool isAlive)
{
    getCell (row, column)->setIsAlive(isAlive);
}


//================================================//
// Getter methods.

/**
    Returns pointer to a cell object.
    @param row Row index of the cell.
    @param column Column index of the cell.
 */

Cell* Grid::getCell (int row, int column)
{
    return m_Cells[row * Variables::numColumns + column];
}

/**
    Returns boolean representing the state of the cell.
    @param row Row index of the cell.
    @param column Column index of the cell.
 */

bool Grid::getCellIsAlive (int row, int column)
{
    // Used to make sure row and column values actually point to existing cell.
    if (row < 0 || column < 0 || row == Variables::numRows || column == Variables::numColumns)
        return 0;
    
    else
        return getCell (row, column)->getIsAlive();
}


//================================================//
// Grid logic methods.

/**
    Returns int representing number of live cells surrounding a given cell.
    @param row Row index of the cell.
    @param column Column index of the cell.
 */

int Grid::getNumAlive(int row, int column)
{
    return (
            getCellIsAlive (row, column - 1) +
            getCellIsAlive (row, column + 1) +
            getCellIsAlive (row - 1, column) +
            getCellIsAlive (row - 1, column - 1) +
            getCellIsAlive (row - 1, column + 1) +
            getCellIsAlive (row + 1, column) +
            getCellIsAlive (row + 1, column - 1) +
            getCellIsAlive (row + 1, column + 1)
            );
}


//================================================//
// Grid state methods.

/**
    Updates the state of a given cell based on the Conway Game of Life algorithm.
    @param row Row index of the cell.
    @param column Column index of the cell.
    @param numAlive Number of live cells.
 */

void Grid::updateCellState(int row, int column, int numAlive)
{
    // 1) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    // 2) Any live cell with two or three live neighbours lives on to the next generation.
    // 3) Any live cell with more than three live neighbours dies, as if by overpopulation.
    // 4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    
    if (getCellIsAlive (row, column))
    {
        // Rule 1
        if (numAlive < 2)
            setCellIsAlive (row, column, false);
        
        // Rule 3
        else if (numAlive > 3)
            setCellIsAlive (row, column, false);
    }
    
    // Rule 4
    else if (numAlive == 3)
        setCellIsAlive (row, column, true);
    
    getCell (row, column)->updateFade();
}

/**
    Updates the state of the entire grid.
 */

void Grid::updateGridState()
{
    for (int row = 0; row < Variables::numRows; ++row)
        for (int column = 0; column < Variables::numColumns; ++column)
            updateCellState (row, column, getNumAlive (row, column));
}


//================================================//
// Timer class methods.

/**
    Inherited from juce::Timer class.
    This is used to regularly update the grid based on a set time interval.
 */

void Grid::timerCallback()
{
    updateGridState();
}
