#include "Headers.h"


//================================================//
// Grid class containing all cells and logic for game of life algorithm.

Grid::Grid()
{
    startTimer (Variables::gridRefreshRate);
    
    m_Cells.ensureStorageAllocated(Variables::numRows * Variables::numColumns);
    
    for (int i = 0; i < Variables::numRows * Variables::numColumns; i++)
    {
        m_Cells.add(new Cell());
    }
    
    for (int row = 0; row < Variables::numRows; row++)
    {
        for (int column = 0; column < Variables::numColumns; column++)
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

void Grid::setCellIsAlive (int row, int column, bool isAlive)
{
    getCell (row, column)->setIsAlive(isAlive);
}


//================================================//
// Getter methods.

Cell* Grid::getCell (int row, int column)
{
    return m_Cells[row * Variables::numColumns + column];
}

bool Grid::getCellIsAlive (int row, int column)
{
    if (row < 0 || column < 0 || row == Variables::numRows || column == Variables::numColumns)
        return 0;
    
    else
        return getCell (row, column)->getIsAlive();
}


//================================================//
// Grid logic methods.

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

void Grid::updateGridState()
{
    for (int row = 0; row < Variables::numRows; row++)
    {
        for (int column = 0; column < Variables::numColumns; column++)
        {
            // Get number of cells alive around current cell.
            int numAlive = getNumAlive (row, column);
            
            // Calculate state for next iteration.
            updateCellState (row, column, numAlive);
        }
    }
}


//

float Grid::getDensity()
{
    float density;
    
    float centerX = (float)Variables::numColumns / 2.0f;
    float centerY = (float)Variables::numRows / 2.0f;
    
    float r = std::sqrt (std::powf (centerX, 2.0f) + std::powf (centerY, 2.0f));
    
    float fade = 0;
    float distance = 0;
    float sum = 0;
    
    for (int column = 0; column < Variables::numColumns; ++column)
    {
        for (int row = 0; row < Variables::numRows; ++row)
        {
            fade = getCell (row, column)->getFade();
            distance = std::sqrt (std::powf (centerX - column, 2.0f) + std::powf (centerY - row, 2.0f));
            
            sum += (3.0f / M_PI * fade * std::powf (1.0f - std::powf (distance / r, 2.0f), 2.0f));
        }
    }
    
    // Equation found here:
    // https://doc.arcgis.com/en/insights/latest/analyze/GUID-81BF4C72-7A78-4987-9AB6-E941977D7635-web.png
    density = 1.0f / std::powf (r, 2.0f) * sum;

    return density;
}


//================================================//
// Timer class methods.

void Grid::timerCallback()
{
    updateGridState();
}
