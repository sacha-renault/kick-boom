/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 Oct 2024 12:16:05am
    Author:  LWZF9234

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice(Automation& pitchAtm) : pitchAutomation(pitchAtm) { }

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;  // Only play SynthSound objects
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    // get frequency for this note and set into the oscillator
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    oscillator.setFrequency(frequency);

    // note initialization for processing
    envelope.noteOn();
    position = 0;
    level = velocity;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    envelope.noteOff();
    if (!allowTailOff || !envelope.isActive())
        clearCurrentNote();
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    for (int sample = 0; sample < numSamples; ++sample)
    {

        // Get the pitch multiplier for the current sample
        float pitchMultiplier = pitchAutomation.getInterpolationAtSample(position);

        // Adjust the oscillator frequency for pitch changes
        oscillator.setFrequency(frequency * pitchMultiplier);
        
        // Generate the current sample from the oscillator
        float currentSample = oscillator.processSample(0.0f);

        // Apply the ADSR envelope to shape the sound over time
        currentSample *= envelope.getNextSample();

        // Write the generated sample to the audio buffer for each channel
        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        {
            outputBuffer.addSample(channel, startSample + sample, currentSample * level);
        }

        // Increment the position for each sample processed
        position++;
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    // TODO
}

void SynthVoice::controllerMoved(int controllerNumber, int newValue)
{
    // TODO
}
