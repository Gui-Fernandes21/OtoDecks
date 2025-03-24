/*
  ==============================================================================

    Track.h
    Created: 8 Mar 2025 12:37:08am
    Author:  guifernandespro

    Description:
    This class represents an individual track in the DJ application.
    It stores track metadata, including the file, filename, and URL,
    allowing easy access and management within the playlist.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================
// Track: Represents an audio track with metadata such as file location and name.
//
class Track
{
public:
    // Constructor: Initializes a Track with a given file.
    Track(juce::File file);
    ~Track();

    // Sets the track's filename.
    void setFileName(juce::String fileName);
    // Sets the track's file URL.
    void setFileURL(juce::URL url);
    // Retrieves the track's filename.
    juce::String getFileName();
    // Retrieves the track's file URL.
    juce::URL getFileURL();
    // Retrieves the actual file associated with the track.
    juce::File getFile();

private:
    // File object representing the track.
    juce::File file;

    // Name of the file (without path).
    juce::String fileName;

    // URL pointing to the track file location.
    juce::URL fileURL;
};
