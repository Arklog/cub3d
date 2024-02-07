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

t_errors	load_map(t_map *map) {
	int		fd;
	char	buffer[BUFFER_SIZE];
	size_t 	n;

	fd = open(map->file.filename, O_RDONLY);
	if (fd < 0)
		return E_MAP_INVALID_PATH;
	n = read(fd, buffer, BUFFER_SIZE);
	while (n > 0)
	{
		if (!memappend(map->file.raw_data, buffer, map->file.dlen, n, &(map->file.dlen)))
			return (E_ALLOCATION_FAILURE);
		n = read(fd, buffer, BUFFER_SIZE);
	}
	return (E_NO_ERROR);
}