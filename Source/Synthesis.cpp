#include "Headers.h"


//================================================//
// Synthesis class.

Synthesis::Synthesis(Grid& grid)
    :   m_Grid (grid)
{
    initOscillators();
}

Synthesis::~Synthesis() {}

void Synthesis::initOscillators()
{
    m_Oscillators.ensureStorageAllocated (Variables::numColumns);
    
    for (int i = 0; i < Variables::numColumns; i++)
    {
        m_Oscillators.add (new SineOscillator());
    }
}


//================================================//
// Setter methods.

void Synthesis::setBlockSize (int blockSize)                        { m_BlockSize = blockSize; }


//================================================//
// Getter methods.

int Synthesis::getBlockSize()                                       { return m_BlockSize; }

float Synthesis::getColumnGain (int column)
{
    float gain = 0;
    
    for (int row = 0; row < Variables::numRows; row++)
    {
        gain += m_Grid.getCell (row, column)->getFade();
    }
    
    gain /= (float)Variables::numRows;
    
    return gain;
}

float Synthesis::getColumnPan (int column)
{
    // TODO:
    // Make this more precise.
    
    float pan = 0;
    
    for (int row = 0; row < Variables::numRows; row++)
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
    for (int row = 0; row < Variables::numRows; row++)
        m_Grid.getCell (row, column)->updateFade();
}


//================================================//
// Init methods.

void Synthesis::prepareToPlay (float frequency, float sampleRate, int blockSize)
{
    for (int i = 0; i < Variables::numColumns; i++)
    {
        m_Oscillators[i]->prepareToPlay (frequency * (1.3 * i + 1), sampleRate, blockSize);
    }
    
    setBlockSize(blockSize);
}


//================================================//
// DSP methods.

void Synthesis::processBlock (juce::AudioBuffer<float>& buffer)
{
    buffer.clear();
    
    for (int column = 0; column < Variables::numColumns; column++)
    {
        auto numChannels = buffer.getNumChannels();
        auto& block = m_Oscillators[column]->processBlock();
        
        juce::Array<float> gainValues;
        juce::Array<float> panValues;
        
        gainValues.ensureStorageAllocated (m_BlockSize);
        panValues.ensureStorageAllocated (m_BlockSize);
        
        // Gets gain and pan values.
        for (int i = 0; i < m_BlockSize; i++)
        {
            // Get gain values and store them.
            float gain = getColumnGain (column);
            gain *= getSpectralGainDecay (gain, column, m_Oscillators[column]->getFrequency());
            gainValues.add(gain);
            
            // Get pan values and store them.
            panValues.add (getColumnPan (column));
            
            // Update fade values.
            updateFadeValues (column);
        }
        
        for (int sample = 0; sample < m_BlockSize; sample++)
        {
            block.applyGain (0, sample, 1, gainValues[sample]);
        }
        
        if (numChannels > 1)
        {
            // Makes the block stereo.
            block.setSize (numChannels, m_BlockSize, true);
            block.copyFrom (1, 0, block, 0, 0, m_BlockSize);
            
            //float leftGain = ;
            //float rightGain = ;
            
            //block.applyGain(<#int channel#>, <#int startSample#>, <#int numSamples#>, <#float gain#>);
        }
        
        
        
        // Adds the processed block to the audio buffer.
        for (int channel = 0; channel < numChannels; channel++)
        {
            buffer.addFrom (channel, 0, block, channel, 0, m_BlockSize);
        }
    }
}
