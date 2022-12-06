/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class GainSliderTutorialAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    GainSliderTutorialAudioProcessor();
    ~GainSliderTutorialAudioProcessor() override;

    //i'll create some variables to make it easier to access our sliders..
    float gain;

    //==============================================================================
    //prepare to play is where we initialise our audio objects..
    //a filter might require an initialisation funcntion to work properly
    //it might require the sample rate..
    //this is where we call that function
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    //you can worry about this function later once you've got other things going
    //for now it's not too important
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    //this function is where all the magic happens!
    //in this plug-in, this is where we will be applying our volume parameter to incoming audio!
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    //this function is where we call the function to build the editor!
    //we will need to edit this function and pass in the parameters valuetreestate variable..
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //we will make a function to handle our controls..
    //it runs at audio rate so we hand it an index variable so it knows which channel its on
    void controls(int i);

    //here we setup another valueTreeState..
    // this one is constantly running and all others inherit from this one!!
    // we will use it in the function that calls the editor to be built, in its constructor!
    
    juce::AudioProcessorValueTreeState parameters;

    //we create an atomic float because they automatically update themselves..
    //we set it up as a pointer and then give it a nullptr and later we will give it something to point to
    std::atomic<float>* volume = nullptr;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainSliderTutorialAudioProcessor)
};
