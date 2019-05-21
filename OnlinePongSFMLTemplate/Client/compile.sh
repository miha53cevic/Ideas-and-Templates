#!/bin/bash
g++ -std=c++17 -o app main.cpp $(pkg-config --libs --cflags sfml-graphics sfml-system sfml-network)
