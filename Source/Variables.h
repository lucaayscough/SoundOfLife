#pragma once


struct Variables
{
    static const int windowHeight = 1024.0;                                                     // Height of plugin window.
    static const int windowWidth = 1024.0;                                                      // Width of plugin window.
    static const bool useColour = true;                                                         // If false UI will be black/white else will be black/red and will use fade value.
    
    static const int numRows = 16;                                                              // Number of rows for Game of Life simulation.
    static const int numColumns = 16;                                                           // Number of columns for Game of Life simulation.
    
    static const int gridRefreshRate = 5000;                                                    // Grid refresh rate in ms.
    static const int uiRefreshRate = 33;                                                        // UI refresh rate in ms.
    
    static const int lowRandomRange = 0;                                                        // Value used to set the amount of randomness used to init the grid.
    static constexpr float fadeAmount = 0.0000005f;                                             // Value used to increment fade values in cells.
    
    static const int numOscillators = 16;                                                       // Number of oscillators to instantiate.
    static const int numLFOs = 4;                                                               // Number of LFOs to instantiate
        
    static constexpr float startFrequency = 50.0f;                                              // Frequency used for the first oscillator.
    static constexpr float inharmonicity = 1.01f;                                               // Value used to diverge the frequency of oscillators.
    static constexpr float frequencyLFO[4] = {0.01f, 0.002f, 0.023f, 0.001f};                   // Array containing LFO frequencies.
    static constexpr float filterCutoff = 100.0f;                                               // Cutoff value for the filter.
};
