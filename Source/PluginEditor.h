/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class KickMasterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KickMasterAudioProcessorEditor (KickMasterAudioProcessor&);
    ~KickMasterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Add WebBrowserComponent here
    juce::WebBrowserComponent webBrowser;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KickMasterAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KickMasterAudioProcessorEditor)
};
