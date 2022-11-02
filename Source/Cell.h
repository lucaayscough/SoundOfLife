#pragma once


class Cell
{
public:
    Cell();
    ~Cell();
    
    // Setter methods.
    void setIsAlive (bool _isAlive);
    
    // Getter methods.
    bool getIsAlive();
    
private:
    bool isAlive = false;                   // Defines whether the cell is dead or alive.
    float fade = 0.0f;                      
};
