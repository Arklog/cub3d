#include "map.h"
#include "cub3d.h"

/**
 * Create a new buffer of size sn + nn and copy the content of src into it, then append app at the end of the buffer.
 * At the end free src, replace it with the new buffer and update the size.
 *
 * @warning app must not be null
 * @warning nsize must not be null
 *
 * @return the new buffer or NULL if an error occurred
 */
static void *memappend(void **src, void *app, size_t sn, size_t nn, size_t *nsize)
{
	size_t	nlen;
	void	*new;

	nlen = sn + nn;
	new = malloc(nlen);
	if (!new)
		return (NULL);
	ft_memcpy(new, *src, sn);
	ft_memcpy(new + sn, app, nn);
	if (*src)
		free(*src);
	*src = new;
	*nsize = nlen;
	return (new);
}

static t_errors split_map(char *data, t_map *map)
{
	size_t	n;
	size_t	i;

	n = ft_countc(data, '\n');
	if (!n)
		return (E_MAP_INVALID_DIMENSIONS);
	i = 0;
	map->buffer = malloc(sizeof(char *) * (n + 1));
	map->lines = map->buffer;
	if (!map->lines)
		return (E_ALLOCATION_FAILURE);
	map->nlines = n;
	map->lines[n] = NULL;
	while (i < n)
	{
		map->lines[i] = data;
		data = ft_strchr(data, '\n');
		if (data)
			*(data++) = 0;
		++i;
	}
	return (E_NO_ERROR);
}

t_errors	load_map(t_map *map) {
	int		fd;
	char	buffer[BUFFER_SIZE];
	ssize_t	n;

	fd = open(map->file.filename, O_RDONLY);
	if (fd < 0)
		return E_MAP_INVALID_PATH;
	n = read(fd, buffer, BUFFER_SIZE);
	while (n > 0)
	{
		if (!memappend((void **)&(map->file.raw_data), buffer, map->file.buffer_size, n, &(map->file.buffer_size)))
			return (close(fd), E_ALLOCATION_FAILURE);
		n = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	if (n < 0)
		return (E_IO_ERROR);
	else if (!memappend((void **)&(map->file.raw_data), "", map->file.buffer_size, 1, &(map->file.buffer_size)))
		return (E_ALLOCATION_FAILURE);
	return (split_map(map->file.raw_data, map));
}