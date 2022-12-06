/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GainSliderTutorialAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    //here is the declaration for our constructor..
    //we need to include a pointer to the valuetree so we can let the editor know what it needs to construct itself
    //we will create the object that it points to later.. in the processor
    GainSliderTutorialAudioProcessorEditor (GainSliderTutorialAudioProcessor& p, juce::AudioProcessorValueTreeState& vts);
    ~GainSliderTutorialAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //here we create a ValueTree..
    juce::AudioProcessorValueTreeState& valueTreeState;
    //here we define a type to make it easier to set up our sliders..
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment; 
    //here we set up sliders..
    juce::Slider volume;
    //here we are using our pre-define typedef to pass to the unique_ptr variable..
    std::unique_ptr<SliderAttachment> volumeAttach;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainSliderTutorialAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainSliderTutorialAudioProcessorEditor)
};
