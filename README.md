# SND_AICA_fw
Free source code for the firmware loaded by Linux SND_AICA driver (for the SEGA Dreamcast soundcard)

## Licensing

The initial contents of this repository come from http://linuxdc.cvs.sourceforge.net/linuxdc/linux-sh-dc/sound/oss/aica/firmware/
The full code repository is declared as being licensed under GPLv2 (presumably because it is a port of the kernel to run on the SEGA Dreamcast).

Another copy of the firmware source code was available here:
http://sourceforge.net/p/cadcdev/kallistios/ci/master/tree/

And this is released under the KOS license according to the AUTHORS file of that repository:
http://sourceforge.net/p/cadcdev/kallistios/ci/master/tree/AUTHORS

A copy of the KOS licensing text (which is also made available in the LICENSE.KOS file in this repository) was found here:
https://github.com/multimediamike/dreamroq/blob/master/LICENSE.KOS

## Authors

Based on the comments in the souce files, these are the original authors of this:

* Dan Potter
* mrbrown
* Marcus

## Building

Install the the crosscompiler:

> sudo apt-get install gcc-arm-none-eabi

And run make to build the firmware image;

> make