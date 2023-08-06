/*
  ==============================================================================

    TPTFilterSynthsOfSelf.h
    Created: 4 May 2023 10:18:51am
    Author:  Mason Self

  ==============================================================================
*/

#pragma once
#include <juce_dsp/juce_dsp.h>

class TPTFilterSynthsOfSelf
{
public:
    void Prepare(juce::dsp::StateVariableTPTFilterType filterType, juce::dsp::ProcessSpec spec, float initFreq);
    void SetCutoffFreqFromNormalizedInput(float normalizedInput);
    
    const float filterCutoffMin {25.0f}, filterCutoffMax{19990.0f}; 
    using tptFloatFilter = juce::dsp::StateVariableTPTFilter<float>;
    tptFloatFilter filter;
    
private:
    const float defaultResonance {0.7f}; //TODO: make this a user defined param
};
