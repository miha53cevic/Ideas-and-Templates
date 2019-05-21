#!/bin/bash
g++ -std=c++17 -o app server.cpp main.cpp $(pkg-config --libs --cflags sfml-system sfml-network)
