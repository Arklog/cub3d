#include "map.h"
#include "cub3d.h"

/**
 * Create a new buffer of size sn + nn and copy the content of src into it, then append app at the end of the buffer.
 * At the end free src, replace it with the new buffer and update the size.
 *
 * @param	src	the source buffer
 * @param	app	the buffer to append
 * @param	sn	the size of the src buffer
 * @param	nn	the size of the app buffer
 * @param	nsize	a pointer to the size of the new buffer
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

static t_errors split_map(char *data, t_parser *parser)
{
	size_t	n;
	size_t	i;
	char	*buffer;

	n = ft_countc(data, '\n') + 1;
	if (!n)
		return (E_MAP_INVALID_DIMENSIONS);
	buffer = parser->buffer;
	parser->lines = malloc(sizeof(char *) * n);
	parser->nlines = n;
	if (!parser->lines)
		return (E_ALLOCATION_FAILURE);
	i = 0;
	while (i < n)
	{
		parser->lines[i++] = buffer;
		buffer = ft_strchr(buffer, '\n');
		if (buffer)
			*(buffer++) = 0;
	}
	return (E_NO_ERROR);
}

t_errors	load_map_file(const char *filename, t_parser *parser) {
	int		fd;
	char		buffer[BUFFER_SIZE];
	ssize_t		n;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return E_MAP_INVALID_PATH;
	n = read(fd, buffer, BUFFER_SIZE);
	while (n > 0)
	{
		if (!memappend((void **)&(parser->buffer), buffer, parser->buffer_size, n, &(parser->buffer_size)))
			return (close(fd), E_ALLOCATION_FAILURE);
		n = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	if (n < 0)
		return (E_IO_ERROR);
	else if (!memappend((void **)&(parser->buffer), "", parser->buffer_size, 1, &(parser->buffer_size)))
		return (E_ALLOCATION_FAILURE);
	return (split_map(parser->buffer, parser));
}
