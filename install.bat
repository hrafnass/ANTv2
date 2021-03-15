$INSTALL_PATH=antv2

REM Build program directories
MD $INSTALL_PATH
MD $INSTALL_PATH\html
REM copies all needed files
COPY html\pattern.html INSTALL_PATH\html\pattern.html
COPY release\untitled.exe INSTALL_PATH\html\ANTv2.exe
COPY run_ant.bat INSTALL_PATH\run.bat
