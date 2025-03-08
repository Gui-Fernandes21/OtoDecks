/*
  ==============================================================================

    PlaylistComponent.h
    Created: 2 Mar 2025 8:06:04pm
    Author:  guifernandespro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DeckGUI.h"
#include "Track.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener
{
public:
    PlaylistComponent(DeckGUI* deck1, DeckGUI* deck2);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
        
    int getNumRows() override;
    void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    juce::Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

    void buttonClicked(juce::Button* button) override;
private:

    juce::TableListBox tableComponent;

    std::vector<Track> trackTitles;

    DeckGUI* deck1;
    DeckGUI* deck2;

    juce::FileChooser fChooser{ "Select a file..." };

    juce::TextButton loadFileBtn{ "Load into playlist" };
    juce::TextButton playOnFirstDeck{ "Play on Deck 1" };
    juce::TextButton playOnSecondDeck{ "Play on Deck 2" };

    void addSongToPlaylist();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
