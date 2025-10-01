/* ************************************************************************** */
/*                                                                            */
/*   config_to_cub_transfer.c                                                */
/*   Transfer parsed configuration to raycasting structures                  */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h> 

/**
 * Converts RGB struct to uint32_t color format (RGBA)
 */
static uint32_t rgb_to_uint32(t_rgb rgb)
{
    return ((rgb.r << 24) | (rgb.g << 16) | (rgb.b << 8) | 0xFF);
}

/**
 * Transfers color configuration from parser to raycaster
 */
static int transfer_colors(t_config *cfg, t_cub *cub)
{
    // Copy RGB values to int arrays
    cub->colors->ceil[0] = cfg->colors.ceil.r;
    cub->colors->ceil[1] = cfg->colors.ceil.g;
    cub->colors->ceil[2] = cfg->colors.ceil.b;
    
    cub->colors->floor[0] = cfg->colors.floor.r;
    cub->colors->floor[1] = cfg->colors.floor.g;
    cub->colors->floor[2] = cfg->colors.floor.b;
    
    // Convert to uint32_t format for rendering
    cub->colors->ceil_col = rgb_to_uint32(cfg->colors.ceil);
    cub->colors->floor_col = rgb_to_uint32(cfg->colors.floor);
    
    return (0);
}

/**
 * Transfers texture paths from parser to raycaster
 */
static int transfer_texture_paths(t_config *cfg, t_cub *cub)
{
    cub->dir->north_path = ft_strdup(cfg->textures.north.path);
    if (!cub->dir->north_path)
        return (-1);
    
    cub->dir->south_path = ft_strdup(cfg->textures.south.path);
    if (!cub->dir->south_path)
        return (-1);
    
    cub->dir->east_path = ft_strdup(cfg->textures.east.path);
    if (!cub->dir->east_path)
        return (-1);
    
    cub->dir->west_path = ft_strdup(cfg->textures.west.path);
    if (!cub->dir->west_path)
        return (-1);
    
    // Set door path to NULL or default if you have doors
    cub->dir->door_path = NULL;
    
    return (0);
}

/**
 * Transfers map data from parser to raycaster
 */
static int transfer_map(t_config *cfg, t_cub *cub)
{
    int i;
    
    // Transfer map dimensions
    cub->game->map_height = cfg->vars.height;
    cub->game->map_width = cfg->vars.width;
    
    // Copy the map array
    cub->game->map = (char **)malloc(sizeof(char *) * (cfg->vars.height + 1));
    if (!cub->game->map)
        return (-1);
    
    i = 0;
    while (i < cfg->vars.height)
    {
        cub->game->map[i] = ft_strdup(cfg->vars.map[i]);
        if (!cub->game->map[i])
        {
            while (--i >= 0)
                free(cub->game->map[i]);
            free(cub->game->map);
            return (-1);
        }
        i++;
    }
    cub->game->map[i] = NULL;
    
    return (0);
}

/**
 * Transfers player position and direction from parser to raycaster
 */
static int transfer_player(t_config *cfg, t_cub *cub)
{
    // Transfer position (parser uses grid coordinates, add 0.5 for center)
    cub->game->xp_pos = cfg->vars.player.x + 0.5;
    cub->game->yp_pos = cfg->vars.player.y + 0.5;
    
    // Transfer facing direction
    cub->game->facing_dir = cfg->vars.player.dir;
    
    return (0);
}

/**
 * Main transfer function: copies all data from parser config to raycaster
 * 
 * @param cfg: Parsed configuration from parser
 * @param cub: Raycaster structure to populate
 * @return: 0 on success, -1 on failure
 */
int config_to_cub(t_config *cfg, t_cub *cub)
{
    if (!cfg || !cub)
        return (-1);
    
    // Transfer colors
    if (transfer_colors(cfg, cub) == -1)
        return (-1);
    
    // Transfer texture paths
    if (transfer_texture_paths(cfg, cub) == -1)
        return (-1);
    
    // Transfer map data
    if (transfer_map(cfg, cub) == -1)
        return (-1);
    
    // Transfer player data
    if (transfer_player(cfg, cub) == -1)
        return (-1);
    
    // Initialize door states if you have doors
    init_door_states(cub->game);
    
    return (0);
}

/**
 * Example usage in main:
 * 
 * int main(int argc, char **argv)
 * {
 *     t_config cfg;
 *     t_cub cub;
 *     
 *     // Parse the .cub file
 *     if (parse_cub(argv[1], &cfg) == -1)
 *         return (perr("Parse error"));
 *     
 *     // Initialize raycaster structures
 *     if (struct_init(&cub) == -1)
 *     {
 *         free_config(&cfg);
 *         return (perr("Init error"));
 *     }
 *     
 *     // Transfer data from parser to raycaster
 *     if (config_to_cub(&cfg, &cub) == -1)
 *     {
 *         free_config(&cfg);
 *         ft_free_struct(&cub, 1);
 *         return (perr("Transfer error"));
 *     }
 *     
 *     // Clean up parser config (data is now copied to cub)
 *     free_config(&cfg);
 *     
 *     // Continue with raycaster initialization
 *     facing_dir(&cub);  // Set up direction vectors
 *     
 *     // Start the game...
 *     
 *     return (0);
 * }
 */