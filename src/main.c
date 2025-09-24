#include "cub3d.h"   // your structs + parse_cub prototype
#include <stdio.h>   // printf

int main(int argc, char **argv)
{
    t_config cfg;

    if (argc != 2)
    {
        printf("Usage: %s map.cub\n", argv[0]);
        return (1);
    }
    if (parse_cub(argv[1], &cfg))
    {
        printf("Parsing failed\n");
        return (1);
    }
    printf("Parsing OK\n");
    return (0);
}
