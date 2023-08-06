#pragma once

#include "PluginProcessor.h"
#include "Presets_SNF.h"
#include "BarberPoleSlider.h"
#include "ColorDefines_ShaveNFade.h"
#include <preset_component_base/preset_component_base.h>
#include <sos_curve_adjuster/sos_curve_adjuster.h>
#include <sos_drop_down_window/sos_drop_down_window.h>


//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
        public juce::Slider::Listener,
        public juce::Value::Listener,
        public juce::Button::Listener,
        public juce::Timer
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider*) override;
    void valueChanged (juce::Value& v) override;
    void buttonClicked (juce::Button* b) override;
    void timerCallback() override;

private:
    void SetCurveAdjustersToPreset(int presetIndex);

    AudioPluginAudioProcessor& audioProcessor;

    const float adjusterSize {175.0f};
    const float adjusterComponentSize{200.0f};

    const int defaultWindowWidth {650};
    const int defaultWindowHeight {400};
    const int modDropDownWindowYSize {230};

    CurveAdjusterComponent highPassFilterCurveAdjuster;
    CurveAdjusterComponent lowPassFilterCurveAdjuster;
    CurveAdjusterComponent amplitudeCurveAdjuster;
    BarberPoleSlider slider;
    LFO_modEditor modWindow;
    DropDownTab modTab;
    PresetComponentBase presetComponent;

    CurveAdjuster::Presets presets;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
