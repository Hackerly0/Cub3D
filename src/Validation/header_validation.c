#include <cub3d.h>

int validate_textures(t_config *cfg)
{
    if (!cfg->textures.north.path)
    {
        printf("Error\nMissing North texture (NO)\n");
        return (1);
    }
    if (!cfg->textures.south.path)
    {
        printf("Error\nMissing South texture (SO)\n");
        return (1);
    }
    if (!cfg->textures.east.path)
    {
        printf("Error\nMissing East texture (EA)\n");
        return (1);
    }
    if (!cfg->textures.west.path)
    {
        printf("Error\nMissing West texture (WE)\n");
        return (1);
    }
    return (0);
}

int validate_colors(t_config *cfg)
{
    // Note: Your current code doesn't initialize colors to invalid values
    // You should initialize them to -1 and check here
    // For now, assuming they're set if >= 0
    
    if (cfg->colors.floor.r < 0 || cfg->colors.floor.g < 0 || cfg->colors.floor.b < 0)
    {
        printf("Error\nMissing or invalid Floor color (F)\n");
        return (1);
    }
    if (cfg->colors.ceil.r < 0 || cfg->colors.ceil.g < 0 || cfg->colors.ceil.b < 0)
    {
        printf("Error\nMissing or invalid Ceiling color (C)\n");
        return (1);
    }
    return (0);
}

int validate_headers_complete(t_config *cfg)
{
    if (validate_textures(cfg))
        return (1);
    if (validate_colors(cfg))
        return (1);
    return (0);
}
