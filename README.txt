meld-1.8

This is where people come to cling on to a gtk2/python2 version of meld-1.8.

Most dependencies are in deps/ readme's included, on Debian build/t with: 
dpkg-buildpackage -us -uc; dh_clean; dpkg-buildpackage -us -uc -nc -j5 --no-post-clean

Pre-built .debs are (to be once these fully ork) located in deps/deb , 
there are hacks and workarounds to have these build on modern systems, 
like pointing dh_python2 to dh_python3. ( not yet tested ).
I did build a 'full' python2 package using the debian/rules
from the Debian Buster version, this gave me the python2.pm i needed
to satisfy pycair. Version of .debs needs to be bumped to not have apt 
grab something of oldoldstable, that was why i started doing it this way in
the first place, it was simply a mess trying to have the dependencies for
meld-1.8 in place on a modern system, thankfully, everything does seem to 
actually work. 

The theme file to override meld's theme should be called ~/.gtkrc-2.0
A dark (and a bit green) theme is provided by default, a light theme
will be on todo. There is a red, green and blue version of the gtkrc
and (some of the) pixmapped images that lives in data/theme/dark/
