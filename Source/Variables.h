#pragma once


struct Variables
{
    static const int windowHeight = 1024.0;
    static const int windowWidth = 1024.0;
    static const int numRows = 16;
    static const int numColumns = 16;
    
    static const int gridRefreshRate = 2000;
    static const int uiRefreshRate = 33;
    
    static const int lowRandomRange = -0;
    static constexpr float fadeAmount = 0.0001;
    static constexpr float frequencyMultiplier = 2.0;
    
    static const bool useColour = true;
    static constexpr float startFrequency = 50.0f;
};
