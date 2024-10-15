/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Oct 2024 12:16:05am
    Author:  LWZF9234

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// SynthSound.h
class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/) override
    {
        return true;
    }

    bool appliesToChannel(int /*midiChannel*/) override
    {
        return true;
    }
};

// SynthVoice.h
class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;  // Only play SynthSound objects
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        float frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        oscillator.setFrequency(frequency);
        level = velocity;
        envelope.noteOn();
    }

    void stopNote(float velocity, bool allowTailOff) override
    {
        envelope.noteOff();
        if (!allowTailOff || !envelope.isActive())
            clearCurrentNote();
    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            // Generate the current sample from the oscillator based on the set frequency
            float currentSample = oscillator.processSample(0.0f);  // Oscillator generates the waveform

            // Apply the ADSR envelope to shape the sound over time
            currentSample *= envelope.getNextSample();

            // Write the generated sample to the audio buffer for each channel
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample + sample, currentSample * level);  // Apply velocity (level)
            }
        }
    }


    void pitchWheelMoved(int newPitchWheelValue) override { }

    void controllerMoved(int controllerNumber, int newValue) override { }

private:
    //juce::dsp::Oscillator<float> oscillator{ [](float x) { return std::sin(x); } };  // Sine wave oscillator
    juce::dsp::Oscillator<float> oscillator{ [](float x) { return x < 0.0f ? -1.0f : 1.0f; } };  // Square wave
    juce::ADSR envelope;
    float level;
    float frequency;
    float phase = 0.0f;
};

