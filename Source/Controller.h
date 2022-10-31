#pragma once


//================================================//
/// Controller class containing all logic for model and view classes.

class Controller : private juce::Timer
{
public:
    Controller (Model& _model, View& _view);
    ~Controller();

private:
    // Callback methods.
    void timerCallback() override;
    
private:
    Model& model;
    View& view;
    
    GridController grid;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controller)
};
