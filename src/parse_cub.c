#include <cub3d.h>
#include "../GNL/get_next_line.h"

static int is_blank(const char *s)
{
    int i = 0;
    if (!s) return 1;
    while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
        i++;
    return s[i] == '\0';
}

static void rstrip_newline(char *s)
{
    int n;
    if (!s) return;
    n = (int)strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
    {
        s[n - 1] = '\0';
        n--;
    }
}

static int starts_with_id(const char *s, const char *id)
{
    int i = 0;
    if (!s || !id) return 0;
    while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
        i++;
    return (strncmp(s + i, id, strlen(id)) == 0);
}

static void parser_init(t_config *cfg)
{
    cfg->textures.north.path = NULL;
    cfg->textures.south.path = NULL;
    cfg->textures.west.path = NULL;
    cfg->textures.east.path = NULL;
    
    cfg->vars.map = NULL;
    cfg->vars.width = 0;
    cfg->vars.height = 0;
    cfg->vars.player.x = -1;
    cfg->vars.player.y = -1;
    cfg->vars.player.dir = 0;
    
    // Initialize colors to invalid values
    cfg->colors.floor.r = -1;
    cfg->colors.floor.g = -1;
    cfg->colors.floor.b = -1;
    cfg->colors.ceil.r = -1;
    cfg->colors.ceil.g = -1;
    cfg->colors.ceil.b = -1;
}

int parse_cub(const char *path, t_config *cfg)
{
    int fd, phase = 0, r;
    char *line;

    if (!path || !cfg) return 1;
    parser_init(cfg);

    fd = open(path, O_RDONLY);
    if (fd < 0) { 
        printf("Error\ncannot open file\n"); 
        return 1; 
    }

    while ((line = get_next_line(fd)))
    {
        rstrip_newline(line);

        if (phase == 0) // Header phase
        {
            if (is_blank(line)) { /* skip */ }
            else if (starts_with_id(line, "NO")) { 
                r = parse_tex_id(line, &cfg->textures.north.path); 
                if (r) { printf("Error\ninvalid NO\n"); free(line); close(fd); return 1; }
            }
            else if (starts_with_id(line, "SO")) { 
                r = parse_tex_id(line, &cfg->textures.south.path); 
                if (r) { printf("Error\ninvalid SO\n"); free(line); close(fd); return 1; }
            }
            else if (starts_with_id(line, "WE")) { 
                r = parse_tex_id(line, &cfg->textures.west.path); 
                if (r) { printf("Error\ninvalid WE\n"); free(line); close(fd); return 1; }
            }
            else if (starts_with_id(line, "EA")) { 
                r = parse_tex_id(line, &cfg->textures.east.path); 
                if (r) { printf("Error\ninvalid EA\n"); free(line); close(fd); return 1; }
            }
            else if (starts_with_id(line, "F")) { 
                r = parse_rgb(line, &cfg->colors.floor); 
                if (r) { printf("Error\ninvalid RGB for F\n"); free(line); close(fd); return 1; }
            }
            else if (starts_with_id(line, "C")) { 
                r = parse_rgb(line, &cfg->colors.ceil); 
                if (r) { printf("Error\ninvalid RGB for C\n"); free(line); close(fd); return 1; }
            }
            else if (is_map_line(line)) { 
                // Before switching to map phase, validate all headers are present
                if (validate_headers_complete(cfg)) {
                    free(line); close(fd); return 1;
                }
                phase = 1;
                // Process this line as first map line
            }
            else { 
                printf("Error\nunknown identifier\n"); 
                free(line); close(fd); return 1; 
            }
        }

        if (phase == 1) // Map phase
        {
            if (is_blank(line)) { 
                printf("Error\nblank line inside map\n"); 
                free(line); close(fd); return 1; 
            }
            push_map_line(&cfg->vars, line);
        }
        free(line);
    }
    close(fd);

    // Final validations
    if (!cfg->vars.map) {
        printf("Error\nno map found\n");
        return 1;
    }

    if (pad_map_rect(&cfg->vars)) {
        printf("Error\nalloc failed while padding\n");
        return 1;
    }

    // 1. Basic character validation
    if (validate_chars(&cfg->vars)) 
        return 1;

    // 2. Extract player (this replaces player char with '0')
    if (validate_and_extract_player(&cfg->vars)) 
        return 1;

    // 3. Flood fill validation (the main validation!)
    if (warp_flood_fill(&cfg->vars)) 
        return 1;

    printf("✓ All validations passed!\n");
    printf("✓ Player at (%d, %d) facing '%c'\n", 
           (int)cfg->vars.player.x, (int)cfg->vars.player.y, cfg->vars.player.dir);

    return 0;
}
