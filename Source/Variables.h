#pragma once


struct Variables
{
    static const int windowHeight = 1024.0;
    static const int windowWidth = 1024.0;
    static const bool useColour = false;
    
    static const int numRows = 16;
    static const int numColumns = 16;
    
    static const int gridRefreshRate = 1000;
    static const int uiRefreshRate = 33;
    
    static const int lowRandomRange = 0;
    static constexpr float fadeAmount = 0.000001f;
    
    static const int numOscillators = 16;
    static const int numLFOs = 4;
    
    static constexpr float startFrequency = 50.0f;
    static constexpr float inharmonicity = 1.04f;
    static constexpr float frequencyLFO[4] = {0.01f, 0.001f, 0.02f, 0.003f};
};
