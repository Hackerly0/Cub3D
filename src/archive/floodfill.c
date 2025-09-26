/* Flood fill map validation for Cub3D */
#include "../include/cub3d.h"

/* Create a copy of the map for flood fill (so we don't modify original) */
static char **create_map_copy(t_vars *v)
{
    char    **copy;
    int     i;
    int     j;
    
    if (!v || !v->map)
        return (NULL);

    copy = malloc(sizeof(char *) * (v->height + 1));
    if (!copy)
        return (NULL);
        
    i = 0;
    while (i < v->height)
    {
        copy[i] = malloc(sizeof(char) * (v->width + 1));
        if (!copy[i])
        {
            // Cleanup on failure
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        
        j = 0;
        while (j < v->width)
        {
            copy[i][j] = v->map[i][j];
            j++;
        }
        copy[i][v->width] = '\0';
        i++;
    }
    copy[v->height] = NULL;
    return (copy);
}

/* Free the map copy */
static void free_map_copy(char **map_copy, int height)
{
    int i;
    
    if (!map_copy)
        return;
        
    i = 0;
    while (i < height)
    {
        free(map_copy[i]);
        i++;
    }
    free(map_copy);
}

/* Iterative version using a simple stack (recommended for large maps) */
typedef struct s_point
{
    int x;
    int y;
} t_point;

static int flood_fill_iterative(char **map, int start_y, int start_x, int height, int width)
{
    t_point *stack;
    int stack_size = 0;
    int stack_capacity = height * width;
    int top_y, top_x;
    
    /* Allocate stack */
    stack = malloc(sizeof(t_point) * stack_capacity);
    if (!stack)
        return (1);
    
    /* Push starting point */
    stack[stack_size].x = start_x;
    stack[stack_size].y = start_y;
    stack_size++;
    
    while (stack_size > 0)
    {
        /* Pop from stack */
        stack_size--;
        top_x = stack[stack_size].x;
        top_y = stack[stack_size].y;
        
        /* Check bounds */
        if (top_y < 0 || top_y >= height || top_x < 0 || top_x >= width)
        {
            free(stack);
            return (1); /* Error: reached outside bounds */
        }
        
        /* Check current cell */
        if (map[top_y][top_x] == '1' || map[top_y][top_x] == 'F')
            continue; /* Wall or already visited */
            
        if (map[top_y][top_x] == ' ')
        {
            free(stack);
            return (1); /* Error: reached space/void */
        }
        
        if (map[top_y][top_x] == '0')
        {
            /* Mark as visited */
            map[top_y][top_x] = 'F';
            
            /* Push all 4 neighbors */
            if (stack_size + 4 < stack_capacity)
            {
                stack[stack_size++] = (t_point){top_x, top_y - 1}; /* Up */
                stack[stack_size++] = (t_point){top_x, top_y + 1}; /* Down */
                stack[stack_size++] = (t_point){top_x - 1, top_y}; /* Left */
                stack[stack_size++] = (t_point){top_x + 1, top_y}; /* Right */
            }
        }
    }
    
    free(stack);
    return (0); /* Success */
}

/* Main validation function using flood fill */


/* Enhanced player extraction that works with flood fill */

