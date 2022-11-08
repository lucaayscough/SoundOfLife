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
    float getOscillatorGain (int oscillatorIndex);
    float getOscillatorPan (int oscillatorIndex);
    float getSpectralGainDecay (float gain, float frequency);
    
    // State methods.
    void updateFadeValues (int oscillatorIndex);
    
    // Init methods.
    void prepareToPlay (float frequency, float sampleRate, int blockSize);
    
    // DSP methods.
    void processBlock (juce::AudioBuffer<float>& buffer);
    
private:
    juce::OwnedArray<SineOscillator> m_Oscillators;
    juce::OwnedArray<SineOscillator> m_LFOs;
    
    Panner m_Panner;
    juce::Reverb m_Reverb;
    juce::IIRFilter m_Filter;
    
    Grid& m_Grid;
    
    int m_BlockSize;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synthesis)
};


