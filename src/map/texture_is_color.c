#include "map.h"

/**
 * Check if the line is a color, spaces can be present before and after the color. If last is false,
 * a comma must be present after the color. Spaces can be present before the comma.
 * @param line
 * @param last
 * @return
 */
static int	check_color(const char **line, int last)
{
	int ok;

	if (!**line)
		return (0);
	ok = 0;
	while (ft_isspace(**line))
		++(*line);
	while (ft_isdigit(**line))
		++(*line), ++ok;
	while (ft_isspace(**line))
		++(*line);
	if (!last && **line != ',')
		return (0);
	else if (!last)
		++(*line);
	return (ok <= 3 && ok > 0);
}

static int check_char(const char *line)
{
	return (ft_isdigit(*line) || *line == ',' || ft_isspace(*line));
}

int	texture_is_color(const char *line)
{
	const char	*iter;

	iter = line;
	while (*iter)
		if (!check_char(iter++))
			return (0);
	iter = line;
	return (check_color(&iter, 0) && check_color(&iter, 0) && check_color(&iter, 1));
}