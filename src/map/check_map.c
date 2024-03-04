/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:11:59 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/04 16:26:11 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>

#define CHECKBUFF_TOCHECK '#'

static t_errors	setup_map(t_map *map)
{
	size_t	i;
	char	*iter;

	i = 0;
	while (i < map->height)
	{
		iter = ft_strchr1(map->map[i], PLAYERSTR);
		if (iter)
		{
			map->starting_pos.x = iter - map->map[i];
			map->starting_pos.y = i;
			return (E_NO_ERROR);
		}
		++i;
	}
	return (E_MAP_NO_STARTPOS);
}

static t_errors	create_map_check_buffer(t_map *map, char ***placeholder)
{
	char	**buff;
	size_t	i;

	buff = malloc(sizeof(char *) * (map->height + 1));
	if (!buff)
		return (E_ALLOCATION_FAILURE);
	ft_memset(buff, 0, sizeof(char *) * (map->height + 1));
	i = 0;
	while (i < map->height)
	{
		buff[i] = malloc(map->width + 1);
		if (!buff[i])
		{
			*placeholder = buff;
			return (E_ALLOCATION_FAILURE);
		}
		ft_memset(buff[i++], CHECKBUFF_TOCHECK, map->width + 1);
	}
	*placeholder = buff;
	return (E_NO_ERROR);
}

static void	free_split(char **buff)
{
	size_t	i;

	if (!buff)
		return ;
	i = 0;
	while (buff[i])
		free(buff[i++]);
	free(buff);
}

static void print_checkbuff(char **checkbuff)
{
	while (*checkbuff)
	{
		printf("%s\n", *checkbuff);
		++checkbuff;
	}
	printf("\n");
	fflush(stdout);
}

/**
 * @brief Check if the map is surrounded by walls
 * 
 * @param map			The map
 * @param checkbuff 	A buffer to check which positions have been checked
 * @param pos			The current position to check
 * 
 * @return t_errors 
 */
static t_errors	check_walls(t_map *map, char **checkbuff, t_pos pos)
{
	char	tile;
	t_pos	surrounding[4];

	if (pos.x < 0 || pos.y < 0)
		return (E_MAP_INVALID_WALL);
	print_checkbuff(checkbuff);
	tile = map->map[pos.y][pos.x];
	if (checkbuff[pos.y][pos.x] != CHECKBUFF_TOCHECK)
		return (E_NO_ERROR);
	else
		checkbuff[pos.y][pos.x] = tile;
	if (tile == WALL)
		return (E_NO_ERROR);
	else if (tile == NONE || !tile)
		return (E_MAP_INVALID_WALL);
	surrounding[0] = (t_pos){.x = pos.x, .y = pos.y + 1};
	surrounding[1] = (t_pos){.x = pos.x + 1, .y = pos.y};
	surrounding[2] = (t_pos){.x = pos.x - 1, .y = pos.y};
	surrounding[3] = (t_pos){.x = pos.x, .y = pos.y - 1};
	return (check_walls(map, checkbuff, surrounding[0])
		|| check_walls(map, checkbuff, surrounding[1])
		|| check_walls(map, checkbuff, surrounding[2])
		|| check_walls(map, checkbuff, surrounding[3]));
}

static t_errors check_invalid_char(t_map *map)
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
		return (E_MAP_INVALID_CHAR);
	++i;
	while (i < map->height)
	{
		if (ft_strchr1(map->map[i++], PLAYERSTR))
			return (E_MAP_INVALID_CHAR);
	}
	return (E_NO_ERROR);
}

t_errors	check_map(t_map *map)
{
	char	**tmpbuff;

	tmpbuff = NULL;
	if (setup_map(map))
		return (E_MAP_NO_STARTPOS);
	else if (check_invalid_char(map) || check_one_startpos(map))
		return (E_MAP_INVALID_CHAR);
	else if (create_map_check_buffer(map, &tmpbuff))
		return (free_split(tmpbuff), E_ALLOCATION_FAILURE);
	else if (check_walls(map, tmpbuff, map->starting_pos))
		return (free_split(tmpbuff), E_MAP_INVALID_WALL);
	free_split(tmpbuff);
	return (E_NO_ERROR);
}
