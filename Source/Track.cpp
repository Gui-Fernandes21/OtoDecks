/*
  ==============================================================================

    Track.cpp
    Created: 8 Mar 2025 12:37:08am
    Author:  guifernandespro

  ==============================================================================
*/

#include "Track.h"

Track::Track(juce::File _file) : 
                                 file(_file), 
                                 fileName(_file.getFileNameWithoutExtension()), 
                                 fileURL(juce::URL{_file})
{};

Track::~Track()
{
};

juce::File Track::getFile()
{
    return this->file;
};

juce::String Track::getFileName()
{
    return this->fileName;
};

juce::URL Track::getFileURL()
{
    return this->fileURL;
};

void Track::setFileName(juce::String name)
{
    this->fileName = name;
};

void Track::setFileURL(juce::URL url)
{
    this->fileURL = url;
};