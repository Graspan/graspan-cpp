#! /bin/bash

g++ -std=c++0x -ggdb merge.cpp minset.cpp minset.h -o merge

if [ "$1" = "gdb" ];
then
	gdb ./merge
else
	./merge
fi

rm -f merge
