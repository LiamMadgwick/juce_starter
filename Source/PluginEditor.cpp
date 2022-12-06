/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//this is the constructor for the editor where we actually add our components and other UI
//we also need to declare our value tree
//the valueTreeState is given the vts from the constructor so the valueTreeState can build..
//we also need to declare the valueTreeState in the processor function that calls the editor constructor..
//we will get to that.
GainSliderTutorialAudioProcessorEditor::GainSliderTutorialAudioProcessorEditor (GainSliderTutorialAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts), audioProcessor (p) //compiler want me to put vts before audioProcessor
{
    //in here we build the components..

    volume.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    //the unique_ptr has the function reset, which we do everytime we open the editor with this code..
    //the string in this code is very important!
    // it must match the identifier in the parameter valuetreestate inside  the audio processor.
    volumeAttach.reset(new SliderAttachment(valueTreeState, "V", volume));
    //just setting this up to not be annoying..
    volume.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    //then we add the component and make it visible..
    addAndMakeVisible(volume);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

//this is the deconstructor.. mostly we don't need to worry about it
//a good case might be stopping a timer that is only necessary to update your UI

GainSliderTutorialAudioProcessorEditor::~GainSliderTutorialAudioProcessorEditor()
{
}

//==============================================================================
void GainSliderTutorialAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
}

void GainSliderTutorialAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //just whack it in there..
    //you can use the bounds and rectangle to set up resizable components...
    //i just do it this way because I design UI in other software and can get the exact px-position from there
    volume.setBounds(180, 50, 40, 200);
}
