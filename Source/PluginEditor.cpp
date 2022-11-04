#include "Headers.h"


//================================================//
// Plugin Editor class.

SoundOfLifeAudioProcessorEditor::SoundOfLifeAudioProcessorEditor (SoundOfLifeAudioProcessor& audioProcessor)
    :   AudioProcessorEditor (&audioProcessor),
        audioProcessor (audioProcessor)
{
    setSize (Variables::windowWidth, Variables::windowHeight);
    startTimer (Variables::refreshRate);
}

SoundOfLifeAudioProcessorEditor::~SoundOfLifeAudioProcessorEditor() {}


//================================================//
// Component class methods.

void SoundOfLifeAudioProcessorEditor::paint (juce::Graphics& graphics)
{
    Grid& grid = audioProcessor.getGrid();
    
    float width = (float)Variables::windowWidth / (float)Variables::numRows;
    float height = (float)Variables::windowHeight / (float)Variables::numColumns;
    
    juce::Colour colour;
    
    graphics.fillAll (juce::Colour (0, 0, 0));
    
    for (int i = 0; i < Variables::numRows; i++)
    {
        for (int j = 0; j < Variables::numColumns; j++)
        {
            Cell& _cell = *grid.getCell (i, j);
            
            if (Variables::useColour)
                colour = juce::Colour (255.0f, 255.0f, 255.0f, _cell.getFade());
            
            else
            {
                if (_cell.getIsAlive())
                    colour = juce::Colours::white;
                else
                    colour = juce::Colours::black;
            }
            
            graphics.setColour(colour);
            graphics.fillRect(i * width, j * height, width, height);
        }
    }
}

void SoundOfLifeAudioProcessorEditor::resized() {}


//================================================//
// Timer class methods.

void SoundOfLifeAudioProcessorEditor::timerCallback()
{
    repaint();
}
