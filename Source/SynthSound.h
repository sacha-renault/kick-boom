/*
  ==============================================================================

    SynthSound.h
    Created: 18 Oct 2024 11:53:20am
    Author:  alexi

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

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