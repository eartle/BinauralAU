# Binaural

This is a Mac OS X Audio Unit Effect plug-in.

It's an effect to process a mono sound source and make it appear to come from a particular direction in your headphones. 

## A brief explanation (from my understanding)

An impulse is played from a speaker and recorded with a stereo microphone inside a prostetic head, a micropahone in each ear. The recordings are called HRTFs (Head Related Transfer Functions). When you perform a discrete convolution with this and the input signal you apply back the characteristics of sound coming from the speaker source. If you take HRTFs from many positions around the prosphetic head you can then make sound appear to originate from all of those sound sources allowing you to place a sound anywhere.

# Dependencies

This project uses libsndfile to read the HRTFs which are .wav files. I've personally made a build of libsndfile without ogg, vorbis, or flac dependencies as they are not needed, but you can install through homebrew if that works for you.

`brew install libsndfile`

# Building

This project is built using cmake. The `.gitignore` is setup so that it ignores directories starting with `_` so your cmake build directory should start with that.

To build the project, for example, run these commands from the project root:

```
mkdir _build
cd _build
cmake ..
make install
```

Running cmake will download Apple's Core Audio Utility Classes to be built as a static library in `./etc`.

It will also download some HRTF zip files and unzip them into res to be included in the bundle.

`make install` will build and copy Binaural.component to your ~/Library/Audio/Plug-Ins/Components folder so that it will be found and loaded by apps that can load Audio Units (GarageBand etc).

You can also generate an Xcode project by running `cmake -G Xcode ..` if you'd prefer to develop in that IDE. I create the Xcode project in a seperate build folder `_xcode`.
