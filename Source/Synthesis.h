#pragma once


class Synthesis
{
public:
    Synthesis(Grid& grid);
    ~Synthesis();
    
    void initOscillators();
    
    void setBlockSize (int blockSize);
    int getBlockSize();
    
    void prepareToPlay (float frequency, float sampleRate);
    void prepareToPlay (float frequency, float sampleRate, int blockSize);
    float processSample();
    juce::AudioBuffer<float>& processBlock();
    
private:
    juce::OwnedArray<SineOscillator> m_Oscillators;
    juce::AudioBuffer<float> m_Buffer;
    Grid& m_Grid;
    
    int m_BlockSize;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synthesis)
};
