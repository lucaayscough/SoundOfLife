#pragma once


class SoundOfLifeAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SoundOfLifeAudioProcessorEditor (SoundOfLifeAudioProcessor&, View&);
    ~SoundOfLifeAudioProcessorEditor() override;

    void paint (juce::Graphics& _graphics) override;
    void resized() override;

private:
    SoundOfLifeAudioProcessor& audioProcessor;
    View& view;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundOfLifeAudioProcessorEditor)
};
