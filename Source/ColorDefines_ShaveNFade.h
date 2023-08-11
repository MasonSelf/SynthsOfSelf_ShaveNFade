/*
  ==============================================================================

    ColorDefines_ShaveNFade.h
    Created: 27 Jun 2023 4:20:20pm
    Author:  Mason Self

  ==============================================================================
*/

#pragma once
#define RED juce::Colour(254, 59, 40)
#define BLUE juce::Colour(23, 168, 255)
#define WHITE juce::Colour(240, 240, 236)
#define GREY juce::Colour(180, 188, 194)
#define BLACK juce::Colours::black

#define LEGIBLE_COLOR_ON_GREY (WHITE).interpolatedWith((GREY).contrasting(), 0.7f)
