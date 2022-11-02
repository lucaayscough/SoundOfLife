#include "Headers.h"


Grid::Grid()
{
    startTimer(Variables::refreshRate);
}

Grid::~Grid() {}

void Grid::initialize()
{
    // TODO:
    // Make this initalize a frame of dead cells.
    
    
    for (int row = 0; row < Variables::numRows; row++)
    {
        for (int column = 0; column < Variables::numColumns; column++)
        {
            
            // If cell is a border cell set to dead.
            if (row == 0 || row == Variables::numRows - 1 || column == 0 || column == Variables::numColumns - 1)
            {
                grid[row][column] = 0;
            }
            
            // Else randomly set to 0 or 1.
            else
            {
                int _random = random.nextInt (juce::Range<int> (Variables::lowRandomRange, 2));
                if (_random < 0)
                    _random = 0;
            
                grid[row][column] = _random;
            }
        }
    }
}

int Grid::getNumAlive(int _row, int _column)
{
    return (
            grid[_row][_column - 1]     +
            grid[_row][_column + 1]     +
            grid[_row - 1][_column]     +
            grid[_row - 1][_column - 1] +
            grid[_row - 1][_column + 1] +
            grid[_row + 1][_column]     +
            grid[_row + 1][_column - 1] +
            grid[_row + 1][_column + 1]
            );
}

void Grid::setNextState(int _row, int _column, int _numAlive)
{
    // 1) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    // 2) Any live cell with two or three live neighbours lives on to the next generation.
    // 3) Any live cell with more than three live neighbours dies, as if by overpopulation.
    // 4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    
    if (grid[_row][_column])
    {
        // Rule 1
        if (_numAlive < 2)
            grid[_row][_column] = 0;
        
        // Rule 3
        else if (_numAlive > 3)
            grid[_row][_column] = 0;
    }
    
    // Rule 4
    else if (_numAlive == 3)
        grid[_row][_column] = 1;
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

float Grid::getCell(int _row, int _column)
{
    return grid[_row][_column];
}

void Grid::timerCallback()
{
    updateGrid();
}
