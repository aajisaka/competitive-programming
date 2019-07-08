#!/bin/bash

# copy templates to code directory
mkdir -p code
cp template.cpp code/a.cpp
cp template.cpp code/b.cpp
cp template.cpp code/c.cpp
cp template.cpp code/d.cpp
cp template.cpp code/e.cpp
cp template.cpp code/f.cpp
cp template.cpp code/g.cpp

make -j4
