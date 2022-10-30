#pragma once


class View  : public juce::Component
{
public:
    View();
    ~View();
    
    void paint (juce::Graphics& _graphics) override;
    void resized() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (View)
};
