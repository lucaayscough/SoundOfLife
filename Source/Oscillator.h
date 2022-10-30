#pragma once


//================================================//
/// Base oscillator class which outputs a phasor wave.

class Oscillator
{
public:
    Oscillator();
    virtual ~Oscillator();
    
    // Setter methods.
    void setFrequency (float _frequency);
    void setSampleRate (float _sampleRate);
    void setPhase (float _phase);
    void setPhaseDelta (float _phaseDelta);
    
    // Getter methods.
    float getFrequency();
    float getSampleRate();
    float getPhase();
    float getPhaseDelta();
    
    // Phase methods.
    void updatePhase();
    void updatePhaseDelta();
    
    // Init methods.
    void prepareToPlay (float _frequency, float _sampleRate);
    
    // DSP methods.
    virtual float output (float _phase);
    float processSample();
    void processBlock (juce::AudioBuffer<float>& _buffer);
    
private:
    float frequency;
    float sampleRate;
    float phase;
    float phaseDelta;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};


//================================================//
/// Square wave oscillator class.

class SineOscillator : public Oscillator
{
public:
    // DSP methods.
    float output (float _phase) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineOscillator)
};


//================================================//
/// Square wave oscillator class.

class SquareOscillator : public Oscillator
{
public:
    // DSP methods.
    float output (float _phase) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SquareOscillator)
};


//================================================//
/// Pulse wave oscillator class.

class PulseOscillator : public Oscillator
{
public:
    // Setter methods.
    void setPulseWidth (float _pulseWidth);
    
    // Getter methods.
    float getPulseWidth();
    
    // DSP methods.
    float output (float _phase) override;
    
private:
    float pulseWidth = 0.5f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PulseOscillator)
};


//================================================//
/// Triangle wave oscillator class.

class TriangleOscillator : public Oscillator
{
public:
    // DSP methods.
    float output (float _phase) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TriangleOscillator)
};


//================================================//
/// Sawtooth wave oscillator class.

class SawtoothOscillator : public Oscillator
{
public:
    // DSP methods.
    float output (float _phase) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SawtoothOscillator)
};
