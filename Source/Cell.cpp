#include "Headers.h"


//================================================//
// Cell model class.

CellModel::CellModel() {}

CellModel::~CellModel() {}


//================================================//
// Cell view class.

CellView::CellView() {}

CellView::~CellView() {}


//================================================//
// Component methods.

void CellView::paint (juce::Graphics& _graphics)
{
    _graphics.fillAll (juce::Colours::white);
}

void CellView::resized() {}


//================================================//
// Cell controller class.

CellController::CellController() {}

CellController::~CellController() {}
