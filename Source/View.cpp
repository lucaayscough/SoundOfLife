#include "Headers.h"


View::View()
{
}

View::~View()
{
}

void View::paint (juce::Graphics& _graphics)
{
    _graphics.fillAll (juce::Colours::black);
}

void View::resized()
{
}
