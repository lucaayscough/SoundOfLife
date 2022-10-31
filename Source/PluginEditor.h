#pragma once


//================================================//

class SoundOfLifeAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SoundOfLifeAudioProcessorEditor (SoundOfLifeAudioProcessor&, View&);
    ~SoundOfLifeAudioProcessorEditor() override;
    
    // Graphics methods.
    void paint (juce::Graphics& _graphics) override;
    void resized() override;

private:
    SoundOfLifeAudioProcessor& audioProcessor;                                                  // Reference to audio processor.
    View& view;                                                                                 // Reference to view containing all UI components.

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundOfLifeAudioProcessorEditor)
};
