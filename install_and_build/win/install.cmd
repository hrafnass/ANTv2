# copy the qt files in the wanted directory
SET _ROOT=C:\qt\5.12.2\
SET PATH=%_ROOT%\submodules\qtbase\bin;C:\qt\mingw64\bin;

# Basismodule bauen
cd C:\qt\5.12.2\submodules\qtbase
configure.bat -shared -debug-and-release -platform win32-g++ -qt-zlib -qt-pcre -qt-libpng -qt-libjpeg -qt-freetype -opengl desktop -opensource -confirm-license -make libs -nomake tools -nomake examples -nomake tests
mingw32-make -j 4
mingw32-make -j 4 install

# Svg module bauen
C:\qt\5.12.2\submodules\qtsvg
qmake.exe -o Makefile qtsvg.pro
# Wenn Fehler: ERROR: Missing CMake tests. Either create tests in tests/auto/cmake, or disable cmake config file creation with CONFIG-=create_cmake.
# dann CMAKE_MODULE_TESTS = '-' zu Beginn von qmake.conf einfügen
mingw32-make
mingw32-make install 
