#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
      highPassFilterCurveAdjuster(0,
                                  p.paramID,
                                  false,
                                  adjusterComponentSize,
                                  adjusterComponentSize,
                                  true,
                                  true,
                                  adjusterSize,
                                  adjusterSize,
                                  p,
                                  p.highPassFilterCurveAdjuster,
                                  true,
                                  "high pass",
                                  "20hz",
                                  "20kHz"),
      lowPassFilterCurveAdjuster(0,
                                 p.paramID,
                                 false,
                                 true,
                                 true,
                                 adjusterComponentSize,
                                 adjusterComponentSize,
                                 adjusterSize,
                                 adjusterSize,
                                 p,
                                 p.lowPassFilterCurveAdjuster,
                                 true,
                                 "low pass",
                                 "20hz",
                                 "20kHz"),
      amplitudeCurveAdjuster(0,
                             p.paramID,
                             false,
                             true,
                             true,
                             adjusterComponentSize,
                             adjusterComponentSize,
                             adjusterSize,
                             adjusterSize,
                             p,
                             p.amplitudeCurveAdjuster,
                             true,
                             "gain",
                             "-inf",
                             "unity"),
      slider(p,
             p.paramID,
             0,
             WHITE,
             RED),
      modWindow(p,
                p.modProcessor,
                150.0f,
                150.0f,
                1,
                2,
                3,
                4,
                5,
                6,
                {"mod output"},
                {"hp", "lp", "gain"},
                BLACK,
                RED,
                BLUE,
                juce::Colours::lightgreen,
                RED,
                WHITE),
      modTab(WHITE, RED, "Modulation", 2.0f, 20.0f),
      presetComponent({"default",
                            "low pass fade",
                            "high pass fade",
                            "thin band pass fade",
                            "very adjustable dj filter",
                            "stair steps",
                            "spikes",
                            "dropout",
                            "wub",
                            "yara",
                            "micro bumps (Kyle Harris)"},
                      p.presetState)
{
    addAndMakeVisible(slider);

    slider.addListener(this);

    setSize (650, 400);
    addAndMakeVisible(highPassFilterCurveAdjuster);
    addAndMakeVisible(lowPassFilterCurveAdjuster);
    addAndMakeVisible(amplitudeCurveAdjuster);
    addAndMakeVisible(presetComponent);
    addAndMakeVisible(modTab);
    modTab.addListener(this);

    setWantsKeyboardFocus(true);

    //add listeners to override preset (with "*")
    highPassFilterCurveAdjuster.curveAdjusterEditor.handleChanged.addListener(this);
    lowPassFilterCurveAdjuster.curveAdjusterEditor.handleChanged.addListener(this);
    amplitudeCurveAdjuster.curveAdjusterEditor.handleChanged.addListener(this);

    startTimerHz(60);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    slider.removeListener(this);
    highPassFilterCurveAdjuster.curveAdjusterEditor.handleChanged.removeListener(this);
    lowPassFilterCurveAdjuster.curveAdjusterEditor.handleChanged.removeListener(this);
    amplitudeCurveAdjuster.curveAdjusterEditor.handleChanged.removeListener(this);
    presetComponent.presetSelection.removeListener(this);
    modTab.removeListener(this);
    stopTimer();
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    //main background
    g.fillAll (GREY);
    g.setColour (BLUE);
    g.fillRect(juce::Rectangle<int>(0, 0, adjusterComponentSize * 2 + 47, getHeight()));

    //background behind modulation
    g.setColour(WHITE);
    g.fillRect(juce::Rectangle<int>(0, defaultWindowHeight, defaultWindowWidth, modDropDownWindowYSize ));

    //name
    g.setFont (60.0f);
    g.setColour(juce::Colours::white);
    g.setOpacity(0.5f);
    g.drawFittedText("Shave", adjusterComponentSize + 37, 0, 200, 70, juce::Justification::centred, 1);
    g.drawFittedText("N", adjusterComponentSize + 148, 0, 200, 70, juce::Justification::centred, 1);
    g.drawFittedText("Fade", adjusterComponentSize * 2 + 42, 0, 200, 70, juce::Justification::centred, 1);

    //version #
    g.setFont(10.0f);
    g.drawFittedText("v1.0.4", 610, 45, 30, 10, juce::Justification::centred, 1);

    //me
    g.setFont (30.0f);
    g.drawFittedText("Synths of Self", 30, 5, 250, 50, juce::Justification::topLeft, 1);
    g.setFont (15.0f);
    g.drawFittedText("synthsofself.com", 30, 41, 250, 50, juce::Justification::topLeft, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto adjustersTotalWidth = adjusterComponentSize * 3.0f + 30.0f;
    auto xIncrement = adjusterComponentSize + 10.0f;
    auto sideMargin = (defaultWindowWidth - adjustersTotalWidth) / 2.0f;
    //const auto yForAdjusters = getHeight() - adjusterComponentSize;

    auto xForAdjuster = sideMargin + 17;
    auto yForAdjusters = defaultWindowHeight - adjusterComponentSize - sideMargin - 60;

    highPassFilterCurveAdjuster.setBounds(xForAdjuster, yForAdjusters, adjusterComponentSize, adjusterComponentSize);
    presetComponent.setBounds(xForAdjuster, defaultWindowHeight - 60, xIncrement + adjusterSize / 2 , 60);
    auto modWindowWidth = defaultWindowWidth - xForAdjuster * 2 + 8;
    modWindow.setBounds(xForAdjuster - 4, defaultWindowHeight, modWindowWidth, modDropDownWindowYSize);

    xForAdjuster += xIncrement;

    lowPassFilterCurveAdjuster.setBounds(xForAdjuster, yForAdjusters, adjusterComponentSize, adjusterComponentSize);

    xForAdjuster += xIncrement;

    amplitudeCurveAdjuster.setBounds(xForAdjuster, yForAdjusters, adjusterComponentSize, adjusterComponentSize);

    modTab.setBounds(getWidth() - 125, defaultWindowHeight - 30, 125, 30);
    slider.setBounds(sideMargin, highPassFilterCurveAdjuster.getY() - 90, adjustersTotalWidth, 100);

}

//TODO: does this actually need to be a slider listener? maybe not
void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider*)
{

}

