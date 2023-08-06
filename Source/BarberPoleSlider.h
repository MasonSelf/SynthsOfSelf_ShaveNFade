/*
  ==============================================================================

    BarberPoleSlider.h
    Created: 27 Jun 2023 2:31:48pm
    Author:  Mason Self

  ==============================================================================
*/

#pragma once
#include "ColorDefines_ShaveNFade.h"
#include "BinaryData.h"
#include <sliders_sos/sliders_sos.h>

class BarberPoleSlider : public SOSSliderHorizontal
{
public:
    
    BarberPoleSlider(AudioPluginAudioProcessor& p, const juce::Identifier& paramID ,int paramIndex, juce::Colour trackColor, juce::Colour fillColor)
    : SOSSliderHorizontal(p, paramID, paramIndex, trackColor, fillColor, juce::Colours::white)
    {
    }
    
    void paint(juce::Graphics& g) override
    {
        //track
        float left   = static_cast<float>(image.getWidth()) / 2.0f;
        float top    = static_cast<float>(getHeight()) / 2.0f - trackWidth / 2.0f;
        float right  = static_cast<float>(getWidth() - image.getWidth() / 2.0f);
        float bottom = static_cast<float>(getHeight()) / 2.0f + trackWidth / 2.0f;
        
        juce::Rectangle<float> trackRectangle {{left, top}, {right, bottom}};
        
        g.setColour(trackColor);
        g.setOpacity(0.5f);
        g.fillRoundedRectangle(trackRectangle, amountRounded);
        
        //track fill
        auto handleX = GetHandlePosition();
        auto trackFillRectangle = trackRectangle.withRight(handleX + 10.0f);
        g.setColour(trackFillColor);
        g.setOpacity(0.85f);
        g.fillRoundedRectangle(trackFillRectangle, amountRounded);
        
        //handle
        g.setOpacity(1.0f);
        g.drawImageAt(image, static_cast<int>(handleX), 27);
    }
    
    float GetHandlePosition()
    {
        //multiplier scales the normalized value minus the width of the handle for x origin to draw handle
        auto multiplier = (static_cast<float>(getWidth()) - image.getWidth())  / static_cast<float>(getWidth());
        float normalizedValue = getValue() / getRange().getEnd();
        return normalizedValue * getWidth() * multiplier;
    }
    
private:
    juce::Image image {juce::ImageCache::getFromMemory(BinaryData::barberPole_png, 3084)};
};
