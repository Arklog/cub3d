/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:21:48 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/04 14:13:53 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "map.h"
#include "defines.h"

static t_errors	load_one_texture(t_cub3d *cub, const char *line, int8_t idx, const char *test)
{
	t_texture	t;
	t_errors	code;
	u_int8_t	fcid;
	u_int16_t	wid;

	ft_memset(&t, 0, sizeof(t_texture));
	fcid = *((u_int8_t *)test);
	wid = *((u_int16_t *)test);
	code = E_NO_ERROR;
	if (texture_is_color(line)
		&& wid != NORTH_ID && wid != SOUTH_ID && wid != WEST_ID && wid != EAST_ID)
		code = load_color(line, &t);
	else if (texture_is_animated(line))
		code = load_animated(line, &t, cub);
	else if (texture_is_texture(line) && fcid != FLOOR_ID && fcid != CEILING_ID)
		code = load_texture(line, &t, cub);
	else
		return (E_TEXTURE_ERROR);
	cub->textures[idx] = t;
	return (code);
}

static int8_t	find_index(const char *line)
{
	if (*((u_int16_t *)line) == NORTH_ID)
		return (TEXTURE_NORTH);
	else if (*((u_int16_t *)line) == SOUTH_ID)
		return (TEXTURE_SOUTH);
	else if (*((u_int16_t *)line) == WEST_ID)
		return (TEXTURE_WEST);
	else if (*((u_int16_t *)line) == EAST_ID)
		return (TEXTURE_EAST);
	else if (*((u_int8_t *)line) == FLOOR_ID)
		return (TEXTURE_FLOOR);
	else if (*((u_int8_t *)line) == CEILING_ID)
		return (TEXTURE_CEILING);
	else
		return (-1);
}

static int	load_one(t_cub3d *cub, const char *line, u_int8_t *load_flags)
{
	int8_t	idx;
	const char	*tmp;

	(void)cub;
	while (*line && ft_isspace(*line))
		++line;
	if (!*line)
		return (E_NO_ERROR);
	tmp = line;
	idx = find_index(line);
	if (idx < 0)
		return (E_TEXTURE_INVALID_INDEX);
	else if ((*load_flags >> idx) & 1)
		return (E_TEXTURE_ALREADY_LOADED);
	else
		line += 1 + (idx < TEXTURE_FLOOR);
	*load_flags += 1 << idx;
	return (load_one_texture(cub, line, idx, tmp));
}

t_errors	load_textures(t_cub3d *cube)
{
	const char		**lines;
	unsigned int	i;
	u_int8_t		load_flags;
	t_errors		err;

	load_flags = 0;
	lines = (const char **)(cube->parser.lines);
	i = 0;
	while (i < cube->parser.nlines && lines[i] && load_flags != TEXTURES_FLAG_FULL)
	{
		err = load_one(cube, lines[i++], &load_flags);
		if (err)
			return (err);
	}
	if (load_flags != TEXTURES_FLAG_FULL)
		return (E_TEXTURE_MISSING);
	cube->parser.line_index = i;
	return (E_NO_ERROR);
}
