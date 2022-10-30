#pragma once


class Controller
{
public:
    Controller (View& _view, Model& _model);
    ~Controller();

private:
    View& view;
    Model& model;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controller)
};
