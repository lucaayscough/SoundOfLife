#include "Headers.h"


//================================================//
// Cell class containing state information.

Cell::Cell() {}

Cell::~Cell() {}


//================================================//
// Setter methods.

void Cell::setIsAlive (bool isAlive)                                { m_IsAlive = isAlive; }
void Cell::setFade (float fade)                                     { m_Fade = fade; }


//================================================//
// Getter methods.

bool Cell::getIsAlive()                                             { return m_IsAlive; }
float Cell::getFade()                                               { return m_Fade; }


//================================================//
// State methods.

/**
    Updates cell fade value.
 */

void Cell::updateFade()
{
    if (m_IsAlive && m_Fade < 1.0f)
        m_Fade += Variables::fadeAmount;
    
    else if (!m_IsAlive && m_Fade > 0.0f)
        m_Fade -= Variables::fadeAmount;
}
