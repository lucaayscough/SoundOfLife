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

void Synthesis::setBlockSize (int blockSize)
{
    m_BlockSize = blockSize;
}


//================================================//
// Getter methods.

int Synthesis::getBlockSize()
{
    return m_BlockSize;
}

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

float Synthesis::getSpectrumGainDecay (float gain, float column)
{
    return gain * (1.0 / (2.7182 * (column + 1.0)));
}


//================================================//
// AudioBuffer methods.

void Synthesis::sumBuffers (juce::AudioBuffer<float>& buffer_1, juce::AudioBuffer<float>& buffer_2)
{
    jassert (buffer_1.getNumSamples() == buffer_2.getNumSamples());
    
    auto* bufferToWrite = buffer_1.getWritePointer(0);
    auto* bufferToRead = buffer_2.getReadPointer(0);
    
    for (int i = 0; i < m_BlockSize; i++)
    {
        bufferToWrite[i] += bufferToRead[i];
    }
}


//================================================//
// Init methods.

void Synthesis::prepareToPlay (float frequency, float sampleRate)
{
    for (int i = 0; i < Variables::numColumns; i++)
    {
        m_Oscillators[i]->prepareToPlay (frequency * (1.05 * i + 1), sampleRate);
    }
}

void Synthesis::prepareToPlay (float frequency, float sampleRate, int blockSize)
{
    for (int i = 0; i < Variables::numColumns; i++)
    {
        m_Oscillators[i]->prepareToPlay (frequency * (1.3 * i + 1), sampleRate, blockSize);
    }
    
    setBlockSize(blockSize);
    m_Buffer.setSize(1, blockSize);
}


//================================================//
// DSP methods.

float Synthesis::processSample()
{
    // Generate spectrum from sine waves.
    // First and last columns will always be silent.
    
    float mix = 0;

    for (int column = 0; column < Variables::numColumns; column++)
    {
        float sample = m_Oscillators[column]->processSample();
        float gain = getColumnGain (column);
        sample *= getSpectrumGainDecay (gain, column);
        mix += sample;
    }
    
    return mix;
}

juce::AudioBuffer<float>& Synthesis::processBlock()
{
    m_Buffer.clear();
    
    for (int column = 0; column < Variables::numColumns; column++)
    {
        auto& block = m_Oscillators[column]->processBlock();
        float gain = getColumnGain (column);
        gain *= getSpectrumGainDecay (gain, column);
        block.applyGain(gain);
        sumBuffers (m_Buffer, block);
    }
    
    return m_Buffer;
}
