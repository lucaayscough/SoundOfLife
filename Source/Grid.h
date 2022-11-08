#pragma once

//================================================//
/// Grid class containing all cells and logic for game of life algorithm.

class Grid : public juce::Timer
{
public:
    Grid();
    ~Grid();
    
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
    juce::OwnedArray<Cell> m_Cells;                                         // Array containing cell objects.
    int m_NumCells = Variables::numRows * Variables::numColumns;            // Number of cells.
    juce::Random m_Random;                                                  // Random object used to generate random values.
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Grid)
};
