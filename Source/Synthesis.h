#pragma once


//================================================//
/// Synthesis class which takes care of all audio processing.

class Synthesis
{
public:
    Synthesis(Grid& grid);
    ~Synthesis();
    
    // Setter methods.
    void setBlockSize (int blockSize);
    
    // Getter methods.
    int getBlockSize();
    float getColumnGain (int column);
    float getSpectrumGainDecay (float gain, float column);
    
    // AudioBuffer methods.
    void sumBuffers (juce::AudioBuffer<float>& buffer_1, juce::AudioBuffer<float>& buffer_2);
    
    // Init methods.
    void initOscillators();
    void prepareToPlay (float frequency, float sampleRate);
    void prepareToPlay (float frequency, float sampleRate, int blockSize);
    
    // DSP methods.
    float processSample();
    juce::AudioBuffer<float>& processBlock();
    
private:
    juce::OwnedArray<SineOscillator> m_Oscillators;
    juce::AudioBuffer<float> m_Buffer;
    Grid& m_Grid;
    
    int m_BlockSize;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synthesis)
};


