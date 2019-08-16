# jANA
jANA is a modular synthesizer designed to perform sound synthesis at the highest level of quality possible. It implements techniques drawn from both traditional (subtractive) and less-traditional (FM) synthesizers with full user control over the precision of the computations it performs; the software will synthesize sound at any bit depth and any sample rate internally, reducing these only at the very end of the signal chain to convert to a format playable through commonly available digital audio hardware. The high quality of the result comes at a price, of course: the sound is not produced in real-time. However, the sound-generation engine is designed to take full advantage of the resources available in today's multicore computer systems by performing calculations in parallel as much as possible. It runs on both Windows and Linux, so give it a try today!
