/*
  ==============================================================================

    AutomationPoint.h
    Created: 18 Oct 2024 1:49:24pm
    Author:  alexi

  ==============================================================================
*/

#pragma once

struct AutomationPoint {
    static unsigned int globalId;
    unsigned int id;
    float samplePostion;
    float value;
    AutomationPoint(float samplePostion, float value);
};