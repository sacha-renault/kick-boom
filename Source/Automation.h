/*
  ==============================================================================

    Automation.h
    Created: 18 Oct 2024 1:42:34pm
    Author:  alexi

  ==============================================================================
*/

#pragma once
#include <algorithm>
#include <vector>
#include "AutomationPoint.h"

class Automation {
public:
    float getInterpolationAtSample(int samplePosition);
    unsigned int addAutomationPoint(int position, float value);
    void removeAutomationPoint(unsigned int pointId);

private:
    std::vector<AutomationPoint> automationPoints;  // Vector of automation points
};