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

float Synthesis::getColumnGain(int column)
{
    float gain = 0;
    
    for (int row = 0; row < Variables::numRows; row++)
    {
        Cell& cell = *m_Grid.getCell (row, column);
        
        gain += cell.getFade();
        cell.updateFade();
    }
    
    gain /= (float)Variables::numRows;
    
    return gain;
}

float Synthesis::getSpectrumGainDecay (float gain, float column, float frequency)
{
    return gain * Variables::startFrequency * (1.0 / frequency) ;
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
        auto& block = m_Oscillators[column]->processBlock();
        float gain = getColumnGain (column);
        gain *= getSpectrumGainDecay (gain, column, m_Oscillators[column]->getFrequency());
        block.applyGain (gain);
        
        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
        {
            buffer.addFrom(channel, 0, block, 0, 0, m_BlockSize);
        }
    }
    
    // TODO:
    // Remove this.
    buffer.applyGain (4.0f);
}
