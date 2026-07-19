#!/bin/bash

# Compile object files
gcc -I include -c src/expressions/exp.c -o obj/exp.o
gcc -I include -c src/references/refs.c -o obj/refs.o
gcc -I include -c main.c -o obj/main.o

# Compile main
cd obj 

if gcc -Wall main.o exp.o refs.o -o ../c_notes; then 
    echo -e "\e[1;32mCompilation successful\e[0m" 
    ../c_notes
else 
    echo -e "\e[1;31mCompilation failed\e[0m"
    exit 1
fi 

