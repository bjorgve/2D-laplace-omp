#!/bin/sh

ml purge
ml GCCcore/12.2.0
ml CMake/3.24.3-GCCcore-12.2.0

cmake -S . -B build
cmake --build build


