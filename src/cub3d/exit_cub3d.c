#include <stdlib.h>
#include <stdio.h>
#include "cub3d.h"

static const char	*g_error_msg[E_ERROR_COUNT] = {
[E_NO_ERROR] = "No error",
[E_INVALID_ARGUMENTS] = "Invalid arguments",
[E_MAP_ERROR] = "Invalid map",
[E_MAP_INVALID_EXTENSION] = "Invalid map extension",
[E_MAP_INVALID_DIMENTION] = "Invalid map dimentions",
[E_MAP_INVALID_PATH] = "Invalid map path",
[E_MAP_INVALID_CHAR] = "Invalid character in map",
[E_TEXTURE_ERROR] = "Invalid texture",
[E_TEXTURE_INVALID_PATH] = "Invalid texture path",
[E_ALLOCATION_FAILURE] = "Memory allocation failure",
};

static void	free_map(t_map *map)
{
	if (map->file.raw_data)
		free(map->file.raw_data);
}

void	exit_cub3d(t_cub3d *cub3d, t_errors code)
{
	free_map(&(cub3d->map));
	if (code)
		printf("Error: %s\n", g_error_msg[code]);
	exit(code > 0);
}
