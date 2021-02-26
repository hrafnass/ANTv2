# 1. Windows - Qt - Installation:
***
## 1.1 Requirements:
* Compiler:
    * GCC 7.x or later
* Qt-submodules:
    * qtbase
    * qtsvg

## 1.2. Building Qt in the ANTv2-Repository:
    1. Build qtbase (It has the essential modules (qtgui, ...) and tools (qmake, ...)):
```
        > COPY Qt C:\Qt                                             # copies the Qt folder into C:\Qt - C:\Qt is the installation folder for Qt. If you want another directory change C:\Qt. Than you must change C:\Qt in all other settings.       
        > SET _ROOT=C:\Qt\5.12.2\
        > SET PATH=%_ROOT%\submodules\qtbase\bin;C:\qt\mingw64\bin; # set the right path for the qt - folder 
        > cd C:\Qt\5.12.2\submodules\qtbase                         # go into the qtbase directory
        > configure.bat -shared -debug-and-release -platform win32-g++ -qt-zlib -qt-pcre -qt-libpng -qt-libjpeg -qt-freetype -opengl desktop -opensource -confirm-license -make libs -nomake tools -nomake examples -nomake tests   # all settings which are needed for ANTv2
        > mingw32-make -j 4                                         # mingw32-make build the qt libs and tools. -j 4 sets the number of jobs.
        > mingw32-make -j 4 install                                 # installs the qtbase files
```

    2. Build qtsvg:
```
        > cd C:\qt\5.12.2\submodules\qtsvg                          # change the directory into qtsvg dir.
        > qmake.exe -o Makefile qtsvg.pro                           # creates the Makefile for qtsvg
        >                                                           # Wenn Fehler: ERROR: Missing CMake tests. Either create tests in tests/auto/cmake, or disable cmake config file creation with CONFIG-=create_cmake.
# dann CMAKE_MODULE_TESTS = '-' zu Beginn von qmake.conf einfügen
        > mingw32-make                                              # builds qtsvg
        > mingw32-make install                                      # install qtsvg
```
## 1.3 Other Qt-Versions:
For other suitable Qt source code versions, you only have to change VERSION and the source code path to your code.

## 2. Installation note:
* Windows File Paths over 260 Characters:
    * The Standard File Path length in Windows account for 260 Characters. You have to make sure that you don't come over this length. C:\Qt works for a normal Qt installation on Windows 10. If you use another, longer path the installation could fail.
* Antivirus software:
    * In the most times AV software should not make problems during the qt build. 
