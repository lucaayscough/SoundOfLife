#include "Headers.h"


//================================================//
// Grid model class.

GridModel::GridModel() {}

GridModel::~GridModel() {}


//================================================//
// Grid view class.

GridView::GridView() {}

GridView::~GridView() {}


//================================================//
// Component methods.

void GridView::paint (juce::Graphics& _graphics) {}

void GridView::resized()
{
    auto _cellWidth = Variables::windowWidth / Variables::numColumns;
    auto _cellHeight = Variables::windowHeight / Variables::numRows;

    int i = 0;
    
    for (int row = 0; row < Variables::numRows; row++)
    {
        for (int column = 0; column < Variables::numColumns; column++)
        {
            cells[i]->setBounds (column * _cellWidth, row * _cellHeight, _cellWidth, _cellHeight);
            addAndMakeVisible(cells[i]);
            
            i++;
        }
    }
}

//================================================//
// Getter methods.

juce::OwnedArray<CellView>& GridView::getCells()                    { return cells; }


//================================================//
// Grid controller class.

GridController::GridController (GridModel& _gridModel, GridView& _gridView)
    :   gridModel (_gridModel), gridView (_gridView)
{
    constructCellsView();
}

GridController::~GridController() {}


//================================================//
// Init methods.

/**
    Fills the cells array with new cells.
 */

void GridController::constructCellsView()
{
    auto& _cells = gridView.getCells();
    auto _numCells = Variables::numRows * Variables::numColumns;
    
    // Allocate storage needed to store cells in array.
    _cells.ensureStorageAllocated(_numCells);
    
    // Construct cells and push the into cells array.
    for (int i = 0; i < _numCells; i++)
        _cells.add(new CellView());
}
