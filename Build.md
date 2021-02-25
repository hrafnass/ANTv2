# Build ANTv2 from Source:
 
## Build for Windows:
    * This instructions work only with the [Qt install instructions](Qt/INSTALL_WIN.md).
 
``` 
     > SET PATH=%PATH%C:\Qt\Qt\5.12.2\submodules\qtbase\mkspecs;C:\Qt\mingw64\bin;C:\Qt\Qt-5.12.2\bin     # Add the needed paths to the PATH-Variable; mkspecs is for the config files, else the whole mkspecs
     > # folder must copied in the mkspecs folder of the Qt installation folder
     > qmake.exe -o Makefile AntWinV2.pro "CONFIG+=release"     # CONFIG+=release creates a release-version of ANTv2, without you create a debug version
     > mingw32-make
```
