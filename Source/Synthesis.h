#pragma once


class Synthesis
{
public:
    Synthesis(Grid& _grid);
    ~Synthesis();
    
    void initOscillators();
    void prepareToPlay (float _frequency, float _sampleRate);
    float processSample();
    
private:
    juce::OwnedArray<TriangleOscillator> oscillators;
    Grid& grid;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synthesis)
};
