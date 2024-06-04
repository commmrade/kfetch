#include<Packager.hpp>



int packagesCount(std::string &distro)
{
    
    if(distro == "Arch Linux")
    {
        FILE* pack = popen("pacman -Q | wc -l", "r");

        std::string buf;
        char ch;

        while((ch = fgetc(pack)) != EOF)
        {
            buf += ch;
        }
        pclose(pack);
        return atoi(buf.c_str());
        
    }
    else if(distro.contains("Ubuntu") || distro.contains("Debian"))
    {
        FILE* pack = popen("dpkg --get-selections | wc -l", "r");

        std::string buf;
        char ch;

        while((ch = fgetc(pack)) != EOF)
        {
            buf += ch;
        }
        pclose(pack);
        return atoi(buf.c_str());
    }
    else if(distro.contains("Fedora"))
    {
        FILE* pack = popen("dnf list installed | wc -l", "r");

        std::string buf;
        char ch;

        while((ch = fgetc(pack)) != EOF)
        {
            buf += ch;
        }
        pclose(pack);
        return atoi(buf.c_str());
    }
    else
    {
        return -1;
    }
}