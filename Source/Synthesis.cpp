#include "Headers.h"


//================================================//
// Synthesis class.

Synthesis::Synthesis(Grid& grid)
    :   m_Grid (grid)
{
    // Init Oscillators.
    m_Oscillators.ensureStorageAllocated (Variables::numOscillators);
    m_Oscillators.ensureStorageAllocated (Variables::numLFOs);
    
    for (int i = 0; i < Variables::numOscillators; ++i)
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

float Synthesis::getOscillatorGain (int oscillatorIndex)
{
    float gain = 0;
    
    float startColumn = oscillatorIndex * (Variables::numColumns / Variables::numOscillators);
    float endColumn = startColumn + (Variables::numColumns / Variables::numOscillators);
    
    for (int column = startColumn; column < endColumn; ++column)
    {
        for (int row = 0; row < Variables::numRows; ++row)
            gain += m_Grid.getCell (row, column)->getFade();
    }
    
    gain /= (float)Variables::numRows * (float)Variables::numColumns / (float)Variables::numOscillators;
    
    return gain;
}

float Synthesis::getOscillatorPan (int oscillatorIndex)
{
    // TODO:
    // Make this more precise.
    
    float pan = 0;
    
    float startColumn = oscillatorIndex * (Variables::numColumns / Variables::numOscillators);
    float endColumn = startColumn + (Variables::numColumns / Variables::numOscillators);
    
    for (int column = startColumn; column < endColumn; ++column)
    {
        for (int row = 0; row < Variables::numRows; ++row)
        {
            Cell& cell = *m_Grid.getCell (row, column);
            
            if (row < Variables::numRows / 2)
                pan += cell.getFade();
            
            else
                pan -= cell.getFade();
        }
    }
    
    pan /= Variables::numRows * (endColumn - startColumn) / 2.0;
    
    if (pan > 1.0)
        pan = 1.0;
    else if (pan < -1.0)
        pan = -1.0;
    
    return pan;
}

float Synthesis::getSpectralGainDecay (float gain, float frequency)
{
    // Explanation for this is here: https://en.wikipedia.org/wiki/Pink_noise
    return gain * Variables::startFrequency * (1.0f / frequency) ;
}


//================================================//
// State methods.

void Synthesis::updateFadeValues (int oscillatorIndex)
{
    float startColumn = oscillatorIndex * (Variables::numColumns / Variables::numOscillators);
    float endColumn = startColumn + (Variables::numColumns / Variables::numOscillators);
    
    for (int column = startColumn; column < endColumn; ++column)
        for (int row = 0; row < Variables::numRows; ++row)
            m_Grid.getCell (row, column)->updateFade();
}


//================================================//
// Init methods.

void Synthesis::prepareToPlay (float sampleRate, int blockSize)
{
    auto frequency = Variables::startFrequency;
    
    for (int i = 0; i < Variables::numOscillators; ++i)
    {
        m_Oscillators[i]->prepareToPlay (frequency, sampleRate, blockSize);
        
        // Harmonic series: https://en.wikipedia.org/wiki/Harmonic_series_(mathematics)
        // And also this: https://en.wikipedia.org/wiki/Inharmonicity
        frequency += frequency / (i + 1.0f) * Variables::inharmonicity;
    }
    
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
    m_FilterLeft.setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, 300.0));
    m_FilterRight.setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, 300.0));
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
    
    for (int oscillatorIndex = 0; oscillatorIndex < Variables::numOscillators; ++oscillatorIndex)
    {
        panValues.clearQuick();
        
        for (int i = 0; i < blockSize; ++i)
        {
            /*
            // Frequency modulation.
            auto oldFreq = m_Oscillators[column]->getFrequency();
            auto newFreq = oldFreq + (m_LFOs[column % Variables::numLFOs]->processSample() * 40.0);
    
            m_Oscillators[column]->setFrequency (newFreq);
            
            */
            // Sample to be further processed.
            sample = m_Oscillators[oscillatorIndex]->processSample();
            
            // Gain to be applied.
            gain = getOscillatorGain (oscillatorIndex);
            gain *= getSpectralGainDecay (gain, m_Oscillators[oscillatorIndex]->getFrequency());
            
            // Pan to be applied.
            panValues.add (getOscillatorPan (oscillatorIndex));
            
            // Update fade values for entire column.
            updateFadeValues (oscillatorIndex);
        
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
             */
        }
        
        // Apply pan to buffer.
        m_Panner.processBlock (block, panValues);
    }
    
    for (int channel = 0; channel < numChannels; ++channel)
    {
        buffer.addFrom (channel, 0, block, channel, 0, blockSize);
    }
    
    auto* leftChannel = buffer.getWritePointer(0);
    auto* rightChannel = buffer.getWritePointer(1);
    
    m_FilterLeft.processSamples(leftChannel, buffer.getNumSamples());
    m_FilterRight.processSamples(rightChannel, buffer.getNumSamples());
    
    m_Reverb.processStereo(leftChannel, rightChannel, buffer.getNumSamples());
}
