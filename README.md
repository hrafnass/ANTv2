# ANTv2
***
## Table of Contents
1. [General Informations about ANTv2](#general-informations)
2. [Used Technologies](#used-technologies)
3. [Building & Installation](#building-&-installation)
4. [License](#license)

## General Informations about ANTv2
* Directories:
    1. [html](html) includes the html patterns for the calculated values.
    2. [qt](qt) includes all used submodules. The used qtmodules and tools are under the [GLPv3](COPYING) and the [LGPLv3](COPYING.LESSER):
        1. [qtbase]() for creating the essential libraries (qtcore, qtgui, ...) and all building tools (qmake, ...). Qmake is used to build all other modules and an easy way to create [ANTv2](#build-instruction). (In Work!)
        2. [qtsvg](qt/5.12.2/submodules/qtsvg-everywhere-src-5.12.2/) used for the svg-ressources. (In Work!)
    3. [Readme](Readme) has a full documentation about all possible functions and settings of the program. (In Work!)
    4. [src](src) ANTv2 source code under the [GPLv3](LICENSE).

## Used Technologies
* In Work

## Building & Installation
***
### Qt-submodules/libraries:
Who wants the complete Qt source code can click [here]() or download it from the Qt archieves or github repositories.
* Windows:
    * In Work

* Linux:
    * [Installation instruction](qt/INSTALL_LINUX.md)
    * If you want the [Qt website](https://doc.qt.io/qt-5/linux-building.html)

* MacOS
    * In Work

### ANTv2
* Building and Installing:
    * Windows:
        * run install.cmd path_where_you_want_to_install_antv2 
    * Linux:
        * run install.sh path_where_you_want_to_install_antv2

    path_where_you_want_to_install_antv2:   If you add no path the actuell directory is used.

    For everybody, who wants a prebuild windows version, download [here](https://github.com/hrafnass/Game).
    The install script needs a preinstall qt version and the shell must could access the qt and compiler tools (qmake, make, ...)

## Licenses
* GPLv3:
    * [qmake](qt/5.12.2/submodules/qtbase-everywhere-src-5.12.2/qmake/) (tool for building ANTv2 and the needed essentials and features)
    * ANTv2
* LGPLv3:
    * [QtSvg](qt/5.12.2/submodules/qtsvg-everywhere-src-5.12.2/)
    * [QtCore](qt/5.12.2/submodules/qtbase-everywhere-src-5.12.2/)
    * [QtGui](qt/5.12.2/submodules/qtbase-everywhere-src-5.12.2/)
    * [QtWidgets](qt/5.12.2/submodules/qtbase-everywhere-src-5.12.2/)
