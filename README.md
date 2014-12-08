# Binaural

This is a Mac OS X Audio Unit Effect plug-in.

It's an effect to create a 3D sound in your headphones by doing a discrete convolution (FIR (finite impulse response) filter) with the input and a HRTF (head related transfer function). 

## A brief explanation (from my understanding)

An impulse is played from a speaker and recorded with stereo speakers inside a prostetic head. This is the HRTF. When you perform a discrete convolution with this and the input signal for each ear you apply back the characteristics of sound coming from the speaker source. So a mono input signal can be split into a stereo signal and when played through headphones the listener will hear the input signal appear to originate from the location of the speaker around the prosphetic head. If you take HRTFs from many positions around the prosphetic head you can then make sound appear to originate from all of those sound sources allowing you to place a sound anywhere in 3D.

# Dependencies

This project uses libsndfile to read the HRTFs which are .wav files. I've made a build without ogg, vorbis, or flac dependencies, but you can install through homebrew if that works for you.

`brew install libsndfile`

# Building

This project is built using cmake. The .gitignore is setup so that it ignores directories starting with _ so start your cmake build directory should start with that.

To build the project, for example, run these commands from the project root:

```
mkdir _build
cd _build
cmake ..
make install
```

Running cmake will download Apple's Core Audio Utility Classes to be built as a static library in `./etc`.

It will also download some HRTF (head related transfer function) files into res to be included in the bundle.

`make install` will copy Binaural.component to your ~/Library/Audio/Plug-Ins/Components folder so that it will be found and loaded by apps that can load Audio Units (GarageBand etc).

You can also generate an Xcode project by running `cmake -G Xcode ..` if you'd prefer to develop in that IDE. I create the Xcode project in a seperate build folder `_xcode`.