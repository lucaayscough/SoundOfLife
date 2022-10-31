#pragma once


//================================================//
/// Grid model class.

struct GridModel
{
public:
    GridModel();
    ~GridModel();
    
    // Getter methods.
    juce::OwnedArray<CellModel>& getCells();
    
private:
    juce::OwnedArray<CellModel> cells;
    
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
    void constructCellsModel();
    void constructCellsView();
    void constructCellsController();
    
    // Grid update methods.
    void updateGrid();
    
    
private:
    GridModel& gridModel;
    GridView& gridView;
    
    juce::OwnedArray<CellController> cells;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridController)
};
