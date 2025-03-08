/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 5 Feb 2025 2:29:17pm
    Author:  guifernandespro

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager) : formatManager(_formatManager) {};
DJAudioPlayer::~DJAudioPlayer() {};


// =====================================================================================
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) 
{
    // Set some default values
    reverbParameters.roomSize = 0.5f;
    reverbParameters.damping = 0.5f;
    reverbParameters.wetLevel = 0.33f;
    reverbParameters.dryLevel = 0.4f;
    reverbParameters.width = 1.0f;
    reverbParameters.freezeMode = 0.0f;

    reverb.setParameters(reverbParameters);

    // Prepare the reverb for the correct sample rate and buffer size
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = (juce::uint32) samplesPerBlockExpected;
    spec.numChannels = 2; 
    reverb.prepare(spec);


    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
};

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);

    juce::AudioBuffer<float>* buffer = bufferToFill.buffer;

    juce::dsp::AudioBlock<float> fullBlock(*buffer);

    auto subBlock = fullBlock.getSubBlock((size_t)bufferToFill.startSample,
        (size_t)bufferToFill.numSamples);

    juce::dsp::ProcessContextReplacing<float> context(subBlock);

    reverb.process(context);
}

void DJAudioPlayer::releaseResources() 
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
};


void DJAudioPlayer::loadURL(juce::URL audioUrl) 
{

    auto* reader = formatManager.createReaderFor(audioUrl.createInputStream(false));

    if (reader != nullptr) // file was successfully loaded
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
};
void DJAudioPlayer::setGain(double gain) 
{
    if (gain < 0 || gain > 1.0) {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    };
};
void DJAudioPlayer::setSpeed(double ratio) 
{
    if (ratio < 0 || ratio > 10.0) {
        std::cout << "DJAudioPlayer::setSpeed speed should be between 0 and 10" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    };
};
void DJAudioPlayer::setPosition(double posInSecs) 
{
    transportSource.setPosition(posInSecs);
};

void DJAudioPlayer::setPositionRelative(double pos) {
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
};

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
};

void DJAudioPlayer::start() 
{
    transportSource.start();
};
void DJAudioPlayer::stop()
{
    transportSource.stop();
};

void DJAudioPlayer::setReverb(double ratio)
{
    reverbParameters.wetLevel = (float) ratio;
    reverb.setParameters(reverbParameters);
};

