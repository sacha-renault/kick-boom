/*
  ==============================================================================

    AutomationPoint.cpp
    Created: 18 Oct 2024 1:49:24pm
    Author:  alexi

  ==============================================================================
*/

#include "AutomationPoint.h"

// Set the default id to 0
std::atomic<unsigned int> AutomationPoint::globalId{ 0 };

// every automation point are initialized with the correct values + unique id
AutomationPoint::AutomationPoint(float samplePosition, float value) 
    : samplePosition(samplePosition), value(value), id(globalId++) { }
