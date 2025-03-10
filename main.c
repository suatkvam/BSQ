#include "fr_readmap.h"

int main(int argc, char **argv)
{
    int fd;
    int i;

    if (argc == 1)
    {
        write(2, "No input file provided\n", 22);
        return (1);
    }
    
    i = 1;
    while (i < argc)
    {
        fd = ft_openfile(argv[i]);
        if (fd != -1)
        {
            ft_readfile(fd);
            close(fd);
        }
        i++;
    }
    return (0);
}