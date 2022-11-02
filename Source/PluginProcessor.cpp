#include "Headers.h"


//==============================================================================
SoundOfLifeAudioProcessor::SoundOfLifeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    :   AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
        synthesis (grid)
#endif
{
    grid.initialize();
}

SoundOfLifeAudioProcessor::~SoundOfLifeAudioProcessor() {}

//==============================================================================
const juce::String SoundOfLifeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SoundOfLifeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SoundOfLifeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SoundOfLifeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SoundOfLifeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SoundOfLifeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SoundOfLifeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SoundOfLifeAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SoundOfLifeAudioProcessor::getProgramName (int index)
{
    return {};
}

void SoundOfLifeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SoundOfLifeAudioProcessor::prepareToPlay(double _sampleRate, int _samplesPerBlock)
{
    synthesis.prepareToPlay(55, _sampleRate);
}

void SoundOfLifeAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SoundOfLifeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SoundOfLifeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for(int i = 0; i < buffer.getNumSamples(); i++)
    {
        auto sample = synthesis.processSample();
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);
            channelData[i] = sample * 0.5;
        }
    }
}

//==============================================================================
bool SoundOfLifeAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* SoundOfLifeAudioProcessor::createEditor()
{
    return new SoundOfLifeAudioProcessorEditor (*this);
}

//==============================================================================
void SoundOfLifeAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void SoundOfLifeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SoundOfLifeAudioProcessor();
}




Grid& SoundOfLifeAudioProcessor::getGrid()
{
    return grid;
}
