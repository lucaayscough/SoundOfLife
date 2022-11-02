#include "Headers.h"


//================================================//
// Cell class containing state information.

Cell::Cell() {}

Cell::~Cell() {}


//================================================//
// Setter methods.

void Cell::setIsAlive (bool _isAlive)                               { isAlive = _isAlive; }
void Cell::setFade (float _fade)                                    { fade = _fade; }


//================================================//
// Getter methods.

bool Cell::getIsAlive()                                             { return isAlive; }
float Cell::getFade()                                               { return fade; }


//================================================//
// State methods.

void Cell::updateFade()
{
    if (isAlive && fade < 1.0f)
    {
        fade += Variables::fadeAmount;
    }
    
    else if (!isAlive && fade > 0.0f)
    {
        fade -= Variables::fadeAmount;
    }
}
