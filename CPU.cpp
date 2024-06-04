#include<CPU.hpp>



std::string cpuName()
{
    std::ifstream file;
    std::string result;

    file.open("/proc/cpuinfo");

    if(file.is_open())
    {
        std::string line;
        while(std::getline(file, line))
        {
            if(line.contains("model name"))
            {
                result =  line.substr(line.find(":") + 2);
                break;
            }
        }
        file.close();
    }
    return result;
}