#include "map.h"

t_errors	load_texture(const char *line, t_texture *tex, t_cub3d *cub)
{
	t_texture_simple	t;

	ft_memset(&t, 0, sizeof(t_texture_simple));
	while (*line && ft_isspace(*line))
		++line;
	if (!*line)
		return (E_TEXTURE_INVALID_PATH);
	t.data = mlx_xpm_file_to_image(cub->mlx.mlx, (char *)line, &t.width, &t.height);
	if (!t.data)
		return (E_TEXTURE_ERROR);
	tex->type = T_TEXTURE;
	tex->data.texture = t;
	return (E_NO_ERROR);
}