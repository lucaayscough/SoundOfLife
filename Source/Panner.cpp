#include "Headers.h"


Panner::Panner() {}

Panner::~Panner() {}

void Panner::setPan (float pan)
{
    m_Pan = pan;
    setGains();
}

float Panner::getPan()
{
    return m_Pan;
}

void Panner::setGains()
{
    m_LeftGain = 1.0;
    m_RightGain = 1.0;
    
    if (m_Pan < 0.0)
    {
        m_RightGain += m_Pan;
    }
    
    else if (m_Pan > 0.0)
    {
        m_LeftGain -= m_Pan;
    }
}

void Panner::processBlock (juce::AudioBuffer<float>& buffer)
{
    if (buffer.getNumChannels() != 2)
        return;
    
    buffer.applyGain (0, 0, buffer.getNumSamples(), m_LeftGain);
    buffer.applyGain (1, 0, buffer.getNumSamples(), m_RightGain);
}

void Panner::processBlock (juce::AudioBuffer<float>& buffer, juce::Array<float>& panValues)
{
    if (buffer.getNumChannels() != 2)
        return;
    
    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        setPan (panValues[sample]);
        
        buffer.applyGain (0, sample, 1, m_LeftGain);
        buffer.applyGain (1, sample, 1, m_RightGain);
    }
}
