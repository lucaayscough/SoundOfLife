#include "Headers.h"


Synthesis::Synthesis(Grid& _grid)
    :   grid (_grid)
{
    initOscillators();
}

Synthesis::~Synthesis() {}

void Synthesis::initOscillators()
{
    oscillators.ensureStorageAllocated (Variables::numColumns);
    
    for (int i = 0; i < Variables::numColumns; i++)
    {
        oscillators.add (new SineOscillator());
    }
}

void Synthesis::prepareToPlay (float _frequency, float _sampleRate)
{
    for (int i = 0; i < Variables::numColumns; i++)
    {
        oscillators[i]->prepareToPlay (_frequency * (i + 1), _sampleRate);
    }
}

float Synthesis::processSample()
{
    // Generate spectrum from sine waves.
    // First and last columns will always be silent.
    
    float _mix = 0;
    float _log;
    float _sample = 0;
    
    for (int i = 0; i < Variables::numColumns; i++)
    {
        _log = std::log10((float)i + 1);
        
        for (int row = 0; row < Variables::numRows; row++)
        {
            if (grid.getCell(row, i))
            {
                _sample += oscillators[i]->processSample() * (1.0 / (i + 1));
                
                break;
            }
        }
        
        _mix += _sample / (float)Variables::numRows;
    }
    
    return _mix;
}
