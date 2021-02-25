REM Dateipfade:
REM g++.exe und gcc.exe
SET COMPILER=C:\qt\mingw64\bin\mingw32-make.exe
REM qmake.exe
SET QMAKE=C:\qt\Qt-5.12.2\bin\qmake.exe

REM Bauen der exe:
REM qmake.exe -o Makefile %PRO_FILE_NAME%
SET PATH=%PATH%C:\Qt\mingw64\bin;C:\Qt\Qt-5.12.2\bin
C:\qt\Qt-5.12.2\bin\qmake.exe -o Makefile AntWinV2.pro "CONFIG+=release"
mingw32-make

