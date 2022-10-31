#pragma once


//================================================//
/// Cell model class.

class CellModel
{
public:
    CellModel();
    ~CellModel();

    // Getter methods.
    bool getIsAlive();
    
    // Setter methods.
    void setIsAlive (bool _isAlive);
    
private:
    bool isAlive = false;
    
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
    
    // Setter methods.
    void setColour(const juce::Colour& _colour);
    
private:
    juce::Colour colour;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CellView)
};


//================================================//
/// Cell controller class.

class CellController
{
public:
    CellController(CellModel& _model, CellView& _view);
    ~CellController();
    
    // State methdos.
    void setAlive();
    void setDead();
    
private:
    CellModel& model;
    CellView& view;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CellController)
};
