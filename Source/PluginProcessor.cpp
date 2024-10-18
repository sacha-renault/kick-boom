/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KickMasterAudioProcessor::KickMasterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    pluginParameters(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
}

KickMasterAudioProcessor::~KickMasterAudioProcessor()
{
}

//==============================================================================
const juce::String KickMasterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KickMasterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KickMasterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KickMasterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KickMasterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KickMasterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KickMasterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KickMasterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KickMasterAudioProcessor::getProgramName (int index)
{
    return {};
}

void KickMasterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KickMasterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.clearVoices();

    for (int i = 0; i < 8; ++i)  // Adding 8 voices for polyphony
        synth.addVoice(new SynthVoice());  // Your SynthVoice class

    synth.clearSounds();
    synth.addSound(new SynthSound());  // Add your SynthSound class
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void KickMasterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KickMasterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void KickMasterAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();  // Clear the audio buffer before processing

    // Synthesiser renders the audio based on incoming MIDI
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}


//==============================================================================
bool KickMasterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KickMasterAudioProcessor::createEditor()
{
    return new KickMasterAudioProcessorEditor (*this);
}

//==============================================================================
void KickMasterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KickMasterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KickMasterAudioProcessor();
}

//==============================================================================
// Helper function to get all voices in the synth
std::vector<SynthVoice*> KickMasterAudioProcessor::getVoices() {
    int numVoices = synth.getNumVoices();
    std::vector<SynthVoice*> voices;
    voices.reserve(numVoices);  // Reserve space for efficiency

    for (int i = 0; i < numVoices; ++i) {
        auto voice = synth.getVoice(i);
        if (auto* synthVoice = dynamic_cast<SynthVoice*>(voice)) {
            voices.push_back(synthVoice);
        }
    }

    return voices;
}

void KickMasterAudioProcessor::setAdsr(float attack, float decay, float sustain, float release) {
    // Create a adre parameter object
    juce::ADSR::Parameters params(attack, decay, sustain, release);

    // Set it to plugin state
    envelope.setParameters(params);

    // Set it for every voice of the synth
    for (SynthVoice* voice : getVoices()) {
        voice->envelope.setParameters(params); // update all voice with new parameters
    }
}

