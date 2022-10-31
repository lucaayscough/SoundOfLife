#pragma once


//================================================//
/// Model class containing all application data and states.

class View  : public juce::Component
{
public:
    View();
    ~View();
    
    // Component methods.
    void paint (juce::Graphics& _graphics) override;
    void resized() override;
    
    // Getter methods.
    GridView& getGrid();
    
private:
    GridView grid;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (View)
};
