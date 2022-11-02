#pragma once


class Cell
{
public:
    Cell();
    ~Cell();
    
    // Setter methods.
    void setIsAlive (bool _isAlive);
    void setFade (float _fade);
    
    // Getter methods.
    bool getIsAlive();
    float getFade();
    
    // State methods.
    void updateFade();
    
private:
    bool isAlive = false;                   // Defines whether the cell is dead or alive.
    float fade = 0.0f;                      
};
