#include "Headers.h"


//================================================//
// View class.

View::View()
{
    addAndMakeVisible (grid);
}

View::~View() {}


//================================================//
// Component methods.

void View::paint (juce::Graphics& _graphics)
{
    _graphics.fillAll (juce::Colours::black);
}

void View::resized()
{
    grid.setBounds (getLocalBounds());
}


//================================================//
// View class.

GridView& View::getGrid()                                           { return grid; }
