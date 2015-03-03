GFK
========

Gaming Fun Kit. A cross-platform C++ game framework which supports networked 2D/3D multiplayer games on Mac, Linux, Windows, and Android.

If you somehow stumbled upon this framework, I wouldn't recommend using it quite yet. There is still a lot of work to be done.

Dependencies
-------------------
- CMake
- A working C++ compiler with C++11 support
- OpenGL
- X11 for Linux
- libUUID for Linux
- Android SDK/NDK for Android builds

Build
------
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

Android Build
-------------

See [test/jet/android/installDebug.sh](test/jet/android/installDebug.sh), along with [test/jet/android/jni/Android.mk](test/jet/android/jni/Android.mk)
