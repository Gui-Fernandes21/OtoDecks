/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 8 Mar 2025 8:41:07pm
    Author:  guifernandespro

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawLinearSlider(juce::Graphics& g,
        int x, int y,
        int width, int height,
        float sliderPos, float minSliderPos,
        float maxSliderPos,
        const juce::Slider::SliderStyle style,
        juce::Slider& slider) override;
};
