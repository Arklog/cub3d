/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:11:59 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/14 17:30:09 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "stack.h"
#include <stdio.h>



static t_errors	check_invalid_char(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!ft_strchr(MAP_ALLOWED_CHAR, map->map[i][j++]))
				return (E_MAP_INVALID_CHAR);
		}
		++i;
	}
	return (E_NO_ERROR);
}

static t_errors	check_one_startpos(t_map *map)
{
	size_t	i;

	i = map->starting_pos.y;
	if (ft_strchr1(map->map[i] + map->starting_pos.x + 1, PLAYERSTR))
		return (E_MAP_MULTIPLE_STARTPOS);
	++i;
	while (i < map->height)
	{
		if (ft_strchr1(map->map[i++], PLAYERSTR))
			return (E_MAP_MULTIPLE_STARTPOS);
	}
	return (E_NO_ERROR);
}

t_errors	check_map(t_map *map)
{
	char	**tmpbuff;

	tmpbuff = NULL;
	if (setup_map(map))
		return (E_MAP_NO_STARTPOS);
	else if (check_invalid_char(map))
		return (E_MAP_INVALID_CHAR);
	else if (check_one_startpos(map))
		return (E_MAP_MULTIPLE_STARTPOS);
	else if (create_map_check_buffer(map, &tmpbuff))
		return (free_split(tmpbuff), E_ALLOCATION_FAILURE);
	else if (check_all_walls(map, tmpbuff))
		return (free_split(tmpbuff), E_MAP_INVALID_WALL);
	free_split(tmpbuff);
	return (E_NO_ERROR);
}
