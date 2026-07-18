#!/bin/bash

# Compile object files
gcc -I include -c src/expressions/exp.c -o obj/exp.o
gcc -I include -c main.c -o obj/main.o

# Compile main
cd obj 
gcc main.o exp.o -o ../c_notes

../c_notes

