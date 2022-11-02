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
        oscillators.add (new TriangleOscillator());
    }
}

void Synthesis::prepareToPlay (float _frequency, float _sampleRate)
{
    for (int i = 0; i < Variables::numColumns; i++)
    {
        oscillators[i]->prepareToPlay (_frequency * (2.235 * i + 1), _sampleRate);
    }
}

float Synthesis::processSample()
{
    // Generate spectrum from sine waves.
    // First and last columns will always be silent.
    
    float _mix = 0;

    for (int column = 0; column < Variables::numColumns; column++)
    {
        float _sample = oscillators[column]->processSample();
     
        float gain = 0;
        
        for (int row = 0; row < Variables::numRows; row++)
        {x
            gain += grid.getCell (row, column)->getFade();
            grid.getCell (row, column)->updateFade();
        }

        gain /= (float)Variables::numRows;
        
        _mix += (_sample * gain) * (1.0 / (2.7182 * ((float)column + 1.0)));
    }
    
    return _mix;
}
