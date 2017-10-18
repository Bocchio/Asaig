# Asaig

As simple as it gets WAVE file player.

And because it's simple, it just reads PCM WAVE files ¯\\\_(ツ)\_/¯

Ended up using ALSA to write to the audio device. And because of that it isn't ANSI C :(

If you know a way to do that (that doesn't involve making a kernel module or is "deprecated", ehem I'm looking at you OSS) and it'd make this code ANSI please tell me.

Other than that it does just that: it plays a .wav file. The nice thing about this little piece of code it's that's more like a boilerplate for any other implementation (change a couple of things and you could have this working on a microcontroller I think).

It isn't as powerful as alsaplayer but, hey, it's extremely simple!