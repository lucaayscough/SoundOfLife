#include "Headers.h"


//================================================//
// Synthesis class.

Synthesis::Synthesis(Grid& grid)
    :   m_Grid (grid)
{
    // Init Oscillators.
    m_Oscillators.ensureStorageAllocated (Variables::numColumns);
    m_Oscillators.ensureStorageAllocated (Variables::numLFOs);
    
    for (int i = 0; i < Variables::numColumns; ++i)
        m_Oscillators.add (new SineOscillator());
    
    for (int i = 0; i < Variables::numLFOs; ++i)
        m_LFOs.add (new SineOscillator);
}

Synthesis::~Synthesis() {}


//================================================//
// Setter methods.

void Synthesis::setBlockSize (int blockSize)                        { m_BlockSize = blockSize; }


//================================================//
// Getter methods.

int Synthesis::getBlockSize()                                       { return m_BlockSize; }

float Synthesis::getColumnGain (int column)
{
    float gain = 0;
    
    for (int row = 0; row < Variables::numRows; ++row)
        gain += m_Grid.getCell (row, column)->getFade();
    
    gain /= (float)Variables::numRows;
    
    return gain;
}

float Synthesis::getColumnPan (int column)
{
    // TODO:
    // Make this more precise.
    
    float pan = 0;
    
    for (int row = 0; row < Variables::numRows; ++row)
    {
        Cell& cell = *m_Grid.getCell (row, column);
        
        if (row < Variables::numRows / 2)
            pan += cell.getFade();
        
        else
            pan -= cell.getFade();
    }
    
    pan /= Variables::numRows / 2.0;
    
    if (pan > 1.0)
        pan = 1.0;
    else if (pan < -1.0)
        pan = -1.0;
    
    return pan;
}

float Synthesis::getSpectralGainDecay (float gain, float column, float frequency)
{
    return gain * Variables::startFrequency * (1.0 / frequency) ;
}


//================================================//
// State methods.

void Synthesis::updateFadeValues (int column)
{
    for (int row = 0; row < Variables::numRows; ++row)
        m_Grid.getCell (row, column)->updateFade();
}


//================================================//
// Init methods.

void Synthesis::prepareToPlay (float frequency, float sampleRate, int blockSize)
{
    for (int i = 0; i < Variables::numColumns; ++i)
        m_Oscillators[i]->prepareToPlay (frequency * (Variables::frequencyMultiplier * i + 1), sampleRate, blockSize);
    
    for (int i = 0; i < Variables::numLFOs; ++i)
        m_LFOs[i]->prepareToPlay (Variables::frequencyLFO[i], sampleRate, blockSize);
    
    setBlockSize (blockSize);
    
    // Reverb.
    juce::Reverb::Parameters reverbParameters;
    reverbParameters.dryLevel = 0.0f;
    reverbParameters.wetLevel = 1.0f;
    reverbParameters.roomSize = 1.0f;
    m_Reverb.reset();

    // Filter.
    m_Filter.setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, 1000));
    m_Filter.reset();
}


//================================================//
// DSP methods.

void Synthesis::processBlock (juce::AudioBuffer<float>& buffer)
{
    int numChannels = buffer.getNumChannels();
    int blockSize = buffer.getNumSamples();
    
    float sample = 0;
    float gain;
    
    juce::AudioBuffer<float> block;
    juce::Array<float> panValues;
    
    block.setSize (numChannels, blockSize);
    panValues.ensureStorageAllocated (m_BlockSize);
    
    buffer.clear();
    block.clear();
    
    for (int column = 0; column < Variables::numColumns; ++column)
    {
        panValues.clearQuick();
        
        for (int i = 0; i < blockSize; ++i)
        {
            /*
            // Frequency modulation.
            auto oldFreq = m_Oscillators[column]->getFrequency();
            auto newFreq = oldFreq + (m_LFOs[column % Variables::numLFOs]->processSample() * 10.0);
            
            m_Oscillators[column]->setFrequency (newFreq);
            
    
            // Pulse width modulation.
            auto oldPulse = m_Oscillators[column]->getPulseWidth();
            auto newPulse = oldPulse + (m_LFOs[(column + 1) % Variables::numLFOs]->processSample() / 2.3f);
            
            m_Oscillators[column]->setPulseWidth(newPulse);
            
            
            */
            
            
            // Sample to be further processed.
            sample = m_Oscillators[column]->processSample();
            
            // Gain to be applied.
            gain = getColumnGain (column);
            gain *= getSpectralGainDecay (gain, column, m_Oscillators[column]->getFrequency());
            
            // Pan to be applied.
            panValues.add (getColumnPan (column));
            
            // Update fade values for entire column.
            updateFadeValues (column);
        
            // Apply processing to sample.
            sample *= gain;
            
            // Add to buffer.
            for (int channel = 0; channel < numChannels; ++channel)
            {
                auto* channelData = block.getWritePointer (channel);
                channelData[i] += sample;
            }
            
            /*
            // Reset values.
            m_Oscillators[column]->setFrequency (oldFreq);
            m_Oscillators[column]->setPulseWidth (oldPulse);
             */
        }
        
        // Apply pan to buffer.
        m_Panner.processBlock (block, panValues);
    }
    
    for (int channel = 0; channel < numChannels; ++channel)
    {
        buffer.addFrom (channel, 0, block, channel, 0, blockSize);
    }
    
    //auto* leftChannel = buffer.getWritePointer(0);
    //auto* rightChannel = buffer.getWritePointer(1);
    
    //m_Filter.processSamples(leftChannel, buffer.getNumSamples());
    //m_Filter.processSamples(rightChannel, buffer.getNumSamples());
    
    //m_Reverb.processStereo(leftChannel, rightChannel, buffer.getNumSamples());
}
