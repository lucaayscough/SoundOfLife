#pragma once


//================================================//
/// Controller class containing all logic for model and view classes.

class Controller
{
public:
    Controller (Model& _model, View& _view);
    ~Controller();

private:
    Model& model;
    View& view;
    
    GridController grid;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controller)
};
