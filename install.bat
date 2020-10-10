@echo off

REM define the paths for all needed directories
set main = ANTv2
REM directory for the html print pattern
set html = %main%\html
REM directory needed for the program
set bin = %main%\bin
set bit = %bin%\exe
set readme = %bit%\Readme
set imageformats = %bit%\imageformats
set platforms = %bit%\imageformats

REM Build the Antv2 exe
start qmake.exe
start make.exe

REM check if you choose an own installation directory or take the default
if [%1] == []
    md %main%
    md %html%
    md %bin%
    md %bit%
    md %readme%
    md %imageformats%
    md %platforms%
else
    set input = %1%\
    md %input%%main%
    md %input%%html%
    md %input%%bin%
    md %input%%bit%
    md %input%%readme%
    md %input%%imageformats%
    md %input%%platforms%

echo "Created the directory structure for ANTv2."

REM Ccopy the needed files
copy untitled.exe %bit%
copy html\pattern.html %html%
copy Readme\Readme.pdf %readme%

REM IN WORK - dlls aren't copied

REM echo "Copied all needed files"

    
