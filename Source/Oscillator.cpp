#include "Headers.h"


//================================================//
// Base Oscillator class.

Oscillator::Oscillator()
{
}

Oscillator::~Oscillator()
{
}


//================================================//

void Oscillator::setFrequency (float _frequency)
{
    frequency = _frequency;
}

void Oscillator::setSampleRate (float _sampleRate)
{
    sampleRate = _sampleRate;
}

void Oscillator::setPhase (float _phase)
{
    phase = _phase;
}

void Oscillator::setPhaseDelta (float _phaseDelta)
{
    phaseDelta = _phaseDelta;
}

//================================================//

float Oscillator::getFrequency()
{
    return frequency;
}

float Oscillator::getSampleRate()
{
    return sampleRate;
}

float Oscillator::getPhase()
{
    return phase;
}

float Oscillator::getPhaseDelta()
{
    return phaseDelta;
}


//================================================//

void Oscillator::updatePhase()
{
    setPhase(getPhase() + getPhaseDelta());
    
    if (getPhase() > 1.0f)
        setPhase(getPhase() - 1.0f);
}

void Oscillator::updatePhaseDelta()
{
    setPhaseDelta(getFrequency() / getSampleRate());
}


//================================================//

void Oscillator::prepareToPlay (float _frequency, float _sampleRate)
{
    setFrequency(_frequency);
    setSampleRate(_sampleRate);
    updatePhaseDelta();
}


//================================================//

float Oscillator::output (float _phase)
{
    return _phase;
}

float Oscillator::processSample()
{
    float _sample = output(getPhase());
    updatePhase();
    
    return _sample;
}

void Oscillator::processBlock (juce::AudioBuffer<float>& _buffer)
{
}


//================================================//
// Sine wave oscillator.

float SineOscillator::output (float _phase)
{
    return std::sin(2.0f * _phase * M_PI);
}


//================================================//
// Square wave oscillator.

float SquareOscillator::output (float _phase)
{
    if (_phase < 0.5f)
        return 1.0f;
    
    else
        return -1.0f;
}


//================================================//
// Pulse wave oscillator.


//================================================//
// Setter methods.

void PulseOscillator::setPulseWidth (float _pulseWidth)
{
    pulseWidth = _pulseWidth;
}


//================================================//
// Getter methods.

float PulseOscillator::getPulseWidth()
{
    return pulseWidth;
}


//================================================//
// DSP methods.

float PulseOscillator::output (float _phase)
{
    auto _pulseWidth = getPulseWidth();
    
    if (_phase < _pulseWidth)
        return 1.0f;
    
    else
        return -1.0f;
}


//================================================//
// Triangle wave oscillator.


//================================================//
// DSP methods.

float TriangleOscillator::output (float _phase)
{
    // Algorithm used to compute triangle wave in range [-1,1] --> https://wikimedia.org/api/rest_v1/media/math/render/svg/bc9fd743afd5943b7f83248e59d55d97119257b9
    return 2.0f * std::fabs(2.0f * (_phase - std::floor(_phase + 0.5f))) - 1.0f;
}


//================================================//
// Sawtooth wave oscillator.


//================================================//
// DSP methods.

float SawtoothOscillator::output (float _phase)
{
    // Algorithm used to compute sawtooth wave in range [-1,1] --> https://wikimedia.org/api/rest_v1/media/math/render/svg/0f07cb8c8f5850b17ad8c3415800046cd1f38967
    return 2.0f * (_phase - std::floor(0.5f + _phase));
}
