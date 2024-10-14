#!/bin/bash

SOURCEDIR=$PWD

if [ "$1" == "" ]; then
    MAKEFILES_TYPE='Unix Makefiles'
    BUILDDIR=$PWD"/build/"
    MESSAGE="Now run make in $BUILDDIR."
fi

if [ "$CMAKE_BINARY" == "" ]; then
    CMAKE_BINARY="cmake"
fi

echo "CMake binary      : $CMAKE_BINARY"
echo "Source directory  : $SOURCEDIR"
echo "Build directory   : $BUILDDIR"

mkdir -p $BUILDDIR
cd $BUILDDIR

$CMAKE_BINARY -G "$MAKEFILES_TYPE" . \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DBUILD_TESTING=ON \
    -DBUiLD_WITH_CCACHE=ON \
    $SOURCEDIR && echo "$MESSAGE"
