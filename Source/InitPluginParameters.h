/*
  ==============================================================================

    InitPluginParameters.h
    Created: 18 Oct 2024 10:26:00am
    Author:  alexi

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    using juce::AudioProcessorValueTreeStateParameterAttributes;

    layout.add(
        std::make_unique<juce::AudioParameterFloat>("gain", "Gain", 0.0f, 1.0f, 0.5f));


    return layout;
}