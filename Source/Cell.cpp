#include "Headers.h"


//================================================//
// Cell class containing state information.

Cell::Cell() {}

Cell::~Cell() {}


//================================================//
// Setter methods.

void Cell::setIsAlive (bool _isAlive) { isAlive = _isAlive; }


//================================================//
// Getter methods.

bool Cell::getIsAlive() { return isAlive; }
