/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 2 Mar 2025 8:06:04pm
    Author:  guifernandespro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _player1, DeckGUI* _player2):
                                    player1(_player1), player2(_player2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    tableComponent.getHeader().addColumn("Track Title", 1, 210);
    tableComponent.getHeader().addColumn("", 2, 50);

    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
    
    addAndMakeVisible(loadFileBtn);
    addAndMakeVisible(playOnFirstDeck);
    addAndMakeVisible(playOnSecondDeck);

    loadFileBtn.addListener(this);
    playOnFirstDeck.addListener(this);
    playOnSecondDeck.addListener(this);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowHeight = getHeight() / 8;

    loadFileBtn.setBounds(0, 0, getWidth(), rowHeight );
    playOnFirstDeck.setBounds(0, rowHeight, getWidth()/2, rowHeight);
    playOnSecondDeck.setBounds(getWidth() / 2, rowHeight, getWidth() / 2, rowHeight);

    tableComponent.setBounds(0, rowHeight*2, getWidth(), rowHeight * 7);
}


int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
};

void PlaylistComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) {
        g.fillAll(juce::Colours::orange);
    }
    else {
        g.fillAll(juce::Colours::darkgoldenrod);
    }
};

void PlaylistComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.drawText(trackTitles[rowNumber].getFileName(),
               2, 0, 
               width - 4, height, 
               juce::Justification::centredLeft, 
               true);
};

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (columnId == 2) {
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* btn = new juce::TextButton{ "X" };
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }

    return existingComponentToUpdate;
};

void PlaylistComponent::buttonClicked(juce::Button* button)
{   
    // int id = std::stoi(button->getComponentID().toStdString());

    // std::cout << "Button clicked: " << trackTitles[id] << std::endl;

    if (button == &loadFileBtn) {
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;

        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser) {
                juce::File chosenFile = chooser.getResult();
                trackTitles.push_back(Track{ chosenFile });
        });

        repaint();
    }
};