# SoundOfLife

<p>
The basic idea for this drone piece is to run a simulation of Conway’s Game of Life and map different output values to parameters controlling the audio output.
</p>

<p>
The basic program contains sixteen oscillators and four LFOs which define the bulk of the sound. After experimenting, I decided to divide the grid and assign each section to a different oscillator. At the most basic level, each cell influences the gain and panning of its parent oscillator.
</p>

<p>
One slight change I made to the original simulation is adding a fade value which allows for states in-between dead/alive, which I found very useful for creating transitions between each state update of the simulation.
</p>

<p>
The grid is initialised to a random state with each cell having an equal chance of being dead or alive.
</p>

<p>
I have also instantiated LFOs used to modulate the frequency of the main oscillator array.
</p>

<p>
Each oscillator in the main oscillator array is set to a frequency in relation to each other to recreate the harmonic series and as different oscillators fade in and out different tones are generated, then the LFOs mapped to the oscillator frequencies create aggressive and contrasting beatings between the sine tones.
</p>

<p>
I also use a gain scaling function to reduce the gain of the oscillators as a function of their frequency using pink noise as a reference.
</p>

<p>
The gain of each oscillator is obtained by summing the “fade” value in each cell and then normalising.
</p>

<p>
Pan is similarly calculated by summing the “fade” values while also taking into account the cell's y coordinate.
</p>

<p>
After applying gain and pan the output of all oscillators is summed and passed through a filter, which has cutoff modulated by a triangle wave LFO, a tanh distortion function and finally a reverb.
</p>
