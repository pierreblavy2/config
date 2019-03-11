# Features
* Parse simple hierarchical config files, see example.cpp and example.txt
* Can be extended to custom types, see example-extend-convert.hpp
* Can be extended to custom containers, see example-extend-container.hpp

# How to install
* Download the source code
* Extract src/lib/* to your library folder
* #include <config/config.hpp> to read config
* #include <config/convert_lexical.hpp> to add string to number conversions to config (require boost/lexical_cast)
* #include <container/xxx.hpp> to add support for the xxx container. xxx=array, deque, set, unordered_set, vector

# License
    Copyright : Pierre Blavy 2018
    License : GPL 3.0 or any later version
    
# Developpement versions 
The developpement version can be downloaded on
https://tentacule.be/fossil/cpp-config

