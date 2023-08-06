/*
  ==============================================================================

    TPTFilterSynthsOfSelf.cpp
    Created: 4 May 2023 10:18:51am
    Author:  Mason Self

  ==============================================================================
*/

#include "TPTFilterSynthsOfSelf.h"

void TPTFilterSynthsOfSelf::Prepare(juce::dsp::StateVariableTPTFilterType filterType, juce::dsp::ProcessSpec spec, float initFreq)
{
    filter.prepare(spec);
    filter.setType(filterType);
    filter.setResonance(defaultResonance);
    filter.setCutoffFrequency(initFreq);
    filter.reset();
}

void TPTFilterSynthsOfSelf::SetCutoffFreqFromNormalizedInput(float normalizedInput)
{
    auto targetFreq = juce::jlimit(filterCutoffMin, filterCutoffMax, juce::mapToLog10(normalizedInput, filterCutoffMin, filterCutoffMax));
    filter.setCutoffFrequency(targetFreq);
}


