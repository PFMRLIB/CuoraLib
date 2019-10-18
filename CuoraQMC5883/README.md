# CuoraQMC5883
## Description
CuoraQMC5883 is a simple library for QMC5883 3-Axis magnetic sensor.
## Structure
The library consists of two files:`CuoraQMC5883.h`(Header) and `CuoraQMC5883.c`(Source file).
## Functions,Macros and Constants
Detailed information on them are shown in the header file.
## Usage
1.Use `qmc5883_init()` to initialize the sensor.  
2.Use `qmc5883_read_all()` to read from the sensor.  
3.Use `qmc5883_get_azimuth()` to get azimuth from x and y data.
## Notes
1.QMC5883L is NOT similar to HMC5883L(e.g.QMC5883L has a different register map, and doesn't support idle mode).Please read their datasheets for detailed information.  
2.When using the library on Arduino or other C++ compliers, use an `extern "C"` block to wrap `#include` codes.  