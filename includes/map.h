//
// Created by pierre on 2/5/24.
//

#ifndef CUB3D_MAP_H
#define CUB3D_MAP_H

#include <fcntl.h>
#include <unistd.h>
#include "types.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include "mlx.h"
#include "ft_stdlib.h"

# define BUFFER_SIZE 4096

# define MAP_CHAR "01NSEW"

t_errors	load_map(t_map *map);

int 		texture_is_color(const char *line);

t_errors	load_color(const char *line, t_texture *tex);

int 		texture_is_animated(const char *line);

t_errors	load_animated(const char *line, t_texture *tex, t_cub3d *cub);

int 		texture_is_texture(const char *line);

t_errors	load_texture(const char *line, t_texture *tex, t_cub3d *cub);

t_errors	check_map(t_map *map);

#endif //CUB3D_MAP_H
