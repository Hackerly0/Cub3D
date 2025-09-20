#include "cub.h"
#include <math.h>

uint32_t	get_pixel_color(mlx_texture_t *tex, int x, int y)
{
	int			i;
	uint8_t		*pixels;

	if (!tex || x < 0 || y < 0
		|| x >= (int)tex->width || y >= (int)tex->height)
		return (0xFF0000FF);
	pixels = tex->pixels;
	i = (y * tex->width + x) * 4;
	return ((pixels[i + 3] << 24) | (pixels[i] << 16)
		| (pixels[i + 1] << 8) | pixels[i + 2]);
}

mlx_texture_t	*get_wall_texture(t_cub *cub, int side, int step_x, int step_y)
{
	if (side == 0)
	{
		if (step_x > 0)
			return (cub->textures->east);
		return (cub->textures->west);
	}
	if (step_y > 0)
		return (cub->textures->south);
	return (cub->textures->north);
}

static void	init_ray_vars(t_cub *cub, int x, t_rays *ray)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIDTH - 1;
	ray->ray_x = cub->game->dir_x + cub->game->plane_x * camera_x;
	ray->ray_y = cub->game->dir_y + cub->game->plane_y * camera_x;
	ray->map_x = (int)cub->game->xp_pos;
	ray->map_y = (int)cub->game->yp_pos;
	if (ray->ray_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0f / ray->ray_x);
	if (ray->ray_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0f / ray->ray_y);
}

static void	init_steps(t_cub *cub, t_rays *ray)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (cub->game->xp_pos - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0f - cub->game->xp_pos) * ray->delta_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (cub->game->yp_pos - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0f - cub->game->yp_pos) * ray->delta_y;
	}
}

static void	perform_dda(t_cub *cub)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (cub->rays->side_x < cub->rays->side_y)
		{
			cub->rays->side_x += cub->rays->delta_x;
			cub->rays->map_x += cub->rays->step_x;
			cub->rays->side = 0;
		}
		else
		{
			cub->rays->side_y += cub->rays->delta_y;
			cub->rays->map_y += cub->rays->step_y;
			cub->rays->side = 1;
		}
		if (cub->rays->map_x < 0 || cub->rays->map_x >= cub->game->map_width
			|| cub->rays->map_y < 0 || cub->rays->map_y >= cub->game->map_height
			|| cub->game->map[cub->rays->map_y][cub->rays->map_x] == '1')
			hit = 1;
	}
}

static float	get_distance(t_cub *cub)
{
	float	dist;

	if (cub->rays->side == 0)
	{
		dist = (cub->rays->map_x - cub->game->xp_pos
				+ (1 - cub->rays->step_x) / 2.0f) / cub->rays->ray_x;
	}
	else
	{
		dist = (cub->rays->map_y - cub->game->yp_pos
				+ (1 - cub->rays->step_y) / 2.0f) / cub->rays->ray_y;
	}
	if (dist < 0.001f)
		dist = 0.001f;
	return (dist);
}
static void draw_wall(t_cub *cub, int x, int wall_height, int start, int end)
{
    mlx_texture_t *texture;
    float wall_x;
    int tex_x;
    float tex_step;
    float tex_pos;
    int y;
    
    // Calculate wall hit position
    if (cub->rays->side == 0)
        wall_x = cub->game->yp_pos + get_distance(cub) * cub->rays->ray_y;
    else
        wall_x = cub->game->xp_pos + get_distance(cub) * cub->rays->ray_x;
    
    wall_x -= floor(wall_x);
    
    // Get texture
    texture = get_wall_texture(cub, cub->rays->side, cub->rays->step_x, cub->rays->step_y);
    tex_x = (int)(wall_x * texture->width);
    
    // Flip texture for certain walls
    if ((cub->rays->side == 0 && cub->rays->step_x < 0) || 
        (cub->rays->side == 1 && cub->rays->step_y > 0))
        tex_x = texture->width - tex_x - 1;
    
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= (int)texture->width) tex_x = texture->width - 1;
    
    // Draw ceiling
    y = 0;
    while (y < start)
    {
        mlx_put_pixel(cub->textures->pixel_ray, x, y, cub->colors->ceil_col);
        y++;
    }
    
    // Draw textured wall
    tex_step = (float)texture->height / wall_height;
    tex_pos = (start - HEIGHT / 2 + wall_height / 2) * tex_step;
    
    y = start;
    while (y < end)
    {
        int tex_y = (int)tex_pos & (texture->height - 1);
        uint32_t color = get_pixel_color(texture, tex_x, tex_y);
        
        // Make y-side walls darker
        if (cub->rays->side == 1)
            color = (color >> 1) & 0x7F7F7F7F;
        
        mlx_put_pixel(cub->textures->pixel_ray, x, y, color);
        tex_pos += tex_step;
        y++;
    }
    
    // Draw floor
    y = end;
    while (y < HEIGHT)
    {
        mlx_put_pixel(cub->textures->pixel_ray, x, y, cub->colors->floor_col);
        y++;
    }
}
static void	draw_column(t_cub *cub, int x,float dist)
{
	int				wall_height;
	int				start;
	int				end;

	wall_height = (int)(HEIGHT / dist);
	start = (-wall_height / 2) + (HEIGHT / 2);
	end = (wall_height / 2) + (HEIGHT / 2);
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	draw_wall(cub, x, wall_height, start, end);
}

void	cast_ray(t_cub *cub, int x)
{
	float	dist;

	init_ray_vars(cub, x, cub->rays);
	init_steps(cub, cub->rays);
	perform_dda(cub);
	dist = get_distance(cub);
	draw_column(cub, x, dist);
}

int	ray(t_cub *cub)
{
	int	x;

	x = 0;
	cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
	if (!cub->textures->pixel_ray)
		return (1);
	while (x < WIDTH)
	{
		cast_ray(cub, x);
		x++;
	}
	mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
	return (0);
}
