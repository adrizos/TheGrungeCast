/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheGrungeCastAudioProcessor::TheGrungeCastAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  )
#endif
{
    state = new AudioProcessorValueTreeState(*this, nullptr);
    state->createAndAddParameter("Drive", "Drive", "Drive", NormalisableRange<float>(0.0, 1.0, 0.0001), 1.0, nullptr, nullptr);
    state->createAndAddParameter("Range", "Range", "Range", NormalisableRange<float>(0.0, 3000, 0.0001), 1.0, nullptr, nullptr);
    state->createAndAddParameter("Blend", "Blend", "Blend", NormalisableRange<float>(0.0, 1.0, 0.0001), 1.0, nullptr, nullptr);
    state->createAndAddParameter("Volume", "Volume", "Volume", NormalisableRange<float>(0.0, 3, 0.0001), 1.0, nullptr, nullptr);
    
    state->state = ValueTree("Drive");
    state->state = ValueTree("Range");
    state->state = ValueTree("Blend");
    state->state = ValueTree("Volume");
    //doesnt seem to make sense but = gets overloaded in constructor and indexs them or something...
}

TheGrungeCastAudioProcessor::~TheGrungeCastAudioProcessor()
{
}

//==============================================================================
const String TheGrungeCastAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheGrungeCastAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool TheGrungeCastAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool TheGrungeCastAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double TheGrungeCastAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheGrungeCastAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int TheGrungeCastAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheGrungeCastAudioProcessor::setCurrentProgram (int index)
{
}

const String TheGrungeCastAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheGrungeCastAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TheGrungeCastAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TheGrungeCastAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheGrungeCastAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void TheGrungeCastAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
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
    
    float drive = *state->getRawParameterValue("Drive");
    float range = *state->getRawParameterValue("Drive");
    float blend = *state->getRawParameterValue("Drive");
    float volume = *state->getRawParameterValue("Drive");
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        // ..do something to the data...
        //the buffer is an array of float values, the audio samples
        //this is just the audio data we're manipulating
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++){
            float cleanSig = *channelData; //clean signal before any distortion
            
            //apply gain
            *channelData *= drive * range; //range and drive go together and increases the maximum value of drive
            
           //clip signal
            //amplify signal (get closer to 1, heavier distortion)
            // original code : *channelData = (((((2.f/float_Pi) * atan(*channelData)) * blend) + (cleanSig * (1.f / blend))) / 2) * volume;
            *channelData = (((((2.f/float_Pi) * atan(*channelData)) * blend) + (cleanSig * (1.0 - blend))) / 2) * volume;
          
            channelData++;
        }
    }
}
AudioProcessorValueTreeState& TheGrungeCastAudioProcessor::getState() {
    return *state; //returns reference
}

//==============================================================================
bool TheGrungeCastAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TheGrungeCastAudioProcessor::createEditor()
{
    return new TheGrungeCastAudioProcessorEditor (*this);
}

//==============================================================================
void TheGrungeCastAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);
}

void TheGrungeCastAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    
    if (tree.isValid()) {
        state->state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheGrungeCastAudioProcessor();
}

