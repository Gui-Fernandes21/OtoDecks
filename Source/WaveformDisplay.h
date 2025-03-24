/*
  ==============================================================================

    WaveformDisplay.h
    Created: 19 Feb 2025 3:06:43pm
    Author:  guifernandespro

    Description:
    This class provides a graphical representation of an audio track's waveform.
    It allows users to visualize track structure and interact with the playhead
    for navigation.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
// WaveformDisplay: Renders an audio waveform and updates the playhead position.
//
class WaveformDisplay : public juce::Component,
                        public juce::ChangeListener // Listens for waveform updates
{
public:
    // Constructor: Initializes the waveform display with a format manager and cache.
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                    juce::AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    // Called when the a new track is being loaded waveform data changes.
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    // Loads an audio file from a given URL into the waveform display.
    void loadURL(juce::URL audioURL);

    // Sets the relative position of the playhead.
    void setPositionRelative(double pos);

private:
    // Audio thumbnail for waveform visualization.
    juce::AudioThumbnail audioThumb;
    // Flag indicating whether a file is loaded.
    bool fileLoaded;
    // Current playhead position (relative to track length).
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
