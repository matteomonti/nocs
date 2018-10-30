# NOCS
NOCS (Not Only Colliding Spheres) exact 2D gas dynamics framework.
For documentation, visit docs folder.

## Compilation Instructions (Ubuntu 18.04 LTS only)

This barebone guide indicates how to compile a NOCS simulation written in the `src/main.cpp` file. I hope that this will be enough for most user-case scenarios... (I am working on Ubuntu 18.04 LTS WSL and it works!)

### Prerequisites

You will need the `clang` compiler with the `libc++` standard libraries, therefore I suggest you the following terminal commands:
```bash
$ sudo apt update
$ sudo apt upgrade
$ sudo apt install build-essential
$ sudo apt install clang
$ sudo apt install libc++-dev
```

This should be enough to install all the libraries required for the no graphical version of the simulation (e.g. a simulation without window rendering, obtained by executing the `make` command).

As for the graphical part, you will be required to download and install Graziano Servizi's library [passe-par-tout](http://www.physycom.unibo.it/labinfo/passe_par_tout.php).

After you have decompressed the `tar.gz` archive, open a terminal in the folder and execute the following commands:
```bash
$ sudo apt install libxt-dev libx11-dev libxext-dev
# if you wish to use the OpenGL backend of the library (you should)
$ sudo apt install glew-utils freeglut3-dev libglew1.5-dev libglu1-mesa-dev libgl1-mesa-glx
$ sudo bash installatore_di_passe_par_tout
```
And then you just press many times `enter` and hope for the best.
At the end of the library installation process you might notice (if you are italian) that the testing program at the end of the installation process DOES NOT START, that's because the graphical library installation program fails to update the shared library cache of the operating system. But worry not! Because you can do that by yourself with the following command:
```
$ sudo /sbin/ldconfig /usr/local/lib64
```
This will inform the system that the graphical shared library `libGG.so` actually exists somewhere in your system...

At this point, you should be able to even compile a program with a graphical rendering! Try that by using the command `make graphics` (but remember to use `make clean` if you already compiled stuff with the `make` command! Otherwise it will not recompile your code!).

Whatever happens during this process, **STAY DETERMINED.**