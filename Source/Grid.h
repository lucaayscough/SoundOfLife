#pragma once


class Grid : public juce::Timer
{
public:
    Grid();
    ~Grid();
    
    void initialize();
    
    int getNumAlive(int _row, int _column);
    void setNextState(int _row, int _column, int _numAlive);
    void updateGrid();
    
    float getCell(int _row, int _column);
    
    void timerCallback() override;
    
private:
    float grid[Variables::numRows][Variables::numColumns];
    int numCells = Variables::numRows * Variables::numColumns;
    
    juce::Random random;
    juce::String gridOutput;
};



