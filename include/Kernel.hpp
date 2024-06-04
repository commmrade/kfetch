#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

struct Ram
{
    float usedRam;
    float totalRam;
};


std::string disroName();
std::string kernelVersion();
std::pair<int, int> systemUptime();

Ram ramUsage();

Ram swapUsage();

