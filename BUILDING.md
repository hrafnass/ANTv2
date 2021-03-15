# Building ANTv2
***
If you want to use the prebuild executable for Windows instead look at [https://github.com/hrafnass/ANTv2Exe](https://github.com/hrafnass/ANTv2Exe).

# Prerequisite Packages
***
To build ANTv2 and Qt from source code you need some packages.

# Required dependencies:
* C++-Compiler (GCC 7.x or later)
* Qt Framework (Qt 5.12.2)
    * The needed modules (qtbase, qtsvg) for ANTv2 are include in [libs](libs).

# Installing these packages

Use the following commands for installation:

### Debian / Ubuntu
```
        sudo apt-get install build-essential gcc g++ libqt5svg5-dev qtbase5-dev qt5-qmake
```

### Fedora /CentOS
```
        sudo yum install gcc g++ qt5-base-devel qt5-qtsvg-devel
```
## MacOS and OSX 11 and above
    * Install xcode commandline tools
        * Install the full 
        * Install only the commandline tools
            ```
                $ xcode-select --install
            ```
    * Install [Homebrew](https://brew.sh/)
        * e.g. install with:
            ```
                $ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
            ```
    * Install Qt:
        ```
            $ brew install qt
        ```
    * Add the following line in your .bash_profile file to add Qt to your environment Variable (PATH)
        ```
            export PATH=/usr/local/opt/qt/bin:$PATH
        ```
        
### Windows
* Installation instruction for the needed qt modules from source code in [libs](libs)
    * Build qtbase
    ```
        $ REM It copies the Qt folder into C:\Qt - C:\Qt is the installation folder for Qt. 
        $ REM If you want another directory change C:\Qt. Than you must change C:\Qt in all other settings.
        $ COPY Qt C:\Qt                                                    
        $ SET _ROOT=C:\Qt\5.12.2\
        $ REM Set the right path for the qt - folder 
        $ SET PATH=%_ROOT%\submodules\qtbase\bin;C:\qt\mingw64\bin;
        $ cd C:\Qt\5.12.2\submodules\qtbase
        $ REM All settings which are needed for ANTv2
        $ configure.bat -shared -debug-and-release -platform win32-g++ -qt-zlib -qt-pcre -qt-libpng -qt-libjpeg -qt-freetype -opengl desktop -opensource -confirm-license -make libs -nomake tools -nomake examples -nomake tests   
        $ REM Run the make from your prefered Compiler e.g. mingw32:
        $ REM mingw32-make build and install qtbase. -j 4 sets the number of jobs
        $ mingw32-make -j 4                                         .
        $ mingw32-make -j 4 install
    ```

    * Build qtsvg
    ```
        $ REM qtbase must installed bevor
        $ cd C:\qt\5.12.2\submodules\qtsvg
        $ REM creates the Makefile for qtsvg
        $ qmake.exe -o Makefile qtsvg.pro                          
        $ REM If: ERROR: Missing CMake tests. Either create tests in tests/auto/cmake, or disable cmake config file creation with CONFIG-=create_cmake and add CMAKE_MODULE_TESTS = '-' at top of qmake.conf.
        $ REM Run the make from your prefered Compiler e.g. mingw32:
        $ REM Build and install qtsvg
        $ mingw32-make                                             
        $ mingw32-make install                                     
    ```

# Building ANTv2

### Linux
    In Work

### macOS
    In Work

### Windows
* This instructions only work with the prior qt installation instruction. If you installed Qt in an other location you have to change the filepaths.

    ```
        $ REM Add the needed paths to the PATH-Variable; mkspecs is for the config files, else the whole mkspecs-folder must copied in the mkspecs folder of the Qt installation
        $ SET PATH=%PATH%C:\Qt\Qt\5.12.2\submodules\qtbase\mkspecs;C:\Qt\mingw64\bin;C:\Qt\Qt-5.12.2\bin
        $ REM CONFIG+=release creates a release-version of ANTv2, without you create a debug version
        $ qmake.exe -o Makefile AntWinV2.pro "CONFIG+=release"
        $ REM Run the make from your prefered Compiler e.g. mingw32:
        $ mingw32-make
    ```
    * If you want to run ANTv2 add the qt library paths at the environment variables or use [run_ant.bat](run_ant.bat)
