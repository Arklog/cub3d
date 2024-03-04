/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:16:33 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/01 16:16:44 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static t_errors	check_dimensions(t_map *map)
{
	const char	**iter;
	size_t		width;
	size_t		height;

	height = 0;
	iter = map->lines;
	width = ft_strlen(*iter);
	while (iter)
	{
		if (ft_strlen(*iter) != width)
			return (E_MAP_INVALID_DIMENSIONS);
		++height;
		++iter;
	}
	return (E_NO_ERROR);
}

static t_errors check_char(t_map *map)
{
	const char **iter;
	const char	*line;

	iter = map->lines;
	while (iter)
	{
		line = *iter;
		while (line)
		{
			if (!ft_strchr(MAPFILE_CHARSET, *(line++)))
				return (E_MAP_INVALID_CHAR);
		}
		++iter;
	}
	return (E_NO_ERROR);
}

static t_errors	check_wall(t_map *map)
{
	const char **iter;
	char		*buff;
	int 		ok;

	buff = malloc(map->width + 1);
	if (!buff)
		return (E_ALLOCATION_FAILURE);
	buff[map->width] = 0;
	ft_memset(buff, '1', map->width);
	iter = map->lines;
	ok = 1;
	while (iter && ok)
	{
		if (((iter == map->lines || iter == map->lines + map->height - 1) && ft_strcmp(*iter, buff))
			|| ((*iter)[0] != '1' || (*iter)[map->width - 1] != '1'))
			ok = 0;
		++iter;
	}
	free(buff);
	return ((!ok) * E_MAP_INVALID_WALL);
}

t_errors	check_map(t_map *map)
{
	int code;

	code = check_char(map);
	if (code)
		return (code);
	code = check_dimensions(map);
	if (code)
		return (code);
	code = check_wall(map);
	if (code)
		return (code);
	return (E_NO_ERROR);
}
