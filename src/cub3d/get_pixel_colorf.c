/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_colorf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:47:52 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/12 17:30:45 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_color	get_color_from_color(union u_texture *tex, double x, double y)
{
	(void)x;
	(void)y;
	return (tex->color);
}

static t_color	get_color_from_tex(union u_texture *tex, double x, double y)
{
	t_texture_simple	*t;
	t_color				c;
	int					xi;
	int					yi;

	t = &(tex->texture);
	xi = (int)(x * (double)t->width);
	yi = (int)(y * (double)t->height);
	c.value = *((u_int32_t *)(t->raw + t->line_size * yi + (t->bpp / 8) * xi));
	return (c);
}

static t_color	get_color_from_animated(union u_texture *tex,
	double x, double y)
{
	size_t			idx;
	union u_texture	placeholder;

	idx = tex->animated_texture.current;
	placeholder.texture = tex->animated_texture.textures[idx];
	return (get_color_from_tex(&placeholder, x, y));
}

t_color (*const g_tex_lookup[3])(union u_texture *, double x, double y) = {
get_color_from_color,
get_color_from_tex,
get_color_from_animated};

t_color	get_pixel_colorf(t_cub3d *cub, t_point wall, double y)
{
	t_texture	*tex;
	t_texture_index idx;
	double 		x;

	if (wall.direction == NORTH)
	{
		idx = TEXTURE_NORTH;
		x = 1.0f - (float)((int)wall.x % TILE) / (float)TILE;
	}
	else if (wall.direction == SOUTH)
	{
		idx = TEXTURE_SOUTH;
		x = (float)((int)wall.x % TILE) / (float)TILE;
	}
	else if (wall.direction == WEST)
	{
		idx = TEXTURE_WEST;
		x = (float)((int)wall.y % TILE) / (float)TILE;
	}
	else
	{
		idx = TEXTURE_EAST;
		x = (float)((int)wall.y % TILE) / (float)TILE;
	}
	if (x < 0 || x > 1 || y < 0 || y > 1)
		exit_cub3d(cub, E_TEXTURE_ERROR);
	tex = cub->textures + idx;
	return (g_tex_lookup[tex->type](&(tex->u_data), x, y));
}