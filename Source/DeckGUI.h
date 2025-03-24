/*
  ==============================================================================

    DeckGUI.h
    Created: 7 Feb 2025 6:05:38pm
    Author:  guifernandespro

    Description:
    This class defines the graphical user interface (GUI) for a DJ deck,
    allowing user interaction with playback controls, volume, speed,
    and waveform visualization. It also includes hot cue functionality
    and integrates with the DJAudioPlayer.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
// DeckGUI: Handles user interaction with a single deck in the DJ application.
// It allows controlling playback, volume, speed, position, and hot cues.
//
class DeckGUI : public juce::Component,
                public juce::Button::Listener,  // Handles button clicks
                public juce::Slider::Listener,  // Handles slider movements
                public juce::Timer              // Updates UI periodically
{
public:
    // Constructor: Initializes the DeckGUI with a DJAudioPlayer instance,
    // an AudioFormatManager, and an AudioThumbnailCache for waveform display.
    DeckGUI(DJAudioPlayer* player,
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);

    ~DeckGUI() override;

    void paint(juce::Graphics&) override;

    void resized() override;

    void buttonClicked(juce::Button*) override;

    // Handles slider value changes (e.g., volume, speed, position).
    void sliderValueChanged(juce::Slider*) override;

    // Called periodically to update UI elements (e.g., waveform progress).
    void timerCallback() override;

    // Handles mouse interactions, including right-click resets for hot cues.
    void mouseDown(const juce::MouseEvent& event) override;

    // Handles setting, jumping to, and resetting hot cue points.
    void handleHotCueClick(juce::TextButton& button, double& cuePoint,
        juce::Colour cueColor, bool isRightClick);

    // Loads an audio file into the deck for playback.
    void uploadFileToBePlayed(juce::File file);

private:
    // Playback controls
    juce::TextButton playButton{ "PLAY" };  // Starts playback
    juce::TextButton stopButton{ "STOP" };  // Stops playback

    // Hot Cue buttons (store and jump to specific track positions)
    juce::TextButton hotCueButton1{ "Cue 1" };
    juce::TextButton hotCueButton2{ "Cue 2" };
    double cuePoint1 = -1.0;  // Stores position for Cue 1
    double cuePoint2 = -1.0;  // Stores position for Cue 2

    // Volume control
    juce::Slider volSlider;  // Adjusts track volume

    // Speed control
    juce::Slider speedSlider;  // Adjusts playback speed

    // Position control
    juce::Slider posSlider;  // Allows seeking through the track

    // Pointer to the associated DJAudioPlayer instance
    DJAudioPlayer* player;

    // Displays the waveform visualization of the track
    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
