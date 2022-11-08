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
    juce::OwnedArray<SineOscillator> m_Oscillators;             // Array of oscillators.
    juce::OwnedArray<SineOscillator> m_LFOs;                    // Array of LFOs.
    
    Panner m_Panner;                                            // Panner used to pan oscillators.
    juce::Reverb m_Reverb;                                      // Reverb used at end of signal chain.
    
    juce::IIRFilter m_FilterLeft;                               // Filter for left channel.
    juce::IIRFilter m_FilterRight;                              // Filter for right channel.
    
    Grid& m_Grid;                                               // Reference to grid object.
    
    int m_BlockSize;                                            // Requested block size.
    float m_SampleRate;                                         // Requested sample rate.
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synthesis)
};


