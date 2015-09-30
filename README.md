# si-units
## Summary
An implementation of a set of SI units, based on the Kg-m-s triplet.
It is a typesafe set of classes that behave coherently in regard with the operation applied to them 
(multiplication, division, addition…).
This lib requires a C++14-compliant compiler.

## Installation
This is a header-only lib. To use the whole library, just include the "Units.h" header into your 
source code.
For a smaller compilation time, the operator<< overloads on iostreams are defined in their own .cpp 
file. By default, you will need to add the "Units.cpp" to your build toolchain. To benefit from the 
header-only feature, you just have to #define UNITS_HEADER_ONLY just before #including the "Units.h" 
header.
