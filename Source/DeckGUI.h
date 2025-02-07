/*
  ==============================================================================

    DeckGUI.h
    Created: 7 Feb 2025 6:05:38pm
    Author:  guifernandespro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component, 
                 public juce::Button::Listener,
                 public juce::Slider::Listener
{
public:
    DeckGUI(DJAudioPlayer* player);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /* IMPLEMENT BUTTON LISTENER */
    void buttonClicked(juce::Button*) override;

    /* Implement slider::listener */
    void sliderValueChanged(juce::Slider*) override;

private:

    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton loadButton{ "LOAD" };

    juce::FileChooser fChooser{ "Select a file..." };

    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
