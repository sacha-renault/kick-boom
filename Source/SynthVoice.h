/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Oct 2024 12:16:05am
    Author:  LWZF9234

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newValue) override;


    juce::dsp::Oscillator<float> oscillator{ [](float x) { return std::sin(x); } };  // Sine wave oscillator
    juce::ADSR envelope;
    float level;
    float frequency;
    float phase = 0.0f;
    int position = 0;

};


