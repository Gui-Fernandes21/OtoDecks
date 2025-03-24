/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 5 Feb 2025 2:29:17pm
    Author:  guifernandespro

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//============================================================================= =
// DJAudioPlayer: Manages audio playback, processing, and controls for a DJ deck.
//
class DJAudioPlayer : public juce::AudioSource
{
public:
    // Constructor: Initializes the audio player with a reference to the format manager.
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);

    ~DJAudioPlayer();

    //==============================================================================

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    
    void releaseResources() override;

    // Loads an audio file from a given URL into the player.
    void loadURL(juce::URL audioUrl);

    // Sets the volume level (gain) of the player.
    void setGain(double gain);
    // Adjusts the playback speed (pitch/time stretching).
    void setSpeed(double ratio);
    // Sets the track playback position in seconds.
    void setPosition(double posInSecs);
    // Sets the track playback position relative to the total length (0.0 - 1.0).
    void setPositionRelative(double pos);

    // Retrieves the current playback position relative to the track length.
    double getPositionRelative();

    // Starts audio playback.
    void start();
    // Stops audio playback.
    void stop();

private:
    // Reference to the audio format manager for decoding audio files.
    juce::AudioFormatManager& formatManager;

    // Unique pointer to the audio file source.
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

    // Transport source that handles playback controls such as start/stop and positioning.
    juce::AudioTransportSource transportSource;

    // Resampling source to adjust playback speed (pitch control).
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
};