#include "Headers.h"


Grid::Grid()
{
    startTimer(Variables::refreshRate);
}

Grid::~Grid() {}

void Grid::initialize()
{
    for (int i = 0; i < Variables::numRows; i++)
    {
        for (int j = 0; j < Variables::numColumns; j++)
        {
            int _random = random.nextInt (juce::Range<int> (-3, 2));
            if (_random < 0)
                _random = 0;
            
            grid[i][j] = _random;
            
            gridOutput += (juce::String (grid[i][j]) + " ");
        }
        
        gridOutput += "\n";
    }
    
    DBG (gridOutput);
}

void Grid::updateGrid()
{
    DBG ("Updating...");
    
    gridOutput.clear();
    
    for (int row = 0; row < Variables::numRows; row++)
    {
        for (int column = 0; column < Variables::numColumns; column++)
        {
            // Count number of live cells around current cell.
            int numAlive = 0;
            
            // Check cell left.
            if (column > 0)
                if (grid[row][column - 1])
                    numAlive++;
            
            // Check cell right.
            if (column < Variables::numColumns - 1)
                if (grid[row][column + 1])
                    numAlive++;
            
            // Check cell top.
            if (row > 0)
                if (grid[row - 1][column])
                    numAlive++;
                    
            // Check cell top-left.
            if (row > 0 && column > 0)
                if (grid[row - 1][column - 1])
                    numAlive++;
            
            // Check cell top-right.
            if (row > 0 && column < Variables::numColumns - 1)
                if (grid[row - 1][column + 1])
                    numAlive++;
            
            // Check cell bottom.
            if (row < Variables::numRows - 1)
                if (grid[row + 1][column])
                    numAlive++;
            
            // Check cell bottom-left.
            if (row < Variables::numRows - 1 && column > 0)
                if (grid[row + 1][column - 1])
                    numAlive++;
            
            // Check cell bottom-right.
            if (row < Variables::numRows - 1 && column > Variables::numColumns - 1)
                if (grid[row + 1][column + 1])
                    numAlive++;
        
            
            
            // 1) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            // 2) Any live cell with two or three live neighbours lives on to the next generation.
            // 3) Any live cell with more than three live neighbours dies, as if by overpopulation.
            // 4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            
            
            // Calculate state for next iteration.
            
            if (grid[row][column])
            {
                if (numAlive < 2)
                    grid[row][column] = 0;
                
                else if (numAlive > 3)
                    grid[row][column] = 0;
            }
            
            else if (numAlive == 3)
                grid[row][column] = 1;
            
            gridOutput += (juce::String (grid[row][column]) + " ");
        }
        
        gridOutput += "\n";
    }
    
    
    //DBG (gridOutput);
}

float Grid::getCell(int _row, int _column)
{
    return grid[_row][_column];
}

void Grid::timerCallback()
{
    updateGrid();
}
