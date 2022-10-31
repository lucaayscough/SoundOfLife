#pragma once


//================================================//
/// Grid model class.

class GridModel
{
public:
    GridModel();
    ~GridModel();
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridModel)
};


//================================================//
/// Grid view class.

class GridView  : public juce::Component
{
public:
    GridView();
    ~GridView();
    
    // Component class.
    void paint (juce::Graphics& _graphics) override;
    void resized() override;
    
    // Getter methods.
    juce::OwnedArray<CellView>& getCells();
    
private:
    juce::OwnedArray<CellView> cells;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridView)
};


//================================================//
/// Grid controller class.

class GridController
{
public:
    GridController (GridModel& _gridModel, GridView& _gridView);
    ~GridController();
    
    // Init methods.
    void constructCellsView();
    
private:
    GridModel& gridModel;
    GridView& gridView;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridController)
};
