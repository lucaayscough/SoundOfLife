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
    float getColumnPan (int column);
    float getSpectralGainDecay (float gain, float column, float frequency);
    
    // State methods.
    void updateFadeValues (int column);
    
    // Init methods.
    void prepareToPlay (float frequency, float sampleRate, int blockSize);
    
    // DSP methods.
    void processBlock (juce::AudioBuffer<float>& buffer);
    
private:
    juce::OwnedArray<TriangleOscillator> m_Oscillators;
    
    Panner m_Panner;
    juce::Reverb m_Reverb;
    
    Grid& m_Grid;
    
    int m_BlockSize;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synthesis)
};


