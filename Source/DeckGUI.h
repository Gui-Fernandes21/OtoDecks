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
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component, 
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager &formatManagerToUse,
            juce::AudioThumbnailCache &cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button*) override;

    void sliderValueChanged(juce::Slider*) override;

    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    void timerCallback() override;
    void mouseDown(const juce::MouseEvent& event) override;

    void uploadFileToBePlayed(juce::File file);

private:

    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };

    juce::TextButton hotCueButton1{ "Cue 1" };
    juce::TextButton hotCueButton2{ "Cue 2" };
    double cuePoint1 = -1.0;
    double cuePoint2 = -1.0;

    juce::Label volLabel;
    juce::Slider volSlider;

    juce::Label speedLabel;
    juce::Slider speedSlider;
    
    juce::Label posLabel;
    juce::Slider posSlider;

    juce::Slider revSlider;
    juce::Label revLabel;


    DJAudioPlayer* player;

    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
