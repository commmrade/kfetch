#include "GPU.hpp"
#include <algorithm>
#include <cstdio>
#include <format>
#include<iostream>
#include<fstream>
#include <ostream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<sstream>
#include<print>
#include<stdexcept>
#include<chrono>
#include<Packager.hpp>
#include <colors.hpp>
#include<logos.hpp>
#include<CPU.hpp>
#include<Kernel.hpp>
#include<Desktop.hpp>
#include <utility>

struct System
{
    std::string distro_name;
    std::string kernel_version;
    std::pair<int, int> uptime;
    std::string display_res;
    std::string DE_name;
    std::string cpu_name;
    std::string gpu_name;

    int packages;

    Ram ram;
    Ram swap;
    
};



int main(int, char**){

    System system;

    std::ifstream file;
    file.open("/etc/os-release");

    system.distro_name = disroName();
    system.kernel_version = kernelVersion();

    system.uptime = systemUptime();
    //std::string packages_count = std::system("pacman -Q | wc -l");


    //Packages count
    system.packages = packagesCount(system.distro_name);

    //TODO: Arch based-distros
    


    //Display resolution

    system.display_res = displayRes();

    //Finding which DE is used
    system.DE_name = desktopEnv();

    //Finding which CPU is used
    system.cpu_name = cpuName();

    //Finding which GPU is used
    system.gpu_name = GPUName();

    //Ram usage
    system.ram = ramUsage();

    //Swap usage
    system.swap = swapUsage();



    //PRINTIING DATA

    if(system.distro_name.contains("Arch"))
    {
        std::cout << Logo::archlogo << std::endl;
    }
    else if(system.distro_name.contains("Ubuntu"))
    {
        std::cout << Logo::ubuntulogo << std::endl;
    }
    else if(system.distro_name.contains("Debian"))
    {
        std::cout << Logo::debianlogo << std::endl;
    }

    std::cout << "" << std::endl;
    std::println("{}OS{}: {}", BLUE, RESET, system.distro_name);
    std::println("{}Kernel{}: {}", BLUE, RESET, system.kernel_version);
    std::println("{}Uptime{}: {} / {}", BLUE, RESET, system.uptime.first, system.uptime.second);
    std::println("{}Packages{}: {}", BLUE, RESET, system.packages);
    std::println("{}DE{}: {}", BLUE, RESET, system.DE_name);
    std::println("{}CPU{}: {}", BLUE, RESET, system.cpu_name);
    std::println("{}GPU{}: {}", BLUE, RESET, system.gpu_name);
    std::println("{}RAM usage{}: {} / {} Gb", BLUE, RESET, system.ram.usedRam, system.ram.totalRam);
    std::println("{}Swap usage{}: {} / {} Gb", BLUE, RESET, system.swap.usedRam, system.swap.totalRam);
    

    
}
