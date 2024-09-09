# Installing on Linux

## Prerequisites

GStreamer is included in all Linux distributions. We recommend using the latest version of a fast moving distribution such as Fedora, Ubuntu (non-LTS), Debian sid or OpenSuse to get a recent GStreamer release.

All the commands given in this section are intended to be typed in from
a terminal.

> ![Warning](images/icons/emoticons/warning.svg)
Make sure you have superuser (root) access rights to install GStreamer.

## Install GStreamer on Fedora

Run the following command:

```
dnf install gstreamer1-devel gstreamer1-plugins-base-tools gstreamer1-doc gstreamer1-plugins-base-devel gstreamer1-plugins-good gstreamer1-plugins-good-extras gstreamer1-plugins-ugly gstreamer1-plugins-bad-free gstreamer1-plugins-bad-free-devel gstreamer1-plugins-bad-free-extras
```

## Install GStreamer on Ubuntu or Debian

Run the following command:

```
apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
```

## Building applications using GStreamer

The only other “development environment” that is required is
the `gcc` compiler and a text editor. In order to compile code that
requires GStreamer and uses the GStreamer core library, remember
to add this string to your `gcc` command:

```
pkg-config --cflags --libs gstreamer-1.0
```

If you're using other GStreamer libraries, e.g. the video library, you
have to add additional packages after gstreamer-1.0 in the above string
(gstreamer-video-1.0 for the video library, for example).

If your application is built with the help of libtool, e.g. when using
automake/autoconf as a build system, you have to run
the `configure` script from inside the `gst-sdk-shell` environment.

#### Getting the tutorial's source code

The source code for the tutorials can be copied and pasted from the
tutorial pages into a text file, but, for convenience, it is also available
in a GIT repository in the `subprojects/gst-docs/examples/tutorials` subdirectory.

The GIT repository can be cloned with:

```
git clone https://gitlab.freedesktop.org/gstreamer/gstreamer
```

#### Building the tutorials

```
gcc basic-tutorial-1.c -o basic-tutorial-1 `pkg-config --cflags --libs gstreamer-1.0`
```

Using the file name of the tutorial you are interested in
(`basic-tutorial-1` in this example).

> ![Warning](images/icons/emoticons/warning.svg) Depending on the GStreamer libraries you need to use, you will have to add more packages to the `pkg-config` command, besides `gstreamer-1.0`
> At the bottom of each tutorial's source code you will find the command for that specific tutorial, including the required libraries, in the required order.
> When developing your own applications, the GStreamer documentation will tell you what library a function belongs to.

#### Running the tutorials

To run the tutorials, simply execute the desired tutorial:

``` c
./basic-tutorial-1
```


### Building the tutorials with Meson
The GStreamer tutorials also support to be built with Meson. Therefore, they are built along with the rest of the project when you compile it. However, they can also be run individually. In the root folder of GStreamer:
``` 
meson setup builddir
```
This configures the building directory. Then, to compile and run a single tutorial:
``` 
meson compile -C builddir subprojects/gst-docs/examples/tutorials/basic-tutorial-1
```
``` 
./builddir/subprojects/gst-docs/examples/tutorials/basic-tutorial-1
```
#### Building and debugging using VSCode
VSCode allows to compile, debug, and execute targets using its [Meson extension](https://marketplace.visualstudio.com/items?itemName=mesonbuild.mesonbuild). This is ideal for junior developers who are not yet familiar with the command line and basic Meson commands.

Individual targets can be compiled separately by clicking on them in the left sidebar of the Meson extension. It also allows you to debug targets in the ["Run and Debug"](https://code.visualstudio.com/docs/editor/debugging) menu on the same sidebar.
