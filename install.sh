#!/bin/bash

# installation location
INSTALL_PATH=antv2

# create directories
mkdir $INSTALL_PATH

# copies all needed files and directories
cp -r html $INSTALL_PATH/ $INSTALL_PATH/
cp release/untitled $INSTALL_PATH/ANTv2
