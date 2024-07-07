#include<GPU.hpp>



std::string GPUName()
{
    FILE* gpu = popen("lspci | grep VGA", "r");

    std::string buf;
    char sym;
    while((sym = fgetc(gpu)) != EOF)
    {
        buf += sym;
    }
    pclose(gpu);

    if(!buf.empty())
    {
        uint start = buf.find("Radeon");
        uint end = buf.find("]", start + 1);
        return buf.substr(start, end - start);
    }
    return "Not defined";
    
}