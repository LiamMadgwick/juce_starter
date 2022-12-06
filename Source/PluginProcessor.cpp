/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//this constructor for this can be kind of confusing..
// we need to create the parameters after the audio buses.. with a ,
// the paramater tree gets given a pointer to itself and a nullptr for its call to an undo function..
// then followed by a , we create the actual paramaters insde the {} if you want to create more
// it would look like this {stdunique blah blah ("v","vol", 0, 1, 0), stdunique blah blah2 ("x", "xol", 0, 1, 0)} so on..
//==============================================================================
GainSliderTutorialAudioProcessor::GainSliderTutorialAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)), 
        parameters(*this, nullptr, juce::Identifier("params"),
        {
           std::make_unique<juce::AudioParameterFloat>("V", "Volume", 0.f, 1.f, 0.5f)
        }
    )
{
    //in the constructor here.. we linke the atomic float ptrs to the audioparamaterfloats..
    volume = parameters.getRawParameterValue("V");
}

GainSliderTutorialAudioProcessor::~GainSliderTutorialAudioProcessor()
{
}

//==============================================================================
const juce::String GainSliderTutorialAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainSliderTutorialAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainSliderTutorialAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainSliderTutorialAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainSliderTutorialAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainSliderTutorialAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainSliderTutorialAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainSliderTutorialAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GainSliderTutorialAudioProcessor::getProgramName (int index)
{
    return {};
}

void GainSliderTutorialAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GainSliderTutorialAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GainSliderTutorialAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

//here i just simplified this function so that it was easier to write the constructor for the processor..
bool GainSliderTutorialAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}

//here i'll create the controls function..

void GainSliderTutorialAudioProcessor::controls(int i)
{
    gain = *volume;
}

void GainSliderTutorialAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    //inside this for loop we iterate over each channel
    //and get samples in blocks..
    //to get at each sample which is what we want to do..
    //we create a new forloop inside this for loop..
    //first we create our limit,called numSamples, because it is defined by the number of samples in the buffer.

    int numSamples = buffer.getNumSamples();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //here is the original set up that juce gives..
            //auto* channelData = buffer.getWritePointer (channel);

        //i set it up like this, so i can more easily use it with my dsp library.
        float* data = buffer.getWritePointer(channel);

        //n is standard notation for this sort of loop..
        //n for sample number..
        for (int n = 0; n < numSamples; n++)
        {
            //call our controls function and pass channel as the index..
            //kind of unnecessary in this case but useful in others!
            controls(channel); 

            //here we effect the audio sample by sample!
            data[n] *= gain;
        }

        // ..do something to the data...
        // we did!
    }
}

//==============================================================================
bool GainSliderTutorialAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

//here we will add the paramaters valuetreestate into the constuctor of the editor...
juce::AudioProcessorEditor* GainSliderTutorialAudioProcessor::createEditor()
{
    return new GainSliderTutorialAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void GainSliderTutorialAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainSliderTutorialAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainSliderTutorialAudioProcessor();
}
