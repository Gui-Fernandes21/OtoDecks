/*
  ==============================================================================

    DeckGUI.cpp
    Created: 7 Feb 2025 6:05:38pm
    Author:  guifernandespro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                 juce::AudioFormatManager& formatManagerToUse,
                 juce::AudioThumbnailCache& cacheToUse) : 
                                                            player(_player), 
                                                            waveformDisplay(formatManagerToUse, cacheToUse)
{

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);

    //initiation of the hot cue buttons together with their mouse listeners.
    addAndMakeVisible(hotCueButton1);
    addAndMakeVisible(hotCueButton2);
    hotCueButton1.addMouseListener(this, false);
    hotCueButton2.addMouseListener(this, false);

    addAndMakeVisible(volSlider);

    addAndMakeVisible(speedSlider);
    
    addAndMakeVisible(posSlider);

    addAndMakeVisible(waveformDisplay);

    playButton.addListener(this);
    stopButton.addListener(this);

    // initiation of speed slider
    speedSlider.addListener(this);
    speedSlider.setValue(1.0);
    speedSlider.setRange(0.0, 10.0);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setTextValueSuffix(" Speed.");
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 80, 20);

    // initiation of position slider
    posSlider.addListener(this);
    posSlider.setRange(0.0, 1.0);
    posSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);


    // Volume slider initiation
    volSlider.addListener(this);
    volSlider.setValue(.5);
    volSlider.setRange(0.0, 1.0);
    volSlider.setNumDecimalPlacesToDisplay(2);
    volSlider.setTextValueSuffix(" Volume.");
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    volSlider.setSliderStyle(juce::Slider::Rotary);


    startTimer(500);

}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8;
    double halfW = getWidth() / 2;

    waveformDisplay.setBounds(0, 0, getWidth(), rowH * 2);
    posSlider.setBounds(0, rowH * 2, getWidth(), rowH / 2);

    hotCueButton1.setBounds(0, rowH * 2.5, halfW, rowH);
    hotCueButton2.setBounds(halfW, rowH * 2.5, halfW, rowH);

    speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    volSlider.setBounds(0, rowH * 5, getWidth(), rowH * 1.5);

    playButton.setBounds(0, rowH * 7, getWidth() / 2, rowH);
    stopButton.setBounds(getWidth() / 2, rowH * 7, getWidth() / 2, rowH);
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton) {
        std::cout << "Play Button was clicked" << std::endl;
        player->start();
        return;
    };
    if (button == &stopButton) {
        std::cout << "Stop Button was clicked" << std::endl;
        player->stop();
        return;
    };
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider) {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider) {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider) {
        player->setPositionRelative(slider->getValue());
    }
}

void DeckGUI::timerCallback()
{
    // set the value of the position slider for every change on the playhead
    posSlider.setValue(player->getPositionRelative());
    // set the value of the playhead for the audio position
    waveformDisplay.setPositionRelative(player->getPositionRelative());
};

// public function to let the PlaylistComponent Upload the selected Track from the playlist
void DeckGUI::uploadFileToBePlayed(juce::File file)
{
    player->loadURL(juce::URL{ file });
    waveformDisplay.loadURL(juce::URL{ file });
};

void DeckGUI::mouseDown(const juce::MouseEvent& event)
{
    bool isRightClick = event.mods.isRightButtonDown();

    handleHotCueClick(hotCueButton1, cuePoint1, juce::Colours::red, isRightClick);
    handleHotCueClick(hotCueButton2, cuePoint2, juce::Colours::green, isRightClick);
}

void DeckGUI::handleHotCueClick(juce::TextButton& button, double& cuePoint, juce::Colour cueColor, bool isRightClick)
{
    if (!button.isMouseOver())
        return;

    if (isRightClick)
    {
        // Reset cue point
        cuePoint = -1.0;
        button.setColour(juce::TextButton::buttonColourId,
            juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::TextButton::buttonColourId));
    }
    else
    {
        // Set or jump to hot cue
        if (cuePoint < 0.0)
        {
            cuePoint = player->getPositionRelative();
            button.setColour(juce::TextButton::buttonColourId, cueColor);
        }
        else
        {
            player->setPositionRelative(cuePoint);
        }
    }
}