void AudioPluginAudioProcessorEditor::valueChanged (juce::Value& v)
{
    if(v.refersToSameSourceAs(presetComponent.presetSelection)) //change in preset
    {
        int i = (int)presetComponent.presetSelection.getValue();
        if (i < presets.states.size())
        {
            SetCurveAdjustersToPreset(i);
        }
    }
    else                                                        //handle / curve was changed manually
    {
        presetComponent.presetHasBeenDeviatedFrom.setValue(1);
    }
}

void AudioPluginAudioProcessorEditor::buttonClicked (juce::Button* b)
{
    if (b == &modTab)
    {
        if (modTab.getToggleState())
        {
            setSize(defaultWindowWidth, defaultWindowHeight + modDropDownWindowYSize);
            addAndMakeVisible(modWindow);
        }
        else
        {
            setSize(defaultWindowWidth, defaultWindowHeight);
            removeChildComponent(&modWindow);
        }
    }
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    if (presetComponent.HasBeenInitialized)
    {
        presetComponent.presetSelection.addListener(this);
    }
}

void AudioPluginAudioProcessorEditor::SetCurveAdjustersToPreset(int presetIndex)
{
    highPassFilterCurveAdjuster.curveAdjusterEditor.ReplaceState(presets.states.at(presetIndex).hp);
    lowPassFilterCurveAdjuster.curveAdjusterEditor.ReplaceState(presets.states.at(presetIndex).lp);
    amplitudeCurveAdjuster.curveAdjusterEditor.ReplaceState(presets.states.at(presetIndex).amp);
}

