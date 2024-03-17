/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:21:13 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/04 14:42:47 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_longest_line(t_parser *parser)
{
	size_t	i;
	size_t	max;
	size_t	len;

	i = parser->line_index;
	max = 0;
	while (i < parser->nlines)
	{
		len = ft_strlen(parser->lines[i++]);
		if (len > max)
			max = len;
	}
	return (max);
}

t_errors	copy_line(const char *line, char *buffer, size_t max_len)
{
	size_t	len;
	size_t	remaining;

	len = ft_strlen(line);
	remaining = max_len - len;
	ft_memcpy(buffer, line, len);
	ft_memset(buffer + len, NONE, remaining);
	buffer[max_len] = 0;
	return (E_NO_ERROR);
}

t_errors	create_map(t_map *map)
{
	size_t	i;
	size_t	height;
	size_t	width;
	char	*buffer;

	height = map->height;
	width = map->width;
	buffer = map->buffer;
	map->map = malloc(sizeof(char *) * height);
	if (!map->map)
		return (E_ALLOCATION_FAILURE);
	i = 0;
	while (i < height)
	{
		map->map[i++] = buffer;
		buffer += width + 1;
	}
	return (E_NO_ERROR);
}

t_errors	parse_map(t_cub3d *cub)
{
	size_t		max_len;
	size_t		height;
	t_parser	*parser;
	t_map		*map;
	char		*buffer;

	parser = &(cub->parser);
	map = &(cub->map);
	max_len = get_longest_line(parser);
	height = parser->nlines - parser->line_index;
	map->buffer = malloc((max_len + 1) * height + 1);
	if (!cub->map.buffer)
		return (E_ALLOCATION_FAILURE);
	buffer = map->buffer;
	while (parser->line_index < parser->nlines)
	{
		copy_line(parser->lines[parser->line_index++], buffer, max_len);
		buffer += max_len + 1;
	}
	map->width = max_len;
	map->height = height;
	return (create_map(map));
}
