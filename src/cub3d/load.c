//
// Created by pierre on 2/6/24.
//
#include "cub3d.h"
#include "map.h"

static int check_map_extension(const char *filename)
{
	static const u_int32_t	ext = 0x6275632e;
	size_t					len;

	len = ft_strlen(filename);
	if (len < 4 || *((u_int32_t *)(filename + len - 4)) != ext)
		return (E_MAP_INVALID_EXTENSION);
	return (E_NO_ERROR);
}

int load(t_cub3d *cub3d)
{
	t_errors	code;

	if (check_map_extension(cub3d->map.file.filename))
		exit_cub3d(cub3d, E_MAP_INVALID_EXTENSION);
	code = load_map(&(cub3d->map));
	if (code)
		exit_cub3d(cub3d, code);
	code = load_textures(cub3d);
	if (code)
		exit_cub3d(cub3d, code);
	return (E_NO_ERROR);
}