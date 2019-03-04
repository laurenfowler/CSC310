#!/bin/bash
c++ -c error_checking.cpp
echo making .o files
c++ -o myJtar jtar.cpp error_checking.o
echo compiling and linking
