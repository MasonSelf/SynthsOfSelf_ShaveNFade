#pragma once

#include "TPTFilterSynthsOfSelf.h"
#include <sos_modulator/sos_modulator.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <sos_preset_component_base/sos_preset_component_base.h>
#include <sos_sliders/sos_sliders.h>
#include <sos_curve_adjuster/sos_curve_adjuster.h>
//#include <sos_IAudioProcessor/sos_IAudioProcessor.h>

//==============================================================================
class AudioPluginAudioProcessor  : public juce::AudioProcessor, public IAudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    juce::AudioProcessorValueTreeState & GetAPVTS() override;
    const juce::Array<juce::AudioProcessorParameter *> & GetParams() override;
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    const double smoothedRampLength {0.015};

    CurveAdjuster::CurveAdjusterProcessor highPassFilterCurveAdjuster;
    CurveAdjuster::CurveAdjusterProcessor lowPassFilterCurveAdjuster;
    CurveAdjuster::CurveAdjusterProcessor amplitudeCurveAdjuster;


    const juce::String paramID {"filternfade"};
    const juce::Identifier resetOrTriggerParamID {"resetOrTriggerParamID"};
    const juce::Identifier freezeParamID {"freezeParamID"};
    const juce::Identifier rateFreeParamID {"rateFreeParamID"};
    const juce::Identifier rateSyncParamID {"rateSyncParamID"};
    const juce::Identifier rateBlendParamID {"rateBlendParamID"};
    const juce::Identifier modAmpParamID {"modAmpParamID"};


    juce::AudioProcessorValueTreeState apvts;

    LFO_modProcessor modProcessor;
    PresetStateManager presetState;

private:
    TPTFilterSynthsOfSelf hpFilter, lpFilter;
    float gainTarget {1.0f};
    float hpTarget {0.0f};
    float lpTarget {1.0f};
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
