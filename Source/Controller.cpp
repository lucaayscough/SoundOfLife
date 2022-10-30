#include "Headers.h"


Controller::Controller (View& _view, Model& _model)
    :   view(_view), model(_model)
{
}

Controller::~Controller()
{
}
