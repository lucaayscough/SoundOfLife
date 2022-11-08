#pragma once


//================================================//
/// Cell class containing internal cell state.

class Cell
{
public:
    Cell();
    ~Cell();
    
    // Setter methods.
    void setIsAlive (bool isAlive);
    void setFade (float fade);
    
    // Getter methods.
    bool getIsAlive();
    float getFade();
    
    // State methods.
    void updateFade();
    
private:
    bool m_IsAlive = false;                     // Defines whether the cell is dead or alive.
    float m_Fade = 0.0f;                        // Used to fade between dead/live states.
};
