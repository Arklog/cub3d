/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:29:59 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/14 17:30:00 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

#define CHECKBUFF_TOCHECK ' '

t_errors	setup_map(t_map *map)
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

t_errors	create_map_check_buffer(t_map *map, char ***placeholder)
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

void	free_split(char **buff)
{
	size_t	i;

	if (!buff)
		return ;
	i = 0;
	while (buff[i])
		free(buff[i++]);
	free(buff);
}
