/*
  ==============================================================================

    AutomationPoint.h
    Created: 18 Oct 2024 1:49:24pm
    Author:  alexi

  ==============================================================================
*/

#pragma once
#include <atomic>

struct AutomationPoint {
    static std::atomic<unsigned int> globalId;  // Static ID generator
    unsigned int id;                            // Unique ID for each AutomationPoint
    float samplePosition;                       // Position of the point
    float value;                                // Value at the point
    AutomationPoint(float samplePostion, float value);
};