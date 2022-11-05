#pragma once


class Panner
{
public:
    Panner();
    ~Panner();
    
    // Setter methods.
    void setPan (float pan);
    
    // Getter methods.
    float getPan();
    
    // Helper methods.
    void setGains();
    
    // DSP methods.
    void processBlock (juce::AudioBuffer<float>& buffer);
    void processBlock (juce::AudioBuffer<float>& buffer, juce::Array<float>& panValues);
    
    
private:
    float m_Pan = 0.0;
    float m_LeftGain = 1.0;
    float m_RightGain = 1.0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Panner)
};
