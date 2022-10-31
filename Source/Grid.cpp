#include "Headers.h"


//================================================//
// Grid model class.

GridModel::GridModel() {}

GridModel::~GridModel() {}


//================================================//
// Grid model class.

juce::OwnedArray<CellModel>& GridModel::getCells()                    { return cells; }


//================================================//
// Grid view class.

GridView::GridView() {}

GridView::~GridView() {}


//================================================//
// Component methods.

void GridView::paint (juce::Graphics& _graphics) {}

void GridView::resized()
{
    // Calculate size of cells.
    auto _cellWidth = Variables::windowWidth / Variables::numColumns;
    auto _cellHeight = Variables::windowHeight / Variables::numRows;

    int i = 0;
    
    // Iterate through all cells.
    for (int row = 0; row < Variables::numRows; row++)
    {
        for (int column = 0; column < Variables::numColumns; column++)
        {
            // Set bounds to current cell and make it visible.
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
    constructCellsModel();
    constructCellsView();
}

GridController::~GridController() {}


//================================================//
// Init methods.

/**
    Fills the cells model array with new cells.
 */

void GridController::constructCellsModel()
{
    auto& _cells = gridModel.getCells();
    auto _numCells = Variables::numRows * Variables::numColumns;
    
    // Allocate storage needed to store cells in array.
    _cells.ensureStorageAllocated(_numCells);
    
    // Construct cells and push the into cells array.
    for (int i = 0; i < _numCells; i++)
        _cells.add(new CellModel());
}

/**
    Fills the cells view array with new cells.
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

/**
    Fills the cells controller array with new cells.
 */

void GridController::constructCellsController()
{
    auto& _model = gridModel.getCells();
    auto& _view = gridView.getCells();
    
    auto _numCells = Variables::numRows * Variables::numColumns;
    
    // Allocate storage needed to store cells in array.
    cells.ensureStorageAllocated(_numCells);
    
    // Construct cells and push the into cells array.
    for (int i = 0; i < _numCells; i++)
        cells.add(new CellController(*_model[i], *_view[i]));
}


//================================================//
// Grid update methods.

/**
    Updates the entire view of grid.
 */

void GridController::updateGrid()
{
    DBG ("Updating grid...");

    auto& _cellsModel = gridModel.getCells();
    auto& _cellsView = gridView.getCells();
    
    juce::Random random;
    
    int i = 0;
    
    // Iterate through all cells.
    for (int row = 0; row < Variables::numRows; row++)
    {
        for (int column = 0; column < Variables::numColumns; column++)
        {
            if (random.nextInt (juce::Range<int> (0, 2)))
            {
                _cellsModel[i]->setIsAlive(true);
                _cellsView[i]->setColour (juce::Colours::white);
            }
            
            else
            {
                _cellsModel[i]->setIsAlive(false);
                _cellsView[i]->setColour (juce::Colours::black);
            }
            
            i++;
        }
    }
    
    gridView.repaint();
}
