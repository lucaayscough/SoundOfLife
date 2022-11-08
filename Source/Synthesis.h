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
    void setSampleRate (float sampleRate);
    
    // Getter methods.
    int getBlockSize();
    float getSampleRate();
    
    // Helper methods.
    float getOscillatorGain (int oscillatorIndex);
    float getOscillatorPan (int oscillatorIndex);
    float getSpectralGainDecay (float gain, float frequency);
    
    // State methods.
    void updateFadeValues (int oscillatorIndex);
    
    // Init methods.
    void prepareToPlay (float sampleRate, int blockSize);
    
    // DSP methods.
    void processBlock (juce::AudioBuffer<float>& buffer);
    
private:
    juce::OwnedArray<SineOscillator> m_Oscillators;
    juce::OwnedArray<SineOscillator> m_LFOs;
    
    Panner m_Panner;
    juce::Reverb m_Reverb;
    
    juce::IIRFilter m_FilterLeft;
    juce::IIRFilter m_FilterRight;
    
    Grid& m_Grid;
    
    int m_BlockSize;
    float m_SampleRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synthesis)
};


