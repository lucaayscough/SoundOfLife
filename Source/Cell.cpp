#include "Headers.h"


//================================================//
// Cell model class.

CellModel::CellModel() {}
CellModel::~CellModel() {}


//================================================//
// Getter methods.

bool CellModel::getIsAlive()
{
    return isAlive;
}


//================================================//
// Setter methods.

void CellModel::setIsAlive (bool _isAlive)
{
    isAlive = _isAlive;
}


//================================================//
// Cell view class.

CellView::CellView() {}

CellView::~CellView() {}


//================================================//
// Component methods.

void CellView::paint (juce::Graphics& _graphics)
{
    _graphics.fillAll (colour);
}

void CellView::resized() {}


//================================================//
// Setter methods.

void CellView::setColour(const juce::Colour& _colour)               { colour = _colour; }


//================================================//
// Cell controller class.

CellController::CellController(CellModel& _model, CellView& _view)
    :   model (_model), view (_view)
{
}

CellController::~CellController() {}


//================================================//
// State methods.

void CellController::setAlive()
{
    
}

void CellController::setDead()
{
    
}
