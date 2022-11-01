#pragma once


//================================================//

class SoundOfLifeAudioProcessorEditor : public juce::AudioProcessorEditor, juce::Timer
{
public:
    SoundOfLifeAudioProcessorEditor (SoundOfLifeAudioProcessor&);
    ~SoundOfLifeAudioProcessorEditor() override;
    
    // Graphics methods.
    void paint (juce::Graphics& _graphics) override;
    void resized() override;
    
    void timerCallback() override;

private:
    SoundOfLifeAudioProcessor& audioProcessor;                                              

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundOfLifeAudioProcessorEditor)
};
