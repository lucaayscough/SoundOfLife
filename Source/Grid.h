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
    void setCellIsAlive (int _row, int _column, bool _isAlive);
    
    // Getter methods.
    Cell* getCell (int _row, int _column);
    bool getCellIsAlive (int _row, int _column);
    
    // Grid logic methods.
    int getNumAlive (int _row, int _column);
    
    // Grid state methods.
    void setNextState (int _row, int _column, int _numAlive);
    void updateGrid();
    
    // Timer class methods.
    void timerCallback() override;
    
private:
    juce::OwnedArray<Cell> cells;

    int numCells = Variables::numRows * Variables::numColumns;
    
    juce::Random random;
    juce::String gridOutput;
};



