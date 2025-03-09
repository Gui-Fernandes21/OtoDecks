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

    addAndMakeVisible(hotCueButton1);
    addAndMakeVisible(hotCueButton2);
    hotCueButton1.addListener(this);
    hotCueButton1.addMouseListener(this, false);
    hotCueButton2.addListener(this);
    hotCueButton2.addMouseListener(this, false);

    addAndMakeVisible(volSlider);

    addAndMakeVisible(speedSlider);
    
    addAndMakeVisible(posSlider);

    addAndMakeVisible(waveformDisplay);

    playButton.addListener(this);
    stopButton.addListener(this);


    speedSlider.addListener(this);
    speedSlider.setValue(1.0);
    speedSlider.setRange(0.0, 10.0);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setTextValueSuffix(" Speed.");
    
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 80, 20);


    posSlider.addListener(this);
    posSlider.setRange(0.0, 1.0);
    posSlider.setTooltip("Drag slider to control where the song should play from");
    //posSlider.setSliderStyle(juce::Slider::LinearBar);
    //posLabel.setText(juce::String("Position of the music"), juce::dontSendNotification);
    //posLabel.attachToComponent(&volSlider, true);
    posSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);


    volSlider.addListener(this);
    volSlider.setValue(.5);
    volSlider.setRange(0.0, 1.0);
    volSlider.setNumDecimalPlacesToDisplay(2);
    volSlider.setTextValueSuffix(" Volume.");
    //volLabel.attachToComponent(&volSlider, true);
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
    // g.drawText ("DeckGUI", getLocalBounds(),
                //juce::Justification::centred, true);   // draw some placeholder text
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

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files) 
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
};

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1) {
        player->loadURL(juce::URL{ juce::File { files[0] } });
        waveformDisplay.loadURL(juce::URL{ juce::File { files[0] } });
    }
};

void DeckGUI::timerCallback()
{
    posSlider.setValue(player->getPositionRelative());
    waveformDisplay.setPositionRelative(player->getPositionRelative());
};

void DeckGUI::uploadFileToBePlayed(juce::File file)
{
    player->loadURL(juce::URL{ file });
    waveformDisplay.loadURL(juce::URL{ file });
};

void DeckGUI::mouseDown(const juce::MouseEvent& event)
{
    std::cout << "click" << std::endl;

    if (event.mods.isRightButtonDown())
    {
        if (hotCueButton1.isMouseOver())
        {
            cuePoint1 = -1.0;
            hotCueButton1.setColour(juce::TextButton::buttonColourId, juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::TextButton::buttonColourId));
        }
        if (hotCueButton2.isMouseOver())
        {
            cuePoint2 = -1.0;
            hotCueButton2.setColour(juce::TextButton::buttonColourId, juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::TextButton::buttonColourId));
        }
    }
    else {
        if (hotCueButton1.isMouseOver()) {
            if (cuePoint1 < 0.0)
            {
                cuePoint1 = player->getPositionRelative();
                hotCueButton1.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
            }
            else
            {
                player->setPositionRelative(cuePoint1);
            }
        }
        if (hotCueButton2.isMouseOver()) {
            if (cuePoint2 < 0.0)
            {
                cuePoint2 = player->getPositionRelative();
                hotCueButton2.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
            }
            else
            {
                player->setPositionRelative(cuePoint2);
            }
        }
    }
}