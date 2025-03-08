/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 5 Feb 2025 2:29:17pm
    Author:  guifernandespro

  ==============================================================================
*/

#pragma once

#include <juce_dsp/juce_dsp.h>
#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public juce::AudioSource {
    public: 
        
        DJAudioPlayer(juce::AudioFormatManager& _formatManager);
        ~DJAudioPlayer();

        //==============================================================================
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;


        void loadURL(juce::URL audioUrl);
        void setGain(double gain);
        void setSpeed(double ratio);
        void setPosition(double posInSecs);
        void setPositionRelative(double pos);

        void setReverb(double ratio);

        // get the relative position of the playhead
        double getPositionRelative();

        void start();
        void stop();

    private:

        juce::dsp::Reverb reverb;
        juce::dsp::Reverb::Parameters reverbParameters;

        juce::AudioFormatManager& formatManager;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::AudioTransportSource transportSource;
        juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
};