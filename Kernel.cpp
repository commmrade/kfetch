#include<Kernel.hpp>
#include <fstream>


std::string distroName()
{
    std::ifstream file;
    std::string result{"Not defined"};


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
                result = line.substr(start + 1, end - start - 1);
                break;
            }
        }
        file.close();        
    }
    return result;
}

std::string kernelVersion()
{
    std::ifstream file;
    std::string result{};

    
    file.open("/proc/version");
    if(file.is_open())
    {
        std::stringstream s;
        file >> s.rdbuf();
        std::string line = s.str();
        

        if(!line.empty())
        {
            uint start = 14;
            uint end = line.find_first_of("(");

            result = line.substr(start, end - start - 1);
        }
    }
    file.close();
    return result;
}

std::pair<int, int> systemUptime()
{
    std::ifstream file;
    std::pair<int, int> result;


    file.open("/proc/uptime");
    if(file.is_open())
    {
        std::stringstream s;
        file >> s.rdbuf();
        int mins;
        sscanf(s.str().c_str(), "%d", &mins);
        mins = mins / 60;
        

        result.first = mins / 60;
        result.second = mins % 60;

        file.close();
    }
    return result;
}

Ram ramUsage()
{
    std::ifstream file;
    Ram result{};


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
        result.usedRam = memUsed / 1024 / 1024.0f;
        result.totalRam = memTotal / 1024 / 1024.0f;
        //std::cout << (memUsed) / 1024 / 1024.0f << " / " << (memTotal) / 1024 / 1024.0f <<  " GB" << std::endl;
        file.close();
    }
    return result;
}
Ram swapUsage()
{
    std::ifstream file;
    Ram result;


    file.open("/proc/swaps");

    if(file.is_open())
    {
        //std::cout << "fdf\n";
        std::stringstream s;
        file >> s.rdbuf();
        std::string str;
        for(int i = 0; i <= 7; ++i)
        {
            s >> str;
        }
        result.totalRam = atoi(str.c_str()) / 1024 / 1024.0f;
        s >> str;
        result.usedRam = atoi(str.c_str()) / 1024 / 1024.0f;
        
        //std::cout << system.swap_total << std::endl;


        file.close();
    }
    return result;
}