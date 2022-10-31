#include "Headers.h"


//================================================//
// Controller class.

Controller::Controller (Model& _model, View& _view)
    :   model (_model), view (_view),
        grid (_model.getGrid(), _view.getGrid())
{
    startTimer(1000);
}

Controller::~Controller() {}


//================================================//
// Callback methods.

void Controller::timerCallback()
{
    grid.updateGrid();
}
