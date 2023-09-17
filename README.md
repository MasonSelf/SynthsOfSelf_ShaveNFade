# Shave N Fade
![Screenshot 2023-08-24 at 3.17.17 PM.png](..%2F..%2F..%2FSynths%20of%20Self%20Media%2FScreenshot%202023-08-24%20at%203.17.17%20PM.png)

Shave N Fade an audio effect plugin made with [JUCE](https://github.com/juce-framework/JUCE).
Combining control over high pass filter cutoff frequency, low pass filter cutoff frequency, and gain 
in one macro parameter, Shave N Fade facilates nuanced transitional fade in / out aesthetics.
Prominent [Curve Adjusters](https://github.com/MasonSelf/sos_curve_adjuster) offer deep scaling of each sub-parameter, catering to the
user's perception of the "feeling" of the macro control.
## Submodules

To facilitate code sharing with [Later Gator](https://github.com/MasonSelf/SynthsOfSelf_LaterGator) 
(and more plugins in the future), much of the codebase for this project is 
included in the following submodules:
* [sos_IAudioProcessor](https://github.com/MasonSelf/sos_IAudioProcessor)
* [sos_drop_down_window](https://github.com/MasonSelf/sos_drop_down_window)
* [sos_modulator](https://github.com/MasonSelf/sos_modulator)
* [sos_maths](https://github.com/MasonSelf/sos_maths)
* [sos_curve_adjuster](https://github.com/MasonSelf/sos_curve_adjuster)
* [sos_slider](https://github.com/MasonSelf/sos_sliders)
* [sos_preset_component_base](https://github.com/MasonSelf/sos_preset_component_base)

These submodules are included via the [Projucer](https://docs.juce.com/master/tutorial_new_projucer_project.html) as 
"user modules" in [ShaveNFade.jucer](https://github.com/MasonSelf/SynthsOfSelf_ShaveNFade/blob/main/ShaveNFade.jucer).

## End User Documentation

* [Written User Guide](https://www.masonself.com/shave-n-fade-manual)
* [Getting Started With Shave N Fade Video](https://youtu.be/bpdqnYLYeSA?si=Cu8Pf6Jlh2fLtvQu)




