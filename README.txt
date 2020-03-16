If you want to re-link the AntV2 you first have to build Qt library and the used tools (qmake).
In this project was Qt5.12.2 and mingw used.
Download the Qt-library and toolchain to build Qt5.12.2 from https://github.com/hrafnass/qt5.12.2_build or
use git clone https://github.com/hrafnass/qt5.12.2_build.

Re-Linking:

1. create a Makefile from AntWinV2.pro
qmake -o Makefile AntWinV2.pro
