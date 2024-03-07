/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:11:59 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/07 20:38:45 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "stack.h"
#include <stdio.h>

#define CHECKBUFF_TOCHECK ' '

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
			map->starting_pos.x = (int)(iter - map->map[i]);
			map->starting_pos.y = (int)i;
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
		ft_memset(buff[i], CHECKBUFF_TOCHECK, map->width);
		buff[i++][map->width] = 0;
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
 * Generate surrounding positions and push them to the stack if not already checked
 * @param stack
 * @param cpos
 * @param checkbuff
 */
static t_errors gen_new_pos_and_push(t_posstack **stack, t_pos cpos, char **checkbuff, t_map *map)
{
	t_pos	newpos[4];
	t_pos 	c;
	int i;

	newpos[0] = (t_pos){cpos.x + 1, cpos.y};
	newpos[1] = (t_pos){cpos.x - 1, cpos.y};
	newpos[2] = (t_pos){cpos.x, cpos.y + 1};
	newpos[3] = (t_pos){cpos.x, cpos.y - 1};
	i = 0;
	while (i < 4)
	{
		c = newpos[i++];
		if (!(c.x < 0 || c.y < 0 || (size_t)c.x >= map->width || (size_t)c.y >= map->height)
			&& checkbuff[c.y][c.x] == CHECKBUFF_TOCHECK)
		{
			if (push(stack, c))
				return (E_ALLOCATION_FAILURE);
			checkbuff[c.y][c.x] = map->map[c.y][c.x];
		}
	}
	return (E_NO_ERROR);
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
	t_posstack *stack;

	stack = NULL;
	push(&stack, pos);
	checkbuff[pos.y][pos.x] = map->map[pos.y][pos.x];
	while (stack)
	{
		pop(&stack, &pos);
		if (map->map[pos.y][pos.x] == NONE)
			return (clear(&stack), E_MAP_INVALID_WALL);
		if (!(map->map[pos.y][pos.x] == WALL) && gen_new_pos_and_push(&stack, pos, checkbuff, map))
			return (clear(&stack), E_ALLOCATION_FAILURE);
		print_checkbuff(checkbuff);
	}
	return (E_NO_ERROR);
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
