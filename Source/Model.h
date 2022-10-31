#pragma once


//================================================//
/// Model class containing all application data and states.

class Model
{
public:
    Model();
    ~Model();
    
    // Getter methods.
    GridModel& getGrid();

private:
    GridModel grid;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Model)
};
