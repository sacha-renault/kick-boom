/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthVoice.h"
#include "SynthSound.h"
#include "InitPluginParameters.h"
#include "Automation.h"

// forward decl
class SynthVoice;

//==============================================================================
/**
*/
class KickMasterAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    KickMasterAudioProcessor();
    ~KickMasterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    // To modify the voices (eg adsr, wave shape, etc ...)
    void setAdsr(float attack, float decay, float sustain, float release);
    void setWaveShape();
    float getParameter(std::string name);
    void setParameter(std::string name, float value);

private:
    juce::Synthesiser synth;
    std::vector<SynthVoice*> getVoices();

    //==============================================================================
    // Init the parameters for the plugin
    juce::AudioProcessorValueTreeState pluginParameters;
    juce::ADSR envelope;
    Automation pitchAutomation;
    // something to store waveshape here ...

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KickMasterAudioProcessor)
};
