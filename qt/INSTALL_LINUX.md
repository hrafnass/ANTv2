# 1. Linux - Qt - Installation:
***
## 1.1 Requirements:
* Compiler:
* GCC 7                    : openSUSE 15.x
* GCC 7                    : SUSE Linux Enterprise Server
* GCC 5.3.1 via devtoolset-4   : Red Hat Enterprise Linux 7.x
* GCC 7.x or later         : Ubuntu 18.04
* GCC (5 or later)         : Generic Linux

## 1.2. Building Qt in the ANTv2-Repository:
    1. Build qtbase (It has the essential modules (qtgui, ...) and tools (qmake, ...)):
```
        > SAVEPATH=~/Documents                                          # saves the path where ANTv2 is saved i.e ~/Documents
        > VERSION=5.12.2                                                # ANTv2 uses Qt5.12.2 
        > cd SAVEPATH/ANTv2/qt/5.12.2/submodules/qtbase-everywhere-src-%VERSION%/
        > sudo su                                                       # to install qt outside the build directory, it could be that you must be root
        > ./configure --opensource                                      # /usr/local/Qt-%VERSION% is the default dir; to change this use -prefix. e.g. ./configure -prefix ~/Documents.
        > make
        > make install
```
    2. Environment Variables:
        * shells:
            1. bash, ksh, zsh, sh (add in .profile):
```
                > PATH=/usr/local/Qt-%VERSION%/bin:$PATH    # add the bin folder of the installed Qt-Version in PATH - change the path, if you used -prefix to your bin directory path 
                > export PATH
```
            2. csh, tcsh (add in .login)
```
                > setenv PATH /usr/local/Qt-%VERSION%/bin:$PATH
```
    3. Build qtsvg:
```
        > cd SAVEPATH/ANTv2/qt/5.12.2/submodules/qtsvg-everywhere-src-%VERSION%/
        > qmake
        > make
        > make install
```
## 1.3 Other Qt-Versions:
For other suitable Qt source code versions, you only have to change VERSION and the source code path to your code.
