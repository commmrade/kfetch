#include<Desktop.hpp>
#include <cstdio>
#include <cstdlib>


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
std::string shellVersion()
{
    std::string shell_env(getenv("SHELL"));

    if(shell_env == "/usr/bin/bash")
    {
        FILE *shell = popen("bash --version", "r");
        std::string buf;
        char ch;
        
        while((ch = fgetc(shell)) != EOF)
        {
            buf += ch;
        }
        pclose(shell);

        uint start = buf.find("version") + 8;
        uint end = buf.find("(");

        return "bash " + buf.substr(start, end - start);
    }
    else if(shell_env == "/usr/bin/zsh")
    {
        FILE *shell = popen("zsh --version", "r");
        std::string buf;
        char ch;
        
        while((ch = fgetc(shell)) != EOF)
        {
            buf += ch;
        }
        pclose(shell);

        uint end = buf.find("(");
        return buf.substr(0, end - 1);
    }

    return "";
}