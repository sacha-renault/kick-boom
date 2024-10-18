/*
  ==============================================================================

    AutomationPoint.cpp
    Created: 18 Oct 2024 1:49:24pm
    Author:  alexi

  ==============================================================================
*/

#include "AutomationPoint.h"

// Set the default id to 0
unsigned int AutomationPoint::globalId = 0;

// every automation point are initialized with the correct values + unique id
AutomationPoint::AutomationPoint(float samplePostion, float value) 
    : samplePostion(samplePostion), value(value), id(globalId++) { }
