#!/bin/bash 

gcc -o pay pay.c 

if [[ "$1" == "-t" ]]; then
    ./pay                                 # Show the help menu
    ./pay -r 28 -h 50 -d 10 -t 0.17       # Test over time and double time
    ./pay -r 10 -h 30 -t 0.12             # No overtime or double time
    ./pay -r 6.25 -h 20 -d 5 -t 0.15      # Double time but no overtime
    ./pay -r 28 -h 50 -d 10 -t 0.17 -j    # Test json export
    echo ""                               # Newline 

fi

