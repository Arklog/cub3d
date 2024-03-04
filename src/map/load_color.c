/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:46:30 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/04 14:46:58 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static u_int8_t	strtobyte(const char *str, char **endptr)
{
	u_int64_t			v;
	char				*needle;
	static const char	*base = "0123456789";

	v = 0;
	*endptr = (char *)str + ft_strlen(str);
	while (str < *endptr)
	{
		v *= 10;
		needle = ft_strchr(base, *(str++));
		if (!needle)
		{
			*endptr = NULL;
			return (v);
		}
		v += (needle - base);
	}
	return (v);
}

static const char	*parse_one(char *line, u_int8_t *field, int last)
{
	char	*endptr;
	char	*end;
	char	*beg;
	long	v;

	while (*line && ft_isspace(*line))
		++line;
	beg = line;
	end = ft_strchr(line, (!last) * ',');
	if (!end)
		return (NULL);
	else
		*end = 0;
	v = strtobyte(beg, &endptr);
	if (endptr != end || v < 0 || v > 255)
		return (NULL);
	else
		*field = (u_int8_t)v;
	return (end + (!last));
}

t_errors	load_color(const char *line, t_texture *tex)
{
	t_color	c;

	ft_memset(&c, 0, sizeof(t_color));
	line = parse_one((char *)line, &c.r, 0);
	if (!line)
		return (E_COLOR_INVALID);
	line = parse_one((char *)line, &c.g, 0);
	if (!line)
		return (E_COLOR_INVALID);
	line = parse_one((char *)line, &c.b, 1);
	if (!line)
		return (E_COLOR_INVALID);
	tex->type = T_COLOR;
	tex->u_data.color = c;
	return (E_NO_ERROR);
}
