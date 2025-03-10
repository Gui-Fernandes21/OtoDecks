/*
  ==============================================================================

    PlaylistComponent.h
    Created: 2 Mar 2025 8:06:04pm
    Author:  guifernandespro

    Description:
    This class manages the playlist functionality in the DJ application.
    It allows users to add, delete, and play tracks from a table-based playlist.
    Tracks can be assigned to Deck 1 or Deck 2 for playback.
    It also includes a crossfade slider for smooth transitions between decks.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DeckGUI.h"
#include "Track.h"
#include "CustomLookAndFeel.h"

//==============================================================================
// PlaylistComponent: Handles the track list and user interactions with the playlist.
//
class PlaylistComponent : public juce::Component,
                          public juce::TableListBoxModel, // Manages table data rendering
                          public juce::Button::Listener,  // Handles button interactions
                          public juce::Slider::Listener   // Handles slider interactions
{
public:
    // Constructor: Initializes the playlist with references to both decks and players.
    PlaylistComponent(DeckGUI* deck1, DeckGUI* deck2, DJAudioPlayer* player1, DJAudioPlayer* player2);

    ~PlaylistComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    int getNumRows() override;
    void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    // Handles crossfade slider movements.
    void sliderValueChanged(juce::Slider*) override;

    // Deletes a track from the playlist based on its index.
    void deleteTrackFromPlaylist(int id);

    // Updates the table UI when a cell needs to be refreshed.
    juce::Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

    // Handles button clicks for loading and playing tracks.
    void buttonClicked(juce::Button* button) override;

private:
    // Table component that displays the list of tracks.
    juce::TableListBox tableComponent;

    // Vector storing the list of tracks in the playlist.
    std::vector<Track> trackTitles;

    // References to the deck GUIs for assigning tracks.
    DeckGUI* deck1;
    DeckGUI* deck2;

    // References to the audio players controlling playback.
    DJAudioPlayer* player1;
    DJAudioPlayer* player2;

    // File chooser for selecting audio files.
    juce::FileChooser fChooser{ "Select a file..." };

    // Buttons for adding and playing tracks.
    juce::TextButton loadFileBtn{ "Load into playlist" };  // Adds track to the playlist
    juce::TextButton playOnFirstDeck{ "Play on Deck 1" };  // Sends track to Deck 1
    juce::TextButton playOnSecondDeck{ "Play on Deck 2" }; // Sends track to Deck 2

    // Crossfader slider for smooth track transitions.
    juce::Slider crossFadeSlider;
    juce::Label crossFadeLabel;

    // Custom LookAndFeel for styling the crossfader.
    CustomLookAndFeel crossfadeLookAndFeel;

    // Adds a song to the playlist and updates the table.
    void addSongToPlaylist();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
