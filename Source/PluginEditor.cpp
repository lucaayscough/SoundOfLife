#include "Headers.h"


//================================================//
// Plugin Editor class.

SoundOfLifeAudioProcessorEditor::SoundOfLifeAudioProcessorEditor (SoundOfLifeAudioProcessor& _audioProcessor, View& _view)
    :   AudioProcessorEditor (&_audioProcessor),
        audioProcessor (_audioProcessor),
        view (_view)
{
    setSize (Variables::windowWidth, Variables::windowHeight);
    addAndMakeVisible (view);
}

SoundOfLifeAudioProcessorEditor::~SoundOfLifeAudioProcessorEditor() {}


//================================================//

void SoundOfLifeAudioProcessorEditor::paint (juce::Graphics& _graphics){}

void SoundOfLifeAudioProcessorEditor::resized()
{
    // Sets the bounds for the entire view.
    view.setBounds(getLocalBounds());
}
