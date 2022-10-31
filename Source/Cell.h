#pragma once


//================================================//
/// Cell model class.

class CellModel
{
public:
    CellModel();
    ~CellModel();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CellModel)
};


//================================================//
/// Cell view class.

class CellView  : public juce::Component
{
public:
    CellView();
    ~CellView();
    
    // Component methods.
    void paint (juce::Graphics& _graphics) override;
    void resized() override;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CellView)
};


//================================================//
/// Cell controller class.

class CellController
{
public:
    CellController();
    ~CellController();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CellController)
};
