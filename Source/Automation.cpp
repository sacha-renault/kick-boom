/*
  ==============================================================================

    Automation.cpp
    Created: 18 Oct 2024 1:42:34pm
    Author:  alexi

  ==============================================================================
*/

#include "Automation.h"

#include "Automation.h"
#include <algorithm>

// Get the interpolated value at a specific sample position
float Automation::getInterpolationAtSample(int samplePosition) {
    if (automationPoints.empty()) {
        return 0.0f;  // Return 0 if there are no points
    }

    // If the sample position is before the first point, return the first point's value
    if (samplePosition <= automationPoints.front().samplePosition) {
        return automationPoints.front().value;
    }

    // If the sample position is after the last point, return the last point's value
    if (samplePosition >= automationPoints.back().samplePosition) {
        return automationPoints.back().value;
    }

    // Find the two points between which the sample position falls
    for (size_t i = 1; i < automationPoints.size(); ++i) {
        if (samplePosition <= automationPoints[i].samplePosition) {
            const AutomationPoint& prev = automationPoints[i - 1];
            const AutomationPoint& next = automationPoints[i];

            // Linear interpolation
            float t = (samplePosition - prev.samplePosition) / (next.samplePosition - prev.samplePosition);
            return prev.value + t * (next.value - prev.value);
        }
    }

    return 0.0f;  // Should not reach here
}

// Add a new automation point and return the unique ID of the created point
unsigned int Automation::addAutomationPoint(int position, float value) {
    // add the new point
    AutomationPoint newPoint(static_cast<float>(position), value);
    automationPoints.push_back(newPoint);

    // Sort the points by sample position after adding the new point
    std::sort(automationPoints.begin(), automationPoints.end(),
        [](const AutomationPoint& a, const AutomationPoint& b) {
            return a.samplePosition < b.samplePosition;
        });

    // Return the unique ID of the created point
    return newPoint.id;  
}

// Remove an automation point based on its unique ID
void Automation::removeAutomationPoint(unsigned int pointId) {
    // Find and erase the automation point with the matching ID
    auto it = std::remove_if(automationPoints.begin(), automationPoints.end(),
        [pointId](const AutomationPoint& point) {
            return point.id == pointId;
        });

    // remove the point
    if (it != automationPoints.end()) {
        automationPoints.erase(it, automationPoints.end());
    }
    // no need to do anything, will still be sorted
}
