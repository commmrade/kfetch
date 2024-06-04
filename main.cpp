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

struct System
{
    std::string distro_name;
    std::string kernel_version;
    
    std::string uptime;

    int packages;

    std::string display_res;

    std::string DE_name;

    std::string cpu_name;
    std::string gpu_name;

    float ram_used;
    float ram_total;

    float swam_used;
    float swap_total;
    
};



int main(int, char**){

    System system;

    std::ifstream file;
    file.open("/etc/os-release");

    if(file.is_open())
    {
        std::string line;
        while(std::getline(file, line))
        {
            if(line.contains("PRETTY_NAME"))
            {
                uint start = line.find_first_of("\"");
                uint end = line.find_last_of("\"");
                system.distro_name = line.substr(start + 1, end - start - 1);
                break;
            }
        }
        file.close();        
    }
    file.open("/proc/version");
    if(file.is_open())
    {
        std::stringstream s;
        file >> s.rdbuf();
        std::string line = s.str();
        
        uint start = 14;
        uint end = line.find_first_of("(");

        system.kernel_version = line.substr(start, end - start - 1);
        file.close();
    }
    file.open("/proc/uptime");
    if(file.is_open())
    {
        std::stringstream s;
        file >> s.rdbuf();
        int mins;
        sscanf(s.str().c_str(), "%d", &mins);
        mins = mins / 60;
        
        system.uptime = std::format("{} hours, {} minutes", mins / 60, mins % 60);
        file.close();
    }
    //std::string packages_count = std::system("pacman -Q | wc -l");


    //Packages count
    if(system.distro_name == "Arch Linux")
    {
        FILE* pack = popen("pacman -Q | wc -l", "r");

        std::string buf;
        char ch;

        while((ch = fgetc(pack)) != EOF)
        {
            buf += ch;
        }
        pclose(pack);
        system.packages = atoi(buf.c_str());
        
    }
    else if(system.distro_name.contains("Ubuntu") || system.distro_name.contains("Debian"))
    {
        FILE* pack = popen("dpkg --get-selections | wc -l", "r");

        std::string buf;
        char ch;

        while((ch = fgetc(pack)) != EOF)
        {
            buf += ch;
        }
        pclose(pack);
        system.packages = atoi(buf.c_str());
    }
    else if(system.distro_name.contains("Fedora"))
    {
        FILE* pack = popen("dnf list installed | wc -l", "r");

        std::string buf;
        char ch;

        while((ch = fgetc(pack)) != EOF)
        {
            buf += ch;
        }
        pclose(pack);
        system.packages = atoi(buf.c_str());
    }
    else
    {
        system.packages = -1;
    }

    //TODO: Arch based-distros
    


    //Display resolution

    {
        FILE *res = popen("xrandr", "r");

        std::string display_info ;
        char ch;
        
        while((ch = fgetc(res)) != EOF)
        {
            display_info += ch;
        }
        pclose(res);
       
        uint start = display_info.find("current") + 8;
        uint end = display_info.find("maximum");

        //std::cout << display_info.substr(start, end - start - 2) << std::endl;
        system.display_res = display_info.substr(start, end - start - 2);    
    }

    //Finding which DE is used
    {
        FILE *de = popen("echo $XDG_CURRENT_DESKTOP", "r");

        std::string buf;
        char ch;


        while((ch = fgetc(de)) != EOF)
        {
            buf += ch;
        }
        pclose(de);

        system.DE_name = std::string(buf);
    }

    //Finding which CPU is used
    file.open("/proc/cpuinfo");

    if(file.is_open())
    {
        std::string line;
        while(std::getline(file, line))
        {
            if(line.contains("model name"))
            {
                system.cpu_name = line.substr(line.find(":") + 2);
                break;
            }
        }
        file.close();
    }

    //Finding which GPU is used
    {
        FILE* gpu = popen("lspci | grep VGA", "r");

        std::string buf;
        char sym;
        while((sym = fgetc(gpu)) != EOF)
        {
           buf += sym;
        }
        pclose(gpu);
        uint start = buf.find("Radeon");
        uint end = buf.find("]", start + 1);
        system.gpu_name = buf.substr(start, end - start);
        //std::cout << buf.substr(buf.find_last_of(":") + 2) << std::endl;
    }

    //Ram usage
    file.open("/proc/meminfo");

    if(file.is_open())
    {
        std::string line;
        int memTotal;
        int memUsed;
        while(std::getline(file, line))
        {
            if(line.contains("MemTotal")) {
                sscanf(line.c_str(), "MemTotal:  %d kB", &memTotal);
            }
            else if (line.contains("Active")) {
                sscanf(line.c_str(), "Active: %d kB", &memUsed);
            
            }
        }
        system.ram_used = memUsed / 1024 / 1024.0f;
        system.ram_total = memTotal / 1024 / 1024.0f;
        //std::cout << (memUsed) / 1024 / 1024.0f << " / " << (memTotal) / 1024 / 1024.0f <<  " GB" << std::endl;
        file.close();
    }

    //Swap usage
    file.open("/proc/swaps");

    if(file.is_open())
    {
        std::cout << "fdf\n";
        std::stringstream s;
        file >> s.rdbuf();
        std::string str;
        for(int i = 0; i <= 7; ++i)
        {
            s >> str;
        }
        system.swap_total = atoi(str.c_str()) / 1024 / 1024.0f;
        s >> str;
        system.swam_used = atoi(str.c_str()) / 1024 / 1024.0f;
        
        std::cout << system.swap_total << std::endl;


        file.close();
    }



    //PRINTIING DATA

    std::println("OS: {}", system.distro_name);
    std::println("Kernel: {}", system.kernel_version);
    std::println("Uptime: {}", system.uptime);
    std::println("Packages: {}", system.packages);
    std::println("Desktop Environment: {}", system.DE_name);
    std::println("CPU: {}", system.cpu_name);
    std::println("GPU: {}", system.gpu_name);
    std::println("RAM usage: {} / {} Gb", system.ram_used, system.ram_total);
    std::println("Swap usage: {} / {} Gb", system.swam_used, system.swap_total);
    

   
}
