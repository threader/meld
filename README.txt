meld-1.8

This is where people come to cling on to a gtk2/python2 version of meld-1.8.

Most dependencies are in deps/ readme's included, on Debian build/t with: 
dpkg-buildpackage -us -uc; dpkg-buildpackage -us -uc -nc --no-post-clean

Pre-built .debs are located in deps/deb , there are hacks and workarounds
to have these build on modern Debian SID systems, like using dh_python3
in some cases, I did build a 'full' python2 package using the debian/rules
from the Debian Buster version, this gave me the python2.pm i needed
to satisfy pycairo, but i dont know if i will bother more with that 
so no need to install python2 from here, at least yet. I also need to
bump the version of these packages to have them interfer less with the
normal apt/dpkg operations, that was why i started doing it this way in
the first place, it was simply a mess trying to have the dependencies for
meld-1.8 in place on a modern system, thankfully, everything does seem to 
actually work. 

The theme file to override meld's theme should be called ~/.gtkrc-2.0
However i will focus on providing a dark theme and maybe a default clearlocks
or something, this black theme currently sometimes segfault's, and images
are loaded trough osmosis or telekenisis or something, it sometimes spews
the logs with not finding the images, but always finds the image. 
I'm just glad meld-1.8 could be coaxed to works at all with all opts, frankly.
