#pragma once


//================================================//

class SoundOfLifeAudioProcessorEditor : public juce::AudioProcessorEditor, juce::Timer
{
public:
    SoundOfLifeAudioProcessorEditor (SoundOfLifeAudioProcessor&);
    ~SoundOfLifeAudioProcessorEditor() override;
    
    // Component class methods.
    void paint (juce::Graphics& graphics) override;
    void resized() override;
    
    // Timer class methods.
    void timerCallback() override;

private:
    SoundOfLifeAudioProcessor& audioProcessor;                                              

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundOfLifeAudioProcessorEditor)
};
