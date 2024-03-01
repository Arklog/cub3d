#include "cub3d.h"
#include "mlx.h"
#include "map.h"

static t_errors load_one_texture(t_cub3d *cub, const char *line, int8_t idx)
{
	t_texture	t;
	t_errors	code;

	ft_memset(&t, 0, sizeof(t_texture));
	if (texture_is_color(line))
		code = load_color(line, &t);
	else if (texture_is_animated(line))
		code = load_animated(line, &t, cub);
	else if (texture_is_texture(line))
		code = load_texture(line, &t, cub);
	else
		return (E_TEXTURE_ERROR);
	cub->textures[idx] = t;
	return (code);
}

static int8_t find_index(const char *line)
{
	if (*((u_int16_t *)line) == 0x4f4e)
		return (TEXTURE_NORTH);
	else if (*((u_int16_t *)line) == 0x4f53)
		return (TEXTURE_SOUTH);
	else if (*((u_int16_t *)line) == 0x4557)
		return (TEXTURE_WEST);
	else if (*((u_int16_t *)line) == 0x4145)
		return (TEXTURE_EAST);
	else if (*((u_int8_t *)line) == 0x46)
		return (TEXTURE_FLOOR);
	else if (*((u_int8_t *)line) == 0x43)
		return (TEXTURE_CEILING);
	else
		return (-1);
}

static int load_one(t_cub3d *cub, const char *line, u_int8_t *load_flags)
{
	int8_t	idx;

	(void)cub;
	while (*line && ft_isspace(*line))
		++line;
	if (!*line)
		return (E_NO_ERROR);
	idx = find_index(line);
	if ((*load_flags >> idx) & 1)
		return (E_TEXTURE_ALREADY_LOADED);
	else if (idx < 0)
		return (idx);
	else
		line += 1 + (idx < TEXTURE_FLOOR);
	*load_flags += 1 << idx;
	return (load_one_texture(cub, line, idx));
}

int load_textures(t_cub3d *cube)
{
	const char		**lines;
	unsigned int	i;
	u_int8_t		load_flags;

	load_flags = 0;
	lines = cube->map.lines;
	if (!lines)
		return (E_ALLOCATION_FAILURE);
	i = 0;
	while (lines[i] && !load_one(cube, lines[i], &load_flags))
		++i;
	if (load_flags != 63)
		return (E_TEXTURE_MISSING);
	while (ft_isspacestr(lines[i]))
		++i;
	cube->map.lines = lines + i;
	return (E_NO_ERROR);
}