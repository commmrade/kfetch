#include<Desktop.hpp>


std::string displayRes()
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
    return display_info.substr(start, end - start - 2); 
}

std::string desktopEnv()
{
    FILE *de = popen("echo $XDG_CURRENT_DESKTOP", "r");

    std::string buf;
    char ch;


    while((ch = fgetc(de)) != EOF)
    {
        buf += ch;
    }
    pclose(de);
    buf.erase(buf.end() - 1, buf.end());
    return buf;
}