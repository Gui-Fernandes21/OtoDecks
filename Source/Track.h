/*
  ==============================================================================

    Track.h
    Created: 8 Mar 2025 12:37:08am
    Author:  guifernandespro

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Track 
{
public:
    Track(juce::File file);
    ~Track();

    void setFileName(juce::String fileName);
    void setFileURL(juce::URL url);

    juce::String getFileName();
    juce::URL getFileURL();
private:
    juce::File file;
    juce::String fileName;
    juce::URL fileURL;
};