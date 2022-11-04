#include "Headers.h"


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

void Synthesis::setBlockSize (int blockSize)
{
    m_BlockSize = blockSize;
}

int Synthesis::getBlockSize()
{
    return m_BlockSize;
}

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

float Synthesis::processSample()
{
    // Generate spectrum from sine waves.
    // First and last columns will always be silent.
    
    float mix = 0;

    for (int column = 0; column < Variables::numColumns; column++)
    {
        float sample = m_Oscillators[column]->processSample();
     
        float gain = 0;
        
        for (int row = 0; row < Variables::numRows; row++)
        {
            Cell& cell = *m_Grid.getCell (row, column);
            
            gain += cell.getFade();
            cell.updateFade();
        }

        gain /= (float)Variables::numRows;
        
        mix += (sample * gain) * (1.0 / (2.7182 * ((float)column + 1.0)));
    }
    
    return mix;
}

juce::AudioBuffer<float>& Synthesis::processBlock()
{
    m_Buffer.clear();
    
    for (int column = 0; column < Variables::numColumns; column++)
    {
        auto& block = m_Oscillators[column]->processBlock();
     
        float gain = 0;
        
        for (int row = 0; row < Variables::numRows; row++)
        {
            Cell& cell = *m_Grid.getCell (row, column);
            
            gain += cell.getFade();
            cell.updateFade();
        }

        gain /= (float)Variables::numRows;
        
        for (int i = 0; i < m_BlockSize; i++)
        {
            auto sample = block.getSample (0, i);
            auto oldSample = m_Buffer.getSample (0, i);
            
            sample = (sample * gain) * (1.0 / (2.7182 * (column + 1.0)));
            
            m_Buffer.setSample(0, i, sample + oldSample);
        }
    }
    
    return m_Buffer;
}
