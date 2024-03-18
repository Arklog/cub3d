/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre </var/spool/mail/pierre>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:26:55 by pierre            #+#    #+#             */
/*   Updated: 2024/03/18 15:29:11 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stack.h"
#include "map.h"

/**
 * Generate surrounding positions and push them to
 * the stack if not already checked
 * @param stack
 * @param cpos
 * @param checkbuff
 */
static t_errors	gen_new_pos_and_push(t_posstack **stack,
			t_pos cpos, char **checkbuff, t_map *map)
{
	t_pos	newpos[4];
	t_pos	c;
	int		i;

	newpos[0] = (t_pos){cpos.x + 1, cpos.y};
	newpos[1] = (t_pos){cpos.x - 1, cpos.y};
	newpos[2] = (t_pos){cpos.x, cpos.y + 1};
	newpos[3] = (t_pos){cpos.x, cpos.y - 1};
	i = 0;
	while (i < 4)
	{
		c = newpos[i++];
		if (!(c.x < 0 || c.y < 0
				|| (size_t)c.x >= map->width || (size_t)c.y >= map->height)
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
	t_posstack	*stack;

	stack = NULL;
	push(&stack, pos);
	checkbuff[pos.y][pos.x] = map->map[pos.y][pos.x];
	while (stack)
	{
		pop(&stack, &pos);
		if (map->map[pos.y][pos.x] == NONE)
			return (clear(&stack), E_MAP_INVALID_WALL);
		if (!(map->map[pos.y][pos.x] == WALL)
			&& gen_new_pos_and_push(&stack, pos, checkbuff, map))
			return (clear(&stack), E_ALLOCATION_FAILURE);
	}
	return (E_NO_ERROR);
}

t_errors	check_all_walls(t_map *map, char **checkbuff)
{
	int		i;
	int		j;
	char	tile;
	char	checkchar;

	i = 0;
	while (i < (int)map->height)
	{
		j = 0;
		while (j < (int)map->width)
		{
			tile = map->map[i][j];
			checkchar = checkbuff[i][j];
			if (tile == PATH && checkchar == CHECKBUFF_TOCHECK)
			{
				if (check_walls(map, checkbuff, (t_pos){j, i}))
					return (E_MAP_INVALID_WALL);
			}
			++j;
		}
		++i;
	}
	return (E_NO_ERROR);
}
