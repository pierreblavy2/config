#!/bin/sh

#require -std=c++17
#tested  -std=c++17 , -std=c++20, -std=c++23

rm -f config-example
g++ -O3 -std=c++23 -o config-example example.cpp ../config/config.cpp -I../
