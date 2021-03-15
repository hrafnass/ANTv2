REM Build program directories
MD antv2
MD antv2\html
REM copies all needed files
COPY html\pattern.html antv2\html\pattern.html
COPY release\untitled.exe antv2\html\ANTv2.exe
COPY run_ant.bat antv2\run.bat
