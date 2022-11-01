#include "Headers.h"


//================================================//
// Plugin Editor class.

SoundOfLifeAudioProcessorEditor::SoundOfLifeAudioProcessorEditor (SoundOfLifeAudioProcessor& _audioProcessor)
    :   AudioProcessorEditor (&_audioProcessor),
        audioProcessor (_audioProcessor)
{
    setSize (Variables::windowWidth, Variables::windowHeight);
    startTimer(Variables::refreshRate);
}

SoundOfLifeAudioProcessorEditor::~SoundOfLifeAudioProcessorEditor() {}


//================================================//

void SoundOfLifeAudioProcessorEditor::paint (juce::Graphics& _graphics)
{
    Grid& _grid = audioProcessor.getGrid();
    float _width = Variables::windowWidth / Variables::numRows;
    float _height = Variables::windowHeight / Variables::numColumns;
    
    for (int i = 0; i < Variables::numRows; i++)
    {
        for (int j = 0; j < Variables::numColumns; j++)
        {
            
            juce::Colour colour;
            
            if (_grid.getCell(i, j))
                colour = juce::Colours::white;
            else
                colour = juce::Colours::black;
            
            _graphics.setColour(colour);
            _graphics.fillRect(i * _width, j * _height, _width, _height);
        }
    }
}

void SoundOfLifeAudioProcessorEditor::resized()
{
}

void SoundOfLifeAudioProcessorEditor::timerCallback()
{
    repaint();
}
