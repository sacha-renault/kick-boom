/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KickMasterAudioProcessorEditor::KickMasterAudioProcessorEditor (KickMasterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    p.setAdsr(0, 0, 1, 1);

    // make webbrowser as "root" of the editor, everything will be managed from html / vue
    addAndMakeVisible(webBrowser);
    webBrowser.goToURL("https://www.google.com");
    
}

KickMasterAudioProcessorEditor::~KickMasterAudioProcessorEditor()
{
}

//==============================================================================
void KickMasterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
}

void KickMasterAudioProcessorEditor::resized()
{ 
    // Set the bounds of the WebBrowserComponent to fill the window
    webBrowser.setBounds(getLocalBounds());
}
