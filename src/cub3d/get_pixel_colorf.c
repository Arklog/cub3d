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
	xi = x * t->width;
	yi = y * t->height;
	c.value = t->line_size * yi + (t->bpp / 8) * xi;
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

t_color	get_pixel_colorf(t_cub3d *cub, t_texture_index idx, double x, double y)
{
	t_texture	*tex;

	tex = cub->textures + idx;
	return (g_tex_lookup[tex->type](&(tex->u_data), x, y));
}

t_color	get_pixel_color(t_cub3d *cub, t_texture_index idx, int x, int y)
{
	return (get_pixel_colorf(cub, idx, x / TILE, y / TILE));
}
