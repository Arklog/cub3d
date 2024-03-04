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

static t_errors init_mlx(t_cub3d *cub)
{
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		return (E_MLX_INIT);
	cub->mlx.window = mlx_new_window(cub->mlx.mlx, 640, 480, "cub3d");
	if (!cub->mlx.window)
		return (E_MLX_WINDOW);
	return (E_NO_ERROR);
}

t_errors load_cub3d(const char *filename, t_cub3d *cub3d)
{
	t_errors	code;

	if (check_map_extension(filename))
		return (E_MAP_INVALID_EXTENSION);
	code = load_map_file(filename, &(cub3d->parser));
	if (code)
		return (code);
	code = init_mlx(cub3d);
	if (code)
		return (code);
	code = load_textures(cub3d);
	if (code)
		return (code);
	return (E_NO_ERROR);
}