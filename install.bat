@echo off


REM Ask where the installed qt bin folder is
set /p qt="Where did you installed Qt (qmake.exe) e.g. C:\Qt\5.12.2\mingw73_64\bin\, if you used the qt source code, given with the ANTv2 source code ? "
REM Ask where the wanted make.exe is
set /p make="Add the path to your wanted make.exe e.g. C:\Qt\Tools\mingw730_64\bin\mingw32-make.exe"
REM In which folder the user want to install
set /p main="Add your wanted install path "

REM variables for the needed folders of qt:
REM cut the bin folder
set qt=%qt:~0,-4%
set qt_bin=%qt%\bin\
set qt_plugins=%qt%\plugins\
echo "Changing temporarly the PATH variable for installation."
set PATH=%PATH%;%qt_bin%;%qt_plugins%

REM directories for the builded exe
set html=%main%\html
set bin=%main%\bin
set bit=%bin%\exe
set readme=%bit%\Readme
REM build variablen
REM build folder
set build_folder=%main%\build
REM qmake path
set qmake=%bin_folder%\qmake.exe

REM get the path of the ANTv2 folder without \
set antv2_folder=%~dp0
echo "ANTv2 Source location: "%antv2_folder%

REM build all needed folders
md %html%
md %bin%
md %bit%
md %readme%
md %build_folder%
echo "Created the directory structure for ANTv2."

REM add all other needed files
copy %antv2_folder%\html\pattern.html %html%
copy %antv2_folder%\Readme\Readme.pdf %readme%
echo "Added all other needed files."

REM change directory in build_folder
cd build_folder
start "" %qt_bin%\qmake.exe -o Makefile %antv2_folder%AntWinV2.pro
pause
echo "Runned qmake.exe."

REM Building ANTv2.exe - run make.exe in bin\exe
cd ..\bin\exe\
start "" %make% %build_folder%\Makefile
pause
echo "Runned make.exe"

REM create a run script
echo "set PATH="%PATH% > ANTv2.bat
echo " start ANTv2.exe" >> ANTv2.bat
echo "Created ANTv2.bat"
