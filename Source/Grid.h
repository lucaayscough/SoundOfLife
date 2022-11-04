#pragma once


/// Grid class containing all cells and logic for game of life algorithm.

class Grid : public juce::Timer
{
public:
    Grid();
    ~Grid();
    
    // Init methods.
    void initializeCells();
    void initializeGrid();
    
    // Setter methods.
    void setCellIsAlive (int row, int column, bool isAlive);
    
    // Getter methods.
    Cell* getCell (int row, int column);
    bool getCellIsAlive (int row, int column);
    
    // Grid logic methods.
    int getNumAlive (int row, int column);
    
    // Grid state methods.
    void updateCellState (int row, int column, int numAlive);
    void updateGridState();
    
    // Timer class methods.
    void timerCallback() override;
    
private:
    juce::OwnedArray<Cell> m_Cells;

    int m_NumCells = Variables::numRows * Variables::numColumns;
    
    juce::Random m_Random;
    juce::String m_GridOutput;
};
