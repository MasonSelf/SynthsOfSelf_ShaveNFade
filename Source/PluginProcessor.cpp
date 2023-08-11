#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include <testModule/testModule.h>
//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
       highPassFilterCurveAdjuster("highPassCurveAdjuster",
                                      1.0f,
                                      smoothedRampLength,
                                      {{{0.0f, 0.805f}, {0.0245f, 0.3257f}, {1.0f, 0.0f}}} ),
       lowPassFilterCurveAdjuster(   "lowPassCurveAdjuster",
                                     1.0f,
                                     smoothedRampLength,
                                     {{{0.0f, 0.0f}, {0.3428f, 0.70857f}, {1.0f, 1.0f}}} ),
       amplitudeCurveAdjuster(       "amplitueCurveAdjuster",
                                     1.0f,
                                     smoothedRampLength,
                                     {{{0.0f, 0.0f}, {0.0314357f, 0.5342857f}, {0.508571f, 0.542857f}},
                                      {{0.508571f, 0.542857f}, {0.9057142f, 0.5428571f}, {1.0f, 1.0f}}} ),

//TODO: parameter pack?

       apvts(*this, nullptr, juce::Identifier("audioProcesserValueTree"), {
               std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"filternfade", 1},
                                                           "Filter N Fade",
                                                           juce::NormalisableRange<float>(0.00000f, 1.00000f, 0.00001f), 1.00000f), //version hint in parameterID
               std::make_unique<juce::AudioParameterBool>(juce::ParameterID{resetOrTriggerParamID.toString(), 1},
                                                          "Reset / Trigger",
                                                          false),
               std::make_unique<juce::AudioParameterBool>(juce::ParameterID{freezeParamID.toString(), 1},
                                                          "Freeze",
                                                          false),
               std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{rateFreeParamID.toString(), 1}, //version int in param id
                                                           "Free Rate",                       //visible name
                                                           juce::NormalisableRange<float>(0.0f, 40.0f, 0.00001f, 0.3f),
                                                           1.0f), //skew factor
               std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{rateSyncParamID.toString(), 1},
                                                            "Sync Rate",
                                                            TempoSync::SyncStrings,
                                                            4),
               std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{rateBlendParamID.toString(), 1}, //version int in param id
                                                           "Rate Blend",                       //visible name
                                                           juce::NormalisableRange<float>(0.0f, 1.0f, 0.00001f),
                                                           0.5f),
               std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{modAmpParamID.toString(), 1}, //version int in param id
                                                           "Modulation Amplitude",                       //visible name
                                                           juce::NormalisableRange<float>(0.0f, 1.0f, 0.00001f),
                                                           1.0f),
       }),
       modProcessor("modulation",
                    apvts,
                    rateFreeParamID,
                    rateSyncParamID,
                    rateBlendParamID,
                    resetOrTriggerParamID,
                    freezeParamID,
                    modAmpParamID,
                    {"hp", "lp", "gain"})
{
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}


juce::AudioProcessorValueTreeState& AudioPluginAudioProcessor::GetAPVTS()
{
    return apvts;
}
const juce::Array<juce::AudioProcessorParameter *> & AudioPluginAudioProcessor::GetParams()
{
    return getParameters();
}
//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //smoothed vals reset
    highPassFilterCurveAdjuster.smoothedVal.Reset(sampleRate);
    lowPassFilterCurveAdjuster.smoothedVal.Reset(sampleRate);
    amplitudeCurveAdjuster.smoothedVal.Reset(sampleRate);

    //filter init
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.sampleRate = sampleRate;
    spec.numChannels = static_cast<juce::uint32>(getTotalNumOutputChannels());

    hpFilter.Prepare(juce::dsp::StateVariableTPTFilterType::highpass, spec, hpFilter.filterCutoffMin);
    lpFilter.Prepare(juce::dsp::StateVariableTPTFilterType::lowpass, spec, lpFilter.filterCutoffMax);

    modProcessor.Init(sampleRate);
}

void AudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& )
{

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //get tempo info
    auto playHeadData = getPlayHead()->getPosition();
    if (playHeadData.hasValue())
    {
        modProcessor.tempoData.ProcessTempoData(playHeadData);
    }
    
    modProcessor.Process(buffer.getNumSamples());

    auto hpMod = modProcessor.GetModdedVal("filternfade", "hp");
    auto lpMod = modProcessor.GetModdedVal("filternfade", "lp");
    auto gainMod = modProcessor.GetModdedVal("filternfade", "gain");

    //for traces
    //todo: implement inputX in getTranslatedOutput not here!
    highPassFilterCurveAdjuster.inputX.set(hpMod);
    lowPassFilterCurveAdjuster.inputX.set(lpMod);
    amplitudeCurveAdjuster.inputX.set(gainMod);

    hpTarget = highPassFilterCurveAdjuster.GetTranslatedOutput(hpMod);
    lpTarget = lowPassFilterCurveAdjuster.GetTranslatedOutput(lpMod);
    gainTarget = amplitudeCurveAdjuster.GetTranslatedOutput(gainMod);

    //iterate through samples
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {

        hpFilter.SetCutoffFreqFromNormalizedInput(highPassFilterCurveAdjuster.smoothedVal.GetNextValue(hpTarget));
        lpFilter.SetCutoffFreqFromNormalizedInput(lowPassFilterCurveAdjuster.smoothedVal.GetNextValue(lpTarget));

        auto smoothedGain = amplitudeCurveAdjuster.smoothedVal.GetNextValue(gainTarget);

        //iterate through channels
        //this is done on the inside loop so that each channel gets
        //the same gain target
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer (channel);
            channelData[i] = hpFilter.filter.processSample(channel, channelData[i]);
            channelData[i] = lpFilter.filter.processSample(channel, channelData[i]);
            channelData[i] *= smoothedGain;
        }
    }

}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    //SAVE STATE

    //create output stream
    juce::MemoryOutputStream stream(destData, false);

    //save adjusters
    highPassFilterCurveAdjuster.SaveState(apvts);
    lowPassFilterCurveAdjuster.SaveState(apvts);
    amplitudeCurveAdjuster.SaveState(apvts);

    //save preset state
    presetState.SaveState(apvts);
    modProcessor.SaveState(apvts);

    //write to stream
    apvts.state.writeToStream(stream);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //LOAD STATE

    juce::ValueTree tree = juce::ValueTree::readFromData(data, static_cast<size_t>(sizeInBytes));
    if (tree.isValid())
    {
        //load and remove curve adjusters from tree
        highPassFilterCurveAdjuster.LoadAndRemoveStateFromAPTVS(tree);
        lowPassFilterCurveAdjuster.LoadAndRemoveStateFromAPTVS(tree);
        amplitudeCurveAdjuster.LoadAndRemoveStateFromAPTVS(tree);

        //preset manager
        presetState.LoadStateAndRemoveFromAPTVS(tree);
        modProcessor.LoadAndRemoveStateFromAPTVS(tree);

        //restore rest of apvts (params)
        apvts.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
