/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 8 Mar 2025 8:41:07pm
    Author:  guifernandespro

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g,
    int x, int y,
    int width, int height,
    float sliderPos, float minSliderPos,
    float maxSliderPos,
    const juce::Slider::SliderStyle style,
    juce::Slider& slider)
{
    // Base Track
    g.setColour(juce::Colours::darkgrey);
    g.fillRect((float)x, (float)(y + height / 2 - 2), (float)width, 4.0f); // Draw track

    // Highlight Track (From center)
    g.setColour(juce::Colours::lightblue);
    float centerX = (float)(x + width / 2); // Center position
    if (slider.getValue() > 0.5)
    {
        g.fillRect(centerX, (float)(y + height / 2 - 2), sliderPos - centerX, 4.0f);
    }
    else
    {
        g.fillRect(sliderPos, (float)(y + height / 2 - 2), centerX - sliderPos, 4.0f);
    }

    // Draw Thumb (Knob)
    g.setColour(juce::Colours::white);
    g.fillEllipse(sliderPos - 5, (float)(y + height / 2 - 5), 10.0f, 10.0f);
}