//
// Created by pierre on 2/6/24.
//
#include "cub3d.h"
#include "map.h"

static int check_map_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (E_MAP_INVALID_EXTENSION);
	if (ft_strncmp(filename + len - 4, ".cub", 4))
		return (E_MAP_INVALID_EXTENSION);
	return (E_NO_ERROR);
}

int load(t_cub3d *cub3d)
{
	t_errors	code;

	if (!check_map_extension(cub3d->map.file.filename))
		exit_cub3d(cub3d, E_MAP_INVALID_EXTENSION);
	code = load_map(&(cub3d->map));
	if (code)
		exit_cub3d(cub3d, code);
	return (0);
}