/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheGrungeCastAudioProcessorEditor::TheGrungeCastAudioProcessorEditor (TheGrungeCastAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    //custom image setup
    backgroundImage = ImageCache::getFromMemory(Images::background3_png, Images::background3_pngSize);
    
    addAndMakeVisible(driveKnob = new Slider("Drive"));
    driveKnob->setSliderStyle(Slider::Rotary);
    driveKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    
    addAndMakeVisible(rangeKnob = new Slider("Range"));
    rangeKnob->setSliderStyle(Slider::Rotary);
    rangeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(blendKnob = new Slider("Blend"));
    blendKnob->setSliderStyle(Slider::Rotary);
    blendKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(volumeKnob = new Slider("Volume"));
    volumeKnob->setSliderStyle(Slider::Rotary);
    volumeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(toneKnob = new Slider("Tone"));
    toneKnob->setSliderStyle(Slider::Rotary);
    toneKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    //global styling
    //set track color
    getLookAndFeel().setColour(Slider::rotarySliderFillColourId , Colours::grey);
    //set all Sliders thumb color
    getLookAndFeel().setColour(Slider::thumbColourId, Colour(0xffe47272));
    
    driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "Drive", *driveKnob);
    rangeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "Range", *rangeKnob);
    blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "Blend", *blendKnob);
    volumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "Volume", *volumeKnob);
    toneAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "Tone", *toneKnob);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //setSize (500, 200); first horizontal ratio
    setSize(400,500);
}

TheGrungeCastAudioProcessorEditor::~TheGrungeCastAudioProcessorEditor()
{
}

//==============================================================================
void TheGrungeCastAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colour (0xffe2984a));
    
    //set background image
    g.drawImage(backgroundImage, 0, 0, 400,500,0,0,400,500);
    
    
    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
    g.drawText("Drive", 152, 180, 100, 100, Justification::centred, false);
    g.drawText("Range", 152, 310, 100, 100, Justification::centred, false);
    g.drawText("Blend", ((getWidth() / 5) * 1.65) - (100 /2), ((getHeight() * 2.15) / 3) + 95, 75, 75, Justification::centred, false);
    g.drawText("Volume", ((getWidth() / 5) * 2.65) - (100 /2), ((getHeight() * 2.15) / 3) + 95, 75, 75, Justification::centred, false);
    g.drawText("Tone", ((getWidth() / 5) * 3.65) - (100 /2), ((getHeight() * 2.15) / 3) + 95, 75, 75, Justification::centred, false);
    
    //draw text for weather updates
//    g.drawText("Current Weather in Seattle: 70F, Cloudy, 45% Percipitation", getWidth() / 95, ((getHeight() * 2.15) / 3) + 55, 395, 100, Justification::centred, false);
    
    
    
}

void TheGrungeCastAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //x,y,width,height
//    driveKnob->setBounds(((getWidth() / 5) * 1.5) - (100 /2), ((getHeight() * 2) / 5) - (100/2), 100, 100);
//    rangeKnob->setBounds(((getWidth() / 5) * 3.5) - (100 /2), ((getHeight() * 2) / 5) - (100 / 2), 100, 100);
//    blendKnob->setBounds(((getWidth() / 5) * 1.65) - (100 /2), ((getHeight() * 2.15) / 3) - (100 / 2), 75, 75);
//    volumeKnob->setBounds(((getWidth() / 5) * 2.65) - (100 /2), ((getHeight() * 2.15) / 3) - (100 / 2), 75, 75);
//    toneKnob->setBounds(((getWidth() / 5) * 3.65) - (100 /2), ((getHeight() * 2.15) / 3) - (100 / 2), 75, 75);
    
    driveKnob->setBounds(152, 130, 100, 100);
    rangeKnob->setBounds(152,260 , 100, 100);
    
    blendKnob->setBounds(((getWidth() / 5) * 1.65) - (100 /2), ((getHeight() * 2.15) / 2.5) - (100 / 2) + 30, 75, 75);
    volumeKnob->setBounds(((getWidth() / 5) * 2.65) - (100 /2), ((getHeight() * 2.15) / 2.5) - (100 / 2) + 30, 75, 75);
    toneKnob->setBounds(((getWidth() / 5) * 3.65) - (100 /2), ((getHeight() * 2.15) / 2.5) - (100 / 2) + 30, 75, 75);
    
    

}
