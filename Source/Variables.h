#pragma once


struct Variables
{
    static const int windowHeight = 1024.0f;
    static const int windowWidth = 1024.0f;
    static const int numRows = 32;
    static const int numColumns = 32;
    
    static const int gridRefreshRate = 100;
    static const int uiRefreshRate = 33;
    
    static const int lowRandomRange = -5;
    static constexpr float fadeAmount = 0.01;
    static const bool useColour = true;
};
